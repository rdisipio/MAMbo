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
    SetCutName("LPLUSJETS", "reco_unweight", 0, "All Events after Analysis Top Cuts          ");
    SetCutName("LPLUSJETS", "reco_unweight", 1, "A tagged Large-R jet                        ");
    SetCutName("LPLUSJETS", "reco_unweight", 2, "Exist a jet with deltaPhi(lep,Large-R jet)>1");
    SetCutName("LPLUSJETS", "reco_unweight", 3, "Exist b-jet in the event                    ");
    SetCutName("LPLUSJETS", "reco_unweight", 4, "Exist a jet with deltaR(Large-R jet,jet)>1.5");
    SetCutName("LPLUSJETS", "reco_unweight", 5, "Exist a jet with deltaR(lepton,jet)<1.5     ");

    AddCounterName("LPLUSJETS", "particle_unweight", 5 );
    SetCutName("LPLUSJETS", "particle_unweight", 0, "All Events after Analysis Top Cuts          ");
    SetCutName("LPLUSJETS", "particle_unweight", 1, "A tagged Large-R jet                        ");
    SetCutName("LPLUSJETS", "particle_unweight", 2, "Exist a jet with deltaPhi(lep,Large-R jet)>1");
    SetCutName("LPLUSJETS", "particle_unweight", 3, "Exist b-jet in the event                    ");
    SetCutName("LPLUSJETS", "particle_unweight", 4, "Exist a jet with deltaR(Large-R jet,jet)>1.5");
    SetCutName("LPLUSJETS", "particle_unweight", 5, "Exist a jet with deltaR(lepton,jet)<1.5     ");

    
    return success;
}


//bool CutFlowBoostedSL::Apply( EventData * ed, int * lastCutPassed )
bool CutFlowBoostedSL::Apply( EventData * ed)
{
  bool success = true;

  CutFlow::Start();
  
  unsigned long isMCSignal = m_config->custom_params_flag["isMCSignal"];
  unsigned long isRealData = m_config->custom_params_flag["isRealData"];
 

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
  
  // Set to  1 for data
  if(isRealData) weight_reco_level = 1;   
  
  //Set the weights as event properties so we can call in the selections
  ed->property["weight_reco_level"]     = weight_reco_level;
  ed->property["weight_particle_level"] = weight_particle_level;
  
  
  // Apply selections 
  const bool passedRecoSelection     = PassedCutFlowReco( ed );
  const bool passedParticleSelection =  isRealData ? false : PassedCutFlowParticle( ed );
  
  

  return success;
}




