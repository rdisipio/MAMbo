#include "CutFlowBoostedSL.h"

CutFlowBoostedSL::CutFlowBoostedSL()
{
  
  #ifdef __MOMA__
  m_moma = MoMATool::GetHandle();
  cout << "INFO: ATLAS ROOTCORE detected. MoMA tool initialized." << endl;
  #endif
}

CutFlowBoostedSL::~CutFlowBoostedSL()
{
  #ifdef __MOMA__
  SAFE_DELETE( m_moma );
  #endif
  SAFE_DELETE( m_scalerFakes )
}
/////////////////////////////////////////

bool CutFlowBoostedSL::Initialize() {
    bool success = true;

    m_rand = new TRandom3( 0 ); 

    AddChannel("LPLUSJETS");  
    AddCounterName("LPLUSJETS", "reco_unweight", 6 );
    SetCutName("LPLUSJETS", "reco_unweight", 0, "All Events after Analysis Top Cuts          ");
    SetCutName("LPLUSJETS", "reco_unweight", 1, "A tagged Large-R jet                        ");
    SetCutName("LPLUSJETS", "reco_unweight", 2, "Exist a jet with deltaPhi(lep,Large-R jet)>1");
    SetCutName("LPLUSJETS", "reco_unweight", 3, "Exist b-jet in the event                    ");
    SetCutName("LPLUSJETS", "reco_unweight", 4, "Exist a jet with deltaR(Large-R jet,jet)>1.5");
    SetCutName("LPLUSJETS", "reco_unweight", 5, "Exist a jet with deltaR(lepton,jet)<2       ");
    SetCutName("LPLUSJETS", "reco_unweight", 6, "Bjet matched with a top                     ");
    
    AddCounterName("LPLUSJETS", "reco_weighted", 6 );
    SetCutName("LPLUSJETS", "reco_weighted", 0, "All Events after Analysis Top Cuts          ");
    SetCutName("LPLUSJETS", "reco_weighted", 1, "A tagged Large-R jet                        ");
    SetCutName("LPLUSJETS", "reco_weighted", 2, "Exist a jet with deltaPhi(lep,Large-R jet)>1");
    SetCutName("LPLUSJETS", "reco_weighted", 3, "Exist b-jet in the event                    ");
    SetCutName("LPLUSJETS", "reco_weighted", 4, "Exist a jet with deltaR(Large-R jet,jet)>1.5");
    SetCutName("LPLUSJETS", "reco_weighted", 5, "Exist a jet with deltaR(lepton,jet)<2       ");
    SetCutName("LPLUSJETS", "reco_weighted", 6, "Bjet matched with a top                     ");

    AddCounterName("LPLUSJETS", "particle_unweight", 6 );
    SetCutName("LPLUSJETS", "particle_unweight", 0, "All Events after Analysis Top Cuts          ");
    SetCutName("LPLUSJETS", "particle_unweight", 1, "A tagged Large-R jet                        ");
    SetCutName("LPLUSJETS", "particle_unweight", 2, "Exist a jet with deltaPhi(lep,Large-R jet)>1");
    SetCutName("LPLUSJETS", "particle_unweight", 3, "Exist b-jet in the event                    ");
    SetCutName("LPLUSJETS", "particle_unweight", 4, "Exist a jet with deltaR(Large-R jet,jet)>1.5");
    SetCutName("LPLUSJETS", "particle_unweight", 5, "Exist a jet with deltaR(lepton,jet)<2       ");
    SetCutName("LPLUSJETS", "particle_unweight", 6, "Bjet matched with a top                     ");
    
    m_bTagSF_name = "scaleFactor_BTAG_77"; 
    m_leptonSF_name = "scaleFactor_LEPTON" ;
    m_pileupSF_name = "scaleFactor_PILEUP";	
    
    unsigned long isQCD      = m_config->custom_params_flag["isQCD"];
    if(isQCD)
    {
      int nParameters = 2;
      string method = "MM";
      if( m_config->custom_params_string.count("FakesEvaluationMethod")) method = m_config->custom_params_string["FakesEvaluationMethod"];
      cout<<"Config name "<<method;
      //if( m_config->channel == 0 ) nParameters = 4;
      m_scalerFakes = ScalerFakes::GetHandle( m_config->channel, nParameters, method);
    }
    
    
    
    if( m_config->custom_params_string.count( "scale_syst" ) ) {

        const string syst = m_config->custom_params_string["scale_syst"];

        cout << "INFO: Scale factor systematic: " << syst << endl;
        if( syst.find( "lepton" ) != string::npos )
        {
	    m_leptonSF_name = syst;   
	}
	  
	else if( syst.find( "bTag" ) != string::npos )
	{
	    m_bTagSF_name = syst;  
	}
	  
	else if( syst.find( "pileup" ) != string::npos )
	{
	    m_pileupSF_name = syst;
	}
	else if( syst != "NOMINAL" )
	{
	  	throw runtime_error( "Unknown scale syst " + syst );
	}  
    }	 
    
    return success;
}


