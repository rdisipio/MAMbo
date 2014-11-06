#include "CutFlowTTbarResolved.h"

CutFlowTTbarResolved::CutFlowTTbarResolved() {
    m_pseudotop_reco = new PseudoTopReconstruction();
    m_pseudotop_particle = new PseudoTopReconstruction();
    
    m_pseudotop_matching_reco2particle   = new PseudoTopMatching( PseudoTopMatching::kRecoToParticle );
    m_pseudotop_matching_reco2parton     = new PseudoTopMatching( PseudoTopMatching::kRecoToParton );
    m_pseudotop_matching_particle2parton = new PseudoTopMatching( PseudoTopMatching::kParticleToParton );
    
    alias = {
        "beforeCuts", "trig", "pvtx", "lept", "met30", "mtw35", "2j", "4j", "4j1b", "afterCuts"
    };
}

CutFlowTTbarResolved::~CutFlowTTbarResolved() {
    SAFE_DELETE( m_pseudotop_reco )
    SAFE_DELETE( m_pseudotop_particle )
    
    SAFE_DELETE( m_pseudotop_matching_reco2particle )
    SAFE_DELETE( m_pseudotop_matching_reco2parton )
    SAFE_DELETE( m_pseudotop_matching_particle2parton )
}

/////////////////////////////////////////

