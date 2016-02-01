#!/bin/bash

analysis=tt_diffxs_13TeV
#outtag=TTbarResolved_resolved
syst=nominal
production=TTDIFFXS_55
normalizationfilepath=${MAMBODIR}/share/data/NEvents_${production}/
filedir=${MAMBODIR}/run/scripts_ttdiffxs_13TeV_ljets/filelists_${production}/
#paramsdir=${MAMBODIR}/share/control/analysis_params/${outtag}
lumi=3209.05

decay=ljets
[ ! -z $2 ] && decay=$2

for ch in el mu
do

   [ $ch == "el" ] && ch_tag="electron"
   [ $ch == "mu" ] && ch_tag="muon"
      
   filelist=${MAMBODIR}/run/scripts_ttdiffxs_13TeV_ljets/AllBkg${production}.txt

   while read flist           
     do 
  
       if [[ "x$flist" == "x#"* ]]; then
         continue
       fi
 
         dsids=`echo $flist | cut -d. -f2`

         inputfile=`ls ${filedir}/mc.${dsids}.*`

	 normalizationfile=${normalizationfilepath}/$( echo ${flist} | sed s/mc.// | sed "s/.txt/.evt.n/" )
         echo "normfile: ${normalizationfile}"

    	 tag=${analysis}.mc.bkg.${dsids}.${ch}.${decay}


	 params=${MAMBODIR}/run/Boosted13TeVBkg_${ch}.${decay}.${dsids}.xml
         cp ${MAMBODIR}/run/scripts_ttdiffxs_13TeV_ljets/Boosted13TevBkg.xml.template ${params}

         sed -i "s|@CHANNEL@|${ch_tag}|"     ${params}
         sed -i "s|@NORMFILE@|${normalizationfile}|"  ${params}
         sed -i "s|@LUMI@|${lumi}|" ${params}  

         mkdir -p ${MAMBODIR}/run/output/BackGroundMC_${production}
         outfile=BackGroundMC_${production}/${tag}.histograms.root
         jobname=${tag}".sh"


      	 echo "config ${params}"
#	 echo "input ${inputfile}"
#	 echo "output ${outfile}"
#	 echo "Submitting ${jobname}"

        MAMbo-submit.sh -p ${params} -f ${inputfile} -o ${outfile} -j ${jobname}
     done < ${filelist}

     echo
done
