#!/bin/bash

analysis=tt_diffxs_8TeV
analytag=TTbarResolved_resolved

paramsdir=${MAMBODIR}/share/control/merging/${analytag}
outdir=${MAMBODIR}/run/output/${analytag}
syst=nominal
ILUMI=1

for sample in Zjets Diboson
do
  for syst in xsec_up xsec_down
  do
     [ $sample == "SingleTop" ] && syst="st_$syst"
     [ $sample == "Zjets"     ] && syst="zjets_$syst"
     [ $sample == "Diboson"   ] && syst="diboson_$syst"

     for ch in el mu
     do
       params=${paramsdir}/${sample}_${ch}.${syst}.xml
       MAMbo-mergeSamples.py -l ${ILUMI} -c ${params} -o ${outdir}/${syst}/${analysis}.mc.${sample}.${ch}.${syst}.histograms.root &
     done
     wait

  echo
  echo //////////////////////////////////////
  echo

  hadd -f ${outdir}/${syst}/${analysis}.mc.${sample}.co.${syst}.histograms.root \
        ${outdir}/${syst}/${analysis}.mc.${sample}.el.${syst}.histograms.root \
        ${outdir}/${syst}/${analysis}.mc.${sample}.mu.${syst}.histograms.root

  done # up or down

done # sample
