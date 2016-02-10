#!/bin/bash

analysis=tt_diffxs_13TeV
#outtag=TTbarResolved_resolved

systs="nocut"
#systs=`cat resolved_kinematic_systematics.dat resolved_scale_systematics.dat | grep extra`
# | egrep -e "EG|MUONS"`
#systs=`cat  resolved_scale_systematics.dat | grep lepton`
decays="nofullhad ljets"
decays="nofullhad"

production=TTDIFFXS_55
samples=mc.410000.PowhegPythiaEvtGen.e3698_s2608_s2183_r7267_r6282_p2516.${production}_v2.txt
[ ! -z $1 ] && samples=$(cat $1)

for sample in $samples
do
	for syst in $systs
	do
		for decay in $decays
		do
			#syst=nominal

			#paramsdir=${MAMBODIR}/share/control/analysis_params/${outtag}	

			dsid=$(echo $sample | cut -d. -f2)
			gridtag=$(echo $sample | cut -d. -f4 )
			simulationtype=$(echo $gridtag | cut -d_ -f2)
		
			sendOnce=0
		#set -x

			batchid=hadd.$dsid.$decay.$syst.$simulationtype
			script=../jobs/$batchid.sh
			cat > $script << EOF
	#!/bin/bash
		if [[ $simulationtype == "s"* ]]
		then
			echo full sim!
				hadd -f output/$syst/${analysis}.mc.DiTop.${dsid}.el.${syst}.${decay}.histograms.root output/$syst/${analysis}.mc.DiTop.${dsid}.el.*.${decay}.histograms.root.??
				hadd -f output/$syst/${analysis}.mc.DiTop.${dsid}.mu.${syst}.${decay}.histograms.root output/$syst/${analysis}.mc.DiTop.${dsid}.mu.*.${decay}.histograms.root.??
			
				hadd -f output/$syst/${analysis}.mc.DiTop.${dsid}.co.${syst}.${decay}.histograms.root output/$syst/${analysis}.mc.DiTop.${dsid}.el.${syst}.${decay}.histograms.root output/$syst/${analysis}.mc.DiTop.${dsid}.mu.${syst}.${decay}.histograms.root
			else
			hadd -f output/$syst/${analysis}.mc.AFII.DiTop.${dsid}.el.${syst}.${decay}.histograms.root output/$syst/${analysis}.mc.AFII.DiTop.${dsid}.el.*.${decay}.histograms.root.??
			hadd -f output/$syst/${analysis}.mc.AFII.DiTop.${dsid}.mu.${syst}.${decay}.histograms.root output/$syst/${analysis}.mc.AFII.DiTop.${dsid}.mu.*.${decay}.histograms.root.??
			
			hadd -f output/$syst/${analysis}.mc.AFII.DiTop.${dsid}.co.${syst}.${decay}.histograms.root output/$syst/${analysis}.mc.AFII.DiTop.${dsid}.el.${syst}.${decay}.histograms.root output/$syst/${analysis}.mc.AFII.DiTop.${dsid}.mu.${syst}.${decay}.histograms.root
			fi	
	
EOF
			chmod +x $script
			./$script
#			qsub -q T3_BO_LOCAL $script
		done


	done
done
