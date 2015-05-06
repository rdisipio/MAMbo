#!/bin/bash

analysis=TTbarResolved_resolved
analytag=tt_diffxs_8TeV

#ILUMI=20300
ILUMI=1.0
dsid=110404

syst=nominal
[ ! -z $1 ] && syst=$1

ch=co
[ ! -z $2 ] && ch=$2

outdir=$MAMBODIR/run/output/${analysis}

params=$MAMBODIR/share/control/merging/${analysis}/Unfolding_${dsid}_template.xml
newparams=$MAMBODIR/share/control/merging/${analysis}/.otf/Unfolding_${dsid}_${ch}_${syst}.xml

cp $params $newparams

sed -i "s/@CHANNEL@/${ch}/g" $newparams
sed -i "s/@SYST@/${syst}/g"  $newparams

MAMbo-mergeSamples.py -l ${ILUMI} -c ${newparams} -o ${outdir}/${syst}/${analytag}.mc.DiTop.${dsid}.${ch}.${syst}.histograms.root

