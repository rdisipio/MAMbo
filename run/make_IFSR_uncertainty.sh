#!/bin/bash

analysis=tt_diffxs_8TeV
analytag=TTbarResolved_resolved

dsid=110404
[ ! -z $1 ] && dsid=$1

outdir=${MAMBOOUTPUTDIR}

for ch in el mu
do
   MAMbo-makeIFSRUncertainty.py -c control/merging/${analytag}/Uncertainty_${dsid}_${ch}_IFSR.xml \
                 -o ${outdir}/radHi/${analysis}.mc.DiTop.${dsid}.${ch}.radHi.histograms.root,${outdir}/radLo/${analysis}.mc.DiTop.${dsid}.${ch}.radLo.histograms.root  
done
