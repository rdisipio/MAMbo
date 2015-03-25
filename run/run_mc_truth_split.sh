#!/bin/bash

for ll in el mu ; do

  ./clean.sh


  for list in `cd  lists ; ls split_list_eos_new_${ll}_a?` ; do

    base=`echo $list | sed "s/split_list_eos_new_${ll}_//g"`
    mclist=`echo $list | sed "s/_${ll}/_mc/g"`
    # echo " $base"
    # make the config:

    cfg=control/analysis_params/TTbarResolved_resolved/mcparticles_${ll}.xml
    echo "runMAMbo -p ${cfg} -f lists/${mclist} -o histograms_PowHeg_${ll}_particle_${base}.root >& log_ptcl_${ll}_${base}.txt &"


  done

done
