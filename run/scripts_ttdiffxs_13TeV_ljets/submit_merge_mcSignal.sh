analysis=tt_diffxs_13TeV

#systs="`cat boosted_reduced_systematics.txt`"
production=TTDIFFXS_62
#samples=mc.410000.PowhegPythiaEvtGen.e3698_s2608_s2183_r7267_r6282_p2516.${production}_v5.txt
#samples=mc.410001.PowhegPythiaEvtGen.e3783_s2608_r7326_r6282_p2516.${production}_v5.txt
#samples=mc.410002.PowhegPythiaEvtGen.e3783_s2608_r7326_r6282_p2516.${production}_v5.txt
#samples=mc.410003.aMcAtNloHerwigppEvtGen.e4441_a766_a810_r6282_p2516.${production}_v5.txt
#samples=mc.410003.aMcAtNloHerwigppEvtGen.e4441_s2726_r7326_r6282_p2516.${production}_v5.txt
#samples=mc.410004.PowhegHerwigppEvtGen.e3836_a766_a810_r6282_p2516.${production}_v5.txt
#samples=mc.410500.PowhegPythia8EvtGen.e4797_s2726_r7326_r6282_p2516.${production}_v5.txt
#systs="nominal nocut"
systs="nocut"
[ ! -z $1 ] && samples=$(cat $1) # inputfile with all samples in ex:  ./submit_merge_mcSignal.sh SignalSystematics.txt 
for sample in $samples
do
	for syst in $systs
	do
	    if [[ ${syst} == "nominal"  ||  ${syst} == "nocut" ]]; then
		dir=${MAMBODIR}/run/output/Signal/${syst}	
	    else
		dir=${MAMBODIR}/run/output/Signal/syst/$syst
	    fi
	    dsid=$(echo $sample | cut -d. -f2)
	    gridtag=$(echo $sample | cut -d. -f4 )
	    simulationtype=$(echo $gridtag | cut -d_ -f2)
	    
	    sendOnce=0
		#set -x

	    batchid=hadd.$dsid.$syst.$simulationtype
	    script=../jobs/$batchid.sh
	    cat > $script << EOF
	#!/bin/bash
		if [[ $simulationtype == "s"* ]]
		then
			echo full sim!
				hadd -f ${dir}/${analysis}.mc.DiTop.${dsid}.el.${syst}.histograms.root ${dir}/${analysis}.mc.DiTop.${dsid}.el.*.histograms.root.??
				hadd -f ${dir}/${analysis}.mc.DiTop.${dsid}.mu.${syst}.histograms.root ${dir}/${analysis}.mc.DiTop.${dsid}.mu.*.histograms.root.??
			
				hadd -f ${dir}/${analysis}.mc.DiTop.${dsid}.co.${syst}.histograms.root ${dir}/${analysis}.mc.DiTop.${dsid}.el.${syst}.histograms.root ${dir}/${analysis}.mc.DiTop.${dsid}.mu.${syst}.histograms.root
			else
			hadd -f ${dir}/${analysis}.mc.AFII.DiTop.${dsid}.el.${syst}.histograms.root ${dir}/${analysis}.mc.AFII.DiTop.${dsid}.el.*.histograms.root.??
			hadd -f ${dir}/${analysis}.mc.AFII.DiTop.${dsid}.mu.${syst}.histograms.root ${dir}/${analysis}.mc.AFII.DiTop.${dsid}.mu.*.histograms.root.??
			
			hadd -f ${dir}/${analysis}.mc.AFII.DiTop.${dsid}.co.${syst}.histograms.root ${dir}/${analysis}.mc.AFII.DiTop.${dsid}.el.${syst}.histograms.root ${dir}/${analysis}.mc.AFII.DiTop.${dsid}.mu.${syst}.histograms.root
			fi	
	
EOF
	#		chmod +x $script
	#		./$script
			qsub -q T3_BO_LOCAL $script
	done
	
	
done

