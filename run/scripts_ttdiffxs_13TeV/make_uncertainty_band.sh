#!/bin/bash

analysis=13TeV_ljets_resolved

paramsdir=${MAMBODIR}/share/control/analysis_params/${analysis}/merging
outdir=${MAMBODIR}/run/output/${analysis}

dsid=410000
[ ! -z $1 ] && dsid=$1

ch=el
[ ! -z $2 ] && ch=$2

syst=nominal
[ ! -z $3 ] && syst=$3


for unc in statonly #statsyst
do
   tag=mc15_13TeV_25ns.DAOD_TOPQ1.${analysis}.Uncertainty_statonly.${dsid}.${ch}.${syst}

   MAMbo-makeUncertaintyBand.py -c ${paramsdir}/Uncertainty_${dsid}_${ch}_statonly.xml \
                                -o ${outdir}/${syst}/${tag}.histograms.root            \
                                -x ${outdir}/${syst}/${tag}.histograms.xml

done
