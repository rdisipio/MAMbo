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

[[ "x$2" == "x" ]] || syst=$2
echo "Running with systematics: $syst"

outdir=${MAMBODIR}/run/output/${outtag}/${syst}
[[ -d ${outdir} ]] || mkdir -p ${outdir}

for ch in el mu
do
  params=${MAMBODIR}/share/control/analysis_params/${outtag}/mc_${ch}.xml

  for filelist in $( ls ${sourcedir} | grep ${dtsgroup} | grep ${ch} | sort )
  do
     dsid=$( echo ${filelist} | cut -d'.' -f3 )
     tag=${analysis}.${dtsgroup}.${dsid}.${ch}.${syst}

     outfile=${syst}/${tag}.histograms.root
     jobname=${tag}

     echo Submitting ${tag} Output: ${outdir}/${outfile}
     MAMbo-submit.sh -p ${params} -f ${sourcedir}/${filelist} -o ${outfile} -j ${jobname} # -d 1
  done
done
