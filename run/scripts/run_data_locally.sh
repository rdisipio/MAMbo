#!/bin/sh


for ll in el mu ; do


  ./clean.sh

#opt="-n 10000"
opt=""


echo "=== Running data ${ll} ... "

#  echo "runMAMbo  ${opt} -p control/analysis_params/TTbarResolved_resolved/realdata_${ll}.xml -f  lists/list_data_${ll}.txt -o histograms_data_${ll}.root >& log_data_${ll}.txt &"
       runMAMbo  ${opt} -p control/analysis_params/TTbarResolved_resolved/realdata_${ll}.xml -f  lists/list_data_${ll}.txt -o histograms_data_${ll}.root >& log_data_${ll}.txt &

# 2> /dev/null



done
