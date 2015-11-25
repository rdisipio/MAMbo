#include "CutFlowBoostedSL.h"

CutFlowBoostedSL::CutFlowBoostedSL()
{
}

CutFlowBoostedSL::~CutFlowBoostedSL()
{
}
/////////////////////////////////////////

bool CutFlowBoostedSL::Initialize() {
    bool success = true;

    
    AddChannel("LPLUSJETS");
    
    AddCounterName("LPLUSJETS", "reco_unweight", 5 );
    SetCutName("LPLUSJETS", "reco_unweight", 0, "All Events after Analysis Top Cuts");
    SetCutName("LPLUSJETS", "reco_unweight", 1, "Tagger");
    SetCutName("LPLUSJETS", "reco_unweight", 2, "One jet in a DeltaR from lepton");
    SetCutName("LPLUSJETS", "reco_unweight", 3, "DeltaR jet Large-R jet");
    SetCutName("LPLUSJETS", "reco_unweight", 4, "DeltaPhi jet lepton");
    SetCutName("LPLUSJETS", "reco_unweight", 5, "Btag" );
    
    return success;
}


//bool CutFlowBoostedSL::Apply( EventData * ed, int * lastCutPassed )
bool CutFlowBoostedSL::Apply( EventData * ed)
{
  bool success = true;

  CutFlow::Start();

  //////MANAGE THE WEIGHTS//////////////////////////////////////////
  double weight_reco_level     = 1.;
  double weight_particle_level = 1.;
  
  weight_reco_level     = ed->info.mcWeight;
  weight_particle_level = ed->info.mcWeight;
  
  const double scaleFactor_PILEUP     = ed->property["scaleFactor_PILEUP"];
  // const double scaleFactor_ZVERTEX    = ed->property["scaleFactor_ZVERTEX"];
  ///const double scaleFactor_TRIGGER    = ed->property["scaleFactor_TRIGGER"];
  const double scaleFactor_LEPTON     = ed->property["scaleFactor_LEPTON"]; 
  //  const double scaleFactor_JVFSF      = ed->property["scaleFactor_JVFSF"]; 
  const double scaleFactor_BTAG       = ed->property["scaleFactor_BTAG"];
  
  // THis is what we have now (TO BE FIXED with nedeed wrights)
  weight_reco_level *= scaleFactor_PILEUP * scaleFactor_LEPTON * scaleFactor_BTAG;
   
  // in 8 TeV analysis we had only PILEUP and ZVERTEX
  weight_particle_level *= scaleFactor_PILEUP; // * scaleFactor_ZVERTEX;
  
  //Set the weights as event properties so we can call in the selections
  ed->property["weight_reco_level"]     = weight_reco_level;
  ed->property["weight_particle_level"] = weight_particle_level;
  
  
  // Apply selections 
  const bool passedRecoSelection     = PassedCutFlowReco( ed );
  const bool passedParticleSelection = PassedCutFlowParticle( ed );
  
  

  return success;
}




