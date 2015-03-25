#!/bin/sh

for ll in el mu ; do
  hadd histograms_PowHeg_${ll}_particle.root histograms_PowHeg_${ll}_particle_a?.root
done

hadd histograms_PowHeg_ll_particle.root histograms_PowHeg_el_particle.root histograms_PowHeg_mu_particle.root

