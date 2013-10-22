#include "CutFlowTTHTo2LeptonsSS.h"

CutFlowTTHTo2LeptonsSS::CutFlowTTHTo2LeptonsSS()
{
  AddChannel( "ELEL" );

  AddCounterName( "ELEL", "weighted" );
  AddCounterName( "ELEL", "unweight" );
}

CutFlowTTHTo2LeptonsSS::~CutFlowTTHTo2LeptonsSS()
{
}


/////////////////////////////////////////


bool CutFlowTTHTo2LeptonsSS::Initialize()
{
  bool success = true;

  SetCutName( "ELEL", "weighted", 0, "All Events" );
  SetCutName( "ELEL", "weighted", 1, "Trigger" );
  SetCutName( "ELEL", "weighted", 2, "Prim. Vtx" );
  SetCutName( "ELEL", "weighted", 3, "Cleaning" );
  SetCutName( "ELEL", "weighted", 4, "2 leptons" );
  SetCutName( "ELEL", "weighted", 5, "2 electrons" );
  SetCutName( "ELEL", "weighted", 6, ">= 1 SS pair" );
  SetCutName( "ELEL", "weighted", 7, "Z mass veto" );
  SetCutName( "ELEL", "weighted", 8, ">= 2 jet" );

  SetCutName( "ELEL", "unweight", 0, "All Events" );
  SetCutName( "ELEL", "unweight", 1, "Trigger" );
  SetCutName( "ELEL", "unweight", 2, "Prim. Vtx" );
  SetCutName( "ELEL", "unweight", 3, "Cleaning" );
  SetCutName( "ELEL", "unweight", 4, "2 leptons" );
  SetCutName( "ELEL", "unweight", 5, "2 electrons" );
  SetCutName( "ELEL", "unweight", 6, ">= 1 SS pair" );
  SetCutName( "ELEL", "unweight", 7, "Z mass veto" );
  SetCutName( "ELEL", "unweight", 8, ">= 2 jet" );

  return success;
}


/////////////////////////////////////////


bool CutFlowTTHTo2LeptonsSS::Apply( EventData * ed )
{
  bool success = true;

  CutFlow::Start();

  //// example:
  double weight = ed->info.mcWeight;
  PassedCut( "ELEL", "weighted", weight );
  PassedCut( "ELEL", "unweight" );
 
  // Pass electron trigger
  bool trigflag = 
    ( PASSED_TRIGGER( "EF_e24vhi_medium1" ) || PASSED_TRIGGER( "EF_e24vhi_medium1" ) ) ||
    ( PASSED_TRIGGER( "EF_e60_medium1" )    || PASSED_TRIGGER( "EF_mu24i_tight" ) );
  if( !trigflag ) return success;
  PassedCut( "ELEL", "weighted", weight );
  PassedCut( "ELEL", "unweight" );

  // PV
  if( int(ed->property["goodPV"]) == 0 ) return success;
  PassedCut( "ELEL", "weighted", weight );
  PassedCut( "ELEL", "unweight" );

  // Event cleaning
  if( int( ed->property["passEventCleaning"] ) != 1 ) return success;
  PassedCut( "ELEL", "weighted", weight );
  PassedCut( "ELEL", "unweight" );


  int el_n  = ed->electrons.n;
  int mu_n  = ed->muons.n;
  int jet_n = ed->jets.n;

  double ETmiss = ed->MET.et;
  if( ETmiss == 0. ) ETmiss = -1e10;
  m_hm->GetHistogram( "met_pt" )->Fill( ETmiss/GeV, weight );

  m_hm->GetHistogram( "el_n" )->Fill( el_n, weight );
  for( int j = 0 ; j < el_n ; ++j ) {
    m_hm->GetHistogram( "el_pt" )->Fill( ed->electrons.pT.at( j ) / GeV, weight );
    m_hm->GetHistogram( "el_eta" )->Fill( ed->electrons.eta.at( j ), weight );
    m_hm->GetHistogram( "el_phi" )->Fill( ed->electrons.phi.at( j ), weight );
    m_hm->GetHistogram( "el_E" )->Fill( ed->electrons.E.at( j ) / GeV, weight );

    double etcone20_o_pT = ed->electrons.property["Etcone20"].at(j) / ed->electrons.pT.at( j );
    m_hm->GetHistogram( "el_Etcone20_over_pT" )->Fill( etcone20_o_pT, weight );
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

  // At least 2 electrons, or 2 muons, or 1e1mu
  if( ( el_n + mu_n ) < 2 ) return success;
  PassedCut( "ELEL", "weighted", weight );
  PassedCut( "ELEL", "unweight" );

  // 2 el
  if( el_n < 2 ) return success;
  PassedCut( "ELEL", "weighted", weight );
  PassedCut( "ELEL", "unweight" );

  // Same-sign
  const double q1 = ed->electrons.q[0];
  const double q2 = ed->electrons.q[1];
  if( q1*q2 < 0 ) return success;
  PassedCut( "ELEL", "weighted", weight );
  PassedCut( "ELEL", "unweight" );

  // Z mass veto
  TLorentzVector Z = HelperFunctions::MakeFourMomentum( ed->electrons, 0 ) + HelperFunctions::MakeFourMomentum( ed->electrons, 1 );
  if( fabs( Z.M()/GeV - 91.2 ) <= 10. ) return success;
  PassedCut( "ELEL", "weighted", weight );
  PassedCut( "ELEL", "unweight" );

  // jet count
  if( jet_n < 2 ) return success;
  PassedCut( "ELEL", "weighted", weight );
  PassedCut( "ELEL", "unweight" );

  return success;
}


/////////////////////////////////////////
// Plugin

extern "C" {
  CutFlowPluginFactory_TTHTo2LeptonsSS * MakeCutFlowPlugin() {
    return new CutFlowPluginFactory_TTHTo2LeptonsSS( "TTHTo2LeptonsSS" );
  };
}