//bool CutFlowBoostedSL::Apply( EventData * ed, int * lastCutPassed )
bool CutFlowBoostedSL::Apply( EventData * ed)
{
  bool success = true;
  
  CutFlow::Start();
  
  unsigned long isMCSignal = m_config->custom_params_flag["isMCSignal"];
  unsigned long isRealData = m_config->custom_params_flag["isRealData"];
  unsigned long isQCD      = m_config->custom_params_flag["isQCD"];
  
  unsigned long isStressTest = 0;
  string stressTestType = "none";
  
  if( m_config->custom_params_string.count( "stressTest" ) ) //mr
  {
    stressTestType = m_config->custom_params_string["stressTest"];
    if( stressTestType != "none" && stressTestType != "tt_m" && stressTestType != "pt_t" )
    {
      cout << "Warning: stress test type " << stressTestType << " is unknown, setting it to \"none\"\n";
      stressTestType = "none";
    }
    else if(  stressTestType != "none" ) isStressTest = 1;
  }
  
  //////MANAGE THE WEIGHTS//////////////////////////////////////////
  double weight_reco_level     = 1.;
  double weight_particle_level = 1.;
  
  weight_reco_level     = ed->info.mcWeight;
  weight_particle_level = ed->info.mcWeight;
  
  const double scaleFactor_PILEUP     = ed->property[ m_pileupSF_name ];
    // const double scaleFactor_ZVERTEX    = ed->property["scaleFactor_ZVERTEX"];
  ///const double scaleFactor_TRIGGER    = ed->property["scaleFactor_TRIGGER"];
  const double scaleFactor_LEPTON     = ed->property[ m_leptonSF_name ]; 
  //  const double scaleFactor_JVFSF      = ed->property["scaleFactor_JVFSF"]; 
  const double scaleFactor_BTAG       = ed->property[ m_bTagSF_name ]; 
   
   
  // THis is what we have now (TO BE FIXED with nedeed weights)
  weight_reco_level *= scaleFactor_PILEUP * scaleFactor_LEPTON * scaleFactor_BTAG;
  
  // in 8 TeV analysis we had only PILEUP and ZVERTEX for now we use 1
  ///weight_particle_level *= scaleFactor_PILEUP * scaleFactor_ZVERTEX;
  
  // Set to  1 for data
  if(isRealData || isQCD) weight_reco_level = 1;   
  
  if( !isRealData && !isQCD ) {
    
    if( isStressTest )//mr
    {
      TLorentzVector t1 = Particle(ed->mctruth, 0).MakeLorentz();
      TLorentzVector t2 = Particle(ed->mctruth, 1).MakeLorentz();
      TLorentzVector tt = t1 + t2;
      if( stressTestType == "tt_m" )
      {
	if(tt.M() > 400000) cout<<"weight_reco_level "<<weight_reco_level;
	weight_reco_level *= (0.9 + 0.00036 *  tt.M()/GeV);
	weight_particle_level *= (0.9 + 0.00036 *  tt.M()/GeV);
        if(tt.M() > 400000) cout<<" weight_reco_level "<<weight_reco_level<<endl;
	
      }
      if( stressTestType == "pt_t" )
      {
	double pt_average = (t1.Pt() + t2.Pt()) / 2.;  
	weight_reco_level *= (1.0 +  1/600. * (pt_average/GeV - 200));
	weight_particle_level *= (1.0 +  1/600. * (pt_average/GeV - 200));
	
	
      }
       
    }
  }
  
  ed->property["weight_reco_level"]     = weight_reco_level;
  ed->property["weight_particle_level"] = weight_particle_level;
  
//   const bool passedRecoSelectionWjet  = PassedCutFlowRecoControlWjets( ed ); 
//   if(passedRecoSelectionWjet){
//     FillHistogramsReco(ed, weight_reco_level, "WJETcontrol");
//   }
  // Apply selections 
  const bool passedRecoSelection     = PassedCutFlowReco( ed );
  const bool passedParticleSelection =  !isMCSignal ? false : PassedCutFlowParticle( ed );
  
 
  
  //Set the weights after QCD 
  weight_reco_level = ed->property["weight_reco_level"] ;
  
  ////////CHECKING WEIGHTS///////////////////////////////////////////////
  //  cout<< " scaleFactor_BTAG      "  <<  scaleFactor_BTAG    << endl;
  //  cout<< " scaleFactor_LEPTON    "  <<  scaleFactor_LEPTON    << endl;
  //  cout<< " scaleFactor_PILEUP    "  <<  scaleFactor_PILEUP   << endl;
  // cout<< " weight_reco_level      "  <<  weight_reco_level  << endl;
  // cout<< " weight_particle_level  "  <<  weight_particle_level  << endl;

  if (!passedParticleSelection && !passedRecoSelection)
    return success;

  /////FOR CLOSURE///////////////////
  bool fillHistos = true;
  bool splitSample =  m_config->custom_params_string.count("splitSample");
 
  if (isMCSignal and splitSample) {
    bool splitSampleInvert =  false;
    if (m_config->custom_params_string.count("splitSampleInvert"))
	splitSampleInvert = not (m_config->custom_params_string["splitSampleInvert"] == "0" or m_config->custom_params_string["splitSampleInvert"] == "false");
    // cout << "splitSample and Invert? " << splitSample << " " << splitSampleInvert << endl;
    fillHistos =   (m_rand -> Integer(2)); // this or not;)
    if (splitSampleInvert)
      fillHistos = not fillHistos;
    
    if (not fillHistos)
      return success;
  }
  
  if( passedRecoSelection ) { ///RECO ONLY  ----  FILL FOR ALL MC AND DATA
    if (fillHistos)
      FillHistogramsReco(ed, weight_reco_level, "1fj1b");
  }
  
  if(!isRealData){
    if (passedRecoSelection && passedParticleSelection){ ////RECO && PARTICLE ---- FILL ONLY FOR MC SIGNAL
      if (fillHistos){
	FillHistogramsParticle(ed, weight_particle_level);
	FillMatrixRecoToParticle(ed, weight_reco_level);	
      }
    }
    if( passedRecoSelection && isMCSignal ) { ///RECO ONLY FOR PARTON STUFF ---- FILL ONLY FOR MC SIGNAL
      if (fillHistos)
	FillMatrixRecoToParton(ed, weight_reco_level);
      
    }
  }
  
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
    PassedCut( "LPLUSJETS", "reco_weighted",weight); 
    
    //****************Evaluation of QCD weight
    unsigned long isQCD      = m_config->custom_params_flag["isQCD"];
    if(isQCD){
      double qcd_weight = m_scalerFakes->GetFakesWeight( ed );
      cout<<"Qcd weight "<<qcd_weight<<endl;
      if(qcd_weight != 0)
	weight     *= qcd_weight;
      else
	cout<<"WARNING:: QCD weight 0"<<endl;
      ed->property["weight_reco_level"] *= qcd_weight;
      m_hm->GetHistogram( "reco/QCDcontrol/topH/QCDweight" )->Fill(qcd_weight, 1. );
      
    }
    FillHistogramsReco(ed, weight, "QCDcontrol");
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
    	ed->property["RecoHadTopJetCandidate"] = lj;


	break;
      }
    }
    
    if(HadTopJetCandidate < 0) return !passed;
    PassedCut( "LPLUSJETS", "reco_unweight");
    PassedCut( "LPLUSJETS", "reco_weighted",weight); 
    
    
    
    const bool control = ( m_config->channel == kElectron ) ? (el_n >= 1 && ed->electrons.pT.at(0)>25000) : (mu_n >= 1 && ed->muons.pT.at(0)>25000);
    
    
    if (!control) {
       cout<<"WARNING the lepton selection coud be broken!"<<endl;
       return !passed;
    }
 
   //Define the lepton to use during selection
    TLorentzVector lepton;
    if ( m_config->channel == kElectron ) lepton.SetPtEtaPhiE(ed->electrons.pT.at(0), ed->electrons.eta.at(0), ed->electrons.phi.at(0), ed->electrons.E.at(0));
    else lepton.SetPtEtaPhiE(ed->muons.pT.at(0), ed->muons.eta.at(0), ed->muons.phi.at(0), ed->muons.E.at(0));
    
    
    
   //**************** Exist a jet with deltaPhi(lep,HadTopJetCandidate)>1*************************
    double dPhi_lepljet = PhysicsHelperFunctions::deltaPhi(ed->fjets.phi.at(HadTopJetCandidate),lepton.Phi());
    //m_hm->GetHistogram( "reco/1fj1b/topH/DeltaPhi_lep" )->Fill(PhysicsHelperFunctions::deltaPhi(ed->fjets.phi.at(HadTopJetCandidate),lepton.Phi()), weight );
    if ( dPhi_lepljet < 1) return !passed;
    PassedCut( "LPLUSJETS", "reco_unweight");
    PassedCut( "LPLUSJETS", "reco_weighted",weight); 
    
    //**************** Exist b-jet in the event*************************
    
    vector<int> btagged_jet;
    for( int bj = 0 ; bj < jet_n ; ++bj ) {
      if(ed->jets.property["mv2c20"].at(bj) > -0.4434 ) btagged_jet.push_back(bj);
    }
    if(btagged_jet.size() == 0) return !passed;
    PassedCut( "LPLUSJETS", "reco_unweight");
    PassedCut( "LPLUSJETS", "reco_weighted",weight); 
    
    
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
    PassedCut( "LPLUSJETS", "reco_weighted",weight); 
    
    
    //**************** Exist a jet with deltaR(lepton,jet)<2.0*************************
    for ( auto &ltj : jet_farFromHadTopJetCandidate ){
      
      double dR = PhysicsHelperFunctions::deltaR(lepton.Eta(),ed->jets.eta.at(ltj),lepton.Phi(),ed->jets.phi.at(ltj));
      	m_hm->GetHistogram("reco/1fj1b/topH/DeltaR_smallJ")->Fill( PhysicsHelperFunctions::deltaR(ed->fjets.eta.at(HadTopJetCandidate),ed->jets.eta.at(ltj), ed->fjets.phi.at(HadTopJetCandidate),ed->jets.phi.at(ltj)), weight );//
      	m_hm->GetHistogram("reco/1fj1b/lep/DeltaR_smallJ")->Fill( dR , weight );
	if (dR < 2.0) {
	  LepTopJetCandidate.push_back(ltj);
	 
	}
	
    }
     
  
    if(LepTopJetCandidate.size() == 0) return !passed;
    PassedCut( "LPLUSJETS", "reco_unweight");
    PassedCut( "LPLUSJETS", "reco_weighted",weight); 
    
    
    //*************** Position of b-jet *********************************
    bool btag_hadronicside=false;
    bool btag_leptonicside=false;
    
    //    cout<<" bjet_n reco "<<btagged_jet.size()<<endl;
   for ( auto &bj : btagged_jet )
    {
      double dR = PhysicsHelperFunctions::deltaR(ed->fjets.eta.at(HadTopJetCandidate),ed->jets.eta.at(bj),ed->fjets.phi.at(HadTopJetCandidate),ed->jets.phi.at(bj));
      if(dR < 1.0) {
	btag_hadronicside = true;
	break;
	
      }
    }
    
    for ( auto &bj : btagged_jet )
    {
      for ( auto &ltj : LepTopJetCandidate ){
	if( bj  == ltj )
	{
	  btag_leptonicside=true;
	  break;
	}
	
      }
      if(btag_leptonicside) break;
    }
    
    if (!btag_hadronicside && !btag_leptonicside) return !passed;
    PassedCut( "LPLUSJETS", "reco_unweight");
    PassedCut( "LPLUSJETS", "reco_weighted", weight); 
   
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
    const int    bjet_n = ed->truth_bjets.n;
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
    
    
//     for( int lj = 0 ; lj < fjet_n ; ++lj ) {
//       const double sd12  = ed->truth_fjets.property["sd12"].at(lj);
//       const double tau32 = ed->truth_fjets.property["tau32"].at(lj);
//       const double tau21 = ed->truth_fjets.property["tau21"].at(lj);
//      
//       
//       int topTag = 0;
//       if(Tagger != "none")
//       topTag = ed->truth_fjets.property[Tagger.c_str()].at(lj);
//       else 
//       {
// 	cout<<"FATAL::Top Tagger not set in config file"<<endl;
// 	exit(1);
//       }
//       //cout<<"property topTag "<<topTag<<endl;
//       if(topTag == 1 && (ed->truth_fjets.pT.at(lj) > 300 * GeV) && fabs(ed->truth_fjets.eta.at(lj)) < 2){
// 	//The first Large-R jet found has the highest pT, become the HadTopJetCandidate
// 	HadTopJetCandidate = lj;
// 	ed->property["ParticleHadTopJetCandidate"] = lj;
// 
// 
// 	break;
//       }
//     }
    vector<int> FatJets;
    for( int lj = 0 ; lj < fjet_n ; ++lj ) {
      const double sd12  = ed->truth_fjets.property["sd12"].at(lj);
      const double tau32 = ed->truth_fjets.property["tau32"].at(lj);
      const double tau21 = ed->truth_fjets.property["tau21"].at(lj);
      
      //cout<<"property topTag "<<topTag<<endl; 

      /////////////------- LARGE-R MASS >100  & tau32 < 0.75 as tagging requirement at Particle Level ---------//////////////
      if((ed->truth_fjets.pT.at(lj) > 300 * GeV) && fabs(ed->truth_fjets.eta.at(lj)) < 2 && (ed->truth_fjets.m.at(lj) > 100. * GeV) && tau32 < 0.75 ){
	//The first Large-R jet found has the highest pT, become the HadTopJetCandidate
	if( HadTopJetCandidate == -1 ) {
	  HadTopJetCandidate = lj;
	  ed->property["ParticleHadTopJetCandidate"] = lj;
	}
	FatJets.push_back(lj);
	
	//break;
      }
    }
    
    if(HadTopJetCandidate < 0) return !passed;
    PassedCut( "LPLUSJETS", "particle_unweight");
    
   
    const bool control = ( m_config->channel == kElectron ) ? (el_n >= 1 && ed->truth_electrons.pT.at(0)>25000) : (mu_n >= 1 && ed->truth_muons.pT.at(0)>25000);
    
    
    if (!control) {
      cout<<"WARNING the lepton selection coud be broken!"<<endl;
      return !passed;
    }
    
    //Define the lepton to use during selection
    TLorentzVector lepton;
    if ( m_config->channel == kElectron ) lepton.SetPtEtaPhiE(ed->truth_electrons.pT.at(0), ed->truth_electrons.eta.at(0), ed->truth_electrons.phi.at(0), ed->truth_electrons.E.at(0));
    else lepton.SetPtEtaPhiE(ed->truth_muons.pT.at(0), ed->truth_muons.eta.at(0), ed->truth_muons.phi.at(0), ed->truth_muons.E.at(0));
    
    
    
   //**************** Exist a jet with deltaPhi(lep,HadTopJetCandidate)>1*************************
    double dPhi_lepljet = PhysicsHelperFunctions::deltaPhi(ed->truth_fjets.phi.at(HadTopJetCandidate),lepton.Phi());
    //m_hm->GetHistogram( "particle/1fj1b/topH/DeltaPhi_lep" )->Fill(PhysicsHelperFunctions::deltaPhi(ed->truth_fjets.phi.at(HadTopJetCandidate),lepton.Phi()), weight );
    if ( dPhi_lepljet < 1) return !passed;
    PassedCut( "LPLUSJETS", "particle_unweight");
    
    
    //**************** Exist b-jet in the event*************************
    if (bjet_n < 1)        return !passed;
    PassedCut( "LPLUSJETS", "particle_unweight" );
    
    
    
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
    
    
    //**************** Exist a jet with deltaR(lepton,jet)<2.0*************************
    for ( auto &ltj : jet_farFromHadTopJetCandidate ){
      
      double dR = PhysicsHelperFunctions::deltaR(lepton.Eta(),ed->truth_jets.eta.at(ltj),lepton.Phi(),ed->truth_jets.phi.at(ltj));
      m_hm->GetHistogram("particle/1fj1b/topH/DeltaR_smallJ")->Fill( PhysicsHelperFunctions::deltaR(ed->truth_fjets.eta.at(HadTopJetCandidate),ed->truth_jets.eta.at(ltj), ed->truth_fjets.phi.at(HadTopJetCandidate),ed->truth_jets.phi.at(ltj)), weight );
      m_hm->GetHistogram("particle/1fj1b/lep/DeltaR_smallJ")->Fill( dR , weight );
   	if (dR < 2.0) {
   	  LepTopJetCandidate.push_back(ltj);
	
   	}
	
    }
     
  
    if(LepTopJetCandidate.size() == 0) return !passed;
    PassedCut( "LPLUSJETS", "particle_unweight");
    
    //*************** Position of b-jet *********************************
    bool btag_hadronicside=false;
    bool btag_leptonicside=false;
    
    //    cout<<" bjet_n "<<bjet_n<<endl;
    for(int bj = 0; bj<bjet_n; bj++)
    {
      double dR = PhysicsHelperFunctions::deltaR(ed->truth_fjets.eta.at(HadTopJetCandidate),ed->truth_bjets.eta.at(bj),ed->truth_fjets.phi.at(HadTopJetCandidate),ed->truth_bjets.phi.at(bj));
      if(dR <= 1.0) {
	btag_hadronicside = true;
	break;
	
      }
    }
    
    for(int bj = 0; bj<bjet_n; bj++)
    {
      for ( auto &ltj : LepTopJetCandidate ){
	if(ed->truth_bjets.index.at(bj) == ed->truth_jets.index.at(ltj))
	{
	  btag_leptonicside=true;
	  break;
	}
	
      }
      if(btag_leptonicside) break;
    }
    
    if (!btag_hadronicside && !btag_leptonicside) return !passed;
    PassedCut( "LPLUSJETS", "particle_unweight");
    
    //    m_hm->GetHistogram("particle/1fj1b/topH/Multiplicity")->Fill( FatJets.size() , weight );

  
  return passed;
  

}

