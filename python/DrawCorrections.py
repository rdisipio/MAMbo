#!/usr/bin/python

import os, sys
from ROOT import *

from MAMboPlottingToolkit import *
_cans = []
_files = []
_corrs = []
_h = []


Paths = ['particle', 'reco', 'particle_not_reco', 'reco_not_particle', 'matched', 'reco_and_particle']

def next_tmp(xmin, xmax):
    print xmin, xmax
    h = TH2D("tmp%i" % (len(_h),), "tmp", 100, xmin, xmax, 100, 0., 1.) 
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
    tag = ''
    if objname.find('top') >= 0 and varname != "absrap": tag = '_0'
    path =  '/' + basepath + '/' + objname + '/' + varname+tag
    h_part = rfile.Get(Paths[0] + path)
    return h_part.GetXaxis().GetXmax()
def GetMin(rfile, objname = 'topH', varname = 'pt', icorr = 0, basepath = '4j2b'):
    tag = ''
    if objname.find('top') >= 0 and varname != "absrap": tag = '_0'
    path =  '/' + basepath + '/' + objname + '/' + varname+tag
    h_part = rfile.Get(Paths[0] + path)
    return h_part.GetXaxis().GetXmin()



def GetCorrection(rfile, objname = 'topH', varname = 'pt', icorr = 0, basepath = '4j2b'):
    tag = ''
    if objname.find('top') >= 0 and varname != "absrap": tag = '_0'
    path =  '/' + basepath + '/' + objname + '/' + varname+tag

    print '    Getting %s/%s/%s/%s' % (Paths[0],basepath,objname,varname+tag)
    print '        %s' %(Paths[0] + path)
    h_part = rfile.Get(Paths[0] + path)
    h_reco = rfile.Get(Paths[1] + path)
    h_pnr = rfile.Get(Paths[2] + path)
    h_rnp = rfile.Get(Paths[3] + path)
    h_match = rfile.Get(Paths[4] + path)
    h_rp = rfile.Get(Paths[5] + path)
    

    PrintBinContent(h_part)
    PrintBinContent(h_pnr)

    print '  RMS: %f %f' % (h_part.GetRMS(), h_pnr.GetRMS())

    eff = MakeRatio( h_part,  h_pnr)
    acc = MakeRatio( h_rnp, h_reco)
    match = MakeRatio( h_match,  h_rp)

    if icorr == 0: return eff
    if icorr == 1: return acc
    if icorr == 2: return match
    return

def DrawCorrection(ll, rfile, objname = 'topH', varname = 'pt_0', icorr = 0, basepath = '4j2b'):
    print '  Drawing %s/%s/%s' % (basepath,objname,varname)

    corr = GetCorrection(rfile, objname, varname, icorr, basepath)

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
    next_tmp(xmin, xmax)

    corr.Draw('P')
    _corrs.append(corr)
    can.Print(canname + '.eps')
    can.Print(canname + '.png')

####################################################

ljets = [ 'el', 'mu']

for ll in ljets:

    rfile = TFile('/afs/cern.ch/user/q/qitek/qitek/TopResolved_8TeV_MAMbo/MAMbo/run/histograms_PowHeg_%s.root' % (ll,), 'read')
    _files.append(rfile)
    print 'Opened file %s' % (rfile.GetName(),)

    Obj = ['topH', 'topL', 'tt']
    Var = ['pt', 'pt', 'm', 'absrap']

    for obj in Obj:
        for var in Var:
            DrawCorrection(ll, rfile, obj, var, 1)
            DrawCorrection(ll, rfile, obj, var, 2)


    
#
gApplication.Run()

