#include "CutFlowTTbarResolvedParticleLevel.h"

CutFlowTTbarResolvedParticleLevel::CutFlowTTbarResolvedParticleLevel()
{
   m_pseudotop_particle = new PseudoTopReconstruction();

   m_pseudotop_matching_particle2parton = new PseudoTopMatching( PseudoTopMatching::kParticleToParton );

   alias = {
	"beforeCuts", "trig", "pvtx", "lept", "met30", "mtw35", "2j", "4j", "4j1b", "afterCuts"
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

    AddCounterName("LPLUSJETS", "particle_unweight", 9);
    SetCutName("LPLUSJETS", "particle_unweight", 0, "All Events");
    SetCutName("LPLUSJETS", "particle_unweight", 1, "Trigger");
    SetCutName("LPLUSJETS", "particle_unweight", 2, "Prim. Vtx");
    SetCutName("LPLUSJETS", "particle_unweight", 3, "SingleLepton");
    SetCutName("LPLUSJETS", "particle_unweight", 4, "Lep pT > 25 GeV" );
    SetCutName("LPLUSJETS", "particle_unweight", 5, "ETmiss > 30 GeV");
    SetCutName("LPLUSJETS", "particle_unweight", 6, "mTW > 35 GeV");
    SetCutName("LPLUSJETS", "particle_unweight", 7, "NJets >= 4");
    SetCutName("LPLUSJETS", "particle_unweight", 8, "Nbtags >= 1");
    SetCutName("LPLUSJETS", "particle_unweight", 9, "Nbtags >= 2");

    AddCounterName("LPLUSJETS", "particle_weighted", 9);
    SetCutName("LPLUSJETS", "particle_weighted", 0, "All Events");
    SetCutName("LPLUSJETS", "particle_weighted", 1, "Trigger");
    SetCutName("LPLUSJETS", "particle_weighted", 2, "Prim. Vtx");
    SetCutName("LPLUSJETS", "particle_weighted", 3, "SingleLepton");
    SetCutName("LPLUSJETS", "particle_weighted", 4, "Lep pT > 25 GeV" );
    SetCutName("LPLUSJETS", "particle_weighted", 5, "ETmiss > 30 GeV");
    SetCutName("LPLUSJETS", "particle_weighted", 6, "mTW > 35 GeV");
    SetCutName("LPLUSJETS", "particle_weighted", 7, "NJets >= 4");
    SetCutName("LPLUSJETS", "particle_weighted", 8, "Nbtags >= 1");
    SetCutName("LPLUSJETS", "particle_weighted", 9, "Nbtags >= 2");

    return success;
}


/////////////////////////////////////////


bool CutFlowTTbarResolvedParticleLevel::Apply( EventData * ed )
{
  bool success = true;

  CutFlow::Start();

  unsigned long isMCSignal = m_config->custom_params_flag["isMCSignal"];

  double weight_particle_level = 1.;
  // apply scaleFactor_PILEUP * scaleFactor_ZVERTEX ?
  ed->property["weight_particle_level"] = weight_particle_level;

  const bool passedParticleSelection = PassedCutFlowParticle( ed );

  int Debug = 0;

  bool fillHistos = true;
  bool fillCorrections = true;

/*
  bool splitSample = true; // HACK!
  if (splitSample) {
    fillHistos = not (m_rand -> Integer(2));
    fillCorrections = not fillHistos;
  }
*/

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
  if (fillHistos) {
     FillHistogramsPseudotopParticle(ed, weight_particle_level);
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
    for (int fj = 0; fj < ed->truth_fjets.n; ++fj) {
        JetValues jet;
        jet.pt  = ed->truth_fjets.pT.at(fj);
        jet.eta = ed->truth_fjets.eta.at(fj);
        jet.phi = ed->truth_fjets.phi.at(fj);
        jet.E   = ed->truth_fjets.E.at(fj);
        jet.m   = ed->truth_fjets.m.at(fj);
        values.fatJets.push_back(&jet);
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

    // 5 ETmiss
    if (ETmiss < 30 * GeV) return !passed;
    PassedCut( "LPLUSJETS", "particle_unweight" );
    PassedCut( "LPLUSJETS", "particle_weighted", weight );

    // 6 MTW
    if (mwt < 35 * GeV)    return !passed;
    PassedCut( "LPLUSJETS", "particle_unweight" );
    PassedCut( "LPLUSJETS", "particle_weighted", weight );

    // 7 Njets >= 4
    if (jet_n < 4)         return !passed;
    PassedCut( "LPLUSJETS", "particle_unweight" );
    PassedCut( "LPLUSJETS", "particle_weighted", weight );

    // 8 Nbjets >= 1
    if (bjet_n < 1)        return !passed;
    PassedCut( "LPLUSJETS", "particle_unweight" );
    PassedCut( "LPLUSJETS", "particle_weighted", weight );

    FillHistogramsControlPlotsParticle( values );

    // 9 Nbjets >= 2
    if (bjet_n < 2)        return !passed;
    PassedCut( "LPLUSJETS", "particle_unweight" );
    PassedCut( "LPLUSJETS", "particle_weighted", weight );

    FillHistogramsControlPlotsParticle( values );

    return passed;
}


/////////////////////////////////////////
 

void CutFlowTTbarResolvedParticleLevel::FillHistogramsControlPlotsParticle( ControlPlotValues& values )
{
    const int cut = GetLastPassedCut( "LPLUSJETS", "particle_weighted" ) -1;
    string path = "parton/cutflow/" + alias[cut] + "/";
    FillHistograms(path, values);
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

    m_hm->FillHistograms( path + "fjet_n", values.fjet_n, values.weight );
    for (int fj = 0; fj < values.fatJets.size(); ++fj) {
        JetValues* jet = values.fatJets.at(fj);
        m_hm->FillHistograms( path + "fjet_eta",  jet->eta, values.weight );
        m_hm->FillHistograms( path + "fjet_pt",  jet->pt / GeV, values.weight );
        m_hm->FillHistograms( path + "fjet_phi",  jet->phi, values.weight );
        m_hm->FillHistograms( path + "fjet_E",  jet->E / GeV, values.weight );
        m_hm->FillHistograms( path + "fjet_m",  jet->m / GeV, values.weight );
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

    if (index %3 == 0 and mbl > 0.){
        m_hm->FillHistograms(level + "/4j2b/" + topType + "/mlb", mbl, weight );
    }
}

/////////////////////////////////////////
void CutFlowTTbarResolvedParticleLevel::FillHistogramsTopPairs(string path, TLorentzVector &topL, TLorentzVector &topH, TLorentzVector &ttSystem, const double weight){

   // Pout, two entries per event:
   TVector3 zUnit(0., 0., 1.);
   TVector3 top1 = topL.Vect();
   TVector3 top2 = topH.Vect();
   if (top1.Mag() > 0.) {
     TVector3 perp = zUnit.Cross(top1);
     double pout = top2.Dot(perp) / perp.Mag();
     m_hm->FillHistograms(path + "Pout", pout / GeV, weight);
     //    if (_fillSpecial2D) m_hm->FillHistograms(path + "SystemPtVsPout", pout, ttSystem.Pt());
   }
   if (top2.Mag() > 0.) {
     TVector3 perp = zUnit.Cross(top2);
    double pout = top1.Dot(perp) / perp.Mag();
    m_hm->FillHistograms(path + "Pout", pout / GeV, weight);
    //    if (_fillSpecial2D) m_hm->FillHistograms(path + "SystemPtVsPout", pout, ttSystem.Pt());
   }

   // top quark pT ratio, two entries per event:
   // z = pTop1 / pTop2
   if (topH.Pt() > 0.) {
     double z = topL.Pt() / topH.Pt();
     m_hm->FillHistograms(path + "z_ttbar", z, weight);
   }
   if (topL.Pt() > 0.) {
     double z = topH.Pt() / topL.Pt();
     m_hm->FillHistograms(path + "z_ttbar", z, weight);
   }

   // TODO: top pT dPt as function of pT average
   // chi = exp |y1-y2|
   double chittbar = exp(TMath::Abs(topL.Rapidity() - topH.Rapidity()));
   m_hm->FillHistograms(path + "Chi_ttbar", chittbar , weight);
   //  if (_fillSpecial2D) m_hm->FillHistograms(path + "SystemPtVsChittbar", chittbar, ttSystem.Pt());

   // y_boost
   double yboost = 0.5*(TMath::Abs(topL.Rapidity() + topH.Rapidity()));
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

   /*
   // TODO!
   m_hm->FillMatrices(path + "SalamDeltaVsDeltaPhi", DeltaPhi, Delta1, weight);
   m_hm->FillMatrices(path + "SalamDeltaVsDeltaPhi", DeltaPhi, Delta2, weight);
   */

   m_hm->FillHistograms(path + "dPhi_ttbar", DeltaPhi, weight);
   m_hm->FillHistograms(path + "Salam_ttbar", Delta1, weight);
   m_hm->FillHistograms(path + "Salam_ttbar", Delta2, weight);

 }

/////////////////////////////////////////

void CutFlowTTbarResolvedParticleLevel::FillHistogramsPseudoTopPairs(EventData::Reco_t& particle, int indexL, int indexH, int indextt, string level, const double weight){

  Particle ptopL(particle, indexL);
  Particle ptopH(particle, indexH);
  Particle pttSystem(particle, indextt);

  TLorentzVector topL = ptopL.MakeLorentz();
  TLorentzVector topH = ptopH.MakeLorentz();
  TLorentzVector ttSystem = pttSystem.MakeLorentz();

  string path = level + "/4j2b/difference/";

  FillHistogramsTopPairs(path, topL, topH, ttSystem, weight);
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

  string path = level + "/4j2b/difference/";
  FillHistogramsTopPairs(path, topL, topH, ttSystem, weight);

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

    FillHistogramsPseudoTopPairs(ed->reco, 0, 1, 2, level, weight);

}


/////////////////////////////////////////

void CutFlowTTbarResolvedParticleLevel::FillHistogramsPseudotopParton( EventData * ed, const double weight )
{
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


void CutFlowTTbarResolvedParticleLevel::FillMatrix(string path, Particle& py, Particle& px, double weight){
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

    // particle > parton
    FillMatrix("particle/4j2b/topL/Matrix_particle_parton", particleTopL, partonTopL, weight);
    FillMatrix("particle/4j2b/topH/Matrix_particle_parton", particleTopH, partonTopH, weight);
    FillMatrix("particle/4j2b/tt/Matrix_particle_parton", particleTT, partonTT, weight);
    FillMatrix("parton/4j2b/topL/Matrix_parton_particle", partonTopL, particleTopL, weight);
    FillMatrix("parton/4j2b/topH/Matrix_parton_particle", partonTopH, particleTopH, weight);
    FillMatrix("parton/4j2b/tt/Matrix_parton_particle", partonTT, particleTT, weight);
  }


/////////////////////////////////////////
// Plugin

extern "C" {
  CutFlowPluginFactory_TTbarResolvedParticleLevel * MakeCutFlowPlugin() {
    return new CutFlowPluginFactory_TTbarResolvedParticleLevel( "TTbarResolvedParticleLevel" );
  };
}