bool  CutFlowBoostedSL::PassedCutFlowRecoControlWjets(EventData * ed) {
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
    
    if( mwt+ETmiss < 80000 ) return !passed;
    if( bjet_n > 0 )   return !passed;
}

void CutFlowBoostedSL::FillHistogramsReco( EventData * ed, const double weight, string selection )
{
  
  int recoindex=-1; 
  
  //Define what is the hadronic top without a tagger
  if (selection != "1fj1b"){
    for( unsigned int fj = 0 ; fj < ed->fjets.pT.size() ; ++fj ) {
      if( ed->fjets.pT.at(fj)<300000 || fabs(ed->fjets.eta.at(fj)) > 2) continue;
      recoindex = fj;
      break;
    } 
  }
  else
    recoindex= ed->property["RecoHadTopJetCandidate"];
  
 
  if(recoindex != -1){
    TLorentzVector fjets = HelperFunctions::MakeFourMomentum( ed->fjets, recoindex );
    m_hm->GetHistogram( "reco/"+selection+"/topH/pt" )->Fill( fjets.Pt() / GeV, weight);
    m_hm->GetHistogram( "reco/"+selection+"/topH/eta" )->Fill( fjets.Eta(), weight);
    m_hm->GetHistogram( "reco/"+selection+"/topH/m" )->Fill( fjets.M() / GeV, weight);
    m_hm->GetHistogram( "reco/"+selection+"/topH/phi" )->Fill( fjets.Phi(), weight);  
    m_hm->GetHistogram( "reco/"+selection+"/topH/rapidity" )->Fill( fjets.Rapidity(), weight);
    m_hm->GetHistogram( "reco/"+selection+"/topH/absrap" )->Fill( fabs(fjets.Rapidity()), weight);
    m_hm->GetHistogram( "reco/"+selection+"/topH/absrap_1" )->Fill( fabs(fjets.Rapidity()), weight);
    m_hm->GetHistogram( "reco/"+selection+"/topH/absrap_2" )->Fill( fabs(fjets.Rapidity()), weight);
    m_hm->GetHistogram( "reco/"+selection+"/topH/d12" )->Fill( ed->fjets.property["sd12"].at(recoindex) / GeV, weight);
    m_hm->GetHistogram( "reco/"+selection+"/topH/d23" )->Fill( ed->fjets.property["sd23"].at(recoindex) / GeV, weight);
    m_hm->GetHistogram( "reco/"+selection+"/topH/tau32" )->Fill( ed->fjets.property["tau32"].at(recoindex), weight);
    m_hm->GetHistogram( "reco/"+selection+"/topH/tau21" )->Fill( ed->fjets.property["tau21"].at(recoindex), weight);
  }
  m_hm->GetHistogram( "reco/"+selection+"/met/phi" )->Fill(ed->MET.phi, weight);
  m_hm->GetHistogram( "reco/"+selection+"/met/pt" )->Fill(ed->MET.et /GeV, weight);
  double lep_pT = m_config->channel == kElectron ? ed->electrons.pT.at(0) : ed->muons.pT.at(0);
  double lep_phi = m_config->channel == kElectron ? ed->electrons.phi.at(0) : ed->muons.phi.at(0);
  double lep_eta= m_config->channel == kElectron ? ed->electrons.eta.at(0) : ed->muons.eta.at(0);
 
  m_hm->GetHistogram( "reco/"+selection+"/lep/pt" )->Fill( lep_pT / GeV, weight);
  m_hm->GetHistogram( "reco/"+selection+"/lep/phi" )->Fill( lep_phi, weight);
  m_hm->GetHistogram( "reco/"+selection+"/lep/eta" )->Fill( lep_eta, weight);
  if(recoindex != -1) m_hm->GetHistogram( "reco/"+selection+"/topH/DeltaPhi_lep" )->Fill( deltaPhi( ed->fjets.phi.at(recoindex),lep_phi) , weight);
  m_hm->GetHistogram( "reco/"+selection+"/largejet/Number" )->Fill( ed->fjets.pT.size(), weight);
  int toptaggedjet = 0;
  for( unsigned int fj = 0 ; fj < ed->fjets.pT.size() ; ++fj ) {
    if( ed->fjets.pT.at(fj)<300000 || fabs(ed->fjets.eta.at(fj)) > 2) continue;
    m_hm->GetHistogram( "reco/"+selection+"/largejet/DeltaPhi_lep" )->Fill( deltaPhi( ed->fjets.phi.at(fj),lep_phi) , weight);
    m_hm->GetHistogram( "reco/"+selection+"/largejet/pt" )->Fill( ed->fjets.pT.at(fj) / GeV, weight);
    m_hm->GetHistogram( "reco/"+selection+"/largejet/eta" )->Fill( ed->fjets.eta.at(fj), weight);
    m_hm->GetHistogram( "reco/"+selection+"/largejet/phi" )->Fill( ed->fjets.phi.at(fj), weight);
    m_hm->GetHistogram( "reco/"+selection+"/largejet/m" )->Fill( ed->fjets.m.at(fj) / GeV, weight);
    if( ed->fjets.property[m_config->custom_params_string["tagger"].c_str()].at(fj) == 1) 
      toptaggedjet++;
  }
  m_hm->GetHistogram( "reco/"+selection+"/topH/Number" )->Fill(toptaggedjet , weight);
  m_hm->GetHistogram( "reco/"+selection+"/smallJ/Number" )->Fill(ed->jets.pT.size() , weight);
  for( unsigned int sj = 0 ; sj < ed->jets.pT.size() ; ++sj ) {
    m_hm->GetHistogram( "reco/"+selection+"/smallJ/pt" )->Fill( ed->jets.pT.at(sj) /GeV, weight);
    m_hm->GetHistogram( "reco/"+selection+"/smallJ/phi" )->Fill( ed->jets.phi.at(sj), weight);
    m_hm->GetHistogram( "reco/"+selection+"/smallJ/eta" )->Fill( ed->jets.eta.at(sj), weight);
 }

   m_hm->GetHistogram( "reco/"+selection+"/bjet/Number" )->Fill(ed->bjets.pT.size() , weight);
}

