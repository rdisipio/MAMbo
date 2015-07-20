#!/bin/bash

analysis=tt_diffxs_8TeV
outtag=TTbarResolved_resolved
syst=particle

queue=T3_BO_LOCAL
[[ ${HOSTNAME} == *"cern.ch"* ]] && queue=1nh

dsid=105200
decay=nofullhad
[[ ! -z $1 ]] && decay=$1

#pdfset=NNPDF23_nlo_as_0119
pdfset=MSTW2008nlo68cl 
[[ ! -z $2 ]] && pdfset=$2

eigen=0
[[ ! -z $3 ]] && eigen=$3

pdftag=PDF_${pdfset}_${eigen}

[[ ! -d ${MAMBOOUTPUTDIR}/particle ]] && mkdir -p ${MAMBOOUTPUTDIR}/particle

for ch in el mu
do
     echo "INFO: submitting DiTop dsid=$dsid channel ${ch}"

     params=${MAMBODIR}/share/control/analysis_params/${outtag}/mcparticle_${ch}_${decay}.${pdftag}.xml 
     filelist=${MAMBODIR}/share/control/file_list/${outtag}/mc.DiTop.${dsid}.mc.txt

     for flist in $(ls ${filelist}.*)
     do
         batchid=$(echo ${flist} | grep -oE "[^.]+$")

	 tag=${analysis}.mc.DiTop.${dsid}.${ch}.${syst}.${decay}.${pdftag}

         outfile=${syst}/${tag}.histograms.root.${batchid}
         jobname=${tag}.${batchid}
       
	 echo "Submitting ${jobname}"

         MAMbo-submit.sh -p ${params} -f ${flist} -o ${outfile} -j ${jobname} -q ${queue}
     done

     echo
done
