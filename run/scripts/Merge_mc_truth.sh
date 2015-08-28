#!/bin/sh

tag=_ljets
#tag=_particle_ljets
#tag=_particle
#tag=_incl

for ll in el mu ; do
  hadd histograms_PowHeg_${ll}_particle${tag}.root histograms_PowHeg_${ll}_particle_a?${tag}.root
done

hadd histograms_PowHeg_co_particle${tag}.root histograms_PowHeg_el_particle${tag}.root histograms_PowHeg_mu_particle${tag}.root

