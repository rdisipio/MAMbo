#!/usr/bin/python

# jk 22.12.2015

import os, sys, math

from ROOT import *

path = '/afs/cern.ch/work/m/mromano/public/Diff13TeV/output/'

#ljets = ['el', 'mu', 'co']
ljets = [ 'co']
topos = {'resolved' : '4j2b', 
         # 'boosted' : '1fj0b' 
}

for topo in topos:

  for ljet in ljets:
    print '=== %s %s ===' % (topo,ljet,)
    fnamelist = [ ['Diboson' + '_' + ljet, 'Diboson'],
                  ['Stop' + '_' + ljet, 'singletop'],
                  ['Wjets' + '_' + ljet, '$W$+jets'],
                  ['Zjets' + '_' + ljet, '$Z$+jets'],
                  ['tt_diffxs_13TeV.mc.DiTop.410000.' +  ljet + '.nominal.nofullhad.histograms', '$\\ttbar{}$ signal'],
                  ['tt_diffxs_13TeV.data.AllPeriod.' + ljet + '.Resolved.histograms', 'Data'] ]
    flist = []
    histos = []

    #print ' Cut name ',
    for fnamel in fnamelist:
        fname = fnamel[0]
        if fname == fnamelist[-1][0]:
          endl = ''
        rfile = TFile(path + fname + '.root', "read")
        flist.append(rfile)

        ### !!! to move to passed_*cutflow_mc for MC !!!!
        hname = 'reco/' + topos[topo] + '/topH/pt'
        histo = rfile.Get(hname)
        histos.append(histo)
        val = histo.Integral(-1,-1)
        if fnamel[1].find('Data') < 0:
          print ' %s & %4.1f \\\\\n' % (fnamel[1], val,),
        else: 
          print ' %s & %4.0f \\\\\n' % (fnamel[1], val,),
        

   
