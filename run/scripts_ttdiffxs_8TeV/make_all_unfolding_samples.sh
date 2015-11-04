#!/bin/bash

analysis=TTbarResolved_resolved
analytag=tt_diffxs_8TeV
tag_wjets=tt_chasymm
systfile=${MAMBODIR}/share/control/analysis_params/${analysis}/qcd_systematics.dat
decay=nofullhad

ch=co
[ ! -z $1 ] && ch=$1

for syst in WjetsSF_up WjetsSF_down
do
  ./make_unfolding_sample.sh $syst $ch $decay
done

for sample in st zjets diboson
do
  for syst in xsec_up xsec_down 
  do
    syst="${sample}_${syst}"
      ./make_unfolding_sample.sh $syst $ch $decay
  done
done

for syst in $(cat ${systfile} )
do
  ./make_unfolding_sample.sh $syst $ch $decay
done

