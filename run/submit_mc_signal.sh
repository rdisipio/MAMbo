#!/bin/bash

analysis=tt_diffxs_8TeV
outtag=TTbarResolved_resolved
syst=nominal

paramsdir=${MAMBODIR}/share/control/analysis_params/${outtag}

dsid=110404
[ ! -z $1 ] && dsid=$1

decay=ljets
[ ! -z $2 ] && decay=$2

for ch in el mu
do
     echo "INFO: submitting DiTop dsid=$dsid channel ${ch} decay ${decay}"

     [ $ch == "el" ] && ch_tag="electron"
     [ $ch == "mu" ] && ch_tag="muon"
      
     filelist=${MAMBODIR}/share/control/file_list/${outtag}/mc.DiTop.${dsid}.${ch}.txt
     filelist_mc=$( echo $filelist | sed "s/${ch}.root/mc.root/" )

     for flist in $(ls ${filelist}.*)
     do
         batchid=$(echo ${flist} | grep -oE "[^.]+$")

         flist_mc=$( echo ${flist} | sed "s/.${ch}.txt/.mc.txt/" )

    	 tag=${analysis}.mc.DiTop.${dsid}.${ch}.${syst}.${decay}

         params=${paramsdir}/mcsignal_${ch}.${syst}.${batchid}.xml
         cp ${paramsdir}/mcsignal_template_${decay}.xml ${params}

         sed -i "s|@CHANNEL@|${ch_tag}|"     ${params}
         sed -i "s|@MCFILELIST@|${flist_mc}|"  ${params}
         outfile=${syst}/${tag}.histograms.root.${batchid}
         jobname=${tag}.${batchid}

         echo ${params}  
         echo ${flist_mc}
       
	 echo "Submitting ${jobname}"
         MAMbo-submit.sh -p ${params} -f ${flist} -o ${outfile} -j ${jobname}
     done

     echo
done
