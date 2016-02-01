#!/bin/bash

path="${MAMBODIR}/run/output/BackGroundMC_prod35"
channels="el mu"
for f in `ls *.run`
do 
echo ${f}
	for c in ${channels}
        do
          runs=`cat ${f}`
	  echo "Runs ${runs}"  
	  
	  roots=""
	  
          for r in ${runs[@]}
          do
           roots="${roots} `ls ${path}/*${r}.${c}*root`"
          done
          out=`echo ${f} | sed s/.run/_$c.root/`
          out="${MAMBODIR}/run/output/prod_35_all_updated/"${out}
  
          hadd -f $out $roots
        done  
done
  
  
