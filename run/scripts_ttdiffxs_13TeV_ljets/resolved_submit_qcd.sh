#!/bin/bash

analysis=tt_diffxs_13TeV

sourcedir=$PWD
method=MM
filelistdir=filelists_TTDIFFXS_62
systs="fakes_realEff_stat_D fakes_realEff_stat_U fakes_fakeEff_stat_D fakes_fakeEff_stat_U fakes_fakeEff_MCscale_D fakes_fakeEff_MCscale_U fakes_fakeEff_CR_S"







template=$PWD/control/analysis_params/13TeV_ljets_resolved/config/qcd_Resolved_MM.xml.template

for syst in $systs
do
	for ch in electron muon
	do
	#  [[ ${ch} == "el" ]] && stream="Egamma"
	#  [[ ${ch} == "mu" ]] && stream="Muons"
	  stream="Main"
	  for list in `ls ${filelistdir}/ | grep data`
	  do
		run=`echo $list | cut -d. -f2`
		topology=Resolved
		tag=${analysis}.qcd.${stream}.${run}.${ch}.${topology}.$method

		jobname=${tag}.$syst
		
		paramfile=$PWD/control/analysis_params/13TeV_ljets_resolved/config/qcd_${topology}_${ch}_${method}_$syst.xml
		cp $template $paramfile
		sed -i.bak s/@CHANNEL@/$ch/g $paramfile
		sed -i.bak s/@SYST@/$syst/g $paramfile
		

		filelist=$PWD/${filelistdir}/$list
		mkdir -p output/$syst
		outfile=$syst/${tag}.histograms.root

		MAMbo-submit.sh -p ${paramfile} -f ${filelist} -o ${outfile} -j ${jobname}
		
	  done

	done
done
