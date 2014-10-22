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

class OutputType:
   unknown     = 0
   histogram   = 1
   graph       = 2
   both        = 3


########################################


def ReadConfiguration( configFileName ):
   with open( configFileName, 'rt') as f:
      tree = ElementTree.parse(f)

   if tree == None:
      print "ERROR: cannot parse input file", configFileName
      exit(1)

   histograms_configuration = []
   for node in tree.iter( "histogram" ):
       histograms_configuration += [ node.attrib.get('hpath') ]

   samples_configuration = {}
   for node in tree.iter( "sample" ):
      name = node.attrib.get('name')
      samples_configuration[name] = SampleWrapper()
      samples_configuration[name].name        = name
      fpath = node.attrib.get('file')
      samples_configuration[name].file        = TFile.Open( fpath )

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
       for sample, h in hlist.iteritems():

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
             points[i]['u'] += pow( h.GetBinError(i+1), 2 )
             points[i]['d'] += pow( h.GetBinError(i+1), 2 )

                
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
