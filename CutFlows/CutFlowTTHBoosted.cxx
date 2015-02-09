#include "CutFlowTTHBoosted.h"

CutFlowTTHBoosted::CutFlowTTHBoosted()
{
    m_cutAlias = {
        "beforeCuts", "trig", "pvtx", "2lep", "pTlep", "met", "1fjet", "2fjet"
    };
  
}

CutFlowTTHBoosted::~CutFlowTTHBoosted()
{
}


/////////////////////////////////////////


bool CutFlowTTHBoosted::Initialize()
{
   bool success = true;

   static int n_cuts = 7;

   AddChannel( "EMU" );

   AddCounterName( "EMU", "unweight", n_cuts ); 
   SetCutName( "EMU", "unweight", 0, "All event" );
   SetCutName( "EMU", "unweight", 1, "Trigger");
   SetCutName( "EMU", "unweight", 2, "Prim. Vtx");
   SetCutName( "EMU", "unweight", 3, "SingleLepton");
   SetCutName( "EMU", "unweight", 4, "Lep pT > 25 GeV" );
   SetCutName( "EMU", "unweight", 5, "ETmiss > 30 GeV");
   SetCutName( "EMU", "unweight", 6, "N akt4 jets >= 1");
   SetCutName( "EMU", "unweight", 6, "N akt4 jets >= 2");

   AddCounterName( "EMU", "weighted", n_cuts );
   SetCutName( "EMU", "weighted", 0, "All event" );
   SetCutName( "EMU", "weighted", 1, "Trigger");
   SetCutName( "EMU", "weighted", 2, "Prim. Vtx");
   SetCutName( "EMU", "weighted", 3, "SingleLepton");
   SetCutName( "EMU", "weighted", 4, "Lep pT > 25 GeV" );
   SetCutName( "EMU", "weighted", 5, "ETmiss > 30 GeV");
   SetCutName( "EMU", "weighted", 6, "N akt4 jets >= 1");
   SetCutName( "EMU", "weighted", 6, "N akt4 jets >= 2"); 

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


bool CutFlowTTHBoosted::Apply( EventData * ed )
{
  bool success = true;

  CutFlow::Start();

  //// example:
  // double weight = ed->info.mcWeight;
  // m_hm->GetHistogram( "fjet_pt" )->Fill( ed->fjet.pT / GeV, weight );
  //
  // PassedCut( "EL", "unweight" );
  // PassedCut( "EL", "weighted", 1.05 );

  const bool passedSelection_emu_2t  = PassedCutFlow_emu_2t( ed );

  return success;
}


/////////////////////////////////////////


bool CutFlowTTHBoosted::PassedCutFlow_emu_2t( EventData * ed ) 
{ 
    bool passed = true;

    double weight = ed->info.mcWeight;

    int    el_n   = ed->electrons.n;
    int    mu_n   = ed->muons.n;   
    int    jet_n  = ed->jets.n;
    int    fjet_n = ed->fjets.n;
    int    bjet_n = ed->bjets.n;
    double ETmiss = ed->MET.et;
  
    // 0) All events
    PassedCut( "EMU", "reco_weighted", weight );
    PassedCut( "EMU", "reco_unweight");
//    FillHistogramsControlPlotsReco( values );
    
    // 1) Trigger
    PassedCut("EMU", "reco_weighted", weight );
    PassedCut("EMU", "reco_unweight");

    // 2) Prim. Vtx
    PassedCut("EMU", "reco_weighted", weight );
    PassedCut("EMU", "reco_unweight");

    // 3) 1 el && 1 mu
    if( (el_n != 1) && (mu_n != 1 ) ) return !passed;

    PassedCut("EMU", "reco_weighted", weight );
    PassedCut("EMU", "reco_unweight");

    // 4) lepton pT
    const double el_pt = ed->electrons.pT.at(0);
    const double mu_pt = ed->muons.pT.at(0);

    if( el_pt < 25 * GeV ) return !passed;
    if( mu_pt < 25 * GeV ) return !passed;
    PassedCut("EMU", "reco_weighted", weight );
    PassedCut("EMU", "reco_unweight");

    // 5) ETmiss cut
    if( ETmiss < 20 * GeV ) return !passed;
    PassedCut("EMU", "reco_weighted", weight );
    PassedCut("EMU", "reco_unweight");

    // 6) N fat jets >= 1
    if( fjet_n < 1 ) return !passed;
    PassedCut("EMU", "reco_weighted", weight );
    PassedCut("EMU", "reco_unweight");

    // 7) N fat jets >= 2
    if(	fjet_n < 2 ) return !passed;
    PassedCut("EMU", "reco_weighted", weight );
    PassedCut("EMU", "reco_unweight");

    return passed;
}

/////////////////////////////////////////
// Plugin

extern "C" {
  CutFlowPluginFactory_TTHBoosted * MakeCutFlowPlugin() {
    return new CutFlowPluginFactory_TTHBoosted( "TTHBoosted" );
  };
}

