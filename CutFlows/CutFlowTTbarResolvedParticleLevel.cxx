#include "CutFlowTTbarResolvedParticleLevel.h"

CutFlowTTbarResolvedParticleLevel::CutFlowTTbarResolvedParticleLevel()
{
}

CutFlowTTbarResolvedParticleLevel::~CutFlowTTbarResolvedParticleLevel()
{
}


/////////////////////////////////////////


bool CutFlowTTbarResolvedParticleLevel::Initialize()
{
   bool success = true;

   // AddChannel( "EL" );
   // AddCounter( "EL", "weighted", 3 );
   // AddCounter( "EL", "unweight", 3 );

   // SetCutName( "EL", "weighted", 0, "AllEvents" );
   // SetCutName( "EL", "weighted", 1, "Trigger" );
   // SetCutName( "EL", "weighted", 2, "Prim. Vtx" );
   // SetCutName( "EL", "weighted", 3, "single electron" );   

   return success;
}


/////////////////////////////////////////


bool CutFlowTTbarResolvedParticleLevel::Apply( EventData * ed )
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
  CutFlowPluginFactory_TTbarResolvedParticleLevel * MakeCutFlowPlugin() {
    return new CutFlowPluginFactory_TTbarResolvedParticleLevel( "TTbarResolvedParticleLevel" );
  };
}

