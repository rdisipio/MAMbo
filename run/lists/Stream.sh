#!/bin/sh

for ll in el mu mc ; do
  file=list_eos_new_${ll}.txt
  rm -f ${file}
  for i in `cat list_eos_new.txt  | grep ${ll}.root` ; do
    echo "root://eosatlas/${i}" >> ${file} 
  done
done


