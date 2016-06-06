
#!/bin/bash

analysis=tt_diffxs_13TeV
syst=closure0
production=TTDIFFXS_55


#paramsdir=${MAMBODIR}/share/control/analysis_params/${outtag}

dsid=410000
[ ! -z $1 ] && dsid=$1

decay=ljets
[ ! -z $2 ] && decay=$2



normalizationdir=${MAMBODIR}/share/data/NEvents_${production}
normalizationfile=$normalizationdir/410000.PowhegPythiaEvtGen.e3698_s2608_s2183_r7267_r6282_p2516.${production}_v2.evt.n




for ch in el mu
do
     echo "INFO: submitting DiTop dsid=$dsid channel ${ch} decay ${decay}"

     [ $ch == "el" ] && ch_tag="electron"
     [ $ch == "mu" ] && ch_tag="muon"
      
          

     filelistdir=$PWD/filelists_${production}/	
     filelist=$filelistdir/mc.410000.PowhegPythiaEvtGen.e3698_s2608_s2183_r7267_r6282_p2516.${production}_v2.txt
     filelist_mc=$filelistdir/mc.410000.PowhegPythiaEvtGen.e3698_s2608_s2183_r7267_r6282_p2516.${production}_v2.txt

     for flist in $(ls ${filelist}.??)
     do
         batchid=$(echo ${flist} | grep -oE "[^.]+$")

         flist_mc=$( echo ${flist} | sed "s/.${ch}.txt/.mc.txt/" )

    	 tag=${analysis}.mc.DiTop.${dsid}.${ch}.${syst}.${decay}

###CLOSURE  0	
	 params=${MAMBODIR}/run/Boosted13TeV_nominal_half0${ch}.${syst}.${decay}.${batchid}.xml
         cp ${MAMBODIR}/run/scripts_ttdiffxs_13TeV_ljets/Boosted13TeV.nominal.nofullhad.half0.xml.template ${params}
###CLOSURE  1
#	 params=${MAMBODIR}/run/Boosted13TeV_nominal_half1${ch}.${syst}.${decay}.${batchid}.xml
#	 cp ${MAMBODIR}/run/scripts_ttdiffxs_13TeV_ljets/Boosted13TeV.nominal.nofullhad.half1.xml.template ${params}


         sed -i "s|@CHANNEL@|${ch_tag}|"     ${params}
         sed -i "s|@MCFILELIST@|${flist_mc}|"  ${params}
         sed -i "s|@NORMFILE@|${normalizationfile}|"  ${params}
         mkdir -p ${MAMBODIR}/run/output/${syst}
         outfile=${syst}/${tag}.histograms.root.${batchid}
         jobname=${tag}.${batchid}

         echo ${params}  
         echo ${flist_mc}
       
	 echo "Submitting ${jobname}"
         MAMbo-submit.sh -p ${params} -f ${flist} -o ${outfile} -j ${jobname}
     done

     echo
done
