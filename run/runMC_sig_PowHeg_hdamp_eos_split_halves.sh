#!/bin/sh


for ll in el mu ; do

  ./clean.sh
  opt=""

  for half in 0 1 ; do

    for list in `cd  lists ; ls split_list_eos_new_${ll}_a?` ; do

      base=`echo $list | sed "s/split_list_eos_new_${ll}_//g"`
      mclist=`echo $list | sed "s/_${ll}/_mc/g"`
      # echo " $base"
      # make the config:
      cfg=control/analysis_params_TTbarResolved_mcsignal_${ll}_eos_half${half}_${base}.xml
      cat control/analysis_params_TTbarResolved_mcsignal_${ll}_eos_half${half}.xml | sed "s|list_eos_new_mc.txt|${mclist}|g" > ${cfg}
      # run:
      echo "   runMAMbo ${opt} -p ${cfg} -f lists/${list} -o histograms_PowHeg_${ll}_half${half}_NewWhad_${base}.root >& log_${ll}_half${half}_${base}.txt & "

    done
  done
done
