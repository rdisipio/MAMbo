#!/bin/bash

echo "Making top pT predictions by N. Kidonakis..."
root -l -b -q 'RebinTheory_pTt_aNNLO.C+("data/ptaNNNLO8lhc173.3m.dat")' >& log_pTt_m.txt
root -l -b -q 'RebinTheory_pTt_aNNLO.C+("data/ptaNNNLO8lhc173.3halfm.dat")' >& log_pTt_halfm.txt
root -l -b -q 'RebinTheory_pTt_aNNLO.C+("data/ptaNNNLO8lhc173.3-2m.dat")' >& log_pTt_2m.txt


echo "Making predictions by Li Lin..."
root -l -b -q 'RebinTheory_pTtt_NNLO.C+("data/pTtt_8000.dat", 0, false, 0, "recreate")' >& log_pTtt.txt
root -l -b -q 'RebinTheory_yt_aNNLO.C+' >& log_yt.txt
root -l -b -q 'RebinTheory_mtt_NNLO.C+' >& log_mtt.txt


echo "Making predictions by DiffTop..."
root -l -b -q 'RebinTheory_yt_difftop.C+' >& log_yt_difftop.txt
root -l -b -q 'RebinTheory_pTt_difftop.C+' >& log_pTt_difftop.txt


ls -lart *.root
