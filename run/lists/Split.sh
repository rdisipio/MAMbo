#!/bin/bash

# base=list_eos_new

if [ $# -lt 1 ] ; then
  echo "ERROR: no file list to split provided!"
  exit 1
fi

base=`basename $1 .txt`

#for ll in el mu mc ; do
#  split -l 8 ${base}_${ll}.txt split_${base}_${ll}_
#done

split -l 5 ${base}.txt split_${base}_
