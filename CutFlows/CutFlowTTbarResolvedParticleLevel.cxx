#include "CutFlowTTbarResolvedParticleLevel.h"

CutFlowTTbarResolvedParticleLevel::CutFlowTTbarResolvedParticleLevel()
{
   m_pseudotop_particle = new PseudoTopReconstruction();

   m_pseudotop_matching_particle2parton = new PseudoTopMatching( PseudoTopMatching::kParticleToParton );

   alias = {
	"beforeCuts", "trig", "pvtx", "lep", "pTlep", "met", "mtw", "3j0b", "4j0b", "4j1b", "afterCuts"
   };
}

CutFlowTTbarResolvedParticleLevel::~CutFlowTTbarResolvedParticleLevel()
{
   SAFE_DELETE( m_pseudotop_particle )
   SAFE_DELETE( m_pseudotop_matching_particle2parton )
}


/////////////////////////////////////////


bool CutFlowTTbarResolvedParticleLevel::Initialize()
{
    bool success = true;

    AddChannel("LPLUSJETS");

    AddCounterName("LPLUSJETS", "particle_unweight", 10 );
    SetCutName("LPLUSJETS", "particle_unweight", 0, "All Events");
    SetCutName("LPLUSJETS", "particle_unweight", 1, "Trigger");
    SetCutName("LPLUSJETS", "particle_unweight", 2, "Prim. Vtx");
    SetCutName("LPLUSJETS", "particle_unweight", 3, "SingleLepton");
    SetCutName("LPLUSJETS", "particle_unweight", 4, "Lep pT > 25 GeV" );
    if( m_config->channel == kElectron ) {
       SetCutName("LPLUSJETS", "particle_unweight", 5, "ETmiss > 30 GeV");
       SetCutName("LPLUSJETS", "particle_unweight", 6, "mTW > 30 GeV");
    }
    else {
       SetCutName("LPLUSJETS", "particle_unweight", 5, "ETmiss > 20 GeV");
       SetCutName("LPLUSJETS", "particle_unweight", 6, "mTW + ETmiss > 60 GeV");
    }
    SetCutName("LPLUSJETS", "particle_unweight", 7, "NJets >= 3");
    SetCutName("LPLUSJETS", "particle_unweight", 8, "NJets >= 4");
    SetCutName("LPLUSJETS", "particle_unweight", 9, "Nbtags >= 1");
    SetCutName("LPLUSJETS", "particle_unweight", 10, "Nbtags >= 2");

    AddCounterName("LPLUSJETS", "particle_weighted", 10 );
    SetCutName("LPLUSJETS", "particle_weighted", 0, "All Events");
    SetCutName("LPLUSJETS", "particle_weighted", 1, "Trigger");
    SetCutName("LPLUSJETS", "particle_weighted", 2, "Prim. Vtx");
    SetCutName("LPLUSJETS", "particle_weighted", 3, "SingleLepton");
    SetCutName("LPLUSJETS", "particle_weighted", 4, "Lep pT > 25 GeV" );
    if( m_config->channel == kElectron ) {
       SetCutName("LPLUSJETS", "particle_weighted", 5, "ETmiss > 30 GeV");
       SetCutName("LPLUSJETS", "particle_weighted", 6, "mTW > 30 GeV");
    }
    else {
       SetCutName("LPLUSJETS", "particle_weighted", 5, "ETmiss > 20 GeV");
       SetCutName("LPLUSJETS", "particle_weighted", 6, "mTW + ETmiss > 60 GeV");
    }
    SetCutName("LPLUSJETS", "particle_weighted", 7, "NJets >= 3");
    SetCutName("LPLUSJETS", "particle_weighted", 8, "NJets >= 4");
    SetCutName("LPLUSJETS", "particle_weighted", 9, "Nbtags >= 1");
    SetCutName("LPLUSJETS", "particle_weighted", 10, "Nbtags >= 2");

    return success;
}


/////////////////////////////////////////


