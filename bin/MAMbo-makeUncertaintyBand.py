#!/usr/bin/env python

import os, sys, time
import optparse
sys.path.append( os.environ['MAMBODIR'] + "/python" )

from ProgressBar import *

from xml.etree import ElementTree

from ROOT import *

from math import sqrt, pow

########################################


class SampleWrapper:
   name        = ""
   file        = ""
   systematics = {}

class OutputType:
   unknown     = 0
   histogram   = 1
   graph       = 2
   both        = 3


########################################

def ReadFromExternalFile( hfilename ):
   hlist = []

   with open( hfilename, 'rt') as f:
      tree = ElementTree.parse( f )

   for node in tree.iter( "histogram" ):
      hlist += [ node.attrib.get('hpath') ]

   return hlist


#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


def ReadConfiguration( configFileName ):
   with open( configFileName, 'rt') as f:
      tree = ElementTree.parse(f)

   if tree == None:
      print "ERROR: cannot parse input file", configFileName
      exit(1)

   histograms_configuration = []
  
   for node in tree.iter( "histograms" ):
       if "file" in node.attrib:
          hfilename = node.attrib.get('file')
          print "INFO: histograms defined in external file", hfilename
          histograms_configuration = ReadFromExternalFile( hfilename )
       else:
          for node in tree.iter( "histogram" ):
             histograms_configuration += [ node.attrib.get('hpath') ]

   samples_configuration = {}
   for node in tree.iter( "sample" ):
      name = node.attrib.get('name')
      samples_configuration[name] = SampleWrapper()
      samples_configuration[name].name        = name
  
      fpath = node.attrib.get('file')
      if not fpath.startswith('/'): fpath = os.environ['MAMBOOUTPUTDIR'] + "/" + fpath
      samples_configuration[name].file        = TFile.Open( fpath )

      samples_configuration[name].systematics = {}
      for syst in node.iter("syst"):
         sname = syst.attrib['name']
         samples_configuration[name].systematics[sname] = {}
         for shift in syst.iter("shift"):
            side   = shift.attrib["side"]
            sfname = shift.attrib["file"]
            if not sfname.startswith('/'): sfname = os.environ['MAMBOOUTPUTDIR'] + "/" + sfname 
            samples_configuration[name].systematics[sname][side] = TFile.Open( sfname ) 

   return histograms_configuration, samples_configuration


####################################################


def GatherHistograms( hname, hpath ):
    hlist = {}

    for sample in samples_configuration:

        f = samples_configuration[sample].file
        if f == None:
            print "ERROR: invalid input file for sample", sample
        hsource = f.Get( hpath )

        if hsource == None:
            print "ERORR: invalid histogram", hpath, "for sample", sample, "in file", f.GetTitle()

        newname = "%s_%s" % ( sample, hname )
        hlist[sample] = hsource.Clone( newname )

        # smoothing
#        if sample in [ "qcd", "fakes", "Fakes", "QCD" ]: hlist[sample].Smooth()

        for syst,flist in samples_configuration[sample].systematics.iteritems():
           for side, fname in flist.iteritems():
              hsource = fname.Get( hpath )
              newname = "%s_%s_%s_%s" % ( sample, hname, syst, side )
              if hsource == None: print "ERROR: invalid histogram", sample, hname, syst, side
              hlist[newname] = hsource.Clone( newname )
#              if sample in [ "qcd", "fakes", "QCD", "Fakes" ]: hlist[newname].Smooth()

    return hlist


####################################################


def CreateROOTPath( path ):
    tokens = path.split( '/' )
    if len( tokens ) == 1:
        return gDirectory.GetDirectory(".")
    else:
        nextdir = tokens[0]

        if gDirectory.FindObject( nextdir ) == None:
            gDirectory.mkdir( nextdir )
        gDirectory.cd( nextdir )

        newpath = path.replace( tokens[0] + "/", "" )

        return CreateROOTPath( newpath )


####################################################


def DumpSystematicsToXMLFile( hpath, edges, points, uncertainty ):
    nbins = len( points )

    xmlfile.write( "<histogram hpath=\"%s\">\n" % hpath ) 

    xmlfile.write( "\t<nominal>" )
    for i in range(nbins):
       y_n = points[i]['n']
       xmlfile.write( "%f" % y_n )
       if i < nbins-1: xmlfile.write( "," )
    xmlfile.write( "</nominal>\n" )

    xmlfile.write( "\t<edges>" )
    for i in range(nbins+1):
       xl = edges[i]
       if xl.is_integer(): xmlfile.write( "%i" % xl )
       else: xmlfile.write( "%.2f" % xl )
       if i < nbins: xmlfile.write( "," )
    xmlfile.write( "</edges>\n" ) 
   

    for sname, syst in uncertainty.iteritems():
       xmlfile.write( "\t<uncertainty name=\"%s\">\n" % sname )

       xmlfile.write( "\t\t<u>")
       for i in range(nbins):    
          y_u = syst['u'][i]
          y_n = points[i]['n']
          dy_rel = 100. * y_u / y_n if not y_n == 0. else 0.
          sgn = "+" if dy_rel > 0. else ""
          xmlfile.write( "%s%4.3f" % ( sgn, dy_rel ) )
          if i < nbins-1: xmlfile.write( "," )
       xmlfile.write( "</u>\n")

       xmlfile.write( "\t\t<d>")
       for i in range(nbins):
          y_d = syst['d'][i]
          y_n = points[i]['n']
          dy_rel = -100. * y_d / y_n if not y_n == 0. else 0.
          sgn = "+" if dy_rel > 0. else ""
          xmlfile.write( "%s%4.3f" % ( sgn, dy_rel ) )
          if i < nbins-1: xmlfile.write( "," )
       xmlfile.write( "</d>\n")

       xmlfile.write( "\t</uncertainty>\n" )

    xmlfile.write( "</histogram>\n" )


