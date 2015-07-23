#!/bin/bash


#area=/eos/atlas/user/j/jschovan/top-phys/2015/20150121_ntuples/
#area=/eos/atlas/user/q/qitek/top-phys/2015/20150716_ntuples/
#    !!!
#file=all.txt
#rm -f ${file}
#for i in `eos ls ${area} ` ; do
#  echo $i >> ${file}
#done
#file=list_Marino.txt

# area=/eos/atlas/user/m/mromano/minintuples-december
# source ./ListEos.sh | grep root > ListMarinoNew.sh

file=ListMarinoNew.txt


for ll in el mu mc ; do
  echo "Working on ${ll}..."
  for j in PowhegPythia_P2011C_ttbar_hdamp172p5_nonallhad.mcfixed_at180_combined_pdf_dijet \
           PowhegPythia_P2011C_HERAPDF15NLO_ttbar.at180_combined_pdf_dijet  \
           PowhegPythia_Perugia2012radHi_ttbar_hdamp345p0_nonallhad \
           PowhegPythia_Perugia2012radLo_ttbar_hdamp172p5_nonallhad \
           AlpgenAutoPythia_P2012_radHi_ttbar_ktfac0p5_jjjjNp0 \
           AlpgenAutoPythia_P2012_radHi_ttbar_ktfac0p5_jjjjNp1 \
           AlpgenAutoPythia_P2012_radHi_ttbar_ktfac0p5_jjjjNp2 \
           AlpgenAutoPythia_P2012_radHi_ttbar_ktfac0p5_jjjjNp3 \
           AlpgenAutoPythia_P2012_radHi_ttbar_ktfac0p5_jjjjNp4inc \
           AlpgenAutoPythia_P2012_radLo_ttbar_ktfac2p0_jjjjNp0 \
           AlpgenAutoPythia_P2012_radLo_ttbar_ktfac2p0_jjjjNp1 \
           AlpgenAutoPythia_P2012_radLo_ttbar_ktfac2p0_jjjjNp2 \
           AlpgenAutoPythia_P2012_radLo_ttbar_ktfac2p0_jjjjNp3 \
           AlpgenAutoPythia_P2012_radLo_ttbar_ktfac2p0_jjjjNp4inc ; do
    list=list_${j}_${ll}.txt
    rm -f ${list}
    echo "  Making ${list} ..."
    for i in `cat ${file} | grep ${j} | grep _${ll}.root` ; do
      echo $i >> ${list}
    done
    if [ "$j" == "PowhegPythia_P2011C_ttbar_hdamp172p5_nonallhad.mcfixed_at180_combined_pdf_dijet" ] ; then
      echo "OK, splitting $j ..."
      ./Split.sh  ${list}
    fi

  done # ttbar samples
done # el um mc

