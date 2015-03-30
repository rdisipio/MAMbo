#!/bin/bash

analysis=tt_diffxs_8TeV
analytag=TTbarResolved_resolved
ILUMI=20300
sample=DiTop

systdir=${MAMBODIR}/share/control/analysis_params/${analytag}
paramsdir=${MAMBODIR}/share/control/merging/${analytag}
outdir=${MAMBODIR}/run/output/${analytag}

[[ -d ${paramsdir}/.otf ]] || mkdir -p ${paramsdir}/.otf

dsid=110404
[ ! -z $1 ] && dsid=$1

syst=nominal
[ ! -z $2 ] && syst=$2

for ch in el mu
do
  params_src=${paramsdir}/${sample}_${dsid}_template.xml
  params=${paramsdir}/.otf/${sample}_${dsid}_${ch}.xml
  cp ${params_src} ${params}

  sed -i "s/@CHANNEL@/${ch}/g" ${params}
  sed -i "s/@SYST@/${syst}/g"  ${params}

  MAMbo-mergeSamples.py -l ${ILUMI} -c ${params} -o ${outdir}/${syst}/${analysis}.mc.${sample}.${dsid}.${ch}.${syst}.histograms.root
done
