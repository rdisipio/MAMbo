#!/bin/bash

analysis=tt_diffxs_8TeV
analytag=TTbarResolved_resolved

paramsdir=${MAMBODIR}/share/control/merging/${analytag}
outdir=${MAMBODIR}/run/output/${analytag}

dsid=110404

for ch in el mu
do
    MAMbo-makeIFSRUncertainty.py -c ${paramsdir}/Uncertainty_${dsid}_${ch}_IFSR.xml \
            -o ${outdir}/radHi/${analysis}.mc.DiTop.${dsid}.${ch}.radHi.histograms.root,${outdir}/radLo/${analysis}.mc.DiTop.${dsid}.${ch}.radLo.histograms.root 
done

echo 
echo /////////////////////////////////////////////
echo

for syst in radHi radLo
do
   hadd -f ${outdir}/${syst}/${analysis}.mc.DiTop.${dsid}.co.${syst}.histograms.root \
           ${outdir}/${syst}/${analysis}.mc.DiTop.${dsid}.el.${syst}.histograms.root \
           ${outdir}/${syst}/${analysis}.mc.DiTop.${dsid}.mu.${syst}.histograms.root &
done

wait
