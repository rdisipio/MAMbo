#!/bin/bash

analysis=tt_diffxs_8TeV
outtag=TTbarResolved_resolved
paramsdir=${MAMBODIR}/share/control/analysis_params/${outtag}

infile=AlpgenPythia.dat
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

  [ $ch == "el" ] && ch_tag="electron"
  [ $ch == "mu" ] && ch_tag="muon"

  params=${paramsdir}/mcsignal_${ch}.${dsid}.xml 
  cp ${paramsdir}/mcsignal_template.xml ${params}

  filelist=${MAMBODIR}/share/control/file_list/${outtag}/mc.DiTop.${dsid}.${ch}.txt
  filelist_mc=$( echo $filelist | sed "s/${ch}.txt/mc.txt/" )
 
  sed -i "s|@CHANNEL@|${ch_tag}|"       ${params}
  sed -i "s|@MCFILELIST@|${filelist_mc}|"  ${params}
 
  tag=${analysis}.mc.DiTop.${dsid}.${ch}.${syst}

  outfile=${syst}/${tag}.histograms.root
  jobname=${tag}
       
  echo "Submitting ${jobname} Outfile ${outfile}"
  MAMbo-submit.sh -p ${params} -f ${filelist} -o ${outfile} -j ${jobname}
  
done
