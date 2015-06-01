#!/bin/sh

if [ $# -lt 1 ] ; then
  echo "Usage: $0 string"
  exit 1
fi

for i in `qs.sh  | grep $1 | cut -d " " -f 1` ; do bkill $i ; done


