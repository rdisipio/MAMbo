#!/bin/bash

# JK May 5,6th 2016

# single top:
# for id in 410011 410012 410013 410014 410025 410026 ; do

#delay=1

# Zjets:
# special missing samples:
#for id in 361407 361409 361422 361426 ; do
#for id in `cat scripts_ttdiffxs_13TeV_ljets/Zjets.run | grep 361` ; do
for id in `cat scripts_ttdiffxs_13TeV_ljets/ttV.run scripts_ttdiffxs_13TeV_ljets/Diboson.run` ; do
   echo "*** Submitting jobs for dsid ${id}"
   ls _submit*${id}_a??
   ###!!!
   ./scripts_ttdiffxs_13TeV_ljets_prague/Qsub.sh ${id}_a
   #echo "Sleeping ${delay}s...zzz..."
   #sleep $delay
done