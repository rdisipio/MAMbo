#!/bin/bash

job=$1
log=$(echo $job | sed 's/job/log/' | sed 's/.sh//' )
name=$(echo $job | cut -d'/' -f2 | sed 's/.job//' | sed 's/.sh//' )

brokenhost='wn-205-04-23-02-b'
#echo job $job
#echo log $log
#echo name $name

#bsub -q T3_BO  -o $log -J $name $job
bsub -R "select[ (hname!='wn-205-04-23-02-b')]" -o $log -J $name -q T3_BO_LOCAL $job 
