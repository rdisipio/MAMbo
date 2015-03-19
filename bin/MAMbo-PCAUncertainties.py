#!/usr/bin/env python

import os, sys, time
import optparse
sys.path.append( os.environ['MAMBODIR'] + "/python" )

from ProgressBar import *

from xml.etree import ElementTree

import numpy as np
from numpy import linalg as LA
from numpy import random as rand

np.set_printoptions(precision=4,linewidth=200,suppress=True)

from ROOT import *
rand3gen = TRandom3()

histograms = {}

ignore_these_systematics = [ 'statsyst', 'systonly', 'statonly', 'stat' ]

########################################


def ReadInput( filename ):
   with open( filename, 'rt') as f:
      tree = ElementTree.parse(f)
 
      for histogram in tree.findall( './/histogram' ):
         hpath = histogram.attrib.get('hpath')
         histograms[hpath] = {}

#         print "*", hpath

         nbins = -1
         for nominal in histogram.findall( '.nominal' ):
             #print nominal.text
             values = nominal.text.split(',')
             nbins = len( values )
             histograms[hpath]['nominal'] = [ float(txt) for txt in values ]
#             print hpath, nbins,histograms[hpath]['nominal']


         for syst in histogram.findall('.uncertainty'):
             systname = syst.attrib.get('name')
             histograms[hpath][systname] = { 'u' : [ 0. ] * nbins, 'd' : [ 0. ] * nbins }

             for var in [ 'u', 'd' ]:
                for shift in syst.findall('.'+var):
                   values = shift.text.split(',')
                   histograms[hpath][systname][var] = [ float(txt)/100. for txt in values ]

                   # consistency check
                   n = len( histograms[hpath][systname][var] )
                   if not n == nbins: raise Exception( 'Bin mismatch for systematic shift %s:%s:%s found:%i nbins=%i' % ( hpath, systname, var, n, nbins ) )

#             print "  *", systname


########################################################################


def MakeCovarianceMatrix( hname, ntoys=10000 ):

   histogram = histograms[hname]
   nominal = histogram['nominal']
   nbins = len( nominal )

   toys  = np.zeros( [ ntoys, nbins ] )

   for itoy in range( ntoys ):

      delta = np.zeros( nbins )
      for sname, syst in histogram.iteritems():
         if sname in [ 'nominal' ]: continue
         if sname in ignore_these_systematics: continue

         #l = rand.normal(0.,1.)
         l = rand3gen.Gaus(0,1)
         for n in range(nbins):
            s = syst['u'][n] if l > 0. else syst['d'][n] #NB: fractional shifts (e.g. 0.10 = 10% )

            delta[n] += abs(l) * s # linear interpolation

      for n in range(nbins):
         toys[itoy][n] = nominal[n] * ( 1. + delta[n] )

   C = np.cov( toys,rowvar=0 )

   return C


########################################################################


def CorrelationMatrix( cov ):

  nbins = cov.shape[0]

  corr = zeros( nbins, nbins )
  for i in range(nbins):
     sigma_i = cov[i][i]
     for j in range(nbins):
        sigma_j = cov[j][j]

        corr[i][j] = cov[i][j] / (sigma_i * sigma_j) 

########################################################################


def NumpyMatrixToTH2D( m ):
    nbinsx = m.shape[0]
    nbinsy = m.shape[1]

    mo = TH2D( "", "", nbinsx, -0.5, nbinsx-0.5, nbinsy, -0.5, nbinsy-0.5 )
    for i in range( nbinsx ):
       for j in range( nbinsy ):
          mo.SetBinContent( i+1, nbinsy-j, m[i][j] )

    return mo



########################################################################


def ApplyPCA( hname, ntoys=10000 ):
   print "Applying PCA to:", hname

   if not histograms.has_key(hname): raise Exception( "Invalid variable name: " + hname )

   histogram = histograms[hname]
   nominal   = histogram['nominal']
   nbins = len( nominal )

   Ctot = MakeCovarianceMatrix( hname, ntoys )
 
   print "Total covariance matrix for %s:" % hname
   print Ctot

   S, V = LA.eig( Ctot )

   print "Eigenvalues:"
   print S
   print "Eigenvectors:"
   print V

   k = 0
   smax = max(S)
   for n in range(len(S)):
     if S[n] / smax > 1e-3: k += 1
   print "Found %i large eigenvalues" % k

   pca_systematics = {}
   for i in range(nbins):
      sname = "pca_syst_%i" % (i+1)
      pca_systematics[sname] = { 'u' : np.zeros(nbins), 'd' : np.zeros(nbins) }

      v = V[:,i] * np.sqrt( S[i] ) / nominal[i]

      print "Eigenvector", i, "=", v

      for k in range(nbins): 
         pca_systematics[sname]['u'][k] = v[k]
         pca_systematics[sname]['d'][k] = -v[k]

########################################################################


if __name__ == "__main__":

   parser = optparse.OptionParser( usage = "%prog [options]" )
   parser.add_option( "-i", "--input-xml", help="Input XML file [%default]", dest="input", default="uncertainty.xml" )
   parser.add_option( "-o", "--ouput-xml", help="Output XML file [%default]", dest="output", default="uncertainty.pca.xml" ) 
   parser.add_option( "-v", "--variables", help="Variable name/path (csv list)", dest="variables", default="reco/4j2b/topH/pt,reco/4j2b/topH/absrap" )
   parser.add_option( "-n", "--ntoys", help="Number of toys [%default]", dest="ntoys", default=10000 )
   (opts, args) = parser.parse_args()

   ReadInput( opts.input )

   variables = opts.variables.split(',')

   for hname in variables:
      ApplyPCA( hname, int(opts.ntoys) )
