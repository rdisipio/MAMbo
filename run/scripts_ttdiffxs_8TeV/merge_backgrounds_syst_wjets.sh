#!/bin/bash

analysis=tt_diffxs_8TeV

syst=nominal
[ ! -z $1 ] && syst=$1

tag_wjets=tt_chasymm
[ ! -z $2 ] && wjets=$2

[[ ! -d ${MAMBOOUTPUTDIR}/${syst} ]] && mkdir -p ${MAMBOOUTPUTDIR}/${syst}

for ch in el mu
do
  [ $ch == "el" ] && stream="Egamma"
  [ $ch == "mu" ] && stream="Muons"

  hadd -f ${MAMBOOUTPUTDIR}/${syst}/${analysis}.mc.Background.${ch}.${syst}.histograms.root \
          ${MAMBOOUTPUTDIR}/${syst}/${analysis}.mc.Wjets.${ch}.${tag_wjets}.${syst}.histograms.root \
          ${MAMBOOUTPUTDIR}/nominal/${analysis}.mc.SingleTop.${ch}.nominal.histograms.root \
          ${MAMBOOUTPUTDIR}/nominal/${analysis}.mc.Zjets.${ch}.nominal.histograms.root \
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
