#!/bin/bash

dsid=110404
[ ! -z $1 ] && dsid=$1

for ch in el mu #co
do
  MAMbo-makePlots.py control/analysis_params/TTbarResolved_resolved/plots_${dsid}_${ch}.xml &
done
wait
