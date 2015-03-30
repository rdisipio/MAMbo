#!/bin/bash

analysis=tt_diffxs_8TeV
outtag=TTbarResolved_resolved
syst=nominal

dsid=110404
[ ! -z $1 ] && dsid=$1

for ch in el mu
do
     echo "INFO: submitting DiTop dsid=$dsid channel ${ch}"

     params=${MAMBODIR}/share/control/analysis_params/${outtag}/mcsignal_${dsid}_${ch}.xml 
     filelist=${MAMBODIR}/share/control/file_list/${outtag}/mc.DiTop.${dsid}.${ch}.txt

     for flist in $(ls ${filelist}.*)
     do
         batchid=$(echo ${flist} | grep -oE "[^.]+$")

	 tag=${analysis}.mc.DiTop.${dsid}.${ch}.${syst}

         outfile=${syst}/${tag}.histograms.root.${batchid}
         jobname=${tag}.${batchid}
       
	 echo "Submitting ${jobname}"
         MAMbo-submit.sh -p ${params} -f ${flist} -o ${outfile} -j ${jobname}
     done

     echo
done
