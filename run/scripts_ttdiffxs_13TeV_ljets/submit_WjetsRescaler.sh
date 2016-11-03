#!/bin/bash

#backgrounds="" #single top is special
channels="el mu co"
set -x

systs="Fcc_up Fcc_down Fc_up Fc_down Flight_up Flight_down"
directory="/home/ATLAS-T3/ffabbri/13TeVAnalisys/AnalysisTop/MAMbo/run/scripts_ttdiffxs_13TeV_ljets/output/TTDIFFXS_62_v30_newNorm"

for syst in $systs
do
	for c in $channels
	do
			nominal=${directory}"/nominal/tt_diffxs_13TeV.mc.Wjets.$c.nominal.histograms.root"
			path=${directory}"/"${syst}"/tt_diffxs_13TeV.mc.Wjets.${c}.${syst}.histograms.root"
			
			echo ${path}
					# £cp -v $nominal $path
				  #cp -v $path $path.backup
				   # continue
					batchid="WjetsRescaler.$c.$syst"
					script="../jobs/$batchid.sh"
					log="../logs/$batchid.log"
					cat > $script << EOF
				   root -b -q 'boosted_WjetsRescaler.C("$path", "$nominal" )'
			  
EOF
					chmod +x $script
					echo $script
				  ./$script
# 			               bsub -oe -oo $log -J $batchid -q T3_BO_LOCAL $script

		

			
	done

done
