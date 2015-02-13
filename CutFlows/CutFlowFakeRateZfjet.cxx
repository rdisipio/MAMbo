#include "CutFlowFakeRateZfjet.h"

CutFlowFakeRateZfjet::CutFlowFakeRateZfjet()
{
//  cout << "DEBUG: ZpT min = " << m_config->cuts["ZpTmin"] << endl;

  m_cutAlias = {
        "beforeCuts", "0el", "2mu", "Zm", "ZpT", "1fj", "dPhi_Zfj"
    };
}

CutFlowFakeRateZfjet::~CutFlowFakeRateZfjet()
{
}


/////////////////////////////////////////


bool CutFlowFakeRateZfjet::Initialize()
{
   bool success = true;

   static int n_cuts = 6;

   AddChannel( "MU" );

   AddCounterName( "MU", "unweight", n_cuts ); 
   SetCutName( "MU", "unweight", 0, "All events" );
   SetCutName( "MU", "unweight", 1, "0 electrons");
   SetCutName( "MU", "unweight", 2, "2 muons");
   SetCutName( "MU", "unweight", 3, "Z mass window" );
   SetCutName( "MU", "unweight", 4, "Z pT > 200" ); 
   SetCutName( "MU", "unweight", 5, "N akt10 jets >= 1");
   SetCutName( "MU", "unweight", 6, "dPhi(Z,fj) > 2.5" );

   AddCounterName( "MU", "weighted", n_cuts );
   SetCutName( "MU", "weighted", 0, "All events" );
   SetCutName( "MU", "weighted", 1, "0 electrons");
   SetCutName( "MU", "weighted", 2, "2 muons");
   SetCutName( "MU", "weighted", 3, "Z mass window" );
   SetCutName( "MU", "weighted", 4, "Z pT > 200" ); 
   SetCutName( "MU", "weighted", 5, "N akt10 jets >= 1");
   SetCutName( "MU", "weighted", 6, "dPhi(Z,fj)	> 2.5" );


   return success;
}


/////////////////////////////////////////


bool CutFlowFakeRateZfjet::Apply( EventData * ed )
{
  bool success = true;

  CutFlow::Start();

  double weight = ed->info.mcWeight;
  ed->property["weight"] = weight;

  PassedCut( "MU", "unweight" );
  PassedCut( "MU", "weighted", weight );
  FillHistograms( ed );

  int el_n   = ed->electrons.n;
  int mu_n   = ed->muons.n;
  int jet_n  = ed->jets.n;
  int fjet_n = ed->fjets.n;

  //////////////////////
  // init real cutflow

  if( el_n > 0 ) return success;
  PassedCut( "MU", "unweight" );
  PassedCut( "MU", "weighted", weight );

  if( mu_n < 2 ) return success;
  PassedCut( "MU", "unweight" );
  PassedCut( "MU", "weighted", weight );

  TLorentzVector Z, l1, l2;
  l1 = HelperFunctions::MakeFourMomentum( ed->muons, 0 );
  l2 = HelperFunctions::MakeFourMomentum( ed->muons, 1 );

  Z = l1 + l2;
  ed->property["Z_m"]  = Z.M();
  ed->property["Z_pt"] = Z.Pt();

  FillHistograms( ed );

  // Z mass window
  if( fabs( Z.M() - 91.2*GeV ) > 10*GeV ) return success;
  PassedCut( "MU", "unweight" );
  PassedCut( "MU", "weighted", weight );
  FillHistograms( ed );

  // Z Transverse momentum
  if( Z.Pt() < 200 * GeV ) return success;
  PassedCut( "MU", "unweight" );
  PassedCut( "MU", "weighted", weight );
  FillHistograms( ed );

  // No. of fat jets > 0
  if( fjet_n == 0 ) return success;
  PassedCut( "MU", "unweight" );
  PassedCut( "MU", "weighted", weight );
  FillHistograms( ed );

  TLorentzVector fj = HelperFunctions::MakeFourMomentum( ed->fjets, 0 );

  double dPhi = fabs( Z.DeltaPhi( fj ) );
  ed->property["dPhi"] = dPhi;

/*
  m_hm->GetHistogram( "dPhi_Zfj_allZ" )->Fill( dPhi, weight );
  m_hm->Get2DHistogram( "fjet_pt_vs_Z_pt" )->Fill( ZpT/GeV, fj.Pt()/GeV, weight );
  m_hm->Get2DHistogram( "dPhi_Zfj_vs_Z_pt" )->Fill( ZpT/GeV, dPhi, weight );
*/

  // dPhi( Z, fj ) ~ back to back 

  if( dPhi < 2.5 ) return success;
  PassedCut( "MU", "unweight" );
  PassedCut( "MU", "weighted", weight );
  FillHistograms( ed );

  return success;
}


