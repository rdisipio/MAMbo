export MOMADIR=${MAMBODIR}/MoMA

ATHENAVERSION=17.2.11.14
export ATLAS_LOCAL_ROOT_BASE=/cvmfs/atlas.cern.ch/repo/ATLASLocalRootBase
alias setupATLAS='source ${ATLAS_LOCAL_ROOT_BASE}/user/atlasLocalSetup.sh'
setupATLAS

if [ ${USER} == "disipio" ]
then
  RCDIR=$LOCALDISK/AnalysisTop-1.8.0
fi

cd ${RCDIR}
source rcSetup.sh
cd ${MOMADIR}
