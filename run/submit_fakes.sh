#!/bin/bash

analysis=tt_diffxs_8TeV

sourcedir=${MAMBODIR}/share/control/file_list/TTbarResolved_resolved

syst=nominal
[[ "x$1" == "x" ]] || syst=$1

for channel in el mu
do
  [[ ${channel} == "el" ]] && stream="Egamma"
  [[ ${channel} == "mu" ]] && stream="Muons"

  for period in A B C D E G H I J L
  do
    tag=${analysis}.qcd.${stream}.period${period}.${channel}.${syst}

    jobname=${tag}
    paramfile=control/analysis_params/TTbarResolved_resolved/qcd_${channel}.xml

    filelist=${sourcedir}/qcd.${stream}.period${period}.${channel}.txt

    outfile=${syst}/${tag}.histograms.root

    MAMbo-submit.sh -p ${paramfile} -f ${filelist} -o ${outfile} -j ${jobname}
  done

done
