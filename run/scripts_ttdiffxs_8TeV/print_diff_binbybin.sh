#!/bin/bash

syst=$1
hpath="reco/4j2b/topH/pt"

f1=${MAMBOOUTPUTDIR}/${syst}_up/tt_diffxs_8TeV.mc.DiTop.110404.co.${syst}_up.histograms.root 
f2=${MAMBOOUTPUTDIR}/${syst}_down/tt_diffxs_8TeV.mc.DiTop.110404.co.${syst}_down.histograms.root

root -b -l $f1 $f2 << EOF
.L print_diff_binbybin.C
print_diff_binbybin( "$hpath" );
.q
EOF
