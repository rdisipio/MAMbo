#!/bin/bash
#README: Launch the script in the main directory of the new production, possibly after the merge of all bkg.
systs="CA_2ex_up CA_2ex_down CA_3ex_up CA_3ex_down CA_4incl_up CA_4incl_down Fc_up Fc_down"
#systs="CA_up CA_down Fcc_up Fcc_down Flight_up Flight_down QCDNorm_up_30 QCDNorm_down_30"
#systs="QCDNorm_up_30 QCDNorm_down_30"
directory=$PWD
for channel in el mu co
do
name=tt_diffxs_13TeV.QCD.AllPeriod.${channel}.Boosted.MM.nominal.histograms.root 
 for sys in ${systs[@]}
 do
  cd $sys
  name1=${name/nominal/$sys}
  echo $name1
  ln -snf ${directory}/nominal/$name $name1
  for bkg in Diboson ttV Zjets Stop
  do
   ln -snf ${directory}/nominal/tt_diffxs_13TeV.mc.${bkg}.${channel}.nominal.histograms.root tt_diffxs_13TeV.mc.${bkg}.${channel}.${sys}.histograms.root
  done
   ln -snf ${directory}/nominal/tt_diffxs_13TeV.mc.DiTop.410000.${channel}.nominal.histograms.root tt_diffxs_13TeV.mc.DiTop.410000.${channel}.${sys}.histograms.root
  cd -
 done
done
