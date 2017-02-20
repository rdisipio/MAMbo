#!/bin/bash

backgrounds="" #single top is special
channels="el mu co"
set -x
skipStop=
systs="nominal nocut"
stresses="tt_pt tt_rapidity tt_m t_pt"
 g++ `root-config --cflags --libs` resolved_StressTestRescaler.C  -Wall -o resolved_StressTestRescaler

 
for syst in $systs
do
        for stress in $stresses
        do       
                for c in $channels
                do
                
                                nominal_nocut="output/nocut/tt_diffxs_13TeV.mc.DiTop.410000.$c.nocut.nofullhad.histograms.root"
                                stress_nocut="output/$stress/nocut/tt_diffxs_13TeV.mc.DiTop.410000.$c.nocut.nofullhad.histograms.root"
                                path="output/$stress/$syst/tt_diffxs_13TeV.mc.DiTop.410000.$c.$syst.nofullhad.histograms.root"
                                                # £cp -v $nominal $path
                                          #cp -v $path $path.backup
                                           # continue
                                                batchid="resolved_StressTestRescaler.$c.$syst"
                                                script="../jobs/$batchid.sh"
                                                log="../logs/$batchid.log"
                                                cat > $script << EOF 
                                           # root -b -q 'resolved_StressTestRescaler.C("$path", "$stress_nocut", "$nominal_nocut", "$syst" )'
                                           ./resolved_StressTestRescaler $path $stress_nocut $nominal_nocut $syst
                                  
EOF
                                                chmod +x $script
                                                echo $script
        				   ./$script
        #                                       bsub -oe -oo $log -J $batchid -q T3_BO_LOCAL $script

                        

                                
                done
        done

done
