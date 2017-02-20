#!/bin/bash

channels="el mu co"
set -x
systs="Fcc_up Fcc_down Fc_up Fc_down Flight_up Flight_down"

for syst in $systs
do
	for c in $channels
	do
			nominal="output/nominal/tt_diffxs_13TeV.mc.Wjets.$c.nominal.nofullhad.histograms.root"
			path="output/$syst/tt_diffxs_13TeV.mc.Wjets.$c.$syst.nofullhad.histograms.root"
					# £cp -v $nominal $path
				  #cp -v $path $path.backup
				   # continue
					batchid="WjetsRescaler.$c.$syst"
					script="../jobs/$batchid.sh"
					log="../logs/$batchid.log"
					cat > $script << EOF
				   #root -b -q 'resolved_WjetsRescaler.C("$path", "$nominal" )'
                                   ./resolved_WjetsRescaler $path $nominal
EOF
					chmod +x $script
					echo $script
#				   ./$script
			               bsub -oe -oo $log -J $batchid -q T3_BO_LOCAL $script

		

			
	done

done
