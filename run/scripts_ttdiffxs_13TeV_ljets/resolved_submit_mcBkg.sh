#!/bin/bash
#set -x
analysis=tt_diffxs_13TeV
#outtag=TTbarResolved_resolved
syst=nominal
nomalizationfilepath=${MAMBODIR}/share/data/NEvents13TeV
filelistdir=$PWD/filelists_TTDIFFXS_3/
#paramsdir=${MAMBODIR}/share/control/analysis_params/${outtag}

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
 
         dsid=`echo $flist | cut -d. -f1`

         nomalizationfile=${nomalizationfilepath}/$( echo ${flist} | sed "s/.list/.evt.n/" )
    	 tag=${analysis}.mc.bkg.${dsid}.${ch}.${syst}
         mkdir -p output/${syst}
         outfile=${syst}/${tag}.histograms.root
         jobname=${tag}
 	 params=$PWD/Resolved13TeV.${dsid}.${ch}.${syst}.xml
	 cp Resolved13TevBkg.xml.template ${params}

         sed -i "s|@CHANNEL@|${ch_tag}|"     ${params}
         sed -i "s|@NORMFILE@|${nomalizationfile}|"  ${params}
         jobname=${tag}

         echo ${params}  
         
       
	 echo "Submitting ${jobname}"
	 flist=${filelistdir}/${flist}
	 echo ${flist}
	 
         MAMbo-submit.sh -p ${params} -f ${flist} -o ${outfile} -j ${jobname}
     done < ${filelist}


     echo
done
