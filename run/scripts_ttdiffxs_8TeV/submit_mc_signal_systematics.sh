#!/bin/bash


analysis=tt_diffxs_8TeV
analytag=TTbarResolved_resolved

systdir=${MAMBODIR}/share/control/analysis_params/${analytag}

SYST_KIN=${systdir}/signal_systematics_event_kinematics.dat
SYST_SF=${systdir}/signal_systematics_scalefactors.dat 
SYST_ELJETS=${systdir}/signal_systematics_eljets_only.dat
SYST_MUJETS=${systdir}/signal_systematics_mujets_only.dat

dsid=110404
[ ! -z $1 ] && dsid=$1

for syst in $(cat ${SYST_ELJETS} )
do
  for var in up down
  do
    ./submit_mc_signal_as_bkg.sh ${dsid} ${syst}_${var}
  done
done

for syst in $(cat ${SYST_MUJETS} )
do
  for var in up down
  do
    ./submit_mc_signal_as_bkg.sh ${dsid} ${syst}_${var}
  done
done

for syst in $(cat ${SYST_KIN} )
do
  for var in up down
  do
    ./submit_mc_signal_as_bkg.sh ${dsid} ${syst}_${var}
  done
done

for syst in $(cat ${SYST_SF} )
do
    ./submit_mc_signal_as_bkg.sh ${dsid} ${syst}
done

# these are one-sided
./submit_mc_signal_as_bkg.sh ${dsid} jer
./submit_mc_signal_as_bkg.sh ${dsid} jeff
./submit_mc_signal_as_bkg.sh ${dsid} muid_res
./submit_mc_signal_as_bkg.sh ${dsid} mums_res
