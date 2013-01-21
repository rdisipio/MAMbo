#include "CutFlowFakeRateZjet.h"

CutFlowFakeRateZjet::CutFlowFakeRateZjet()
{
}

CutFlowFakeRateZjet::~CutFlowFakeRateZjet()
{
}


/////////////////////////////////////////


bool CutFlowFakeRateZjet::Apply( EventData * ed, int * lastCutPassed )
{
  bool success = true;

  CutFlow::Start();

  //// example:
  // double weight = ed->info.mcWeight;
  // m_hm->GetHistogram( "fjet_pt" )->Fill( ed->fjet.pT / GeV, weight );

  return success;
}


/////////////////////////////////////////
// Plugin

extern "C" {
  CutFlowPluginFactory_FakeRateZjet * MakeCutFlowPlugin() {
    return new CutFlowPluginFactory_FakeRateZjet( "FakeRateZjet" );
  };
}
