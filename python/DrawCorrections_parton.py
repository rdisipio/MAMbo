#!/usr/bin/python

# jiri kvita, marino romano, 2015

from ROOT import *
try:
    gROOT.LoadMacro( os.environ['MAMBODIR'] + "/share/rootlogon.C" )
    gROOT.LoadMacro( os.environ['MAMBODIR'] + "/share/AtlasUtils.C" )
    gROOT.LoadMacro( os.environ['MAMBODIR'] + "/share/AtlasStyle.C" )
except:
    gROOT.LoadMacro( "../share/rootlogon.C" )
    gROOT.LoadMacro( "../share/AtlasUtils.C" )
    gROOT.LoadMacro( "../share/AtlasStyle.C" )

import os, sys
from array import array
from CorrStyle import *

_cans = []
_files = []
_corrs = []

    
from MAMboPlottingToolkit import *

Paths = ['particle', 'reco', 'matched_p', 'matched_r', 'reco_and_particle_r', 'parton']

ObjNames = { 'topL' : 't,lep',
             'topH' : 't,had',
             'WL' : 'W,lep',
             'WH' : 'W,had',
             #'topL' : 'leptonic pseudo-top','topH' : 'hadronic pseudo-top',
             #'WL' : 'W_{l}',
             #'WH' : 'W_{h}',
             'tt' : 't#bar{t}',
             'difference' : ''}


TitleNames = { 'pt' : [  'p_{T}', '[GeV]' ], 
               'm' : [  'm', '[GeV]' ], 
               'absrap' : [  '|y|', '' ], 
               'rapidity' : [  'y', '' ],
               'Pout' : [  'p_{out}', '[GeV]' ],
               'absPout' : [  '|p_{out}|', '[GeV]' ],
               'z_ttbar' : [  'z_{#hat{t}_{l}#hat{t}_{h}}', '' ],
               'Yboost' : [  'y_{boost}', '' ],
               'Chi_ttbar' : [  '#chi_{#hat{t}_{l}#hat{t}_{h}}', '' ],
               'dPhi_ttbar' : [  '#Delta#phi_{#hat{t}_{l}#hat{t}_{h}}', '' ],
               'Salam_ttbar' : [  'S_{#hat{t}_{l}#hat{t}_{h}}', '' ],
               'HT_ttbar' : [  'H_{T}^{t#bar{t}}', '[GeV]' ],
               'HT_pseudo' : [  'H_{T}^{pseudo}', '[GeV]' ],
               'R_lb' : [  '[p_{T}^{j1} + p_{T}^{j2}] / [ p_{T}^{b,lep} + p_{T}^{b,had}]', '' ],
               'R_Wb_had' : [  'p_{T}^{W,had} / p_{T}^{b,had}', '' ],
               'R_Wb_lep' : [  'p_{T}^{W,lep} / p_{T}^{b,lep}', '' ],
               'R_Wt_had' : [  'p_{T}^{W,had} / p_{T}^{t,had}', '' ],
               'R_Wt_lep' : [  'p_{T}^{W,lep} / p_{T}^{t,lep}', '' ],
               }

CorrNames = { 'eff' : 'Efficiency correction', 
#              'match' : 'Misassignment correction f_{match}', 
              'acc' : 'Acceptance correction f_{acc}' }

#################
def CheckAcc(acc,name):
    #vals = array('d', [0.,0.])
    x = Double(0.) # ROOT.Double
    eff = Double(0.)
    for i in range(0,acc.GetN()):
        #acc.GetPoint(i,vals[0],vals[1])
        acc.GetPoint(i,x,eff)
        if eff > 1.0001:
            print '  ERROR: acceptance=%4.2f in bin %i of %s!' % (eff,i,name)
    return

def GetTag(objname, varname):
    tag = ''
    #if objname.find('top') >= 0 and varname != "absrap": tag = '_0'
    #if objname.find('tt') >= 0 and varname == "pt": tag = '_5'
    return tag


def GetMax(rfile, objname = 'topH', varname = 'pt', icorr = 0, basepath = '4j2b'):
    tag = GetTag(objname, varname)
    path =  '/' + basepath + '/' + objname + '/' + varname+tag
    suffix = "_5"
    if path.find('absPout') >= 0:
        suffix = ''
    print 'GetMax taken from %s' % (Paths[0] + path + suffix,)
    h_part = rfile.Get(Paths[0] + path + suffix)
    return h_part.GetXaxis().GetXmax()

