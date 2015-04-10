#!/usr/bin/env python

import os, sys, time
import optparse
sys.path.append( os.environ['MAMBODIR'] + "/python" )

from ProgressBar import *

from xml.etree import ElementTree

from ROOT import *

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

        for syst,flist in samples_configuration[sample].systematics.iteritems():
           for side, fname in flist.iteritems():
              hsource = fname.Get( hpath )
              newname = "%s_%s_%s_%s" % ( sample, hname, syst, side )
              if hsource == None: print "ERROR: invalid histogram", sample, hname, syst, side
              hlist[newname] = hsource.Clone( newname )

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


#######################################


def DumpSystematicsToXMLFile( hpath, h_n, uncertainty ):
    nbins = h_n.GetNbinsX()
    edges = [ h_n.GetBinLowEdge(i+1) for i in range(nbins+1) ]

    xmlfile.write( "<histogram hpath=\"%s\">\n" % hpath ) 

    xmlfile.write( "\t<nominal>" )
    for i in range(nbins):
       y_n = h_n.GetBinContent( i+1 )
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
          y_n = h_n.GetBinContent( i+1 )
          dy_rel = 100. * y_u / y_n if not y_n == 0. else 0.
          sgn = "+" if dy_rel > 0. else ""
          xmlfile.write( "%s%4.3f" % ( sgn, dy_rel ) )
          if i < nbins-1: xmlfile.write( "," )
       xmlfile.write( "</u>\n")

       xmlfile.write( "\t\t<d>")
       for i in range(nbins):
          y_d = syst['d'][i]
          y_n = h_n.GetBinContent( i+1 )
          dy_rel = 100. * y_d / y_n if not y_n == 0. else 0.
          sgn = "+" if dy_rel > 0. else ""
          xmlfile.write( "%s%4.3f" % ( sgn, dy_rel ) )
          if i < nbins-1: xmlfile.write( "," )
       xmlfile.write( "</d>\n")

       xmlfile.write( "\t</uncertainty>\n" )

    xmlfile.write( "</histogram>\n" )


#######################################


def sqrt_signed(x):
    return sqrt(x) if x >= 0. else -1. * sqrt(-x)


#######################################


