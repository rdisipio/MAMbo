#!/bin/bash

if [ $# -lt 2 ]
then
	echo "Too few parameters"
	exit
fi

pattern=$1
dest=$2
mkdir -p $dest
datasets=$(rucio list-dids $pattern | grep "CONTAINER")
datasets=$(echo $datasets | cut -d"|" -f2)
#datasets_nouser=$(echo $datasets | cut -d":" -f2)
echo $datasets

for d in $datasets

do
    destination=""
    
    files=$(rucio list-file-replicas --rse INFN-BOLOGNA-T3_LOCALGROUPDISK $d | awk '/srm:/{print $(NF-1)}' )
 
    d=${d##*":"}
    
    if [[ $d == *"Main"* ]]
	then
		echo "It's data!"
		d=$( echo $d | cut -d: -f2)
		run=$(echo $d | cut -d. -f3)
		stream=$(echo $d | cut -d. -f4)
		tag=$(echo $d | cut -d. -f6)
		jiratag=$(echo $d | cut -d. -f7 | sed s/_ljets//)
		destination=$dest/data.${run}.${stream}.${tag}.${jiratag}.txt
	else
 		echo "It'S mc!"
                d=$( echo $d | cut -d: -f2)
		run=$(echo $d | cut -d. -f3)
		generator=$(echo $d | cut -d. -f4)
		tag=$(echo $d | cut -d. -f6)
		jiratag=$(echo $d | cut -d. -f7 | sed s/_ljets//)
		destination=$dest/mc.${run}.${generator}.${tag}.${jiratag}.txt
        fi
        
    echo $destination
    echo "" > $destination
    
    for file in $files
    do
      file="/gpfs_data/storm"${file##*"/srm/managerv2?SFN="}
      echo $file >> $destination
     
    done
    
    nfiles=$(cat $destination | wc -l )
    echo "Destination is $destination ($nfiles files)"
    if [ $nfiles == 0 ]
        then
		echo $d >> empty.txt
	fi
done
