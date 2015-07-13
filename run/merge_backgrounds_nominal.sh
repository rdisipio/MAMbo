#!/bin/bash

analysis=tt_diffxs_8TeV
analytag=TTbarResolved_resolved

paramsdir=${MAMBODIR}/share/control/merging/${analytag}
outdir=${MAMBODIR}/run/output/${analytag}
syst=nominal
ILUMI=20300 
dsid=110404

tag_wjets=tt_chasymm
[ ! -z $1 ] && wjets=$1

syst=nominal

./merge_wjets_samples_custom.sh ${tag_wjets} ${syst}

echo
echo "//////////////////////////////////"
echo

for ch in el mu
do
  for sample in SingleTop Zjets Diboson
  do
    ofile=${outdir}/${syst}/${analysis}.mc.${sample}.${ch}.${syst}.histograms.root
    MAMbo-mergeSamples.py -l ${ILUMI} -c ${paramsdir}/${sample}_${ch}.xml -o ${ofile} &
  done
  wait
done

  echo
  echo "//////////////////////////////////"
  echo

for ch in el mu
do
  [ $ch == "el" ] && stream="Egamma"
  [ $ch == "mu" ] && stream="Muons"

  hadd -f ${MAMBOOUTPUTDIR}/${syst}/${analysis}.mc.Background.${ch}.${syst}.histograms.root \
          ${MAMBOOUTPUTDIR}/${syst}/${analysis}.mc.Wjets.${ch}.${tag_wjets}.${syst}.histograms.root \
          ${MAMBOOUTPUTDIR}/${syst}/${analysis}.mc.SingleTop.${ch}.${syst}.histograms.root \
          ${MAMBOOUTPUTDIR}/${syst}/${analysis}.mc.Zjets.${ch}.${syst}.histograms.root \
          ${MAMBOOUTPUTDIR}/${syst}/${analysis}.mc.Diboson.${ch}.${syst}.histograms.root \
          ${MAMBOOUTPUTDIR}/${syst}/${analysis}.qcd.${stream}.${ch}.${syst}.histograms.root &
done
wait

echo
echo /////////////////////////////
echo

for ch in el mu
do
   hadd -f ${MAMBOOUTPUTDIR}/${syst}/${analysis}.mc.Expected.${ch}.${syst}.histograms.root \
           ${MAMBOOUTPUTDIR}/${syst}/${analysis}.mc.Background.${ch}.${syst}.histograms.root \
           ${MAMBOOUTPUTDIR}/${syst}/${analysis}.mc.DiTop.${dsid}.${ch}.${syst}.histograms.root &
done
wait

echo
echo /////////////////////////////
echo

hadd -f ${MAMBOOUTPUTDIR}/${syst}/${analysis}.mc.Background.co.${syst}.histograms.root \
        ${MAMBOOUTPUTDIR}/${syst}/${analysis}.mc.Background.el.${syst}.histograms.root \
        ${MAMBOOUTPUTDIR}/${syst}/${analysis}.mc.Background.mu.${syst}.histograms.root &

hadd -f ${MAMBOOUTPUTDIR}/${syst}/${analysis}.mc.Expected.co.${syst}.histograms.root \
        ${MAMBOOUTPUTDIR}/${syst}/${analysis}.mc.Expected.el.${syst}.histograms.root \
        ${MAMBOOUTPUTDIR}/${syst}/${analysis}.mc.Expected.mu.${syst}.histograms.root &

wait
echo "Done."
