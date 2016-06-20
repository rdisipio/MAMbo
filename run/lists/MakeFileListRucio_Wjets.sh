#!/bin/bash

# http://www.farm.particle.cz/twiki/bin/view/ATLAS/UsefulRucioCommands
# you need:
# localSetupRucioClients


for list in  bg_Wjets_new ; do
  for sample in `cat ${list}.txt` ; do
    tag=`echo $sample | cut -d \. -f 4,5`
    echo "Sample: $sample tag: $tag"
    rucio list-file-replicas --rse PRAGUELCG2_LOCALGROUPDISK --proto root ${sample} | awk '/root:/{print $(NF-1)}' | sed 's|/dpm/|//dpm/|g' > list_${uid}_${tag}_v8.txt
  done
done
