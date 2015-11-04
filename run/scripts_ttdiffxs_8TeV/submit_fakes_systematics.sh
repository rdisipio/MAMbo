#!/bin/bash

systfile=$MAMBODIR/run/systematics_qcd.dat
[ ! -z $1 ] && systfile=$1

for syst in $( cat $systfile )
do
   ./submit_fakes.sh $syst  
done

