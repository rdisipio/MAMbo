#!/bin/sh


#tag="_incl"
tag="_ljets"

#tag="_7TeVpst"
#tag="_noMonoJetW"
#tag="_boostedW"


for half in 0 1 ; do
  echo "half${half}${tag}"
  for ll in el mu ; do
    echo "  ${ll}"
    hadd histograms_PowHeg_${ll}_half${half}${tag}.root histograms_PowHeg_${ll}_half${half}${tag}_a?.root
  done
done

for ll in el mu ; do
  echo "${ll}"
  hadd histograms_PowHeg_${ll}${tag}.root histograms_PowHeg_${ll}_half0${tag}.root histograms_PowHeg_${ll}_half1${tag}.root
done

for half in 0 1 ; do
  hadd histograms_PowHeg_co_half${half}${tag}.root histograms_PowHeg_el_half${half}${tag}.root histograms_PowHeg_mu_half${half}${tag}.root
done


for ll in el mu ; do
  hadd histograms_PowHeg_${ll}${tag}.root histograms_PowHeg_${ll}_half0${tag}.root histograms_PowHeg_${ll}_half1${tag}.root
done

hadd histograms_PowHeg_co${tag}.root histograms_PowHeg_el${tag}.root histograms_PowHeg_mu${tag}.root



