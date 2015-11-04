#!/bin/bash

file_list_dir=$MAMBODIR/share/control/file_list/TTbarResolved_resolved

for dts in $(ls $MAMBONTUPLEDIR/ | grep AlpgenAutoPythia_P2012_rad | grep -v .root. )
do
#user.mromano.201432.AlpgenAutoPythia_P2012_radHi_ttbar_ktfac0p5_jjjjNp2.e2356_a188_a222_r4540_p1575.at180_nosyst_mu.root

   dsid=$(echo $dts | cut -d'.' -f3)
   hr=$(echo $dts | cut -d'.'	-f4)
   ch=$(echo $dts | cut -d'.' -f6 | cut -d'_' -f3)

   echo ${dsid}:${hr}:${ch}

   flname=mc.DiTop.${dsid}.${ch}.txt

   makeFileList.sh ${MAMBONTUPLEDIR}/$dts > ${file_list_dir}/${flname}
   sed -i "s|${MAMBONTUPLEDIR}/||g" ${file_list_dir}/${flname}

   [ $ch == "mc" ] ||   ./printSumOfWeights.py ${file_list_dir}/${flname}   
done

