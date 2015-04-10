#!/usr/bin/env python

#for d in $(ls $MAMBONTUPLEDIR) ; do ./extract_genevents.py $MAMBONTUPLEDIR/$d ; done

import sys, os
from ROOT import *

hname = "mini_fullCutFlow_noWeights"

sourcedir = sys.argv[1]

ngen = 0

dsid = sourcedir.split('/')[-1].split('.')[2]
ch   = sourcedir.split('/')[-1].split('.')[4].split("_")[-1]

files = [ sourcedir + "/" + file for file in os.listdir(sourcedir) if file.find(".root") >= 0 ]
#print files

for filename in files:
   f = TFile.Open( filename )
   h = f.Get( hname )

   n = h.GetBinContent(1)

   ngen += n

   f.Close()

print "DSID:", dsid, "ch:", ch, " genevents:", ngen
