#!/bin/bash

systfile=$MAMBODIR/run/systematics_qcd.dat

for syst in $( cat $systfile )
do
   ./submit_fakes.sh $syst  
done

