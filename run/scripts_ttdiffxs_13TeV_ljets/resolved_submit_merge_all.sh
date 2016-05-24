#!/bin/bash

systs="nominal `cat resolved_kinematic_systematics.dat resolved_scale_systematics.dat` Zjets_up Stop_up Diboson_up ttV_up wjets_stat wjets_syst"
#systs="nominal"
systs="Diboson_up Stop_up Zjets_up" 
channels="el mu co"

for  syst in $systs
do
	dir="$PWD/output/$syst/"

		batchid=hadd.all.$syst
		script=../jobs/$batchid.sh
		log=../jobs/$batchid.log
		rm -f $log
		cat > $script << EOF
#!/bin/bash
cd $dir
for c in $channels
do
                bkgs="Wjets Zjets Diboson ttV Stop"
                backgroundsamples=""
                for b in \$bkgs
                do
                        backgroundsamples="\$backgroundsamples tt_diffxs_13TeV.mc.\$b.\$c.$syst.nofullhad.histograms.root"
#		backgroundsamples="tt_diffxs_13TeV.mc.Wjets.\$c.$syst.nofullhad.histograms.root tt_diffxs_13TeV.mc.Zjets.\$c.$syst.nofullhad.histograms.root tt_diffxs_13TeV.mc.Diboson.\$c.$syst.nofullhad.histograms.root tt_diffxs_13TeV.mc.ttV.\$c.$syst.nofullhad.histograms.root
                done
                backgroundsamples="\$backgroundsamples tt_diffxs_13TeV.qcd.Main.AllPeriod.\$c.Resolved.MM.histograms.root"
		signalsample="tt_diffxs_13TeV.mc.DiTop.410000.\$c.$syst.nofullhad.histograms.root"
		#do all background
		hadd -f tt_diffxs_13TeV.mc.AllBkg.\$c.$syst.nofullhad.histograms.root \$backgroundsamples
		#do total prediction
		hadd -f tt_diffxs_13TeV.mc.TotalPrediction.\$c.$syst.nofullhad.histograms.root \$signalsample tt_diffxs_13TeV.mc.AllBkg.\$c.$syst.nofullhad.histograms.root
done
		#hadd -f AllBkg_co.root AllBkg_el.root AllBkg_mu.root
		
                #hadd -f TotalPrediction_co.root TotalPrediction_el.root TotalPrediction_mu.root
EOF
	chmod +x $script
#	./$script
	bsub -oe -oo $log -J $batchid -q T3_BO_LOCAL $script

done
