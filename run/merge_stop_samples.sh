#!/bin/bash

analysis=tt_diffxs_8TeV
analytag=TTbarResolved_resolved

paramsdir=${MAMBODIR}/share/control/merging/${analytag}
outdir=${MAMBODIR}/run/output/${analytag}
syst=nominal
ILUMI=20300 

for syst in st_xsec_up st_xsec_down
do
   for ch in el mu
   do
       params=${paramsdir}/SingleTop_${ch}.${syst}.xml
       MAMbo-mergeSamples.py -l ${ILUMI} -c ${params} -o ${outdir}/${syst}/${analysis}.mc.SingleTop.${ch}.${syst}.histograms.root &
   done
   wait
done

echo
echo //////////////////////////////////////
echo

hadd -f ${outdir}/${syst}/${analysis}.mc.SingleTop.co.${syst}.histograms.root \
        ${outdir}/${syst}/${analysis}.mc.SingleTop.el.${syst}.histograms.root \
        ${outdir}/${syst}/${analysis}.mc.SingleTop.mu.${syst}.histograms.root
  
