#!/bin/bash

analysis=tt_diffxs_8TeV

sourcedir=${MAMBODIR}/share/control/file_list/TTbarResolved_resolved

syst=nominal
[[ "x$1" == "x" ]] || syst=$1

[ ! -d $MAMBOOUTPUTDIR/${syst} ] && mkdir -p $MAMBOOUTPUTDIR/${syst}

for channel in el mu
do
  [[ ${channel} == "el" ]] && stream="Egamma"
  [[ ${channel} == "mu" ]] && stream="Muons"

  for period in A B C D E G H I J L
  do
    tag=${analysis}.qcd.${stream}.period${period}.${channel}.${syst}

    jobname=${tag}
    params=control/analysis_params/TTbarResolved_resolved/qcd_${channel}.xml

    newparams=$(echo $params | sed "s/xml/${syst}.xml/" )
    cp ${params} ${newparams}

    [ ! syst == "nominal" ] && sed -i "s/NOMINAL/${syst}/g" ${newparams}

    filelist=${sourcedir}/qcd.${stream}.period${period}.${channel}.txt

    outfile=${syst}/${tag}.histograms.root

    MAMbo-submit.sh -p ${newparams} -f ${filelist} -o ${outfile} -j ${jobname}
  done

done
