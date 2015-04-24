#!/bin/bash

analysis=tt_diffxs_8TeV

syst=nominal
[ ! -z $1 ] && syst=$1

wjets=Sherpa
[ ! -z $2 ] && wjets=$2

for ch in el mu
do
  [ $ch == "el" ] && stream="Egamma"
  [ $ch == "mu" ] && stream="Muons"

  hadd -f ${MAMBOOUTPUTDIR}/${syst}/${analysis}.mc.Background.${ch}.${syst}.histograms.root \
          ${MAMBOOUTPUTDIR}/${syst}/${analysis}.mc.Wjets.${wjets}.${ch}.${syst}.histograms.root \
          ${MAMBOOUTPUTDIR}/${syst}/${analysis}.mc.SingleTop.${ch}.${syst}.histograms.root \
          ${MAMBOOUTPUTDIR}/${syst}/${analysis}.mc.Zjets.${ch}.${syst}.histograms.root \
          ${MAMBOOUTPUTDIR}/${syst}/${analysis}.mc.Diboson.${ch}.${syst}.histograms.root \
          ${MAMBOOUTPUTDIR}/${syst}/${analysis}.qcd.${stream}.${ch}.${syst}.histograms.root 
done

hadd -f ${MAMBOOUTPUTDIR}/${syst}/${analysis}.mc.Background.co.${syst}.histograms.root \
        ${MAMBOOUTPUTDIR}/${syst}/${analysis}.mc.Background.el.${syst}.histograms.root \
        ${MAMBOOUTPUTDIR}/${syst}/${analysis}.mc.Background.mu.${syst}.histograms.root 
