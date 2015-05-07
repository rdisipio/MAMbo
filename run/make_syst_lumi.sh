#!/bin/bash

analysis=tt_diffxs_8TeV
analytag=TTbarResolved_resolved

paramsdir=${MAMBODIR}/share/control/merging/${analytag}
outdir=${MAMBODIR}/run/output/${analytag}

sample=DiTop
for syst in Lumi_up Lumi_down
do
  for dsid in 110404 #110340
  do
    for ch in el mu
    do

        params=${paramsdir}/${sample}_${dsid}_${ch}_${syst}.xml

        tag=${analysis}.mc.${sample}.${dsid}.${ch}.${syst}

        MAMbo-mergeSamples.py -l 1.0 -c ${params} -o ${outdir}/${syst}/${tag}.histograms.root &
     done #channel
     wait

     echo
     echo ///////////////////////////////////
     echo

     hadd -f ${outdir}/${syst}/${analysis}.mc.${sample}.${dsid}.co.${syst}.histograms.root \
             ${outdir}/${syst}/${analysis}.mc.${sample}.${dsid}.el.${syst}.histograms.root \
             ${outdir}/${syst}/${analysis}.mc.${sample}.${dsid}.mu.${syst}.histograms.root

     echo
     echo ///////////////////////////////////
     echo

  done #dsid
done #syst
