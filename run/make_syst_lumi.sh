#!/bin/bash

analysis=tt_diffxs_8TeV
analytag=TTbarResolved_resolved

paramsdir=${MAMBODIR}/share/control/merging/${analytag}
outdir=${MAMBODIR}/run/output/${analytag}

sample=DiTop
for ch in el mu
do
  for syst in Lumi_up Lumi_down
  do
     for dsid in 110404 #110340
     do
        params=${paramsdir}/${sample}_${dsid}_${ch}_${syst}.xml

        tag=${analysis}.mc.${sample}.${dsid}.${ch}.${syst}

        MAMbo-mergeSamples.py -c ${params} -o ${outdir}/${syst}/${tag}.histograms.root
     done
  done
done


sample=Background
for ch in el mu
do
  for syst in Lumi_up Lumi_down
  do
     params=${paramsdir}/${sample}_${ch}_${syst}.xml
     tag=${analysis}.mc.${sample}.${ch}.${syst}

     MAMbo-mergeSamples.py -c ${params} -o ${outdir}/${syst}/${tag}.histograms.root
  done
done
