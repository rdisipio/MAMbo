#!/bin/bash

analysis=tt_diffxs_8TeV
analytag=TTbarResolved_resolved

paramsdir=${MAMBODIR}/share/control/merging/${analytag}
outdir=${MAMBODIR}/run/output/${analytag}
syst=nominal
ILUMI=20300 

ch=$1
[[ ! -z $2 ]] && syst=$2


for flav in lf c bbcc
do
   MAMbo-mergeSamples.py -l ${ILUMI} -c ${paramsdir}/Wjets_${flav}_${ch}.tt_chasymm.xml -o ${outdir}/${syst}/${analysis}.mc.Wjets_${flav}.${ch}.${syst}.histograms.root
done

ofile=${outdir}/${syst}/${analysis}.mc.Wjets.${ch}.${syst}.histograms.root
hadd -f ${ofile} \
        ${outdir}/${syst}/${analysis}.mc.Wjets_lf.${ch}.${syst}.histograms.root \
        ${outdir}/${syst}/${analysis}.mc.Wjets_c.${ch}.${syst}.histograms.root \
        ${outdir}/${syst}/${analysis}.mc.Wjets_bbcc.${ch}.${syst}.histograms.root
