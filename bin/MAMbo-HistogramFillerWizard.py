#!/usr/bin/env python

from ROOT import *
import sys
import os
#import optparse
import shutil

shareDir = os.environ["MAMBODIR"] + "/share/templates/"
templateWHeader = open( shareDir + "HistogramFillerTEMPLATE.h", 'r' ).read()
templateWSrc    = open( shareDir + "HistogramFillerTEMPLATE.cxx", 'r' ).read()


#parser = optparse.OptionParser( usage = "%prog [options] ntuple.root" )
#parser.add_option( "-t", "--tree",    help="Tree name [%default]", dest="treeName",    default="mini" )
#parser.add_option( "-w", "--wrapper", help="Wrapper name",         dest="wrapperName", default="Mini" )
#(opts, args) = parser.parse_args()

if len( sys.argv ) == 1:
  print "Usage:", sys.argv[0],"NTUPLE.root"
  exit(0)

HistogramFillerName = sys.argv[-1]

print "Creating HistogramFiller", HistogramFillerName

cfheaderFile = open( "HistogramFiller" + HistogramFillerName + ".h", 'w' )
cfheader = templateWHeader.replace( "@NAME@", HistogramFillerName )
cfheaderFile.write( cfheader )

cfsrcFile = open( "HistogramFiller" + HistogramFillerName + ".cxx", 'w' )
cfsrc = templateWSrc.replace( "@NAME@", HistogramFillerName )
cfsrcFile.write( cfsrc )
