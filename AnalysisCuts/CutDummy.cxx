#include "CutDummy.h"

CutDummy::CutDummy() : IAnalysisCut( "DummyCut" )
{
}


CutDummy::~CutDummy()
{
}


/////////////////////////////////////


void CutDummy::Configure( const AnalysisCutParams_t& params )
{
}


/////////////////////////////////////


bool CutDummy::Apply( EventData * ed )
{
  bool passed = true;

  // nothing to do
  
  return passed;
}


/////////////////////////////////////////
// Plugin

extern "C" {
    AnalysisCutPluginFactory_Dummy * MakeAnalysisCutPlugin() {
        return new AnalysisCutPluginFactory_Dummy("Dummy");
    };
}

