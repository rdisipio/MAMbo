#!/bin/bash


# jk 2.6.2015
# area=/eos/atlas/user/m/mromano/minintuples-december
# source ./ListEos.sh | grep root > ListMarinoNew.sh
file=ListMarinoNew.sh

# data:
for ll in el mu ; do
  echo "Working on ${ll}..."
  for j in DATA_RESOLVED_2014_11_03_${ll}  ; do
    list=list_data_${ll}.txt
    rm -f ${list}
    veto=Egamma
    if [ ${ll} == "el" ] ; then
      veto="Muon"
    fi
    echo "  Making ${list} ..."
    for i in `cat ${file} | grep ${j} | grep -v loose | grep -v ${veto}` ; do
      echo $i >> ${list}
    done
  done
done


# loose:
for ll in el mu ; do
  echo "Working on ${ll}..."
  for j in DATA_RESOLVED_2014_11_03_${ll}  ; do
    list=list_data_loose_${ll}.txt
    rm -f ${list}
    echo "  Making ${list} ..."
    veto=Egamma
    if [ ${ll} == "el" ] ; then
      veto="Muon"
    fi
    for i in `cat ${file} | grep ${j} | grep loose | grep -v ${veto}` ; do
      echo $i >> ${list}
    done
  done
done
