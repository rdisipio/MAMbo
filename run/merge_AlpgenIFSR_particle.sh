#!/bin/bash

analysis=tt_diffxs_8TeV
analytag=TTbarResolved_resolved
#ILUMI=20300
ILUMI=1
sample=DiTop
syst=nominal
gen=AlpgenIFSR
decay=nofullhad

paramsdir=${MAMBODIR}/share/control/merging/${analytag}
outdir=${MAMBODIR}/run/output/${analytag}

for syst in radHi radLo
do
   for ch in el mu
   do
      for decay in nofullhad ljets dilep 
      do
         params=${paramsdir}/DiTop_AlpgenIFSR_${syst}_${decay}_${ch}_particle.xml
         outfile=${outdir}/particle/${analysis}.mc.${sample}.${gen}.${decay}.${ch}.${syst}.particle.histograms.root

         MAMbo-mergeSamples.py -l ${ILUMI} -c ${params} -o ${outfile} &
      done
      wait
   done

   for decay in nofullhad ljets dilep
   do
      hadd -f ${outdir}/particle/${analysis}.mc.${sample}.${gen}.${decay}.co.${syst}.particle.histograms.root \
              ${outdir}/particle/${analysis}.mc.${sample}.${gen}.${decay}.el.${syst}.particle.histograms.root \
              ${outdir}/particle/${analysis}.mc.${sample}.${gen}.${decay}.mu.${syst}.particle.histograms.root &
   done
   wait
done
