#!/usr/bin/python

from ROOT import *

hnames = ['AbsoluteDiffXs',
          'TheoryXs_abs',
          'RelativeDiffXs',
          'TheoryXs_rel']
gpath = '/afs/cern.ch/user/d/disipio/work/public/ttbar_diffxs_8TeV/unfolded/parton/'

##############################################################

def CheckXsect(flist):
    dintegrals = {}
    for fname in flist:
        print 'prosessing %s' % (gpath + fname,)
        rfile = TFile(gpath + fname, 'read')
        integrals = []
        for hname in hnames:
            print '  prosessing %s' % (hname,)
            hist = rfile.Get(hname)
            integral = hist.Integral(1, hist.GetXaxis().GetNbins(), 'width')
            integrals.append(integral)
        print '*** processed %s' % fname
        dintegrals[fname] = integrals
    for item in dintegrals:
        print '=== %s === ' % (item,)
        print '  ', dintegrals[item]
            
##############################################################
##############################################################
##############################################################

flist = [ 'difference_absPout_ll.central.root', 
          'difference_Chi_ttbar_ll.central.root',
          'difference_dPhi_ttbar_ll.central.root',
          'difference_HT_ttbar_ll.central.root',
          'difference_Pout_ll.central.root', 
          'difference_Yboost_ll.central.root', 
          'difference_z_ttbar_ll.central.root',
          'topH_absrap_ll.central.root',
          'topH_pt_ll.central.boosted.root',
          'topH_pt_ll.central.root', 
          'tt_absrap_ll.central.root', 
          'tt_m_ll.central.root',
          'tt_pt_ll.central.root' ]

CheckXsect(flist)
