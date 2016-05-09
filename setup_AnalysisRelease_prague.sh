# September 2014 - Setup script for Analysis Release

# setup atlas
source /home/kepkao/setupsCVMFS/setup_atlas.sh

# run the usual setup
source setup_AnalysisRelease.sh

export X509_USER_PROXY=$HOME/myproxy

export MAMBO_USE_ANALYSISTOP=1

setupATLAS
# just once: rcSetup Top,2.3.45a
rcSetup
