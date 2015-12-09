#!/bin/bash

analysis=tt_diffxs_13TeV
#outtag=TTbarResolved_resolved
syst=nominal
nomalizationfilepath=${MAMBODIR}/share/data/NEvents13TeV
filedir=${MAMBODIR}/run/NewList
#paramsdir=${MAMBODIR}/share/control/analysis_params/${outtag}


decay=ljets
[ ! -z $2 ] && decay=$2

for ch in el mu
do

   [ $ch == "el" ] && ch_tag="electron"
   [ $ch == "mu" ] && ch_tag="muon"
      
   filelist=AllBkg.txt

   while read flist           
     do 
  
       if [[ "x$flist" == "x#"* ]]; then
         continue
       fi
 
         dsids=`echo $flist | cut -d. -f1`

         nomalizationfile=${nomalizationfilepath}/$( echo ${flist} | sed "s/.list/.evt.n/" )

    	 tag=${analysis}.mc.bkg.${dsids}.${ch}.${decay}

#         params=prova13TeV_nocut_${ch}.${syst}.${decay}.${dsids}.xml
 #        cp prova13TeV_nocut.xml.template ${params}

	 params=prova13TeVBkg_${ch}.${decay}.${dsids}.xml
         cp prova13TevBkg.xml.template ${params}

         sed -i "s|@CHANNEL@|${ch_tag}|"     ${params}
         sed -i "s|@NORMFILE@|${nomalizationfile}|"  ${params}
         mkdir -p output/BackGroundMC
         outfile=BackGroundMC/${tag}.histograms.root
         jobname=${tag}

         echo ${params}  
         
       
	 echo "Submitting ${jobname}"
	 flist=${filedir}/${flist}
	 echo ${flist}
	 
         MAMbo-submit.sh -p ${params} -f ${flist} -o ${outfile} -j ${jobname}
     done < ${filelist}

     echo
done
