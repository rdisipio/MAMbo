#!/bin/bash

analysis=TTbarResolved_resolved
analytag=tt_diffxs_8TeV
tag_wjets=tt_chasymm
systfile=${MAMBODIR}/share/control/analysis_params/${analysis}/qcd_systematics.dat

ch=co
[ ! -z $1 ] && ch=$1

for syst in WjetsSF_up WjetsSF_down
do
  ./make_unfolding_sample.sh $syst $ch
done

for syst in $(cat ${systfile} )
do
  ./make_unfolding_sample.sh $syst $ch
done

