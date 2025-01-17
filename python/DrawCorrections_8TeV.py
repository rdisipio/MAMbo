#!/usr/bin/python

# jiri kvita, 2015

from ROOT import *
try:
    gROOT.LoadMacro( os.environ['MAMBODIR'] + "/share/rootlogon.C" )
    gROOT.LoadMacro( os.environ['MAMBODIR'] + "/share/AtlasUtils.C" )
    gROOT.LoadMacro( os.environ['MAMBODIR'] + "/share/AtlasStyle.C" )
except:
    gROOT.LoadMacro( "../share/rootlogon.C" )
    gROOT.LoadMacro( "../share/AtlasUtils.C" )
    gROOT.LoadMacro( "../share/AtlasStyle.C" )

from CorrStyle import *
import os, sys
from array import array

_cans = []
_files = []
_corrs = []



from MAMboPlottingToolkit_8TeV import *

Col = [kOrange+10, kBlue+2, kViolet-1 ]

Paths = ['particle', 'reco', 'matched_p', 'matched_r', 'reco_and_particle_r']

ObjNames = { #'topL' : 'leptonic pseudo-top','topH' : 'hadronic pseudo-top',

             'topL' : 't,lep',
             'topH' : 't,had',

             'WL' : 'W,lep',
             'WH' : 'W,had',

             #'topL' : '#hat{t}_{l}',
             #'topH' : '#hat{t}_{h}',
             #'WL' : '#hat{W}_{l}',
             #'WH' : '#hat{W}_{h}',
             'tt' : 't#bar{t}',
             #'tt' : '#hat{t}_{l}#hat{t}_{h}',
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
CorrNames = { 'eff' : 'Efficiency correction f_{eff}', 
              'match' : 'Matching correction f_{match}', 
              'acc' : 'Acceptance correction f_{acc}' }


#################
def ZeroErrorBars(corr):
    for i in range(0,corr.GetN()):
        corr.SetPointError(i,0., 0., 0., 0.)


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

    matrixPath =  '/' + basepath + '/' + objname + '/Matrix_reco_particle_' + varname+tag
    print 'Getting the matrix %s from file %s' % (Paths[1] + matrixPath, rfile.GetName(),)
    h_matrix = rfile.Get( Paths[1] + matrixPath )

    print '        %s' %(Paths[1] + path)
    h_reco = rfile.Get(Paths[1] + path)

    print '        %s' %(Paths[2] + path)
    # h_match_p = rfile.Get(Paths[2] + path)
    # fix by Marino:
    h_match_p = h_matrix.ProjectionY( "particle_recoandparticle", 1, h_matrix.GetNbinsY() )

    print '        %s' %(Paths[3] + path)
    # h_match_r = rfile.Get(Paths[3] + path)
    # 9.5.2016 JK:
    h_match_r = h_matrix.ProjectionX( "reco_recoandparticle", 1, h_matrix.GetNbinsX() )

    print '        %s' %(Paths[4] + path)
    h_rp = rfile.Get(Paths[4] + path)
    # fix by Marino:
    # removed by jk 9.5.2016
    
#    xtitle=h_rp.GetXaxis().GetTitle()
#    ytitle=h_rp.GetYaxis().GetTitle()

    PrintBinContent(h_part)
    #PrintBinContent(h_pnr)

    print '  Making eff...'
    #print '    RMS check: %f %f' % (h_part.GetRMS(),h_match_p.GetRMS(),)
    #print '    RMS check: %f ' % (h_part.GetRMS(),)
    #print '    RMS check: %f ' % (h_match_p.GetRMS(),)
    eff = MakeRatio( h_part,  h_match_p, False)

    print '  Making acc...'
    #print '    RMS check: %f ' % (h_reco.GetRMS(), )
    #print '    RMS check: %f ' % (h_rp.GetRMS(), )
    ###!!! acc = MakeRatio( h_rp, h_reco, False)
    ###!!!   CheckAcc(acc,'%s %s' % (h_rp.GetName(),h_rp.GetTitle()) )

    print '  Making match...'
    #print '    RMS check: %f ' % (h_rp.GetRMS())
    #print '    RMS check: %f ' % (h_match_r.GetRMS(), )
    ### !!! match = MakeRatio( h_match_r,  h_rp, False)

    # HACK for eff only!!!
    return eff,h_part,h_match_p

    if icorr == 0: return eff,h_part,h_match_p
    if icorr == 1: return acc,h_rp,h_reco
    if icorr == 2: return match,h_match_r,h_rp
    return

#################
def DrawCorrection(ll, rfiles, pfiles, objname = 'topH', varname = 'pt', icorr = 0, basepath = '4j2b'):
    print '  Drawing %s/%s/%s' % (basepath,objname,varname)

    tag = ''
    if icorr == 0: tag = 'eff'
    if icorr == 1: tag = 'acc'
    if icorr == 2: tag = 'match'

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
  
    opt = 'P'
    count = 0
    xmin = -1
    xmax = -1
    for rfile,pfile in zip(rfiles,pfiles):

        corr,h1,h2 = GetCorrection(rfile, pfile, objname, varname, icorr, basepath)

        col = Col[icorr]
        corr.SetLineColor(col)
        if count > 0:
            corr.SetLineWidth(2)
            corr.SetLineStyle(1+count)
            corr.SetMarkerStyle(0)
            corr.SetMarkerSize(0)
            corr.SetMarkerStyle(0)
            corr.SetMarkerColor(0)
            ZeroErrorBars(corr)
        else:
            corr.SetMarkerSize(1)
            corr.SetMarkerStyle(20)
            corr.SetMarkerColor(col)
            
        if count == 0:
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
        if count == 0:
            if icorr == 0:
                tmp = next_tmp(xmin, xmax, title, 0., 24.)
                #tmp.GetXaxis().SetTitle(xtitle)
                SetStyle(tmp, xtitle, ytitle)
            else:
                tmp = next_tmp(xmin, xmax, title)
                #tmp.GetXaxis().SetTitle(xtitle)
                SetStyle(tmp, xtitle, ytitle)

        #tmp.GetYaxis().SetTitleOffset(1.8)
        tmp.GetXaxis().SetNdivisions(505)
	#tmp.GetXaxis().SetLabelFont(43)
	#tmp.GetXaxis().SetLabelSize(15)

        SetStyle(corr, xtitle, ytitle)

        corr.Draw(opt)
        _corrs.append(corr)
        opt = 'L'
        count = count+1

    ATLAS_LABEL(0.16, 0.88, kBlack)
    myText(0.335, 0.88, kBlack, "Simulation");

    can.Print('eps/' + canname + '.eps')
    can.Print('png/' + canname + '.png')
    can.Print('pdf/' + canname + '.pdf')

####################################################
####################################################
####################################################

SetAtlasStyle()

gStyle.SetOptTitle(0)

# do not even try this unless in bartch mode;)
#ljets = [ 'co', 'el', 'mu']
# better use separate channels, due to the amount of plots:
#
#ljets = [ 'el' ]
#ljets = [ 'mu' ]
ljets = [ 'co' ]

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
#rpath='/afs/cern.ch/user/q/qitek/public/MCsigHalves/June27/'
#rpath='/afs/cern.ch/user/q/qitek/public/MCsigHalves/July17/'

# 8TeV re-run:
# for acc and match:
#rpath='/afs/cern.ch/user/q/qitek/public/TopDiff8/'
# for efficiency:
rpath='/afs/cern.ch/user/m/mromano/work/public/Rivet8TeV/MamboOutput/nominal/'
ppath='/afs/cern.ch/user/m/mromano/work/public/Rivet8TeV/MamboOutput/particle/'


GenNames = [ 'tt_diffxs_8TeV.mc.DiTop.110404',
             'tt_diffxs_8TeV.mc.DiTop.110408',
             'tt_diffxs_8TeV.mc.DiTop.110407'
         ]


channel='nofullhad'
# channel='ljets'

os.system('mkdir png eps pdf')
ROOT.gROOT.SetBatch(1)

for ll in ljets:


    rfiles = []
    pfiles = []

    for genname in GenNames:
        rfile = TFile('%s%s.%s.nominal.%s.histograms.root' % (rpath, genname, ll, channel), 'read')
        _files.append(rfile)
        rfiles.append(rfile)
        print 'Opened file %s' % (rfile.GetName(),)
        
        pfile = TFile('%s%s.%s.particle.%s.histograms.root' % (ppath, genname, ll, channel, ), 'read')
        _files.append(pfile)
        pfiles.append(pfile)
        print 'Opened file %s' % (pfile.GetName(),)


    Obj = ['topH', 
           #'topL',
           #'WH', 
           #'WL',
           #'tt'
    ]
    Var = ['pt'
           #, 'm', 
           #'absrap'
    ]

    for obj in Obj:
        for var in Var:
            # eff
            DrawCorrection(ll, rfiles, pfiles, obj, var, 0)
            # the rest:
            #DrawCorrection(ll, rfiles, pfiles, obj, var, 1)
            #DrawCorrection(ll, rfiles, pfiles, obj, var, 2)
            pass


    SpecObj = ['difference' ]
    SpecVar = ['Pout', 'absPout', 'z_ttbar', 'Yboost', 'Chi_ttbar', 'dPhi_ttbar', 'Salam_ttbar', 
               'HT_ttbar', 'HT_pseudo',
               'R_lb', 
               'R_Wb_lep', 
               'R_Wb_had',
               'R_Wt_lep', 
               'R_Wt_had' 
    ]

    for obj in SpecObj:
        for var in SpecVar:
            #DrawCorrection(ll, rfiles, pfiles, obj, var, 0)
            #DrawCorrection(ll, rfiles, pfiles, obj, var, 1)
            #DrawCorrection(ll, rfiles, pfiles, obj, var, 2)
            pass

    
#
#gApplication.Run()

