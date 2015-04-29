#!/bin/bash

analysis=tt_diffxs_8TeV
analytag=TTbarResolved_resolved

paramsdir=${MAMBODIR}/share/control/merging/${analytag}
outdir=${MAMBODIR}/run/output/${analytag}
syst=nominal
ILUMI=20300 

ch=$1
[[ ! -z $2 ]] && syst=$2

#for ch in el mu
#do

for flav in lf c bbcc
do
   echo INFO: Merging W+$flav channel: $ch
 
   for njets in 3jincl 4jincl
   do
      MAMbo-mergeSamples.py -l ${ILUMI} -c ${paramsdir}/Wjets_${flav}_${njets}_${ch}.xml -o ${outdir}/${syst}/${analysis}.mc.Wjets_${flav}_${njets}.${ch}.${syst}.histograms.root
   done

   ofile=${outdir}/${syst}/${analysis}.mc.Wjets_${flav}.${ch}.${syst}.histograms.root
   hadd -f ${ofile} ${outdir}/${syst}/${analysis}.mc.Wjets_${flav}_?jincl.${ch}.${syst}.histograms.root

   echo ////////////////////////////////
done
echo
echo INFO: Merging final W+jets channel: $ch
ofile=${outdir}/${syst}/${analysis}.mc.Wjets.${ch}.${syst}.histograms.root
hadd -f ${ofile} \
        ${outdir}/${syst}/${analysis}.mc.Wjets_lf.${ch}.${syst}.histograms.root \
        ${outdir}/${syst}/${analysis}.mc.Wjets_c.${ch}.${syst}.histograms.root \
        ${outdir}/${syst}/${analysis}.mc.Wjets_bbcc.${ch}.${syst}.histograms.root
echo
echo ////////////////////////////////
echo

#done


#echo INFO: Merging combined channels W+jets
#ofile=${outdir}/${syst}/${analysis}.mc.Wjets.co.${syst}.histograms.root 
#hadd -f ${ofile} \
#        ${outdir}/${syst}/${analysis}.mc.Wjets.el.${syst}.histograms.root ${outdir}/${syst}/${analysis}.mc.Wjets.mu.${syst}.histograms.root
