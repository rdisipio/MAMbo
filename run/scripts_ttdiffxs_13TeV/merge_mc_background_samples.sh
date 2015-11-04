#!/bin/bash

analysis=13TeV_ljets_resolved

paramsdir=${MAMBODIR}/share/control/analysis_params/${analysis}/merging
outdir=${MAMBODIR}/run/output/${analysis}

syst=nominal
ILUMI=1700.

for sample in DiTop_410000 SingleTop Wjets
do
   for ch in el #mu
   do
       params=${paramsdir}/${sample}_${ch}.xml
       MAMbo-mergeSamples.py -l ${ILUMI} -c ${params} -o ${outdir}/${syst}/mc15_13TeV_25ns.DAOD_TOPQ1.${analysis}.${sample}.${ch}.${syst}.histograms.root
   done

  echo
  echo //////////////////////////////////////
  echo

#  hadd -f ${outdir}/${syst}/${analysis}.mc.${sample}.co.${syst}.histograms.root \
#        ${outdir}/${syst}/${analysis}.mc.${sample}.el.${syst}.histograms.root \
#        ${outdir}/${syst}/${analysis}.mc.${sample}.mu.${syst}.histograms.root

done # sample