#######################################


def CreateMergedHistograms( outputClass = OutputType.graph ):

    progress = ProgressBar( 0, len(histograms_configuration), 77, mode='static', char="#" )

    outfile = TFile.Open( outFileName, "RECREATE" )

    for hpath in histograms_configuration:
       outfile.cd()
	
       hname = hpath.split('/')[-1]

       #print "INFO: merging histogram", hpath

       hlist = GatherHistograms( hname, hpath )

       graph  = None
       points = None
       edges  = []
       nbins  = 0
       title  = ""
       total_uncertainty = {}

       for sample in samples_configuration.keys():
  
          h = hlist[sample]	

          if graph == None:

             newdir = CreateROOTPath( hpath )

             nbins = h.GetNbinsX()
             title = h.GetTitle()

             points = [ { 'n': 0., 'u': 0.,  'd': 0. } for i in range(nbins) ]
             edges  = [ 0. for i in range(nbins+1) ]

             graph = TGraphAsymmErrors()
             graph.SetName( hname )
             graph.SetTitle( title )

          sample_uncertainty = {}

          # fill nominal
          for i in range(nbins):
             points[i]['n'] += h.GetBinContent(i+1)
             edges[i] = h.GetBinLowEdge(i+1)
          edges[nbins] = h.GetBinLowEdge(nbins+1)

          # stat unc first
          sample_uncertainty['statonly'] = { 'u' : [ 0 ] * nbins, 'd' : [ 0 ] * nbins }

          if not total_uncertainty.has_key('statonly'):
              total_uncertainty['statonly']  = { 'u' : [ 0 ] * nbins, 'd' : [ 0 ] * nbins }
              total_uncertainty['statsyst'] = { 'u' : [ 0 ] * nbins, 'd' : [ 0 ] * nbins }
              total_uncertainty['systonly'] = { 'u' : [ 0 ] * nbins, 'd' : [ 0 ] * nbins }

          for i in range(nbins):
             sample_uncertainty['statonly']['u'][i] = h.GetBinError(i+1)
             sample_uncertainty['statonly']['d'][i] = h.GetBinError(i+1)

             points[i]['u'] += pow( sample_uncertainty['statonly']['u'][i], 2 )
             points[i]['d'] += pow( sample_uncertainty['statonly']['d'][i], 2 )
             total_uncertainty['statonly']['u'][i] += pow( sample_uncertainty['statonly']['u'][i], 2 )
             total_uncertainty['statonly']['d'][i] += pow( sample_uncertainty['statonly']['d'][i], 2 )
             total_uncertainty['statsyst']['u'][i] += pow( sample_uncertainty['statonly']['u'][i], 2 )
             total_uncertainty['statsyst']['d'][i] += pow( sample_uncertainty['statonly']['d'][i], 2 )
 
          # syst unc
          for systname in samples_configuration[sample].systematics.keys():
             if not total_uncertainty.has_key( systname ): 
                total_uncertainty[systname] = { 'u' : [ 0 ] * nbins, 'd' : [ 0 ] * nbins }

             sample_uncertainty[systname] = { 'u' : [ 0 ] * nbins, 'd' : [ 0 ] * nbins }

             hpattern = "%s_%s_%s_" % ( sample, hname, systname )

             for i in range(nbins):

                 # scheme: both positive 
                 dy_u = 0.
                 dy_d = 0.
                 if samples_configuration[sample].systematics[systname].has_key( "up" ):
                    h_u = hlist[hpattern+"up"]
                    h_d = hlist[hpattern+"down"]

                    dy_u = h_u.GetBinContent(i+1) - h.GetBinContent(i+1)
                    dy_d = h_d.GetBinContent(i+1) - h.GetBinContent(i+1) 

                 elif samples_configuration[sample].systematics[systname].has_key( "single" ):
                    h_sys = hlist[hpattern+"single"]

                    dy_u = h_sys.GetBinContent(i+1) - h.GetBinContent(i+1)
                    dy_d = -dy_u
                 else:
                    print "ERROR: side is neither up, down or single"
                    exit(1)

                 if dy_u > 0. and dy_d < 0.:
                    # normal behavior
                    sample_uncertainty[systname]['u'][i] = dy_u
                    sample_uncertainty[systname]['d'][i] = dy_d
                 elif dy_u < 0. and dy_d > 0.:
                    # crossing
                    sample_uncertainty[systname]['u'][i] = dy_u                    
                    sample_uncertainty[systname]['d'][i] = dy_d
                 elif dy_u > 0. and dy_d > 0.:
                    # both upward
                    sample_uncertainty[systname]['u'][i] = max( [ dy_u, dy_d ] ) 
                    sample_uncertainty[systname]['d'][i] = 0.
                 elif dy_u < 0. and dy_d < 0.:
                    # both downward
                    sample_uncertainty[systname]['u'][i] = 0.
                    sample_uncertainty[systname]['d'][i] = min( [ dy_u, dy_d ] )
                 else:
                    sample_uncertainty[systname]['u'][i] = 0.
                    sample_uncertainty[systname]['d'][i] = 0.

                 # add errors in quadrature
                 dy_u = sample_uncertainty[systname]['u'][i]
                 dy_d = sample_uncertainty[systname]['d'][i]
                 dy_u_2 = dy_u*dy_u
                 dy_d_2 = dy_d*dy_d

                 if dy_u >= 0.: 
                    points[i]['u'] += dy_u_2
                    total_uncertainty[systname]['u'][i]   += dy_u_2
                    total_uncertainty['statsyst']['u'][i] += dy_u_2
                    total_uncertainty['systonly']['u'][i] += dy_u_2
                    points[i]['d'] += dy_d_2
                    total_uncertainty[systname]['d'][i]   += dy_d_2
                    total_uncertainty['statsyst']['d'][i] += dy_d_2
                    total_uncertainty['systonly']['d'][i] += dy_d_2
                 elif dy_u < 0.: 
                    points[i]['d'] += dy_u_2
                    total_uncertainty[systname]['d'][i]   += dy_u_2
                    total_uncertainty['statsyst']['d'][i] += dy_u_2
                    total_uncertainty['systonly']['d'][i] += dy_u_2
                    points[i]['u'] += dy_d_2
                    total_uncertainty[systname]['u'][i]   += dy_d_2
                    total_uncertainty['statsyst']['u'][i] += dy_d_2
                    total_uncertainty['systonly']['u'][i] += dy_d_2
    
       # apply square root
       for systname in total_uncertainty.keys():
             for var in ['u', 'd']: 
               nbins = len( total_uncertainty[systname][var] )
               for i in range( nbins ):    
                  dy = total_uncertainty[systname][var][i]
                  if dy < 0.:
                     raise Exception( "ERROR: negative uncertainty for %s:%s:%s" % (systname,var,i) ) 
                  total_uncertainty[systname][var][i] = sqrt( total_uncertainty[systname][var][i] )
