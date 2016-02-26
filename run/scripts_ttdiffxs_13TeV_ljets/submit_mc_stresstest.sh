
#!/bin/bash

analysis=tt_diffxs_13TeV
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
      
          
#     filelist=${MAMBODIR}/run/scripts_ttdiffxs_13TeV_ljets/filelists_TTDIFFXS_35/mc.410000.PowhegPythiaEvtGen.e3698_s2608_s2183_r7267_r6282_p2460.TTDIFFXS_35_v2.txt
#     filelist_mc=${MAMBODIR}/run/scripts_ttdiffxs_13TeV_ljets/filelists_TTDIFFXS_35/mc.410000.PowhegPythiaEvtGen.e3698_s2608_s2183_r7267_r6282_p2460.TTDIFFXS_35_v2.txt

     filelistdir=${MAMBODIR}/run/scripts_ttdiffxs_13TeV_ljets/filelists_${production}
     filelist=$filelistdir/mc.410000.PowhegPythiaEvtGen.e3698_s2608_s2183_r7267_r6282_p2516.${production}_v2.txt
     filelist_mc=$filelistdir/mc.410000.PowhegPythiaEvtGen.e3698_s2608_s2183_r7267_r6282_p2516.${production}_v2.txt

     for flist in $(ls ${filelist}.??)
     do
        for stressType in "tt_m" "t_pt" "tt_mBump" "tt_rapidity" 
        do
           batchid=$(echo ${flist} | grep -oE "[^.]+$")

           flist_mc=$( echo ${flist} | sed "s/.${ch}.txt/.mc.txt/" )
 
           selection="nominal"
    	  
           
##NO CUT
            selection="nocut"
            params=${MAMBODIR}/run/Boosted13TeV_nocut_${ch}.stressTest_${stressType}.${decay}.${batchid}.xml
            cp ${MAMBODIR}/run/scripts_ttdiffxs_13TeV_ljets/Boosted13TeV.nocut.stressTest.xml.template ${params}


# ####NOMINAL
# 	   params=${MAMBODIR}/run/Boosted13TeV_${ch}.stressTest_${stressType}.${decay}.${batchid}.xml
#         cp ${MAMBODIR}/run/scripts_ttdiffxs_13TeV_ljets/Boosted13TeV.stressTest.xml.template ${params}

	   tag=${analysis}.mc.DiTop.${dsid}.${ch}.${selection}.stressTest_${stressType}.${decay}
    	   

           sed -i "s|@CHANNEL@|${ch_tag}|"     ${params}
           sed -i "s|@MCFILELIST@|${flist_mc}|"  ${params}
           sed -i "s|@NORMFILE@|${normalizationfile}|"  ${params}
           sed -i "s|@STRESSTYPE@|${stressType}|"  ${params}
           mkdir -p ${MAMBODIR}/run/output/stressTest
           outfile=stressTest/${tag}.histograms.root.${batchid}
           jobname=${tag}.${batchid}

           echo ${params}  
           echo ${flist_mc}
       
	   echo "Submitting ${jobname}"
           MAMbo-submit.sh -p ${params} -f ${flist} -o ${outfile} -j ${jobname}
         done
     done

     echo
done
