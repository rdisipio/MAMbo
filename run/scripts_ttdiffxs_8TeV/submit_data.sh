#!/bin/bash

analysis=tt_diffxs_8TeV

sourcedir=${MAMBODIR}/share/control/file_list/TTbarResolved_resolved

for ch in el mu
do
  [[ ${ch} == "el" ]] && stream="Egamma"
  [[ ${ch} == "mu" ]] && stream="Muons"

  for period in A B C D E G H I J L
  do
    tag=${analysis}.data.${stream}.period${period}.${ch}

    jobname=${tag}
    paramfile=control/analysis_params/TTbarResolved_resolved/realdata_${ch}.xml

    filelist=${sourcedir}/data.${stream}.period${period}.${ch}.txt

    outfile=nominal/${tag}.histograms.root

    MAMbo-submit.sh -p ${paramfile} -f ${filelist} -o ${outfile} -j ${jobname}
  done

done
