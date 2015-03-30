#!/bin/bash

analysis=tt_diffxs_8TeV
analytag=TTbarResolved_resolved

paramsdir=${MAMBODIR}/share/control/merging/${analytag}
outdir=${MAMBODIR}/run/output/${analytag}

dsid=110404
[ ! -z $1 ] && dsid=$1

ch=el
[ ! -z $2 ] && ch=$2

syst=nominal
[ ! -z $3 ] && syst=$3


# stat only
MAMbo-makeUncertaintyBand.py -c ${paramsdir}/Uncertainty_${dsid}_${ch}_statonly.xml \
                             -o ${outdir}/${syst}/${analysis}.mc.Uncertainty_statonly.${dsid}.${ch}.${syst}.histograms.root \
    			     -x ${outdir}/${syst}/${analysis}.mc.Uncertainty_statonly.${dsid}.${ch}.${syst}.xml

# stat + syst
MAMbo-makeUncertaintyBand.py -c ${paramsdir}/Uncertainty_${dsid}_${ch}_statsyst.xml \
                             -o ${outdir}/${syst}/${analysis}.mc.Uncertainty_statsyst.${dsid}.${ch}.${syst}.histograms.root \
                             -x ${outdir}/${syst}/${analysis}.mc.Uncertainty_statsyst.${dsid}.${ch}.${syst}.xml

