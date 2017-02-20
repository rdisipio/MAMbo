#!/bin/bash

function MakePDFSysts
{

	systs=""
	#ct14nlo
	for i in {0..56}
	do
		if [ $# == 1 ]
		then
			if [ $1 != "ct14nlo" ]
			then
				break
			fi
		fi
		systs="PDF_CT14nlo_${i}_nominal ${systs}"		
		systs="PDF_CT14nlo_${i}_nocut ${systs}"		
	done
	#NNPDF30_nlo_as_0118
	for i in {0..100}
	do
		if [ $# == 1 ]
		then
			if [ $1 != "NNPDF30_nlo_as_0118" ]
			then
				break
			fi
		fi	
		systs="PDF_NNPDF30_nlo_as_0118_${i}_nominal ${systs}"
		systs="PDF_NNPDF30_nlo_as_0118_${i}_nocut ${systs}"
	done
	#MMHT2014nlo68cl
	for i in {0..50}
	do
		if [ $# == 1 ]
		then
			if [ $1 != "MMHT2014nlo68cl" ]
			then
				break
			fi
		fi	
		systs="PDF_MMHT2014nlo68cl_${i}_nominal ${systs}"
		systs="PDF_MMHT2014nlo68cl_${i}_nocut ${systs}"
	done
	#PDF4LHC15_nlo_30
	for i in {0..30}
	do
		if [ $# == 1 ]
		then
			if [ $1 != "PDF4LHC15_nlo_30" ]
			then
				break
			fi
		fi
		systs="PDF4LHC15_nlo_30_${i}_nominal ${systs}"
		systs="PDF4LHC15_nlo_30_${i}_nocut ${systs}"
	done
	#PDF4LHC15_nlo_asvar
	for i in {0..1}
	do
		if [ $# == 1 ]
		then
			if [ $1 != "PDF4LHC15_nlo_asvar" ]
			then
				break
			fi
		fi
		systs="PDF4LHC15_nlo_asvar_${i}_nominal ${systs}"
		systs="PDF4LHC15_nlo_asvar_${i}_nocut ${systs}"
	done
	echo $systs
}


pdfsysts=`MakePDFSysts PDF4LHC15_nlo_30`





analysis=tt_diffxs_13TeV
#outtag=TTbarResolved_resolved

systs="nocut"
systs=$pdfsysts
systs="nominal  `cat resolved_kinematic_systematics.dat resolved_scale_systematics.dat`"
# | egrep -e "EG|MUONS"`
#systs=`cat  resolved_scale_systematics.dat | grep lepton`
decays="nofullhad ljets"
decays="nofullhad"
#systs=$(cat failedsysts.txt )
production=TTDIFFXS_62
samples=mc.410000.PowhegPythiaEvtGen.e3698_s2608_s2183_r7267_r6282_p2516.${production}_v5.txt
#systs="nominal nocut"
#systs=$pdfsysts
systs="`cat resolved_scale_systematics.dat`"
systs="nominal nocut"
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
			log=../logs/$batchid.log
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
	#		./$script
#			qsub -q T3_BO_LOCAL $script
       			 bsub -oe -oo $log -J $batchid -q T3_BO_LOCAL $script

		done


	done
done
