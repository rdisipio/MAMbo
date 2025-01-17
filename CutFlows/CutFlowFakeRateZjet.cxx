#include "CutFlowFakeRateZjet.h"

CutFlowFakeRateZjet::CutFlowFakeRateZjet()
{
  SetCounterName( "cutflow" );

  cout << "DEBUG: ZpT min = " << m_config->cuts["ZpTmin"] << endl;
}

CutFlowFakeRateZjet::~CutFlowFakeRateZjet()
{
}


/////////////////////////////////////////


bool CutFlowFakeRateZjet::Apply( EventData * ed, int * lastCutPassed )
{
  bool success = true;

  CutFlow::Start();

  double weight = ed->info.eventWeight;

  PassedCut( weight );

  int el_n  = ed->electrons.n;
  int mu_n  = ed->muons.n;
  int jet_n = ed->jets.n;

  //////////////////////
  // init real cutflow

  if( el_n > 0 ) return success;
  PassedCut( weight );

  if( mu_n < 2 ) return success;
  PassedCut( weight );

  if( jet_n != 1 ) return success;
  PassedCut( weight );
  
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
    m_hm->GetHistogram( "jet_m" )->Fill( ed->jets.m.at( j ), weight );
  }
  
  
  TLorentzVector Z, l1, l2, j1;
  l1.SetPtEtaPhiE( ed->muons.pT.at( 0 ), ed->muons.eta.at( 0 ), ed->muons.phi.at( 0 ), ed->muons.E.at( 0 ) );
  l2.SetPtEtaPhiE( ed->muons.pT.at( 1 ), ed->muons.eta.at( 1 ), ed->muons.phi.at( 1 ), ed->muons.E.at( 1 ) );

  // Di-lepton Invariant mass
  Z = l1 + l2;
  m_hm->GetHistogram( "m_ll" )->Fill( Z.M() / GeV, weight );
  m_hm->GetHistogram( "m_ll_high" )->Fill( Z.M() / GeV, weight );

  if( fabs( Z.M() - 91.2*GeV ) > 10*GeV ) return success;
  PassedCut( weight );

  // Z Transverse momentum
  double ZpT = Z.Pt();
  m_hm->GetHistogram( "Z_pt" )->Fill( ZpT/GeV, weight );

  j1.SetPtEtaPhiE( ed->jets.pT.at( 0 ), ed->jets.eta.at( 0 ), ed->jets.phi.at( 0 ), ed->jets.E.at( 0 ) );
  double dPhi = fabs( Z.DeltaPhi( j1 ) );
  m_hm->GetHistogram( "dPhi_Zj_allZ" )->Fill( dPhi, weight );

  for( int j = 0 ; j < jet_n ; ++j ) {
    m_hm->Get2DHistogram( "jet_pt_vs_Z_pt" )->Fill( ZpT/GeV, ed->jets.pT.at(j)/GeV, weight );
  }
  m_hm->Get2DHistogram( "dPhi_Zj1_vs_Z_pt" )->Fill( ZpT/GeV, dPhi, weight );

  if( ZpT < 200 * GeV ) return success;
  PassedCut( weight );

  // dPhi( Z, j ) ~ back to back 
  m_hm->GetHistogram( "dPhi_Zj_hiPtZ" )->Fill( dPhi, weight );
  for( int j = 0 ; j < jet_n ; ++j ) {
    m_hm->GetHistogram( "jet_pt_hiPtZ" )->Fill( ed->jets.pT.at( j ) / GeV, weight );
    //m_hm->GetHistogram( "jet_eta" )->Fill( ed->jets.eta.at( j ), weight );
    //m_hm->GetHistogram( "jet_phi" )->Fill( ed->jets.phi.at( j ), weight );
    //m_hm->GetHistogram( "jet_E" )->Fill( ed->jets.E.at( j ) / GeV, weight );
    //m_hm->GetHistogram( "jet_m" )->Fill( ed->jets.m.at( j ), weight );
  }  

  if( ( jet_n > 1 ) && ( ed->jets.pT.at(1) > 30*GeV ) ) return success;
  //if( dPhi < 2.5 ) return success;
  PassedCut( weight );

  return success;
}


/////////////////////////////////////////
// Plugin

extern "C" {
  CutFlowPluginFactory_FakeRateZjet * MakeCutFlowPlugin() {
    return new CutFlowPluginFactory_FakeRateZjet( "FakeRateZjet" );
  };
}