def CreateHistograms( outfilenames, sf68 ):

    outfile_u = TFile.Open( outfilenames['u'], "RECREATE" )
    outfile_d = TFile.Open( outfilenames['d'], "RECREATE" )

    for hpath in histograms_configuration:
       hname = hpath.split('/')[-1]
       
       hlist = GatherHistograms( hname, hpath )

       nbins = -1
       title = ""

       uncertainty = {}

       for sample in samples_configuration.keys():
          h_n   = hlist[sample]
          nbins = h_n.GetNbinsX()
          title = h_n.GetTitle()

          h_out_u = h_n.Clone()
          h_out_d = h_n.Clone()

          h_out_u.Reset("ICES")
          h_out_d.Reset("ICES")

          if not uncertainty.has_key( 'total' ):
             uncertainty['total']  = { 'u' : [ 0 ] * nbins, 'd' : [ 0 ] * nbins }

 
          for systname in samples_configuration[sample].systematics.keys():
             uncertainty[systname] = { 'u' : [ 0. ] * nbins, 'd' : [ 0. ] * nbins }
             
             hpattern = "%s_%s_%s_" % ( sample, hname, systname )

             for i in range(nbins):
                 y_n = h_n.GetBinContent(i+1)

                 dy_u = 0.
                 dy_d = 0.

                 if samples_configuration[sample].systematics[systname].has_key( "up" ):
                    h_u = hlist[hpattern+"up"]
                    h_d = hlist[hpattern+"down"]

                    dy_u = h_u.GetBinContent(i+1) - y_n
                    dy_d = h_d.GetBinContent(i+1) - y_n

                 elif samples_configuration[sample].systematics[systname].has_key( "single" ):
                    h_sys = hlist[hpattern+"single"]

                    dy_u = h_sys.GetBinContent(i+1) - y_n
                    dy_d = -dy_u
                 else:
                    print "ERROR: side is neither up, down or single"
                    exit(1)

                 if dy_u > 0. and dy_d < 0.:
                    # normal behavior
                    uncertainty[systname]['u'][i] = dy_u
                    uncertainty[systname]['d'][i] = dy_d
                 elif dy_u < 0. and dy_d > 0.:
                    # crossing
                    uncertainty[systname]['u'][i] = dy_u                    
                    uncertainty[systname]['d'][i] = dy_d
                 elif dy_u > 0. and dy_d > 0.:
                    # both upward
                    uncertainty[systname]['u'][i] = max( [ dy_u, dy_d ] ) 
                    uncertainty[systname]['d'][i] = 0.
                 elif dy_u < 0. and dy_d < 0.:
                    # both downward
                    uncertainty[systname]['u'][i] = 0.
                    uncertainty[systname]['d'][i] = min( [ dy_u, dy_d ] )
                 else:
                    uncertainty[systname]['u'][i] = 0.
                    uncertainty[systname]['d'][i] = 0.

                 # total band: add errors in quadrature
                 dy_u = uncertainty[systname]['u'][i]
                 dy_d = uncertainty[systname]['d'][i]
                 dy_u_2 = dy_u*dy_u
                 dy_d_2 = dy_d*dy_d

                 if dy_u >= 0.: 
                    uncertainty['total']['u'][i] += dy_u_2
                    uncertainty['total']['d'][i] += dy_d_2
                 elif dy_u < 0.: 
                    uncertainty['total']['d'][i] += dy_u_2
                    uncertainty['total']['u'][i] += dy_d_2

          # apply square root
          for i in range( nbins ):
             dy_u = sf68 * sqrt( uncertainty['total']['u'][i] )
             dy_d = sf68 * sqrt( uncertainty['total']['d'][i] )

             uncertainty['total']['u'][i] = dy_u
             uncertainty['total']['d'][i] = dy_d

             y_n = h_n.GetBinContent( i+1 )

             h_out_u.SetBinContent( i+1, y_n + dy_u )
             h_out_d.SetBinContent( i+1, y_n - dy_d )


          # Print out relative shift
          DumpSystematicsToXMLFile( hpath, h_n, uncertainty )

          # write out

          outfile_u.cd()
          CreateROOTPath( hpath )
          h_out_u.Write( hname )

          outfile_d.cd()
          CreateROOTPath( hpath )
          h_out_d.Write( hname )
    

########################################################################


if __name__ == "__main__":
   
   parser = optparse.OptionParser( usage = "%prog [options] configfile.xml" )
   parser.add_option( "-c", "--config", help="Configuration files",         dest="config", default="" )
   parser.add_option( "-o", "--output", help="Output file name [%default]", dest="output", default="ct10_up.histograms.root,ct10_down.histograms.root" )
   parser.add_option( "-x", "--output-xml",     help="Dump systematics to XML file [%default]", dest="xmloutput", default="uncertainty.ct10.xml" )
   parser.add_option( "-e", "--errorsf", help="Scale factor to 68% CL [%default]", dest="errorsf", default=1.0/1.645 )
   (opts, args) = parser.parse_args()

   configFileName = opts.config
   if configFileName == "":
        print "ERROR: please specify a config file in xml format."
        exit(1)

   outfilenames = opts.output.split(",")

   for outFileName in outfilenames:
      print "INFO: Output file name:", outFileName
 
   histograms_configuration, samples_configuration  = ReadConfiguration( configFileName )

   sf68 = float( opts.errorsf )
   xmlfile = open( opts.xmloutput, 'w' )
   xmlfile.write( "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n" )
   xmlfile.write( "<document>\n" )

   CreateHistograms( { 'u' : outfilenames[0], 'd' : outfilenames[1] }, sf68 )

   xmlfile.write( "</document>" )   
   xmlfile.close()

