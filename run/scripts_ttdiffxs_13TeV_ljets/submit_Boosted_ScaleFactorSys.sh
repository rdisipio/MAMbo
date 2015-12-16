#!/bin/bash

analysis=tt_diffxs_13TeV

dsid=410000
[ ! -z $1 ] && dsid=$1

decay=ljets
[ ! -z $2 ] && decay=$2

nomalizationfile=${MAMBODIR}/share/data/NEvents13TeV/410000.PowhegPythiaEvtGen.e3698_s2608_s2183_r6765_r6282_p2442.evt.n
sysname_file=${MAMBODIR}/run/scripts_ttdiffxs_13TeV_ljets/ScaleFactorSys_boosted.txt

for ch in el mu
do
     echo "INFO: submitting DiTop dsid=$dsid channel ${ch} decay ${decay}"

     [ $ch == "el" ] && ch_tag="electron"
     [ $ch == "mu" ] && ch_tag="muon"

     [ $ch == "el" ] && ch_sys="_MU_"
     [ $ch == "mu" ] && ch_sys="_EL_"
      
     filelist=${MAMBODIR}/run/scripts_ttdiffxs_13TeV_ljets/filelists_TTDIFFXS_3/generator.txt
     filelist_mc=${MAMBODIR}/run/scripts_ttdiffxs_13TeV_ljets/filelists_TTDIFFXS_3/generator.txt

     while read syst 
     do
       for flist in $(ls ${filelist}.??)
       do
          if [[ "x$syst" == "x#"* ]]; then
             continue
          fi
          if [[ ${syst} == *${ch_sys}* ]]; then
             continue
          fi
     
          batchid=$(echo ${flist} | grep -oE "[^.]+$")

          flist_mc=$( echo ${flist} | sed "s/.${ch}.txt/.mc.txt/" )

    	  tag=${analysis}.mc.DiTop.${dsid}.${ch}.${syst}.${decay}


 	  params=${MAMBODIR}/run/Boosted13TeV_${ch}.${syst}.${decay}.${batchid}.xml
          cp ${MAMBODIR}/run/scripts_ttdiffxs_13TeV_ljets/Boosted13TeV.sys.xml.template ${params}

          sed -i "s|@CHANNEL@|${ch_tag}|"     ${params}
          sed -i "s|@MCFILELIST@|${flist_mc}|"  ${params}
          sed -i "s|@NORMFILE@|${nomalizationfile}|"  ${params}
          sed -i "s|@SYST@|${syst}|"  ${params}
         
          mkdir -p ${MAMBODIR}/run/output/${syst}
          outfile=${syst}/${tag}.histograms.root.${batchid}
          jobname=${tag}.${batchid}

          echo ${params}  
          echo ${flist_mc}
       
	  echo "Submitting ${jobname}"
          MAMbo-submit.sh -p ${params} -f ${flist} -o ${outfile} -j ${jobname}
       done
     done < ${sysname_file}
     echo
done
