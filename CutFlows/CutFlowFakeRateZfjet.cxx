#include "CutFlowFakeRateZfjet.h"

CutFlowFakeRateZfjet::CutFlowFakeRateZfjet()
{
  SetCounterName( "cutflow" );

  cout << "DEBUG: ZpT min = " << m_config->cuts["ZpTmin"] << endl;
}

CutFlowFakeRateZfjet::~CutFlowFakeRateZfjet()
{
}


/////////////////////////////////////////


bool CutFlowFakeRateZfjet::Apply( EventData * ed, int * lastCutPassed )
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

  if( jet_n == 0 ) return success;
  PassedCut( weight );

  
  const int fjet_n = HelperFunctions::FindFatJets( ed, 200*GeV, fastjet::cambridge_algorithm, 1.2 );

  
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
    m_hm->GetHistogram( "jet_m" )->Fill( ed->jets.m.at( j ) / GeV, weight );
  }
  
  m_hm->GetHistogram( "fjet_n" )->Fill( jet_n, weight );
  for( int j = 0 ; j < fjet_n ; ++j ) {
    m_hm->GetHistogram( "fjet_pt" )->Fill( ed->fjets.pT.at( j ) / GeV, weight );
    m_hm->GetHistogram( "fjet_eta" )->Fill( ed->fjets.eta.at( j ), weight );
    m_hm->GetHistogram( "fjet_phi" )->Fill( ed->fjets.phi.at( j ), weight );
    m_hm->GetHistogram( "fjet_E" )->Fill( ed->fjets.E.at( j ) / GeV, weight );
    m_hm->GetHistogram( "fjet_m" )->Fill( ed->fjets.m.at( j ) / GeV, weight );
  }
  
  
  TLorentzVector Z, l1, l2, fj;
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

  if( ZpT < 200 * GeV ) return success;
  PassedCut( weight );

  // No. of fat jets > 0
  if( fjet_n == 0 ) return success;
  PassedCut( weight );

  fj.SetPtEtaPhiE( ed->fjets.pT.at( 0 ), ed->fjets.eta.at( 0 ), ed->fjets.phi.at( 0 ), ed->fjets.E.at( 0 ) );

  double dPhi = fabs( Z.DeltaPhi( fj ) );
  m_hm->GetHistogram( "dPhi_Zfj_allZ" )->Fill( dPhi, weight );
  m_hm->Get2DHistogram( "fjet_pt_vs_Z_pt" )->Fill( ZpT/GeV, fj.Pt()/GeV, weight );
  m_hm->Get2DHistogram( "dPhi_Zfj_vs_Z_pt" )->Fill( ZpT/GeV, dPhi, weight );

  int tjet_n = 0;
  for( int i = 0 ; i < fjet_n ; ++i ) {
    if( ed->fjets.tag.at(i) == 1 ) {
      ++tjet_n;

      m_hm->GetHistogram( "hadt_m" )->Fill( ed->fjets.hadt_m.at(i) / GeV, weight );
      m_hm->GetHistogram( "hadt_pt" )->Fill( ed->fjets.pT.at(i) / GeV, weight );
      m_hm->GetHistogram( "hadt_pt_zoom" )->Fill( ed->fjets.pT.at(i) / GeV, weight );
    }
  }
  m_hm->GetHistogram( "tjet_n" )->Fill( tjet_n, weight );
  
  // dPhi( Z, fj ) ~ back to back 
  m_hm->GetHistogram( "dPhi_Zfj_hiPtZ" )->Fill( dPhi, weight );
 
  m_hm->GetHistogram( "fjet_pt_hiPtZ" )->Fill( fj.Pt() / GeV, weight );

  if( dPhi < 2.5 ) return success;
  PassedCut( weight );

  return success;
}


/////////////////////////////////////////
// Plugin

extern "C" {
  CutFlowPluginFactory_FakeRateZfjet * MakeCutFlowPlugin() {
    return new CutFlowPluginFactory_FakeRateZfjet( "FakeRateZfjet" );
  };
}

