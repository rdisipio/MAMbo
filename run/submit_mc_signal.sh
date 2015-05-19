#!/bin/bash

analysis=tt_diffxs_8TeV
outtag=TTbarResolved_resolved
syst=nominal

paramsdir=${MAMBODIR}/share/control/analysis_params/${outtag}

dsid=110404
[ ! -z $1 ] && dsid=$1

for ch in el mu
do
     echo "INFO: submitting DiTop dsid=$dsid channel ${ch}"

     [ $ch == "el" ] && ch_tag="electron"
     [ $ch == "mu" ] && ch_tag="muon"
      
     params=${MAMBODIR}/share/control/analysis_params/${outtag}/mcsignal_${dsid}_${ch}.xml 
     filelist=${MAMBODIR}/share/control/file_list/${outtag}/mc.DiTop.${dsid}.${ch}.txt
     filelist_mc=$( echo $filelist | sed "s/${ch}.root/mc.root/" )
#${MAMBODIR}/share/control/file_list/${outtag}/mc.DiTop.${dsid}.mc.txt

     for flist in $(ls ${filelist}.*)
     do
         batchid=$(echo ${flist} | grep -oE "[^.]+$")

         flist_mc=${flist}.${batchid}

    	 tag=${analysis}.mc.DiTop.${dsid}.${ch}.${syst}

         params=${paramsdir}/mcsignal_${ch}.${syst}.xml
         cp ${paramsdir}/mcsignal_template.xml ${params}

         sed -i "s|@CHANNEL@|${ch_tag}|"     ${params}
         sed -i "s|@FILELIST@|${flist_mc}|"  ${params}

         outfile=${syst}/${tag}.histograms.root.${batchid}
         jobname=${tag}.${batchid}
       
	 echo "Submitting ${jobname}"
         MAMbo-submit.sh -p ${params} -f ${flist} -o ${outfile} -j ${jobname}
     done

     echo
done