bool CutFlowTTbarResolvedParticleLevel::Apply( EventData * ed )
{
  bool success = true;

  CutFlow::Start();

  unsigned long isMCSignal = m_config->custom_params_flag["isMCSignal"];

  //int isDileptonic = ed->property["isDileptonic"];
  //cout << "DEBUG: isDileptonic = " << isDileptonic << endl;
  //if( isDileptonic < 0 ) cout << "WARNING: event " << ed->info.eventNumber << " isDileptonic flag not initialized" << endl;
  //if( isDileptonic ) cout << "INFO: event " << ed->info.eventNumber << " isDileptonic" << endl;
 
  double weight_particle_level = 1.;
  // apply scaleFactor_PILEUP * scaleFactor_ZVERTEX ?
  ed->property["weight_particle_level"] = weight_particle_level;

  const bool passedParticleSelection = PassedCutFlowParticle( ed );

  int Debug = 0;

  bool fillHistos = true;
  bool fillCorrections = true;


  // there is always a parton-level top  
  if (isMCSignal && fillHistos) {
     FillHistogramsPseudotopParton(ed, weight_particle_level);
  }

  // nb: events could NOT pass the particle-level selection
  //     but you could still be able to reconstruct pseudotops (i.e. 1l4j2b)

  if( !passedParticleSelection ) return success;

  m_pseudotop_particle->SetEventData(ed);
  m_pseudotop_particle->SetTarget(PseudoTopReconstruction::kTruth);
  m_pseudotop_particle->SetChargedLepton(m_config->channel, 0);

      if (Debug) {
        cout << "    jet_n=" << ed->jets.n << " bjets_n=" << ed->bjets.n << endl;
        cout << "    truth_jet_n=" << ed->truth_jets.n << " truth_bjets_n=" << ed->truth_bjets.n << endl;
      }

  m_pseudotop_particle->Run();
  m_VarField["particle_HT_pseudo"] = m_pseudotop_particle->GetHt();
  m_VarField["particle_R_lb"] = m_pseudotop_particle->GetR_lb();
  m_VarField["particle_R_Wb_had"] = m_pseudotop_particle->GetR_Wb_had();
  m_VarField["particle_R_Wb_lep"] = m_pseudotop_particle->GetR_Wb_lep();
  if (fillHistos) {
     FillHistogramsPseudotopParticle(ed, weight_particle_level);
     FillHistogramsPseudotopResponseParticleToParton(ed, weight_particle_level);
  }

  return success;
}



/////////////////////////////////////////


bool CutFlowTTbarResolvedParticleLevel::PassedCutFlowParticle(EventData * ed) {
    bool passed = true;

    const double weight = ed->property["weight_particle_level"];

    const int    el_n  = ed->truth_electrons.n;
    const int    mu_n  = ed->truth_muons.n;

    const bool   single_lept = ( m_config->channel == kElectron ) ?
                                (el_n == 1)&&(mu_n==0) :
                                (el_n == 0)&&(mu_n==1);

    const int    jet_n  = ed->truth_jets.n;
    const int    bjet_n = ed->truth_bjets.n;
    const double ETmiss = ed->MET_truth.et;
    const double mwt    = ed->MET_truth.mwt;

    ControlPlotValues values;
    values.weight = weight;
    values.lep_pt  = ( ed->truth_leptons.n > 0 ) ?  ed->truth_leptons.pT.at(0) : 0.;;
    values.lep_eta = ( ed->truth_leptons.n > 0 ) ?  ed->truth_leptons.eta.at(0) : 0.;;
    values.lep_phi = ( ed->truth_leptons.n > 0 ) ?  ed->truth_leptons.phi.at(0) : 0.;;
values.lep_E   = ( ed->truth_leptons.n > 0 ) ?  ed->truth_leptons.E.at(0) : 0.;;
    values.jet_n   = ed->truth_jets.n;
    values.bjet_n  = ed->truth_bjets.n;
    values.fjet_n  = ed->truth_fjets.n;
    values.ETmiss  = ed->MET_truth.et;
    values.mwt     = ed->MET_truth.mwt;

    for (int j = 0; j < ed->truth_jets.n; ++j) {
        JetValues jet;
        jet.pt  = ed->truth_jets.pT.at(j);
        jet.eta = ed->truth_jets.eta.at(j);
        jet.phi = ed->truth_jets.phi.at(j);
        jet.E   = ed->truth_jets.E.at(j);
        jet.m   = ed->truth_jets.m.at(j);
        values.jets.push_back(&jet);
    }
    for (int bj = 0; bj < ed->truth_bjets.n; ++bj) {
        JetValues jet;
        jet.pt  = ed->truth_bjets.pT.at(bj);
        jet.eta = ed->truth_bjets.eta.at(bj);
        jet.phi = ed->truth_bjets.phi.at(bj);
        jet.E   = ed->truth_bjets.E.at(bj);
        jet.m   = ed->truth_bjets.m.at(bj);
        values.bJets.push_back(&jet);
    }
// 0 All events
    PassedCut( "LPLUSJETS", "particle_unweight" );
    PassedCut( "LPLUSJETS", "particle_weighted", weight );
    FillHistogramsControlPlotsParticle( values );

    // 1 trigger 
    PassedCut( "LPLUSJETS", "particle_unweight" );
    PassedCut( "LPLUSJETS", "particle_weighted", weight );

    // 2 primary vertex
    PassedCut( "LPLUSJETS", "particle_unweight" );
    PassedCut( "LPLUSJETS", "particle_weighted", weight );

    // 3 single lepton
    if( !single_lept )   return !passed;
    PassedCut( "LPLUSJETS", "particle_unweight" );
    PassedCut( "LPLUSJETS", "particle_weighted", weight );

    double lep_pt = ( m_config->channel == kElectron ) ? ed->truth_electrons.pT.at(0) : ed->truth_muons.pT.at(0);

    // 4 lepton pt
    if (lep_pt < 25 * GeV) return !passed;
    PassedCut( "LPLUSJETS", "particle_unweight" );
    PassedCut( "LPLUSJETS", "particle_weighted", weight );

    // 5 ETmiss cut
    const double met_cut = ( m_config->channel == kElectron ) ? 30*GeV : 20*GeV;
    if( ETmiss < met_cut ) return !passed;
    PassedCut("LPLUSJETS", "particle_weighted", weight );
    PassedCut("LPLUSJETS", "particle_unweight");

    // 6 mTW > 30 GeV or mTW+ETmiss>60 GeV
    if( m_config->channel == kElectron ) {
       if( mwt < 30 * GeV) return !passed;
    }
    else {
       if( (mwt + ETmiss) < 60 * GeV ) return !passed;
    }
    PassedCut("LPLUSJETS", "particle_weighted", weight );
    PassedCut("LPLUSJETS", "particle_unweight");

    // 7 Njets >= 3
    if ( jet_n < 3 ) return !passed;
    PassedCut("LPLUSJETS", "particle_weighted", weight );
    PassedCut("LPLUSJETS", "particle_unweight");
    FillHistogramsControlPlotsParticle( values );

    // 8 Njets >= 4
    if (jet_n < 4)         return !passed;
    PassedCut( "LPLUSJETS", "particle_unweight" );
    PassedCut( "LPLUSJETS", "particle_weighted", weight );

    // 9 Nbjets >= 1
    if (bjet_n < 1)        return !passed;
    PassedCut( "LPLUSJETS", "particle_unweight" );
    PassedCut( "LPLUSJETS", "particle_weighted", weight );

    FillHistogramsControlPlotsParticle( values );

    // 10 Nbjets >= 2
    if (bjet_n < 2)        return !passed;
    PassedCut( "LPLUSJETS", "particle_unweight" );
    PassedCut( "LPLUSJETS", "particle_weighted", weight );

    FillHistogramsControlPlotsParticle( values );

    return passed;
}


