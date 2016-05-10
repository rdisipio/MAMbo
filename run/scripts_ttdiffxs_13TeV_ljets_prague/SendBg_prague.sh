#!/bin/bash

# JK May 5,6th 2016

# single top:
# for id in 410011 410012 410013 410014 410025 410026 ; do

# Zjets:
for id in `cat scripts_ttdiffxs_13TeV_ljets/Zjets.run | grep 361` ; do
   ./scripts_ttdiffxs_13TeV_ljets_prague/Qsub.sh ${id}_a
done