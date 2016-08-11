#!/usr/bin/env python

from math import sqrt
import os, time
import optparse

from xml.etree import ElementTree

from ROOT import *

hpath="passed_boosted_ejets_1fj0b/cutflow_mc_pu_zvtx"

####################################################
def ReadFromFile(histoname1):
  
  
  thisname = histoname1[:-1]
  
  print('file !%s!'%thisname)
  file=TFile.Open(thisname,"READ")
  histo = file.Get(hpath).Clone()
  
  return histo.GetBinContent(1)

####################################################

if __name__ == "__main__":
  
  parser = optparse.OptionParser()
  parser.add_option( "-i", "--input", help="Files with all considered entuples",         dest="config", default="" )
  parser.add_option( "-o", "--output", help="Output file", dest="outfile", default="" )
  (opts, args) = parser.parse_args()
  
  configFileName = opts.config
  SplittedName = opts.outfile.split(".")
  
  DSID=int(SplittedName[0])

  TotalNumberOfEvent=0.

  with open(configFileName, 'rt') as f:
   for line in f:
    histoname=line 
    if "root" in histoname:
      TotalNumberOfEvent+= ReadFromFile(histoname)
      ReadFromFile(histoname)
     
  with open(opts.outfile, 'w') as OutFile:
    OutFile.write(str(DSID)+" "+str(TotalNumberOfEvent))
  