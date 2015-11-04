#!/bin/sh


#for ll in el ; do
#for ll in mu ; do
for ll in el mu ; do

  ./clean.sh

#opt="-n 100000"
opt=""


#echo runMAMbo ${opt} -p control/analysis_params_TTbarResolved_mcsignal_${ll}_eos.xml -f lists/list_eos_new_${ll}.txt -o histograms_PowHeg_${ll}.root

#echo     runMAMbo ${opt} -p control/analysis_params_TTbarResolved_mcsignal_${ll}_eos.xml -f lists/list_eos_new_${ll}.txt -o histograms_PowHeg_${ll}_small.root
# echo     runMAMbo ${opt} -p control/analysis_params_TTbarResolved_mcsignal_${ll}_eos.xml -f lists/list_eos_new_${ll}.txt -o histograms_PowHeg_${ll}_noNuPtclFit.root
echo "   runMAMbo ${opt} -p control/analysis_params_TTbarResolved_mcsignal_${ll}_eos.xml -f lists/list_eos_new_${ll}.txt -o histograms_PowHeg_${ll}_fixed.root >& log_${ll}.txt "



done
