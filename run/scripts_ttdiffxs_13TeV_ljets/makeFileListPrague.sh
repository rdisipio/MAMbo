#!/bin/bash
function getLocalPath()
{

#!/bin/bash
if [ "x$1" == "x" ]
then
        exit
fi
ds=$1
files=`dq2-ls -pf -s PRAGUELCG2_LOCALGROUPDISK $ds | grep srm`
#echo $files
for f in $files
do
        localpath=`echo $f  | sed s#srm:#root:#`
        echo $localpath
done
}

if [ $# -lt 2 ]
then
	echo "Too few parameters"
	exit
fi



pattern=$1
dest=$2
mkdir -p $dest
datasets=$(dq2-ls $pattern)

for d in $datasets
do
	echo $d
	destination=""
	#check if it's a data sample
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
		#user.mromano.410000.PowhegPythiaEvtGen.DAOD_TOPQ1.e3698_s2608_s2183_r7267_r6282_p2516.TTDIFFXS_55_v2_ljets.output.root/
		d=$( echo $d | cut -d: -f2)
		run=$(echo $d | cut -d. -f3)
		generator=$(echo $d | cut -d. -f4)
		tag=$(echo $d | cut -d. -f6)
		jiratag=$(echo $d | cut -d. -f7 | sed s/_ljets//)
		destination=$dest/mc.${run}.${generator}.${tag}.${jiratag}.txt
	fi
	getLocalPath $d > $destination
	nfiles=$(cat $destination | wc -l )
	echo "Destination is $destination ($nfiles files)"
	if [ $nfiles == 0 ]
	then
		echo $d >> empty.txt
	fi
done
