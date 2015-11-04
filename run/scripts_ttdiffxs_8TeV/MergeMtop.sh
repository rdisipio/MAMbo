#!/bin/sh


for ll in el mu ; do
  for mass in `cat lists/masses.txt` ; do
   hadd histograms_PowHeg_${ll}_particle_${mass}_ljets.root  histograms_PowHeg_${ll}_particle_${mass}_split_list_mtop_a??_incl.root
   hadd histograms_PowHeg_${ll}_ljets_${mass}.root  histograms_PowHeg_${ll}_incl_${mass}_split_list_mtop_a??.root
  done
done

for mass in `cat lists/masses.txt` ; do
 hadd histograms_PowHeg_co_particle_${mass}_ljets.root  histograms_PowHeg_el_particle_${mass}_ljets.root histograms_PowHeg_mu_particle_${mass}_ljets.root
 hadd histograms_PowHeg_co_ljets_${mass}.root  histograms_PowHeg_el_ljets_${mass}.root histograms_PowHeg_mu_ljets_${mass}.root
done

