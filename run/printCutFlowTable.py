#!/usr/bin/env python

import os, sys
from ROOT import *

analysis = "TTbarResolved_resolved"
syst = "nominal"

basedir = os.environ['MAMBODIR'] + "/run/output/" + analysis + "/" + syst + "/"

hname_wgt = "LPLUSJETS_cutflow_reco_weighted"
hname_unw  = "LPLUSJETS_cutflow_reco_unweight" 

channels = [ 'el', 'mu' ]

infilename = sys.argv[1]
infile = TFile.Open( infilename )

cutflow_unweight = infile.Get( hname_unw )
cutflow_weighted = infile.Get( hname_wgt )

ncuts = 11

print "Cut  |   unweight  |   weighted"
print "--------------------------"
for i in range( 8, ncuts ):
   print "%2i)  | %10.0f  | %10.0f" % ( i+1, cutflow_unweight.GetBinContent( i+1 ), cutflow_weighted.GetBinContent( i+1 ) )
