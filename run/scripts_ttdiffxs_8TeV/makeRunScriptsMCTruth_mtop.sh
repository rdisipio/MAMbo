#!/bin/bash

#tag=_particle_ljets
tag=_incl


for listbase in `cat lists/masses.txt` ; do


for ll in el mu ; do

  ./clean.sh







    for list in `cd  lists ; ls split_list_mtop_${listbase}_${ll}_a??` ; do

      base=`echo $list | sed "s/${listbase}_${ll}_//g"`
      mclist=`echo $list | sed "s/_${ll}/_mc/g"`
      # echo " $base"
      # make the config:

      cfg=control/analysis_params/TTbarResolved_resolved/mcparticles_${ll}_JK.xml
      #cfg=control/mcparticles_${ll}_JK.xml

      echo "runMAMbo -p ${cfg} -f lists/${mclist} -o histograms_PowHeg_${ll}_particle_${listbase}_${base}${tag}.root >& log_ptcl_${ll}_${listbase}_${base}${tag}.txt"


  done

done

done
