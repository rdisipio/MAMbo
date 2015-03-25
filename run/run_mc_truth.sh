#!/bin/bash

#for ll in el  ; do
#for ll in mu ; do
for ll in el mu ; do

./clean.sh


#  echo "  runMAMbo -p control/analysis_params/TTbarResolved_resolved/mcparticles_${ll}_JK.xml -f /afs/cern.ch/work/j/jpacalt/TopResolved8TeV_trees/list__PowhegPythia_P2011C_ttbar_hdamp172p5_nonallhad2014_11_12_mc.txt -o histograms_PowHeg_${ll}_particle.root


#  runMAMbo -p control/analysis_params/TTbarResolved_resolved/mcparticles_${ll}_JK.xml -f /afs/cern.ch/work/j/jpacalt/TopResolved8TeV_trees/list__PowhegPythia_P2011C_ttbar_hdamp172p5_nonallhad2014_11_12_mc.txt -o histograms_PowHeg_${ll}_particle.root

echo runMAMbo -p control/analysis_params/TTbarResolved_resolved/mcparticles_${ll}_JK.xml -f lists/list_eos_new_mc.txt -o histograms_PowHeg_${ll}_particle.root 

done
