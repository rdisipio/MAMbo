#!/usr/bin/env python

import os, sys
import optparse

from ROOT import *

#from xml.etree import ElementTree
#import numpy as np

histograms = {}


########################################


def FetchHistograms( hlist, fdata, func ):

   f_data = TFile.Open( fdata )
   f_unc  = TFile.Open( func )

   for hpath in hlist:
      histograms[hpath] = { 'data' : None, 'unc' : None, 'final' : None }

      histograms[hpath]['data'] = f_data.Get( hpath ).Clone( hpath + "_data" )
      histograms[hpath]['unc']  = f_unc.Get( hpath ).Clone( hpath + "_unc" )


########################################


def CreateROOTPath( path ):
    tokens = path.split( '/' )
    if len( tokens ) == 1:
        return gDirectory.GetDirectory(".")
    else:
        nextdir = tokens[0]

        if gDirectory.FindObject( nextdir ) == None:
            gDirectory.mkdir( nextdir )
        gDirectory.cd( nextdir )

        newpath = path.replace( tokens[0] + "/", "" )

        return CreateROOTPath( newpath )


####################################################


def CreateHistogram( hpath ):
   outfile.cd()

   data = histograms[hpath]['data']
   unc  = histograms[hpath]['unc']

   CreateROOTPath( hpath )
 
   histograms[hpath]['final'] = TGraphAsymmErrors()

   final = histograms[hpath]['final']
   final.SetName( hpath.split('/')[-1] )

   nbins = data.GetNbinsX()
   j = 0
   for i in range(nbins):
      x = data.GetBinCenter( i+1 )
      y = data.GetBinContent( i+1 )
     
      bw = data.GetBinWidth( i+1 )

      e_stat = data.GetBinError( i+1 )

      x_mc = Double()
      y_mc = Double()
      unc.GetPoint( i, x_mc, y_mc )

      e_tot_u = unc.GetErrorYhigh(i)
      e_tot_d = unc.GetErrorYhigh(i)

      if not y_mc == 0.:
        e_final_u = ( e_tot_u/y_mc ) * y
        e_final_d = ( e_tot_d/y_mc ) * y
      else:
        print "WARNING: histogram", hpath, "has zero value in bin", i, " . skipping point.."
        continue

      final.SetPoint( j, x, y )
      final.SetPointError( j, bw/2, bw/2, e_final_d, e_final_u )

      j += 1

   final.Write()


########################################################################

    
if __name__ == "__main__":
   
   parser = optparse.OptionParser( usage = "%prog [options] configfile.xml" )
   parser.add_option( "-u", "--uncertainty", help="Input Uncertainty file name",  dest="uncFileName",  default="" )
   parser.add_option( "-d", "--data",        help="Input Real data file name",    dest="dataFileName", default="" )
   parser.add_option( "-g", "--graphs",      help="Graphs to be produced",        dest="hlist",        default="AbsoluteDiffXs,RelativeDiffXs" )
   parser.add_option( "-o", "--output",      help="Output file name [%default]",  dest="output",       default="unfolded.root" )
   (opts, args) = parser.parse_args()

   if opts.uncFileName == "":
      print "ERROR: please specify the input file containing the uncertainty band."
      exit(1)
   if opts.dataFileName == "":
      print "ERROR: please specify the input file containing the unfolded data-bkg."
      exit(1)

   hlist = opts.hlist.split(',')
   FetchHistograms( hlist, opts.dataFileName, opts.uncFileName )

   outFileName = opts.output
   print "INFO: Output file name:", outFileName
 
   outfile = TFile.Open( outFileName, "RECREATE" )

   for hpath in hlist:
      CreateHistogram( hpath )

   outfile.Close()

