#!/bin/bash

#
# d -i 's/\/gpfs_data\/local\/atlas\/mromano\/Resolved8TeV\/minintuples-november\///g' *.txt.*

#sourcedir=/gpfs_data/local/atlas/mromano/Resolved8TeV/minintuples-december-combined_pdf_dijet_7

targetdir=${MAMBODIR}/share/control/file_list/TTbarResolved_resolved

function make_file_list_DiTop
{
dtsgroup=DiTop
for ch in el mu
do
   dsid=110404
   filelist=mc.${dtsgroup}.${dsid}.${ch}.txt
   sample=$( ls ${MAMBONTUPLEDIR} | grep ${dsid} | grep ${ch} )
   echo "${dtsgroup} ${dsid} ${ch} -> ${targetdir}/${filelist}"

   makeFileList.sh ${MAMBONTUPLEDIR}/${sample} > ${targetdir}/${filelist}
   sed -i "s|${MAMBONTUPLEDIR}/||g" ${targetdir}/${filelist}
   split_file_list.sh ${targetdir}/${filelist}
done
}



function make_file_list_Wjets
{
dtsgroup=Wjets
for ch in el mu
do
   for sample in $(ls ${MAMBONTUPLEDIR} | grep Auto | grep "W" | grep "2jet" | grep ${ch} | sort ) 
   do
      dsid=$( echo ${sample} | cut -d'.' -f3 )
      filelist=mc.${dtsgroup}.${dsid}.${ch}.txt
      echo "${dtsgroup} ${dsid} ${ch} -> ${filelist}"
      makeFileList.sh ${MAMBONTUPLEDIR}/${sample} > ${targetdir}/${filelist}
      sed -i "s|${MAMBONTUPLEDIR}/||g" ${targetdir}/${filelist}
   done
done
}


function make_file_list_SingleTop
{
dtsgroup=SingleTop
for ch in el mu
do 
  for dsid in 110090 110091 110119 110140
  do
      filelist=mc.${dtsgroup}.${dsid}.${ch}.txt
      sample=$( ls ${MAMBONTUPLEDIR} | grep ${dsid} | grep ${ch} | grep "2jet" )
      echo "${dtsgroup} ${dsid} ${ch} -> ${targetdir}/${filelist}"
      makeFileList.sh ${MAMBONTUPLEDIR}/${sample} > ${targetdir}/${filelist}
      sed -i "s|${MAMBONTUPLEDIR}/||g" ${targetdir}/${filelist}
  done
done
}


function make_file_list_Zjets
{
dtsgroup=Zjets
for ch in el mu
do
   for sample in $(ls ${MAMBONTUPLEDIR} | grep Auto | grep "Z" | grep "2jet" | grep ${ch} | sort )
   do
      dsid=$( echo ${sample} | cut -d'.' -f3 )
      filelist=mc.${dtsgroup}.${dsid}.${ch}.txt
      echo "${dtsgroup} ${dsid} ${ch} -> ${filelist}"
      makeFileList.sh ${MAMBONTUPLEDIR}/${sample} > ${targetdir}/${filelist}
      sed -i "s|${MAMBONTUPLEDIR}/||g" ${targetdir}/${filelist}
   done

#   for sample in $(ls ${MAMBONTUPLEDIR} | grep Auto | grep "Z" | grep "tau" | grep ${ch} | sort )
#   do 
#      dsid=$( echo ${sample} | cut -d'.' -f4 )
#      filelist=mc.${dtsgroup}.${dsid}.${ch}.txt
#      echo "${dtsgroup} ${dsid} ${ch} -> ${targetdir}/${filelist}"
#      makeFileList.sh ${MAMBONTUPLEDIR}/${sample} > ${targetdir}/${filelist}
#  done

done
}

function make_file_list_Diboson
{
dtsgroup=Diboson
for ch in el mu
do
  for dsid in 105985 105986 105987
  do
      sample=$(ls ${MAMBONTUPLEDIR} | grep ${dsid} | grep ${ch} | grep "2jet" )
      filelist=mc.${dtsgroup}.${dsid}.${ch}.txt
      echo "${dtsgroup} ${dsid} ${ch} -> ${targetdir}/${filelist}"
      makeFileList.sh ${MAMBONTUPLEDIR}/${sample} > ${targetdir}/${filelist}
      sed -i "s|${MAMBONTUPLEDIR}/||g" ${targetdir}/${filelist}
  done
done
}

#########################

#make_file_list_DiTop
make_file_list_SingleTop
#make_file_list_Wjets
#make_file_list_Zjets
make_file_list_Diboson