/////////////////////////////////////////
 

void CutFlowTTbarResolvedParticleLevel::FillHistogramsControlPlotsParticle( ControlPlotValues& values )
{
  //    const int cut = GetLastPassedCut( "LPLUSJETS", "particle_weighted" ) -1;
    //string path = "parton/cutflow/" + alias[cut] + "/";
    //FillHistograms(path, values);
}


// move this to the histogramming facility

void CutFlowTTbarResolvedParticleLevel::FillHistograms(string path, ControlPlotValues& values ){
    m_hm->FillHistograms( path + "lep_pt" , values.lep_pt / GeV, values.weight );
    m_hm->FillHistograms( path + "lep_eta", values.lep_eta, values.weight);
    m_hm->FillHistograms( path + "lep_phi", values.lep_phi,	 values.weight );
    m_hm->FillHistograms( path + "lep_E" ,  values.lep_E / GeV,  values.weight );
    m_hm->FillHistograms( path + "met_pt" ,  values.ETmiss / GeV, values.weight );
    m_hm->FillHistograms( path + "mtw" , values.mwt  / GeV, values.weight );

    m_hm->FillHistograms( path + "jet_n",  values.jet_n, values.weight );
    for (int j = 0; j < values.jets.size(); ++j) {
        JetValues* jet = values.jets.at(j);
        m_hm->FillHistograms( path + "jet_eta" ,  jet->eta, values.weight );
        m_hm->FillHistograms( path + "jet_pt",  jet->pt / GeV, values.weight );
        m_hm->FillHistograms( path + "jet_phi" , jet->phi, values.weight );
        m_hm->FillHistograms( path + "jet_E", jet->E / GeV, values.weight );
        m_hm->FillHistograms( path + "jet_m" ,  jet->m / GeV, values.weight );
    }

    m_hm->FillHistograms( path + "bjet_n", values.bjet_n, values.weight );
    for (int bj = 0; bj < values.bJets.size(); ++bj) {
        JetValues* jet = values.bJets.at(bj);
        m_hm->FillHistograms( path + "bjet_eta",  jet->eta, values.weight );
        m_hm->FillHistograms( path + "bjet_pt",  jet->pt / GeV, values.weight );
        m_hm->FillHistograms( path + "bjet_phi",  jet->phi, values.weight );
        m_hm->FillHistograms( path + "bjet_E",  jet->E / GeV, values.weight );
        m_hm->FillHistograms( path + "bjet_m",  jet->m / GeV, values.weight );
    }
}

/////////////////////////////////////////


