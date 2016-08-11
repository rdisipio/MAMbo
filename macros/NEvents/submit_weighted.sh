#!/bin/bash
set -x


filelistdir="../../run/scripts_ttdiffxs_13TeV_ljets/filelists_TTDIFFXS_62_v22/"
cd $filelistdir
datasets=`ls mc*txt | grep 62_v22`
cd -
for ds in $datasets
do
	script=`echo $ds | sed "s#txt#sh#"`
	out=`echo $ds | sed "s#txt#evt.n#" | sed s/mc.//`
	cat > $script << EOF
#!/bin/bash
cd $PWD
python CountInitialEvents.py -i $filelistdir/$ds -o $out 2>&1 | tee $out".log"


EOF
chmod +x $script	
qsub -q T3_BO_LOCAL $script
#./$script

done

set +x
