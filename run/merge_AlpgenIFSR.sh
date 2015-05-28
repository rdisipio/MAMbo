#!/bin/bash

analysis=tt_diffxs_8TeV
analytag=TTbarResolved_resolved
ILUMI=20300
sample=DiTop
decay=ljets

paramsdir=${MAMBODIR}/share/control/merging/${analytag}
outdir=${MAMBODIR}/run/output/${analytag}

for ch in el mu
do
   for syst in radHi radLo
   do
      for decay in ljets dilep nofullhad
      do
         params=${paramsdir}/DiTop_AlpgenIFSR_${syst}_${decay}_${ch}.xml
         outfile=${outdir}/${syst}/${analysis}.mc.${sample}.AlpgenIFSR.${decay}.${ch}.${syst}.histograms.root

         MAMbo-mergeSamples.py -l ${ILUMI} -c ${params} -o ${outfile}
      done
   done
done
