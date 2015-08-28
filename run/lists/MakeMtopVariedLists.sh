#!/bin/bash

cat ListMassVaried.txt | cut -d \. -f 4 | cut -d _ -f 1,2 | sort | uniq > masses.txt



for ll in el mu mc ; do
 
  for mass in `cat masses.txt` ; do
     cat ListMassVaried.txt | grep $mass | grep _${ll} > list_mtop_${mass}_${ll}.txt
  done


done