void CutFlowTTbarResolvedParticleLevel::FillHistogramsPseudoTop(EventData::Reco_t& particle, int index, string level, string topType, const double weight, const double mbl){
    Particle p(particle, index);
    m_hm->FillHistograms(level + "/4j2b/" + topType + "/pt", p.pt / GeV, weight);
    m_hm->FillHistograms(level + "/4j2b/" + topType + "/eta", p.eta, weight);
    m_hm->FillHistograms(level + "/4j2b/" + topType + "/phi", p.phi, weight);
    m_hm->FillHistograms(level + "/4j2b/" + topType + "/E", p.E / GeV, weight);
    m_hm->FillHistograms(level + "/4j2b/" + topType + "/m", p.m / GeV, weight);
    m_hm->FillHistograms(level + "/4j2b/" + topType + "/absrap", fabs(p.y), weight);
    m_hm->FillHistograms(level + "/4j2b/" + topType + "/rapidity", p.y, weight);

    if ( index %3 == 0 and mbl > 0.){
        m_hm->FillHistograms(level + "/4j2b/" + topType + "/mlb", mbl, weight );
    }
}

/////////////////////////////////////////
void CutFlowTTbarResolvedParticleLevel::FillHistogramsTopPairs(string level, TLorentzVector &topL, TLorentzVector &topH, TLorentzVector &ttSystem, TLorentzVector &WL, TLorentzVector &WH, const double weight){

  string path = level + "/4j2b/difference/";
   // Pout, two entries per event:
   TVector3 zUnit(0., 0., 1.);
   TVector3 top1 = topL.Vect();
   TVector3 top2 = topH.Vect();
   if (top1.Mag() > 0.) {
     TVector3 perp = zUnit.Cross(top1);
     double pout = top2.Dot(perp) / perp.Mag();
     m_VarField[level+"_Pout1"]=pout;
     m_hm->FillHistograms(path + "Pout", pout / GeV, weight);
     //    if (_fillSpecial2D) m_hm->FillHistograms(path + "SystemPtVsPout", pout, ttSystem.Pt());
   }
   if (top2.Mag() > 0.) {
     TVector3 perp = zUnit.Cross(top2);
    double pout = top1.Dot(perp) / perp.Mag();
    m_VarField[level+"_Pout2"]=pout;
    m_hm->FillHistograms(path + "Pout", pout / GeV, weight);
    //    if (_fillSpecial2D) m_hm->FillHistograms(path + "SystemPtVsPout", pout, ttSystem.Pt());
   }

   // top quark pT ratio, two entries per event:
   // z = pTop1 / pTop2
   if (topH.Pt() > 0.) {
     double z = topL.Pt() / topH.Pt();
     m_VarField[level+"_z_ttbar1"]=z;
     m_hm->FillHistograms(path + "z_ttbar", z, weight);
   }
   if (topL.Pt() > 0.) {
     double z = topH.Pt() / topL.Pt();
     m_VarField[level+"_z_ttbar2"]=z;
     m_hm->FillHistograms(path + "z_ttbar", z, weight);
   }

   // top pT dPt as function of pT average:
   m_hm->FillMatrices(path + "dTopPt_vs_AverTopPt", 0.5*(topH.Pt() + topL.Pt()) / GeV, (topH.Pt() - topL.Pt()) / GeV, weight);
   m_hm->FillMatrices(path + "dTopPt_vs_AverTopPt", 0.5*(topH.Pt() + topL.Pt()) / GeV, (topL.Pt() - topH.Pt()) / GeV, weight);
   m_hm->FillMatrices(path + "dTopPtLH_vs_AverTopPt", 0.5*(topH.Pt() + topL.Pt()) / GeV, (topL.Pt() - topH.Pt()) / GeV, weight);
   m_hm->FillMatrices(path + "dTopPtLH_vs_TopLPt", topL.Pt() / GeV, (topL.Pt() - topH.Pt()) / GeV, weight);
   m_hm->FillMatrices(path + "dTopPtLH_vs_TopHPt", topH.Pt() / GeV, (topL.Pt() - topH.Pt()) / GeV, weight);
   
   m_VarField[level+"_topH_pt"]=topH.Pt() / GeV;
   m_VarField[level+"_topL_pt"]=topL.Pt() / GeV;
   
   // chi = exp |y1-y2|
   double chittbar = exp(TMath::Abs(topL.Rapidity() - topH.Rapidity()));
   m_VarField[level+"_Chi_ttbar"]=chittbar;
   m_hm->FillHistograms(path + "Chi_ttbar", chittbar , weight);
   //  if (_fillSpecial2D) m_hm->FillHistograms(path + "SystemPtVsChittbar", chittbar, ttSystem.Pt());

   // y_boost
   double yboost = 0.5*(TMath::Abs(topL.Rapidity() + topH.Rapidity()));
   m_VarField[level+"_Yboost"]=yboost;
   m_hm->FillHistograms(path + "Yboost", yboost , weight);
   // if (_fillSpecial2D) m_hm->FillHistograms(path + "SystemPtVsYboost", yboost, ttSystem.Pt());

   // ttbar cos theta *
   TVector3 SystemVec = ttSystem.Vect(); // need this for the boost
   TLorentzVector TopLCMS;
   TopLCMS.SetPtEtaPhiE(topL.Pt(), topL.Eta(), topL.Phi(), topL.E());
   TLorentzVector TopHCMS;
   TopHCMS.SetPtEtaPhiE(topH.Pt(), topH.Eta(), topH.Phi(), topH.E());

   // w.r.t. beam axis:
   TVector3 boostVec = - (ttSystem.BoostVector()); // boost back to the original frame
   TopLCMS.Boost(0., 0., boostVec.Z());
   TopHCMS.Boost(0., 0., boostVec.Z());
   double TopLCosThetaStar = cos(TopLCMS.Theta());
   double TopHCosThetaStar = cos(TopHCMS.Theta());
   // JK: fill just one of these? Should be complements to Pi, anyway...
   m_hm->FillHistograms(path + "topLCosThetaStar", TopLCosThetaStar, weight);
   m_hm->FillHistograms(path + "topHCosThetaStar", TopHCosThetaStar, weight);

   // opening angle in lab:
   TVector3 TopLVec = topL.Vect();
   TVector3 TopHVec = topH.Vect();
   double TopCosAngle = TopLVec.Dot(TopHVec) / ((TopHVec.Mag())*(TopLVec.Mag()));
   m_hm->FillHistograms(path + "TopCosOpeningAngle", TopCosAngle, weight);


   // variables by Gavin Salam:
   double pt1 = topL.Pt();
   double pt2 = topH.Pt();
   double HT = pt1 + pt2;
   double Delta1 = (3*pt1 - pt2) / HT;
   double Delta2 = (3*pt2 - pt1) / HT;
   double DeltaPhi = TMath::Abs(topL.DeltaPhi(topH));
   m_VarField[level+"_Salam_ttbar1"]=Delta1;
   m_VarField[level+"_Salam_ttbar2"]=Delta2;
   m_VarField[level+"_dPhi"]=DeltaPhi;
   m_VarField[level+"_HT_ttbar"]=HT;
   
   m_hm->FillHistograms(path + "dPhi_ttbar", DeltaPhi, weight);
   // two entries per event:
   m_hm->FillMatrices(path + "Salam_ttbar_vs_dPhi_ttbar", DeltaPhi, Delta1, weight);
   m_hm->FillMatrices(path + "Salam_ttbar_vs_dPhi_ttbar", DeltaPhi, Delta2, weight);
   m_hm->FillHistograms(path + "Salam_ttbar", Delta1, weight);
   m_hm->FillHistograms(path + "Salam_ttbar", Delta2, weight);
   m_hm->FillHistograms(path + "HT_ttbar",m_VarField.find("reco_HT_ttbar")->second / GeV, weight);
   if (level == "reco")
     m_hm->FillHistograms(path + "HT_pseudo",m_VarField.find("reco_HT_pseudo")->second / GeV, weight);
   else if (level == "particle")
     m_hm->FillHistograms(path + "HT_pseudo",m_VarField.find("particle_HT_pseudo")->second / GeV, weight);
   
   //px, py, pz
   double pxL = pt1*cos(topL.Phi());
   double pyL = pt1*sin(topL.Phi());
   double pzL = pt1*sinh(topL.Eta());
   double pxH = pt1*cos(topH.Phi());
   double pyH = pt1*sin(topH.Phi());
   double pzH = pt1*sinh(topH.Eta());
   m_VarField[level+"_pxL"] = pxL;
   m_VarField[level+"_pxH"] = pxH;
   m_VarField[level+"_pyL"] = pyL;
   m_VarField[level+"_pyH"] = pyH;
   m_VarField[level+"_pzL"] = pzL;
   m_VarField[level+"_pzH"] = pzH;
   
   //W gymnastics
   if (level=="particle"){
     m_VarField[level+"_ptRatioWtopL"] = WL.Pt()/topL.Pt();
     m_VarField[level+"_ptRatioWtopH"] = WH.Pt()/topH.Pt();
     m_hm->FillHistograms(path+"ptRatioWtopH",m_VarField.find("particle_ptRatioWtopH")->second, weight);
     m_hm->FillHistograms(path+"ptRatioWtopL",m_VarField.find("particle_ptRatioWtopL")->second, weight);
     m_hm->FillHistograms(path+"R_lb",m_VarField.find("particle_R_lb")->second, weight);
     m_hm->FillHistograms(path+"mlb",m_VarField.find("particle_mlb")->second, weight);
     m_hm->FillHistograms(path+"R_Wb_had",m_VarField.find("particle_R_Wb_had")->second, weight);
     m_hm->FillHistograms(path+"R_Wb_lep",m_VarField.find("particle_R_Wb_lep")->second, weight);
  }
}

