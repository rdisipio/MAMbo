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
  

class OutputType:
   unknown     = 0
   histogram   = 1
   graph       = 2
   both        = 3


hpath="LPLUSJETS_cutflow_reco_weighted"
hpath_data="LPLUSJETS_cutflow_reco_unweight"
########################################
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#the configuration is the same used for MAMbo-makePlots.py

def ReadConfiguration( configFileName ):
   with open( configFileName, 'rt') as f:
      tree = ElementTree.parse(f)

   if tree == None:
      print "ERROR: cannot parse input file", configFileName
      exit(1)

   samples_configuration = {}
   for node in tree.iter( "file" ):
      name = node.attrib.get('sample')
      
      if name == "uncertainty":
        continue 
       
      samples_configuration[name] = SampleWrapper()
      samples_configuration[name].name        = name
  
      fpath = node.attrib.get('path')
      if not fpath.startswith('/'): fpath = os.environ['MAMBOOUTPUTDIR'] + "/" + fpath
      samples_configuration[name].file        = TFile.Open( fpath )

    
   return samples_configuration


####################################################


def GatherHistograms(samples_configuration):
    hlist = {}

    for sample in samples_configuration:
        f = samples_configuration[sample].file
        if f == None:
            print "ERROR: invalid input file for sample", sample
        
        if samples_configuration[sample].name == "data":
            hsource = f.Get( hpath_data )
        else:
            hsource = f.Get( hpath )

        if hsource == None:
            print "ERORR: invalid histogram", hpath, "for sample", sample, "in file", f.GetTitle()

        newname = "%s_%s" % ( sample, "cutflow" )
        hlist[sample] = hsource.Clone( newname )

    return hlist
   

########################################################################


if __name__ == "__main__":
   
   parser = optparse.OptionParser( usage = "%prog [options] configfile.xml" )
   parser.add_option( "-c", "--config", help="Configuration files",         dest="config", default="" )
   (opts, args) = parser.parse_args()
  
   configFileName = opts.config
   if configFileName == "":
        print "ERROR: please specify a config file in xml format."
        exit(1)

  
 
   samples_configuration  = ReadConfiguration( configFileName )

   hlist = GatherHistograms(samples_configuration)
 
   sample_Name=["DiTop", "Wjets", "SingleTop", "Diboson", "Zjets", "Fakes", "data"]
   for sample in sample_Name: 
     nbins = hlist[sample].GetNbinsX()
     uncertainty = 100 * hlist[sample].GetBinError(nbins) / hlist[sample].GetBinContent(nbins)
     print sample.rjust(9), "   ", repr(hlist[sample].GetBinContent(nbins)).rjust(7).ljust( 7)[:7], " +/- ",repr(hlist[sample].GetBinError(nbins)).rjust(7).ljust( 7)[:7], " ( +/- ", repr(uncertainty).rjust(7).ljust( 7)[:7], " )"
   
 


