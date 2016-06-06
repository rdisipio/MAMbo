#!/bin/bash

analysis=tt_diffxs_13TeV
methods="MM"
systs="nominal fakes_realEff_stat_D fakes_realEff_stat_U fakes_fakeEff_stat_D fakes_fakeEff_stat_U fakes_fakeEff_MCscale_D fakes_fakeEff_MCscale_U fakes_fakeEff_CR_S"
dirQcd="QCD_prod62"
 
for method in $methods
do
    for syst in $systs
    do
	
	[ ! -z $1 ] && dsid=$1
	
	sendOnce=0
	#set -x
	dsid="AllPeriod"
	
	batchid=hadd.qcd.$dsid.nofullhad.$syst
	script=../jobs/$batchid.sh
	cat > $script << EOF
	#!/bin/bash
	
		hadd -f output/$dirQcd/$syst/${analysis}.QCD.${dsid}.el.Boosted.$method.${syst}.histograms.root output/$dirQcd/$syst/${analysis}.QCD.00*.el.Boosted.$method.$syst.histograms.root
		hadd -f output/$dirQcd/$syst/${analysis}.QCD.${dsid}.mu.Boosted.$method.${syst}.histograms.root output/$dirQcd/$syst/${analysis}.QCD.00*.mu.Boosted.$method.$syst.histograms.root
		hadd -f output/$dirQcd/$syst/${analysis}.QCD.${dsid}.co.Boosted.$method.${syst}.histograms.root output/$dirQcd/$syst/${analysis}.QCD.${dsid}.el.Boosted.$method.${syst}.histograms.root output/$dirQcd/$syst/${analysis}.QCD.${dsid}.mu.Boosted.$method.${syst}.histograms.root 

EOF
		echo $script
		chmod +x $script
		./$script
		#	qsub -q T3_BO_LOCAL $script



	done
done
