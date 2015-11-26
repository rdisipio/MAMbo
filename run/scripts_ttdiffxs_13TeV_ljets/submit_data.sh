#!/bin/bash

analysis=tt_diffxs_13TeV

sourcedir=$PWD


for ch in el mu
do
#  [[ ${ch} == "el" ]] && stream="Egamma"
#  [[ ${ch} == "mu" ]] && stream="Muons"
  stream="Main"
  for list in `ls filelists_TTDIFFXS_3/ | grep user.amenga`
  do
    run=`echo $list | cut -d. -f3`
    tag=${analysis}.data.${stream}.${run}.${ch}

    jobname=${tag}
    paramfile=realdata_${ch}.xml

    filelist=filelists_TTDIFFXS_3/$list
    mkdir -p output/nominal
    outfile=output/nominal/${tag}.histograms.root

    MAMbo-submit.sh -p ${paramfile} -f ${filelist} -o ${outfile} -j ${jobname}
  done

done
