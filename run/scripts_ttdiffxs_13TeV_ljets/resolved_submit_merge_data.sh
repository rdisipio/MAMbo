#!/bin/bash

analysis=tt_diffxs_13TeV
#outtag=TTbarResolved_resolved

systs="data  qcd"
#systs=`cat resolved_kinematic_systematics.dat resolved_scale_systematics.dat | egrep -e "EG|MUONS"`
#systs=`cat  resolved_scale_systematics.dat | grep lepton`
decays="nofullhad ljets"
decays="nofullhad"
for syst in $systs
do
	
	#syst=nominal

	#paramsdir=${MAMBODIR}/share/control/analysis_params/${outtag}	

	
	[ ! -z $1 ] && dsid=$1

	sendOnce=0
#set -x
	dsid="AllPeriod"

	batchid=hadd.$dsid.$decay.$syst
	script=../jobs/$batchid.sh
	cat > $script << EOF
#!/bin/bash
		#tag=${analysis}.mc.DiTop.${dsid}.${ch}.${syst}.${decay}
	#	tt_diffxs_13TeV.mc.DiTop.410000.mu.nominal.nofullhad.histograms.root.40
	hadd -f output/nominal/${analysis}.${syst}.Main.${dsid}.el.Resolved.histograms.root output/nominal/${analysis}.${syst}.Main.00*.el.Resolved.histograms.root
	hadd -f output/nominal/${analysis}.${syst}.Main.${dsid}.mu.Resolved.histograms.root output/nominal/${analysis}.${syst}.Main.00*.mu.Resolved.histograms.root
	hadd -f output/nominal/${analysis}.${syst}.Main.${dsid}.co.Resolved.histograms.root output/nominal/${analysis}.${syst}.Main.${dsid}.el.Resolved.histograms.root output/nominal/${analysis}.${syst}.Main.${dsid}.mu.Resolved.histograms.root 

EOF
	chmod +x $script
#	./$script
		qsub -q T3_BO_LOCAL $script



done
