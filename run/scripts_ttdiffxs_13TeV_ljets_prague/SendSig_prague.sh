#!/bin/bash

# JK May 8th 2016

# signal fullsim:
for id in 410000 ; do
   ./scripts_ttdiffxs_13TeV_ljets_prague/Qsub.sh ${id}_a
done