#include "CutFlowTTbarResolved.h"

CutFlowTTbarResolved::CutFlowTTbarResolved() {
    m_pseudotop_reco = new PseudoTopReconstruction();
    m_pseudotop_particle = new PseudoTopReconstruction();
    
    m_pseudotop_matching_reco2particle   = new PseudoTopMatching( PseudoTopMatching::kRecoToParticle );
    m_pseudotop_matching_reco2parton     = new PseudoTopMatching( PseudoTopMatching::kRecoToParton );
    m_pseudotop_matching_particle2parton = new PseudoTopMatching( PseudoTopMatching::kParticleToParton );
}

CutFlowTTbarResolved::~CutFlowTTbarResolved() {
    delete m_pseudotop_reco;
    delete m_pseudotop_particle;
    
    delete m_pseudotop_matching_reco2particle;
    delete m_pseudotop_matching_reco2parton;
    delete m_pseudotop_matching_particle2parton;
}


/////////////////////////////////////////

bool CutFlowTTbarResolved::Initialize() {
    bool success = true;

    // AddChannel( "EL" );
    // AddCounter( "EL", "reco_weighted", 3 );
    // AddCounter( "EL", "reco_unweight", 3 );

    // SetCutName( "EL", "reco_weighted", 0, "AllEvents" );
    // SetCutName( "EL", "reco_weighted", 1, "Trigger" );
    // SetCutName( "EL", "reco_weighted", 2, "Prim. Vtx" );
    // SetCutName( "EL", "reco_weighted", 3, "single electron" );   

    AddChannel("COMBINED");
    AddCounterName("COMBINED", "reco_weighted", 9);
    AddCounterName("COMBINED", "reco_unweight", 9);
    AddCounterName("COMBINED", "particle_weighted", 9);
    AddCounterName("COMBINED", "particle_unweight", 9);

    SetCutName("COMBINED", "reco_weighted", 0, "All Events");
    SetCutName("COMBINED", "reco_weighted", 1, "Trigger");
    SetCutName("COMBINED", "reco_weighted", 2, "Prim. Vtx");
    SetCutName("COMBINED", "reco_weighted", 3, "SingleLepton");
    SetCutName("COMBINED", "reco_weighted", 4, "ETmiss > 30 GeV");
    SetCutName("COMBINED", "reco_weighted", 5, "mTW > 35 GeV");
    SetCutName("COMBINED", "reco_weighted", 6, "NJets >= 2");
    SetCutName("COMBINED", "reco_weighted", 7, "NJets >= 4");
    SetCutName("COMBINED", "reco_weighted", 8, "Nbtags >= 1");
    SetCutName("COMBINED", "reco_weighted", 9, "Nbtags >= 2");

    SetCutName("COMBINED", "reco_unweight", 0, "All Events");
    SetCutName("COMBINED", "reco_unweight", 1, "Trigger");
    SetCutName("COMBINED", "reco_unweight", 2, "Prim. Vtx");
    SetCutName("COMBINED", "reco_unweight", 3, "SingleLepton");
    SetCutName("COMBINED", "reco_unweight", 4, "ETmiss > 30 GeV");
    SetCutName("COMBINED", "reco_unweight", 5, "mTW > 35 GeV");
    SetCutName("COMBINED", "reco_unweight", 6, "NJets >= 2");
    SetCutName("COMBINED", "reco_unweight", 7, "NJets >= 4");
    SetCutName("COMBINED", "reco_unweight", 8, "Nbtags >= 1");
    SetCutName("COMBINED", "reco_unweight", 9, "Nbtags >= 2");
    
    SetCutName("COMBINED", "particle_weighted", 0, "All Events");
    SetCutName("COMBINED", "particle_weighted", 1, "Trigger");
    SetCutName("COMBINED", "particle_weighted", 2, "Prim. Vtx");
    SetCutName("COMBINED", "particle_weighted", 3, "SingleLepton");
    SetCutName("COMBINED", "particle_weighted", 4, "ETmiss > 30 GeV");
    SetCutName("COMBINED", "particle_weighted", 5, "mTW > 35 GeV");
    SetCutName("COMBINED", "particle_weighted", 6, "NJets >= 2");
    SetCutName("COMBINED", "particle_weighted", 7, "NJets >= 4");
    SetCutName("COMBINED", "particle_weighted", 8, "Nbtags >= 1");
    SetCutName("COMBINED", "particle_weighted", 9, "Nbtags >= 2");

    SetCutName("COMBINED", "particle_unweight", 0, "All Events");
    SetCutName("COMBINED", "particle_unweight", 1, "Trigger");
    SetCutName("COMBINED", "particle_unweight", 2, "Prim. Vtx");
    SetCutName("COMBINED", "particle_unweight", 3, "SingleLepton");
    SetCutName("COMBINED", "particle_unweight", 4, "ETmiss > 30 GeV");
    SetCutName("COMBINED", "particle_unweight", 5, "mTW > 35 GeV");
    SetCutName("COMBINED", "particle_unweight", 6, "NJets >= 2");
    SetCutName("COMBINED", "particle_unweight", 7, "NJets >= 4");
    SetCutName("COMBINED", "particle_unweight", 8, "Nbtags >= 1");
    SetCutName("COMBINED", "particle_unweight", 9, "Nbtags >= 2");

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

    int isMCSignal = (int) m_config->custom_params["isMCSignal"];
    int isRealData = (int) m_config->custom_params["isRealData"];

    double weight_reco_level     = 1.;
    double weight_particle_level = 1.;

    if( !isRealData ) {
   	 weight_reco_level     = ed->info.mcWeight;
         weight_particle_level = ed->info.mcWeight;

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

    if (fabs(weight_reco_level) > 5.) printf("WARNING: event %i has large weight_reco_level w = %f\n", ed->info.eventNumber, weight_reco_level);

    // Apply selections and fill control histograms (pt, eta, etc..)
    const bool passedRecoSelection     = PassedCutFlowReco( ed );
    const bool passedParticleSelection = PassedCutFlowParticle( ed );

    // Have fun with pseudo tops!

    if( !passedRecoSelection ) return success;

    m_pseudotop_reco->SetEventData(ed);
    m_pseudotop_reco->SetTarget(PseudoTopReconstruction::kReco);
    
    m_pseudotop_reco->SetChargedLepton(m_config->channel, 0);
    m_pseudotop_reco->Run();

    // dumped indices:
    // reco                : 0=t_lep 1=t_had 2=ttbar
    // truth (particle lvl): 3=t_lep 4=t_had 5=ttbar
    // truth (parton lvl)  : 6=t_lep 7=t_had 8=ttbar

    FillHistogramsPseudotopReco(ed, weight_reco_level);

    if( !isMCSignal) return success;
    
    // there is always a parton-level top
    FillHistogramsPseudotopParton(ed, weight_particle_level);
    FillHistogramsPseudotopResponseRecoToParton(ed, weight_reco_level);
    FillHistogramsMatchingRecoToParton(weight_reco_level);

    
    // nb: events could NOT pass the particle-level selection
    //     but you could still be able to reconstruct pseudotops (i.e. 1l4j2b)
    if( !passedParticleSelection ) return success;

    m_pseudotop_particle->SetEventData(ed);
    m_pseudotop_particle->SetTarget(PseudoTopReconstruction::kTruth);
    m_pseudotop_particle->SetChargedLepton(m_config->channel, 0);

    /*
    try {
        m_pseudotop_particle->Run();
    }
    catch( ... ) {
        cout << "WARNING: pseudotop reconstruction at particle level failed" << endl;
        cout << "jet_n=" << ed->jets.n << " bjets_n=" << ed->bjets.n << endl;
        return success;
    }
    */
    m_pseudotop_particle->Run();    

    FillHistogramsPseudotopParticle(ed, weight_particle_level);

    FillHistogramsPseudotopResponseRecoToParticle(ed, weight_reco_level);
    FillHistogramsPseudotopResponseParticleToParton(ed, weight_particle_level);

    m_pseudotop_matching_reco2particle->SetEventData(ed);
    m_pseudotop_matching_reco2particle->DoMatching(0, 3, "pseudotop_lep");
    m_pseudotop_matching_reco2particle->DoMatching(1, 4, "pseudotop_had");
    m_pseudotop_matching_reco2particle->DoMatching(2, 5, "pseudottbar");
    // jk:
    m_pseudotop_matching_reco2particle->DoObjectsMatching( 0 ); // debug

    FillHistogramsMatchingRecoToParticle(weight_reco_level);
    FillHistogramsMatchingParticleToParton(weight_particle_level);

    return success;
}


/////////////////////////////////////////

bool CutFlowTTbarResolved::PassedCutFlowReco(EventData * ed) {
    bool passed = true;

    int    jet_n  = ed->jets.n;
    int    bjet_n = ed->bjets.n;
    double ETmiss = ed->MET.et;
    double mwt    = ed->MET.mwt;
    double lep_pt = ed->lepton.pT;
    
    const double weight = ed->property["weight_reco_level"];
    
    
    // all events
    PassedCut( "COMBINED", "reco_weighted", weight );
    PassedCut( "COMBINED", "reco_unweight");
    FillHistogramsControlPlotsReco( ed, weight );
    
    // Trigger
    PassedCut("COMBINED", "reco_weighted", weight );
    PassedCut("COMBINED", "reco_unweight");

    // Prim. Vtx
    PassedCut("COMBINED", "reco_weighted", weight );
    PassedCut("COMBINED", "reco_unweight");

    // SingleLepton
    PassedCut("COMBINED", "reco_weighted", weight );
    PassedCut("COMBINED", "reco_unweight");

    // ETmiss > 30 GeV
    if (ETmiss < 30 * GeV) return !passed;

    PassedCut("COMBINED", "reco_weighted", weight );
    PassedCut("COMBINED", "reco_unweight");


    // mTW > 35 GeV
    if (mwt < 35 * GeV) return !passed;

    PassedCut("COMBINED", "reco_weighted", weight );
    PassedCut("COMBINED", "reco_unweight");
    
    if ( jet_n < 2) return !passed;
    PassedCut("COMBINED", "reco_weighted", weight );
    PassedCut("COMBINED", "reco_unweight");

    if ( jet_n < 4) return !passed;
    PassedCut("COMBINED", "reco_weighted", weight );
    PassedCut("COMBINED", "reco_unweight");

    // Nbtags >= 1
    if (bjet_n < 1) return !passed;

    PassedCut("COMBINED", "reco_weighted", weight );
    PassedCut("COMBINED", "reco_unweight");

    FillHistogramsControlPlotsReco( ed, weight );

    // Nbtags >= 2
    if (bjet_n < 2) return !passed;

    PassedCut("COMBINED", "reco_weighted", weight );
    PassedCut("COMBINED", "reco_unweight");

    FillHistogramsControlPlotsReco( ed, weight );


    return passed;
}

bool CutFlowTTbarResolved::PassedCutFlowParticle(EventData * ed) {
    bool passed = true;

    const double weight = ed->property["weight_particle_level"];
    
    const int    el_n  = ed->truth_electrons.n; 
    const int    mu_n  = ed->truth_muons.n; 
    const bool   single_lept = (el_n == 1)&&(mu_n==0) || (el_n == 0)&&(mu_n==1);
    const int    jet_n  = ed->truth_jets.n;
    const int    bjet_n = ed->truth_bjets.n;
    const double ETmiss = ed->MET_truth.et;
    const double mwt    = ed->MET_truth.mwt;
    const double lep_pt = ed->truth_lepton.pT;
    
    // All events
    PassedCut( "COMBINED", "particle_unweight" );
    PassedCut( "COMBINED", "particle_weighted", weight );
    FillHistogramsControlPlotsParticle( ed, weight );
    
    // trigger 
    PassedCut( "COMBINED", "particle_unweight" );
    PassedCut( "COMBINED", "particle_weighted", weight );
    
    // primary vertex
    PassedCut( "COMBINED", "particle_unweight" );
    PassedCut( "COMBINED", "particle_weighted", weight );
    
    // single lepton
    
    if( !single_lept )   return !passed;
    PassedCut( "COMBINED", "particle_unweight" );
    PassedCut( "COMBINED", "particle_weighted", weight );
    
    if (lep_pt < 25 * GeV) return !passed;
    PassedCut( "COMBINED", "particle_unweight" );
    PassedCut( "COMBINED", "particle_weighted", weight );
    
    if (ETmiss < 30 * GeV) return !passed;
    PassedCut( "COMBINED", "particle_unweight" );
    PassedCut( "COMBINED", "particle_weighted", weight );
    
    if (mwt < 35 * GeV)    return !passed;
    PassedCut( "COMBINED", "particle_unweight" );
    PassedCut( "COMBINED", "particle_weighted", weight );
    
    if (jet_n < 2 )         return !passed;
    PassedCut( "COMBINED", "particle_unweight" );
    PassedCut( "COMBINED", "particle_weighted", weight );
    
    if (jet_n < 4)         return !passed;
    PassedCut( "COMBINED", "particle_unweight" );
    PassedCut( "COMBINED", "particle_weighted", weight );
    
    if (bjet_n < 2)        return !passed; 
    PassedCut( "COMBINED", "particle_unweight" );
    PassedCut( "COMBINED", "particle_weighted", weight );
    
    FillHistogramsControlPlotsParticle( ed, weight );
    
    return passed;
}


/////////////////////////////////////////

void CutFlowTTbarResolved::FillHistogramsControlPlotsReco( EventData * ed, const double weight )
{
    const int cut = GetLastPassedCut( "COMBINED", "reco_weighted" ) - 1;
    static string pattern = "@CUT@";
    
    static string alias[10] = {
        "c0", "trig", "pvtx", "lept", "met30", "mtw35", "2j", "4j", "4j1b", "4j2b"
    };
    
    double lep_pt  = ed->lepton.pT;
    double lep_eta = ed->lepton.eta;
    double lep_phi = ed->lepton.phi;
    double lep_E   = ed->lepton.E;
    //double lep_q   = ed->lepton.q;
    int    jet_n   = ed->jets.n;
    int    bjet_n  = ed->bjets.n; 
    int    fjet_n  = ed->fjets.n;
    double ETmiss  = ed->MET.et;
    double mwt     = ed->MET.mwt;
    
    m_hm->GetHistogram( HelperFunctions::Replace("reco/reco_@CUT@_lep_eta", pattern, alias[cut]) )->Fill( lep_eta,      weight );
    m_hm->GetHistogram( HelperFunctions::Replace("reco/reco_@CUT@_lep_pt",  pattern, alias[cut]) )->Fill( lep_pt / GeV, weight );
    m_hm->GetHistogram( HelperFunctions::Replace("reco/reco_@CUT@_lep_phi", pattern, alias[cut]) )->Fill( lep_phi,      weight );
    m_hm->GetHistogram( HelperFunctions::Replace("reco/reco_@CUT@_lep_E",   pattern, alias[cut]) )->Fill( lep_E / GeV,  weight );
    
    m_hm->GetHistogram( HelperFunctions::Replace("reco/reco_@CUT@_met_pt", pattern, alias[cut]) )->Fill( ETmiss / GeV, weight );
    m_hm->GetHistogram( HelperFunctions::Replace("reco/reco_@CUT@_mtw", pattern, alias[cut]) )->Fill( mwt  / GeV, weight );
    

    m_hm->GetHistogram( HelperFunctions::Replace("reco/reco_@CUT@_jet_n", pattern, alias[cut]) )->Fill( jet_n, weight );
    for (int j = 0; j < jet_n; ++j) {
        double jet_pt  = ed->jets.pT.at(j);
        double jet_eta = ed->jets.eta.at(j);
        double jet_phi = ed->jets.phi.at(j);
        double jet_E   = ed->jets.E.at(j);
        double jet_m   = ed->jets.m.at(j);

        m_hm->GetHistogram( HelperFunctions::Replace("reco/reco_@CUT@_jet_eta", pattern, alias[cut]) )->Fill( jet_eta, weight );
        m_hm->GetHistogram( HelperFunctions::Replace("reco/reco_@CUT@_jet_pt",  pattern, alias[cut]) )->Fill( jet_pt / GeV, weight );
        m_hm->GetHistogram( HelperFunctions::Replace("reco/reco_@CUT@_jet_phi", pattern, alias[cut]) )->Fill( jet_phi, weight );
        m_hm->GetHistogram( HelperFunctions::Replace("reco/reco_@CUT@_jet_E",   pattern, alias[cut]) )->Fill( jet_E / GeV, weight );
        m_hm->GetHistogram( HelperFunctions::Replace("reco/reco_@CUT@_jet_m",   pattern, alias[cut]) )->Fill( jet_m / GeV, weight );
    }

    m_hm->GetHistogram( HelperFunctions::Replace("reco/reco_@CUT@_fjet_n", pattern, alias[cut]) )->Fill( fjet_n, weight );
    for (int j = 0; j < fjet_n; ++j) {
        double fjet_pt  = ed->fjets.pT.at(j);
        double fjet_eta = ed->fjets.eta.at(j);
        double fjet_phi = ed->fjets.phi.at(j);
        double fjet_E   = ed->fjets.E.at(j);
        double fjet_m   = ed->fjets.m.at(j);

        m_hm->GetHistogram( HelperFunctions::Replace("reco/reco_@CUT@_fjet_eta", pattern, alias[cut]) )->Fill( fjet_eta, weight );
        m_hm->GetHistogram( HelperFunctions::Replace("reco/reco_@CUT@_fjet_pt",  pattern, alias[cut]) )->Fill( fjet_pt / GeV, weight );
        m_hm->GetHistogram( HelperFunctions::Replace("reco/reco_@CUT@_fjet_phi", pattern, alias[cut]) )->Fill( fjet_phi, weight );
        m_hm->GetHistogram( HelperFunctions::Replace("reco/reco_@CUT@_fjet_E",   pattern, alias[cut]) )->Fill( fjet_E / GeV, weight );
        m_hm->GetHistogram( HelperFunctions::Replace("reco/reco_@CUT@_fjet_m",   pattern, alias[cut]) )->Fill( fjet_m / GeV, weight );
    }

   
} 


/////////////////////////////////////////


void CutFlowTTbarResolved::FillHistogramsControlPlotsParticle( EventData * ed, const double weight )
{
    static string pattern = "@CUT@";
    
    static string alias[10] = {
        "c0", "trig", "pvtx", "lept", "met30", "mtw35", "2j", "4j", "4j1b", "4j2b"
    };
    
    const int cut = GetLastPassedCut( "COMBINED", "particle_weighted" ) - 1;
    
    double lep_pt  = ed->truth_lepton.pT;
    double lep_eta = ed->truth_lepton.eta;
    double lep_phi = ed->truth_lepton.phi;
    double lep_E   = ed->truth_lepton.E;
    double lep_q   = ed->truth_lepton.q;
    int    jet_n   = ed->truth_jets.n;
    int    bjet_n  = ed->truth_bjets.n;
    double ETmiss  = ed->MET_truth.et;
    double mwt     = ed->MET_truth.mwt;
    
    m_hm->GetHistogram( HelperFunctions::Replace("particle/particle_@CUT@_lep_eta", pattern, alias[cut]) )->Fill( lep_eta, weight );
    m_hm->GetHistogram( HelperFunctions::Replace("particle/particle_@CUT@_lep_pt",  pattern, alias[cut]) )->Fill( lep_pt / GeV, weight );
    m_hm->GetHistogram( HelperFunctions::Replace("particle/particle_@CUT@_lep_phi", pattern, alias[cut]) )->Fill( lep_phi, weight );
    m_hm->GetHistogram( HelperFunctions::Replace("particle/particle_@CUT@_lep_E",   pattern, alias[cut]) )->Fill( lep_E / GeV, weight );
    
    m_hm->GetHistogram( HelperFunctions::Replace("particle/particle_@CUT@_met_pt",  pattern, alias[cut]) )->Fill( ETmiss / GeV, weight );
    m_hm->GetHistogram( HelperFunctions::Replace("particle/particle_@CUT@_mtw",     pattern, alias[cut]) )->Fill( mwt  / GeV, weight );
    

    m_hm->GetHistogram( HelperFunctions::Replace("particle/particle_@CUT@_jet_n",   pattern, alias[cut]) )->Fill( jet_n, weight );
    
    for (int j = 0; j < jet_n; ++j) {
        double jet_pt  = ed->truth_jets.pT.at(j);
        double jet_eta = ed->truth_jets.eta.at(j);
        double jet_phi = ed->truth_jets.phi.at(j);
        double jet_E   = ed->truth_jets.E.at(j);
        double jet_m   = ed->truth_jets.m.at(j);

        m_hm->GetHistogram( HelperFunctions::Replace("particle/particle_@CUT@_jet_eta", pattern, alias[cut]) )->Fill( jet_eta, weight );
        m_hm->GetHistogram( HelperFunctions::Replace("particle/particle_@CUT@_jet_pt",  pattern, alias[cut]) )->Fill( jet_pt / GeV, weight );
        m_hm->GetHistogram( HelperFunctions::Replace("particle/particle_@CUT@_jet_phi", pattern, alias[cut]) )->Fill( jet_phi, weight );
        m_hm->GetHistogram( HelperFunctions::Replace("particle/particle_@CUT@_jet_E",   pattern, alias[cut]) )->Fill( jet_E / GeV, weight );
        m_hm->GetHistogram( HelperFunctions::Replace("particle/particle_@CUT@_jet_m",   pattern, alias[cut]) )->Fill( jet_m / GeV, weight );
    }
}


/////////////////////////////////////////


void CutFlowTTbarResolved::FillHistogramsPseudotopReco( EventData * ed, const double weight) {
    const double top_lep_pt = ed->reco.pT.at(0);
    const double top_lep_eta = ed->reco.eta.at(0);
    const double top_lep_phi = ed->reco.phi.at(0);
    const double top_lep_E = ed->reco.E.at(0);
    const double top_lep_m = ed->reco.m.at(0);
    const double top_lep_y = PhysicsHelperFunctions::Rapidity(ed->reco, 0);

    const double top_had_pt = ed->reco.pT.at(1);
    const double top_had_eta = ed->reco.eta.at(1);
    const double top_had_phi = ed->reco.phi.at(1);
    const double top_had_E = ed->reco.E.at(1);
    const double top_had_m = ed->reco.m.at(1);
    const double top_had_y = PhysicsHelperFunctions::Rapidity(ed->reco, 1);

    const double ttbar_pt = ed->reco.pT.at(2);
    const double ttbar_eta = ed->reco.eta.at(2);
    const double ttbar_phi = ed->reco.phi.at(2);
    const double ttbar_E = ed->reco.E.at(2);
    const double ttbar_m = ed->reco.m.at(2);
    const double ttbar_y = PhysicsHelperFunctions::Rapidity(ed->reco, 2);

    m_hm->GetHistogram("reco/reco_4j2b_pseudotop_reco_lep_pt")->Fill(top_lep_pt / GeV, weight);
    m_hm->GetHistogram("reco/reco_4j2b_pseudotop_reco_lep_eta")->Fill(top_lep_eta, weight);
    m_hm->GetHistogram("reco/reco_4j2b_pseudotop_reco_lep_phi")->Fill(top_lep_phi, weight);
    m_hm->GetHistogram("reco/reco_4j2b_pseudotop_reco_lep_E")->Fill(top_lep_E / GeV, weight);
    m_hm->GetHistogram("reco/reco_4j2b_pseudotop_reco_lep_m")->Fill(top_lep_m / GeV, weight);
    m_hm->GetHistogram("reco/reco_4j2b_pseudotop_reco_lep_absrap")->Fill(fabs(top_lep_y), weight);

    m_hm->GetHistogram("reco/reco_4j2b_pseudotop_reco_had_pt")->Fill(top_had_pt / GeV, weight);
    m_hm->GetHistogram("reco/reco_4j2b_pseudotop_reco_had_eta")->Fill(top_had_eta, weight);
    m_hm->GetHistogram("reco/reco_4j2b_pseudotop_reco_had_phi")->Fill(top_had_phi, weight);
    m_hm->GetHistogram("reco/reco_4j2b_pseudotop_reco_had_E")->Fill(top_had_E / GeV, weight);
    m_hm->GetHistogram("reco/reco_4j2b_pseudotop_reco_had_m")->Fill(top_had_m / GeV, weight);
    m_hm->GetHistogram("reco/reco_4j2b_pseudotop_reco_had_absrap")->Fill(fabs(top_had_y), weight);

    m_hm->GetHistogram("reco/reco_4j2b_pseudottbar_reco_pt")->Fill(ttbar_pt / GeV, weight);
    m_hm->GetHistogram("reco/reco_4j2b_pseudottbar_reco_eta")->Fill(ttbar_eta, weight);
    m_hm->GetHistogram("reco/reco_4j2b_pseudottbar_reco_phi")->Fill(ttbar_phi, weight);
    m_hm->GetHistogram("reco/reco_4j2b_pseudottbar_reco_E")->Fill(ttbar_E / GeV, weight);
    m_hm->GetHistogram("reco/reco_4j2b_pseudottbar_reco_m")->Fill(ttbar_m / GeV, weight);
    m_hm->GetHistogram("reco/reco_4j2b_pseudottbar_reco_absrap")->Fill(fabs(ttbar_y), weight);
}


/////////////////////////////////////////

void CutFlowTTbarResolved::FillHistogramsPseudotopParticle( EventData * ed, const double weight) {
    const double top_lep_pt = ed->reco.pT.at(3);
    const double top_lep_eta = ed->reco.eta.at(3);
    const double top_lep_phi = ed->reco.phi.at(3);
    const double top_lep_E = ed->reco.E.at(3);
    const double top_lep_m = ed->reco.m.at(3);
    const double top_lep_y = PhysicsHelperFunctions::Rapidity(ed->reco, 3);

    const double top_had_pt = ed->reco.pT.at(4);
    const double top_had_eta = ed->reco.eta.at(4);
    const double top_had_phi = ed->reco.phi.at(4);
    const double top_had_E = ed->reco.E.at(4);
    const double top_had_m = ed->reco.m.at(4);
    const double top_had_y = PhysicsHelperFunctions::Rapidity(ed->reco, 4);

    const double ttbar_pt = ed->reco.pT.at(5);
    const double ttbar_eta = ed->reco.eta.at(5);
    const double ttbar_phi = ed->reco.phi.at(5);
    const double ttbar_E = ed->reco.E.at(5);
    const double ttbar_m = ed->reco.m.at(5);
    const double ttbar_y = PhysicsHelperFunctions::Rapidity(ed->reco, 5);

    m_hm->GetHistogram("particle/particle_4j2b_pseudotop_lep_pt")->Fill(top_lep_pt / GeV, weight);
    m_hm->GetHistogram("particle/particle_4j2b_pseudotop_lep_eta")->Fill(top_lep_eta, weight);
    m_hm->GetHistogram("particle/particle_4j2b_pseudotop_lep_phi")->Fill(top_lep_phi, weight);
    m_hm->GetHistogram("particle/particle_4j2b_pseudotop_lep_E")->Fill(top_lep_E / GeV, weight);
    m_hm->GetHistogram("particle/particle_4j2b_pseudotop_lep_m")->Fill(top_lep_m / GeV, weight);
    m_hm->GetHistogram("particle/particle_4j2b_pseudotop_lep_absrap")->Fill(fabs(top_lep_y), weight);

    m_hm->GetHistogram("particle/particle_4j2b_pseudotop_had_pt")->Fill(top_had_pt / GeV, weight);
    m_hm->GetHistogram("particle/particle_4j2b_pseudotop_had_eta")->Fill(top_had_eta, weight);
    m_hm->GetHistogram("particle/particle_4j2b_pseudotop_had_phi")->Fill(top_had_phi, weight);
    m_hm->GetHistogram("particle/particle_4j2b_pseudotop_had_E")->Fill(top_had_E / GeV, weight);
    m_hm->GetHistogram("particle/particle_4j2b_pseudotop_had_m")->Fill(top_had_m / GeV, weight);
    m_hm->GetHistogram("particle/particle_4j2b_pseudotop_had_absrap")->Fill(fabs(top_had_y), weight);

    m_hm->GetHistogram("particle/particle_4j2b_pseudottbar_pt")->Fill(ttbar_pt / GeV, weight);
    m_hm->GetHistogram("particle/particle_4j2b_pseudottbar_eta")->Fill(ttbar_eta, weight);
    m_hm->GetHistogram("particle/particle_4j2b_pseudottbar_phi")->Fill(ttbar_phi, weight);
    m_hm->GetHistogram("particle/particle_4j2b_pseudottbar_E")->Fill(ttbar_E / GeV, weight);
    m_hm->GetHistogram("particle/particle_4j2b_pseudottbar_m")->Fill(ttbar_m / GeV, weight);
    m_hm->GetHistogram("particle/particle_4j2b_pseudottbar_absrap")->Fill(fabs(ttbar_y), weight);
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
    
    const double parton_top_lep_pt = ed->mctruth.pT.at(ilep);
    const double parton_top_lep_eta = ed->mctruth.eta.at(ilep);
    const double parton_top_lep_phi = ed->mctruth.phi.at(ilep);
    const double parton_top_lep_E = ed->mctruth.E.at(ilep);
    const double parton_top_lep_y = PhysicsHelperFunctions::Rapidity(ed->mctruth, ilep);

    const double parton_top_had_pt = ed->mctruth.pT.at(ihad);
    const double parton_top_had_eta = ed->mctruth.eta.at(ihad);
    const double parton_top_had_phi = ed->mctruth.phi.at(ihad);
    const double parton_top_had_E = ed->mctruth.E.at(ihad);
    const double parton_top_had_y = PhysicsHelperFunctions::Rapidity(ed->mctruth, ihad);

    const double parton_ttbar_pt = ed->mctruth.pT.at(itt);
    const double parton_ttbar_eta = ed->mctruth.eta.at(itt);
    const double parton_ttbar_phi = ed->mctruth.phi.at(itt);
    const double parton_ttbar_E = ed->mctruth.E.at(itt);
    const double parton_ttbar_m = ed->mctruth.m.at(itt);
    const double parton_ttbar_y = PhysicsHelperFunctions::Rapidity(ed->mctruth, itt);

    m_hm->GetHistogram("parton/parton_4j2b_pseudotop_lep_pt")->Fill(parton_top_lep_pt / GeV, weight);
    m_hm->GetHistogram("parton/parton_4j2b_pseudotop_lep_eta")->Fill(parton_top_lep_eta, weight);
    m_hm->GetHistogram("parton/parton_4j2b_pseudotop_lep_phi")->Fill(parton_top_lep_phi, weight);
    m_hm->GetHistogram("parton/parton_4j2b_pseudotop_lep_E")->Fill(parton_top_lep_E / GeV, weight);
    m_hm->GetHistogram("parton/parton_4j2b_pseudotop_lep_absrap")->Fill(fabs(parton_top_lep_y), weight);

    m_hm->GetHistogram("parton/parton_4j2b_pseudotop_had_pt")->Fill(parton_top_had_pt / GeV, weight);
    m_hm->GetHistogram("parton/parton_4j2b_pseudotop_had_eta")->Fill(parton_top_had_eta, weight);
    m_hm->GetHistogram("parton/parton_4j2b_pseudotop_had_phi")->Fill(parton_top_had_phi, weight);
    m_hm->GetHistogram("parton/parton_4j2b_pseudotop_had_E")->Fill(parton_top_had_E / GeV, weight);
    m_hm->GetHistogram("parton/parton_4j2b_pseudotop_had_absrap")->Fill(fabs(parton_top_had_y), weight);

    m_hm->GetHistogram("parton/parton_4j2b_pseudottbar_pt")->Fill(parton_ttbar_pt / GeV, weight);
    m_hm->GetHistogram("parton/parton_4j2b_pseudottbar_eta")->Fill(parton_ttbar_eta, weight);
    m_hm->GetHistogram("parton/parton_4j2b_pseudottbar_phi")->Fill(parton_ttbar_phi, weight);
    m_hm->GetHistogram("parton/parton_4j2b_pseudottbar_E")->Fill(parton_ttbar_E / GeV, weight);
    m_hm->GetHistogram("parton/parton_4j2b_pseudottbar_m")->Fill(parton_ttbar_m / GeV, weight);
    m_hm->GetHistogram("parton/parton_4j2b_pseudottbar_absrap")->Fill(fabs(parton_ttbar_y), weight);

}

//////////////
// matching

void CutFlowTTbarResolved::FillHistogramsMatchingRecoToParticle( double weight )
{
   PhysicsHelperFunctions::PseudoTopMatching::MatchingResult pseudotop_lep = m_pseudotop_matching_reco2particle->GetResults( "pseudotop_lep" );
   
   m_hm->GetHistogram( "matching/matching_reco2particle_4j2b_pseudotop_lep_delta_R" )->Fill(   pseudotop_lep.delta_R, weight );
   m_hm->GetHistogram( "matching/matching_reco2particle_4j2b_pseudotop_lep_delta_pt" )->Fill(  pseudotop_lep.delta_pT / GeV, weight );
   m_hm->GetHistogram( "matching/matching_reco2particle_4j2b_pseudotop_lep_delta_rapidity" )->Fill( pseudotop_lep.delta_rapidity, weight );
   m_hm->GetHistogram( "matching/matching_reco2particle_4j2b_pseudotop_lep_delta_phi" )->Fill( pseudotop_lep.delta_phi, weight );
   m_hm->GetHistogram( "matching/matching_reco2particle_4j2b_pseudotop_lep_delta_m" )->Fill(   pseudotop_lep.delta_m / GeV, weight );
   
   PhysicsHelperFunctions::PseudoTopMatching::MatchingResult pseudotop_had = m_pseudotop_matching_reco2particle->GetResults( "pseudotop_had" );
   
   m_hm->GetHistogram( "matching/matching_reco2particle_4j2b_pseudotop_had_delta_R" )->Fill(   pseudotop_had.delta_R, weight );
   m_hm->GetHistogram( "matching/matching_reco2particle_4j2b_pseudotop_had_delta_pt" )->Fill(  pseudotop_had.delta_pT / GeV, weight );
   m_hm->GetHistogram( "matching/matching_reco2particle_4j2b_pseudotop_had_delta_rapidity" )->Fill( pseudotop_had.delta_rapidity, weight );
   m_hm->GetHistogram( "matching/matching_reco2particle_4j2b_pseudotop_had_delta_phi" )->Fill( pseudotop_had.delta_phi, weight );
   m_hm->GetHistogram( "matching/matching_reco2particle_4j2b_pseudotop_had_delta_m" )->Fill(   pseudotop_had.delta_m / GeV, weight );
   
   PhysicsHelperFunctions::PseudoTopMatching::MatchingResult pseudottbar = m_pseudotop_matching_reco2particle->GetResults( "pseudottbar" );
   
   m_hm->GetHistogram( "matching/matching_reco2particle_4j2b_pseudottbar_delta_R" )->Fill(   pseudottbar.delta_R, weight );
   m_hm->GetHistogram( "matching/matching_reco2particle_4j2b_pseudottbar_delta_pt" )->Fill(  pseudottbar.delta_pT / GeV, weight );
   m_hm->GetHistogram( "matching/matching_reco2particle_4j2b_pseudottbar_delta_rapidity" )->Fill( pseudottbar.delta_rapidity, weight );
   m_hm->GetHistogram( "matching/matching_reco2particle_4j2b_pseudottbar_delta_phi" )->Fill( pseudottbar.delta_phi, weight );
   m_hm->GetHistogram( "matching/matching_reco2particle_4j2b_pseudottbar_delta_m" )->Fill(   pseudottbar.delta_m / GeV, weight );
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
    const double reco_top_lep_pt = ed->reco.pT.at(0);
    const double reco_top_lep_eta = ed->reco.eta.at(0);
    const double reco_top_lep_phi = ed->reco.phi.at(0);
    const double reco_top_lep_E = ed->reco.E.at(0);
    const double reco_top_lep_y = PhysicsHelperFunctions::Rapidity(ed->reco, 0);

    const double reco_top_had_pt = ed->reco.pT.at(1);
    const double reco_top_had_eta = ed->reco.eta.at(1);
    const double reco_top_had_phi = ed->reco.phi.at(1);
    const double reco_top_had_E = ed->reco.E.at(1);
    const double reco_top_had_y = PhysicsHelperFunctions::Rapidity(ed->reco, 1);

    const double reco_ttbar_pt = ed->reco.pT.at(2);
    const double reco_ttbar_eta = ed->reco.eta.at(2);
    const double reco_ttbar_phi = ed->reco.phi.at(2);
    const double reco_ttbar_E = ed->reco.E.at(2);
    const double reco_ttbar_m = ed->reco.m.at(2);
    const double reco_ttbar_y = PhysicsHelperFunctions::Rapidity(ed->reco, 2);

    // particle level
    const double particle_top_lep_pt = ed->reco.pT.at(3);
    const double particle_top_lep_eta = ed->reco.eta.at(3);
    const double particle_top_lep_phi = ed->reco.phi.at(3);
    const double particle_top_lep_E = ed->reco.E.at(3);
    const double particle_top_lep_y = PhysicsHelperFunctions::Rapidity(ed->reco, 3);

    const double particle_top_had_pt = ed->reco.pT.at(4);
    const double particle_top_had_eta = ed->reco.eta.at(4);
    const double particle_top_had_phi = ed->reco.phi.at(4);
    const double particle_top_had_E = ed->reco.E.at(4);
    const double particle_top_had_y = PhysicsHelperFunctions::Rapidity(ed->reco, 4);

    const double particle_ttbar_pt = ed->reco.pT.at(5);
    const double particle_ttbar_eta = ed->reco.eta.at(5);
    const double particle_ttbar_phi = ed->reco.phi.at(5);
    const double particle_ttbar_E = ed->reco.E.at(5);
    const double particle_ttbar_m = ed->reco.m.at(5);
    const double particle_ttbar_y = PhysicsHelperFunctions::Rapidity(ed->reco, 5);
    
    //  reco > particle
    m_hm->Get2DHistogram("response/response_reco2particle_4j2b_pseudotop_lep_pt")->Fill(     particle_top_lep_pt / GeV,  reco_top_lep_pt / GeV, weight);
    m_hm->Get2DHistogram("response/response_reco2particle_4j2b_pseudotop_lep_eta")->Fill(    particle_top_lep_eta,       reco_top_lep_eta, weight);
    m_hm->Get2DHistogram("response/response_reco2particle_4j2b_pseudotop_lep_phi")->Fill(    particle_top_lep_phi,       reco_top_lep_phi, weight);
    m_hm->Get2DHistogram("response/response_reco2particle_4j2b_pseudotop_lep_E")->Fill(      particle_top_lep_E / GeV,   reco_top_lep_E / GeV, weight);
    m_hm->Get2DHistogram("response/response_reco2particle_4j2b_pseudotop_lep_absrap")->Fill( fabs(particle_top_lep_y),   fabs(reco_top_lep_y), weight);

    m_hm->Get2DHistogram("response/response_reco2particle_4j2b_pseudotop_had_pt")->Fill(      particle_top_had_pt / GeV, reco_top_had_pt / GeV, weight);
    m_hm->Get2DHistogram("response/response_reco2particle_4j2b_pseudotop_had_eta")->Fill(     particle_top_had_eta,      reco_top_had_eta, weight);
    m_hm->Get2DHistogram("response/response_reco2particle_4j2b_pseudotop_had_phi")->Fill(     particle_top_had_phi,      reco_top_had_phi, weight);
    m_hm->Get2DHistogram("response/response_reco2particle_4j2b_pseudotop_had_E")->Fill(       particle_top_had_E / GeV,  reco_top_had_E / GeV, weight);
    m_hm->Get2DHistogram("response/response_reco2particle_4j2b_pseudotop_had_absrap")->Fill(  fabs(particle_top_had_y),  fabs(reco_top_had_y), weight);

    m_hm->Get2DHistogram("response/response_reco2particle_4j2b_pseudottbar_pt")->Fill(        particle_ttbar_pt / GeV,   reco_ttbar_pt / GeV, weight);
    m_hm->Get2DHistogram("response/response_reco2particle_4j2b_pseudottbar_eta")->Fill(       particle_ttbar_eta,        reco_ttbar_eta, weight);
    m_hm->Get2DHistogram("response/response_reco2particle_4j2b_pseudottbar_phi")->Fill(       particle_ttbar_phi,        reco_ttbar_phi, weight);
    m_hm->Get2DHistogram("response/response_reco2particle_4j2b_pseudottbar_E")->Fill(         particle_ttbar_E / GeV,    reco_ttbar_E / GeV, weight);
    m_hm->Get2DHistogram("response/response_reco2particle_4j2b_pseudottbar_m")->Fill(         particle_ttbar_m / GeV,    reco_ttbar_m / GeV, weight);
    m_hm->Get2DHistogram("response/response_reco2particle_4j2b_pseudottbar_absrap")->Fill(     fabs(particle_ttbar_y),   fabs(reco_ttbar_y), weight);
 }
 
  void CutFlowTTbarResolved::FillHistogramsPseudotopResponseRecoToParton(      EventData * ed, const double weight )
  {
      // reco level 
    const double reco_top_lep_pt = ed->reco.pT.at(0);
    const double reco_top_lep_eta = ed->reco.eta.at(0);
    const double reco_top_lep_phi = ed->reco.phi.at(0);
    const double reco_top_lep_E = ed->reco.E.at(0);
    const double reco_top_lep_y = PhysicsHelperFunctions::Rapidity(ed->reco, 0);

    const double reco_top_had_pt = ed->reco.pT.at(1);
    const double reco_top_had_eta = ed->reco.eta.at(1);
    const double reco_top_had_phi = ed->reco.phi.at(1);
    const double reco_top_had_E = ed->reco.E.at(1);
    const double reco_top_had_y = PhysicsHelperFunctions::Rapidity(ed->reco, 1);

    const double reco_ttbar_pt = ed->reco.pT.at(2);
    const double reco_ttbar_eta = ed->reco.eta.at(2);
    const double reco_ttbar_phi = ed->reco.phi.at(2);
    const double reco_ttbar_E = ed->reco.E.at(2);
    const double reco_ttbar_m = ed->reco.m.at(2);
    const double reco_ttbar_y = PhysicsHelperFunctions::Rapidity(ed->reco, 2);

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
    
    const double parton_top_lep_pt = ed->mctruth.pT.at(ilep);
    const double parton_top_lep_eta = ed->mctruth.eta.at(ilep);
    const double parton_top_lep_phi = ed->mctruth.phi.at(ilep);
    const double parton_top_lep_E = ed->mctruth.E.at(ilep);
    const double parton_top_lep_y = PhysicsHelperFunctions::Rapidity(ed->mctruth, ilep);

    const double parton_top_had_pt = ed->mctruth.pT.at(ihad);
    const double parton_top_had_eta = ed->mctruth.eta.at(ihad);
    const double parton_top_had_phi = ed->mctruth.phi.at(ihad);
    const double parton_top_had_E = ed->mctruth.E.at(ihad);
    const double parton_top_had_y = PhysicsHelperFunctions::Rapidity(ed->mctruth, ihad);

    const double parton_ttbar_pt = ed->mctruth.pT.at(itt);
    const double parton_ttbar_eta = ed->mctruth.eta.at(itt);
    const double parton_ttbar_phi = ed->mctruth.phi.at(itt);
    const double parton_ttbar_E = ed->mctruth.E.at(itt);
    const double parton_ttbar_m = ed->mctruth.m.at(itt);
    const double parton_ttbar_y = PhysicsHelperFunctions::Rapidity(ed->mctruth, itt);
    
    //  reco > parton
    m_hm->Get2DHistogram("response/response_reco2parton_4j2b_pseudotop_lep_pt")->Fill(     parton_top_lep_pt / GeV,  reco_top_lep_pt / GeV, weight);
    m_hm->Get2DHistogram("response/response_reco2parton_4j2b_pseudotop_lep_eta")->Fill(    parton_top_lep_eta,       reco_top_lep_eta, weight);
    m_hm->Get2DHistogram("response/response_reco2parton_4j2b_pseudotop_lep_phi")->Fill(    parton_top_lep_phi,       reco_top_lep_phi, weight);
    m_hm->Get2DHistogram("response/response_reco2parton_4j2b_pseudotop_lep_E")->Fill(      parton_top_lep_E / GeV,   reco_top_lep_E / GeV, weight);
    m_hm->Get2DHistogram("response/response_reco2parton_4j2b_pseudotop_lep_absrap")->Fill( fabs(parton_top_lep_y),   fabs(reco_top_lep_y), weight);

    m_hm->Get2DHistogram("response/response_reco2parton_4j2b_pseudotop_had_pt")->Fill(      parton_top_had_pt / GeV, reco_top_had_pt / GeV, weight);
    m_hm->Get2DHistogram("response/response_reco2parton_4j2b_pseudotop_had_eta")->Fill(     parton_top_had_eta,      reco_top_had_eta, weight);
    m_hm->Get2DHistogram("response/response_reco2parton_4j2b_pseudotop_had_phi")->Fill(     parton_top_had_phi,      reco_top_had_phi, weight);
    m_hm->Get2DHistogram("response/response_reco2parton_4j2b_pseudotop_had_E")->Fill(       parton_top_had_E / GeV,  reco_top_had_E / GeV, weight);
    m_hm->Get2DHistogram("response/response_reco2parton_4j2b_pseudotop_had_absrap")->Fill(  fabs(parton_top_had_y),  fabs(reco_top_had_y), weight);

    m_hm->Get2DHistogram("response/response_reco2parton_4j2b_pseudottbar_pt")->Fill(        parton_ttbar_pt / GeV,   reco_ttbar_pt / GeV, weight);
    m_hm->Get2DHistogram("response/response_reco2parton_4j2b_pseudottbar_eta")->Fill(       parton_ttbar_eta,        reco_ttbar_eta, weight);
    m_hm->Get2DHistogram("response/response_reco2parton_4j2b_pseudottbar_phi")->Fill(       parton_ttbar_phi,        reco_ttbar_phi, weight);
    m_hm->Get2DHistogram("response/response_reco2parton_4j2b_pseudottbar_E")->Fill(         parton_ttbar_E / GeV,    reco_ttbar_E / GeV, weight);
    m_hm->Get2DHistogram("response/response_reco2parton_4j2b_pseudottbar_m")->Fill(         parton_ttbar_m / GeV,    reco_ttbar_m / GeV, weight);
    m_hm->Get2DHistogram("response/response_reco2parton_4j2b_pseudottbar_absrap")->Fill(    fabs(parton_ttbar_y),   fabs(reco_ttbar_y), weight);
    
  }
  
  void CutFlowTTbarResolved::FillHistogramsPseudotopResponseParticleToParton(  EventData * ed, const double weight )
  {
      // particle level
    const double particle_top_lep_pt = ed->reco.pT.at(3);
    const double particle_top_lep_eta = ed->reco.eta.at(3);
    const double particle_top_lep_phi = ed->reco.phi.at(3);
    const double particle_top_lep_E = ed->reco.E.at(3);
    const double particle_top_lep_y = PhysicsHelperFunctions::Rapidity(ed->reco, 3);

    const double particle_top_had_pt = ed->reco.pT.at(4);
    const double particle_top_had_eta = ed->reco.eta.at(4);
    const double particle_top_had_phi = ed->reco.phi.at(4);
    const double particle_top_had_E = ed->reco.E.at(4);
    const double particle_top_had_y = PhysicsHelperFunctions::Rapidity(ed->reco, 4);

    const double particle_ttbar_pt = ed->reco.pT.at(5);
    const double particle_ttbar_eta = ed->reco.eta.at(5);
    const double particle_ttbar_phi = ed->reco.phi.at(5);
    const double particle_ttbar_E = ed->reco.E.at(5);
    const double particle_ttbar_m = ed->reco.m.at(5);
    const double particle_ttbar_y = PhysicsHelperFunctions::Rapidity(ed->reco, 5);
    
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
    
    const double parton_top_lep_pt = ed->mctruth.pT.at(ilep);
    const double parton_top_lep_eta = ed->mctruth.eta.at(ilep);
    const double parton_top_lep_phi = ed->mctruth.phi.at(ilep);
    const double parton_top_lep_E = ed->mctruth.E.at(ilep);
    const double parton_top_lep_y = PhysicsHelperFunctions::Rapidity(ed->mctruth, ilep);

    const double parton_top_had_pt = ed->mctruth.pT.at(ihad);
    const double parton_top_had_eta = ed->mctruth.eta.at(ihad);
    const double parton_top_had_phi = ed->mctruth.phi.at(ihad);
    const double parton_top_had_E = ed->mctruth.E.at(ihad);
    const double parton_top_had_y = PhysicsHelperFunctions::Rapidity(ed->mctruth, ihad);

    const double parton_ttbar_pt = ed->mctruth.pT.at(itt);
    const double parton_ttbar_eta = ed->mctruth.eta.at(itt);
    const double parton_ttbar_phi = ed->mctruth.phi.at(itt);
    const double parton_ttbar_E = ed->mctruth.E.at(itt);
    const double parton_ttbar_m = ed->mctruth.m.at(itt);
    const double parton_ttbar_y = PhysicsHelperFunctions::Rapidity(ed->mctruth, itt);
    
    // particle > parton
    m_hm->Get2DHistogram("response/response_particle2parton_4j2b_pseudotop_lep_pt")->Fill(     parton_top_lep_pt / GeV,  particle_top_lep_pt / GeV, weight);
    m_hm->Get2DHistogram("response/response_particle2parton_4j2b_pseudotop_lep_eta")->Fill(    parton_top_lep_eta,       particle_top_lep_eta, weight);
    m_hm->Get2DHistogram("response/response_particle2parton_4j2b_pseudotop_lep_phi")->Fill(    parton_top_lep_phi,       particle_top_lep_phi, weight);
    m_hm->Get2DHistogram("response/response_particle2parton_4j2b_pseudotop_lep_E")->Fill(      parton_top_lep_E / GeV,   particle_top_lep_E / GeV, weight);
    m_hm->Get2DHistogram("response/response_particle2parton_4j2b_pseudotop_lep_absrap")->Fill( fabs(parton_top_lep_y),   fabs(particle_top_lep_y), weight);

    m_hm->Get2DHistogram("response/response_particle2parton_4j2b_pseudotop_had_pt")->Fill(      parton_top_had_pt / GeV, particle_top_had_pt / GeV, weight);
    m_hm->Get2DHistogram("response/response_particle2parton_4j2b_pseudotop_had_eta")->Fill(     parton_top_had_eta,      particle_top_had_eta, weight);
    m_hm->Get2DHistogram("response/response_particle2parton_4j2b_pseudotop_had_phi")->Fill(     parton_top_had_phi,      particle_top_had_phi, weight);
    m_hm->Get2DHistogram("response/response_particle2parton_4j2b_pseudotop_had_E")->Fill(       parton_top_had_E / GeV,  particle_top_had_E / GeV, weight);
    m_hm->Get2DHistogram("response/response_particle2parton_4j2b_pseudotop_had_absrap")->Fill(  fabs(parton_top_had_y),  fabs(particle_top_had_y), weight);

    m_hm->Get2DHistogram("response/response_particle2parton_4j2b_pseudottbar_pt")->Fill(        parton_ttbar_pt / GeV,   particle_ttbar_pt / GeV, weight);
    m_hm->Get2DHistogram("response/response_particle2parton_4j2b_pseudottbar_eta")->Fill(       parton_ttbar_eta,        particle_ttbar_eta, weight);
    m_hm->Get2DHistogram("response/response_particle2parton_4j2b_pseudottbar_phi")->Fill(       parton_ttbar_phi,        particle_ttbar_phi, weight);
    m_hm->Get2DHistogram("response/response_particle2parton_4j2b_pseudottbar_E")->Fill(         parton_ttbar_E / GeV,    particle_ttbar_E / GeV, weight);
    m_hm->Get2DHistogram("response/response_particle2parton_4j2b_pseudottbar_m")->Fill(         parton_ttbar_m / GeV,    particle_ttbar_m / GeV, weight);
    m_hm->Get2DHistogram("response/response_particle2parton_4j2b_pseudottbar_absrap")->Fill(    fabs(parton_ttbar_y),   fabs(particle_ttbar_y), weight);
  }
  
  
/////////////////////////////////////////
// Plugin

extern "C" {

    CutFlowPluginFactory_TTbarResolved * MakeCutFlowPlugin() {
        return new CutFlowPluginFactory_TTbarResolved("TTbarResolved");
    };
}