///////////////////////////////////////////////


void CutFlowFakeRateZfjet::FillHistograms( const EventData * ed )
{ 
    const int cut = GetLastPassedCut( "MU", "weighted" ) - 1;    
    string path = "reco/cutflow/" + m_cutAlias[cut] + "/";    

    const double weight = ed->property.at("weight");

    const int electron_n = ed->electrons.n;
    m_hm->FillHistograms( path + "el_n", electron_n, weight );
    for( int i = 0 ; i < electron_n ; ++i ) {
       const double pt  = ed->electrons.pT.at( i ) / GeV;
       const double eta = ed->electrons.eta.at(i);
       const double phi = ed->electrons.phi.at(i);

       m_hm->FillHistograms( path + "el_pt",   pt, weight );
       m_hm->FillHistograms( path + "el_eta", eta, weight );
       m_hm->FillHistograms( path + "el_phi", phi, weight );
    }

    const int muon_n = ed->muons.n;
    m_hm->FillHistograms( path + "mu_n", muon_n, weight );
    for( int i = 0 ; i < muon_n ; ++i ) {
       const double pt  = ed->muons.pT.at( i ) / GeV;
       const double eta = ed->muons.eta.at(i);
       const double phi = ed->muons.phi.at(i);

       m_hm->FillHistograms( path + "mu_pt",   pt, weight );
       m_hm->FillHistograms( path + "mu_eta", eta, weight );
       m_hm->FillHistograms( path + "mu_phi", phi, weight );
    }


    const int jet_n = ed->jets.n;
    m_hm->FillHistograms( path + "jet_n", jet_n, weight );
    for( int i = 0 ; i < jet_n ; ++i ) {
       const double pt = ed->jets.pT.at( i ) / GeV;
       const double eta = ed->jets.eta.at(i);
       const double phi = ed->jets.phi.at(i);
       const double m   = ed->jets.m.at(i) / GeV;

       m_hm->FillHistograms( path + "jet_pt",   pt, weight );
       m_hm->FillHistograms( path + "jet_eta", eta, weight );
       m_hm->FillHistograms( path + "jet_phi", phi, weight );
       m_hm->FillHistograms( path + "jet_m",     m, weight );
    }

    const int bjet_n = ed->bjets.n;
    m_hm->FillHistograms( path + "bjet_n", bjet_n, weight );
    for( int i = 0 ; i < bjet_n ; ++i ) {
       const double pt = ed->bjets.pT.at( i ) / GeV;
       const double eta = ed->bjets.eta.at(i);
       const double phi = ed->bjets.phi.at(i);
       const double m   = ed->bjets.m.at(i) / GeV;

       m_hm->FillHistograms( path + "bjet_pt",   pt, weight );
       m_hm->FillHistograms( path + "bjet_eta", eta, weight );
       m_hm->FillHistograms( path + "bjet_phi", phi, weight );
       m_hm->FillHistograms( path + "bjet_m",     m, weight );
    }

    const int fjet_n = ed->fjets.n;
    m_hm->FillHistograms( path + "fjet_n", fjet_n, weight );
    for( int i = 0 ; i < fjet_n ; ++i ) {
       const double pt = ed->fjets.pT.at( i ) / GeV;
       const double eta = ed->fjets.eta.at(i);
       const double phi = ed->fjets.phi.at(i);
       const double m   = ed->fjets.m.at(i) / GeV;

       m_hm->FillHistograms( path + "fjet_pt",   pt, weight );
       m_hm->FillHistograms( path + "fjet_eta", eta, weight );
       m_hm->FillHistograms( path + "fjet_phi", phi, weight );
       m_hm->FillHistograms( path + "fjet_m",     m, weight );
    }

    if( HelperFunctions::HasProperty( "Z_m", ed ) ) {
       const double Z_m  = ed->property.at("Z_m") / GeV;
       const double Z_pt = ed->property.at("Z_pt") / GeV; 

       m_hm->FillHistograms( path + "Z_m", Z_m, weight );
       m_hm->FillHistograms( path + "Z_pt", Z_pt, weight );
    }
    if( HelperFunctions::HasProperty( "dPhi", ed ) ) {
       const double dPhi = ed->property.at("dPhi");
   
       m_hm->FillHistograms( path + "dPhi", dPhi, weight );
    }

}


/////////////////////////////////////////
// Plugin

extern "C" {
  CutFlowPluginFactory_FakeRateZfjet * MakeCutFlowPlugin() {
    return new CutFlowPluginFactory_FakeRateZfjet( "FakeRateZfjet" );
  };
}

