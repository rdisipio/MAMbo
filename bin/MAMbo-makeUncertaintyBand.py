#!/usr/bin/env python

import os, sys
import optparse

sys.path.append( os.environ['MAMBODIR'] + "/python" )

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
      samples_configuration[name].file        = TFile.Open( fpath )

      samples_configuration[name].systematics = {}
      for syst in node.iter("syst"):
         sname = syst.attrib['name']
         samples_configuration[name].systematics[sname] = {}
         for shift in syst.iter("shift"):
            side   = shift.attrib["side"]
            sfname = shift.attrib["file"] 
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
            print "ERORR: invalid histogram", hpath, "for sample", sample

        newname = "%s_%s" % ( sample, hname )
        hlist[sample] = hsource.Clone( newname )

        for syst,flist in samples_configuration[sample].systematics.iteritems():
           print sample, syst
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


####################################################


def CreateMergedHistograms( outputClass = OutputType.graph ):

    for hpath in histograms_configuration:
       outfile.cd()
	
       hname = hpath.split('/')[-1]

       print "INFO: merging histogram", hpath

       hlist = GatherHistograms( hname, hpath )

       graph  = None
       points = None
       nbins  = 0
       title  = ""
       for sample in samples_configuration.keys():
          h = hlist[sample]	

          if graph == None:

             newdir = CreateROOTPath( hpath )

             nbins = h.GetNbinsX()
             title = h.GetTitle()

             points = [ { 'n': 0., 'u': 0.,  'd': 0. } for i in range(nbins) ]
             graph = TGraphAsymmErrors()
             graph.SetName( hname )
             graph.SetTitle( title )

          for i in range(nbins):
             points[i]['n'] += h.GetBinContent(i+1)

             # stat. unc.
             points[i]['u'] += pow( h.GetBinError(i+1), 2 )
             points[i]['d'] += pow( h.GetBinError(i+1), 2 )

             # syst. unc.
             for systname in samples_configuration[sample].systematics.keys():
                 hpattern = "%s_%s_%s_" % ( sample, hname, systname )
                 h_u = hlist[hpattern+"up"]
                 h_d = hlist[hpattern+"down"]
     
                 dy_u = h_u.GetBinContent(i+1) - h.GetBinContent(i+1)
                 dy_d = h.GetBinContent(i+1) - h_d.GetBinContent(i+1)

                 if dy_u > 0. and dy_d > 0.:
                    points[i]['u'] += pow( dy_u, 2 )
                    points[i]['d'] += pow( dy_d, 2 )
                 elif dy_u < 0. and dy_d < 0.:
                    points[i]['u'] += pow( dy_d, 2 )
                    points[i]['d'] += pow( dy_u, 2 ) 
                 elif dy_u > 0. and dy_d < 0.:      
                    dy_max = max( [ dy_u, -dy_d ] )
                    points[i]['u'] += pow( dy_max, 2 )
                 elif dy_u < 0. and dy_d > 0.:
                    dy_max = max( [ -dy_u, dy_d	] )          
                    points[i]['d'] += pow( dy_max, 2 )
                 else:
                    print "WARNING: unhandled case: sample", sample, "syst", systname, "bin", i, "dy_u =", dy_u, "dy_d =", dy_d

          for i in range(nbins):
             x  = h.GetBinCenter( i+1 )
             y  = points[i]['n']
             bw = h.GetBinWidth( i+1 )
             eyl = sqrt( points[i]['d'] )
             eyh = sqrt( points[i]['u'] )

             graph.SetPoint( i, x, y )
             graph.SetPointError( i, bw/2, bw/2, eyl, eyh )

       graph.Write()


########################################################################

    
if __name__ == "__main__":
   
   parser = optparse.OptionParser( usage = "%prog [options] configfile.xml" )
   parser.add_option( "-c", "--config", help="Configuration files",         dest="config", default="" )
   parser.add_option( "-o", "--output", help="Output file name [%default]", dest="output", default="merged.histograms.root" )
   (opts, args) = parser.parse_args()

   configFileName = opts.config
   if configFileName == "":
        print "ERROR: please specify a config file in xml format."
        exit(1)

   outFileName = opts.output
   print "INFO: Output file name:", outFileName
 
   histograms_configuration, samples_configuration  = ReadConfiguration( configFileName )

   outfile = TFile.Open( outFileName, "RECREATE" )

   CreateMergedHistograms()

   outfile.Close()
