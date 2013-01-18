#include "CutFlow.h"

CutFlow::CutFlow( const string& name ) : m_name( name ), m_hm(NULL)
{
   m_hm = HistogramManager::GetHandle();
}

CutFlow::~CutFlow()
{
}


///////////////////////////////////////


bool CutFlow::Start()
{
  bool success = true;

  m_lastCutPassed = 0;

  return success;
}


///////////////////////////////////////


void CutFlow::Connect( const string& name, int cutN )
{
}


///////////////////////////////////////


void CutFlow::PassedCut()
{
}
