#!/bin/bash

analysis=tt_diffxs_8TeV
analytag=TTbarResolved_resolved
ILUMI=20300
sample=DiTop
syst=nominal
gen=AlpgenPythia
decay=nofullhad

paramsdir=${MAMBODIR}/share/control/merging/${analytag}
outdir=${MAMBODIR}/run/output/${analytag}

for ch in el mu
do
      for decay in nofullhad #ljets dilep 
      do
         params=${paramsdir}/DiTop_${gen}_${decay}_${ch}.xml
         outfile=${outdir}/${syst}/${analysis}.mc.${sample}.${gen}.${decay}.${ch}.${syst}.histograms.root

         MAMbo-mergeSamples.py -l ${ILUMI} -c ${params} -o ${outfile}
      done
done

hadd -f ${outdir}/${syst}/${analysis}.mc.${sample}.${gen}.${decay}.co.${syst}.histograms.root \
        ${outdir}/${syst}/${analysis}.mc.${sample}.${gen}.${decay}.el.${syst}.histograms.root \
        ${outdir}/${syst}/${analysis}.mc.${sample}.${gen}.${decay}.mu.${syst}.histograms.root

#ln -s ${outdir}/${syst}/${analysis}.mc.${sample}.${gen}.${decay}.co.${syst}.histograms.root \
#      ${outdir}/generator/${analysis}.mc.${sample}.110404.co.generator.histograms.root
