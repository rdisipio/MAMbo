#!/usr/bin/python

from ROOT import *


_h = []


def SetStyle(corr, xtitle, ytitle, size=0.045, offset = 1.2):

    corr.GetYaxis().SetTitle(ytitle)
    corr.GetYaxis().SetTitleSize(size);
    corr.GetYaxis().SetTitleOffset(offset)

    corr.GetXaxis().SetTitle(xtitle)
    corr.GetXaxis().SetTitleSize(size);
    corr.GetXaxis().SetTitleOffset(offset)


def PrintBinContent(histo):
    nx = histo.GetXaxis().GetNbins()
    line=''
    prefix = ''
    for binx in range(0,nx+2):
        line = '%s%s %4.1f' % (line, prefix, histo.GetBinContent(binx),)
        prefix=','
    print line

def next_tmp(xmin, xmax, title = 'tmp', ymin=0., ymax=1.1,):
    print xmin, xmax
    h = TH2D("tmp%i" % (len(_h),), title, 100, xmin, xmax, 100, ymin, ymax) 
    h.SetStats(0)
    h.Draw()
    _h.append(h)
    return h