void CutFlowBoostedSL::FillHistogramsParticle( EventData * ed, const double weight )
{

      int particleindex = ed->property["ParticleHadTopJetCandidate"];
      TLorentzVector truth_fjets = HelperFunctions::MakeFourMomentum( ed->truth_fjets, particleindex );

      ///Top particle
      m_hm->GetHistogram( "particle/1fj1b/topH/pt" )->Fill( truth_fjets.Pt() / GeV, weight);
      m_hm->GetHistogram( "particle/1fj1b/topH/eta" )->Fill( truth_fjets.Eta(), weight);
      m_hm->GetHistogram( "particle/1fj1b/topH/m" )->Fill(   truth_fjets.M() / GeV, weight);
      m_hm->GetHistogram( "particle/1fj1b/topH/phi" )->Fill( truth_fjets.Phi(), weight);
      m_hm->GetHistogram( "particle/1fj1b/topH/rapidity" )->Fill(truth_fjets.Rapidity(), weight);
      m_hm->GetHistogram( "particle/1fj1b/topH/absrap" )->Fill( fabs(truth_fjets.Rapidity()), weight);
       m_hm->GetHistogram( "particle/1fj1b/topH/absrap_1" )->Fill( fabs(truth_fjets.Rapidity()), weight);
        m_hm->GetHistogram( "particle/1fj1b/topH/absrap_2" )->Fill( fabs(truth_fjets.Rapidity()), weight);
      m_hm->GetHistogram( "particle/1fj1b/topH/d12" )->Fill( ed->truth_fjets.property["sd12"].at(particleindex) / GeV, weight);
      //m_hm->GetHistogram( "reco/1fj1b/topH/d12" )->Fill( ed->fjets.property["sd23"].at(recoindex) / GeV, weight);
      m_hm->GetHistogram( "particle/1fj1b/topH/tau32" )->Fill( ed->truth_fjets.property["tau32"].at(particleindex) , weight);
      m_hm->GetHistogram( "particle/1fj1b/topH/tau21" )->Fill( ed->truth_fjets.property["tau21"].at(particleindex) , weight);
      double lep_pT = m_config->channel == kElectron ? ed->truth_electrons.pT.at(0) : ed->truth_muons.pT.at(0);
      m_hm->GetHistogram( "particle/1fj1b/lep/pt" )->Fill( lep_pT / GeV, weight);
      for( unsigned int sj = 0 ; sj < ed->truth_jets.pT.size() ; ++sj ) {
	m_hm->GetHistogram( "particle/1fj1b/smallJ/pt" )->Fill( ed->truth_jets.pT.at(sj), weight);
 }

}

