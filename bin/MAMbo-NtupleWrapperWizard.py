#!/usr/bin/env python

from ROOT import *
import sys
import os
import optparse
import shutil

shareDir = os.environ["MAMBODIR"] + "/share/templates/"
templateWHeader = open( shareDir + "NtupleWrapperTEMPLATE.h", 'r' ).read()
templateWSrc    = open( shareDir + "NtupleWrapperTEMPLATE.cxx", 'r' ).read()


parser = optparse.OptionParser( usage = "%prog [options] ntuple.root" )
parser.add_option( "-t", "--tree",    help="Tree name [%default]", dest="treeName",    default="mini" )
parser.add_option( "-w", "--wrapper", help="Wrapper name",         dest="wrapperName", default="Mini" )
(opts, args) = parser.parse_args()

if len( sys.argv ) == 1:
  print "Usage:", sys.argv[0],"NTUPLE.root"
  exit(0)

treeName          = opts.treeName
ntupleWrapperName = opts.wrapperName

inputNtuple = sys.argv[-1]

print "Tree", treeName, "will be read in from file", inputNtuple
print "Output ntuple wrapper will be", ntupleWrapperName

file = TFile( inputNtuple, 'r' )
tree = file.Get( treeName )
tree.MakeClass( ntupleWrapperName)
#tree.MakeSelector( ntupleWrapperName )
shutil.move( ntupleWrapperName + ".C", ntupleWrapperName + ".cxx" ) 

wheaderFile = open( "NtupleWrapper" + ntupleWrapperName + ".h", 'w' )
wheader = templateWHeader.replace( "@NAME@", ntupleWrapperName )
wheaderFile.write( wheader )

wsrcFile = open( "NtupleWrapper" + ntupleWrapperName + ".cxx", 'w' )
wsrc = templateWSrc.replace( "@NAME@", ntupleWrapperName )
wsrcFile.write( wsrc )
