#!/usr/bin/env python

import os, sys
import numpy

from ROOT import *

inFileName = sys.argv[1]
print "Input file:", inFileName

hname = "reco/reco_c0_jet_pt"
if len( sys.argv ) > 2:
    hname = sys.argv[2]

nq = 10
if len( sys.argv ) > 3:
    nq = int( sys.argv[3] )
print "INFO: number of quantiles:", nq


####################################

def InitializeQuantileVector( nq = 10 ):
    # initialize quantile vector
    # e.g. for 10 quantiles: [ 0.1, 0.2, 0.3, .. 1.0 ]
    xq = numpy.ndarray( [ nq ], numpy.float64 )
    yq = numpy.ndarray( [ nq ], numpy.float64 )
    
    for n in range( nq ):
        xq[n] = float(n+1) / float(nq)

    print "Quantiles: x-values"
    for n in range( nq ):
        print "%f" % xq[n], " ",
    print
    
    return xq, yq

####################################


def RebinHistogram( h, nq, xq, yq ):
    
    if h.GetNbinsX() < nq:
        print "ERROR: histogram has less bins than the number of quantiles"
        return None
    
    # ROOT function to retrieve quantiles (x-axis positions)
    h.GetQuantiles( nq, yq, xq )

    # initialize new edges
    edges = numpy.ndarray( [ nq+1 ], numpy.float64 )

    edges[0] = h.GetXaxis().GetXmin()
    for n in range( nq ):
        val =  yq[n] #round( xq[n], 2 )
        bin = h.FindBin( val )
        edges[n+1] = h.GetBinLowEdge( bin )
    edges[nq]   = h.GetXaxis().GetXmax()

    #remove duplicates
    edges = numpy.unique( edges )

    print "New histogram bin edges (%i):" % (len(edges)-1)

    s = ""
    for n in edges: s += "%.2f," % n
    print s

    hq = h.Rebin( nq, h.GetName() + "_rebinned", edges )
    #hq = TH1F( h.GetName() + "_rebinned", h.GetTitle(), nq, edges )
    #hq.Sumw2()
    #hq.Draw("same")

    #for n in range( hq.GetNbinsX() ):
    #    hq.SetBinContent( n+1, hq.GetBinContent(n+1) / hq.GetBinWidth( n+1 ) )
    #    hq.SetBinError( n+1,  hq.GetBinError(n+1) / hq.GetBinWidth( n+1 ) )

    return hq

####################################


if __name__ == "__main__":

    inFile = TFile.Open( inFileName )

    h = inFile.Get( hname )
    if h == None:
        print "Invalid histogram", hname
        exit(1)

    xq, yq = InitializeQuantileVector( nq )

    hq = RebinHistogram( h, nq, xq, yq )

    if hq == None:
        exit( 1 )


#with open( "histograms_binning.csv", "append" ) as ofile:
#    ofile.write( s )

#exit(0)

#outfile = "rebinned.histograms.root"

#hq.SetFillStyle( 1001 )
#hq.SetFillColor( kYellow )
#hq.Draw("same")
#h.Draw("same")

#hq.Write()

#outfile.Close()

