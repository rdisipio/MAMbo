#!/usr/bin/python

import os, sys
from ROOT import *
from array import array
 
from MAMboPlottingToolkit import *
_cans = []
_files = []
_corrs = []
_h = []


Paths = ['particle', 'reco', 'particle_not_reco', 'reco_not_particle', 'matched', 'reco_and_particle']

ObjNames = { #'topL' : 'leptonic pseudo-top','topH' : 'hadronic pseudo-top',
             'topL' : '#hat{t}_{l}',
             'topH' : '#hat{t}_{h}',
             'tt' : '#hat{t}_{l}#hat{t}_{h}' }
TitleNames = { 'pt' : 'p_{T}', 
               'm' : 'm', 
               'absrap' : '|y|', 
               'rapidity' : 'y' }
CorrNames = { 'eff' : 'Efficiency correction: f_{p!r}', 
              'match' : 'Misassignment correction f_{match}', 
              'acc' : 'Acceptance correction f_{r!p}' }

#################
def CheckAcc(acc,name):
    #vals = array('d', [0.,0.])
    x = Double(0.) # ROOT.Double
    eff = Double(0.)
    for i in range(0,acc.GetN()):
        #acc.GetPoint(i,vals[0],vals[1])
        acc.GetPoint(i,x,eff)
        if eff > 1.:
            print '  ERROR: acceptance=%4.2f in bin %i of %s!' % (eff,i,name)
    return

def GetTag(objname, varname):
    tag = ''
    #if objname.find('top') >= 0 and varname != "absrap": tag = '_0'
    #if objname.find('tt') >= 0 and varname == "pt": tag = '_5'
    return tag

def next_tmp(xmin, xmax, title = 'tmp', ymin=0., ymax=1.1,):
    print xmin, xmax
    h = TH2D("tmp%i" % (len(_h),), title, 100, xmin, xmax, 100, ymin, ymax) 
    h.SetStats(0)
    h.Draw()
    _h.append(h)

def PrintBinContent(histo):
    nx = histo.GetXaxis().GetNbins()
    line=''
    prefix = ''
    for binx in range(0,nx+2):
        line = '%s%s %4.1f' % (line, prefix, histo.GetBinContent(binx),)
        prefix=','
    print line

def GetMax(rfile, objname = 'topH', varname = 'pt', icorr = 0, basepath = '4j2b'):
    tag = GetTag(objname, varname)
    path =  '/' + basepath + '/' + objname + '/' + varname+tag
    h_part = rfile.Get(Paths[0] + path)
    return h_part.GetXaxis().GetXmax()
def GetMin(rfile, objname = 'topH', varname = 'pt', icorr = 0, basepath = '4j2b'):
    tag = GetTag(objname, varname)
    path =  '/' + basepath + '/' + objname + '/' + varname+tag
    h_part = rfile.Get(Paths[0] + path)
    return h_part.GetXaxis().GetXmin()


#################
def GetCorrection(rfile, pfile, objname = 'topH', varname = 'pt', icorr = 0, basepath = '4j2b'):
    tag = GetTag(objname, varname)
    path =  '/' + basepath + '/' + objname + '/' + varname+tag

    print '    Getting %s/%s/%s/%s' % (Paths[0],basepath,objname,varname+tag)

    # here access the special particle file:
    print '        %s' %(Paths[0] + path)
    h_part = pfile.Get(Paths[0] + path)

    # from now on, access reco file:

    print '        %s' %(Paths[1] + path)
    h_reco = rfile.Get(Paths[1] + path)

    #print '        %s' %(Paths[2] + path)
    #h_pnr = rfile.Get(Paths[2] + path)
    #print '        %s' %(Paths[3] + path)
    #h_rnp = rfile.Get(Paths[3] + path)

    print '        %s' %(Paths[4] + path)
    h_match = rfile.Get(Paths[4] + path)

    print '        %s' %(Paths[5] + path)
    h_rp = rfile.Get(Paths[5] + path)
    
