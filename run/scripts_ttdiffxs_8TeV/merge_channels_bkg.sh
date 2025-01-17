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


# real data
cofile=${outdir}/nominal/${analysis}.data.Combined.co.histograms.root
elfile=${outdir}/nominal/${analysis}.data.Egamma.el.histograms.root
mufile=${outdir}/nominal/${analysis}.data.Muons.mu.histograms.root
hadd -f ${cofile} ${elfile} ${mufile} &

syst=nominal

# fake leptons
   cofile=${outdir}/nominal/${analysis}.qcd.Combined.co.${syst}.histograms.root
   elfile=${outdir}/nominal/${analysis}.qcd.Egamma.el.${syst}.histograms.root
   mufile=${outdir}/nominal/${analysis}.qcd.Muons.mu.${syst}.histograms.root
   hadd -f ${cofile} ${elfile} ${mufile} &

# Wjets
    cofile=${outdir}/${syst}/${analysis}.mc.Wjets.co.tt_chasymm.${syst}.histograms.root
    elfile=${outdir}/${syst}/${analysis}.mc.Wjets.el.tt_chasymm.${syst}.histograms.root
    mufile=${outdir}/${syst}/${analysis}.mc.Wjets.mu.tt_chasymm.${syst}.histograms.root
    hadd -f ${cofile} ${elfile} ${mufile} &

for sample in SingleTop Zjets Diboson Background
do
    cofile=${outdir}/${syst}/${analysis}.mc.${sample}.co.${syst}.histograms.root
    elfile=${outdir}/${syst}/${analysis}.mc.${sample}.el.${syst}.histograms.root
    mufile=${outdir}/${syst}/${analysis}.mc.${sample}.mu.${syst}.histograms.root
    hadd -f ${cofile} ${elfile} ${mufile} &
done
wait
echo "Done.."
echo
