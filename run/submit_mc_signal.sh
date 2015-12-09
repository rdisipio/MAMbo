#!/bin/bash

analysis=tt_diffxs_13TeV
#outtag=TTbarResolved_resolved
syst=nocut

#paramsdir=${MAMBODIR}/share/control/analysis_params/${outtag}

dsid=410000
[ ! -z $1 ] && dsid=$1

decay=ljets
[ ! -z $2 ] && decay=$2

nomalizationfile=${MAMBODIR}/share/data/NEvents13TeV/410000.PowhegPythiaEvtGen.e3698_s2608_s2183_r6765_r6282_p2442.evt.n

for ch in el mu
do
     echo "INFO: submitting DiTop dsid=$dsid channel ${ch} decay ${decay}"

     [ $ch == "el" ] && ch_tag="electron"
     [ $ch == "mu" ] && ch_tag="muon"
      
     filelist=generator.txt
     filelist_mc=generator.txt

     for flist in $(ls ${filelist}.??)
     do
         batchid=$(echo ${flist} | grep -oE "[^.]+$")

         flist_mc=$( echo ${flist} | sed "s/.${ch}.txt/.mc.txt/" )

    	 tag=${analysis}.mc.DiTop.${dsid}.${ch}.${syst}.${decay}

        params=Boosted13TeV_nocut_${ch}.${syst}.${decay}.${batchid}.xml
        cp Boosted13TeV.nocut.xml.template ${params}

# 	 params=Boosted13TeV_${ch}.${syst}.${decay}.${batchid}.xml
#          cp Boosted13TeV.xml.template ${params}

         sed -i "s|@CHANNEL@|${ch_tag}|"     ${params}
         sed -i "s|@MCFILELIST@|${flist_mc}|"  ${params}
         sed -i "s|@NORMFILE@|${nomalizationfile}|"  ${params}
         mkdir -p output/${syst}
         outfile=${syst}/${tag}.histograms.root.${batchid}
         jobname=${tag}.${batchid}

         echo ${params}  
         echo ${flist_mc}
       
	 echo "Submitting ${jobname}"
         MAMbo-submit.sh -p ${params} -f ${flist} -o ${outfile} -j ${jobname}
     done

     echo
done
