#!/usr/bin/python

# jiri kvita, 2015, 2017

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

from MAMboPlottingToolkit import *


_cans  = []
_files = []
_corrs = []
_hists = []

kEff   = 0
kAcc   = 1
kMatch = 2
kAccWithBoost = 3
kAccMatch = 4
kEffNoMatch = 5
kEffNoMatchWithBoost = 6
 
kCorrs     = { kEff   : 'eff',
               kAcc   : 'acc',
}

kCorrNames = { kEff   : 'Efficiency #varepsilon',
               kAcc   : 'Acceptance correction f_{acc}', 
}

Col = [kOrange+10, kBlue+2, kViolet-1, kGreen+2, kMagenta, kRed+2, kBlack]

ObjNames = { #'lepTop' : 'leptonic pseudo-top','hadTop' : 'hadronic pseudo-top',
             '' : '',
             'lepTop' : 't,lep',
             'hadTop' : 't,had',

             'leading_top' : 't,lead',
             'subleading_top' : 't,subled',
             'ttbar' : 't#bar{t}',
             'difference' : ''}

TitleNames = { 'pt' : [  'p_{T}', '[GeV]' ], 
               'm' : [  'm', '[GeV]' ], 
               'absrap' : [  '|y|', '' ], 
               'rapidity' : [  'y', '' ],
               'y' : [  'y', '' ],
               'y_coarse' : [  'y', '' ],
               'y_fine' : [  'y', '' ],


               'hadTop_cosThetaStar' : [  'cos#theta^{*}_{t,had}', '' ],
               'lepTop_cosThetaStar' : [  'cos#theta^{*}_{t,lep}', '' ],
               
               #'Pout' : [  'p_{out}', '[GeV]' ],
               'Pout' : [  '|p_{out}|', '[GeV]' ],
               'z_ttbar' : [  'z_{t#bar{t}}', '' ],
               'y_boost' : [  'y_{boost}', '' ],
               'chi_tt' : [  '#chi_{t#bar{t}}', '' ],
               'deltaPhi_tt' : [  '#Delta#phi_{t#bar{t}}', '' ],
               'HT_tt' : [  'H_{T}^{t#bar{t}}', '[GeV]' ],
               }


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

#################
def GetCorrection(ll, rfile, pfile, objname = 'hadTop', varname = 'pt', icorr = kEff, basepath = '1fj1b', basepathreco = '1rcj1b', invert = False):

    # naming convention for histogram identifiers:
    # h_PASEDWHATCUTS_BINNEDINWHAT
    # where PASEDWHATCUTS = reco, part, recopart, recopartmatch
    #       BINNEDINWHAT = p...particle, r...reco
    
    particle_name =  '/particle/' + basepath + '/' + objname + '_boosted_rc_' + varname
    if invert == True:
        print 'OK, switching to inversed order naming convention!'
        particle_name =  '/particle/' + basepath + '/boosted_rc_' + varname
    particle_name= particle_name.replace('__', '_')
    # here access particle spectrum:
    print '  accessing particle histogram %s' % (particle_name, )
    h_part_p = pfile.Get(particle_name)

    reco_name =  '/reco/' + basepathreco + '_' + ll + '/' + objname + '_boosted_rc_' + varname
    if invert == True:
        print 'OK, switching to inversed order naming convention!'
        reco_name =  '/reco/' + basepathreco + '_' + ll + '/boosted_rc_' + varname
    reco_name = reco_name.replace('__', '_')
    print '  accessing reco histogram %s' % (reco_name, )
    h_reco_r = rfile.Get(reco_name)

      # access the migration matrix
    matrix_name = '/reco/' + basepathreco + '_' + ll + '/' + objname + '_boosted_rc_' + varname + '_vs_' + objname + '_boosted_rc_' + varname
    if invert == True:
        print 'OK, switching to inversed order naming convention!'
        matrix_name = '/reco/' + basepathreco + '_' + ll + '/boosted_rc_' + varname + '_vs_boosted_rc_' + varname
    matrix_name = matrix_name.replace('__', '_')
    print 'Getting the matrix %s from file %s' % (matrix_name, rfile.GetName())
    h_matrix = rfile.Get(matrix_name)

    
    # pass particle and reco, binned in particle, as a projection of the migration matrix:
    print 'Making the y projection...'
    h_recopart_p = h_matrix.ProjectionY( "particle_recoandparticleY", 1, h_matrix.GetNbinsY() )
 
    # reco and particle, binned in reco:
    print 'Making the x projection...'
    h_recopart_r = h_matrix.ProjectionX( "reco_recoandparticleX", 1, h_matrix.GetNbinsX() )
    
    print '  Making eff...'
    #print '    RMS check: %f ' % (h_part_p.GetRMS(),)
    #print '    RMS check: %f ' % (h_recopartmatch_p.GetRMS(),)
    eff = MakeRatio( h_recopart_p, h_part_p,  False)

     
    print '  Making acc...'
    #print '    RMS check: %f %f' % (h_recopart_r.GetRMS(), h_reco_r.GetRMS())
    acc = MakeRatio( h_recopart_r, h_reco_r, False)
    CheckAcc(acc,'%s %s' % (h_recopart_r.GetName(),h_recopart_r.GetTitle()) )

  
    if icorr == kEff:                  return eff,                  h_part_p,          h_recopart_p
    if icorr == kAcc:                  return acc,                  h_recopart_r,      h_reco_r
          
    return

