#!/usr/bin/python

import os, sys, math

from ROOT import *

path = '/afs/cern.ch/user/m/mromano/public/Diff13TeV/cutflow/root/'

ljets = ['ejets', 'mujets']

for ljet in ljets:
  print '=== %s ===' % (ljet,)
  fnamelist = [ 'Signal_scaled.root', 'allData.root']
  flist = []
  histos = []

  print ' Cut name ',
  for fname in fnamelist:
      if fname == fnamelist[-1]:
        endl = ''
      print ' & %s ' % (fname.replace('.root', ''),),
      rfile = TFile(path+fname, "read")
      flist.append(rfile)
      histo = rfile.Get('passed_resolved_ejets_4j2b_cutflow')
      histos.append(histo)
  print '\\\\ '

  #print flist
  #print histos
  ref=0
  for i in range(1, histos[ref].GetNbinsX()+1):
    print '%s ' % (histos[ref].GetXaxis().GetBinLabel(i), ),
    for isample in range(0,len(flist)):
      print ' & %7.0f' % (histos[isample].GetBinContent(i), ),
    print ' \\\\ '
