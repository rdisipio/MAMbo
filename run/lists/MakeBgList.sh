#!/bin/sh


#area=/eos/atlas/user/j/jschovan/top-phys/2015/20150121_ntuples/
#    !!!
#file=all.txt
#rm -f ${file}
#for i in `eos ls ${area} ` ; do
#  echo $i >> ${file}
#done

file=list_Marino.txt

for ll in el mu ; do
  echo "Working on ${ll}..."
  for j in Ztautau Zee Zmumu Wenu Wtaunu Wmunu WccNp WcNp WbbNp WW WZ ZZ singletop_tchan_lept_antitop singletop_tchan_lept_top st_schan_lep st_Wtchan_incl_DR ; do
    list=list_${j}_${ll}.txt
    rm -f ${list}
    echo "  Making ${list} ..."
    for i in `cat ${file} | grep ${j} | grep _${ll}.root` ; do
      echo $i >> ${list}
    done
  done
done
