#!/bin/bash

ch=$1

[[ $ch == "el" ]] && stream="Egamma"
[[ $ch == "mu" ]] && stream="Muons"

syst=nominal
[ ! -z $2 ] && syst=$2

echo "Data"
./printCutFlowTable.py $MAMBOOUTPUTDIR/${syst}/tt_diffxs_8TeV.data.${stream}.${ch}.histograms.root

echo
echo "///////////////////////////"
echo

echo "DiTop 110404"
./printCutFlowTable.py $MAMBOOUTPUTDIR/${syst}/tt_diffxs_8TeV.mc.DiTop.110404.${ch}.${syst}.histograms.root

echo
echo "///////////////////////////"
echo

echo "Single top"
./printCutFlowTable.py $MAMBOOUTPUTDIR/${syst}/tt_diffxs_8TeV.mc.SingleTop.${ch}.${syst}.histograms.root

echo
echo "///////////////////////////"
echo

echo "Wjets"

./printCutFlowTable.py $MAMBOOUTPUTDIR/${syst}/tt_diffxs_8TeV.mc.Wjets.${ch}.tt_chasymm.${syst}.histograms.root

echo
echo "///////////////////////////"
echo

echo "Zjets"

./printCutFlowTable.py $MAMBOOUTPUTDIR/${syst}/tt_diffxs_8TeV.mc.Zjets.${ch}.${syst}.histograms.root

echo
echo "///////////////////////////"
echo

echo "Diboson"

./printCutFlowTable.py $MAMBOOUTPUTDIR/${syst}/tt_diffxs_8TeV.mc.Diboson.${ch}.${syst}.histograms.root

echo
echo "///////////////////////////"
echo

echo "Fakes"

./printCutFlowTable.py $MAMBOOUTPUTDIR/${syst}/tt_diffxs_8TeV.qcd.${stream}.${ch}.${syst}.histograms.root

echo
echo "///////////////////////////"
echo

