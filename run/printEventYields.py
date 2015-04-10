#!/usr/bin/env python

import os, sys
from ROOT import *

analysis = "TTbarResolved_resolved"
syst = "nominal"

basedir = os.environ['MAMBODIR'] + "/run/output/" + analysis + "/" + syst + "/"

hname_wgt = "LPLUSJETS_cutflow_reco_weighted"
hname_unw  = "LPLUSJETS_cutflow_reco_unweight" 

channels = [ 'el', 'mu' ]
samples = [ 'Data', 'ttbar', 'Single top', 'W+jets', 'Z+jets', 'Diboson', 'Fake Lep.', 'Tot. Bkg', 'Expected' ]

flist = {
'el' : {
'Data'       : "tt_diffxs_8TeV.data.Egamma.el.histograms.root",
'ttbar'      : "tt_diffxs_8TeV.mc.DiTop.110404.el.nominal.histograms.root",
'Single top' : "tt_diffxs_8TeV.mc.SingleTop.el.nominal.histograms.root",
'W+jets'     : "tt_diffxs_8TeV.mc.Wjets.el.nominal.histograms.root",
'Z+jets'     : "tt_diffxs_8TeV.mc.Zjets.el.nominal.histograms.root",
'Diboson'    : "tt_diffxs_8TeV.mc.Diboson.el.nominal.histograms.root",
'Fake Lep.'  : "tt_diffxs_8TeV.qcd.Egamma.el.nominal.histograms.root",
'Tot. Bkg'   : "tt_diffxs_8TeV.mc.Background.el.nominal.histograms.root",
'Expected'   : "tt_diffxs_8TeV.mc.Expected.el.nominal.histograms.root",
},
'mu' : {
'Data'       : "tt_diffxs_8TeV.data.Muons.mu.histograms.root",
'ttbar'      : "tt_diffxs_8TeV.mc.DiTop.110404.mu.nominal.histograms.root",
'Single top' : "tt_diffxs_8TeV.mc.SingleTop.mu.nominal.histograms.root",
'W+jets'     : "tt_diffxs_8TeV.mc.Wjets.mu.nominal.histograms.root",
'Z+jets'     : "tt_diffxs_8TeV.mc.Zjets.mu.nominal.histograms.root",
'Diboson'    : "tt_diffxs_8TeV.mc.Diboson.mu.nominal.histograms.root",
'Fake Lep.'  : "tt_diffxs_8TeV.qcd.Muons.mu.nominal.histograms.root",
'Tot. Bkg'   : "tt_diffxs_8TeV.mc.Background.mu.nominal.histograms.root",
'Expected'   : "tt_diffxs_8TeV.mc.Expected.mu.nominal.histograms.root",
}
}

bin = 9
if len(sys.argv) > 1: bin = int(sys.argv[1])

for ch in channels:
  print "channel: %s+jets" % ch
  for sample in samples:
        fname = flist[ch][sample]
        infile = TFile.Open( basedir + fname )
        h_unw = infile.Get( hname_unw )
        h_wgt = infile.Get( hname_wgt )

#        print "%20s %.0f" % ( sample, h_wgt.GetBinContent( bin ) )
        print "%20s %10.0f / %.0f" % ( sample, h_unw.GetBinContent( bin ), h_wgt.GetBinContent( bin ) )
  print
