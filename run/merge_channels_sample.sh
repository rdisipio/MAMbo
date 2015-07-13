#!/bin/bash

analysis=tt_diffxs_8TeV
analytag=TTbarResolved_resolved
ILUMI=20300
sample=DiTop.110404
syst=nominal
decay=nofullhad

systdir=${MAMBODIR}/share/control/analysis_params/${analytag}

listfile_el=${systdir}/signal_systematics_eljets_only.dat
listfile_mu=${systdir}/signal_systematics_mujets_only.dat

ELJETS_SYSTEMATICS=$(cat ${listfile_el})
MUJETS_SYSTEMATICS=$(cat ${listfile_mu})

containsElement () {
  local e
  for e in "${@:2}"; do [[ "$e" == "$1" ]] && return 0; done
  return 1
}

[ ! -z $1 ] && sample=$1
[ ! -z $2 ] && syst=$2


outdir=${MAMBODIR}/run/output/${analytag}


emujets=${outdir}/${syst}/${analysis}.mc.${sample}.co.${syst}.${decay}.histograms.root

var=$(echo ${syst} | rev | cut -d'_' -f1 | rev)
syst_base=$(echo ${syst} | sed "s|_$var||")

match_el=$(echo ${ELJETS_SYSTEMATICS[*]} | grep ${syst_base})
match_mu=$(echo ${MUJETS_SYSTEMATICS[*]} | grep ${syst_base})

if [[ "$match_el" != "" ]]
then
   echo "INFO: ${syst} is a e+jets channel only systematic uncertainty"
   ejets=${outdir}/${syst}/${analysis}.mc.${sample}.el.${syst}.${decay}.histograms.root
   mujets=${outdir}/nominal/${analysis}.mc.${sample}.mu.nominal.${decay}.histograms.root
elif [[ "$match_mu" != "" ]] 
then
   echo	"INFO: ${syst} is a mu+jets channel only systematic uncertainty"
   ejets=${outdir}/nominal/${analysis}.mc.${sample}.el.nominal.${decay}.histograms.root
   mujets=${outdir}/${syst}/${analysis}.mc.${sample}.mu.${syst}.${decay}.histograms.root
elif [ ${syst} == "muid_res" -o ${syst} == "mums_res" ]
then
   echo "INFO: ${syst} is a single-sided mu+jets channel only systematic uncertainty"
   ejets=${outdir}/nominal/${analysis}.mc.${sample}.el.nominal.${decay}.histograms.root
   mujets=${outdir}/${syst}/${analysis}.mc.${sample}.mu.${syst}.${decay}.histograms.root
else
   echo "INFO: ${syst} is a two-sided systematic uncertainty"
   ejets=${outdir}/${syst}/${analysis}.mc.${sample}.el.${syst}.${decay}.histograms.root
   mujets=${outdir}/${syst}/${analysis}.mc.${sample}.mu.${syst}.${decay}.histograms.root
fi


hadd -f ${emujets} ${ejets} ${mujets}
