#!/usr/bin/env python

# remember to create
# hadd -f tt_diffxs_8TeV.mc.Others.co.nominal.histograms.root  tt_diffxs_8TeV.mc.Others.el.nominal.histograms.root tt_diffxs_8TeV.mc.Others.mu.nominal.histograms.root 

import os,sys
from ROOT import *
import random, math

sys.path.append( os.environ['MAMBODIR'] + "/python" )

from ProgressBar import *

import numpy as np
basedir = os.environ['MAMBOOUTPUTDIR'] + "/nominal/"



######################################

def NormCA( histograms ):

  D_p = histograms['data'].Integral( 1, 9 )
  D_m = histograms['data'].Integral( 10, 18 )

  W_lf_p = histograms['wjets_lf'].Integral( 1, 9 )
  W_lf_m = histograms['wjets_lf'].Integral( 10, 18 )

  W_c_p = histograms['wjets_c'].Integral( 1, 9 )
  W_c_m = histograms['wjets_c'].Integral( 10, 18 )

  W_bbcc_p = histograms['wjets_bbcc'].Integral( 1, 9 )
  W_bbcc_m = histograms['wjets_bbcc'].Integral( 10, 18 )

  W_p = W_lf_p + W_c_p + W_bbcc_p
  W_m = W_lf_m + W_c_m + W_bbcc_m

  ST_p = histograms['stop'].Integral( 1, 9 )
  ST_m = histograms['stop'].Integral( 10, 18 )

  O_p = histograms['others'].Integral( 1, 9 )
  O_m = histograms['others'].Integral( 10, 18 )

  D_p -= ST_p
  D_m -= ST_m

#  D_p -= O_p
#  D_m -= O_m
 
  Wtot = W_p + W_m

  CA = ( D_p - D_m ) / ( W_p - W_m )

  N_DD = CA * Wtot

  # r_MC = sigma_p / sigma_m 
  # N = sigma * Lumi * eff
#  r_MC = W_p / W_m
#  N_DD = ( D_p - D_m ) * ( r_MC + 1 ) / ( r_MC - 1 )

  return N_DD, CA


######################################


def Normalize( hw, i, N_CA, k=4 ):
   N = hw.GetBinContent( i ) + hw.GetBinContent( i + k )
   sf = N_CA / N

   y1 = sf * hw.GetBinContent( i )
   y2 = sf * hw.GetBinContent( i + k )

   hw.SetBinContent( i, y1 )
   hw.SetBinContent( i+k, y2 )


######################################


def Likelihood( histograms, params, N_DD ):
   h = histograms['others'].Clone( "h" )

   hw = h.Clone("hw")
   hw.Reset()

   hw.Add( histograms['wjets_lf'],   params[0] )
   hw.Add( histograms['wjets_c'],    params[1]  )
   hw.Add( histograms['wjets_bbcc'], params[2] )

   N = hw.Integral()
   hw.Scale( N_DD / N )

   h.Add( hw )

   chi2 = histograms['data'].Chi2Test( h, "WW CHI2/NDF" )

   return chi2


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

nj = 3 #njets incl
i  = 7
if len( sys.argv ) > 2: nj = int( sys.argv[2] )
if nj == 3: i = 4
if nj == 4: i = 7 
print "INFO: requested Nj = %i  bins=%i" % ( nj, i )

#hack
for sample, h in histograms.iteritems():
   if h == None: print "ERROR: invalid histogram for sample", sample

   # remove Nj=2 bins
   for b in [ 1, 2, 3, 10, 11, 12 ]:
      h.SetBinContent( b, 0 )

   # remove unwanted region
   if i == 4:
      for b in [ 7, 8, 9, 16, 17, 18 ]:
         h.SetBinContent( b, 0 )
   if i == 7:
      for b in [ 4, 5, 6, 13, 14, 15 ]:
         h.SetBinContent( b, 0 )

histograms['data'].Print("all")


dx = 0.7
if len(sys.argv) > 3: dx = float( sys.argv[3] )

step = 0.01

range_lf   = np.arange( 1.0 - dx, 1.0 + dx, step )
range_c    = np.arange( 1.0 - dx, 1.0 + dx, step )
range_bbcc = np.arange( 1.0 - dx, 1.0 + dx, step )

#range_lf   = np.arange( 0.6, 2.0, step )
#range_c    = np.arange( 0.6, 2.0, step )
#range_bbcc = np.arange( 0.6, 2.0, step )

n_itr = len(range_lf) * len(range_c) * len(range_bbcc)

N_DD, CA = NormCA( histograms )
print "INFO: N_DD = %i ; CA = %.3f" % ( N_DD, CA )


bestfit = []
chi2_min = 1e20

progress = ProgressBar( 0, n_itr, 77, mode='static', char="#" )

print "INFO: Starting main loop"
itr = 0 
for k_lf in range_lf:
   for k_c in range_c:
      for k_bbcc in range_bbcc:

          chi2 = Likelihood( histograms, [ k_lf, k_c, k_bbcc ], N_DD )

          if chi2 < chi2_min:
            chi2_min = chi2
            bestfit  = [ k_lf, k_c, k_bbcc ]

#          progress.increment_amount()
#          print progress, "\r",
          #time.sleep(0.05)
          itr += 1

print "INFO: Best fit:"
print "INFO: X2/NDF = %.2f  CA=%.3f ;  k_l = %.3f  ;  k_c = %.3f  ;  k_bb = %.3f " % ( chi2_min, CA, bestfit[0], bestfit[1], bestfit[2] )          



stepsizes = [ 0.01, 0.01, 0.01 ] # accuracy
params = [ 1.0, 1.0, 1.0 ] # initial guess
N_params = len( params )
A = [ params ]
accepted = 0.
Nitr = 10000
for n in range( Nitr ):
   old_params = A[-1]
   old_logL  = log( Likelihood( histograms, old_params, N_DD ) )

   new_params = np.zeros( N_params )

   for k in range( N_params ):
       new_params[k] = random.gauss( old_params[k], stepsizes[k] )

   new_logL = log( Likelihood( histograms, new_params, N_DD ) )
   
   if new_logL > old_logL:
      A.append( new_params )
      accepted += 1.
      chi2_min = exp( new_logL )
   else:
      u = random.uniform( 0., 1. )
      if( u < math.exp(new_logL - old_logL) ):
         A.append( new_params )
         accepted = accepted + 1.0  # monitor acceptance
         chi2_min = exp( new_logL )
      else:
         A.append( old_params )
         chi2_min = exp( old_logL )

print "INFO: acceptance rate:", accepted/float(Nitr) 
print "INFO: Markov chain best-fit chi2 = %.2  scale factors: [ %.3f, %.3f, %.3f ]" % ( chi2_min, A[-1][0], A[-1][1], A[-1][2] )
