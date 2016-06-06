#!/bin/bash

analysis=tt_diffxs_13TeV
production=TTDIFFXS_62

dsid=410000
[ ! -z $1 ] && dsid=$1

decay=ljets
[ ! -z $2 ] && decay=$2

normalizationdir=${MAMBODIR}/share/data/NEvents_${production}
normalizationfile=$normalizationdir/410000.PowhegPythiaEvtGen.e3698_s2608_s2183_r7267_r6282_p2516.${production}_v5.evt.n
sysname_file=${MAMBODIR}/run/scripts_ttdiffxs_13TeV_ljets/boosted_reduced_systematics.txt
#sysname_file=${MAMBODIR}/run/scripts_ttdiffxs_13TeV_ljets/boosted_el_systematics.txt
lumi=3209.05

for ch in el mu
do
     echo "INFO: submitting DiTop dsid=$dsid channel ${ch} decay ${decay}"

     [ $ch == "el" ] && ch_tag="electron"
     [ $ch == "mu" ] && ch_tag="muon"

     [ $ch == "el" ] && ch_sys="_MU_"
     [ $ch == "mu" ] && ch_sys="_EL_"
      
     filelistdir=${MAMBODIR}"/run/scripts_ttdiffxs_13TeV_ljets/filelists_"${production}
     filelist=$filelistdir/mc.410000.PowhegPythiaEvtGen.e3698_s2608_s2183_r7267_r6282_p2516.${production}_v5.txt
     filelist_mc=$filelistdir/mc.410000.PowhegPythiaEvtGen.e3698_s2608_s2183_r7267_r6282_p2516.${production}_v5.txt

     while read syst 
     do
     
       sys_name="NOMINAL"
       tree_name="nominal"
       
       for flist in $(ls ${filelist}.??)
       do
          if [[ "x$syst" == "x#"* ]]; then
             continue
          fi
#           if [[ ${syst} == *${ch_sys}* ]]; then
#              continue
#           fi
     
          batchid=$(echo ${flist} | grep -oE "[^.]+$")

          flist_mc=$( echo ${flist} | sed "s/.${ch}.txt/.mc.txt/" )

    	  tag=${analysis}.mc.DiTop.${dsid}.${ch}.${syst}.${decay}


 	  params=${MAMBODIR}/run/Boosted13TeV_${ch}.${syst}.${decay}.${batchid}.xml
          cp ${MAMBODIR}/run/scripts_ttdiffxs_13TeV_ljets/Boosted13TeV.sys.xml.template ${params}
          
          if [[ ${syst} == "scaleFactor_"* ]]; then
           sys_name=${syst}
          else
           tree_name=${syst}
          fi

          sed -i "s|@CHANNEL@|${ch_tag}|"     ${params}
          sed -i "s|@MCFILELIST@|${flist_mc}|"  ${params}
          sed -i "s|@NORMFILE@|${normalizationfile}|"  ${params}
          sed -i "s|@LUMI@|${lumi}|" ${params}
          sed -i "s|@TREE@|${tree_name}|"  ${params}
          sed -i "s|@SYST@|${sys_name}|"  ${params}
          
          outdir="prod_62_systnew/"${syst}
          mkdir -p ${MAMBODIR}/run/output/${outdir}
          outfile=${outdir}/${tag}.histograms.root.${batchid}
          jobname=${tag}.${batchid}

          echo ${params}  
          echo ${flist_mc}
       
	  echo "Submitting ${jobname}"
          MAMbo-submit.sh -p ${params} -f ${flist} -o ${outfile} -j ${jobname}
       done
     done < ${sysname_file}
     echo
done
