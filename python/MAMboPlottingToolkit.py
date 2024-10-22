#!/usr/bin/env python

import os, sys

from ROOT import *
#import numpy


#########################################################


def Normalize( h, sf = 1.0, opt = "width" ):
    area = h.Integral( opt )

    if area == 0.:
       print "ERROR: trying to normalize histogram", h.GetName(), "which has zero area"

    h.Scale( sf / area )


#########################################################


def Poissonize( data ):
    '''converts a TH1 representing real data into a TGraphAsymmErrors with poissonized uncertainties'''

    chisq = TMath.ChisquareQuantile

    nbins = data.GetNbinsX()

    graph = TGraphAsymmErrors()
    SetTH1FStyle( graph, color=data.GetMarkerColor(), markerstyle=data.GetMarkerStyle() )

    for n in range( nbins ):
        x = data.GetBinCenter( n+1 )
        y = data.GetBinContent( n+1 )
        bw = data.GetBinWidth( n+1 )

        dy_u = 0.5 * chisq( 1. - 0.1586555, 2. * (y + 1) ) - y 
        dy_d = y - 0.5 * chisq( 0.1586555, 2. * y )

#        print "bin %i y = %f +%f -%f" % ( n, y, dy_u, dy_d )

        graph.SetPoint( n, x, y )
        graph.SetPointError( n, bw/2., bw/2., dy_d, dy_u )

    return graph


#########################################################


def RemoveNegativeBins_TH1( h ):
    nbins = h.GetNbinsX()
    for i in range(nbins):
       y = h.GetBinContent( i+1 )
       if y >= 0.: continue

       h.SetBinContent( i+1, 0. )


#########################################################


def HasVariableBinWidths_TH1( h ):
    hasVariableBinWidths = True
    bw_glob = None
    nbins = h.GetNbinsX()
    for i in range(nbins):
      bw = h.GetBinWidth( i+1 )
      if bw_glob == None:
         bw_glob = bw
      if not bw == bw_glob:
         return hasVariableBinWidths

    return not hasVariableBinWidths


def HasVariableBinWidths_graph( g ):
    hasVariableBinWidths = True
    bw_glob = None
    nbins = g.GetN()
    for i in range(nbins):
      bw  = g.GetErrorXlow(i) + g.GetErrorXhigh(i)
      if bw_glob == None:
         bw_glob = bw
      if not bw == bw_glob:
         return hasVariableBinWidths

    return not hasVariableBinWidths


#########################################################


def DivideByBinWidth_histogram( h ):
    nb = h.GetNbinsX()
    for i in range(nb):
       y = h.GetBinContent( i+1 )
       u = h.GetBinError( i+1 )
       bw = h.GetBinWidth( i+1 )

       h.SetBinContent( i+1, y/bw )
       h.SetBinError( i+1, u/bw )

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

def DivideByBinWidth_graph( g ):
    nb = g.GetN()
    x  = Double()
    y  = Double()
    
    for i in range(nb):
        g.GetPoint( i, x, y )
        bw  = g.GetErrorXlow(i) + g.GetErrorXhigh(i)
        eyl = g.GetErrorYlow(i)
        eyh = g.GetErrorYhigh(i)
  
        g.SetPoint( i, x, y / bw )
        g.SetPointError( i, bw/2., bw/2., eyl/bw, eyh/bw )

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

def DivideByBinWidth( hlist ):
    for sample, h in hlist.iteritems():

        print "h integral of %s before division: %f " % (h.GetName(),  h.Integral())

        if h.Class() in [ TH1F.Class(), TH1D.Class(), TH1I.Class() ]:
 #          if not HasVariableBinWidths_TH1(h): continue
           DivideByBinWidth_histogram( h )
        elif h.Class() in [ TGraph.Class(), TGraphErrors.Class(), TGraphAsymmErrors.Class() ]: 
#           if not HasVariableBinWidths_graph(h): continue
           DivideByBinWidth_graph( h )
        else:
           print "ERROR: cannot divide by bin widht. Object", h.GetName(), "is of an unknown class"

        print "h integral of %s after division: %f " % (h.GetName(),  h.Integral())

#########################################################


