#include "CutFlowBoostedSLParticle.h"

CutFlowBoostedSLParticle::CutFlowBoostedSLParticle()
{
}

CutFlowBoostedSLParticle::~CutFlowBoostedSLParticle()
{
}
/////////////////////////////////////////

bool CutFlowBoostedSLParticle::Initialize() {
    bool success = true;

    AddChannel("LPLUSJETS");  
    AddCounterName("LPLUSJETS", "particle_unweight", 6 );
    SetCutName("LPLUSJETS", "particle_unweight", 0, "All Events after Analysis Top Cuts          ");
    SetCutName("LPLUSJETS", "particle_unweight", 1, "A tagged Large-R jet                        ");
    SetCutName("LPLUSJETS", "particle_unweight", 2, "Exist a jet with deltaPhi(lep,Large-R jet)>1");
    SetCutName("LPLUSJETS", "particle_unweight", 3, "Exist b-jet in the event                    ");
    SetCutName("LPLUSJETS", "particle_unweight", 4, "Exist a jet with deltaR(Large-R jet,jet)>1.5");
    SetCutName("LPLUSJETS", "particle_unweight", 5, "Exist a jet with deltaR(lepton,jet)<1.5     ");
    SetCutName("LPLUSJETS", "particle_unweight", 6, "Bjet matched with a top                     ");

    
    return success;
}


//bool CutFlowBoostedSLParticle::Apply( EventData * ed, int * lastCutPassed )
bool CutFlowBoostedSLParticle::Apply( EventData * ed)
{
  bool success = true;
  
  CutFlow::Start();
  
  unsigned long isMCSignal = m_config->custom_params_flag["isMCSignal"];
  
  //////MANAGE THE WEIGHTS//////////////////////////////////////////
  double weight_particle_level = 1.;
  
  weight_particle_level = ed->info.mcWeight;
  
  const double scaleFactor_PILEUP     = ed->property["scaleFactor_PILEUP"];
  // const double scaleFactor_ZVERTEX    = ed->property["scaleFactor_ZVERTEX"];
  ///const double scaleFactor_TRIGGER    = ed->property["scaleFactor_TRIGGER"];
  
  
  // in 8 TeV analysis we had only PILEUP and ZVERTEX
  //weight_particle_level *= scaleFactor_PILEUP; // * scaleFactor_ZVERTEX;
  
  //cout<<"Weights:  "<<weight_particle_level<<endl;
  //Set the weights as event properties so we can call in the selections
  ed->property["weight_particle_level"] = weight_particle_level;
  
  
  ///////Parton top distributions/////////////////////
  bool passedPartonSelection = FillHistogramsParton( ed, weight_particle_level );

  // Apply particle level selection 
  const bool passedParticleSelection =  PassedCutFlowParticle( ed );
  if (!passedParticleSelection)
    return success;
  
  
  if (passedParticleSelection){ 
    
    FillHistogramsParticle(ed, weight_particle_level);
    
    if(passedPartonSelection) FillHistogramsParticleToParton( ed, weight_particle_level );
    
    
  }
  
  
  
  
  return success;
}

