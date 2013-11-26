#!/usr/bin/env python

from ROOT import *
import sys
import os
#import optparse
import shutil

analysisParamsXML = """
<analysis name=\"@ANALYSISNAME@\">
  <ntuple>@NTUPLENAME@</ntuple>
  <branches>control/branch_list_@NTUPLENAME@.txt</branches>
  <tree>@TREENAME@</tree>
  <histograms>control/histograms_@ANALYSISNAME@.xml</histograms>
  <cutflow>@CUTFLOWNAME@</cutflow>
  <parameters>
    <param name="pTmin" value="20." />    <!-- just an example -->
    <param name="etaMax" value="2.5" />   <!-- just an example -->
  </parameters>
</analysis>
"""

#######################################


def PrintOutHelp():
    print sys.argv[0].split("/")[-1], " analysis_name cutflow_name1[,cutflow_name2,cutflow_name3] [ntuple_wrapper_name,tree_name]"


#######################################
    

shareDir = os.environ["MAMBODIR"] + "/share/templates/"
templateWHeader  = open( shareDir + "CutFlowTEMPLATE.h", 'r' ).read()
templateWSrc     = open( shareDir + "CutFlowTEMPLATE.cxx", 'r' ).read()
templateMakefile = open( shareDir + "Makefile.analysis.template" ).read()
templateReadme   = open( shareDir + "README_StandaloneAnalysis.txt" ).read()

analysisName = sys.argv[1]

if analysisName in [ "-h", "--help", "help" ]:
    PrintOutHelp()
    exit(0)
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

ntupleName = "HWWtth"
treeName   = "HWWTree"
if len( sys.argv ) == 3:
    tokens = sys.argv[3].split(",")
    
    ntupleName = tokens[0]
    treeName   = tokens[1]
    

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
    paramsTxt = analysisParamsXML.replace( "@ANALYSISNAME@", analysisName )
    paramsTxt = paramsTxt.replace( "@CUTFLOWNAME@",  cutflowName )
    paramsTxt = paramsTxt.replace( "@NTUPLENAME@",   ntupleName )
    paramsTxt = paramsTxt.replace( "@TREENAME@",     treeName )
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
readmeFile = open( targetDir + "README.txt", 'w' )
readmeTxt  = templateReadme.replace( "@ANALYSISNAME@", analysisName )
readmeTxt  = readmeTxt.replace( "@TARGETDIR@", targetDir )
readmeTxt  = readmeTxt.replace( "@TREENAME@", treeName )
readmeTxt  = readmeTxt.replace( "@NTUPLENAME@", ntupleName )
readmeTxt  = readmeTxt.replace( "@CUTFLOWNAME@", cutflowName )

print
#print "IMPORTANT: Please, read " + targetDir + "README.txt"
print readmeTxt
