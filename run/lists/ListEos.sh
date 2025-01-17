#!/bin/bash


source ~/bin/asetup.sh


# path=/eos/atlas/user/j/jschovan/top-phys/2015/20150219_ntuples/
# path=/eos/atlas/user/m/mromano/minintuples-december/


# DEFAULT:
# path=/eos/atlas/user/q/qitek/top-phys/2015/20150716_ntuples/


### TODO!!!
# fixed data, but incoplete:
#path=/eos/atlas/user/q/qitek/top-phys/2015/20150826_ntuples/

# COMPLETE FIXED DATA:
# /eos/atlas/user/m/mromano/minintuples-december/user.mromano.period*.at180_2jet_ajc0340_*.root                                                                                                
path=/eos/atlas/user/m/mromano/minintuples-december/


# mass-varied MC samples:
#path=/eos/atlas/user/q/qitek/top-phys/2015/20150827_ntuples/


alias eos='/afs/cern.ch/project/eos/installation/0.3.84-aquamarine/bin/eos.select'


#cd /afs/cern.ch/user/q/qitek/qitek/TopResolved_8TeV_MAMbo/TTbarUnfold8TeV
#. setup.sh
#cd run/


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
