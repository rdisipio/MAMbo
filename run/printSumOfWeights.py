#!/usr/bin/env python

import os,sys

from ROOT import *

basedir = os.environ['MAMBONTUPLEDIR'] + "/"

file_list = sys.argv[1]

hpath = "mini_fullCutFlow_genWeights"
i = 1 #all events
sumw = 0.

f = open( file_list )
for filename in f.readlines():
   filename = filename.strip()

   if not filename.startswith("/"):
      filename = basedir + filename

   file = TFile.Open( filename )
 
   h_cutflow_weighted = file.Get( hpath )

   w = h_cutflow_weighted.GetBinContent( i )

   sumw += w

print "Sum of weights: %f" % sumw