def MakeCanvas( split = 0.25 ):
    c = TCanvas( "DataPrediction", "Data/Prediction", 800, 800 )
    pad0 = TPad( "pad0","pad0",0, split+0.05,1,1,0,0,0 )
    pad0.SetLeftMargin( 0.16 )
    pad0.SetRightMargin( 0.05 )
    pad0.SetBottomMargin( 0. )
    #pad0.SetTopMargin( 0.14 )
    pad0.SetTopMargin( 0.05 )
    pad0.Draw()
    
    pad1 = TPad( "pad1","pad1",0,0,1, split,0,0,0 )
    pad1.SetLeftMargin( 0.16 )
    pad1.SetRightMargin( 0.05 )
    pad1.SetTopMargin( 0. )
    pad1.SetBottomMargin( 0. )
    pad1.SetGridy(1)
    pad1.SetTopMargin(0)
    pad1.SetBottomMargin(0.4)
    pad1.Draw()
    
    pad0.cd()
    return c, pad0, pad1


#########################################################


def MakeATLASLabel( x, y, status = "Internal", iLumi = "21", ECM = "8" ):
    ATLAS_LABEL( x, y, kBlack )

    myText( x+0.12, y, kBlack, status )

    text = "#int Ldt = %s fb^{-1}   #sqrt{s} = %s TeV" % ( iLumi, ECM )

    l = TLatex()
    l.SetTextSize(0.05); 
    l.SetNDC();
    l.SetTextColor(kBlack);
    l.DrawLatex( x, y-0.1, text);


#########################################################


def MakeLegend( params ):
    leg = TLegend( params['xoffset'], params['yoffset'], params['xoffset'] + params['width'], params['yoffset'] )
    leg.SetNColumns(1)
    leg.SetFillColor(0)
    leg.SetFillStyle(0)
    leg.SetBorderSize(0)
    leg.SetTextFont(72)
    leg.SetTextSize(0.04)#0.05)
    return leg


#########################################################


def SetTH1FStyle( h, color = kBlack, linewidth = 1, fillcolor = 0, fillstyle = 0, markerstyle = 21, markersize = 1.3 ):
    '''Set the style with a long list of parameters'''
    
    h.SetLineColor( color )
    h.SetLineWidth( linewidth )
    h.SetFillColor( fillcolor )
    h.SetFillStyle( fillstyle )
    h.SetMarkerStyle( markerstyle )
    h.SetMarkerColor( h.GetLineColor() )
    h.SetMarkerSize( markersize )


#########################################################


def SetAxesStyle( hlist ):
    for h in hlist:
        h.GetYaxis().SetLabelSize( 0.05 )
        h.GetYaxis().SetTitleOffset( 1.6 )
        h.GetYaxis().SetTitleSize( 0.05 )
        
        h.GetXaxis().SetLabelSize( 0 )


#########################################################


def SetMaximum( histograms, key = 'data', sfmax = 1.3, sfmin = 0. ):
    hmax = sfmax * histograms[key].GetMaximum()
    hmin = sfmin * histograms[key].GetMinimum()

    for h in histograms.values(): 
       h.SetMaximum( hmax )
       h.SetMinimum( hmin )


#########################################################


def DrawRatio( data, prediction, xtitle = "" ):
    #global frame, tot_unc, ratio
    
    if data.Class() in [ TGraph().Class(), TGraphErrors.Class(), TGraphAsymmErrors().Class() ]:
       n = data.GetN()
       x = Double()
       y = Double()
       data.GetPoint( 0, x, y )
       exl = data.GetErrorXlow( 0 )
       xmin = x - exl
       data.GetPoint( n-1, x, y )
       exh = data.GetErrorXhigh( n-1 )
       xmax = x + exh
    else:
       xmin = data.GetXaxis().GetXmin()
       xmax = data.GetXaxis().GetXmax()

    # tt diffxs 7 TeV: [ 0.4, 1.6 ]    
    frame = gPad.DrawFrame( xmin, 0.7, xmax, 1.3 )
    #frame = gPad.DrawFrame( xmin, 0.5, xmax, 1.5 )

    frame.GetXaxis().SetNdivisions(508)
    frame.GetYaxis().SetNdivisions(504)
    
    frame.GetXaxis().SetLabelSize( 0.12 )
    frame.GetXaxis().SetTitleSize( 0.14 )
    frame.GetXaxis().SetTitleOffset( 1.2 )
    
    frame.GetYaxis().SetLabelSize( 0.13 )
    frame.GetYaxis().SetTitle( "Data/Prediction" )
    frame.GetYaxis().SetTitleSize( 0.11 )
    frame.GetYaxis().SetTitleOffset( 0.5 )
    
    frame.GetXaxis().SetTitle( xtitle )

    frame.Draw()
    
    tot_unc = MakeUncertaintyBand( prediction )
    ratio   = MakeRatio( data, prediction )
    
    tot_unc.Draw( "e2 same" )
    ratio.Draw("p same" )
    
    gPad.RedrawAxis()

    return frame, tot_unc, ratio

