#!/bin/bash
set -x

analysis=tt_diffxs_13TeV
systs="wjets_stat wjets_syst" #running alone with only wjets bkg
#systs="`cat boosted_reduced_systematics.txt`"
#systs="nominal `cat boosted_reduced_systematics.txt`"

#backgrounds="Wjets Zjets Diboson ttV" #Stop is special and treated separately
backgrounds="Wjets" 
channels="el mu"

skipStop=1

for syst in $systs
do 
    if [[ ${syst} == "nominal" ]]; then
	dir=${MAMBODIR}/run/output/BackGroundMC_TTDIFFXS_62/${syst}	
    else
	dir=${MAMBODIR}/run/output/BackGroundMC_TTDIFFXS_62/syst/$syst
    fi
    
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
                        out="tt_diffxs_13TeV.mc.$b.\$c.$syst.histograms.root"
                        hadd -f $dir/\$out \$roots
                done
                out="tt_diffxs_13TeV.mc.$b.co.$syst.histograms.root"
                roots=""

                hadd -f $dir/\$out $dir/tt_diffxs_13TeV.mc.$b.mu.$syst.histograms.root $dir/tt_diffxs_13TeV.mc.$b.el.$syst.histograms.root

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
                        out="tt_diffxs_13TeV.mc.\$b.\$c.$syst.histograms.root"
                        hadd -f $dir/\$out \$roots                        
                done
                out="tt_diffxs_13TeV.mc.Stop.\$c.$syst.histograms.root"
                roots=""
                for p in $stopProcesses
                do
                        b=Stop_\${p}
                        
                        roots="\$roots $dir/tt_diffxs_13TeV.mc.\$b.\$c.$syst.histograms.root"
                done
                hadd -f  $dir/\$out \$roots
        done
          out="tt_diffxs_13TeV.mc.Stop.co.$syst.histograms.root"
        roots=""

        for p in $stopProcesses
        do
                b=Stop_\${p}
                hadd -f $dir/tt_diffxs_13TeV.mc.\$b.co.$syst.histograms.root $dir/tt_diffxs_13TeV.mc.\$b.el.$syst.histograms.root $dir/tt_diffxs_13TeV.mc.\$b.mu.$syst.histograms.root
                roots="\$roots $dir/tt_diffxs_13TeV.mc.\$b.co.$syst.histograms.root"
        done        
        hadd -f $dir/tt_diffxs_13TeV.mc.Stop.co.$syst.histograms.root $dir/tt_diffxs_13TeV.mc.Stop.el.$syst.histograms.root  $dir/tt_diffxs_13TeV.mc.Stop.mu.$syst.histograms.root 
EOF
        chmod +x $script
        bsub -oe -oo $log -J $batchid -q T3_BO_LOCAL $script
done
