#!/bin/bash

analysis=tt_diffxs_13TeV
#outtag=TTbarResolved_resolved
#systs=nominal
#systs="nominal wjets_stat wjets_syst"
#systs="wjets_stat wjets_syst"
systs="nominal wjets_stat wjets_syst $(cat boosted_reduced_systematics.txt)"
isWjets=0
wjetsRuns=$(cat Wjets.run )
production=TTDIFFXS_62
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
  #  filelist=${MAMBODIR}/run/scripts_ttdiffxs_13TeV_ljets/Stop${production}.txt  
  #  filelist=${MAMBODIR}/run/scripts_ttdiffxs_13TeV_ljets/Diboson${production}.txt
    
  for syst in $systs
  do
      
      sys_name="NOMINAL"
      tree_name="nominal"
      wjetsSyst="nominal"
      
      while read flist           
      do 
	  
	  
	  if [[ "x$flist" == "x#"* ]]; then
              continue
	  fi
	  
	  dsids=`echo $flist | cut -d. -f2`
	  
	  isWjets=0
	  if [[ ${wjetsRuns} == *"${dsids}"* ]]
	  then
	      echo "${dsids}  It's a wjets sample!"
	      isWjets=1
	  fi
	 
	  
	  if [[ ${syst} == "scaleFactor_"* ]]; then
              sys_name=${syst}
          else 
              tree_name=${syst}
          fi
	  
	 if [[ $syst == "wjets"* ]]
	 then
	     if [ $isWjets == "0" ]
	     then
		 echo $syst asked for non-wjet run $dsids, skipping
		 continue
	     fi
             wjetsSyst=$(echo $syst | sed s/wjets_//)
	     echo Wjets syst $wjetsSyst
	     sys_name=NOMINAL
	     tree_name=nominal
	     
	 fi
	 
 

         inputfile=`ls ${filedir}/mc.${dsids}.*`

	 normalizationfile=${normalizationfilepath}/$( echo ${flist} | sed s/mc.// | sed "s/.txt/.evt.n/" )
         echo "normfile: ${normalizationfile}"

    	 tag=${analysis}.mc.bkg.${dsids}.${ch}.${decay}.${syst}


	 params=${MAMBODIR}/run/Boosted13TeVBkg_${ch}.${decay}.${syst}.${dsids}.xml
         cp ${MAMBODIR}/run/scripts_ttdiffxs_13TeV_ljets/Boosted13TevBkg.xml.template ${params}

	 	 
         sed -i "s|@CHANNEL@|${ch_tag}|"     ${params}
         sed -i "s|@NORMFILE@|${normalizationfile}|"  ${params}
         sed -i "s|@LUMI@|${lumi}|" ${params}  
	 sed -i "s|@TREE@|${tree_name}|"  ${params}
         sed -i "s|@SYST@|${sys_name}|"  ${params}
         sed -i "s|@ISWJETS@|${isWjets}|"  ${params}
         sed -i "s|@WJETSSYST@|${wjetsSyst}|"  ${params}
	 
	 mkdir -p ${MAMBODIR}/run/output/BackGroundMC_${production}
	 echo  "syst ${syst}"
	 if [[ ${syst} != "nominal" ]]; then
	     mkdir -p ${MAMBODIR}/run/output/BackGroundMC_${production}/syst/${syst}
	     #outdir=  BackGroundMC_${production}/syst/${syst}
	     outfile=BackGroundMC_${production}/syst/${syst}/${tag}.histograms.root
	 else
	     mkdir -p ${MAMBODIR}/run/output/BackGroundMC_${production}/nominal/
	     outfile=BackGroundMC_${production}/nominal/${tag}.histograms.root
	 fi
       #  outfile=BackGroundMC_${production}/${tag}.histograms.root
         jobname=${tag}".sh"
	 
	 
      	 echo "config ${params}"
#	 echo "input ${inputfile}"
	 echo "output ${outfile}"
#	 echo "Submitting ${jobname}"
	 
	 MAMbo-submit.sh -p ${params} -f ${inputfile} -o ${outfile} -j ${jobname}
      done < ${filelist}
      
     #  echo
  done
done