#!/usr/bin/env python

import os,sys

from ROOT import *

lumi = 20300
basedir = os.environ['MAMBONTUPLEDIR'] + "/"

file_list = sys.argv[1]

hpath_unw = "mini_fullCutFlow_genWeights"
hpath_wgt = "mini_fullCutFlow_genXpileupXzvertexWeights"

i = 1 #all events

if len(sys.argv) > 2: i = int( sys.argv[2] )

sumw_unw = 0.
sumw_wgt = 0.
f = open( file_list )
for filename in f.readlines():
   filename = filename.strip()

   if not filename.startswith("/"):
      filename = basedir + filename

   file = TFile.Open( filename )
 
   h_cutflow_weighted = file.Get( hpath_wgt )
   h_cutflow_unweight = file.Get( hpath_unw )

   if not h_cutflow_weighted:
      print "ERROR: not wgt cutflow found in file", filename
   if not h_cutflow_unweight:
      print "ERROR: not unw cutflow found in file", filename

   sumw_unw += h_cutflow_unweight.GetBinContent( i )
   sumw_wgt += h_cutflow_weighted.GetBinContent( i )

#sf = lumi * 114.49 * 1.1994 / 49948212.0 #unw
#sf = lumi * 114.49 * 1.1994 / 49739715.0 #wgt
sf = 1.0
print "Sum of weights: bin %2i : %10.0f %10.0f %10.0f" % (i, sumw_unw, sumw_wgt, sumw_wgt*sf )
