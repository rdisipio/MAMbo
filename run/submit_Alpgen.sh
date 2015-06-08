#!/bin/bash

analysis=tt_diffxs_8TeV
outtag=TTbarResolved_resolved

infile=AlpgenIFSR.dat
[ ! -z $1 ] && infile=$1

for dts in $(cat ${infile} | grep -v ':mc' | grep -v 'jjjj' | sort )
do
  # 201030:AlpgenAutoPythia_P2012_radHi_ttbar_ktfac0p5_lnlnNp0:el
  # 201020:AlpgenAutoPythia_P2012_ttbar_lnlnNp0:el
  # 164440:AlpgenJimmy_AUET2CTEQ6L1_ttbarlnlnNp0_baseline:el

  dsid=$(echo ${dts} | cut -d':' -f1)
  hr=$(echo ${dts} | cut -d':' -f2)
  ch=$(echo ${dts} | cut -d':' -f3)

  syst=$(echo ${hr} | cut -d'_' -f3)
  [[ $syst == *"ttbar"* ]] && syst=nominal

  params=${MAMBODIR}/share/control/analysis_params/${outtag}/mc_${ch}.xml 
  filelist=${MAMBODIR}/share/control/file_list/${outtag}/mc.DiTop.${dsid}.${ch}.txt

  tag=${analysis}.mc.DiTop.${dsid}.${ch}.${syst}

  outfile=${syst}/${tag}.histograms.root
  jobname=${tag}
       
  echo "Submitting ${jobname} Outfile ${outfile}"
  MAMbo-submit.sh -p ${params} -f ${filelist} -o ${outfile} -j ${jobname}
  
done
