#!/bin/bash

analysis=tt_diffxs_8TeV
analytag=TTbarResolved_resolved
ILUMI=20300
#ILUMI=1
sample=DiTop
syst=nominal
decay=nofullhad

gen=pythia
[ ! -z $1 ] && gen=$1

[[ $gen == "pythia" ]] && gen=AlpgenPythia
[[ $gen == "herwig" ]] && gen=AlpgenHerwig


paramsdir=${MAMBODIR}/share/control/merging/${analytag}
outdir=${MAMBODIR}/run/output/${analytag}

for ch in el mu
do
      for decay in nofullhad ljets dilep 
      do
         params=${paramsdir}/DiTop_${gen}_${decay}_${ch}_particle.xml
         outfile=${outdir}/particle/${analysis}.mc.${sample}.${gen}.${ch}.particle.${decay}.histograms.root

         MAMbo-mergeSamples.py -l ${ILUMI} -c ${params} -o ${outfile} &
      done
      wait
done

for decay in nofullhad ljets dilep
do
   hadd -f ${outdir}/particle/${analysis}.mc.${sample}.${gen}.co.particle.${decay}.histograms.root \
           ${outdir}/particle/${analysis}.mc.${sample}.${gen}.el.particle.${decay}.histograms.root \
           ${outdir}/particle/${analysis}.mc.${sample}.${gen}.mu.particle.${decay}.histograms.root
done