/////////////////////////////////////////RECO SELECTION //////////////////////////////
bool  CutFlowBoostedSL::PassedCutFlowReco(EventData * ed) {
  bool passed = true;
  
  
  //The tagger name is taken from the configuration xml
    string Tagger = "none";
  
     if( m_config->custom_params_string.count( "tagger" ) )
     {
       Tagger=m_config->custom_params_string["tagger"].c_str();
    }
    
    //Read from EventData information on object needed for selection
    int    el_n   = ed->electrons.n; 
    int    mu_n   = ed->muons.n; 
    int    jet_n  = ed->jets.n;
    int    bjet_n = ed->bjets.n;
    int    fjet_n = ed->fjets.n;
    double ETmiss = ed->MET.et;
    double mwt    = ed->MET.mwt;

    
     //Initialize the index of the Hadronic topjetCandidate
    int HadTopJetCandidate = -1;
     //Container of small-R jet that pass requirements on the dR with lepton and HadTopJetCandidate
    vector<int> LepTopJetCandidate;

    double weight = ed->property["weight_reco_level"];
    
    
    const bool passed_boosted_ejets = ed->property["passed_boosted_ejets_1fj0b"]; ///Preselection done in AT for el-channel
    const bool passed_boosted_mujets = ed->property["passed_boosted_mujets_1fj0b"]; ///Preselection done in AT for mu-channel  
      
      
    //****************All event passing analysis top selection *************************
    const bool  single_lept = ( m_config->channel == kElectron )  ?  ( passed_boosted_ejets) : ( passed_boosted_mujets );     
    if( !single_lept )   return !passed;
    
    PassedCut( "LPLUSJETS", "reco_unweight");  
    
    //**************** Exist a tagged Large-R jet with pT>300000 and |eta|<2 *************************
    
    
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
      //cout<<"property topTag "<<topTag<<endl;
      if(topTag == 1 && (ed->fjets.pT.at(lj) > 300 * GeV) && fabs(ed->fjets.eta.at(lj)) < 2){
	//The first Large-R jet found has the highest pT, become the HadTopJetCandidate
	HadTopJetCandidate = lj;
	
	m_hm->GetHistogram( "reco/1fj1b/topJet/pt" )->Fill( ed->fjets.pT.at(lj) / GeV, weight );
	break;
      }
    }
    
    if(HadTopJetCandidate < 0) return !passed;
    PassedCut( "LPLUSJETS", "reco_unweight");
    
    
    
    
    const bool control = ( m_config->channel == kElectron ) ? (el_n >= 1 && ed->electrons.pT.at(0)>25000) : (mu_n >= 1 && ed->muons.pT.at(0)>25000);
    
    
    if (!control) {
       cout<<"WARNING the lepton selection coud be broken!"<<endl;
       exit(1);
    }
 
   //Define the lepton to use during selection
    TLorentzVector lepton;
    if ( m_config->channel == kElectron ) lepton.SetPtEtaPhiE(ed->electrons.pT.at(0), ed->electrons.eta.at(0), ed->electrons.phi.at(0), ed->electrons.E.at(0));
    else lepton.SetPtEtaPhiE(ed->muons.pT.at(0), ed->muons.eta.at(0), ed->muons.phi.at(0), ed->muons.E.at(0));
    
    
    
   //**************** Exist a jet with deltaPhi(lep,HadTopJetCandidate)>1*************************
    double dPhi_lepljet = PhysicsHelperFunctions::deltaPhi(ed->fjets.phi.at(HadTopJetCandidate),lepton.Phi());
    m_hm->GetHistogram( "reco/1fj1b/topH_lep/DeltaPhi" )->Fill(PhysicsHelperFunctions::deltaPhi(ed->fjets.phi.at(HadTopJetCandidate),lepton.Phi()), weight );
    if ( dPhi_lepljet < 1) return !passed;
    PassedCut( "LPLUSJETS", "reco_unweight");
    
    
    //**************** Exist b-jet in the event*************************
    
    vector<int> btagged_jet;
    for( int bj = 0 ; bj < jet_n ; ++bj ) {
      if(ed->jets.property["mv2c20"].at(bj) > -0.4434 ) btagged_jet.push_back(bj);
    }
    if(btagged_jet.size() == 0) return !passed;
    PassedCut( "LPLUSJETS", "reco_unweight");
    
    
   //**************** Exist a jet with deltaR(HadTopJetCandidate,jet)>1.5*************************
    vector<int> jet_farFromHadTopJetCandidate;
   
    for( int sj = 0 ; sj < jet_n ; ++sj ) {
      
      double dR = PhysicsHelperFunctions::deltaR(ed->fjets.eta.at(HadTopJetCandidate),ed->jets.eta.at(sj),ed->fjets.phi.at(HadTopJetCandidate),ed->jets.phi.at(sj));
      if (dR > 1.5) {
	jet_farFromHadTopJetCandidate.push_back(sj);
      } 
    }
    
    if(jet_farFromHadTopJetCandidate.size() == 0) return !passed;
    PassedCut( "LPLUSJETS", "reco_unweight");
    
    
    //**************** Exist a jet with deltaR(lepton,jet)<1.5*************************
    for ( auto &ltj : jet_farFromHadTopJetCandidate ){
      
      double dR = PhysicsHelperFunctions::deltaR(lepton.Eta(),ed->jets.eta.at(ltj),lepton.Phi(),ed->jets.phi.at(ltj));
      	m_hm->GetHistogram("reco/1fj1b/topH_smallJ/DeltaR")->Fill( PhysicsHelperFunctions::deltaR(ed->fjets.eta.at(HadTopJetCandidate),ed->jets.eta.at(ltj), ed->fjets.phi.at(HadTopJetCandidate),ed->jets.phi.at(ltj)), weight );
	m_hm->GetHistogram("reco/1fj1b/lep_smallJ/DeltaR")->Fill( dR , weight );
	if (dR < 1.5) {
	  LepTopJetCandidate.push_back(ltj);
	  
	}
	
    }
     
  
    if(LepTopJetCandidate.size() == 0) return !passed;
    PassedCut( "LPLUSJETS", "reco_unweight");
    
    m_hm->GetHistogram( "reco/1fj1b/topH/pt" )->Fill( ed->fjets.pT.at(HadTopJetCandidate) / GeV, weight );
  
   
    // deltaPhi between the HadTopJetCandidate and lepton ;
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

  
  //The tagger name is taken from the configuration xml
  string Tagger = "none";
  
  if( m_config->custom_params_string.count( "tagger" ) )
    {
       Tagger=m_config->custom_params_string["tagger"].c_str();
    }


    const int    el_n  = ed->truth_electrons.n; 
    const int    mu_n  = ed->truth_muons.n; 
    const int    jet_n  = ed->truth_jets.n;
    const int    fjet_n = ed->truth_fjets.n;   
    const double ETmiss = ed->MET_truth.et;
    const double mwt    = ed->MET_truth.mwt;
    // const bool   single_lept = ( m_config->channel == kElectron ) ?
    //                            (el_n == 1)&&(mu_n==0) :
    //                            (el_n == 0)&&(mu_n==1);
    
    
    // cout<<" el_n "<< el_n <<endl;   
    // cout<<" mu_n "<<  mu_n <<endl;   
    // cout<<" jet_n "<< jet_n <<endl;
    // cout<<" fjet_n "<< fjet_n <<endl;


    //Initialize the index of the Hadronic topjetCandidate
    int HadTopJetCandidate = -1;
     //Container of small-R jet that pass requirements on the dR with lepton and HadTopJetCandidate
    vector<int> LepTopJetCandidate;
    
    const double weight = ed->property["weight_particle_level"];
    
    const bool passed_boosted_ejets = ed->property["passed_boosted_ejets_1fj0b"]; ///Preselection done in AT for el-channel
    const bool passed_boosted_mujets = ed->property["passed_boosted_mujets_1fj0b"]; ///Preselection done in AT for mu-channel  
      
      
    //****************All event passing analysis top selection *************************
    const bool  single_lept = ( m_config->channel == kElectron )  ?  ( passed_boosted_ejets) : ( passed_boosted_mujets );     
    if( !single_lept )   return !passed;
    
    PassedCut( "LPLUSJETS", "particle_unweight");  
    
       //**************** Exist a tagged Large-R jet with pT>300000 and |eta|<2 *************************
    
    
    for( int lj = 0 ; lj < fjet_n ; ++lj ) {
      const double sd12  = ed->truth_fjets.property["sd12"].at(lj);
      const double tau32 = ed->truth_fjets.property["tau32"].at(lj);
      const double tau21 = ed->truth_fjets.property["tau21"].at(lj);
     
      
      int topTag = 0;
      if(Tagger != "none")
      topTag = ed->truth_fjets.property[Tagger.c_str()].at(lj);
      else 
      {
	cout<<"FATAL::Top Tagger not set in config file"<<endl;
	exit(1);
      }
      //cout<<"property topTag "<<topTag<<endl;
      if(topTag == 1 && (ed->truth_fjets.pT.at(lj) > 300 * GeV) && fabs(ed->truth_fjets.eta.at(lj)) < 2){
	//The first Large-R jet found has the highest pT, become the HadTopJetCandidate
	HadTopJetCandidate = lj;
	
	m_hm->GetHistogram( "particle/1fj1b/topJet/pt" )->Fill( ed->truth_fjets.pT.at(lj) / GeV, weight );

	break;
      }
    }
    
    if(HadTopJetCandidate < 0) return !passed;
    PassedCut( "LPLUSJETS", "particle_unweight");
    
   
    const bool control = ( m_config->channel == kElectron ) ? (el_n >= 1 && ed->truth_electrons.pT.at(0)>25000) : (mu_n >= 1 && ed->truth_muons.pT.at(0)>25000);
    
    
    if (!control) {
      cout<<"WARNING the lepton selection coud be broken!"<<endl;
       exit(1);
    }
    
    //Define the lepton to use during selection
    TLorentzVector lepton;
    if ( m_config->channel == kElectron ) lepton.SetPtEtaPhiE(ed->truth_electrons.pT.at(0), ed->truth_electrons.eta.at(0), ed->truth_electrons.phi.at(0), ed->truth_electrons.E.at(0));
    else lepton.SetPtEtaPhiE(ed->truth_muons.pT.at(0), ed->truth_muons.eta.at(0), ed->truth_muons.phi.at(0), ed->truth_muons.E.at(0));
    
    
    
   //**************** Exist a jet with deltaPhi(lep,HadTopJetCandidate)>1*************************
    double dPhi_lepljet = PhysicsHelperFunctions::deltaPhi(ed->truth_fjets.phi.at(HadTopJetCandidate),lepton.Phi());
    m_hm->GetHistogram( "particle/1fj1b/topH_lep/DeltaPhi" )->Fill(PhysicsHelperFunctions::deltaPhi(ed->truth_fjets.phi.at(HadTopJetCandidate),lepton.Phi()), weight );
    if ( dPhi_lepljet < 1) return !passed;
    PassedCut( "LPLUSJETS", "particle_unweight");
    
    
    //**************** Exist b-jet in the event*************************
    
    // vector<int> btagged_jet;    
    // for( int bj = 0 ; bj < jet_n ; ++bj ) {
    //   if(ed->truth_jets.property["mv2c20"].at(bj) > -0.4434 ) btagged_jet.push_back(bj);
    // }
    // if(btagged_jet.size() == 0) return !passed;
    PassedCut( "LPLUSJETS", "particle_unweight");
    
    
   //**************** Exist a jet with deltaR(HadTopJetCandidate,jet)>1.5*************************
    vector<int> jet_farFromHadTopJetCandidate;
   
    for( int sj = 0 ; sj < jet_n ; ++sj ) {
      
      double dR = PhysicsHelperFunctions::deltaR(ed->truth_fjets.eta.at(HadTopJetCandidate),ed->truth_jets.eta.at(sj),ed->truth_fjets.phi.at(HadTopJetCandidate),ed->truth_jets.phi.at(sj));
      if (dR > 1.5) {
   	jet_farFromHadTopJetCandidate.push_back(sj);
      } 
    }
    
    if(jet_farFromHadTopJetCandidate.size() == 0) return !passed;
    PassedCut( "LPLUSJETS", "particle_unweight");
    
    
    //**************** Exist a jet with deltaR(lepton,jet)<1.5*************************
    for ( auto &ltj : jet_farFromHadTopJetCandidate ){
      
      double dR = PhysicsHelperFunctions::deltaR(lepton.Eta(),ed->truth_jets.eta.at(ltj),lepton.Phi(),ed->truth_jets.phi.at(ltj));
      	m_hm->GetHistogram("particle/1fj1b/topH_smallJ/DeltaR")->Fill( PhysicsHelperFunctions::deltaR(ed->truth_fjets.eta.at(HadTopJetCandidate),ed->truth_jets.eta.at(ltj), ed->truth_fjets.phi.at(HadTopJetCandidate),ed->truth_jets.phi.at(ltj)), weight );
   	m_hm->GetHistogram("particle/1fj1b/lep_smallJ/DeltaR")->Fill( dR , weight );
   	if (dR < 1.5) {
   	  LepTopJetCandidate.push_back(ltj);
	  
   	}
	
    }
     
  
    if(LepTopJetCandidate.size() == 0) return !passed;
    PassedCut( "LPLUSJETS", "particle_unweight");
    
    m_hm->GetHistogram( "particle/1fj1b/topH/pt" )->Fill( ed->truth_fjets.pT.at(HadTopJetCandidate) / GeV, weight );
 



  return passed;
  

}
/////////////////////////////////////////

// Plugin
extern "C" {
  CutFlowPluginFactory_BoostedSL * MakeCutFlowPlugin() {
    return new CutFlowPluginFactory_BoostedSL( "BoostedSL" );
  };
}

