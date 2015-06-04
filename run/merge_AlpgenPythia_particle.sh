#!/bin/bash

analysis=tt_diffxs_8TeV
analytag=TTbarResolved_resolved
#ILUMI=20300
ILUMI=1
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
         params=${paramsdir}/DiTop_${gen}_${decay}_${ch}_particle.xml
         outfile=${outdir}/particle/${analysis}.mc.${sample}.${gen}.${decay}.${ch}.nominal.particle.histograms.root

         MAMbo-mergeSamples.py -l ${ILUMI} -c ${params} -o ${outfile}
      done
   done

   hadd -f ${outdir}/particle/histograms_AlpgenPythia_ll_particle.root \
           ${outdir}/particle/${analysis}.mc.${sample}.${gen}.${decay}.el.nominal.particle.histograms.root \
           ${outdir}/particle/${analysis}.mc.${sample}.${gen}.${decay}.mu.nominal.particle.histograms.root
