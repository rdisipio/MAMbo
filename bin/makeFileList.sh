#!/bin/bash

indir=$1

for f in $(ls $indir/*.root* | sort)
do
  echo $f
done
