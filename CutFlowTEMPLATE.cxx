#include "CutFlow@NAME@.h"

CutFlow@NAME@::CutFlow@NAME@()
{
}

CutFlow@NAME@::~CutFlow@NAME@()
{
}


/////////////////////////////////////////


bool CutFlow@NAME@::Apply( EventData * ed, int * lastCutPassed )
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
  CutFlowPluginFactory_@NAME@ * MakeCutFlowPlugin() {
    return new CutFlowPluginFactory_@NAME@( "@NAME@" );
  };
}

