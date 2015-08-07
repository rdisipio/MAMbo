#!/bin/bash


rm *.so *_C.d
rm Theory.C ; ln -s Theory_oldfixed.C Theory.C ; ./RunTheory.sh ; mv *.root oldfixed/

rm *.so *_C.d
rm Theory.C ; ln -s Theory_new.C Theory.C ; ./RunTheory.sh ; mv *.root new/

rm *.so *_C.d
rm Theory.C ; ln -s Theory_old.C Theory.C ; ./RunTheory.sh ; mv *.root orig/

root -l Cmp.C+
