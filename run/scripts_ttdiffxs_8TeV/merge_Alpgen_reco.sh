#!/bin/bash

analysis=tt_diffxs_8TeV
analytag=TTbarResolved_resolved
ILUMI=20300
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
         params=${paramsdir}/DiTop_${gen}_${decay}_${ch}.xml
         outfile=${outdir}/${syst}/${analysis}.mc.${sample}.${gen}.${ch}.${syst}.${decay}.histograms.root

         MAMbo-mergeSamples.py -l ${ILUMI} -c ${params} -o ${outfile}
      done
done

for decay in nofullhad ljets dilep
do
   hadd -f ${outdir}/${syst}/${analysis}.mc.${sample}.${gen}.co.${syst}.${decay}.histograms.root \
           ${outdir}/${syst}/${analysis}.mc.${sample}.${gen}.el.${syst}.${decay}.histograms.root \
           ${outdir}/${syst}/${analysis}.mc.${sample}.${gen}.mu.${syst}.${decay}.histograms.root
done
