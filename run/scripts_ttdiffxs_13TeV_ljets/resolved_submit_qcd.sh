#!/bin/bash

analysis=tt_diffxs_13TeV

sourcedir=$PWD

filelistdir=filelists_TTDIFFXS_55
for method in MM
do
	for ch in el
	do
	#  [[ ${ch} == "el" ]] && stream="Egamma"
	#  [[ ${ch} == "mu" ]] && stream="Muons"
	  stream="Main"
	  for list in `ls ${filelistdir}/ | grep data`
	  do
		run=`echo $list | cut -d. -f2`
		topology=Resolved
		tag=${analysis}.qcd.${stream}.${run}.${ch}.${topology}.$method

		jobname=${tag}
		paramfile=$PWD/control/analysis_params/13TeV_ljets_resolved/config/qcd_${topology}_${ch}_$method.xml

		filelist=$PWD/${filelistdir}/$list
		mkdir -p output_newMM/nominal
		outfile=nominal/${tag}.histograms.root

		MAMbo-submit.sh -p ${paramfile} -f ${filelist} -o ${outfile} -j ${jobname}
		
	  done

	done
done
