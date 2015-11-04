#!/bin/bash

tag=_incl
#tag=_ljets

for listbase in `cat lists/masses.txt` ; do
  #echo "*** Processing ${listbase} ***"
  cd lists/
  for ll in el mu mc ; do
    split -l 2 list_mtop_${listbase}_${ll}.txt split_list_mtop_${listbase}_${ll}_a
  done
  cd ../

  for ll in el mu ; do


    ./clean.sh
    opt=""

    for list in `cd  lists ; ls split_list_mtop_${listbase}_${ll}_a??` ; do
      #echo "  *** Processing list $list"
      base=`echo $list | sed "s/${listbase}_${ll}_//g"`
      mclist=`echo $list | sed "s/_${ll}/_mc/g"`
      #echo "    --- base: $base mclist: ${mclist}"
      # make the config:

      cfg=control/analysis_params_TTbarResolved_mcsignal_${ll}_eos_${listbase}_${base}.xml
      #echo "              cfg: ${cfg}"
      cat control/analysis_params_TTbarResolved_mcsignal_${ll}_eos.xml | sed "s|list_eos_new_mc.txt|${mclist}|g" > ${cfg}
      # prepare run cmd:
      echo "   runMAMbo ${opt} -p ${cfg} -f lists/${list} -o histograms_PowHeg_${ll}${tag}_${listbase}_${base}.root >& log_${ll}_mcsig${tag}_${listbase}_${base}.txt " #& "
    done
  done

done