/////////////////////////////////////////RECO SELECTION //////////////////////////////
bool  CutFlowBoostedSL::PassedCutFlowReco(EventData * ed) {
  bool passed = true;
  
  
    string Tagger = "none";
  
     if( m_config->custom_params_string.count( "tagger" ) )
     {
       Tagger=m_config->custom_params_string["tagger"].c_str();
    }
    
  
    int    el_n   = ed->electrons.n; 
    int    mu_n   = ed->muons.n; 
    int    jet_n  = ed->jets.n;
    int    bjet_n = ed->bjets.n;
    int    fjet_n = ed->fjets.n;
    double ETmiss = ed->MET.et;
    double mwt    = ed->MET.mwt;
    
    int TopJetCandidate = -1;
    int LepTopJetCandidate = -1;

    const double weight = ed->property["weight_reco_level"];
    const bool passed_boosted_ejets = ed->property["passed_boosted_ejets_1fj0b"]; ///Preselection done in AT for el-channel
    const bool passed_boosted_mujets = ed->property["passed_boosted_mujets_1fj0b"]; ///Preselection done in AT for mu-channel  
      
      
   
    const bool  single_lept = ( m_config->channel == kElectron )  ?  ( passed_boosted_ejets) : ( passed_boosted_mujets );     
    if( !single_lept )   return !passed;
    
    PassedCut( "LPLUSJETS", "reco_unweight");  
    
    cout<< "Number of Large-R jet   " <<  fjet_n  << endl;
    
    int taggedEvent=0;
    
    for( int lj = 0 ; lj < fjet_n ; ++lj ) {
      const double sd12  = ed->fjets.property["sd12"].at(lj);
      const double tau32 = ed->fjets.property["tau32"].at(lj);
      const double tau21 = ed->fjets.property["tau21"].at(lj);
      //const int topTag50 = ed->fjets.property["topTag50"].at(lj);
      
      int topTag = 0;
      if(Tagger != "none")
      topTag = ed->fjets.property[Tagger.c_str()].at(lj);
      else 
      {
	cout<<"FATAL::Top Tagger not set in config file"<<endl;
	exit(1);
      }
      cout<<"property topTag "<<topTag<<endl;
      //   cout<< " ed->fjets.pT.at(lj) "  <<  ed->fjets.pT.at(lj)  << endl;
      if(topTag == 1 && (ed->fjets.pT.at(lj) > 300 * GeV) && fabs(ed->fjets.eta.at(lj)) < 2){
	taggedEvent++;
	TopJetCandidate = lj;
	m_hm->GetHistogram( "reco/1fj1b/topH/pt" )->Fill( ed->fjets.pT.at(lj) / GeV, weight );
	break;
      }
    }
    
    if(!taggedEvent) return !passed;
    PassedCut( "LPLUSJETS", "reco_unweight");
    
    
    // Exist a jet with deltaR(lep,jet)<1.5;
    
    const bool control = ( m_config->channel == kElectron ) ? (el_n >= 1 && ed->electrons.pT.at(0)>25000) : (mu_n >= 1 && ed->muons.pT.at(0)>25000);
    
    
    if (!control) {
       cout<<"WARNING the lepton selection coud be broken!"<<endl;
       exit(1);
    }
  
    TLorentzVector lepton;
    if ( m_config->channel == kElectron ) lepton.SetPtEtaPhiE(ed->electrons.pT.at(0), ed->electrons.eta.at(0), ed->electrons.phi.at(0), ed->electrons.E.at(0));
    else lepton.SetPtEtaPhiE(ed->muons.pT.at(0), ed->muons.eta.at(0), ed->muons.phi.at(0), ed->muons.E.at(0));
    
   
    double dR_min = 1;
    for( int sj = 0 ; sj < jet_n ; ++sj ) {
      
      double dR = PhysicsHelperFunctions::deltaR(lepton.Eta(),ed->jets.eta.at(sj),lepton.Phi(),ed->jets.phi.at(sj));
      if (dR < 1.5) {
	LepTopJetCandidate = sj;
	break;
      }
      
    }
    
    if(LepTopJetCandidate == -1) return !passed;
    PassedCut( "LPLUSJETS", "reco_unweight");
    
    // deltaR between the TopJetCandidate and LepTopJetCandidate ;
    double dR_jetljet = PhysicsHelperFunctions::deltaR(ed->fjets.eta.at(TopJetCandidate),ed->jets.eta.at(LepTopJetCandidate),ed->fjets.phi.at(TopJetCandidate),ed->jets.phi.at(LepTopJetCandidate));
    if ( dR_jetljet < 1.5) return !passed;
    PassedCut( "LPLUSJETS", "reco_unweight");
    
    // deltaPhi between the TopJetCandidate and lepton ;
    double dPhi_lepljet = PhysicsHelperFunctions::deltaPhi(ed->fjets.phi.at(TopJetCandidate),lepton.Phi());
    if ( dPhi_lepljet < 1) return !passed;
    PassedCut( "LPLUSJETS", "reco_unweight");
    
    //btag in the event
    
    if ( bjet_n < 1) return !passed;
    PassedCut( "LPLUSJETS", "reco_unweight");
    
     // deltaPhi between the TopJetCandidate and lepton ;
     //// Splitting the lepton channel /////////////////
    // if ( m_config->channel == kElectron )
    //   {
    
    //   }
    // else {
    
    // }
        
    return passed;
}
/////////////////////////////////////////PARTICLE SELECTION //////////////////////////////
bool  CutFlowBoostedSL::PassedCutFlowParticle(EventData * ed) {
  bool passed = true;


  return passed;
  

}
/////////////////////////////////////////

// Plugin
extern "C" {
  CutFlowPluginFactory_BoostedSL * MakeCutFlowPlugin() {
    return new CutFlowPluginFactory_BoostedSL( "BoostedSL" );
  };
}

