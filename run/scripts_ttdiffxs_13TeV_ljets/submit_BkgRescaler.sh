#!/bin/bash

backgrounds="Diboson Zjets ttV Stop" #single top is special
channels="el mu co"
production=TTDIFFXS_62_v20
set -x
skipStop=0


for c in $channels
do
        for b in $backgrounds
        do
		nominal="output/${production}/nominal/tt_diffxs_13TeV.mc.$b.$c.nominal.histograms.root"

                path="output/${production}/${b}_up/tt_diffxs_13TeV.mc.$b.$c.${b}_up.histograms.root"


                for link in $backgrounds
                do
                  if [[ $link == $b ]]; then 
                     continue;
                  fi
                  ln -sfn ${MAMBODIR}/run/output/${production}/nominal/tt_diffxs_13TeV.mc.$link.$c.nominal.histograms.root ${MAMBODIR}/run/output/${production}/${b}_up/tt_diffxs_13TeV.mc.$link.$c.${b}_up.histograms.root
                done
                  if [[ $b == "Stop" ]]; then
                     continue;
                  fi
                
                cp $nominal $path
              #cp -v $path.backup $path
               # continue
                batchid="bkgRescaler.$c.$b"
                script="../jobs/$batchid.sh"
                log="../logs/$batchid.log"
                cat > $script << A
               root -b -q 'boosted_BkgRescaler.C("$path", "$b" )'
          
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
			nominal="output/${production}/nominal/tt_diffxs_13TeV.mc.\$b.$c.nominal.histograms.root"
                        path="output/${production}/Stop_up/tt_diffxs_13TeV.mc.\$b.$c.Stop_up.histograms.root"
                        cp -v \$nominal \$path             
			
                        root -b -q "boosted_BkgRescaler.C(\"\$path\", \"\$b\" )"
                        roots="\$roots \$path"
                done  
                hadd -f output/${production}/Stop_up/tt_diffxs_13TeV.mc.Stop.$c.Stop_up.histograms.root \$roots
               
A
    
          
                chmod +x $script
                echo ./$script
             
                 ./$script
   #                    bsub -oe -oo $log -J $batchid -q T3_BO_LOCAL $script

        
done


