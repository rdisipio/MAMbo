#!/bin/bash

containsElement () {
  local e
  for e in "${@:2}"; do [[ "$e" == "$1" ]] && return 0; done
  return 1
}


analysis=tt_diffxs_8TeV
outtag=TTbarResolved_resolved
syst=nominal

PARAMSDIR=${MAMBODIR}/share/control/analysis_params/${outtag}

SCALE_FACTOR_SYSTEMATICS=$(cat ${PARAMSDIR}/signal_systematics_scalefactors.dat )
ELJETS_SYSTEMATICS=$(cat ${PARAMSDIR}/signal_systematics_eljets_only.dat)
MUJETS_SYSTEMATICS=$(cat ${PARAMSDIR}/signal_systematics_mujets_only.dat)

dsid=110404
[ ! -z $1 ] && dsid=$1

[ ! -z $2 ] && syst=$2
echo "Analyzing signal sample $dsid with systematics: $syst"

decay=nofullhad

outdir=${MAMBODIR}/run/output/${outtag}/${syst}

[[ -d ${outdir} ]] || mkdir -p ${outdir}
echo Output directory: ${outdir}

for ch in el mu
do
     echo "INFO: submitting channel ${ch}"

     params=${MAMBODIR}/share/control/analysis_params/${outtag}/mc_${ch}.xml 
     filelist=${MAMBODIR}/share/control/file_list/${outtag}/mc.DiTop.${dsid}.${ch}.txt

     if [[ "$syst" != "nominal" ]] 
     then
        newparams=$(echo $params | sed "s/xml/${syst}.xml/" )
        cp ${params} ${newparams}
     
        match=$(echo ${SCALE_FACTOR_SYSTEMATICS[*]} | grep ${syst})
        if [[ "$match" != "" ]]
        then
	   echo "${syst} is a scale factor systematic"
           sed -i "s/NOMINAL/${syst}/" ${newparams}  
        else
           echo "${syst} is a kinematics-changing systematic"
           sed -i "s/mini/${syst}/" ${newparams}
        fi
        params=${newparams}
     fi

     for flist in $(ls ${filelist}.*)
     do
         batchid=$(echo ${flist} | grep -oE "[^.]+$")

	 tag=${analysis}.mc.DiTop.${dsid}.${ch}.${syst}.${decay}

         outfile=${syst}/${tag}.histograms.root.${batchid}
         jobname=${tag}.${batchid}
       
	 echo "Submitting ${jobname}"
         MAMbo-submit.sh -p ${params} -f ${flist} -o ${outfile} -j ${jobname}
     done

     echo
done
