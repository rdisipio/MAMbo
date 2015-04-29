#!/usr/bin/env python

import os,sys
from ROOT import *

sys.path.append( os.environ['MAMBODIR'] + "/python" )

from ProgressBar import *

import numpy as np
basedir = os.environ['MAMBOOUTPUTDIR'] + "/nominal/"



######################################

def NormCA( histograms, i, nj_bins = 3, nb_bins = 2, offset = 3 ):

  # offset is due to empty Nj=2 in data and MC
  k = nj_bins * nb_bins + offset
 
  # integrate over Nbj bins ("untagged")
  D_p = histograms['data'].Integral(   i,   i+nb_bins   )
  D_m = histograms['data'].Integral(   i+k, i+k+nb_bins )

  W_lf_p = histograms['wjets_lf'].Integral( i, i+nb_bins )
  W_lf_m = histograms['wjets_lf'].Integral( i+k, i+k+nb_bins ) 

  W_c_p = histograms['wjets_c'].Integral( i, i+nb_bins )
  W_c_m = histograms['wjets_c'].Integral( i+k, i+k+nb_bins )	

  W_bbcc_p = histograms['wjets_bbcc'].Integral( i, i+nb_bins )
  W_bbcc_m = histograms['wjets_bbcc'].Integral( i+k, i+k+nb_bins )	

  W_p = W_lf_p + W_c_p + W_bbcc_p
  W_m = W_lf_m + W_c_m + W_bbcc_m
 
  ST_p = histograms['stop'].Integral(  i,   i+nb_bins   )
  ST_m = histograms['stop'].Integral(  i+k, i+k+nb_bins )

  O_p = histograms['others'].Integral(  i,   i+nb_bins   )
  O_m = histograms['others'].Integral(  i+k, i+k+nb_bins )

  D_p -= ST_p
  D_m -= ST_m

#  D_p -= O_p
#  D_m -= O_m
 
  Wtot = W_p + W_m

  N_DD = ( D_p - D_m ) * ( W_p + W_m ) / ( W_p - W_m )

  # r_MC = sigma_p / sigma_m 
  # N = sigma * Lumi * eff
#  r_MC = W_p / W_m

#  N_DD = ( D_p - D_m ) * ( r_MC + 1 ) / ( r_MC - 1 )

  CA = N_DD / Wtot

  return N_DD, CA


######################################


def Normalize( hw, i, N_CA, k=9 ):
   N = hw.Integral( i, i+2 ) + hw.Integral( i+k, i+k+2 )
   sf = N_CA / N

   for j in [ i, i+k ]:
      y1 = sf * hw.GetBinContent( j )
      y2 = sf * hw.GetBinContent( j+1 )
      y3 = sf * hw.GetBinContent( j+2 )
      hw.SetBinContent( j,   y1 )
      hw.SetBinContent( j+1, y2 )
      hw.SetBinContent( j+2, y3 )

#   Nnew = hw.Integral( i, i+2 ) + hw.Integral( i+k, i+k+2 )
#   print Nnew

######################################


ch = sys.argv[1]

if ch == "el": stream = "Egamma"
if ch == "mu": stream = "Muons"
if ch == "co": stream = "Combined"

files = {
  'data'     : TFile.Open( basedir + "tt_diffxs_8TeV.data.%s.%s.histograms.root" % ( stream, ch ) ),
  'wjets_lf' : TFile.Open( basedir + "tt_diffxs_8TeV.mc.Wjets_lf.%s.nominal.histograms.root" % ch ),
  'wjets_c'  : TFile.Open( basedir + "tt_diffxs_8TeV.mc.Wjets_c.%s.nominal.histograms.root" % ch ),
  'wjets_bbcc' : TFile.Open( basedir + "tt_diffxs_8TeV.mc.Wjets_bbcc.%s.nominal.histograms.root" % ch ),
  'others'   : TFile.Open( basedir + "tt_diffxs_8TeV.mc.Others.%s.nominal.histograms.root" % ch ),
  'stop'     : TFile.Open( basedir + "tt_diffxs_8TeV.mc.SingleTop.%s.nominal.histograms.root" % ch ),
 }

hpath = "reco/cutflow/3j0b/flav_comp"

histograms = { k : f.Get( hpath ) for k,f in files.iteritems() }

i = 4
if len( sys.argv ) > 2: i = int( sys.argv[2] )

#hack
for h in histograms.values():
   for b in range(18):
      # remove Nj=2 bins
      if b in [ 0, 1, 2, 9, 10, 11 ]:
         h.SetBinContent( b+1, 0.0 )

   # remove unwanted region
   if i == 4:
      for b in [ 6, 7, 8, 15, 16, 17 ]:
         h.SetBinContent( b+1, 0.0 )
   else:
      for b in [ 3, 4, 5, 12, 13, 14 ]:
         h.SetBinContent( b+1, 0.0 )

histograms['data'].Print("all")

dx = 0.3
if len(sys.argv) > 3: dx = float( sys.argv[3] )

step = 0.02

range_lf   = np.arange( 1.0 - dx, 1.0 + dx, step )
range_c    = np.arange( 1.0 - dx, 1.0 + dx, step )
range_bbcc = np.arange( 1.0 - dx, 1.0 + dx, step )

#range_lf   = np.arange( 0.6, 2.0, step )
#range_c    = np.arange( 0.6, 2.0, step )
#range_bbcc = np.arange( 0.6, 2.0, step )

n_itr = len(range_lf) * len(range_c) * len(range_bbcc)

N_DD, CA = NormCA( histograms, i )
print "INFO: N_DD = %i ; CA = %.3f" % ( N_DD, CA )

#N_DD_3j, CA_3j = NormCA( histograms, 4 )
#N_DD_4j, CA_4j = NormCA( histograms, 7 )
#N_DD = N_DD_3j+N_DD_4j
#print "INFO: N_DD(3j) = %i  ;  CA (3j) = %.3f" % ( Ntot_3j, CA_3j )
#print "INFO: N_DD(4j) = %i  ;  CA (4j) = %.3f" % ( Ntot_4j, CA_4j )


bestfit = []
chi2_min = 1e20

progress = ProgressBar( 0, n_itr, 77, mode='static', char="#" )

print "INFO: Starting main loop"
itr = 0 
for k_lf in range_lf:
   for k_c in range_c:
      for k_bbcc in range_bbcc:
          h = histograms['others'].Clone( "h" )

          hw = h.Clone("hw")
          hw.Reset()

          hw.Add( histograms['wjets_lf'], k_lf )
          hw.Add( histograms['wjets_c'],  k_c  )
          hw.Add( histograms['wjets_bbcc'], k_bbcc )

#          N = hw.Integral()
#          hw.Scale( N_DD / N )

          Normalize( hw, i, N_DD )
#          Normalize( hw, 7, Ntot_4j )
          h.Add( hw )

          chi2 = histograms['data'].Chi2Test( h, "WW CHI2/NDF" )
          if chi2 < chi2_min:
            chi2_min = chi2
            bestfit  = [ k_lf, k_c, k_bbcc ]

#          progress.increment_amount()
#          print progress, "\r",
          #time.sleep(0.05)
          itr += 1

print
print "INFO: Loop finished"
print
print "INFO: Best fit:"
print "INFO: Chi2 / NDF = %f" % chi2_min
print "INFO: Scale factors: k_l = %.3f ; k_c = %.3f ; k_bb = %.3f " % ( bestfit[0], bestfit[1], bestfit[2] )          