/////////////////////////////////////////

void CutFlowTTbarResolvedParticleLevel::FillHistogramsPseudoTopPairs(EventData::Reco_t& particle, int indexL, int indexH, int indextt, string level, const double weight){

  Particle ptopL(particle, indexL);
  Particle ptopH(particle, indexH);
  Particle pttSystem(particle, indextt);
  Particle pWL(particle, indextt + 1);
  Particle pWH(particle, indextt + 2);

  TLorentzVector topL = ptopL.MakeLorentz();
  TLorentzVector topH = ptopH.MakeLorentz();
  TLorentzVector ttSystem = pttSystem.MakeLorentz();
  TLorentzVector WL = pWL.MakeLorentz();
  TLorentzVector WH = pWH.MakeLorentz();

  FillHistogramsTopPairs(level, topL, topH, ttSystem, WL, WH, weight);
}

/////////////////////////////////////////
void CutFlowTTbarResolvedParticleLevel::FillHistogramsPartonTop(EventData::Truth_t& particle, int index, string level, string topType, const double weight){
  Particle p(particle, index);
  m_hm->FillHistograms(level + "/4j2b/" + topType + "/pt", p.pt / GeV, weight);
  m_hm->FillHistograms(level + "/4j2b/" + topType + "/eta", p.eta, weight);
  m_hm->FillHistograms(level + "/4j2b/" + topType + "/phi", p.phi, weight);
  m_hm->FillHistograms(level + "/4j2b/" + topType + "/E", p.E / GeV, weight);
  m_hm->FillHistograms(level + "/4j2b/" + topType + "/m", p.m / GeV, weight);
  m_hm->FillHistograms(level + "/4j2b/" + topType + "/absrap", fabs(p.y), weight);
  m_hm->FillHistograms(level + "/4j2b/" + topType + "/rapidity", p.y, weight);
}


