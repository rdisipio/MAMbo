#!/bin/bash

analysis=tt_diffxs_13TeV
#outtag=TTbarResolved_resolved

systs="nominal"
systs=`cat resolved_kinematic_systematics.dat resolved_scale_systematics.dat | egrep -e "EG|MUONS"`
decays="nofullhad ljets"
decays="nofullhad"
for syst in $systs
do
	for decay in $decays
	do
		#syst=nominal

		#paramsdir=${MAMBODIR}/share/control/analysis_params/${outtag}	

		dsid=410000
		[ ! -z $1 ] && dsid=$1
	
		sendOnce=0
	#set -x

		batchid=hadd.$dsid.$decay.$syst
		script=../jobs/$batchid.sh
		cat > $script << EOF
#!/bin/bash
			#tag=${analysis}.mc.DiTop.${dsid}.${ch}.${syst}.${decay}
		#	tt_diffxs_13TeV.mc.DiTop.410000.mu.nominal.nofullhad.histograms.root.40
		hadd -f output/$syst/${analysis}.mc.DiTop.${dsid}.el.${syst}.${decay}.histograms.root output/$syst/${analysis}.mc.DiTop.${dsid}.el.*.${decay}.histograms.root.??
		hadd -f output/$syst/${analysis}.mc.DiTop.${dsid}.mu.${syst}.${decay}.histograms.root output/$syst/${analysis}.mc.DiTop.${dsid}.mu.*.${decay}.histograms.root.??
		
		hadd -f output/$syst/${analysis}.mc.DiTop.${dsid}.co.${syst}.${decay}.histograms.root output/$syst/${analysis}.mc.DiTop.${dsid}.el.${syst}.${decay}.histograms.root output/$syst/${analysis}.mc.DiTop.${dsid}.mu.${syst}.${decay}.histograms.root
EOF
#		cat $script
		qsub -q T3_BO_LOCAL $script
	done


done