/////////////////////////////////////////PARTICLE SELECTION //////////////////////////////
bool  CutFlowBoostedSLParticle::PassedCutFlowParticle(EventData * ed) {
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
    
    
//      cout<<" el_n "<< el_n <<endl;   
//      cout<<" mu_n "<<  mu_n <<endl;   
//      cout<<" jet_n "<< jet_n <<endl;
//      cout<<" fjet_n "<< fjet_n <<endl;


    //Initialize the index of the Hadronic topjetCandidate
    int HadTopJetCandidate = -1;
     //Container of small-R jet that pass requirements on the dR with lepton and HadTopJetCandidate
    vector<int> LepTopJetCandidate;
    
    const double weight = ed->property["weight_particle_level"];
    
    const bool passed_boosted_ejets = ed->property["passed_particle_boosted_ejets_1fj0b"]; ///Preselection done in AT for el-channel
    const bool passed_boosted_mujets = ed->property["passed_particle_boosted_mujets_1fj0b"]; ///Preselection done in AT for mu-channel  
      
      
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
      /////////////------- LARGE-R MASS >100  & tau32 < 0.75 as tagging requirement at Particle Level ---------//////////////
      if((ed->truth_fjets.pT.at(lj) > 300 * GeV) && fabs(ed->truth_fjets.eta.at(lj)) < 2 && (ed->truth_fjets.m.at(lj) > 100. * GeV) && (tau32 < 0.75)){
	//The first Large-R jet found has the highest pT, become the HadTopJetCandidate
	HadTopJetCandidate = lj;
	ed->property["ParticleHadTopJetCandidate"] = lj;


	break;
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
    m_hm->GetHistogram( "particle/1fj1b/topH/DeltaPhi_lep" )->Fill(PhysicsHelperFunctions::deltaPhi(ed->truth_fjets.phi.at(HadTopJetCandidate),lepton.Phi()), weight );
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


  return passed;
  

}

void CutFlowBoostedSLParticle::FillHistogramsParticle( EventData * ed, const double weight )
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
  m_hm->GetHistogram( "particle/1fj1b/topH/d12" )->Fill( ed->truth_fjets.property["sd12"].at(particleindex) / GeV, weight);
  //m_hm->GetHistogram( "reco/1fj1b/topH/d12" )->Fill( ed->fjets.property["sd23"].at(recoindex) / GeV, weight);
  m_hm->GetHistogram( "particle/1fj1b/topH/tau32" )->Fill( ed->truth_fjets.property["tau32"].at(particleindex) , weight);
  m_hm->GetHistogram( "particle/1fj1b/topH/tau21" )->Fill( ed->truth_fjets.property["tau21"].at(particleindex) , weight);
  double lep_pT = m_config->channel == kElectron ? ed->truth_electrons.pT.at(0) : ed->truth_muons.pT.at(0);
  m_hm->GetHistogram( "particle/1fj1b/lep/pt" )->Fill( lep_pT / GeV, weight);
  for( unsigned int sj = 0 ; sj < ed->jets.pT.size() ; ++sj ) {
    m_hm->GetHistogram( "particle/1fj1b/smallJ/pt" )->Fill( ed->jets.pT.at(sj), weight);
  }
  
  
  
}
void CutFlowBoostedSLParticle::FillHistogramsParticleToParton( EventData * ed, const double weight )
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
    
    TLorentzVector partonTopH = HelperFunctions::MakeFourMomentum(ed->mctruth, ihad);
    
    // particle level fjet index
    int particleindex = ed->property["ParticleHadTopJetCandidate"];
    TLorentzVector truth_fjets = HelperFunctions::MakeFourMomentum( ed->truth_fjets, particleindex );

    //  particle > parton MMatrix
    m_hm->FillMatrices( "particle/1fj1b/topH/Matrix_particle_parton_pt",  truth_fjets.Pt() / GeV, partonTopH.Pt() / GeV, weight);
    m_hm->FillMatrices( "particle/1fj1b/topH/Matrix_particle_parton_rapidity", truth_fjets.Rapidity(),  partonTopH.Rapidity(),  weight);
    m_hm->FillMatrices( "particle/1fj1b/topH/Matrix_particle_parton_absrap", fabs(truth_fjets.Rapidity()),  fabs(partonTopH.Rapidity()),  weight);
        
  }

  bool CutFlowBoostedSLParticle::FillHistogramsParton( EventData * ed, const double weight )
  {
    
    // parton level
    int ilep, ihad;
    
    bool isDileptonic = ed->property["isDileptonic"];
    if(isDileptonic) return false;
    
    const bool isHadronic = ed->mctruth.property["isHadronic"].at(0);
    if( isHadronic ) {
      ihad = 0;
      ilep = 1;
    }
    else {
      ihad = 1;
      ilep = 0;
    }
    
    TLorentzVector partonTopH = HelperFunctions::MakeFourMomentum(ed->mctruth, ihad);
    if(partonTopH.Pt() < 300000 ) return false;

    //parton TopH
    m_hm->GetHistogram( "parton/1fj1b/topH/pt" )->Fill(  partonTopH.Pt() / GeV, weight);
    m_hm->GetHistogram( "parton/1fj1b/topH/eta")->Fill(  partonTopH.Eta()     , weight);
    m_hm->GetHistogram( "parton/1fj1b/topH/phi")->Fill(  partonTopH.Phi()     , weight);
    m_hm->GetHistogram( "parton/1fj1b/topH/m"  )->Fill(  partonTopH.M()  / GeV, weight);
    m_hm->GetHistogram( "parton/1fj1b/topH/rapidity"  )->Fill( partonTopH.Rapidity()  / GeV, weight);
    m_hm->GetHistogram( "parton/1fj1b/topH/absrap"    )->Fill( fabs(partonTopH.Rapidity())  / GeV, weight);
    

    return true;
  }
/////////////////////////////////////////

// Plugin
extern "C" {
  CutFlowPluginFactory_BoostedSLParticle * MakeCutFlowPlugin() {
    return new CutFlowPluginFactory_BoostedSLParticle( "BoostedSLParticle" );
  };
}

