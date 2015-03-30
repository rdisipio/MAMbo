analysis=tt_diffxs_8TeV
analytag=TTbarResolved_resolved
ILUMI=20300 

dsid=110404
[ ! -z $1 ] && dsid=$1

systdir=${MAMBODIR}/share/control/analysis_params/${analytag}
paramsdir=${MAMBODIR}/share/control/merging/${analytag}
outdir=${MAMBODIR}/run/output/${analytag}

listfile_kin=${systdir}/signal_systematics_event_kinematics.dat 
listfile_sf=${systdir}/signal_systematics_scalefactors.dat
listfile_el=${systdir}/signal_systematics_eljets_only.dat
listfile_mu=${systdir}/signal_systematics_mujets_only.dat

sample=DiTop.${dsid}

# nominal MC
syst=nominal
./merge_channels_sample.sh ${sample} ${syst}
echo "Done.."
echo

for syst in $(cat $listfile_sf)
do
   ./merge_channels_sample.sh ${sample} ${syst}
done
echo "Done scale factor systematics..."
echo /////////////////////////////////


for syst in $(cat $listfile_kin)
do 
       for var in up down
       do
          ./merge_channels_sample.sh ${sample} ${syst}_${var}
       done
    done
echo "Done kinematics-changing systematics..."
echo ////////////////////////////////////////


for syst in $(cat $listfile_eljets_only)
    do
      for var in up down
      do
          ./merge_channels_sample.sh ${sample} ${syst}_${var}
      done #for var
done #for syst
echo "Done electron syst..."
echo //////////////////////

for syst in $(cat $listfile_mujets_only)
do
       for var in up down
       do
          ./merge_channels_sample.sh ${sample} ${syst}_${var}
       done #for var
done #for syst
echo "Done muons systematics..."
echo ///////////////////////////


echo "Creating combined uncertainty bands"

./make_uncertainty_band.sh ${dsid} co nominal

# make uncertainty bands
#MAMbo-makeUncertaintyBand.py -c ${paramsdir}/Uncertainty_${dsid}_co_statonly.xml -o ${outdir}/tt_diffxs_8TeV.mc.Uncertainty_statonly.${dsid}.co.nominal.histograms.root \
#                             -x ${outdir}/tt_diffxs_8TeV.mc.Uncertainty_statonly.${dsid}.co.nominal.xml

#MAMbo-makeUncertaintyBand.py -c ${paramsdir}/Uncertainty_${dsid}_co_statsyst.xml -o ${outdir}/tt_diffxs_8TeV.mc.Uncertainty_statsyst.${dsid}.co.nominal.histograms.root \
#                             -x {outdir}/tt_diffxs_8TeV.mc.Uncertainty_statsyst.${dsid}.co.nominal.xml

