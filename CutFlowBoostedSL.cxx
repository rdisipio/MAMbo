#include "CutFlowBoostedSL.h"

CutFlowBoostedSL::CutFlowBoostedSL()
{
}

CutFlowBoostedSL::~CutFlowBoostedSL()
{
}


/////////////////////////////////////////


bool CutFlowBoostedSL::Apply( EventData * ed, int * lastCutPassed )
{
  bool success = true;

  Start();

  double weight = ed->info.mcWeight;

  int jet_n = ed->jets.n;

  m_hm->GetHistogram( "jet_n" )->Fill( jet_n, weight );
  for( int j = 0 ; j < jet_n ; ++j ) {
    m_hm->GetHistogram( "jet_pt" )->Fill( ed->jets.pT.at( j ) / GeV, weight );
  }

  m_hm->GetHistogram( "fjet_pt" )->Fill( ed->fjet.pT / GeV, weight );

  return success;
}


/////////////////////////////////////////
// Plugin

extern "C" {
  CutFlowPluginFactory_BoostedSL * MakeCutFlowPlugin() {
    return new CutFlowPluginFactory_BoostedSL( "BoostedSL" );
  };
}

