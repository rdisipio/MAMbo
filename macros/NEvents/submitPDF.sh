#!/bin/bash
filelistdir="../scripts_ttdiffxs_13TeV_ljets/filelists_TTDIFFXS_62/"

function submit
{
	ds=$1
	pdf=$2
	variation=$3


	script=`echo $ds | sed "s#.txt#_${pdf}_${variation}.sh#"`
	out=`echo $ds | sed "s#.txt#_${pdf}_${variation}.evt#" | sed s/mc.//`
	cat > $script << EOF
#!/bin/bash
cd $PWD
./GetNEventsPDF $filelistdir/$ds $pdf $variation 2>&1 | tee $out


EOF
chmod +x $script	
#	qsub -q T3_BO_LOCAL $script
./$script
}



datasets=`cat datasets.txt`


maxvariations_CT14nlo=56
maxvariations_NNPDF30_nlo_as_0118=100
maxvariations_MMHT2014nlo68cl=50
maxvariations_PDF4LHC15_nlo_30=30
maxvariations_PDF4LHC15_nlo_asvar=1


#filelistdir="../scripts_ttdiffxs_13TeV_ljets/filelists_TTDIFFXS_62/"
cd $filelistdir
datasets=`ls mc*410003*txt | grep v5 | grep -v a766_`
cd -



for ds in $datasets
do
#ct14nlo
#	for i in {0..56}
#	do
#		submit $ds CT14nlo $i
#	done
	#NNPDF30_nlo_as_0118
#	for i in {0..100}
	#do
#		submit $ds NNPDF30_nlo_as_0118 $i
#	done
#	#MMHT2014nlo68cl
#	for i in {0..50}
#	do
#		submit $ds MMHT2014nlo68cl $i
#	done
	#PDF4LHC15_nlo_30
	for i in {0..30}
	do
		submit $ds PDF4LHC15_nlo_30 $i
	done
#	#PDF4LHC15_nlo_asvar
#	for i in {0..1}
#	do
#		submit $ds PDF4LHC15_nlo_asvar $i
#	done

done

