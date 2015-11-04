#!/bin/bash

analysis=tt_diffxs_8TeV
outtag=TTbarResolved_resolved
syst=particle

queue=T3_BO_LOCAL
[[ ${HOSTNAME} == *"cern.ch"* ]] && queue=1nh

alpgen_list=${PWD}/AlpgenPythia_ljets.dat
[ ! -z $1 ] && alpgen_list=$1


for ch in el mu
do

for dts in $(cat ${alpgen_list} | grep ":${ch}" | grep -v 'jjjj' | sort )
do

  dsid=$(echo ${dts} | cut -d':' -f1)
  hr=$(echo ${dts} | cut -d':' -f2)
#  ch=$(echo ${dts} | cut -d':' -f3)
   
  syst=$(echo ${hr} | cut -d'_' -f3)
  [[ $syst == *"ttbar"* ]] && syst=nominal

  params=${MAMBODIR}/share/control/analysis_params/${outtag}/mcparticle_${ch}.xml
  filelist=${MAMBODIR}/share/control/file_list/${outtag}/mc.DiTop.${dsid}.mc.txt

  tag=${analysis}.mc.DiTop.${dsid}.${ch}.${syst}.particle
  outfile=particle/${tag}.histograms.root
  jobname=${tag}

  echo "Submitting ${jobname} output ${outfile}"

  MAMbo-submit.sh -p ${params} -f ${filelist} -o ${outfile} -j ${jobname} -q ${queue}
done

done
