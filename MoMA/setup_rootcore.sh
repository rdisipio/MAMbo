export MOMADIR=${MAMBODIR}/MoMA

ATHENAVERSION=17.2.11.14
export ATLAS_LOCAL_ROOT_BASE=/cvmfs/atlas.cern.ch/repo/ATLASLocalRootBase
alias setupATLAS='source ${ATLAS_LOCAL_ROOT_BASE}/user/atlasLocalSetup.sh'
setupATLAS

[ ${USER} == "vscarfon" ] && RCDIR=/afs/cern.ch/work/v/vscarfon/public/AnalysisTop-1.8.0
[ ${USER} == "disipio"  ] && RCDIR=/home/ATLAS/disipio/LOCAL_DISK/AnalysisTop-1.8.0

cd ${RCDIR}
source rcSetup.sh

export ROOTCOREDIR=$ROOTCOREBIN

cd ${MAMBODIR}
