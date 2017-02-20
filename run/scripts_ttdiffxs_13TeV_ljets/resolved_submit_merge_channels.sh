#!/bin/bash
set -x




analysis=tt_diffxs_13TeV
#outtag=TTbarResolved_resolved

systs="nocut"
#wjets_stat wjets_syst"
decays="nofullhad ljets"
decays="nofullhad"
production=TTDIFFXS_62
backgrounds="Wjets Zjets Diboson ttV" #single top is special and needs to be trated separately
backgrounds="ttV Diboson"

skipStop=1
backgrounds="Zjets"
systs="nominal"
systs="`cat resolved_kinematic_systematics.dat resolved_scale_systematics.dat`"

channels="el mu"
#systs="nominal"
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
               
                out="tt_diffxs_13TeV.mc.$b.co.$syst.nofullhad.histograms.root"
                roots=""
                for c in $channels
                do
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
     cat  ./$script
done