#                  if var == 'd': total_uncertainty[systname][var][i] *= -1.0

#       for systname in total_uncertainty.keys():
#          for var in ['u', 'd']:
#             nbins = len( total_uncertainty[systname][var] )
#             for i in range( nbins ):    
#                total_uncertainty[systname][var][i] = sqrt( total_uncertainty[systname][var][i] )  

       # Print out relative shift
       DumpSystematicsToXMLFile( hpath, edges, points, total_uncertainty )

       # fill graph
       for i in range(nbins):
          x  = h.GetBinCenter( i+1 )
          y  = points[i]['n']
          bw = h.GetBinWidth( i+1 )
          eyl = sqrt( points[i]['d'] )
          eyh = sqrt( points[i]['u'] )

          graph.SetPoint( i, x, y )
          graph.SetPointError( i, bw/2, bw/2, eyl, eyh )

       graph.Write()
#       if outputClass == OutputType.graph:
#          graph.Write()
#       else:
#          DumpUpDownHistograms( hpath, edges, points )

       progress.increment_amount()
       print progress, "\r",
       #time.sleep(0.05)

    print
    outfile.Close()
    print "INFO: output file closed"
    print
   

########################################################################


def DumpUpDownHistograms( hpath, edges, points ):

    hname = hpath.split('/')[-1]


########################################################################


if __name__ == "__main__":
   
   parser = optparse.OptionParser( usage = "%prog [options] configfile.xml" )
   parser.add_option( "-c", "--config", help="Configuration files",         dest="config", default="" )
   parser.add_option( "-o", "--output", help="Output file name [%default]", dest="output", default="uncertainty.histograms.root" )
   parser.add_option( "-x", "--output-xml", help="Dump systematics to XML file [%default]", dest="xmloutput", default="uncertainty.xml" )
   parser.add_option( "-f", "--format", help="Output format grap|histograms [%default]", dest="format", default="graph" )
   (opts, args) = parser.parse_args()

   configFileName = opts.config
   if configFileName == "":
        print "ERROR: please specify a config file in xml format."
        exit(1)

   outFileName = opts.output
   print "INFO: Output file name:", outFileName
 
   histograms_configuration, samples_configuration  = ReadConfiguration( configFileName )

   xmlfile = open( opts.xmloutput, 'w' )
   xmlfile.write( "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n" )
   xmlfile.write( "<document>\n" )

   format = OutputType.graph if opts.format == "graph" else OutputType.histogram
   CreateMergedHistograms( format )

   xmlfile.write( "</document>" )   
   xmlfile.close()