def GetMin(rfile, objname = 'topH', varname = 'pt', icorr = 0, basepath = '4j2b'):
    tag = GetTag(objname, varname)
    path =  '/' + basepath + '/' + objname + '/' + varname+tag
    suffix = "_5"
    if path.find('absPout') >= 0:
        suffix = ''
    print 'GetMin taken from %s' % (Paths[0] + path + suffix,)
    h_part = rfile.Get(Paths[0] + path + suffix)
    return h_part.GetXaxis().GetXmin()


#################
def GetCorrection(rfile, pfile, objname = 'topH', varname = 'pt', icorr = 0, basepath = '4j2b'):
    tag = GetTag(objname, varname)
    path =  '/' + basepath + '/' + objname + '/' + varname+tag

    print '    Getting %s/%s/%s/%s' % (Paths[0],basepath,objname,varname+tag)

    # here access the special particle file:
    print '        %s' %(Paths[0] + path)
    h_part = pfile.Get(Paths[0] + path)
    print '        %s' %(Paths[5] + path)
    suffix = "_5"
    if path.find('absPout') >= 0:
        suffix = ''
    hpath = Paths[5] + path + suffix
    print 'Trying to get %s' % (hpath,)
    h_partonTot = pfile.Get(hpath)

    # from now on, access reco file:

    print '        %s' %(Paths[1] + path)
    hpath = Paths[1] + path + suffix
    print 'Trying to get %s' % (hpath,)
    h_reco = rfile.Get(hpath)

    #print '        %s' %(Paths[4] + path)
    #h_rp = rfile.Get(Paths[4] + path)
    # fix by Marino:
    matrixPath =  '/' + basepath + '/' + objname + '/Matrix_reco_parton_' + varname+tag+suffix
    h_matrix = rfile.Get( Paths[1] + matrixPath )
    print h_matrix
    h_rp = h_matrix.ProjectionX( "reco_recoandparticle", 1, h_matrix.GetNbinsX() )
    print h_rp

    print '        %s' %(Paths[5] + path)
    h_partonReco = rfile.Get(Paths[5] + path + suffix)
    
#    xtitle=h_rp.GetXaxis().GetTitle()
#    ytitle=h_rp.GetYaxis().GetTitle()

    PrintBinContent(h_part)
    #PrintBinContent(h_pnr)

    # print '  Making eff...'
    # #print '    RMS check: %f %f' % (h_part.GetRMS(),h_match_p.GetRMS(),)
    # print '    RMS check: %f ' % (h_part.GetRMS(),)
    # print '    RMS check: %f ' % (h_match_p.GetRMS(),)
    # eff = MakeRatio( h_part,  h_match_p)
	

   
	
    print '  Making parton eff...'
    print '    RMS check: %f ' % (h_partonTot.GetRMS(),)
    print '    RMS check: %f ' % (h_partonReco.GetRMS(),)
    eff = MakeRatio( h_partonReco, h_partonTot  )

    print '  Making parton acc...'
    print '    RMS check: %f %f' % (h_rp.GetRMS(), h_reco.GetRMS())
    acc = MakeRatio( h_rp, h_reco)
    CheckAcc(acc,'%s %s' % (h_rp.GetName(),h_rp.GetTitle()) )

    if icorr == 0: return eff,h_partonTot,h_partonReco
    if icorr == 1: return acc,h_rp,h_reco
    return

#################
def DrawCorrection(ll, rfile, pfile, objname = 'topH', varname = 'pt', icorr = 0, basepath = '4j2b'):
    print '  Drawing %s/%s/%s' % (basepath,objname,varname)

    corr,h1,h2 = GetCorrection(rfile, pfile, objname, varname, icorr, basepath)

    tag = ''
    if icorr == 0: tag = 'eff'
    if icorr == 1: tag = 'acc'

    canname = '%s_%s_%s_%s' % (tag,objname,varname,ll)
    can = TCanvas(canname, canname, 1, 1, 800, 800)
    #can.Divide(2,1)
    _cans.append(can)

    #can.cd(1)
    #h1.SetMarkerColor(2)
    #m1 = h1.GetMaximum()
    #m2 = h2.GetMaximum()
    #if m1 > m2:
    #    h1.SetMaximum(m1)
    #else:
    #    h1.SetMaximum(m2)
    #h1.Draw();
    #h2.Draw("same");
    
    #can.cd(2)
    can.cd()
    corr.SetLineColor( kSpring - 7)
    corr.SetMarkerColor( kSpring - 7)
    corr.SetMarkerSize(1)
    corr.SetMarkerStyle(20)

    xmin = GetMin(rfile, objname, varname, icorr, basepath)
    xmax = GetMax(rfile, objname, varname, icorr, basepath)

    # HERE
    # xtitle = ObjNames[objname] + ' ' + TitleNames[varname]
    if ObjNames[objname] != 'difference':
        xtitle = TitleNames[varname][0] + '^{' + ObjNames[objname] + '} ' + TitleNames[varname][1]
    else:
        xtitle = TitleNames[varname][0] + ' ' + TitleNames[varname][1]

    print 'XTITLE=%s' % (xtitle,)
    ytitle = CorrNames[tag]

    title=CorrNames[tag] + ';' + xtitle# + ';' + ytitle
    if icorr == 0:
        tmp = next_tmp(xmin, xmax, title, 0., 0.1)
        SetStyle(tmp, xtitle, ytitle)
       # next_tmp(xmin, xmax, title, 0., 24.)
    else:
        tmp = next_tmp(xmin, xmax, title)
        SetStyle(tmp, xtitle, ytitle)

    tmp.GetYaxis().SetTitleOffset(1.3)
    tmp.GetXaxis().SetNdivisions(505)
    SetStyle(corr, xtitle, ytitle)
    corr.Draw('P')
    _corrs.append(corr)

    ATLAS_LABEL(0.16, 0.96, kBlack)
    myText(0.335, 0.96, kBlack, "Internal Simulation");

    can.Print('eps_parton/' + canname + '.eps')
    can.Print('png_parton/' + canname + '.png')
    can.Print('pdf_parton/' + canname + '.pdf')

