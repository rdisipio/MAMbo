#!/bin/bash
set -x




analysis=tt_diffxs_13TeV
#outtag=TTbarResolved_resolved
wjetsSysts="CA_up CA_down Fcc_up Fcc_down Flight_up Flight_down"

systs="nocut"
#wjets_stat wjets_syst"
decays="nofullhad ljets"
decays="nofullhad"
production=TTDIFFXS_62
backgrounds="Wjets Zjets Diboson ttV" #single top is special and needs to be trated separately
backgrounds="ttV Diboson"
systs="`cat resolved_kinematic_systematics.dat resolved_scale_systematics.dat`"

skipStop=1
backgrounds="Wjets"
systs="wjets_stat wjets_syst"
channels="el mu"
systs="nominal"
systs="nominal $wjetsSysts $(cat resolved_*_systematics.dat )"
systs=$wjetsSysts
systs="nominal $wjetsSysts $(cat resolved_*_systematics.dat )"
systs="ttV_up Diboson_up Stop_up Zjets_up Fakes_up fakes_realEff_stat_D fakes_realEff_stat_U fakes_fakeEff_stat_D fakes_fakeEff_stat_U fakes_fakeEff_MCscale_D fakes_fakeEff_MCscale_U fakes_fakeEff_CR_S"
systs="Stop_up"
systs="ttV_up Diboson_up Stop_up Zjets_up Fakes_up"
systs="$(cat resolved_*_systematics.dat )"

systs="$(cat resolved_bkg_systematics.dat )"
systs="nominal $(cat resolved_kin*systematics.dat resolved_scal*systematics.dat)"
systs="Fakes_up"
channels="el mu"
for syst in $systs
do
        dir=output/$syst
        for b in $backgrounds
        do
                batchid=hadd.$b.$syst      
                log=../logs/$batchid.log  
		script=../jobs/$batchid.sh
                f=$b.run
                cat > $script << EOF
                #!/bin/bash
                set -x
               
                for c in $channels
                do
                        runs=\`cat $f\`
                        echo "Runs \$runs"
                        roots=""
                        for r in \$runs
                        do roots="\$roots \`ls $dir/*\$r.\${c}*root\`"
                        done
                        out="tt_diffxs_13TeV.mc.$b.\$c.$syst.nofullhad.histograms.root"
                        hadd -f $dir/\$out \$roots
                done
                out="tt_diffxs_13TeV.mc.$b.co.$syst.nofullhad.histograms.root"
                roots=""
                for c in $channels
                do
                        # roots="\$roots $dir/\`echo $f | sed s/.runs/_\$c.root/\`"
                        roots="\$roots $dir/tt_diffxs_13TeV.mc.$b.\$c.$syst.nofullhad.histograms.root"
                done
                hadd -f $dir/\$out \$roots
        set +x

EOF
                chmod +x $script
                bsub -oe -oo $log -J $batchid -q T3_BO_LOCAL $script
        done
	if [ $skipStop != "0" ]
	then
		continue
	fi
        #single top is special...
        batchid=hadd.Stop.$syst        
        script=../jobs/$batchid.sh   
        log=../logs/$batchid.log
        
        stopProcesses="Wt schan tchan"
        cat > $script << EOF
        #!/bin/bash
        set -x
               
        for c in $channels
        do
                for p in $stopProcesses
                do
                        b=Stop_\$p
                        f=Stop_\${p}.run
                        runs=\`cat \$f\`
                        echo "Runs \$runs"
                        roots=""
                        for r in \$runs
                        do 
                                roots="\$roots \`ls $dir/*\$r.\${c}*root\`"
                        done
                        out="tt_diffxs_13TeV.mc.\$b.\$c.$syst.nofullhad.histograms.root"
                        hadd -f $dir/\$out \$roots                        
                done
                out="tt_diffxs_13TeV.mc.Stop.\$c.$syst.nofullhad.histograms.root"
                roots=""
                for p in $stopProcesses
                do
                        b=Stop_\${p}
                        
                        roots="\$roots $dir/tt_diffxs_13TeV.mc.\$b.\$c.$syst.nofullhad.histograms.root"
                done
                hadd -f  $dir/\$out \$roots
        done
          out="tt_diffxs_13TeV.mc.Stop.co.$syst.nofullhad.histograms.root"
        roots=""

        for p in $stopProcesses
        do
                b=Stop_\${p}
                hadd -f $dir/tt_diffxs_13TeV.mc.\$b.co.$syst.nofullhad.histograms.root $dir/tt_diffxs_13TeV.mc.\$b.el.$syst.nofullhad.histograms.root $dir/tt_diffxs_13TeV.mc.\$b.mu.$syst.nofullhad.histograms.root
                roots="\$roots $dir/tt_diffxs_13TeV.mc.\$b.co.$syst.nofullhad.histograms.root"
        done        
        hadd -f $dir/tt_diffxs_13TeV.mc.Stop.co.$syst.nofullhad.histograms.root $dir/tt_diffxs_13TeV.mc.Stop.el.$syst.nofullhad.histograms.root  $dir/tt_diffxs_13TeV.mc.Stop.mu.$syst.nofullhad.histograms.root 
EOF
        chmod +x $script
      #  bsub -oe -oo $log -J $batchid -q T3_BO_LOCAL $script
      ./$script
done
