#!/bin/bash

nfiles=10

infile=$1
[ ! -z $2 ] && nfiles=$2

#prefix=$(echo $infile | sed -e 's/.txt//')
prefix=${infile}.

split --verbose -d -l ${nfiles} ${infile} ${prefix}
