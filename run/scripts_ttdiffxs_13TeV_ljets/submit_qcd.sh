#!/bin/bash

analysis=tt_diffxs_13TeV

sourcedir=${MAMBODIR}/run/scripts_ttdiffxs_13TeV_ljets
prod="prod62"
systs="nominal fakes_realEff_stat_D fakes_realEff_stat_U fakes_fakeEff_stat_D fakes_fakeEff_stat_U fakes_fakeEff_MCscale_D fakes_fakeEff_MCscale_U fakes_fakeEff_CR_S"
#systs="nominal"

for ch in el mu 
do
#  [[ ${ch} == "el" ]] && stream="Egamma"
#  [[ ${ch} == "mu" ]] && stream="Muons"
  stream="QCD"
  method="MM"
  topology="Boosted"

  for syst in $systs
  do
      
      template=${sourcedir}/qcd_${topology}_${ch}_${method}.xml
      paramfile=${sourcedir}/qcd_${topology}_${ch}_${method}_${syst}.xml
      cp $template $paramfile
      sed -i.bak s/@SYST@/$syst/g $paramfile
      for list in `ls ${MAMBODIR}/run/scripts_ttdiffxs_13TeV_ljets/filelists_TTDIFFXS_62/*physics_Main*`
      do
	  run=`echo $list | cut -d. -f2`
	  topology=Boosted
	  tag=${analysis}.${stream}.${run}.${ch}.${topology}.${method}.${syst}
	  
	  echo $run
	  
	  jobname=${tag}
     
      #filelist=${sourcedir}/filelists_TTDIFFXS_3/$list
	  mkdir -p ${MAMBODIR}/run/output/QCD_${prod}/${syst}
	  outfile=QCD_${prod}/${syst}/${tag}.histograms.root
      # echo $outfile
	 # MAMbo-submit.sh -p ${paramfile} -f ${list} -o ${outfile} -j ${jobname}
      done
  done
  
done
