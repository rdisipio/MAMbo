#!/bin/bash
set -x

#datasets=`cat datasets.txt`


#for ds in $datasets
#do
#	ds=`echo $ds | cut -d: -f2`
#	run=`echo $ds | cut -d. -f3`
#	generator=`echo $ds | cut -d. -f4`
#	tag=`echo $ds | cut -d. -f6`
#	filelist=${run}.${generator}.${tag}.list
#	getLocalPath.sh $ds &> $filelist
#done


filelistdir="../../run/scripts_ttdiffxs_13TeV_ljets/filelists_TTDIFFXS_62/"
cd $filelistdir
datasets=`ls mc*txt | grep v7`
cd -
for ds in $datasets
do
	script=`echo $ds | sed "s#txt#sh#"`
	out=`echo $ds | sed "s#txt#evt#" | sed s/mc.//`
	cat > $script << EOF
#!/bin/bash
cd $PWD
./GetNEvents $filelistdir/$ds 2>&1 | tee  $out


EOF
chmod +x $script	
#	qsub -q T3_BO_LOCAL $script
./$script
done

set +x
