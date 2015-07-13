#!/bin/bash

analysis=tt_diffxs_8TeV
analytag=TTbarResolved_resolved
paramsdir=${MAMBODIR}/share/control/merging/${analytag}
outdir=${MAMBODIR}/run/output/${analytag}

ch=$1

if [[ ${ch} == "el" ]]
then
   ofile=${outdir}/${analysis}.data.Egamma.${ch}.histograms.root
   hadd -f ${ofile} ${outdir}/${analysis}.data.Egamma.period*.${ch}.histograms.root
else
   ofile=${outdir}/${analysis}.data.Muons.${ch}.histograms.root
   hadd	-f ${ofile} ${outdir}/${analysis}.data.Muons.period*.${ch}.histograms.root 
fi


for sample in DiTop SingleTop Wjets #Zjets Diboson
do
  MAMbo-mergeSamples.py -c ${paramsdir}/${sample}_${ch}.xml -o ${outdir}/${analysis}.mc.${sample}.${ch}.histograms.root
done

MAMbo-makeUncertaintyBand.py -c ${paramsdir}/Uncertainty_${ch}.xml -o ${outdir}/${analysis}.mc.Uncertainty.${ch}.histograms.root

MAMbo-makePlots.py control/basic_plots_${ch}.xml
