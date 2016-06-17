#!/bin/bash

# http://www.farm.particle.cz/twiki/bin/view/ATLAS/UsefulRucioCommands
# you need:
# localSetupRucioClients

for list in  sig bkg ; do
  for sample in `cat ${list}.txt` ; do
    tag=`echo $sample | cut -d \. -f 4,5`
    echo $sample $tag
    rucio list-file-replicas --rse PRAGUELCG2_LOCALGROUPDISK --proto root ${sample} | awk '/root:/{print $(NF-1)}' > list_${uid}_${tag}.txt
  done
done

# AFII samples:
for list in  sig_AFII ; do
  for sample in `cat ${list}.txt` ; do
    tag=`echo $sample | cut -d \. -f 4,5`
    echo $sample $tag
    rucio list-file-replicas --rse PRAGUELCG2_LOCALGROUPDISK --proto root ${sample} | awk '/root:/{print $(NF-1)}' > list_${uid}_${tag}_AFII.txt
  done
done


# IMPORTANT DIFF IS THE EXTRA '/' NEEDED AFTER ${sample} here;)
for list in  np ; do
  for sample in `cat ${list}.txt` ; do
    tag=`echo $sample | cut -d \. -f 4,5`
    echo $sample $tag
    rucio list-file-replicas --rse PRAGUELCG2_LOCALGROUPDISK --proto root ${sample}/ | awk '/root:/{print $(NF-1)}' > list_${uid}_${tag}.txt
  done
done