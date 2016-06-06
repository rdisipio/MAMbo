
#!/bin/bash

analysis=tt_diffxs_13TeV
#syst=nocut
production=TTDIFFXS_62

systs="nominal nocut"
#systs="nocut"
decays=ljets

#dsid=410000
#[ ! -z $1 ] && dsid=$1


#[ ! -z $2 ] && decay=$2



for syst in $systs
do
    mkdir -p output/$syst
    for decay in $decays
	do
		#syst=nominal
	
		#paramsdir=${MAMBODIR}/share/control/analysis_params/${outtag}	
	
	samples=mc.410000.PowhegPythiaEvtGen.e3698_s2608_s2183_r7267_r6282_p2516.${production}_v5.txt	

	[ ! -z $1 ] && samples=$(cat $1)
	echo "Running on $samples"
	for sample in $samples
	do
	    filelistdir=$PWD/filelists_${production}/
	    filelist=$filelistdir/$sample
	    
	    dsid=$(echo $sample | cut -d. -f2)
	    nomalizationfile=$(echo $sample | sed s/mc.// | sed s/txt/evt.n/)
	    nomalizationdir=${MAMBODIR}/share/data/NEvents_${production}/
	    nomalizationfile=${nomalizationdir}/${nomalizationfile}
	  	    
  
	    if [ $syst == "nocut" ]
	    then
		template=Boosted13TeV.nocut.xml.template
	    else
		template=Boosted13TeV.xml.template
	    fi
	    
	    
	    sendOnce=0
		#set -x
	    

	    
	    for ch in el mu
	    do
		echo "INFO: submitting DiTop dsid=$dsid channel ${ch} decay ${decay}"

		[ $ch == "el" ] && ch_tag="electron"
		[ $ch == "mu" ] && ch_tag="muon"
		
	#	filelist_mc=$filelist
		gridtag=$(echo $sample | cut -d. -f4 )
		simulationtype=$(echo $gridtag | cut -d_ -f2)
				
		for flist in $(ls ${filelist}.??)
		do
		    batchid=$(echo ${flist} | grep -oE "[^.]+$")
		    
		    flist_mc=$( echo ${flist} | sed "s/.${ch}.txt/.mc.txt/" )
		   
    		    tag=${analysis}.mc.DiTop.${dsid}.${ch}.${syst}.${decay}
		    
		    if [[ $simulationtype == "s"* ]]
		    then
			echo full sim!
			tag=${analysis}.mc.DiTop.${dsid}.${ch}.${syst}.${decay}
		    else
			tag=${analysis}.mc.AFII.DiTop.${dsid}.${ch}.${syst}.${decay}
		    fi
		    
		    
		    params=${MAMBODIR}/run/Boosted13TeV_${tag}.${batchid}.xml
		    cp ${MAMBODIR}/run/scripts_ttdiffxs_13TeV_ljets/$template ${params}
		    
		    
		    sed -i "s|@CHANNEL@|${ch_tag}|"     ${params}
		    sed -i "s|@MCFILELIST@|${flist_mc}|"  ${params}
		    sed -i "s|@NORMFILE@|${nomalizationfile}|"  ${params}
		    mkdir -p ${MAMBODIR}/run/output/${syst}
		    outfile=${syst}/${tag}.histograms.root.${batchid}
		    jobname=${tag}.${batchid}
		    
		    
		    echo ${params} 
 
		    echo ${flist_mc}
		    echo ${outfile}
		    
		    echo "Submitting ${jobname}"
                    MAMbo-submit.sh -p ${params} -f ${flist} -o ${outfile} -j ${jobname}
		    if [ $sendOnce -eq 1 ]
		    then
			break
		    fi
		done
	    done
	    echo
	done
    done
done
