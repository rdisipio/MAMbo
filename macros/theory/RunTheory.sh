#!/bin/sh

echo "Making top pT predictions by N. Kidonakis..."
root -l -b -q 'RebinTheory_pTt_aNNLO.C+("data/ptaNNNLO8lhc173.3m.dat")'
root -l -b -q 'RebinTheory_pTt_aNNLO.C+("data/ptaNNNLO8lhc173.3halfm.dat")'
root -l -b -q 'RebinTheory_pTt_aNNLO.C+("data/ptaNNNLO8lhc173.3-2m.dat")'


echo "Making top Mtt predictions by Li Lin"
root -l -b -q 'RebinTheory_pTtt_NNLO.C+("data/pTtt_8000.dat", 0, false, 0, "recreate")'


ls -lart *.root
