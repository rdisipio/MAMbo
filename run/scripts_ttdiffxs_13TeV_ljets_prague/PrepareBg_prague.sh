#!/bin/bash

# JK May 5,6th 2016

#do this only once or when really needed, takes zillion!!
#./RunBg_prague.py  | grep runM > _submit_bg.sh

# single top:
for id in 410011 410012 410013 410014 410025 410026 ; do
  list=_submit_bg_${id}
  # all but JES!!!
  cat _submit_bg.sh | grep ${id} | grep -v JET_19NP > ${list}.sh
  # ONLY JES!!!
  #cat _submit_bg.sh | grep ${id} | grep JET_19NP > ${list}.sh
  split -l 1 ${list}.sh ${list}_a 
done