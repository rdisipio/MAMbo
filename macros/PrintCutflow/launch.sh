#!/bin/bash

filelistdir="../../run/scripts_ttdiffxs_13TeV_ljets/filelists_TTDIFFXS_3"
mkdir -p cutflow/root
mkdir -p cutflow/text
for filelist in `ls $filelistdir`
do
	outrootfile="cutflow/root/`echo $filist | sed s/.list/.root/`"
	outtextfile="cutflow/root/`echo $filist | sed s/.list/.txt/`"
	./PrintCutflow $filelistdir/$filelist cutFlows.txt $outrootfile $outtextfile
		
done
