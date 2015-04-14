#!/bin/bash

sample=$1
ch=$2

syst=nominal
[ ! -z $3 ] && syst=$3

for file in $(ls $MAMBOOUTPUTDIR/${syst}/tt_diffxs_8TeV.${sample}.*.${ch}.${syst}.histograms.root)
do
   echo ${sample} : ${file}
   ./printCutFlowTable.py ${file}
done
echo
echo "///////////////////////////"
echo
