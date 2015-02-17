#include "CutPtThreshold.h"

CutPtThreshold::CutPtThreshold() : IAnalysisCut( "PtThresholdCut" )
{
}


CutPtThreshold::~CutPtThreshold()
{
}


/////////////////////////////////////


void CutPtThreshold::Configure( const AnalysisCutParams_t& params )
{
}


/////////////////////////////////////


bool CutPtThreshold::Apply( EventData * ed )
{
  bool passed = true;

  // nothing to do
  
  return passed;
}


/////////////////////////////////////////
// Plugin

extern "C" {
    AnalysisCutPluginFactory_PtThreshold * MakeAnalysisCutPlugin() {
        return new AnalysisCutPluginFactory_PtThreshold("PtThreshold");
    };
}

