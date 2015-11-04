#!/bin/bash

file_list_dir=$MAMBODIR/share/control/file_list/TTbarResolved_resolved

ps=pythia
[ ! -z $1 ] && ps=$1

[ $ps == "pythia" ] && gentag=AlpgenAutoPythia_P2012_ttbar
[ $ps == "herwig" ] && gentag=AlpgenJimmy_AUET2CTEQ6L1_ttbar

for dts in $(ls $MAMBONTUPLEDIR/ | grep ${gentag} | grep -v .root. | grep -v jjjj)
do
   #user.mromano.201220.AlpgenAutoPythia_P2012_ttbar_jjlnNp0.e2356_s1581_s1586_r3925_r4540_p1575.at180_nosyst_el.root

   dsid=$(echo $dts | cut -d'.' -f3)
   hr=$(echo $dts | cut -d'.'	-f4)
   ch=$(echo $dts | cut -d'.' -f6 | cut -d'_' -f3)

   [ $ch == "nosyst" ] && ch=$(echo $dts | cut -d'.' -f6 | cut -d'_' -f4)

   echo ${dsid}:${hr}:${ch}

   flname=mc.DiTop.${dsid}.${ch}.txt

   makeFileList.sh ${MAMBONTUPLEDIR}/$dts > ${file_list_dir}/${flname}
   sed -i "s|${MAMBONTUPLEDIR}/||g" ${file_list_dir}/${flname}

   [ ! ${ch} == "mc" ] && ./printSumOfWeights.py ${file_list_dir}/${flname}
done

