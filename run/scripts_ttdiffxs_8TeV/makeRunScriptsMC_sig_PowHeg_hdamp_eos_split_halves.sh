#!/bin/sh

#tag=_incl
#tag=_boostedWonly
#tag=_boostedW
tag=_ljets
#tag=_7TeVpst
#tag=_noMonoJetW

listbase=split_list_PowhegPythia_P2011C_ttbar_hdamp172p5_nonallhad.mcfixed_at180_combined_pdf_dijet
#listbase=split_list_eos_new

for ll in el mu ; do

  ./clean.sh
  opt=""

  for half in 0 1 ; do

    for list in `cd  lists ; ls ${listbase}_${ll}_a?` ; do

      base=`echo $list | sed "s/${listbase}_${ll}_//g"`
      mclist=`echo $list | sed "s/_${ll}/_mc/g"`
      # echo " $base"
      # make the config:
      cfg=control/analysis_params_TTbarResolved_mcsignal_${ll}_eos_half${half}_${base}.xml
      cat control/analysis_params_TTbarResolved_mcsignal_${ll}_eos_half${half}.xml | sed "s|list_eos_new_mc.txt|${mclist}|g" > ${cfg}
      # prepare run cmd:
      echo "   runMAMbo ${opt} -p ${cfg} -f lists/${list} -o histograms_PowHeg_${ll}_half${half}${tag}_${base}.root >& log_${ll}_mcsig_half${half}${tag}_${base}.txt " #& "

    done
  done
done