#################
def DrawCorrection(ll, rfiles, pfiles, objname = 'hadTop', varname = 'pt', icorr = 0, basepath = '1fj1b', basepathreco = '1rcj1b', invert = False):
    print '  Drawing %s/%s/%s' % (basepath,objname,varname)

    tag = kCorrs[icorr]

    canname = '%s_%s_%s_%s' % (tag,objname,varname,ll)
    can = TCanvas(canname, canname, 1, 1, 800, 800)
    #can.Divide(2,1)
    _cans.append(can)

    can.cd()
  
    opt = 'P'
    count = 0
    xmin = -1
    xmax = -1
    for rfile,pfile in zip(rfiles,pfiles):

        corr,h1,h2 = GetCorrection(ll, rfile, pfile, objname, varname, icorr, basepath, basepathreco, invert)

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
            xmin = h1.GetXaxis().GetXmin()
            xmax = h1.GetXaxis().GetXmax()
        
        # HERE
        # xtitle = ObjNames[objname] + ' ' + TitleNames[varname]
        if ObjNames[objname] != 'difference':
            xtitle = TitleNames[varname][0] + '^{' + ObjNames[objname] + '} ' + TitleNames[varname][1]
        else:
            xtitle = TitleNames[varname][0] + ' ' + TitleNames[varname][1]
        xtitle = xtitle.replace('|y|^{t,lep}', '|y^{t,lep}|')
        xtitle = xtitle.replace('|y|^{t,had}', '|y^{t,had}|')
        xtitle = xtitle.replace('|y|^{t#bar{t}}', '|y^{t#bar{t}}|')
        print 'XTITLE=%s' % (xtitle,)
        ytitle = kCorrNames[icorr]

        title = kCorrNames[icorr] + ';' + xtitle# + ';' + ytitle
        if count == 0:
            if icorr == 0:
                tmp = next_tmp(xmin, xmax, title, 0., 1.)
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
        _hists.append(tmp)
        
        SetStyle(corr, xtitle, ytitle)

        corr.Draw(opt)
        _corrs.append(corr)
        opt = 'L'
        count = count+1

    yy = 0.865
    yyoff = 0.80-0.75
    ATLAS_LABEL(0.19, yy, kBlack)
    #myText(0.355, yy, kBlack, "Simulation Preliminary");
    myText(0.355, yy, kBlack, "Simulation Internal");
    #myText(0.355, yy, kBlack, "Simulation");
    myText(0.19, yy-yyoff, kBlack, "Boosted");

    #can.Print('eps_boosted/' + canname + '.eps')
    can.Print('png_boosted/' + canname + '.png')
    can.Print('pdf_boosted/' + canname + '.pdf')
    can.Print('C_boosted/' + canname + '.C' )

####################################################
####################################################
####################################################

SetAtlasStyle()

gStyle.SetOptTitle(0)

ljets = [ ###'ejet', 'mujet',
          'ljet' ]

ptag=''
ftag='nofullhad'

ppath='/afs/cern.ch/user/f/ffabbri/public/InputForJiri_Phase2/'
rpath=ppath

GenNames = [ '410501', #nominal
             '410511.AFII', #ifsr1
             '410512.AFII', #ifsr2
]

os.system('mkdir C_boosted png_boosted eps_boosted pdf_boosted')
gROOT.SetBatch(1)

for ll in ljets:

    rfiles = []
    pfiles = []

    for genname in GenNames[:1]:
        rfile = TFile('%s/mc.%s.nominal.v109.root' % (rpath, genname), 'read')
        _files.append(rfile)
        rfiles.append(rfile)
        print 'Opened file %s' % (rfile.GetName(),)
        
        pfile = rfile ### TFile('%stt_diffxs_13TeV.mc.%s.%s.nocut.%s.histograms.root' % (ppath, genname, ll, ftag, ), 'read')
        _files.append(pfile)
        pfiles.append(pfile)
        print 'Opened file %s' % (pfile.GetName(),)

    Obj = ['hadTop', 
           'lepTop',
           #'leading_top',
           #'subleading_top',
           ### 'topHad', ? for klfitter stuff?
           #'WH', 
           #'WL',
           'ttbar'
    ]
    Var = ['pt',
           'm', 
           'y',
    ]

    for obj in Obj:
        for var in Var:
            if ( obj.find('_top') >= 0 or obj.find('top_') >= 0) and var == 'm':
                continue
            if var == 'y' and (  obj.find('hadTop') <= 0 and obj.find('ttbar') <= 0 ):
                continue
            DrawCorrection(ll, rfiles, pfiles, obj, var, kEff)
            DrawCorrection(ll, rfiles, pfiles, obj, var, kAcc)
            pass


    SpecObj = ['' ]
    SpecVar = [#'hadTop_cosThetaStar',
               #'hadTop_cosThetaStar',
               'Pout',
               #'y_boost',
               'chi_tt',
               #'deltaPhi_tt',
               #'HT_tt',
    ]

    for obj in SpecObj:
        for var in SpecVar:
            DrawCorrection(ll, rfiles, pfiles, obj, var, kEff, invert = True)
            DrawCorrection(ll, rfiles, pfiles, obj, var, kAcc, invert = True)
            pass

    

# gApplication.Run()

