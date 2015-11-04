#!/bin/sh


for tag in radHi radLo ; do



for ll in el mu mc ; do
  ./clean.sh
  opt=""
  cd lists 
  split -l 9 list_${tag}_${ll}.txt list_${tag}_${ll}_a
  cd ../
done

for ll in el mu ; do

  for list in `cd  lists ; ls list_${tag}_${ll}_aa?` ; do

    base=`echo $list | sed "s/list_${tag}_${ll}_//g"`
    mclist=`echo $list | sed "s/_${ll}/_mc/g"`

    # echo " $base"
    # make the config:
    cfg=control/analysis_params_TTbarResolved_mcsignal_${ll}_${tag}_${base}.xml
    cat control/analysis_params_TTbarResolved_mcsignal_${ll}_${tag}.xml | sed "s|list_${tag}_mc.txt|${mclist}|g" > ${cfg}
    # run:
    echo "   runMAMbo ${opt} -p ${cfg} -f lists/${list} -o histograms_${tag}_${ll}_${base}.root >& log_${ll}_${tag}_${base}.txt & "
  done

done

done # IFSR
