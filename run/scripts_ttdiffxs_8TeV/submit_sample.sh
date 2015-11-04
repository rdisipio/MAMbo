#!/bin/bash

analysis=tt_diffxs_8TeV
outtag=TTbarResolved_resolved
syst=nominal

sourcedir=${MAMBODIR}/share/control/file_list/${outtag}

dtsgroup=$1
if [[ ${dtsgroup} == "" ]] 
then
   echo Please specify dtsgroup: DiTop|SingleTop|Wjets|Zjets|Diboson
   exit 0
fi

dsid=$2

syst=nominal
[ ! -z $3 ] && syst=$3

outdir=${MAMBODIR}/run/output/${outtag}/${syst}
[[ -d ${outdir} ]] || mkdir -p ${outdir}

for ch in el mu
do
  params=${MAMBODIR}/share/control/analysis_params/${outtag}/mc_${ch}.xml

  filelist=${sourcedir}/mc.${dtsgroup}.${dsid}.${ch}.txt

  tag=${analysis}.mc.${dtsgroup}.${dsid}.${ch}.${syst}
  outfile=${syst}/${tag}.histograms.root
  jobname=${tag}

  echo Submitting ${tag} Output: ${outdir}/${outfile}
  MAMbo-submit.sh -p ${params} -f ${filelist} -o ${outfile} -j ${jobname} # -d 1

done
