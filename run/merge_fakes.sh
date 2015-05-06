#!/bin/bash

analysis=TTbarResolved_resolved
analytag=tt_diffxs_8TeV

systfile=${MAMBODIR}/share/control/analysis_params/${analysis}/qcd_systematics.dat

outdir=$MAMBODIR/run/output/${analysis}


for syst in $(cat ${systfile} )
do

   echo Merging fake leptons systematic ${syst}
   echo

   for ch in el mu
   do
      [ $ch == "el" ] && stream="Egamma"
      [ $ch == "mu" ] && stream="Muons"

      hadd -f ${outdir}/${syst}/${analytag}.qcd.${stream}.${ch}.${syst}.histograms.root \
             ${outdir}/${syst}/${analytag}.qcd.${stream}.period*.${ch}.${syst}.histograms.root &
   done #channel
   wait

   hadd -f ${outdir}/${syst}/${analytag}.qcd.Combined.co.${syst}.histograms.root \
           ${outdir}/${syst}/${analytag}.qcd.Egamma.el.${syst}.histograms.root \
           ${outdir}/${syst}/${analytag}.qcd.Muons.mu.${syst}.histograms.root 

   echo
   echo ///////////////////////////////
   echo
done
