#include "CutFlowTTbarAllHadBoosted.h"

CutFlowTTbarAllHadBoosted::CutFlowTTbarAllHadBoosted()
{
}

CutFlowTTbarAllHadBoosted::~CutFlowTTbarAllHadBoosted()
{
}


/////////////////////////////////////////


bool CutFlowTTbarAllHadBoosted::Initialize()
{
   bool success = true;

   AddChannel("ALLHADBOOSTED");
   AddCounterName( "ALLHADBOOSTED", "reco_unweight", 5 );
   SetCutName( "ALLHADBOOSTED", "reco_unweight", 0, "All Events after preselection      " );
   SetCutName( "ALLHADBOOSTED", "reco_unweight", 1, "1st leading jet pT > 500 GeV       " );
   SetCutName( "ALLHADBOOSTED", "reco_unweight", 2, "2nd leading jet pT > 350 GeV       " );
   SetCutName( "ALLHADBOOSTED", "reco_unweight", 3, "1st leading jet |m - mtop| < 50 GeV" );
   SetCutName( "ALLHADBOOSTED", "reco_unweight", 4, "2nd leading jet |m - mtop| < 50 GeV" );
   
   return success;
}


/////////////////////////////////////////


bool CutFlowTTbarAllHadBoosted::Apply( EventData * ed )
{
  bool success = true;

  CutFlow::Start();

  //////MANAGE THE WEIGHTS//////////////////////////////////////////
  double weight_reco_level     = 1.;
  double weight_particle_level = 1.;

  weight_reco_level     = ed->info.mcWeight;
  weight_particle_level = ed->info.mcWeight;

  // weight_reco_level *= scaleFactor_PILEUP * scaleFactor_LEPTON * scaleFactor_BTAG * scaleFactor_JVT;

  ed->property["weight_reco_level"]     = weight_reco_level;
  ed->property["weight_particle_level"] = weight_particle_level;

  PassedCut( "ALLHADBOOSTED", "reco_unweight" );
//  PassedCut( "ALLHADBOOSTED", "reco_weighted", weight_reco_level );

  return success;
}


/////////////////////////////////////////
// Plugin

extern "C" {
  CutFlowPluginFactory_TTbarAllHadBoosted * MakeCutFlowPlugin() {
    return new CutFlowPluginFactory_TTbarAllHadBoosted( "TTbarAllHadBoosted" );
  };
}

