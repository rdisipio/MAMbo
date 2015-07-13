#!/bin/bash

analysis=tt_diffxs_8TeV
analytag=TTbarResolved_resolved

paramsdir=${MAMBODIR}/share/control/merging/${analytag}
outdir=${MAMBODIR}/run/output/${analytag}
syst=nominal
ILUMI=20300

#ch=$1
[[ ! -z $1 ]] && syst=$1

tag=Wjets_Sherpa

for ch in el mu
do

  MAMbo-mergeSamples.py -l ${ILUMI} -c ${paramsdir}/${tag}_${ch}.xml \
      -o ${outdir}/${syst}/${analysis}.mc.${tag}.${ch}.${syst}.histograms.root

  echo
  echo //////////////////////////////
  echo
done

echo

hadd -f ${outdir}/${syst}/${analysis}.mc.${tag}.co.${syst}.histograms.root \
        ${outdir}/${syst}/${analysis}.mc.${tag}.el.${syst}.histograms.root \
        ${outdir}/${syst}/${analysis}.mc.${tag}.mu.${syst}.histograms.root
