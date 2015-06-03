#!/bin/bash

#tag=_particle_ljets
tag=_incl

listbase=split_list_PowhegPythia_P2011C_ttbar_hdamp172p5_nonallhad.mcfixed_at180_combined_pdf_dijet
#listbase=split_list_eos_new

for ll in el mu ; do

  ./clean.sh


  for list in `cd  lists ; ls ${listbase}_${ll}_a?` ; do

    base=`echo $list | sed "s/${listbase}_${ll}_//g"`
    mclist=`echo $list | sed "s/_${ll}/_mc/g"`
    # echo " $base"
    # make the config:

    cfg=control/analysis_params/TTbarResolved_resolved/mcparticles_${ll}_JK.xml
    #cfg=control/mcparticles_${ll}_JK.xml

    echo "runMAMbo -p ${cfg} -f lists/${mclist} -o histograms_PowHeg_${ll}_particle_${base}${tag}.root >& log_ptcl_${ll}_${base}${tag}.txt"


  done

done
