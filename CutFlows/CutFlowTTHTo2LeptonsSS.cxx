#include "CutFlowTTHTo2LeptonsSS.h"

CutFlowTTHTo2LeptonsSS::CutFlowTTHTo2LeptonsSS()
{
}

CutFlowTTHTo2LeptonsSS::~CutFlowTTHTo2LeptonsSS()
{
}


/////////////////////////////////////////


bool CutFlowTTHTo2LeptonsSS::Apply( EventData * ed, int * lastCutPassed )
{
  bool success = true;

  CutFlow::Start();

  //// example:
  double weight = ed->info.mcWeight;
  /*
  if( fabs(weight) > 10. ) {
    cout << "WARNING: very large event weight = " << weight << " re-set to zero" << endl;
    weight = 0.;
  }
  */
  // m_hm->GetHistogram( "fjet_pt" )->Fill( ed->fjet.pT / GeV, weight );

  if( !( PASSED_TRIGGER( "EF_e24vhi_medium1" ) || 
	 PASSED_TRIGGER( "EF_e24vhi_medium1" ) ||
	 PASSED_TRIGGER( "EF_e60_medium1" ) ||
	 PASSED_TRIGGER( "EF_mu24i_tight" ) ) )
      return success;

  PassedCut( weight );
  

  double ETmiss = ed->MET.et;
  if( ETmiss == 0. ) ETmiss = -1e10;
  m_hm->GetHistogram( "met_pt" )->Fill( ETmiss/GeV, weight );

  int el_n  = ed->electrons.n;
  int mu_n  = ed->muons.n;
  int jet_n = ed->jets.n;

  m_hm->GetHistogram( "el_n" )->Fill( el_n, weight );
  for( int j = 0 ; j < el_n ; ++j ) {
    m_hm->GetHistogram( "el_pt" )->Fill( ed->electrons.pT.at( j ) / GeV, weight );
    m_hm->GetHistogram( "el_eta" )->Fill( ed->electrons.eta.at( j ), weight );
    m_hm->GetHistogram( "el_phi" )->Fill( ed->electrons.phi.at( j ), weight );
    m_hm->GetHistogram( "el_E" )->Fill( ed->electrons.E.at( j ) / GeV, weight );
  }
  
  m_hm->GetHistogram( "mu_n" )->Fill( mu_n, weight );
  for( int j = 0 ; j < mu_n ; ++j ) {
    m_hm->GetHistogram( "mu_pt" )->Fill( ed->muons.pT.at( j ) / GeV, weight );
    m_hm->GetHistogram( "mu_eta" )->Fill( ed->muons.eta.at( j ), weight );
    m_hm->GetHistogram( "mu_phi" )->Fill( ed->muons.phi.at( j ), weight );
    m_hm->GetHistogram( "mu_E" )->Fill( ed->muons.E.at( j ) / GeV, weight );
  }

  m_hm->GetHistogram( "jet_n" )->Fill( jet_n, weight );
  for( int j = 0 ; j < jet_n ; ++j ) {
    m_hm->GetHistogram( "jet_pt" )->Fill( ed->jets.pT.at( j ) / GeV, weight );
    m_hm->GetHistogram( "jet_eta" )->Fill( ed->jets.eta.at( j ), weight );
    m_hm->GetHistogram( "jet_phi" )->Fill( ed->jets.phi.at( j ), weight );
    m_hm->GetHistogram( "jet_E" )->Fill( ed->jets.E.at( j ) / GeV, weight );
  }


  return success;
}


/////////////////////////////////////////
// Plugin

extern "C" {
  CutFlowPluginFactory_TTHTo2LeptonsSS * MakeCutFlowPlugin() {
    return new CutFlowPluginFactory_TTHTo2LeptonsSS( "TTHTo2LeptonsSS" );
  };
}

