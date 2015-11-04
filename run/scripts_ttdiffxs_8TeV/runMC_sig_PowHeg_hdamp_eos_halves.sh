#!/bin/sh


for ll in el mu ; do

  ./clean.sh
  #opt="-n 100000"
  opt=""

  for half in 0 1 ; do
    echo "   runMAMbo ${opt} -p control/analysis_params_TTbarResolved_mcsignal_${ll}_eos_half${half}.xml -f lists/list_eos_new_${ll}.txt -o histograms_PowHeg_${ll}_fixed_half${half}.root >& log_half${half}_${ll}.txt "
  done


done
