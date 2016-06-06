#!/bin/bash

#backgrounds="" #single top is special
channels="el mu co"
set -x

systs=`cat boosted_reduced_systematics.txt`


for syst in $systs
do
	for c in $channels
	do
			nominal="output/nominal/tt_diffxs_13TeV.mc.Wjets.$c.nominal.histograms.root"
			path="output/$syst/tt_diffxs_13TeV.mc.Wjets.$c.$syst.histograms.root"
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
#				   ./$script
			               bsub -oe -oo $log -J $batchid -q T3_BO_LOCAL $script

		

			
	done

done