void CutFlowTTbarResolvedParticleLevel::FillHistogramsPartonTopPairs(EventData::Truth_t& particle, int indexL, int indexH, int indextt, string level, const double weight){
  Particle ptopL(particle, indexL);
  Particle ptopH(particle, indexH);
  Particle pttSystem(particle, indextt);

  TLorentzVector topL = ptopL.MakeLorentz();
  TLorentzVector topH = ptopH.MakeLorentz();
  TLorentzVector ttSystem = pttSystem.MakeLorentz();
  TLorentzVector WL;
  TLorentzVector WH;

  FillHistogramsTopPairs(level, topL, topH, WL, WH, ttSystem, weight);

}


/////////////////////////////////////////

void CutFlowTTbarResolvedParticleLevel::FillHistogramsPseudotopParticle( EventData * ed, const double weight, string level) {


  if (ed->truth_leptons.n > 0) {
    TLorentzVector lep_bjet = HelperFunctions::MakeFourMomentum(ed->jets, ed->iproperty["ptcl_pseudotop_lep_bjet_index"]);
    TLorentzVector lep = HelperFunctions::MakeFourMomentum( ed->truth_leptons, 0 );
    TLorentzVector lb = lep + lep_bjet;
    FillHistogramsPseudoTop(ed->reco, 0, level, "topL", weight, lb.M());
  } else {
    FillHistogramsPseudoTop(ed->reco, 0, level, "topL", weight, -1);
  }
    FillHistogramsPseudoTop(ed->reco, 1, level, "topH", weight);
    FillHistogramsPseudoTop(ed->reco, 2, level, "tt", weight);

    FillHistogramsPseudoTop(ed->reco, 3, level, "WL", weight);
    FillHistogramsPseudoTop(ed->reco, 4, level, "WH", weight);

    FillHistogramsPseudoTopPairs(ed->reco, 0, 1, 2, level, weight);

}


/////////////////////////////////////////

void CutFlowTTbarResolvedParticleLevel::FillHistogramsPseudotopParton( EventData * ed, const double weight )
{
    int ilep, ihad;
    int itt = 2;

    if (ed->mctruth.n <= 0) {
      cerr << "THIS SHOULD NOT HAPPEN! mctruth size 0! In CutFlowTTbarResolvedParticleLevel::FillHistogramsPseudotopParton" << endl;
      //      return;
    }

    const bool isHadronic = ed->mctruth.property["isHadronic"].at(0);
    if( isHadronic ) {
        ihad = 0;
        ilep = 1;
    }
    else {
	ihad = 1;
        ilep = 0;
    }

    FillHistogramsPartonTop(ed->mctruth, ilep, "parton", "topL", weight);
    FillHistogramsPartonTop(ed->mctruth, ihad, "parton", "topH", weight);
    FillHistogramsPartonTop(ed->mctruth, itt, "parton", "tt", weight);
    FillHistogramsPartonTopPairs(ed->mctruth, ilep, ihad, itt, "parton", weight);

    // TODO: sth like:
    //    FillHistogramsPseudoTopPairs(ed->reco, 0, 1, 2, "reco", weight);

}


/////////////////////////////////////////
// Matching

 void CutFlowTTbarResolvedParticleLevel::FillHistogramsMatchingParticleToParton( double weight )
 {

 }