bool CutFlowTTbarResolved::Initialize() {
    bool success = true;

//    int isMCSignal = (int) m_config->custom_params["isMCSignal"];
    unsigned long isRealData = m_config->custom_params_flag["isRealData"];

    AddChannel("LPLUSJETS");

    AddCounterName("LPLUSJETS", "reco_unweight", 9);
    SetCutName("LPLUSJETS", "reco_unweight", 0, "All Events");
    SetCutName("LPLUSJETS", "reco_unweight", 1, "Trigger");
    SetCutName("LPLUSJETS", "reco_unweight", 2, "Prim. Vtx");
    SetCutName("LPLUSJETS", "reco_unweight", 3, "SingleLepton");
    SetCutName("LPLUSJETS", "reco_unweight", 4, "Lep pT > 25 GeV" );
    SetCutName("LPLUSJETS", "reco_unweight", 5, "ETmiss > 30 GeV");
    SetCutName("LPLUSJETS", "reco_unweight", 6, "mTW > 35 GeV");
    SetCutName("LPLUSJETS", "reco_unweight", 7, "NJets >= 4");
    SetCutName("LPLUSJETS", "reco_unweight", 8, "Nbtags >= 1");
    SetCutName("LPLUSJETS", "reco_unweight", 9, "Nbtags >= 2");

    AddCounterName("LPLUSJETS", "reco_weighted", 9);
    SetCutName("LPLUSJETS", "reco_weighted", 0, "All Events");
    SetCutName("LPLUSJETS", "reco_weighted", 1, "Trigger");
    SetCutName("LPLUSJETS", "reco_weighted", 2, "Prim. Vtx");
    SetCutName("LPLUSJETS", "reco_weighted", 3, "SingleLepton");
    SetCutName("LPLUSJETS", "reco_weighted", 4, "Lep pT > 25 GeV" );
    SetCutName("LPLUSJETS", "reco_weighted", 5, "ETmiss > 30 GeV");
    SetCutName("LPLUSJETS", "reco_weighted", 6, "mTW > 35 GeV");
    SetCutName("LPLUSJETS", "reco_weighted", 7, "NJets >= 4");
    SetCutName("LPLUSJETS", "reco_weighted", 8, "Nbtags >= 1");
    SetCutName("LPLUSJETS", "reco_weighted", 9, "Nbtags >= 2");

    if( isRealData ) return success;

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

bool FillHistograms(int cutN) {
    bool success = true;

    return success;
}


/////////////////////////////////////////

bool CutFlowTTbarResolved::Apply(EventData * ed) {
    bool success = true;

    CutFlow::Start();

    unsigned long isMCSignal = m_config->custom_params_flag["isMCSignal"];
    unsigned long isRealData = m_config->custom_params_flag["isRealData"];

    double weight_reco_level     = 1.;
    double weight_particle_level = 1.;

    if( !isRealData ) {
   	 weight_reco_level     = ed->info.mcWeight;
         weight_particle_level = ed->info.mcWeight;
 
         if( fabs(weight_reco_level) < 1e-5 ) weight_reco_level /= fabs(weight_reco_level);
         if( fabs(weight_particle_level) < 1e-5 ) weight_particle_level /= fabs(weight_particle_level);

         const double scaleFactor_PILEUP     = ed->property["scaleFactor_PILEUP"];
         const double scaleFactor_ELE        = ed->property["scaleFactor_ELE"];
         const double scaleFactor_MUON       = ed->property["scaleFactor_MUON"];
         const double scaleFactor_BTAG       = ed->property["scaleFactor_BTAG"];
         const double scaleFactor_TRIGGER    = ed->property["scaleFactor_TRIGGER"];
         const double scaleFactor_WJETSNORM  = ed->property["scaleFactor_WJETSNORM"];
         const double scaleFactor_WJETSSHAPE = ed->property["scaleFactor_WJETSSHAPE"];
         const double scaleFactor_JVFSF      = ed->property["scaleFactor_JVFSF"];
         const double scaleFactor_ZVERTEX    = ed->property["scaleFactor_ZVERTEX"];

         weight_reco_level *=
            scaleFactor_PILEUP * scaleFactor_TRIGGER * scaleFactor_JVFSF * scaleFactor_ZVERTEX *
            //scaleFactor_ELE *scaleFactor_MUON *
            scaleFactor_BTAG *
            scaleFactor_WJETSNORM * scaleFactor_WJETSSHAPE;
    
         weight_particle_level *= scaleFactor_PILEUP * scaleFactor_ZVERTEX;
    }

    ed->property["weight_particle_level"] = weight_particle_level;
    ed->property["weight_reco_level"]     = weight_reco_level;

//    if (fabs(weight_reco_level) > 5.) printf("WARNING: event %i has large weight_reco_level w = %f\n", ed->info.eventNumber, weight_reco_level);

    // Apply selections and fill control histograms (pt, eta, etc..)
    const bool passedRecoSelection     = PassedCutFlowReco( ed );
    const bool passedParticleSelection = isRealData ? false : PassedCutFlowParticle( ed );

   
    int Debug = 0;
    if (Debug) cout << "Passed Reco: " << passedRecoSelection << " Particle: " << passedParticleSelection << endl;

    if (!passedParticleSelection && !passedRecoSelection)
      return success;


    // Have fun with pseudo tops!

    if (Debug) cout << "  Here1" << endl;

    // yup, needs to be here:
    m_pseudotop_reco->SetEventData(ed);
    if( passedRecoSelection ) {
     
      m_pseudotop_reco->SetEventData(ed);
      m_pseudotop_reco->SetTarget(PseudoTopReconstruction::kReco);
      
      m_pseudotop_reco->SetChargedLepton(m_config->channel, 0);
      m_pseudotop_reco->Run();
      
      // dumped indices:
      // reco                : 0=t_lep 1=t_had 2=ttbar
      // truth (particle lvl): 3=t_lep 4=t_had 5=ttbar
      // truth (parton lvl)  : 6=t_lep 7=t_had 8=ttbar
      
      FillHistogramsPseudotopReco(ed, weight_reco_level);

      if (Debug) cout << "  Here2" << endl;

    } else {
      // due to pseudotop indices in ed:
      // reco: 0,1; particle is 2,3
      m_pseudotop_reco->MakeDummyPseudotops();
    }

    if( !isMCSignal)
      return success;

    // there is always a parton-level top
    if(passedRecoSelection) {

      // NOW: we should think whether we want to fill this only when passed reco, I'd think so? JK
      FillHistogramsPseudotopParton(ed, weight_particle_level);
      if (Debug) cout << "  Here3" << endl;

      // makes sense only when passed reco:
      FillHistogramsPseudotopResponseRecoToParton(ed, weight_reco_level);
      FillHistogramsMatchingRecoToParton(weight_reco_level);
      if (Debug) cout << "  Here4" << endl;

    }
    
    // nb: events could NOT pass the particle-level selection
    //     but you could still be able to reconstruct pseudotops (i.e. 1l4j2b)

    if (Debug) cout << "  Here4" << endl;

    if( !passedParticleSelection ) {
      // need to fill histograms binned in reco quantities,
      // standing for passed: reco!part
      // TODO!
      if(passedRecoSelection) {
	
      }
      return success;
      
    } else { // passed particle

      if (Debug) cout << "  Here5" << endl;

      m_pseudotop_particle->SetEventData(ed);
      m_pseudotop_particle->SetTarget(PseudoTopReconstruction::kTruth);
      m_pseudotop_particle->SetChargedLepton(m_config->channel, 0);

      if (Debug) {
	cout << "  Here6" << endl;
	cout << "    jet_n=" << ed->jets.n << " bjets_n=" << ed->bjets.n << endl;
	cout << "    truth_jet_n=" << ed->truth_jets.n << " truth_bjets_n=" << ed->truth_bjets.n << endl;
      }

      /*
	try {
        m_pseudotop_particle->Run();
	}
	catch( ... ) {
        cout << "WARNING: pseudotop reconstruction at particle level failed" << endl;
        cout << "  jet_n=" << ed->jets.n << " bjets_n=" << ed->bjets.n << endl;
	cout << "  truth_jet_n=" << ed->truth_jets.n << " truth_bjets_n=" << ed->truth_bjets.n << endl;
        return success;
	}
      */
      m_pseudotop_particle->Run();    
      if (Debug) cout << "  Here6.5" << endl;
      FillHistogramsPseudotopParticle(ed, weight_particle_level);
      if (Debug) cout << "  Here7" << endl;


      // if in addition passed also reco, we can fill response matrices:
      if(passedParticleSelection && passedRecoSelection) { // this is slightly over-ifed;-)

	if (Debug) cout << "  Here8" << endl;

      
	// rds:
	m_pseudotop_matching_reco2particle->SetEventData(ed);
	m_pseudotop_matching_reco2particle->DoMatching(0, 3, "pseudotop_lep");
	m_pseudotop_matching_reco2particle->DoMatching(1, 4, "pseudotop_had");
	m_pseudotop_matching_reco2particle->DoMatching(2, 5, "pseudottbar");
	if (Debug) cout << "  Here8.5" << endl;
	// matching:
	FillHistogramsMatchingRecoToParticle(weight_reco_level);
	FillHistogramsMatchingParticleToParton(weight_particle_level);

	// jk:
	bool passedDRMatching = m_pseudotop_matching_reco2particle->DoObjectsMatching(0); // 0 = no debug
	if (Debug) cout << "  Here9" << endl;


      if (Debug) cout << "  Here10" << endl;
	// fill response matrix:
	FillHistogramsPseudotopResponseRecoToParticle(ed, weight_reco_level); 
	FillHistogramsPseudotopResponseParticleToParton(ed, weight_particle_level);
      if (Debug) cout << "  Here11" << endl;


	// fill reco && particle for the denumerator of the f_'missassign':
	// TODO!

	// TODO! fill numerator for the matching eff (f_'missassign')
	// reco && particle && matched:
	if(passedDRMatching) {

	}

      } // passed particle and reco
    } // passed particle

    return success;
}


/////////////////////////////////////////

bool CutFlowTTbarResolved::PassedCutFlowReco(EventData * ed) {
    bool passed = true;

    int    jet_n  = ed->jets.n;
    int    bjet_n = ed->bjets.n;
    double ETmiss = ed->MET.et;
    double mwt    = ed->MET.mwt;
    
    const double weight = ed->property["weight_reco_level"];
 
    ControlPlotValues values;
    values.weight = weight;
    values.lep_pt  = ed->leptons.pT.at(0);
    values.lep_eta = ed->leptons.eta.at(0);
    values.lep_phi = ed->leptons.phi.at(0);
    values.lep_E   = ed->leptons.E.at(0);
    values.jet_n   = ed->jets.n;
    values.bjet_n  = ed->bjets.n; 
    values.fjet_n  = ed->fjets.n;
    values.ETmiss  = ed->MET.et;
    values.mwt     = ed->MET.mwt;
    for (int j = 0; j < ed->jets.n; ++j) {
        JetValues* jet = new JetValues();
        jet->pt  = ed->jets.pT.at(j);
        jet->eta = ed->jets.eta.at(j);
        jet->phi = ed->jets.phi.at(j);
        jet->E   = ed->jets.E.at(j);
        jet->m   = ed->jets.m.at(j);
        values.jets.push_back(jet);
    }
    for (int fj = 0; fj < ed->fjets.n; ++fj) {
        JetValues* jet = new JetValues();
        jet->pt  = ed->fjets.pT.at(fj);
        jet->eta = ed->fjets.eta.at(fj);
        jet->phi = ed->fjets.phi.at(fj);
        jet->E   = ed->fjets.E.at(fj);
        jet->m   = ed->fjets.m.at(fj);
        values.fatJets.push_back(jet);
    }   
    // 0 all events
    PassedCut( "LPLUSJETS", "reco_weighted", weight );
    PassedCut( "LPLUSJETS", "reco_unweight");
    FillHistogramsControlPlotsReco( values );
    
    // 1 Trigger
    PassedCut("LPLUSJETS", "reco_weighted", weight );
    PassedCut("LPLUSJETS", "reco_unweight");

    // 2 Prim. Vtx
    PassedCut("LPLUSJETS", "reco_weighted", weight );
    PassedCut("LPLUSJETS", "reco_unweight");

    // 3 SingleLepton
    PassedCut("LPLUSJETS", "reco_weighted", weight );
    PassedCut("LPLUSJETS", "reco_unweight");

    const double lep_pt = ( m_config->channel == kElectron ) ? ed->electrons.pT.at(0) : ed->muons.pT.at(0);

    // 4 lepton pT
    if (lep_pt < 25 * GeV) return !passed;
    PassedCut("LPLUSJETS", "reco_weighted", weight );
    PassedCut("LPLUSJETS", "reco_unweight");

    // 5 ETmiss > 30 GeV
    if (ETmiss < 30 * GeV) return !passed;
    PassedCut("LPLUSJETS", "reco_weighted", weight );
    PassedCut("LPLUSJETS", "reco_unweight");

    // 6 mTW > 35 GeV
    if (mwt < 35 * GeV) return !passed;
    PassedCut("LPLUSJETS", "reco_weighted", weight );
    PassedCut("LPLUSJETS", "reco_unweight");

    // 7 Njets >= 4    
    if ( jet_n < 4) return !passed;
    PassedCut("LPLUSJETS", "reco_weighted", weight );
    PassedCut("LPLUSJETS", "reco_unweight");

    // 8 Nbtags >= 1
    if (bjet_n < 1) return !passed;
    PassedCut("LPLUSJETS", "reco_weighted", weight );
    PassedCut("LPLUSJETS", "reco_unweight");

    FillHistogramsControlPlotsReco( values );

    // 9 Nbtags >= 2
    if (bjet_n < 2) return !passed;
    
    PassedCut("LPLUSJETS", "reco_weighted", weight );
    PassedCut("LPLUSJETS", "reco_unweight");

    FillHistogramsControlPlotsReco( values );

    return passed;
}

bool CutFlowTTbarResolved::PassedCutFlowParticle(EventData * ed) {    
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

void CutFlowTTbarResolved::FillHistogramsControlPlotsReco( ControlPlotValues& values )
{
    const int cut = GetLastPassedCut( "LPLUSJETS", "reco_weighted" ) - 1;    
    string path = "reco/cutflow/" + alias[cut] + "/";    
    FillHistograms(path, values);   
} 

void CutFlowTTbarResolved::FillHistogramsControlPlotsParticle( ControlPlotValues& values )
{    
    const int cut = GetLastPassedCut( "LPLUSJETS", "particle_weighted" ) -1;    
    string path = "parton/cutflow/" + alias[cut] + "/";
    FillHistograms(path, values);
}

void CutFlowTTbarResolved::FillHistograms(string path, ControlPlotValues& values ){
    m_hm->FillHistograms( path + "lep_pt" , values.lep_pt / GeV, values.weight );
    m_hm->FillHistograms( path + "lep_eta", values.lep_eta, values.weight);
    m_hm->FillHistograms( path + "lep_phi", values.lep_phi,      values.weight );
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



/////////////////////////////////////////
void CutFlowTTbarResolved::FillHistogramsPseudoTop(EventData::Reco_t& particle, int index, string level, string topType, const double weight, const double mbl){   
    Particle p(particle, index);
    m_hm->FillHistograms(level + "/4j2b/" + topType + "/pt", p.pt / GeV, weight);
    m_hm->FillHistograms(level + "/4j2b/" + topType + "/eta", p.eta, weight);
    m_hm->FillHistograms(level + "/4j2b/" + topType + "/phi", p.phi, weight);
    m_hm->FillHistograms(level + "/4j2b/" + topType + "/E", p.E / GeV, weight);
    m_hm->FillHistograms(level + "/4j2b/" + topType + "/m", p.m / GeV, weight);
    m_hm->FillHistograms(level + "/4j2b/" + topType + "/absrap", fabs(p.y), weight);

    if (index %3 == 0){
        m_hm->FillHistograms(level + "/4j2b/" + topType + "/mlb", mbl, weight );
    }
}

void CutFlowTTbarResolved::FillHistogramsPseudoTopTrue(EventData::Truth_t& particle, int index, string level, string topType, const double weight){   
    Particle p(particle, index);
    m_hm->FillHistograms(level + "/4j2b/" + topType + "/pt", p.pt / GeV, weight);
    m_hm->FillHistograms(level + "/4j2b/" + topType + "/eta", p.eta, weight);
    m_hm->FillHistograms(level + "/4j2b/" + topType + "/phi", p.phi, weight);
    m_hm->FillHistograms(level + "/4j2b/" + topType + "/E", p.E / GeV, weight);
    m_hm->FillHistograms(level + "/4j2b/" + topType + "/m", p.m / GeV, weight);
    m_hm->FillHistograms(level + "/4j2b/" + topType + "/absrap", fabs(p.y), weight);
}


void CutFlowTTbarResolved::FillHistogramsPseudotopReco( EventData * ed, const double weight) {
    TLorentzVector lep_bjet = HelperFunctions::MakeFourMomentum(ed->jets, ed->iproperty["reco_pseudotop_lep_bjet_index"]);
    TLorentzVector lep = HelperFunctions::MakeFourMomentum( ed->leptons, 0 );
    TLorentzVector lb = lep + lep_bjet;
    
    FillHistogramsPseudoTop(ed->reco, 0, "reco", "topL", weight, lb.M());
    FillHistogramsPseudoTop(ed->reco, 1, "reco", "topH", weight);
    FillHistogramsPseudoTop(ed->reco, 2, "reco", "tt", weight);
}


/////////////////////////////////////////

void CutFlowTTbarResolved::FillHistogramsPseudotopParticle( EventData * ed, const double weight) {


  if (ed->truth_leptons.n > 0) {
    TLorentzVector lep_bjet = HelperFunctions::MakeFourMomentum(ed->jets, ed->iproperty["ptcl_pseudotop_lep_bjet_index"]);
    TLorentzVector lep = HelperFunctions::MakeFourMomentum( ed->truth_leptons, 0 );
    TLorentzVector lb = lep + lep_bjet;
    FillHistogramsPseudoTop(ed->reco, 3, "particle", "topL", weight, lb.M());
  }

    FillHistogramsPseudoTop(ed->reco, 4, "particle", "topH", weight);
    FillHistogramsPseudoTop(ed->reco, 5, "particle", "tt", weight);
}


void CutFlowTTbarResolved::FillHistogramsPseudotopParton( EventData * ed, const double weight )
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
    
    FillHistogramsPseudoTopTrue(ed->mctruth, ilep, "parton", "topL", weight);
    FillHistogramsPseudoTopTrue(ed->mctruth, ihad, "parton", "topH", weight);
    FillHistogramsPseudoTopTrue(ed->mctruth, itt, "parton", "tt", weight);   
}

//////////////
// matching

void CutFlowTTbarResolved::FillHistogramsMatchingRecoToParticle( double weight )
{
   PhysicsHelperFunctions::PseudoTopMatching::MatchingResult pseudotop_lep = m_pseudotop_matching_reco2particle->GetResults( "pseudotop_lep" );
   
   m_hm->GetHistogram( "reco/matching/topL/delta_R" )->Fill(   pseudotop_lep.delta_R, weight );
   m_hm->GetHistogram( "reco/matching/topL/delta_pt" )->Fill(  pseudotop_lep.delta_pT / GeV, weight );
   m_hm->GetHistogram( "reco/matching/topL/delta_rapidity" )->Fill( pseudotop_lep.delta_rapidity, weight );
   m_hm->GetHistogram( "reco/matching/topL/delta_phi" )->Fill( pseudotop_lep.delta_phi, weight );
   m_hm->GetHistogram( "reco/matching/topL/delta_m" )->Fill(   pseudotop_lep.delta_m / GeV, weight );
   
   PhysicsHelperFunctions::PseudoTopMatching::MatchingResult pseudotop_had = m_pseudotop_matching_reco2particle->GetResults( "pseudotop_had" );
   
   m_hm->GetHistogram( "reco/matching/topH/delta_R" )->Fill(   pseudotop_had.delta_R, weight );
   m_hm->GetHistogram( "reco/matching/topH/delta_pt" )->Fill(  pseudotop_had.delta_pT / GeV, weight );
   m_hm->GetHistogram( "reco/matching/topH/delta_rapidity" )->Fill( pseudotop_had.delta_rapidity, weight );
   m_hm->GetHistogram( "reco/matching/topH/delta_phi" )->Fill( pseudotop_had.delta_phi, weight );
   m_hm->GetHistogram( "reco/matching/topH/delta_m" )->Fill(   pseudotop_had.delta_m / GeV, weight );
   
   PhysicsHelperFunctions::PseudoTopMatching::MatchingResult pseudottbar = m_pseudotop_matching_reco2particle->GetResults( "pseudottbar" );
   
   m_hm->GetHistogram( "reco/matching/topH/delta_R" )->Fill(   pseudottbar.delta_R, weight );
   m_hm->GetHistogram( "reco/matching/topH/delta_pt" )->Fill(  pseudottbar.delta_pT / GeV, weight );
   m_hm->GetHistogram( "reco/matching/topH/delta_rapidity" )->Fill( pseudottbar.delta_rapidity, weight );
   m_hm->GetHistogram( "reco/matching/topH/delta_phi" )->Fill( pseudottbar.delta_phi, weight );
   m_hm->GetHistogram( "reco/matching/topH/delta_m" )->Fill(   pseudottbar.delta_m / GeV, weight );
}

void CutFlowTTbarResolved::FillHistogramsMatchingRecoToParton( double weight )
{
      
}
  
 void CutFlowTTbarResolved::FillHistogramsMatchingParticleToParton( double weight )
 {
      
 }
  
 /////////////////////
 // response matrices
 
 void CutFlowTTbarResolved::FillHistogramsPseudotopResponseRecoToParticle(    EventData * ed, const double weight )
 {
    // reco level 
    Particle recoTopL(ed->reco, 0);
    Particle recoTopH(ed->reco, 1);
    Particle recoTT(ed->reco, 2);

    Particle particleTopL(ed->reco, 3);
    Particle particleTopH(ed->reco, 4);
    Particle particleTT(ed->reco, 5);

    FillMatrix("reco/4j2b/topL/Matrix_reco_particle", recoTopL, particleTopL, weight);
    FillMatrix("reco/4j2b/topH/Matrix_reco_particle", recoTopH, particleTopH, weight);
    FillMatrix("reco/4j2b/tt/Matrix_reco_particle", recoTT, particleTT, weight);     
    FillMatrix("particle/4j2b/topL/Matrix_particle_reco", particleTopL, recoTopL, weight);
    FillMatrix("particle/4j2b/topH/Matrix_particle_reco", particleTopH, recoTopH, weight);
    FillMatrix("particle/4j2b/tt/Matrix_particle_reco", particleTT, recoTT, weight);
 }
 
  void CutFlowTTbarResolved::FillMatrix(string path, Particle& py, Particle& px, double weight){
    m_hm->FillMatrices( path + "_pt", px.pt / GeV, py.pt / GeV, weight);
    m_hm->FillMatrices( path + "_eta", px.eta, py.eta, weight);
    m_hm->FillMatrices( path + "_phi", px.phi, py.phi, weight);
    m_hm->FillMatrices( path + "_m", px.m, py.m, weight);
    m_hm->FillMatrices( path + "_absrap", fabs(px.y), fabs(py.y), weight);
    m_hm->FillMatrices( path + "_E", px.E / GeV, py.E / GeV, weight);
  }
 
  void CutFlowTTbarResolved::FillHistogramsPseudotopResponseRecoToParton(      EventData * ed, const double weight )
  {
      // reco level 
     Particle recoTopL(ed->reco, 0);
     Particle recoTopH(ed->reco, 1);
     Particle recoTT(ed->reco, 2);

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
    
    //  reco > parton
     FillMatrix("reco/4j2b/topL/Matrix_reco_parton", recoTopL, partonTopL, weight);
     FillMatrix("reco/4j2b/topH/Matrix_reco_parton", recoTopH, partonTopH, weight);
     FillMatrix("reco/4j2b/tt/Matrix_reco_parton", recoTT, partonTT, weight);
     FillMatrix("parton/4j2b/topL/Matrix_parton_reco", partonTopL, recoTopL, weight);
     FillMatrix("parton/4j2b/topH/Matrix_parton_reco", partonTopH, recoTopH, weight);
     FillMatrix("parton/4j2b/tt/Matrix_parton_reco", partonTT, recoTT, weight);
  }
  
  void CutFlowTTbarResolved::FillHistogramsPseudotopResponseParticleToParton(  EventData * ed, const double weight )
  {
    // particle level
    Particle particleTopL(ed->reco, 3);
    Particle particleTopH(ed->reco, 4);
    Particle particleTT(ed->reco, 5);

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

    CutFlowPluginFactory_TTbarResolved * MakeCutFlowPlugin() {
        return new CutFlowPluginFactory_TTbarResolved("TTbarResolved");
    };
}

