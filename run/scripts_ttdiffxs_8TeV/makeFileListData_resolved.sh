#!/bin/bash

#sourcedir=/gpfs_data/local/atlas/mromano/Resolved8TeV/minintuples-november
sourcedir=/gpfs_data/local/atlas/mromano/Resolved8TeV/minintuples-december-combined_pdf_dijet_7-data_2jet
targetdir=${MAMBODIR}/share/control/file_list/TTbarResolved_resolved

function make_file_list_Egamma
{
stream=Egamma
ch=el

for p in A B C D E G H I J L
do
   sample=$(ls ${sourcedir} | grep vscarfon | grep "period${p}" | grep ${stream} | grep -v "loose" )

   filelist=data.${stream}.period${p}.${ch}.txt
   echo "${stream} period${p} ${ch} -> ${targetdir}/${filelist}"
   makeFileList.sh ${sourcedir}/${sample} > ${targetdir}/${filelist}
done

for p in A B C D E G H I J L
do
   sample=$(ls ${sourcedir} | grep vscarfon | grep "period${p}" | grep ${stream} | grep "el_loose" )

   filelist=qcd.${stream}.period${p}.${ch}.txt
   echo	"${stream} period${p} ${ch} loose -> ${targetdir}/${filelist}"
   makeFileList.sh ${sourcedir}/${sample} > ${targetdir}/${filelist}
done

}


function make_file_list_Muons
{
stream=Muons
ch=mu

for p in A B C D E G H I J L
do
   sample=$(ls ${sourcedir} | grep vscarfon | grep "period${p}" | grep ${stream} | grep ${ch} | grep -v "loose" )

   filelist=data.${stream}.period${p}.${ch}.txt
   echo "${stream} period${p} ${ch} -> ${targetdir}/${filelist}"
   makeFileList.sh ${sourcedir}/${sample} > ${targetdir}/${filelist}
done

for p in A B C D E G H I J L
do
   sample=$(ls ${sourcedir} | grep vscarfon | grep "period${p}" | grep ${stream} | grep "mu_loose" )

   filelist=qcd.${stream}.period${p}.${ch}.txt
   echo "${stream} period${p} ${ch} loose -> ${targetdir}/${filelist}"
   makeFileList.sh ${sourcedir}/${sample} > ${targetdir}/${filelist}
done

}

#########################

make_file_list_Egamma
make_file_list_Muons
