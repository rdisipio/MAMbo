#############################
# Standalone Analysis HOWTO
#############################

First of all, try to compile:

cd @TARGETDIR@
make

You may want to edit your analysis params files, e.g.:
@TARGETDIR@/control/analysis_params_@ANALYSISNAME@_@CUTFLOWNAME@.xml

For instance, you may want to change the ntuple wrapper or the tree name:

<ntuple>@NTUPLENAME@</ntuple>
<tree>@TREENAME@</tree>

In some cases, the same wrapper can be used to read trees with different names (e.g. if they share a set of branches).

Also, you may want to modify the list of output histograms in @TARGETDIR@/control/histograms_@ANALYSISNAME@.xml
This is just a skeleton, you can define more histograms in different xml files. Remember to modify the analysis params accordingly.

You need to specify your input ROOT files in a text file (eg. create control/file_list.txt), one per line, like this:

/home/myself/ntuples/file1.root
/home/myself/ntuples/file2.root

These are supposed to contain a tree of type @NTUPLENAME@ with name @TREENAME@ in each file.

Finally, to run:

cd @TARGETDIR@
runMAMbo -p control/analysis_params_@ANALYSISNAME@_@CUTFLOWNAME@.xml -f control/file_list.txt -o test.histograms.root

You can find the complete documentation on this twiki page:
https://twiki.cern.ch/twiki/bin/view/Main/MAMbo
