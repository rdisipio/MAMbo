analysis=tt_diffxs_8TeV
analytag=TTbarResolved_resolved
ILUMI=20300 

systdir=${MAMBODIR}/share/control/analysis_params/${analytag}
paramsdir=${MAMBODIR}/share/control/merging/${analytag}
outdir=${MAMBODIR}/run/output/${analytag}

listfile_kin=${systdir}/signal_systematics_event_kinematics.dat
listfile_sf=${systdir}/signal_systematics_scalefactors.dat
listfile_el=${systdir}/signal_systematics_eljets_only.dat
listfile_mu=${systdir}/signal_systematics_mujets_only.dat

[[ -d ${paramsdir}/.otf ]] || mkdir -p ${paramsdir}/.otf

dsid=110404
[ ! -z $1 ] && dsid=$1

decay=nofullhad
[ ! -z $2 ] && decay=$2

echo INFO: Merging signal DSID: ${dsid} decay: ${decay}

#SingleTop Wjets Zjets Diboson
for sample in DiTop
do
   # BTAGSF etc..
   for syst in $(cat $listfile_sf)
   do
      ./merge_signal_sample.sh ${dsid} ${syst} ${decay} &

      echo
      echo "//////////////////////////////////"
      echo
   done # syst
   wait

   # eer ees musc JES etc..
   for syst in $(cat $listfile_el $listfile_mu $listfile_kin)
   do
      for var in up down
      do
         ./merge_signal_sample.sh ${dsid} ${syst}_${var} ${decay} &
   
         echo
         echo "//////////////////////////////////"
         echo
      done #var
      wait
   done # syst

   ./merge_signal_sample.sh ${dsid} muid_res ${decay} &
   ./merge_signal_sample.sh ${dsid} mums_res ${decay} &
   ./merge_signal_sample.sh ${dsid} jeff ${decay} &
   wait
done # sample
