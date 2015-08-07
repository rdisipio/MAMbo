#!/bin/sh

echo "Making predictions by MCFM"
root -l -b -q MakeTheoryHistoMCFM_Mtt.C+
root -l -b -q MakeTheoryHistoMCFM_pTt.C+
root -l -b -q MakeTheoryHistoMCFM_pTtt.C+


echo "Making top pT predictions by N. Kidonakis..."
root -l -b -q 'RebinTheory.C+("data/pttopnnloapprox7lhc173m.dat")'
root -l -b -q 'RebinTheory.C+("data/pttopnnloapprox7lhc1732m.dat")'
root -l -b -q 'RebinTheory.C+("data/pttopnnloapprox7lhc173halfm.dat")'
root -l -b -q 'RebinTheory.C+("data/pttopnnloapprox7lhc173mT.dat")'

echo "Making top Mtt predictions by Li Lin"
root -l -b -q 'RebinTheory_Mtt_NNLO.C+("data/Mtt_7000_Mtt_fin.dat", 0, false, 0, "recreate")'
root -l -b -q 'RebinTheory_Mtt_NNLO.C+("data/Mtt_7000_Mtt_fin.dat", 1, false, 0, "update")'
root -l -b -q 'RebinTheory_Mtt_NNLO.C+("data/Mtt_7000_Mtt_fin.dat", 2, false, 0, "update")'
root -l -b -q 'RebinTheory_Mtt_NNLO.C+("data/Mtt_7000_Mtt_fin.dat", 3, false, 0, "update")'
root -l -b -q 'RebinTheory_Mtt_NNLO.C+("data/Mtt_7000_Mtt_fin.dat", 4, false, 0, "update")'
root -l -b -q 'RebinTheory_Mtt_NNLO.C+("data/Mtt_7000_Mtt_fin.dat", 5, false, 0, "update")'
root -l -b -q 'RebinTheory_Mtt_NNLO.C+("data/Mtt_7000_Mtt_fin.dat", 6, false, 0, "update")'

echo "Making normalized top Mtt predictions by Li Lin"
root -l -b -q 'RebinTheory_Mtt_NNLO.C+("data/Mtt_7000_Mtt_norm.dat", 0, false, 0, "recreate")'
root -l -b -q 'RebinTheory_Mtt_NNLO.C+("data/Mtt_7000_Mtt_norm.dat", 1, false, 0, "update")'
root -l -b -q 'RebinTheory_Mtt_NNLO.C+("data/Mtt_7000_Mtt_norm.dat", 2, false, 0, "update")'
root -l -b -q 'RebinTheory_Mtt_NNLO.C+("data/Mtt_7000_Mtt_norm.dat", 3, false, 0, "update")'
root -l -b -q 'RebinTheory_Mtt_NNLO.C+("data/Mtt_7000_Mtt_norm.dat", 4, false, 0, "update")'
root -l -b -q 'RebinTheory_Mtt_NNLO.C+("data/Mtt_7000_Mtt_norm.dat", 5, false, 0, "update")'
root -l -b -q 'RebinTheory_Mtt_NNLO.C+("data/Mtt_7000_Mtt_norm.dat", 6, false, 0, "update")'

echo "Making pTtt predictions by Li Lin"
root -l -b -q 'RebinTheory_pTtt_NNLO.C+("data/pTtt_7000.dat", 0, false, 0, "recreate")'
root -l -b -q 'RebinTheory_pTtt_NNLO.C+("data/pTtt_7000.dat", 1, false, 0, "update")'
root -l -b -q 'RebinTheory_pTtt_NNLO.C+("data/pTtt_7000.dat", 2, false, 0, "update")'

ls -lart *.root