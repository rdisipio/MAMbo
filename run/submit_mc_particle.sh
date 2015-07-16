#!/bin/bash

analysis=tt_diffxs_8TeV
outtag=TTbarResolved_resolved
syst=particle

queue=T3_BO_LOCAL
[[ ${HOSTNAME} == *"cern.ch"* ]] && queue=1nh

dsid=110404
[ ! -z $1 ] && dsid=$1

decay=nofullhad
[ ! -z $2 ] && decay=$2

[[ ! -d ${MAMBOOUTPUTDIR}/particle ]] && mkdir -p ${MAMBOOUTPUTDIR}/particle

for ch in el mu
do
     echo "INFO: submitting DiTop dsid=$dsid channel ${ch}"

     params=${MAMBODIR}/share/control/analysis_params/${outtag}/mcparticle_${ch}_${decay}.xml 
     filelist=${MAMBODIR}/share/control/file_list/${outtag}/mc.DiTop.${dsid}.mc.txt

     for flist in $(ls ${filelist}.*)
     do
         batchid=$(echo ${flist} | grep -oE "[^.]+$")

	 tag=${analysis}.mc.DiTop.${dsid}.${ch}.${syst}.${decay}

         outfile=${syst}/${tag}.histograms.root.${batchid}
         jobname=${tag}.${batchid}
       
	 echo "Submitting ${jobname}"

         MAMbo-submit.sh -p ${params} -f ${flist} -o ${outfile} -j ${jobname} -q ${queue}
     done

     echo
done