####################################################
####################################################
####################################################

SetAtlasStyle()

ljets = [ 'co', 'el', 'mu']
#ljets = [ 'el', 'mu']
#ljets = [ 'el' ]
#ljets = [ 'mu' ]
#ljets = [ 'co' ]

ptag=''
ftag=''

#ptag='_incl'
#ftag='_incl'


#ptag='_fixed_new'
#ftag='_fixed_new'
#rpath = '/afs/cern.ch/work/q/qitek/TopResolved_8TeV_MAMbo/MAMbo/run/incl/'
#rpath='/home/qitek/qitek/public/MCsigHalves/OldWhad/'
#rpath='/home/qitek/qitek/public/MCsigHalves/NewWhad/'
#rpath='/home/qitek/qitek/public/MCsigHalves/NoDileptonInSignal/'
#rpath='/afs/cern.ch/user/q/qitek/public/MCsigHalves/incl/'

# ljets:
#rpath='/afs/cern.ch/user/q/qitek/public/MCsigHalves/June27/'
# ljets+dilepton, wrong!!!
# rpath='/afs/cern.ch/user/q/qitek/public/MCsigHalves/July17/'
# ljets+dilepton, wrong!!!
# rpath='/afs/cern.ch/user/q/qitek/public/MCsigHalves/Aug3/'

# ljets:
# corrupted: rpath='/afs/cern.ch/user/q/qitek/public/MCsigHalves/Aug7_ljets/'
rpath='/afs/cern.ch/user/q/qitek/public/MCsigHalves/Aug10_ljets/'


os.system('mkdir png_parton eps_parton pdf_parton')
ROOT.gROOT.SetBatch(0)

for ll in ljets:

    rfile = TFile('%shistograms_PowHeg_%s%s.root' % (rpath, ll, ftag, ), 'read')
#    rfile = TFile('%shistograms_PowHeg_%s_halves.root' % (rpath, ll, ), 'read')
    _files.append(rfile)
    print 'Opened file %s' % (rfile.GetName(),)

    pfile = TFile('%shistograms_PowHeg_%s_particle%s.root' % (rpath, ll, ptag, ), 'read')
    _files.append(pfile)
    print 'Opened file %s' % (pfile.GetName(),)

    Obj = ['topH', #'topL',
           #'WH', 
           #'WL',
           'tt']
    Var = ['pt', 'm', 
           'absrap']

    for obj in Obj:
        for var in Var:
            if obj.find('top') >= 0 and var == 'm':
                continue
            DrawCorrection(ll, rfile, pfile, obj, var, 0)
            DrawCorrection(ll, rfile, pfile, obj, var, 1)
            pass


    SpecObj = ['difference' ]
    SpecVar = ['Pout', 'absPout', 'z_ttbar', 'Yboost', 'Chi_ttbar', 'dPhi_ttbar',
               #'Salam_ttbar', 
               'HT_ttbar', 
               #'HT_pseudo',
               #'R_lb', 
               #'R_Wb_lep', 
               #'R_Wb_had',
               #'R_Wt_lep', 
               #'R_Wt_had' 
    ]

    for obj in SpecObj:
        for var in SpecVar:
            #DrawCorrection(ll, rfile, pfile, obj, var, 0)
            #DrawCorrection(ll, rfile, pfile, obj, var, 1)
            pass

    
#
gApplication.Run()

