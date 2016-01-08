#!/bin/bash
set -x
filelistdir="/home/ATLAS-T3/mromano/testarea/unversioned/Diff13TeV/MAMbo/run/scripts_ttdiffxs_13TeV_ljets/filelists_TTDIFFXS_3"
#/run/scripts_ttdiffxs_13TeV_ljets/filelists_TTDIFFXS_3"
mkdir -p cutflow/root
mkdir -p cutflow/text
mkdir jobs
cd $filelistdir
lists=`ls -r  *txt `
cd -
for filelist in $lists
do
	echo "Doing $filelist"
	outrootfile="cutflow/root/`echo $filelist | sed s/.txt/.root/`"
	outtextfile="cutflow/text/$filelist"
	script="jobs/`echo $filelist | sed s/.txt/.sh/`"
#cat > $script << EOF
##!/bin/bash
#./PrintCutflow $filelistdir/$filelist cutFlows.txt $outrootfile $outtextfile
#EOF	
cat > $script << EOF
#!/bin/bash
./PrintCutflow $filelistdir/$filelist cutFlows.txt $outrootfile $outtextfile

EOF
qsub -q T3_BO_LOCAL $script	
done