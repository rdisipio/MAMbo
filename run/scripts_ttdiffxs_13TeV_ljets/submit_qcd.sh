#!/bin/bash

analysis=tt_diffxs_13TeV

sourcedir=${MAMBODIR}/run/scripts_ttdiffxs_13TeV_ljets
prod="prod55_1802"

for ch in el mu
do
#  [[ ${ch} == "el" ]] && stream="Egamma"
#  [[ ${ch} == "mu" ]] && stream="Muons"
  stream="QCD"
  for method in MM
  do
    for list in `ls ${MAMBODIR}/run/scripts_ttdiffxs_13TeV_ljets/filelists_TTDIFFXS_55/*physics_Main*`
    do
      run=`echo $list | cut -d. -f2`
      topology=Boosted
      tag=${analysis}.${stream}.${run}.${ch}.${topology}.${method}

      echo $run

      jobname=${tag}
      paramfile=${sourcedir}/qcd_${topology}_${ch}_${method}.xml
    
      #filelist=${sourcedir}/filelists_TTDIFFXS_3/$list
      mkdir -p ${MAMBODIR}/run/output/QCD_${prod}
      outfile=QCD_${prod}/${tag}.histograms.root
      # echo $outfile
      MAMbo-submit.sh -p ${paramfile} -f ${list} -o ${outfile} -j ${jobname}
    done
  done

done
