#!/usr/bin/env python

from ROOT import *
import sys
import os
#import optparse
import shutil

analysisParamsXML = """
<analysis name=\"@ANALYSISNAME@\">
  <ntuple>HWWtth</ntuple>
  <branches>control/branch_list_HWWtth.txt</branches>
  <tree>HWWTree</tree>
  <histograms>control/histograms_@ANALYSISNAME@.xml</histograms>
  <cutflow>@CUTFLOWNAME@</cutflow>
</analysis>
"""

shareDir = os.environ["MAMBODIR"] + "/share/templates/"
templateWHeader  = open( shareDir + "CutFlowTEMPLATE.h", 'r' ).read()
templateWSrc     = open( shareDir + "CutFlowTEMPLATE.cxx", 'r' ).read()
templateMakefile = open( shareDir + "Makefile.analysis.template" ).read()

analysisName = sys.argv[1]
print "Creating standalone analysis", analysisName

targetDir = os.environ["PWD"] + "/" + analysisName + "/"

try:
    os.mkdir( targetDir )
except:
    print "Directory", targetDir, "may already exist. Remove it first if needed"
    #exit(1)
try:
    os.mkdir( targetDir + "control" )
except:
    pass

if len( sys.argv ) == 2:
    cutflows = [ analysisName ]
else:
    cutflows = sys.argv[2].split( ',' )

cutflowsTxt = ""
for cutflowName in cutflows:
    print "Generating cutflow %s / %s" % ( analysisName, cutflowName )
    
    cfheaderFile = open( targetDir + "CutFlow" + cutflowName + ".h", 'w' )
    cfheader = templateWHeader.replace( "@NAME@", cutflowName )
    cfheaderFile.write( cfheader )

    cfsrcFile = open( targetDir + "CutFlow" + cutflowName + ".cxx", 'w' )
    cfsrc = templateWSrc.replace( "@NAME@", cutflowName )
    cfsrcFile.write( cfsrc )

    paramsFiles = open( targetDir + "control/analysis_params_%s_%s.xml" % ( analysisName, cutflowName ), 'w' )
    paramsTxt = analysisParamsXML.replace( "@ANALYSISNAME@", analysisName ).replace( "@CUTFLOWNAME@", cutflowName )
    paramsFiles.write( paramsTxt )
    paramsFiles.close()

    branchListFile = open( targetDir + "control/branch_list_%s_%s.txt" % ( analysisName, cutflowName ), 'w' )
    branchListFile.close()

    cutflowsTxt += cutflowName + " "

# Create Makefile
analysisMakefile = open( targetDir + "Makefile", 'w' )
makefileTxt = templateMakefile.replace( "@CUTFLOWS@", cutflowsTxt )
analysisMakefile.write( makefileTxt )

# Create config files
shutil.copy2( shareDir + "histograms.xml", targetDir + "control/histograms_%s.xml" % analysisName )

# copy README
shutil.copy2( shareDir + "README_StandaloneAnalysis.txt", targetDir + "README.txt" )