#    xtitle=h_rp.GetXaxis().GetTitle()
#    ytitle=h_rp.GetYaxis().GetTitle()

    PrintBinContent(h_part)
    #PrintBinContent(h_pnr)

    print '  Making eff...'
    print '  RMS check: %f' % (h_part.GetRMS(),)
    print '  RMS check: %f' % ( h_rp.GetRMS(),)
    eff = MakeRatio( h_part,  h_match)
    #eff = MakeRatio( h_part,  h_pnr)
    print '  Making acc...'
    print '  RMS check: %f %f' % (h_reco.GetRMS(), h_rp.GetRMS())
    acc = MakeRatio( h_rp, h_reco)
    CheckAcc(acc,'%s %s' % (h_rp.GetName(),h_rp.GetTitle()) )
    print '  Making match...'
    print '  RMS check: %f %f' % (h_match.GetRMS(), h_rp.GetRMS())
    match = MakeRatio( h_match,  h_rp)

    if icorr == 0: return eff#,xtitle,ytitle
    if icorr == 1: return acc#,xtitle,ytitle
    if icorr == 2: return match#,xtitle,ytitle
    return

#################
def DrawCorrection(ll, rfile, pfile, objname = 'topH', varname = 'pt', icorr = 0, basepath = '4j2b'):
    print '  Drawing %s/%s/%s' % (basepath,objname,varname)

    corr = GetCorrection(rfile, pfile, objname, varname, icorr, basepath)

    tag = ''
    if icorr == 0: tag = 'eff'
    if icorr == 1: tag = 'acc'
    if icorr == 2: tag = 'match'

    canname = '%s_%s_%s_%s' % (tag,objname,varname,ll)
    can = TCanvas(canname, canname)
    _cans.append(can)
    can.cd()
    corr.SetLineColor(2)
    corr.SetMarkerColor(2)
    corr.SetMarkerSize(1)
    corr.SetMarkerStyle(20)

    xmin = GetMin(rfile, objname, varname, icorr, basepath)
    xmax = GetMax(rfile, objname, varname, icorr, basepath)

    xtitle = ObjNames[objname] + ' ' + TitleNames[varname]
    ytitle = ''

    title=CorrNames[tag] + ';' + xtitle + ';' + ytitle
    if icorr == 0:
        next_tmp(xmin, xmax, title, 0., 24.)
    else:
        next_tmp(xmin, xmax, title)
    corr.Draw('P')
    _corrs.append(corr)
    can.Print('eps/' + canname + '.eps')
    can.Print('png/' + canname + '.png')

####################################################
####################################################
####################################################

ljets = [ 'll', 'el', 'mu']
#ljets = [ 'el', 'mu']
#ljets = [ 'el' ]
#ljets = [ 'mu' ]
#ljets = [ 'll' ]

ftag='_Jan2015'

for ll in ljets:

    rfile = TFile('/afs/cern.ch/user/q/qitek/qitek/TopResolved_8TeV_MAMbo/MAMbo/run/histograms_PowHeg_%s%s.root' % (ll,ftag), 'read')
#    rfile = TFile('/afs/cern.ch/user/q/qitek/qitek/TopResolved_8TeV_MAMbo/MAMbo/run/histograms_PowHeg_%s_halves.root' % (ll,), 'read')
    _files.append(rfile)
    print 'Opened file %s' % (rfile.GetName(),)

    pfile = TFile('/afs/cern.ch/user/q/qitek/qitek/TopResolved_8TeV_MAMbo/MAMbo/run/histograms_PowHeg_%s_particle.root' % (ll,), 'read')
    _files.append(pfile)
    print 'Opened file %s' % (pfile.GetName(),)

    Obj = ['topH', 'topL', 'tt']
    Var = ['pt', 'm', 'absrap']

    for obj in Obj:
        for var in Var:
            DrawCorrection(ll, rfile, pfile, obj, var, 0)
            DrawCorrection(ll, rfile, pfile, obj, var, 1)
            DrawCorrection(ll, rfile, pfile, obj, var, 2)


    
#
gApplication.Run()

