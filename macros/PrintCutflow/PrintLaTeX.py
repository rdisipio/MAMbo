#!/usr/bin/python

# jk 22.12.2015

import os, sys, math

from ROOT import *

# path = '/afs/cern.ch/user/m/mromano/public/Diff13TeV/cutflow/root/'
path = '/afs/cern.ch/work/q/qitek/nominal/'


ljets = ['ejets', 'mujets']
topos = {'resolved' : '4j2b_cutflow',
         # 'boosted' : '1fj0b_cutflow' 
}

for topo in topos:

  for ljet in ljets:
    print '=== %s %s ===' % (topo,ljet,)
    fnamelist = [ 'Zjets_el.root', 'Zjets_mu.root', 'Zjets_co.root'
      #'Signal_scaled.root', 'allData.root'
    ]
    flist = []
    histos = []

    print ' Cut name ',
    for fname in fnamelist:
        if fname == fnamelist[-1]:
          endl = ''
        print ' & %s ' % (fname.replace('.root', ''),),
        rfile = TFile(path+fname, "read")
        flist.append(rfile)

        ### !!! to move to passed_*cutflow_mc for MC !!!!
        ### 'passed_' + topo + '_' + ljet +'_' + topos[topo]# + '_scale_factors'

        # 25.5.2016
        # hname = 'LPLUSJETS_cutflow_reco_unweight' 
        hname = 'LPLUSJETS_cutflow_reco_weighted' 

        #if fname.find('data') < 0 and fname.find('DATA') and fname.find('Data'):
        #  hname = hname + ''
        #print hname

        histo = rfile.Get(hname)
        histos.append(histo)
    print '\\\\ '

    #print flist
    #print histos
    ref=0
    for i in range(1, histos[ref].GetNbinsX()+1):
      cutname = histos[ref].GetXaxis().GetBinLabel(i)
      cutname = cutname.replace('_', '\_').replace('==', '$=$').replace('>=', r'$\geq$'), 
      print '%s ' % (cutname, ),
      for isample in range(0,len(flist)):
        print ' & %7.0f' % (histos[isample].GetBinContent(i), ),
      print ' \\\\ '
