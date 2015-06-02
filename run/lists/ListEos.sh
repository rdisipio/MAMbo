#!/bin/bash


source ~/bin/asetup.sh

alias eos='/afs/cern.ch/project/eos/installation/0.3.84-aquamarine/bin/eos.select'


#cd /afs/cern.ch/user/q/qitek/qitek/TopResolved_8TeV_MAMbo/TTbarUnfold8TeV
#. setup.sh
#cd run/

# path=/eos/atlas/user/j/jschovan/top-phys/2015/20150219_ntuples/
path=/eos/atlas/user/m/mromano/minintuples-december/


prefix="root://eosatlas/"


for i in `eos ls ${path}` ; do
  #echo "* ${path}/${i}"
  for j in `eos ls ${path}/${i}` ; do
    echo "${prefix}${path}/${i}/${j}"
    #for k in `eos ls ${path}/${i}/${k}` ; do
      #eos ls -l ${path}/${i}/${j}/${k} | grep root
      #eos ls ${path}/${i}/${j}
    #done
  done
done
