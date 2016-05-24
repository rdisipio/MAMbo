#!/bin/bash

backgrounds="" #single top is special
channels="el mu co"
set -x
skipStop=0


for c in $channels
do
        for b in $backgrounds
        do
		nominal="output/nominal/tt_diffxs_13TeV.mc.$b.$c.nominal.nofullhad.histograms.root"

                path="output/${b}_up/tt_diffxs_13TeV.mc.$b.$c.${b}_up.nofullhad.histograms.root"
                cp -v $nominal $path
              #cp -v $path.backup $path
               # continue
                batchid="bkgRescaler.$c.$b"
                script="../jobs/$batchid.sh"
                log="../logs/$batchid.log"
                cat > $script << A
               root -b -q 'resolved_BkgRescaler.C("$path", "$b" )'
          
A
                chmod +x $script
               ./$script
           #             bsub -oe -oo $log -J $batchid -q T3_BO_LOCAL $script

        done
	if [ $skipStop != "0" ]
	then
		continue
	fi
        #single top
        stopProcesses="Stop_tchan Stop_Wt Stop_schan"
        batchid="bkgRescaler.$c.Stop"
        script="../jobs/$batchid.sh"
        log="../logs/$batchid.log"

        cat > $script  << A
        #!/bin/bash
        set -x
                roots=""
                for b in $stopProcesses
                do
			nominal="output/nominal/tt_diffxs_13TeV.mc.\$b.$c.nominal.nofullhad.histograms.root"
                        path="output/Stop_up/tt_diffxs_13TeV.mc.\$b.$c.Stop_up.nofullhad.histograms.root"
                        cp -v \$nominal \$path             
			
                        root -b -q "resolved_BkgRescaler.C(\"\$path\", \"\$b\" )"
                        roots="\$roots \$path"
                done  
                hadd -f output/Stop_up/tt_diffxs_13TeV.mc.Stop.$c.Stop_up.nofullhad.histograms.root \$roots
               
A
    
          
                chmod +x $script
                echo ./$script
             
                 ./$script
   #                    bsub -oe -oo $log -J $batchid -q T3_BO_LOCAL $script

        
done