#########################################################


def MakeUncertaintyBand( prediction ):
    unc = TGraphAsymmErrors()
    
    SetTH1FStyle( unc, color=kBlack, fillstyle=3004, fillcolor=kBlack, linewidth=0, markersize=0 )
    
    i = 0

    if prediction.Class() in [ TGraph().Class(), TGraphErrors.Class(), TGraphAsymmErrors().Class() ]:
       Npoints = prediction.GetN()
    else:
       Npoints = prediction.GetNbinsX()

    for n in range( Npoints ):
       if prediction.Class() in [ TGraph().Class(), TGraphErrors.Class(), TGraphAsymmErrors().Class() ]:
          x_mc = Double()
          y_mc = Double()
          prediction.GetPoint( n, x_mc, y_mc )
       else:
          x_mc = prediction.GetBinCenter(n+1)
          y_mc = prediction.GetBinContent(n+1)

       if y_mc == 0: continue
    
       unc.SetPoint( i, x_mc, 1.0 )
      
       if prediction.Class() in [ TGraph().Class(), TGraphErrors.Class(), TGraphAsymmErrors().Class() ]:  
          bw_l = prediction.GetErrorXlow( n )
          bw_h = prediction.GetErrorXhigh( n )
          err_y_lo = prediction.GetErrorYlow(n) / y_mc
          err_y_hi = prediction.GetErrorYhigh(n) / y_mc
       else:
          bw_l = prediction.GetBinWidth( n+1 ) / 2. 
          bw_h = prediction.GetBinWidth( n+1 ) / 2.
          err_y_lo = prediction.GetBinError( n+1 ) / y_mc
          err_y_hi = prediction.GetBinError( n+1 ) / y_mc

       unc.SetPointError( i, bw_l, bw_h, err_y_lo, err_y_hi )

       i += 1
  
    return unc


#########################################################


def MakeRatio( data, prediction, setgr = True ):
    ratio = TGraphAsymmErrors()
    
    if setgr:
        SetTH1FStyle( ratio, color=data.GetMarkerColor(), markerstyle=data.GetMarkerStyle() )
    
    if data.Class() in [ TGraph().Class(), TGraphErrors.Class(), TGraphAsymmErrors().Class() ]:
       nbins = data.GetN()
    else:
       nbins = data.GetNbinsX()

    i = 0
    for n in range( nbins ):
        x_mc = Double()
        y_mc = Double()
        x_data = Double()
        y_data = Double()

        if prediction.Class() in [ TGraph().Class(), TGraphErrors.Class(), TGraphAsymmErrors().Class() ]:
           prediction.GetPoint( n, x_mc, y_mc )
        else:
           x_mc = prediction.GetBinCenter( n+1 )
           y_mc = prediction.GetBinContent( n+1 )   
     
        if y_mc == 0.: continue

        if data.Class() in [ TGraph().Class(), TGraphErrors.Class(), TGraphAsymmErrors().Class() ]:
           data.GetPoint( n, x_data, y_data )
           bw = data.GetErrorXlow(n) + data.GetErrorXhigh(n)
           dy_u = data.GetErrorYhigh(n)
           dy_d = data.GetErrorYlow(n)
        else:    
           x_data = data.GetBinCenter( n+1 )
           y_data = data.GetBinContent( n+1 )
           bw = data.GetBinWidth( n+1 )
           dy_u = data.GetBinError( n+1 )
           dy_d = data.GetBinError( n+1 ) 
        
        #print '    setting point %i: %f' % (i,y_data/y_mc,)
        ratio.Divide(data,prediction,"cl=0.683 b(1,1) mode")
        #for n in range( nbins):
        #        print "Bin %i: err = %f" % (n, ratio.GetErrorYhigh(n) )
      #  ratio.SetPoint( i, x_data, y_data/y_mc )
        
      #  ratio.SetPointError( i, bw/2, bw/2, dy_d/y_mc, dy_u/y_mc )
        
        i += 1
    return ratio


#########################################################


