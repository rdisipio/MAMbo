#!/usr/bin/python

# jk 22.12.2015

import os, sys, math

from ROOT import *

#path = '/afs/cern.ch/work/m/mromano/public/Diff13TeV/output/'
path = '/afs/cern.ch/work/q/qitek/nominal/'

ljets = ['el', 'mu', 'co']
label = ['\\ejets{}', '\mujets{}', '\\ljets{}']


#ljets = [ 'co']
topos = {'resolved' : '4j2b', 
         #'boosted' : '1fj1b' 
}


for topo in topos:

  lines = []
  

  line = ''
  il = 0
  for ljet in ljets:
    stop = ' & '
    if ljet == ljets[-1]:
      stop = '\\\\n'
    line = line + ' %s &' % (label[il],)
    il = il + 1
  lines.append(line + ' \\\\\n')
  

  il = 0
  ip = 0
  for ljet in ljets:
    stop = ' & '
    if ljet == ljets[-1]:
      stop = '\\\\'
    line = 'Sample & '
    '=== %s %s ===' % (topo,label[il],)
    fnamelist = [ ['Diboson' + '_' + ljet, 'Diboson'],
                  ['Stop' + '_' + ljet, 'singletop'],
                  ['Wjets' + '_' + ljet, '$W$+jets'],
                  ['Zjets' + '_' + ljet, '$Z$+jets'],
                  ['ttV' + '_' + ljet, '$t\\bar{t}+V$'],
                  ['histograms_PowHeg_'+ ljet, '$t\\bar{t}$'],
                  #['tt_diffxs_13TeV.qcd.Main.AllPeriod.' + ljet + '.Resolved.histograms', 'Multijet'],
                  #['tt_diffxs_13TeV.mc.DiTop.410000.' +  ljet + '.nominal.nofullhad.histograms', '$\\ttbar{}$ signal'],
                  #['tt_diffxs_13TeV.data.Main.AllPeriod.' + ljet + '.Resolved.histograms', 'Data'] 
    ]


    flist = []
    histos = []

    #print ' Cut name ',
    sum = 0.
    ip = 0
    for fnamel in fnamelist:
        fname = fnamel[0]
        if fname == fnamelist[-1][0]:
          endl = ''
        rfile = TFile(path + fname + '.root', "read")
        flist.append(rfile)


        if il == 0:
          lines.append('')


        ### !!! to move to passed_*cutflow_mc for MC !!!!
        hname = 'reco/' + topos[topo] + '/topH/pt'
        histo = rfile.Get(hname)
        histos.append(histo)
        val = histo.Integral(-1,-1)
        if fnamel[1].find('Data') < 0:
          sum = sum + val
          if il == 0:
            lines[ip] = lines[ip] + ( ' %s & ' % (fnamel[1], ) )
          lines[ip] = lines[ip] + ( ' %4.1f %s ' % (val,stop,) )
        else: 
          if il == 0:
            lines[ip] = lines[ip] + ( '\\hline %s &' % (fnamel[1],) )
          lines[ip] = lines[ip] + ( ' %4.0f %s' % (val,stop,) )
        print ip
        ip = ip + 1

    ip = ip+1
    if il == 0:
      lines.append(' %s & ' % ('Total prediction',) )
    lines[ip] = lines[ip] + '  %4.1f %s' % ( sum,stop)

    il = il + 1
   
  # print lines
  for ln in lines:
    print ln
