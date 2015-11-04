#!/bin/bash

analysis=tt_diffxs_8TeV

tag_wjets=tt_chasymm
[ ! -z $1 ] && wjets=$1


for syst in zjets_xsec_up zjets_xsec_down
do


for ch in el mu
do
  [ $ch == "el" ] && stream="Egamma"
  [ $ch == "mu" ] && stream="Muons"

  hadd -f ${MAMBOOUTPUTDIR}/${syst}/${analysis}.mc.Background.${ch}.${syst}.histograms.root \
          ${MAMBOOUTPUTDIR}/nominal/${analysis}.mc.Wjets.${ch}.${tag_wjets}.nominal.histograms.root \
          ${MAMBOOUTPUTDIR}/nominal/${analysis}.mc.SingleTop.${ch}.nominal.histograms.root \
          ${MAMBOOUTPUTDIR}/${syst}/${analysis}.mc.Zjets.${ch}.${syst}.histograms.root \
          ${MAMBOOUTPUTDIR}/nominal/${analysis}.mc.Diboson.${ch}.nominal.histograms.root \
          ${MAMBOOUTPUTDIR}/nominal/${analysis}.qcd.${stream}.${ch}.nominal.histograms.root &
done
wait

echo
echo /////////////////////////////
echo

hadd -f ${MAMBOOUTPUTDIR}/${syst}/${analysis}.mc.Background.co.${syst}.histograms.root \
        ${MAMBOOUTPUTDIR}/${syst}/${analysis}.mc.Background.el.${syst}.histograms.root \
        ${MAMBOOUTPUTDIR}/${syst}/${analysis}.mc.Background.mu.${syst}.histograms.root 

done
