#!/bin/bash

# JK May 5,6,11th 2016

#do this only once or when really needed, takes zillion!!
#./prague/RunBg_prague.py  | grep runM > _submit_bg.sh

# single top:
# for id in 410011 410012 410013 410014 410025 410026 ; do

# Zjets:
#for id in 361407 361409 361422 361426 ; do
###!!!for id in `cat scripts_ttdiffxs_13TeV_ljets/Zjets.run | grep 361` ; do
for id in `cat scripts_ttdiffxs_13TeV_ljets/AllBkgTTDIFFXS_62.txt | cut -d \. -f 2 ` ; do
  echo "Processing $id ..."
  list=_submit_bg_${id}

  # Systs:
  # all but JES!!!
  # cat _submit_bg.sh | grep ${id} | grep -v JET > ${list}.sh
  # other:
  # cat _submit_bg.sh | grep ${id} | egrep "MUON|EG|MET" > ${list}.sh
  # ONLY JES!!!
  # cat _submit_bg.sh | grep ${id} | egrep "JET" > ${list}.sh

  # Nominal:
  # cat _submit_bg.sh | grep ${id} | egrep "nominal" > ${list}.sh

  # other and nominal:
  cat _submit_bg.sh | grep ${id} | egrep "JET|MUON|EG|MET|nominal" > ${list}.sh

  split -l 1 ${list}.sh ${list}_a 
done