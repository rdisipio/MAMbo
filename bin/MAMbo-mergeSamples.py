#!/usr/bin/env python

import os, sys
import optparse

sys.path.append( os.environ['MAMBODIR'] + "/python" )

from xml.etree import ElementTree

from ROOT import *


########################################


class Simulations:
   unknown = 0
   full    = 1
   fast    = 2


class SampleWrapper:
   dsid        = -1
   name        = ""
   generator   = ""
   simulation  = Simulations.unknown
   xsec        = 0.
   kfact       = 0.
   genevt      = 0


########################################


def ReadConfiguration( configFileName ):
   with open( configFileName, 'rt') as f:
      tree = ElementTree.parse(f)

   if tree == None:
      print "ERROR: cannot parse input file", configFileName
      exit(1)

   histograms_configuration = []
   for node in tree.iter( "histogram" ):
#       name = node.attrib.get('name')
       histograms_configuration += [ node.attrib.get('hpath') ]

   samples_configuration = {}
   for node in tree.iter( "sample" ):
      name = node.attrib.get('name')
      samples_configuration[name] = SampleWrapper()
      samples_configuration[name].dsid        = node.attrib.get('dsid')
      samples_configuration[name].name        = name
      samples_configuration[name].generator   = node.attrib.get('generator')
      samples_configuration[name].simulation  = node.attrib.get('simulation')
      samples_configuration[name].xsec        = float( node.attrib.get('xsec') )
      samples_configuration[name].kfact       = float( node.attrib.get('kfact' ) )
      samples_configuration[name].genevt      = float( node.attrib.get('genevt' ) )


   input_files = {} 
   for node in tree.iter( "file" ):
      sample = node.attrib.get('sample')

      path = node.attrib.get('path')
      input_files[sample] = TFile.Open( path )

   return histograms_configuration, samples_configuration, input_files

####################################################


def GatherHistograms( hname, hpath ):
    hlist = {}

    for sample in samples_configuration:

        hsource = input_files[sample].Get( hpath )

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


def CreateMergedHistograms():

    for hpath in histograms_configuration:
        outfile.cd()
	
        hname = hpath.split('/')[-1]

        print "INFO: merging histogram", hpath

        hlist = GatherHistograms( hname, hpath )

        hsum = None
        for sample, h in hlist.iteritems():

	    #area  = h.Integral( "width" )
            genevt = samples_configuration[sample].genevt
            xsec   = samples_configuration[sample].xsec
            kfact  = samples_configuration[sample].kfact
            sf     = xsec * kfact / genevt
            
            if hsum == None:

                newdir = CreateROOTPath( hpath )

                hsum = h.Clone( hname )

                hsum.Reset( "ICES" )
                hsum.SetDirectory( newdir )
            hsum.Add( h, sf )

        hsum.Write()


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
 
   histograms_configuration, samples_configuration, input_files = ReadConfiguration( configFileName )
  
   outfile = TFile.Open( outFileName, "RECREATE" )

   CreateMergedHistograms()

   outfile.Close()
