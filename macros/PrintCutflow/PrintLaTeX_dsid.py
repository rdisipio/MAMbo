#!/usr/bin/python

# jk 22.12.2015

import os, sys, math

from ROOT import *

path='/raid7_atlas2/qitek/mambo_out/nominal/'
# path = '/afs/cern.ch/user/m/mromano/public/Diff13TeV/cutflow/root/'
# path = '/afs/cern.ch/work/q/qitek/nominal/'


ljets = ['el', 'mu']
topos = {'resolved' : '4j2b_cutflow',
         # 'boosted' : '1fj0b_cutflow' 
}

for topo in topos:

  for ljet in ljets:
    print '=== %s %s ===' % (topo,ljet,)
    fnamelist = [ ]
    phys='Zjets'
    for dsid in os.popen('cat ../../run/scripts_ttdiffxs_13TeV_ljets/%s.run' % (phys,)):
      ### STEERING!!!
      rfname='histograms_PowHeg_%s_%s.root' % (dsid[:-1],ljet,)
      fnamelist.append(rfname)


    flist = []
    histos = []

    print ' Cut name / dsid ',
    for fname in fnamelist:
        if fname == fnamelist: #[-1]:
          endl = ''
        print ' & %s ' % (fname.replace('.root', '').replace('histograms_PowHeg_','').replace('_el','').replace('_mu',''),),
        rfile = TFile(path + fname, "read")
        flist.append(rfile)

        ### !!! to move to passed_*cutflow_mc for MC !!!!
        ### 'passed_' + topo + '_' + ljet +'_' + topos[topo]# + '_scale_factors'

        # 25.5.2016
        #hname = 'LPLUSJETS_cutflow_reco_unweight' 
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
        print ' & %3.3f' % (histos[isample].GetBinContent(i), ),
      print ' \\\\ '
