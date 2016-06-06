#!/bin/bash

#systs="`cat boosted_reduced_systematics.txt` Zjets_up Stop_up Diboson_up ttV_up wjets_stat wjets_syst fakes_realEff_stat_D fakes_realEff_stat_U fakes_fakeEff_stat_D fakes_fakeEff_stat_U fakes_fakeEff_MCscale_D fakes_fakeEff_MCscale_U fakes_fakeEff_CR_S"
#systs="nominal"
#systs="Diboson_up Stop_up Zjets_up ttV_up" 
systs="wjets_stat wjets_syst" 
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
                        backgroundsamples="\$backgroundsamples tt_diffxs_13TeV.mc.\$b.\$c.$syst.histograms.root"

                done
                backgroundsamples="\$backgroundsamples tt_diffxs_13TeV.QCD.AllPeriod.\$c.Boosted.MM.$syst.histograms.root" 
		signalsample="tt_diffxs_13TeV.mc.DiTop.410000.\$c.$syst.histograms.root"
		#do all background
		hadd -f tt_diffxs_13TeV.mc.AllBkg.\$c.$syst.histograms.root \$backgroundsamples
		#do total prediction
		hadd -f tt_diffxs_13TeV.mc.TotalPrediction.\$c.$syst.histograms.root \$signalsample tt_diffxs_13TeV.mc.AllBkg.\$c.$syst.histograms.root
done
		#hadd -f AllBkg_co.root AllBkg_el.root AllBkg_mu.root
		
                #hadd -f TotalPrediction_co.root TotalPrediction_el.root TotalPrediction_mu.root
EOF
	chmod +x $script
	./$script
#	bsub -oe -oo $log -J $batchid -q T3_BO_LOCAL $script

done