/////////////////////////////////////////
// response matrices


void CutFlowTTbarResolvedParticleLevel::FillMatrix(string path, Particle& px, Particle& py, double weight){
    m_hm->FillMatrices( path + "_pt", px.pt / GeV, py.pt / GeV, weight);
    m_hm->FillMatrices( path + "_eta", px.eta, py.eta, weight);
    m_hm->FillMatrices( path + "_phi", px.phi, py.phi, weight);
    m_hm->FillMatrices( path + "_m", px.m  / GeV, py.m  / GeV, weight);
    m_hm->FillMatrices( path + "_absrap", fabs(px.y), fabs(py.y), weight);
    m_hm->FillMatrices( path + "_rapidity", px.y, py.y, weight);
    m_hm->FillMatrices( path + "_E", px.E / GeV, py.E / GeV, weight);
  }

  void CutFlowTTbarResolvedParticleLevel::FillHistogramsPseudotopResponseParticleToParton(  EventData * ed, const double weight )
  {
    // particle level
    Particle particleTopL(ed->reco, 0);
    Particle particleTopH(ed->reco, 1);
    Particle particleTT(ed->reco, 2);

    // parton level
    int ilep, ihad;
    int itt = 2;

    const bool isHadronic = ed->mctruth.property["isHadronic"].at(0);
    if( isHadronic ) {
        ihad = 0;
        ilep = 1;
    }
    else {
	ihad = 1;
        ilep = 0;
    }

    Particle partonTopL(ed->mctruth, ilep);
    Particle partonTopH(ed->mctruth, ihad);
    Particle partonTT(ed->mctruth, itt);

    // particle -> parton
    FillMatrix("particle/4j2b/topL/Matrix_particle_parton", particleTopL, partonTopL, weight);
    FillMatrix("particle/4j2b/topH/Matrix_particle_parton", particleTopH, partonTopH, weight);
    FillMatrix("particle/4j2b/tt/Matrix_particle_parton", particleTT, partonTT, weight);
    FillMatrix("parton/4j2b/topL/Matrix_parton_particle", partonTopL, particleTopL, weight);
    FillMatrix("parton/4j2b/topH/Matrix_parton_particle", partonTopH, particleTopH, weight);
    FillMatrix("parton/4j2b/tt/Matrix_parton_particle", partonTT, particleTT, weight);
    
    m_hm->FillMatrices("parton/4j2b/difference/Matrix_parton_particle_Pout",m_VarField.find("parton_Pout1")->second / GeV, m_VarField.find("particle_Pout1")->second / GeV, weight);
    m_hm->FillMatrices("parton/4j2b/difference/Matrix_parton_particle_Pout",m_VarField.find("parton_Pout2")->second / GeV, m_VarField.find("particle_Pout2")->second / GeV, weight);
    m_hm->FillMatrices("parton/4j2b/difference/Matrix_parton_particle_z_ttbar",m_VarField.find("parton_z_ttbar1")->second, m_VarField.find("particle_z_ttbar1")->second, weight);
    m_hm->FillMatrices("parton/4j2b/difference/Matrix_parton_particle_z_ttbar",m_VarField.find("parton_z_ttbar2")->second, m_VarField.find("particle_z_ttbar2")->second, weight);
    m_hm->FillMatrices("parton/4j2b/difference/Matrix_parton_particle_Yboost",m_VarField.find("parton_Yboost")->second ,m_VarField.find("particle_Yboost")->second, weight);
    m_hm->FillMatrices("parton/4j2b/difference/Matrix_parton_particle_dPhi_ttbar",m_VarField.find("parton_dPhi")->second, m_VarField.find("particle_dPhi")->second, weight);
    m_hm->FillMatrices("parton/4j2b/difference/Matrix_parton_particle_HT_ttbar",m_VarField.find("parton_HT_ttbar")->second / GeV, m_VarField.find("particle_HT_ttbar")->second / GeV, weight);
    m_hm->FillMatrices("parton/4j2b/difference/Matrix_parton_particle_Chi_ttbar",m_VarField.find("parton_Chi_ttbar")->second, m_VarField.find("particle_Chi_ttbar")->second, weight);
    m_hm->FillMatrices("parton/4j2b/difference/Matrix_parton_particle_Salam_ttbar",m_VarField.find("parton_Salam_ttbar1")->second, m_VarField.find("particle_Salam_ttbar1")->second, weight);
    m_hm->FillMatrices("parton/4j2b/difference/Matrix_parton_particle_Salam_ttbar",m_VarField.find("parton_Salam_ttbar2")->second, m_VarField.find("particle_Salam_ttbar2")->second, weight);
    m_hm->FillMatrices("parton/4j2b/topL/Matrix_parton_particle_px",m_VarField.find("parton_pxL")->second / GeV, m_VarField.find("particle_pxL")->second / GeV, weight);
    m_hm->FillMatrices("parton/4j2b/topH/Matrix_parton_particle_px",m_VarField.find("parton_pxH")->second / GeV, m_VarField.find("particle_pxH")->second / GeV, weight);
    m_hm->FillMatrices("parton/4j2b/topL/Matrix_parton_particle_py",m_VarField.find("parton_pyL")->second / GeV, m_VarField.find("particle_pyL")->second / GeV, weight);
    m_hm->FillMatrices("parton/4j2b/topH/Matrix_parton_particle_py",m_VarField.find("parton_pyH")->second / GeV, m_VarField.find("particle_pyH")->second / GeV, weight);
    m_hm->FillMatrices("parton/4j2b/topL/Matrix_parton_particle_pz",m_VarField.find("parton_pzL")->second / GeV, m_VarField.find("particle_pzL")->second / GeV, weight);
    m_hm->FillMatrices("parton/4j2b/topH/Matrix_parton_particle_pz",m_VarField.find("parton_pzH")->second / GeV, m_VarField.find("particle_pzH")->second / GeV, weight);    
    
    m_hm->FillMatrices("particle/4j2b/difference/Matrix_particle_parton_Pout",m_VarField.find("particle_Pout1")->second / GeV, m_VarField.find("parton_Pout1")->second / GeV, weight);
    m_hm->FillMatrices("particle/4j2b/difference/Matrix_particle_parton_Pout",m_VarField.find("particle_Pout2")->second / GeV, m_VarField.find("parton_Pout2")->second / GeV, weight);
    m_hm->FillMatrices("particle/4j2b/difference/Matrix_particle_parton_z_ttbar",m_VarField.find("particle_z_ttbar1")->second, m_VarField.find("parton_z_ttbar1")->second, weight);
    m_hm->FillMatrices("particle/4j2b/difference/Matrix_particle_parton_z_ttbar",m_VarField.find("particle_z_ttbar2")->second, m_VarField.find("parton_z_ttbar2")->second, weight);
    m_hm->FillMatrices("particle/4j2b/difference/Matrix_particle_parton_Yboost",m_VarField.find("particle_Yboost")->second, m_VarField.find("parton_Yboost")->second, weight);
    m_hm->FillMatrices("particle/4j2b/difference/Matrix_particle_parton_dPhi_ttbar",m_VarField.find("particle_dPhi")->second, m_VarField.find("parton_dPhi")->second, weight);
    m_hm->FillMatrices("particle/4j2b/difference/Matrix_particle_parton_HT_ttbar",m_VarField.find("particle_HT_ttbar")->second / GeV, m_VarField.find("parton_HT_ttbar")->second / GeV, weight);
    m_hm->FillMatrices("particle/4j2b/difference/Matrix_particle_parton_Chi_ttbar",m_VarField.find("particle_Chi_ttbar")->second, m_VarField.find("parton_Chi_ttbar")->second, weight);
    m_hm->FillMatrices("particle/4j2b/difference/Matrix_particle_parton_Salam_ttbar",m_VarField.find("particle_Salam_ttbar1")->second, m_VarField.find("parton_Salam_ttbar1")->second, weight);
    m_hm->FillMatrices("particle/4j2b/difference/Matrix_particle_parton_Salam_ttbar",m_VarField.find("particle_Salam_ttbar2")->second, m_VarField.find("parton_Salam_ttbar2")->second, weight);
    m_hm->FillMatrices("particle/4j2b/topL/Matrix_particle_parton_px",m_VarField.find("particle_pxL")->second / GeV, m_VarField.find("parton_pxL")->second / GeV, weight);
    m_hm->FillMatrices("particle/4j2b/topH/Matrix_particle_parton_px",m_VarField.find("particle_pxH")->second / GeV, m_VarField.find("parton_pxH")->second / GeV, weight);
    m_hm->FillMatrices("particle/4j2b/topL/Matrix_particle_parton_py",m_VarField.find("particle_pyL")->second / GeV, m_VarField.find("parton_pyL")->second / GeV, weight);
    m_hm->FillMatrices("particle/4j2b/topH/Matrix_particle_parton_py",m_VarField.find("particle_pyH")->second / GeV, m_VarField.find("parton_pyH")->second / GeV, weight);
    m_hm->FillMatrices("particle/4j2b/topL/Matrix_particle_parton_pz",m_VarField.find("particle_pzL")->second / GeV, m_VarField.find("parton_pzL")->second / GeV, weight);
    m_hm->FillMatrices("particle/4j2b/topH/Matrix_particle_parton_pz",m_VarField.find("particle_pzH")->second / GeV, m_VarField.find("parton_pzH")->second / GeV, weight);
  }


/////////////////////////////////////////
// Plugin

extern "C" {
  CutFlowPluginFactory_TTbarResolvedParticleLevel * MakeCutFlowPlugin() {
    return new CutFlowPluginFactory_TTbarResolvedParticleLevel( "TTbarResolvedParticleLevel" );
  };
}

