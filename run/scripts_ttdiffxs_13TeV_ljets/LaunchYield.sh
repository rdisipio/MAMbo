#!/bin/bash

#for sample in "410000" "Wjets" "Zjets" "Diboson" "Stop" "QCD" "ttV" 
for sample in "TotalPrediction" 
do
   for channel in "el" "mu" "co" 
   do
      ../../bin/MAMbo-makeUncertaintyBand.py -c ../control/analysis_params/13TeV_ljets_boosted/Uncertainty_${sample}_${channel}_statsyst.xml -x ${sample}.${channel}.uncertainty.xml -o ${sample}.${channel}.uncertainty.histograms.root

     echo $channel
     ../../bin/MakeYields_fromxml.py -i ${sample}.${channel}.uncertainty.xml -s ${sample}
   done
done 