void CutFlowBoostedSL::FillMatrixRecoToParticle( EventData * ed, const double weight )
{
  int recoindex = ed->property["RecoHadTopJetCandidate"];
  TLorentzVector fjets = HelperFunctions::MakeFourMomentum( ed->fjets, recoindex );

  int particleindex = ed->property["ParticleHadTopJetCandidate"];
  TLorentzVector truth_fjets = HelperFunctions::MakeFourMomentum( ed->truth_fjets, particleindex );

  m_hm->FillMatrices("reco/1fj1b/topH/Matrix_reco_particle_pt", fjets.Pt() / GeV,  truth_fjets.Pt()/ GeV,  weight);
  m_hm->FillMatrices("reco/1fj1b/topH/Matrix_reco_particle_rapidity", fjets.Rapidity(),  truth_fjets.Rapidity(),  weight);
  m_hm->FillMatrices("reco/1fj1b/topH/Matrix_reco_particle_absrap", fabs(fjets.Rapidity()),  fabs(truth_fjets.Rapidity()),  weight);
  m_hm->FillMatrices("reco/1fj1b/topH/Matrix_reco_particle_tau32", ed->fjets.property["tau32"].at(recoindex),  ed->truth_fjets.property["tau32"].at(particleindex),  weight);

}

void CutFlowBoostedSL::FillMatrixRecoToParton( EventData * ed, const double weight )
{
  
  // parton level
  int ilep, ihad;
  
  const bool isHadronic = ed->mctruth.property["isHadronic"].at(0);
  if( isHadronic ) {
    ihad = 0;
    ilep = 1;
  }
  else {
    ihad = 1;
    ilep = 0;
  }
  
  
  int recoindex = ed->property["RecoHadTopJetCandidate"];
  TLorentzVector fjets = HelperFunctions::MakeFourMomentum( ed->fjets, recoindex );
  
  TLorentzVector partonTopH = HelperFunctions::MakeFourMomentum(ed->mctruth, ihad);
  
  //  reco > parton MMatrix
  m_hm->FillMatrices( "reco/1fj1b/topH/Matrix_reco_parton_pt", fjets.Pt() / GeV, partonTopH.Pt() / GeV, weight);
  m_hm->FillMatrices( "reco/1fj1b/topH/Matrix_reco_parton_rapidity", fjets.Rapidity(),  partonTopH.Rapidity(),  weight);
  m_hm->FillMatrices( "reco/1fj1b/topH/Matrix_reco_parton_absrap", fabs(fjets.Rapidity()),  fabs(partonTopH.Rapidity()),  weight);
  m_hm->FillMatrices( "reco/1fj1b/topH/Matrix_reco_parton_absrap", fabs(fjets.Rapidity()),  fabs(partonTopH.Rapidity()),  weight);
}



/////////////////////////////////////////

// Plugin
extern "C" {
  CutFlowPluginFactory_BoostedSL * MakeCutFlowPlugin() {
    return new CutFlowPluginFactory_BoostedSL( "BoostedSL" );
  };
}

