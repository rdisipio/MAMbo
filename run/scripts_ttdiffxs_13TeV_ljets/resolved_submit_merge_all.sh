#!/bin/bash
set -x
wjetsSysts="CA_up CA_down Fcc_up Fcc_down Flight_up Flight_down"
allSysts="nominal `cat resolved_kinematic_systematics.dat resolved_scale_systematics.dat` Zjets_up Stop_up Diboson_up ttV_up fakes_realEff_stat_D fakes_realEff_stat_U fakes_fakeEff_stat_D fakes_fakeEff_stat_U fakes_fakeEff_MCscale_D fakes_fakeEff_MCscale_U fakes_fakeEff_CR_S $wjetsSysts"

systs="nominal `cat resolved_kinematic_systematics.dat resolved_scale_systematics.dat` Zjets_up Stop_up Diboson_up ttV_up wjets_stat wjets_syst"
#systs="nominal"
#systs="Diboson_up Stop_up Zjets_up" 
channels="el mu co"
#systs="fakes_realEff_stat_D fakes_realEff_stat_U fakes_fakeEff_stat_D fakes_fakeEff_stat_U fakes_fakeEff_MCscale_D fakes_fakeEff_MCscale_U fakes_fakeEff_CR_S"
systs="nominal `cat resolved_kinematic_systematics.dat resolved_scale_systematics.dat` 
Zjets_up Stop_up Diboson_up ttV_up 
wjets_stat wjets_syst 
fakes_realEff_stat_D fakes_realEff_stat_U fakes_fakeEff_stat_D fakes_fakeEff_stat_U fakes_fakeEff_MCscale_D fakes_fakeEff_MCscale_U fakes_fakeEff_CR_S"
systs="Fakes_up Zjets_up Diboson_up Stop_up ttV_up"
#systs="`cat resolved_scale_systematics.dat`"

systs=nominal
systs=$allSysts

systs="ttV_up Diboson_up Zjets_up Fakes_up fakes_realEff_stat_D fakes_realEff_stat_U fakes_fakeEff_stat_D fakes_fakeEff_stat_U fakes_fakeEff_MCscale_D fakes_fakeEff_MCscale_U fakes_fakeEff_CR_S"
#systs=$wjetsSysts
systs="Stop_up"
systs="nominal"
systs="ttV_up Diboson_up Zjets_up Fakes_up"
systs="nominal `cat resolved_*syst*.dat`"
systs="`cat resolved_bkg*dat`"
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
                backgroundsamplesNoQCD=\$backgroundsamples
                backgroundsamples="\$backgroundsamples tt_diffxs_13TeV.qcd.Main.AllPeriod.\$c.Resolved.MM.histograms.root"
		signalsample="tt_diffxs_13TeV.mc.DiTop.410000.\$c.$syst.nofullhad.histograms.root"
		#do all background
		hadd -f tt_diffxs_13TeV.mc.AllBkg.\$c.$syst.nofullhad.histograms.root \$backgroundsamples
		hadd -f tt_diffxs_13TeV.mc.AllBkgNoQCD.\$c.$syst.nofullhad.histograms.root \$backgroundsamplesNoQCD
		#do total prediction
		hadd -f tt_diffxs_13TeV.mc.TotalPrediction.\$c.$syst.nofullhad.histograms.root \$signalsample tt_diffxs_13TeV.mc.AllBkg.\$c.$syst.nofullhad.histograms.root
		hadd -f tt_diffxs_13TeV.mc.TotalPredictionNoQCD.\$c.$syst.nofullhad.histograms.root \$signalsample tt_diffxs_13TeV.mc.AllBkgNoQCD.\$c.$syst.nofullhad.histograms.root
done
		#hadd -f AllBkg_co.root AllBkg_el.root AllBkg_mu.root
		
                #hadd -f TotalPrediction_co.root TotalPrediction_el.root TotalPrediction_mu.root
EOF
	chmod +x $script
#	./$script
	bsub -oe -oo $log -J $batchid -q T3_BO_LOCAL $script

done
set +x
