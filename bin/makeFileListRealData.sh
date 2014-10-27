#!/bin/bash

TARGETDIR=${MAMBODIR}/share/control/file_list/TTbarResolved

indir=$1

for fullpath in $(ls $indir/*.root* | grep period | grep -v loose | sort | cut -d':' -f1 )
do
   dir=$( echo ${fullpath} | grep -oE "[^/]+$" )
    
   period=$( echo ${dir} | cut -d'.' -f3 )
   stream=$( echo ${dir} | cut -d'.' -f4 )
   ch=$(     echo ${dir} | cut -d'.' -f6 | cut -d'_' -f6 )

   [[ "${stream}" == "Egamma" && "${ch}" == "mu" ]] && continue
   [[ "${stream}" == "Muons"  && "${ch}" == "el" ]] && continue

   ofile=${TARGETDIR}/data.${stream}.${period}.${ch}.txt

   echo "${dir} -> ${ofile}"

   makeFileList.sh ${fullpath} > ${ofile}
done

