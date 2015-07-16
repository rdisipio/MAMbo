#!/bin/bash

analysis=tt_diffxs_8TeV
analytag=TTbarResolved_resolved
ILUMI=20300
#ILUMI=1
sample=DiTop
dsid=$1

if [[ -z $dsid ]] 
then
 echo "Please specify the DSID"
 exit 0
fi

syst=particle

decay=nofullhad
[ ! -z $2 ] && decay=$2

paramsdir=${MAMBODIR}/share/control/merging/${analytag}
outdir=${MAMBODIR}/run/output/${analytag}

for ch in el mu
do  
  params_tmp=${paramsdir}/DiTop_${dsid}_particle_template.xml
  params=${paramsdir}/DiTop_${dsid}_${ch}_particle_${decay}.xml
  cp ${params_tmp} ${params}

  sed -i "s/@CHANNEL@/${ch}/g"  ${params}
  sed -i "s/@DECAY@/${decay}/g" ${params}

  outfile=${outdir}/particle/${analysis}.mc.${sample}.${dsid}.${ch}.particle.${decay}.histograms.root

  MAMbo-mergeSamples.py -l ${ILUMI} -c ${params} -o ${outfile}
done

hadd -f ${outdir}/particle/${analysis}.mc.${sample}.${dsid}.co.particle.${decay}.histograms.root \
        ${outdir}/particle/${analysis}.mc.${sample}.${dsid}.el.particle.${decay}.histograms.root \
        ${outdir}/particle/${analysis}.mc.${sample}.${dsid}.mu.particle.${decay}.histograms.root
