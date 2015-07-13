#!/bin/bash

file_list_dir=$MAMBODIR/share/control/file_list/TTbarResolved_resolved

for dts in $(ls $MAMBONTUPLEDIR/ | grep Sherpa | grep "root." )
do

   dsid=$(echo $dts | cut -d'.' -f3)
   hr=$(echo $dts | cut -d'.'	-f4)
   ch=$(echo $dts | cut -d'.' -f6 | cut -d'_' -f2)

   echo ${dsid}:${hr}:${ch}

   flname=mc.Wjets.${dsid}.${ch}.txt

   makeFileList.sh ${MAMBONTUPLEDIR}/$dts >> ${file_list_dir}/${flname}

   sed -i "s|${MAMBONTUPLEDIR}/||g" ${file_list_dir}/${flname}
done

