#!/bin/bash

analysis=tt_diffxs_8TeV
analytag=TTbarResolved_resolved

paramsdir=${MAMBODIR}/share/control/merging/${analytag}
outdir=${MAMBODIR}/run/output/${analytag}
syst=nominal
ILUMI=20300 

tag=nosf
[[ ! -z $1 ]] && tag=$1
[[ ! -z $2 ]] && syst=$2

for ch in el mu
do

for flav in lf c bbcc
do
   params=${paramsdir}/Wjets_${flav}_${ch}.${tag}.${syst}.xml

   cp ${paramsdir}/Wjets_${flav}.${tag}.${syst}.xml ${params}
   sed -i "s/@CHANNEL@/${ch}/g" ${params}

   MAMbo-mergeSamples.py -l ${ILUMI} -c ${params} -o ${outdir}/${syst}/${analysis}.mc.Wjets_${flav}.${ch}.${tag}.${syst}.histograms.root

   echo
   echo ////////////////////////////////
   echo
done

ofile=${outdir}/${syst}/${analysis}.mc.Wjets.${ch}.${tag}.${syst}.histograms.root
hadd -f ${ofile} \
        ${outdir}/${syst}/${analysis}.mc.Wjets_lf.${ch}.${tag}.${syst}.histograms.root \
        ${outdir}/${syst}/${analysis}.mc.Wjets_c.${ch}.${tag}.${syst}.histograms.root \
        ${outdir}/${syst}/${analysis}.mc.Wjets_bbcc.${ch}.${tag}.${syst}.histograms.root

        echo ////////////////////////////////

done #channel

for flav in lf c bbcc
do
     hadd -f ${outdir}/${syst}/${analysis}.mc.Wjets_${flav}.co.${tag}.${syst}.histograms.root \
        ${outdir}/${syst}/${analysis}.mc.Wjets_${flav}.el.${tag}.${syst}.histograms.root \
        ${outdir}/${syst}/${analysis}.mc.Wjets_${flav}.mu.${tag}.${syst}.histograms.root

     echo ////////////////////////////////
     echo
done

echo

hadd -f ${outdir}/${syst}/${analysis}.mc.Wjets.co.${tag}.${syst}.histograms.root \
        ${outdir}/${syst}/${analysis}.mc.Wjets.el.${tag}.${syst}.histograms.root \
        ${outdir}/${syst}/${analysis}.mc.Wjets.mu.${tag}.${syst}.histograms.root
  
