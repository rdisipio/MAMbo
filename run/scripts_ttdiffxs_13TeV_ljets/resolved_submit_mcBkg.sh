#!/bin/bash
#set -x
analysis=tt_diffxs_13TeV
#outtag=TTbarResolved_resolved
syst=nominal
nomalizationfilepath=${MAMBODIR}/share/data/NEvents_${production}/
filelistdir=$PWD/filelists_${production}/
#paramsdir=${MAMBODIR}/share/control/analysis_params/${outtag}
sendOnce=0
production=TTDIFFXS_55
for ch in el mu
do

   [ $ch == "el" ] && ch_tag="electron"
   [ $ch == "mu" ] && ch_tag="muon"
      
   filelist=AllBkgTTDIFFXS_55.txt

   while read flist           
     do 
  
       if [[ "x$flist" == "x#"* ]]; then
         continue
       fi
 
         dsid=`echo $flist | cut -d. -f2`

         nomalizationfile=${nomalizationfilepath}/$( echo ${flist} | sed s/mc.// | sed "s/.txt/.evt.n/" )
    	 tag=${analysis}.mc.bkg.${dsid}.${ch}.${syst}
	mkdir -p output_${production}/${syst}
         outfile=${syst}/${tag}.histograms.root
         jobname=${tag}
 	 params=$PWD/control/analysis_params/13TeV_ljets_resolved/config/Resolved13TeV.${dsid}.${ch}.${syst}.xml
	 cp Resolved13TeVBkg.xml.template ${params}

         sed -i "s|@CHANNEL@|${ch_tag}|"     ${params}
         sed -i "s|@NORMFILE@|${nomalizationfile}|"  ${params}
	sed -i "s|@SYST@|${syst}|"  ${params}
         jobname=${tag}

         echo ${params}  
         
       
	 echo "Submitting ${jobname}"
	 flist=${filelistdir}/${flist}
	 echo ${flist}
	 
         MAMbo-submit.sh -p ${params} -f ${flist} -o ${outfile} -j ${jobname}
				if [ $sendOnce -eq 1 ]
				then
					break
				fi		 
     done < ${filelist}


     echo
done
