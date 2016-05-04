#!/bin/bash
set -x




analysis=tt_diffxs_13TeV
#outtag=TTbarResolved_resolved

systs="nocut"
systs="nominal `cat resolved_kinematic_systematics.dat resolved_scale_systematics.dat`"
decays="nofullhad ljets"
decays="nofullhad"
production=TTDIFFXS_62
backgrounds="Wjets Zjets Diboson ttV"
channels="el mu"
systs=nominal
for syst in $systs
do
        dir=output/$syst
        for b in $backgrounds
        do
                batchid=hadd.$b.$syst        
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
                        out=\`echo $f | sed s/.runs/_\$c.root/\`
                        hadd -f $dir/\$out \$roots
                done
                out="\`echo $f | sed s/.runs/_co.root/\`"
                roots=""
                for c in $channels
                do
                        roots="\$roots $dir/\`echo $f | sed s/.runs/_\$c.root/\`"
                done
                hadd -f $dir/\$out \$roots
        set +x

EOF
        done
        #single top is special...
        batchid=hadd.Stop.$syst        
        script=../jobs/$batchid.sh   
        
        
        stopProcesses="Wt schan tchan"
        cat > $script << EOF
        #!/bin/bash
        set -x
               
        for c in $channels
        do
                for p in $stopProcesses
                do
                        f=Stop_\${p}.run
                        runs=\`cat \$f\`
                        echo "Runs \$runs"
                        roots=""
                        for r in \$runs
                        do roots="\$roots \`ls $dir/*\$r.\${c}*root\`"
                        done
                        out=\`echo \$f | sed s/.runs/_\$c.root/\`
                        hadd -f $dir/\$out \$roots                        
                done
                out="Stop_\$c.root"
                roots=""
                for p in $stopProcesses
                do
                        f=Stop_\${p}
                        roots="\$roots $dir/\${f}_\${c}.root"
                done
                hadd -f  $dir/\$out \$roots
                hadd -f $dir/Stop_co.root $dir/Stop_el.root $dir/Stop_mu.root 
        done
EOF
        
done
