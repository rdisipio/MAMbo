#!/bin/bash

analysis=TTbarResolved_resolved
analytag=tt_diffxs_8TeV
tag_wjets=tt_chasymm
systfile=${MAMBODIR}/share/control/analysis_params/${analysis}/qcd_systematics.dat

for syst in $(cat ${systfile} )
do

for ch in el mu
do
  [ $ch == "el" ] && stream="Egamma"
  [ $ch == "mu" ] && stream="Muons"

  hadd -f ${MAMBOOUTPUTDIR}/${syst}/${analytag}.mc.Background.${ch}.${syst}.histograms.root \
          ${MAMBOOUTPUTDIR}/nominal/${analytag}.mc.Wjets.${ch}.${tag_wjets}.nominal.histograms.root \
          ${MAMBOOUTPUTDIR}/nominal/${analytag}.mc.SingleTop.${ch}.nominal.histograms.root \
          ${MAMBOOUTPUTDIR}/nominal/${analytag}.mc.Zjets.${ch}.nominal.histograms.root \
          ${MAMBOOUTPUTDIR}/nominal/${analytag}.mc.Diboson.${ch}.nominal.histograms.root \
          ${MAMBOOUTPUTDIR}/${syst}/${analytag}.qcd.${stream}.${ch}.${syst}.histograms.root &
done
wait

hadd -f ${MAMBOOUTPUTDIR}/${syst}/${analytag}.mc.Background.co.${syst}.histograms.root \
        ${MAMBOOUTPUTDIR}/${syst}/${analytag}.mc.Background.el.${syst}.histograms.root \
        ${MAMBOOUTPUTDIR}/${syst}/${analytag}.mc.Background.mu.${syst}.histograms.root 

done
