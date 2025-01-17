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
               kMatch : 'match',
               kAccWithBoost : 'acc_withboost',
               kAccMatch   : 'accmatch',
               kEffNoMatch   : 'effnomatch',
               kEffNoMatchWithBoost   : 'effnomatch_withboost', }

kCorrNames = { kEff   : 'Efficiency #varepsilon',
               kAcc   : 'Acceptance correction f_{acc}', 
               kMatch : 'Matching correction f_{match}',
               kAccWithBoost : 'Acceptance correction f_{acc}, incl. boost',
               kAccMatch   : 'Acceptance and matching correction f_{acc && match}',
               kEffNoMatch   : 'Efficiency #varepsilon, no match',
               kEffNoMatchWithBoost   : 'Efficiency #varepsilon, no match, incl. boost', }


Col = [kOrange+10, kBlue+2, kViolet-1, kGreen+2, kMagenta, kRed+2, kBlack]

ObjNames = { #'top_lep' : 'leptonic pseudo-top','top_had' : 'hadronic pseudo-top',
             '' : '',
             'top_lep' : 't,lep',
             'top_had' : 't,had',

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

               'top_had_cosThetaStar' : [  'cos#theta^{*}_{t,had}', '' ],
               'top_lep_cosThetaStar' : [  'cos#theta^{*}_{t,lep}', '' ],
               
               'Pout' : [  'p_{out}', '[GeV]' ],
               'absPout' : [  '|p_{out}|', '[GeV]' ],
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
def GetCorrection(ll, rfile, pfile, objname = 'top_had', varname = 'pt', icorr = kEff, basepath = '4j2b'):

    # naming convention for histogram identifiers:
    # h_PASEDWHATCUTS_BINNEDINWHAT
    # where PASEDWHATCUTS = reco, part, recopart, recopartmatch
    #       BINNEDINWHAT = p...particle, r...reco
    
    particle_name =  '/particle/' + basepath + '_' + ll + '/PseudoTop_Particle_' + objname + '_' + varname
    particle_name= particle_name.replace('__', '_')
    # here access particle spectrum:
    print '  accessing particle histogram %s' % (particle_name, )
    h_part_p = pfile.Get(particle_name)

    # now on, access the migration matrix, no matching:
    matrix_name = '/reco/' + basepath + '_' + ll + '/PseudoTop_Particle_' + objname + '_' + varname + '_vs_PseudoTop_Reco_' + objname + '_' + varname
    matrix_name= matrix_name.replace('__', '_')
    print 'Getting the matrix %s from file %s' % (matrix_name, rfile.GetName())
    h_matrixMatch = rfile.Get(matrix_name)


    # now on, access the migration matrix, no matching, incl. boosted:
    matrixWithBoost_name = '/reco/' + basepath + '_' + ll + '_withboost/PseudoTop_Particle_' + objname + '_' + varname + '_vs_PseudoTop_Reco_' + objname + '_' + varname
    matrixWithBoost_name= matrixWithBoost_name.replace('__', '_')
    print 'Getting the matrix %s from file %s' % (matrixWithBoost_name, rfile.GetName())
    h_matrixMatch_withBoost = rfile.Get(matrixWithBoost_name)

    h_recopartWithBoost_p = h_matrixMatch_withBoost.ProjectionY( "particle_recoandparticleYwithboost", 1, h_matrixMatch.GetNbinsY() )   
    
    
    reco_name =  '/reco/' + basepath + '_' + ll + '/PseudoTop_Reco_' + objname + '_' + varname
    reco_name = reco_name.replace('__', '_')
    print '  accessing reco histogram %s' % (reco_name, )
    h_reco_r = rfile.Get(reco_name)

    reco_name_withBoost =  '/reco/' + basepath + '_' + ll + '+_withboost/PseudoTop_Reco_' + objname + '_' + varname
    reco_name_withBoost = reco_name.replace('__', '_')
    print '  accessing reco histogram %s' % (reco_name_withBoost, )
    h_recoWithBoost_r = rfile.Get(reco_name_withBoost)

    
    # pass particle and reco, matched, binned in particle, as a projection of the migration matrix:
    print 'Making the y projection...'
    h_recopartmatch_p = h_matrixMatch.ProjectionY( "particle_recoandparticleYmatch", 1, h_matrixMatch.GetNbinsY() )   
    
    # access the migration matrix, incl. matching:
    matrixmatch_name = '/reco/' + basepath + '_' + ll + '_match/PseudoTop_Particle_' + objname + '_' + varname + '_vs_PseudoTop_Reco_' + objname + '_' + varname
    matrixmatch_name = matrixmatch_name.replace('__', '_')
    print 'Getting the matched matrix %s from file %s' % (matrixmatch_name, rfile.GetName())
    h_matrixmatch = rfile.Get(matrix_name)

    # access the migration matrix, no matching
    matrix_name = '/reco/' + basepath + '_' + ll + '/PseudoTop_Particle_' + objname + '_' + varname + '_vs_PseudoTop_Reco_' + objname + '_' + varname
    matrix_name = matrix_name.replace('__', '_')
    print 'Getting the matrix %s from file %s' % (matrix_name, rfile.GetName())
    h_matrix = rfile.Get(matrix_name)

    
    # pass particle and reco, binned in particle, as a projection of the migration matrix:
    print 'Making the y projection...'
    h_recopart_p = h_matrix.ProjectionY( "particle_recoandparticleY", 1, h_matrix.GetNbinsY() )
 

    # does not seem to work...should not be Y projection??!!
    # h_recopartmatch_r = h_matrixmatch.ProjectionX( "reco_recoandparticleXmatch", 1, h_matrixmatch.GetNbinsX() )
    # OR, works for top had pT:
    recomatch_name =  '/reco/' + basepath + '_' + ll +'_match' + '/PseudoTop_Reco_' + objname + '_' + varname
    recomatch_name = recomatch_name.replace('__', '_')
    print '  accessing reco matched histogram %s' % (recomatch_name, )
    h_recopartmatch_r = rfile.Get(recomatch_name)

    
    # reco and particle, binned in reco:
    print 'Making the x projection...'
    h_recopart_r = h_matrixMatch.ProjectionX( "reco_recoandparticleXmatch", 1, h_matrixMatch.GetNbinsX() )
    
    #xtitle=h_recopart_r.GetXaxis().GetTitle()
    #ytitle=h_recopart_r.GetYaxis().GetTitle()

    ###PrintBinContent(h_part_p)
    #PrintBinContent(h_pnr)

    print '  Making eff...'
    #print '    RMS check: %f ' % (h_part_p.GetRMS(),)
    #print '    RMS check: %f ' % (h_recopartmatch_p.GetRMS(),)
    eff = MakeRatio( h_recopartmatch_p, h_part_p,  False)

    print '  Making effNoMatch...'
    effNoMatch = MakeRatio( h_recopart_p, h_part_p,  False)

    print '  Making effNoMatch_withboost...'
    effNoMatch_withboost = MakeRatio( h_recopartWithBoost_p, h_part_p,  False)
    
    print '  Making acc...'
    #print '    RMS check: %f %f' % (h_recopart_r.GetRMS(), h_reco_r.GetRMS())
    acc = MakeRatio( h_recopart_r, h_reco_r, False)
    CheckAcc(acc,'%s %s' % (h_recopart_r.GetName(),h_recopart_r.GetTitle()) )

    print '  Making match...'
    print '    RMS check: %f' % (h_recopartmatch_r.GetRMS(), )
    print '    RMS check: %f' % (h_recopart_r.GetRMS(), )
    match = MakeRatio( h_recopartmatch_r,  h_recopart_r, False)

    print '  Making acc with boosted...'
    acc_withboost = MakeRatio( h_recopart_r, h_recoWithBoost_r, False)

    print '  Making acc && match...'
    accmatch = MakeRatio( h_recopartmatch_r, h_reco_r, False)

    if icorr == kEff:                  return eff,                  h_part_p,          h_recopartmatch_p
    if icorr == kAcc:                  return acc,                  h_recopart_r,      h_reco_r
    if icorr == kMatch:                return match,                h_recopartmatch_r, h_recopart_r
    if icorr == kAccWithBoost:         return acc_withboost,        h_recopart_r,      h_recoWithBoost_r
    if icorr == kAccMatch:             return accmatch,             h_recopartmatch_r, h_reco_r
    if icorr == kEffNoMatch:           return effNoMatch,           h_part_p,          h_recopart_p
    if icorr == kEffNoMatchWithBoost:  return effNoMatch_withboost, h_part_p,          h_recopartWithBoost_p
        
    return

#################
def DrawCorrection(ll, rfiles, pfiles, objname = 'top_had', varname = 'pt', icorr = 0, basepath = '4j2b'):
    print '  Drawing %s/%s/%s' % (basepath,objname,varname)

    tag = kCorrs[icorr]

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

        corr,h1,h2 = GetCorrection(ll, rfile, pfile, objname, varname, icorr, basepath)

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
    myText(0.19, yy-yyoff, kBlack, "Resolved");

    #can.Print('eps/' + canname + '.eps')
    can.Print('png/' + canname + '.png')
    can.Print('pdf/' + canname + '.pdf')
    can.Print('C/' + canname + '.C' )

####################################################
####################################################
####################################################

SetAtlasStyle()

gStyle.SetOptTitle(0)

ljets = [ ###'ejet', 'mujet',
          'ljet' ]

ptag=''
ftag='nofullhad'

ppath='/afs/cern.ch/user/m/mromano/work/public/Diff13TeVPhase2/output/nominal'
rpath=ppath

GenNames = [ '410501', ]

os.system('mkdir C png eps pdf')
gROOT.SetBatch(1)

for ll in ljets:

    rfiles = []
    pfiles = []

    for genname in GenNames:
        rfile = TFile('%s/mc.%s.nominal.allplots.v109.root' % (rpath, genname), 'read')
        _files.append(rfile)
        rfiles.append(rfile)
        print 'Opened file %s' % (rfile.GetName(),)
        
        pfile = rfile ### TFile('%stt_diffxs_13TeV.mc.%s.%s.nocut.%s.histograms.root' % (ppath, genname, ll, ftag, ), 'read')
        _files.append(pfile)
        pfiles.append(pfile)
        print 'Opened file %s' % (pfile.GetName(),)

    Obj = ['top_had', 
           'top_lep',
           'leading_top',
           'subleading_top',
           ### 'topHad', ? for klfitter stuff?
           #'WH', 
           #'WL',
           'ttbar'
    ]
    Var = [ 'y_coarse',
            'pt',
            'm', 
          
    ]

    for obj in Obj:
        for var in Var:
            if ( obj.find('_top') >= 0 or obj.find('top_') >= 0) and var == 'm':
                continue
            if var == 'y_coarse' and (  obj.find('top_had') <= 0 and obj.find('ttbar') <= 0 ):
                continue
            DrawCorrection(ll, rfiles, pfiles, obj, var, kEff)
            DrawCorrection(ll, rfiles, pfiles, obj, var, kAcc)
            DrawCorrection(ll, rfiles, pfiles, obj, var, kMatch)
            DrawCorrection(ll, rfiles, pfiles, obj, var, kAccWithBoost)
            DrawCorrection(ll, rfiles, pfiles, obj, var, kAccMatch)
            DrawCorrection(ll, rfiles, pfiles, obj, var, kEffNoMatch)
            DrawCorrection(ll, rfiles, pfiles, obj, var, kEffNoMatchWithBoost)
            pass


    SpecObj = ['' ]
    SpecVar = [#'top_had_cosThetaStar',
               #'top_had_cosThetaStar',
               'absPout', 'y_boost', 'chi_tt', 'deltaPhi_tt',
               'HT_tt',
    ]

    for obj in SpecObj:
        for var in SpecVar:
            DrawCorrection(ll, rfiles, pfiles, obj, var, kEff)
            DrawCorrection(ll, rfiles, pfiles, obj, var, kAcc)
            DrawCorrection(ll, rfiles, pfiles, obj, var, kMatch)
            DrawCorrection(ll, rfiles, pfiles, obj, var, kAccWithBoost)
            DrawCorrection(ll, rfiles, pfiles, obj, var, kAccMatch)
            DrawCorrection(ll, rfiles, pfiles, obj, var, kEffNoMatch)
            DrawCorrection(ll, rfiles, pfiles, obj, var, kEffNoMatchWithBoost)
            pass

    

# gApplication.Run()

