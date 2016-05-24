#!/bin/bash
# set -x
ls *evt.n  | while read a
do 
  run=`echo $a | cut -d. -f1`
  
 # echo $run
  tag=`echo $a | cut -d. -f3`
  olddir=../NEvents_TTDIFFXS_55/
  oldfile="$olddir/`echo $a | sed s/TTDIFFXS_62_v5/TTDIFFXS_55_v2/`"
#  oldfile=`ls ../NEvents_TTDIFFXS_55/`
 # echo $a $oldfile
 nlines=`echo $oldfile | wc -l`
 if [ ! -e $oldfile ]
  then 
       continue
 fi
# cat $a
# cat $oldfile
  newevents=`cat $a | sed s/$run//g`
  oldevents=`cat $oldfile | sed s/$run//g`
  echo $a
  echo "$run : `echo $newevents -  $oldevents | bc`"
 done

 
#410116.MadGraphPythia8EvtGen.e4632_s2726_r7326_r6282_p2516.TTDIFFXS_62_v5.evt.n
