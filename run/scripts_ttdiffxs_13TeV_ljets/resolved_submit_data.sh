#!/bin/bash

analysis=tt_diffxs_13TeV

sourcedir=$PWD

filelistdir=filelists_TTDIFFXS_62/
for ch in el mu
do
#  [[ ${ch} == "el" ]] && stream="Egamma"
#  [[ ${ch} == "mu" ]] && stream="Muons"
  stream="Main"
  for list in `ls ${filelistdir}/ | grep data`
  do
    run=`echo $list | cut -d. -f2`
    topology=Resolved
    tag=${analysis}.data.${stream}.${run}.${ch}.${topology}

    jobname=${tag}
    paramfile=$PWD/control/analysis_params/13TeV_ljets_resolved/config/realdata_${topology}_${ch}.xml

    filelist=$PWD/${filelistdir}/$list
    mkdir -p output/nominal
    outfile=nominal/${tag}.histograms.root

    MAMbo-submit.sh -p ${paramfile} -f ${filelist} -o ${outfile} -j ${jobname}
  done

done
