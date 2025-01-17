#include "CutFlowTTHBoosted.h"

CutFlowTTHBoosted::CutFlowTTHBoosted()
{
/*
    m_cutAlias = {
        "beforeCuts", "trig", "pvtx", "2l", "xET30", "2l1fj", "2l2fj"
    };
*/  
}

CutFlowTTHBoosted::~CutFlowTTHBoosted()
{
}


/////////////////////////////////////////


bool CutFlowTTHBoosted::Initialize()
{
   bool success = true;

   static int n_cuts = 6;

   AddChannel( "EMU" );

   AddCounterName( "EMU", "unweight", n_cuts ); 
   SetCutName( "EMU", "unweight", 0, "All events",        "beforeCuts" );
   SetCutName( "EMU", "unweight", 1, "Trigger",           "tri" );
   SetCutName( "EMU", "unweight", 2, "Prim. Vtx",         "ptx" );
   SetCutName( "EMU", "unweight", 3, "1e1mu pT > 25 GeV", "2l" );
   SetCutName( "EMU", "unweight", 4, "ETmiss > 30 GeV",   "xET30" );
   SetCutName( "EMU", "unweight", 5, "N akt10 jets >= 1", "2l1fj" );
   SetCutName( "EMU", "unweight", 6, "N akt10 jets >= 2", "2l2fj" );

   AddCounterName( "EMU", "weighted", n_cuts );
   SetCutName( "EMU", "weighted", 0, "All event",        "beforeCuts"  );
   SetCutName( "EMU", "weighted", 1, "Trigger",           "tri"   );
   SetCutName( "EMU", "weighted", 2, "Prim. Vtx",         "ptx"   );
   SetCutName( "EMU", "weighted", 3, "1e1mu pT > 25 GeV", "2l"    );
   SetCutName( "EMU", "weighted", 4, "ETmiss > 30 GeV",   "xET30" );
   SetCutName( "EMU", "weighted", 5, "N akt10 jets >= 1", "2l1fj" );
   SetCutName( "EMU", "weighted", 6, "N akt10 jets >= 2", "2l2fj" ); 

   return success;
}


/////////////////////////////////////////


bool CutFlowTTHBoosted::Apply( EventData * ed )
{
  bool success = true;

  CutFlow::Start();

  double weight = ed->info.mcWeight;
  ed->property["weight"] = weight;

  const bool passedSelection_emu_2t  = PassedCutFlow_emu_2t( ed );

  return success;
}


/////////////////////////////////////////


bool CutFlowTTHBoosted::PassedCutFlow_emu_2t( EventData * ed ) 
{ 
    bool passed = true;
  
    double weight = ed->property["weight"];
    int    el_n   = ed->electrons.n;
    int    mu_n   = ed->muons.n;   
    int    jet_n  = ed->jets.n;
    int    fjet_n = ed->fjets.n;
    int    bjet_n = ed->bjets.n;
    double ETmiss = ed->MET.et;
  
    // 0) All events
    PassedCut( "EMU", "weighted", weight );
    PassedCut( "EMU", "unweight");
    FillHistograms( ed );
    
    // 1) Trigger
    PassedCut("EMU", "weighted", weight );
    PassedCut("EMU", "unweight");

    // 2) Prim. Vtx
    PassedCut("EMU", "weighted", weight );
    PassedCut("EMU", "unweight");

    // 3) 1 el && 1 mu
    bool is_1el1mu = ( (el_n==1) && (mu_n==1) );
    bool is_2el    = ( (el_n==2) && (mu_n==0) );
    bool is_2mu    = ( (el_n==0) && (mu_n==2) );
    bool good_channel = is_1el1mu || is_2el || is_2mu;

    if( !good_channel ) return !passed;
//    if( el_n != 1 ) return !passed;
//    if(	mu_n !=	1 ) return !passed;
//    const double el_pt = ed->electrons.pT.at(0);
//    const double mu_pt = ed->muons.pT.at(0);
//    const double pt_1 = max( el_pt, mu_pt );
//    const double pt_2 = min( el_pt, mu_pt );
//    if( el_pt < 25 * GeV ) return !passed;
//    if( mu_pt < 25 * GeV ) return !passed;
    PassedCut("EMU", "weighted", weight );
    PassedCut("EMU", "unweight");
    FillHistograms( ed );

    // 4) ETmiss cut
    if( ETmiss < 20 * GeV ) return !passed;
    PassedCut("EMU", "weighted", weight );
    PassedCut("EMU", "unweight");
    FillHistograms( ed );

    // 5) N fat jets >= 1
    if( fjet_n < 1 ) return !passed;
    PassedCut("EMU", "weighted", weight );
    PassedCut("EMU", "unweight");
    FillHistograms( ed );

    // 6) N fat jets >= 2
    if(	fjet_n < 2 ) return !passed;
    PassedCut("EMU", "weighted", weight );
    PassedCut("EMU", "unweight");
    FillHistograms( ed );

    return passed;
}


///////////////////////////////////////////////


void CutFlowTTHBoosted::FillHistograms( const EventData * ed )
{ 
    const int cut = GetLastPassedCut( "EMU", "weighted" ) - 1;   
    const string cutflow = "EMU_weighted"; 
    string path = "reco/cutflow/" + m_cutAlias[cutflow][cut] + "/";    

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

    const int cl_n = ed->clusters.n; 
    m_hm->FillHistograms( path + "cl_n", cl_n, weight );
    for( int i = 0 ; i < cl_n ; ++i ) {
       const double E   = ed->clusters.E.at(i) / GeV;

       m_hm->FillHistograms( path + "cl_E",      E, weight );
    }
}



/////////////////////////////////////////
// Plugin

extern "C" {
  CutFlowPluginFactory_TTHBoosted * MakeCutFlowPlugin() {
    return new CutFlowPluginFactory_TTHBoosted( "TTHBoosted" );
  };
}

