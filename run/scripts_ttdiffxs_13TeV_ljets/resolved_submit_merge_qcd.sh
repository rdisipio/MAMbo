#!/bin/bash

analysis=tt_diffxs_13TeV
#outtag=TTbarResolved_resolved

systs="qcd"
#systs=`cat resolved_kinematic_systematics.dat resolved_scale_systematics.dat | egrep -e "EG|MUONS"`
#systs=`cat  resolved_scale_systematics.dat | grep lepton`
decays="nofullhad ljets"
decays="nofullhad"
methods="MM"
systs="fakes_realEff_stat_D fakes_realEff_stat_U fakes_fakeEff_stat_D fakes_fakeEff_stat_U fakes_fakeEff_MCscale_D fakes_fakeEff_MCscale_U fakes_fakeEff_CR_S"

for method in $methods
do
	for syst in $systs
	do
		
		#syst=$syst

		#paramsdir=${MAMBODIR}/share/control/analysis_params/${outtag}	

		
		[ ! -z $1 ] && dsid=$1

		sendOnce=0
	#set -x
		dsid="AllPeriod"

		batchid=hadd.qcd.$dsid.nofullhad.$syst
		script=../jobs/$batchid.sh
		cat > $script << EOF
	#!/bin/bash
			#tag=${analysis}.mc.DiTop.${dsid}.${ch}.qcd.${decay}
		#	tt_diffxs_13TeV.mc.DiTop.410000.mu.$syst.nofullhad.$method.histograms.root.40
		hadd -f output/$syst/${analysis}.qcd.Main.${dsid}.el.Resolved.$method.histograms.root output/$syst/${analysis}.qcd.Main.00*.el.Resolved.$method.histograms.root
		hadd -f output/$syst/${analysis}.qcd.Main.${dsid}.mu.Resolved.$method.histograms.root output/$syst/${analysis}.qcd.Main.00*.mu.Resolved.$method.histograms.root
		hadd -f output/$syst/${analysis}.qcd.Main.${dsid}.co.Resolved.$method.histograms.root output/$syst/${analysis}.qcd.Main.${dsid}.el.Resolved.$method.histograms.root output/$syst/${analysis}.qcd.Main.${dsid}.mu.Resolved.$method.histograms.root 

EOF
		echo $script
		chmod +x $script
	#	./$script
		#	qsub -q T3_BO_LOCAL $script



	done
done
