#include "CutFlow@NAME@.h"

CutFlow@NAME@::CutFlow@NAME@()
{
}

CutFlow@NAME@::~CutFlow@NAME@()
{
}


/////////////////////////////////////////


bool CutFlow@NAME@::Initialize()
{
   bool success = true;

   // AddChannel( "EL" );
   // AddCounterName( "EL", "weighted", 3 );
   // AddCounterName( "EL", "unweight", 3 );

   // SetCutName( "EL", "weighted", 0, "AllEvents" );
   // SetCutName( "EL", "weighted", 1, "Trigger" );
   // SetCutName( "EL", "weighted", 2, "Prim. Vtx" );
   // SetCutName( "EL", "weighted", 3, "single electron" );   

   return success;
}


/////////////////////////////////////////


bool CutFlow@NAME@::Apply( EventData * ed )
{
  bool success = true;

  CutFlow::Start();

  //// example:
  // double weight = ed->info.mcWeight;
  // m_hm->GetHistogram( "fjet_pt" )->Fill( ed->fjet.pT / GeV, weight );
  //
  // PassedCut( "EL", "unweight" );
  // PassedCut( "EL", "weighted", 1.05 );

  return success;
}


/////////////////////////////////////////
// Plugin

extern "C" {
  CutFlowPluginFactory_@NAME@ * MakeCutFlowPlugin() {
    return new CutFlowPluginFactory_@NAME@( "@NAME@" );
  };
}

