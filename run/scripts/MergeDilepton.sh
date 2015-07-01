#!/bin/sh

for ll in el mu ; do
  hadd histograms_PowHeg_${ll}_dilepton.root histograms_PowHeg_${ll}_dilepton_a?.root
done
hadd histograms_PowHeg_co_dilepton.root histograms_PowHeg_el_dilepton.root histograms_PowHeg_mu_dilepton.root
