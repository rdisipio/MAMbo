#!/usr/bin/env python

from ROOT import *
import sys
import os
#import optparse
import shutil

shareDir = os.environ["MAMBODIR"] + "/share/templates/"
templateWHeader = open( shareDir + "CutFlowTEMPLATE.h", 'r' ).read()
templateWSrc    = open( shareDir + "CutFlowTEMPLATE.cxx", 'r' ).read()


#parser = optparse.OptionParser( usage = "%prog [options] ntuple.root" )
#parser.add_option( "-t", "--tree",    help="Tree name [%default]", dest="treeName",    default="mini" )
#parser.add_option( "-w", "--wrapper", help="Wrapper name",         dest="wrapperName", default="Mini" )
#(opts, args) = parser.parse_args()

if len( sys.argv ) == 1:
  print "Usage:", sys.argv[0],"NTUPLE.root"
  exit(0)

cutflowName = sys.argv[-1]

print "Creating Cutflow", cutflowName

cfheaderFile = open( "CutFlow" + cutflowName + ".h", 'w' )
cfheader = templateWHeader.replace( "@NAME@", cutflowName )
cfheaderFile.write( cfheader )

cfsrcFile = open( "CutFlow" + cutflowName + ".cxx", 'w' )
cfsrc = templateWSrc.replace( "@NAME@", cutflowName )
cfsrcFile.write( cfsrc )
