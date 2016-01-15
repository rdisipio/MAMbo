#!/bin/bash

analysis=tt_diffxs_13TeV

sourcedir=$PWD


for ch in el mu
do
#  [[ ${ch} == "el" ]] && stream="Egamma"
#  [[ ${ch} == "mu" ]] && stream="Muons"
  stream="Main"
  for list in `ls filelists_TTDIFFXS_35/ | grep data`
  do
    run=`echo $list | cut -d. -f2`
    topology=Resolved
    tag=${analysis}.qcd.${stream}.${run}.${ch}.${topology}

    jobname=${tag}
    paramfile=$PWD/control/analysis_params/13TeV_ljets_resolved/config/qcd_${topology}_${ch}.xml

    filelist=$PWD/filelists_TTDIFFXS_35/$list
    mkdir -p output/nominal
    outfile=nominal/${tag}.histograms.root

    MAMbo-submit.sh -p ${paramfile} -f ${filelist} -o ${outfile} -j ${jobname}
  done

done
