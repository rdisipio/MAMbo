#include "CutFlowTTbarResolved.h"

CutFlowTTbarResolved::CutFlowTTbarResolved() {
    m_pseudotop_reco = new PseudoTopReconstruction();
    m_pseudotop_particle = new PseudoTopReconstruction();
}

CutFlowTTbarResolved::~CutFlowTTbarResolved() {
    delete m_pseudotop_reco;
    delete m_pseudotop_particle;
}


/////////////////////////////////////////

bool CutFlowTTbarResolved::Initialize() {
    bool success = true;

    // AddChannel( "EL" );
    // AddCounter( "EL", "weighted", 3 );
    // AddCounter( "EL", "unweight", 3 );

    // SetCutName( "EL", "weighted", 0, "AllEvents" );
    // SetCutName( "EL", "weighted", 1, "Trigger" );
    // SetCutName( "EL", "weighted", 2, "Prim. Vtx" );
    // SetCutName( "EL", "weighted", 3, "single electron" );   

    AddChannel("ALL");
    AddCounterName("ALL", "weighted", 9);
    AddCounterName("ALL", "unweight", 9);

    SetCutName("ALL", "weighted", 0, "All Events");
    SetCutName("ALL", "weighted", 1, "Trigger");
    SetCutName("ALL", "weighted", 2, "Prim. Vtx");
    SetCutName("ALL", "weighted", 3, "SingleLepton");
    SetCutName("ALL", "weighted", 4, "ETmiss > 30 GeV");
    SetCutName("ALL", "weighted", 5, "mTW > 35 GeV");
    SetCutName("ALL", "weighted", 6, "NJets >= 2");
    SetCutName("ALL", "weighted", 7, "NJets >= 4");
    SetCutName("ALL", "weighted", 8, "Nbtags >= 1");
    SetCutName("ALL", "weighted", 9, "Nbtags >= 2");

    SetCutName("ALL", "unweight", 0, "All Events");
    SetCutName("ALL", "unweight", 1, "Trigger");
    SetCutName("ALL", "unweight", 2, "Prim. Vtx");
    SetCutName("ALL", "unweight", 3, "SingleLepton");
    SetCutName("ALL", "unweight", 4, "ETmiss > 30 GeV");
    SetCutName("ALL", "unweight", 5, "mTW > 35 GeV");
    SetCutName("ALL", "unweight", 6, "NJets >= 2");
    SetCutName("ALL", "unweight", 7, "NJets >= 4");
    SetCutName("ALL", "unweight", 8, "Nbtags >= 1");
    SetCutName("ALL", "unweight", 9, "Nbtags >= 2");

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

    int jet_n = ed->jets.n;
    double weight = 1.0; // ed->info.mcWeight;

    const double scaleFactor_PILEUP = ed->property["scaleFactor_PILEUP"];
    const double scaleFactor_ELE = ed->property["scaleFactor_ELE"];
    const double scaleFactor_MUON = ed->property["scaleFactor_MUON"];
    const double scaleFactor_BTAG = ed->property["scaleFactor_BTAG"];
    const double scaleFactor_TRIGGER = ed->property["scaleFactor_TRIGGER"];
    const double scaleFactor_WJETSNORM = ed->property["scaleFactor_WJETSNORM"];
    const double scaleFactor_WJETSSHAPE = ed->property["scaleFactor_WJETSSHAPE"];
    const double scaleFactor_JVFSF = ed->property["scaleFactor_JVFSF"];
    const double scaleFactor_ZVERTEX = ed->property["scaleFactor_ZVERTEX"];

    weight *=
            scaleFactor_PILEUP * scaleFactor_TRIGGER * scaleFactor_JVFSF * scaleFactor_ZVERTEX *
            scaleFactor_ELE * scaleFactor_MUON *
            scaleFactor_BTAG *
            scaleFactor_WJETSNORM * scaleFactor_WJETSSHAPE;

    if (fabs(weight) > 5.) printf("WARNING: event %i has large weight w = %f\n", ed->info.eventNumber, weight);

    // temporary hack
    weight = 1.0;

    // event-wise quantities
    double ETmiss = ed->MET.et;
    double mwt = ed->property["mwt"];

    PassedCut("ALL", "weighted", weight);
    PassedCut("ALL", "unweight");

    if (ETmiss == 0.)
        ETmiss = -1e10;

    double lep_pt = ed->electrons.pT.at(0);
    double lep_eta = ed->electrons.eta.at(0);
    double lep_phi = ed->electrons.phi.at(0);
    double lep_E = ed->electrons.E.at(0);
    double lep_q = ed->electrons.q.at(0);
    // TLorentzVector lepton;
    // lepton.SetPtEtaPhiE( lep_pt, lep_eta, lep_phi, lep_E );

    m_hm->GetHistogram("reco/reco_c0_lep_pt")->Fill(lep_pt / GeV);
    m_hm->GetHistogram("reco/reco_c0_lep_eta")->Fill(lep_eta);
    m_hm->GetHistogram("reco/reco_c0_lep_phi")->Fill(lep_phi);
    m_hm->GetHistogram("reco/reco_c0_lep_E")->Fill(lep_E / GeV);
    m_hm->GetHistogram("reco/reco_c0_met_pt")->Fill(ETmiss / GeV, weight);
    m_hm->GetHistogram("reco/reco_c0_mtw")->Fill(mwt / GeV, weight);

    m_hm->GetHistogram("reco/reco_c0_jet_n")->Fill(jet_n, weight);
    for (int j = 0; j < jet_n; ++j) {
        double jet_pt = ed->jets.pT.at(j);
        double jet_eta = ed->jets.eta.at(j);
        double jet_phi = ed->jets.phi.at(j);
        double jet_E = ed->jets.E.at(j);

        m_hm->GetHistogram("reco/reco_c0_jet_pt")->Fill(jet_pt / GeV, weight);
        m_hm->GetHistogram("reco/reco_c0_jet_eta")->Fill(jet_eta, weight);
        m_hm->GetHistogram("reco/reco_c0_jet_phi")->Fill(jet_phi, weight);
        m_hm->GetHistogram("reco/reco_c0_jet_E")->Fill(jet_E / GeV, weight);
    }


    if (isMCSignal) {
        const int truth_jet_n = ed->truth_jets.n;
        m_hm->GetHistogram("particle/particle_c0_jet_n")->Fill( truth_jet_n, weight );
        for (int j = 0; j < truth_jet_n; ++j) {
            double jet_pt  = ed->truth_jets.pT.at(j);
            double jet_eta = ed->truth_jets.eta.at(j);
            double jet_phi = ed->truth_jets.phi.at(j);
            double jet_E   = ed->truth_jets.E.at(j);

            m_hm->GetHistogram("particle/particle_c0_jet_pt")->Fill(jet_pt / GeV, weight);
            m_hm->GetHistogram("particle/particle_c0_jet_eta")->Fill(jet_eta, weight);
            m_hm->GetHistogram("particle/particle_c0_jet_phi")->Fill(jet_phi, weight);
            m_hm->GetHistogram("particle/particle_c0_jet_E")->Fill(jet_E / GeV, weight);
        }

    }
    //// example:
    // double weight = ed->info.mcWeight;
    // m_hm->GetHistogram( "fjet_pt" )->Fill( ed->fjet.pT / GeV, weight );
    //
    // PassedCut( "EL", "unweight" );
    // PassedCut( "EL", "weighted", 1.05 );


    // Trigger
    PassedCut("ALL", "weighted", weight);
    PassedCut("ALL", "unweight");

    // Prim. Vtx
    PassedCut("ALL", "weighted", weight);
    PassedCut("ALL", "unweight");

    // SingleLepton
    PassedCut("ALL", "weighted", weight);
    PassedCut("ALL", "unweight");

    // ETmiss > 30 GeV
    if (ETmiss < 30 * GeV) return success;

    PassedCut("ALL", "weighted", weight);
    PassedCut("ALL", "unweight");


    // mTW > 35 GeV
    if (mwt < 35 * GeV) return success;

    PassedCut("ALL", "weighted", weight);
    PassedCut("ALL", "unweight");


    // NJets 
    size_t goodjet_n = 0;
    size_t bjet_n = 0;
    size_t ljet_n = 0;
    for (int j = 0; j < jet_n; ++j) {
        double jet_pt = ed->jets.pT.at(j);
        double jet_eta = ed->jets.eta.at(j);
        // double jet_E   = ed->jets.E.at( j );
        double mv1 = ed->jets.property["MV1"].at(j);
        int jindex = ed->jets.index.at(j);

        if (jet_pt > 25 * GeV && (fabs(jet_eta) < 2.5)) goodjet_n++;

        if (mv1 > 0.7892) {
            bjet_n++;

            ed->bjets.pT.push_back(ed->jets.pT.at(j));
            ed->bjets.eta.push_back(ed->jets.eta.at(j));
            ed->bjets.phi.push_back(ed->jets.phi.at(j));
            ed->bjets.E.push_back(ed->jets.E.at(j));
            //   ed->bjets.m.push_back(   ed->jets.m.at(j)   );
            ed->bjets.index.push_back(jindex);
            ed->bjets.property["MV1"].push_back(mv1);
        } else {
            ljet_n++;

            ed->ljets.pT.push_back(ed->jets.pT.at(j));
            ed->ljets.eta.push_back(ed->jets.eta.at(j));
            ed->ljets.phi.push_back(ed->jets.phi.at(j));
            ed->ljets.E.push_back(ed->jets.E.at(j));
            // ed->ljets.m.push_back(   ed->jets.m.at(j)   );
            ed->ljets.index.push_back(jindex);
        }
    }
    //printf( "DEBUG: njets=%i nbjets=%i nljets=%i\n", jet_n, bjet_n, ljet_n );

    if (goodjet_n < 2) return success;
    PassedCut("ALL", "weighted", weight);
    PassedCut("ALL", "unweight");


    if (goodjet_n < 4) return success;
    PassedCut("ALL", "weighted", weight);
    PassedCut("ALL", "unweight");


    // Nbtags >= 1
    if (bjet_n < 1) return success;

    PassedCut("ALL", "weighted", weight);
    PassedCut("ALL", "unweight");


    m_hm->GetHistogram("reco/reco_h_4j1b_lep_pt")->Fill(lep_pt / GeV);
    m_hm->GetHistogram("reco/reco_h_4j1b_lep_eta")->Fill(lep_eta);
    m_hm->GetHistogram("reco/reco_h_4j1b_lep_phi")->Fill(lep_phi);
    m_hm->GetHistogram("reco/reco_h_4j1b_lep_E")->Fill(lep_E / GeV);
    m_hm->GetHistogram("reco/reco_h_4j1b_met_pt")->Fill(ETmiss / GeV, weight);
    m_hm->GetHistogram("reco/reco_h_4j1b_mtw")->Fill(mwt / GeV, weight);

    m_hm->GetHistogram("reco/reco_h_4j1b_jet_n")->Fill(jet_n, weight);
    for (int j = 0; j < jet_n; ++j) {
        double jet_pt = ed->jets.pT.at(j);
        double jet_eta = ed->jets.eta.at(j);
        double jet_phi = ed->jets.phi.at(j);
        double jet_E = ed->jets.E.at(j);

        m_hm->GetHistogram("reco/reco_h_4j1b_jet_pt")->Fill(jet_pt / GeV, weight);
        m_hm->GetHistogram("reco/reco_h_4j1b_jet_eta")->Fill(jet_eta, weight);
        m_hm->GetHistogram("reco/reco_h_4j1b_jet_phi")->Fill(jet_phi, weight);
        m_hm->GetHistogram("reco/reco_h_4j1b_jet_E")->Fill(jet_E / GeV, weight);
    }


    // Nbtags >= 2
    if (bjet_n < 2) return success;

    PassedCut("ALL", "weighted", weight);
    PassedCut("ALL", "unweight");


    m_hm->GetHistogram("reco/reco_h_4j2b_lep_pt")->Fill(lep_pt / GeV);
    m_hm->GetHistogram("reco/reco_h_4j2b_lep_eta")->Fill(lep_eta);
    m_hm->GetHistogram("reco/reco_h_4j2b_lep_phi")->Fill(lep_phi);
    m_hm->GetHistogram("reco/reco_h_4j2b_lep_E")->Fill(lep_E / GeV);
    m_hm->GetHistogram("reco/reco_h_4j2b_met_pt")->Fill(ETmiss / GeV, weight);
    m_hm->GetHistogram("reco/reco_h_4j2b_mtw")->Fill(mwt / GeV, weight);

    m_hm->GetHistogram("reco/reco_h_4j2b_jet_n")->Fill(jet_n, weight);
    for (int j = 0; j < jet_n; ++j) {
        double jet_pt = ed->jets.pT.at(j);
        double jet_eta = ed->jets.eta.at(j);
        double jet_phi = ed->jets.phi.at(j);
        double jet_E = ed->jets.E.at(j);

        m_hm->GetHistogram("reco/reco_h_4j2b_jet_pt")->Fill(jet_pt / GeV, weight);
        m_hm->GetHistogram("reco/reco_h_4j2b_jet_eta")->Fill(jet_eta, weight);
        m_hm->GetHistogram("reco/reco_h_4j2b_jet_phi")->Fill(jet_phi, weight);
        m_hm->GetHistogram("reco/reco_h_4j2b_jet_E")->Fill(jet_E / GeV, weight);
    }


    // Have fun with pseudo tops!

    m_pseudotop_reco->SetEventData(ed);
    m_pseudotop_reco->SetTarget(PseudoTopReconstruction::kReco);
    m_pseudotop_reco->SetChargedLepton(kElectron, 0);
    m_pseudotop_reco->Run();

    // dumped indices:
    // reco                : 0=t_lep 1=t_had 2=ttbar
    // truth (particle lvl): 3=t_lep 4=t_had 5=ttbar
    // truth (parton lvl)  : 6=t_lep 7=t_had 8=ttbar

    FillHistogramsPseudotopReco(ed, weight);

    if (isMCSignal) {
        const int mc_overlap = ed->property["mc_overlap"];
        //        if (mc_overlap) {
        //            cout << "INFO: event is vetoed at MC particle level due to overlap" << endl;
        //            return success;
        //        }
        
        FillHistogramsPseudotopParton( ed, weight );
        
        m_pseudotop_particle->SetEventData(ed);
        m_pseudotop_particle->SetTarget(PseudoTopReconstruction::kTruth);
        m_pseudotop_particle->SetChargedLepton(kElectron, 0);

        try {
            m_pseudotop_particle->Run();
        } catch (...) {
            return success;
        }

        FillHistogramsPseudotopParticle(ed, weight);
        
        FillHistogramsPseudotopResponse(ed, weight);
    }

    return success;
}


/////////////////////////////////////////

bool CutFlowTTbarResolved::PassedCutFlowReco(EventData * ed) {
    bool passed = true;

    int jet_n = ed->jets.n;
    int bjet_n = ed->bjets.n;
    double ETmiss = ed->MET.et;
    double mwt = ed->property["mwt"];
    double lep_pt = ed->electrons.pT.at(0);

    if (lep_pt < 25 * GeV) return !passed;
    if (ETmiss < 30 * GeV) return !passed;
    if (mwt < 35 * GeV) return !passed;
    if (jet_n < 4) return !passed;
    if (bjet_n < 2) return !passed;

    return passed;
}

bool CutFlowTTbarResolved::PassedCutFlowParticle(EventData * ed) {
    bool passed = true;

    return passed;
}


/////////////////////////////////////////

void CutFlowTTbarResolved::FillHistogramsPseudotopReco( EventData * ed, const double weight) {
    const double top_lep_pt = ed->reco.pT.at(0);
    const double top_lep_eta = ed->reco.eta.at(0);
    const double top_lep_phi = ed->reco.phi.at(0);
    const double top_lep_E = ed->reco.E.at(0);
    const double top_lep_y = PhysicsHelperFunctions::Rapidity(ed->reco, 0);

    const double top_had_pt = ed->reco.pT.at(1);
    const double top_had_eta = ed->reco.eta.at(1);
    const double top_had_phi = ed->reco.phi.at(1);
    const double top_had_E = ed->reco.E.at(1);
    const double top_had_y = PhysicsHelperFunctions::Rapidity(ed->reco, 1);

    const double ttbar_pt = ed->reco.pT.at(2);
    const double ttbar_eta = ed->reco.eta.at(2);
    const double ttbar_phi = ed->reco.phi.at(2);
    const double ttbar_E = ed->reco.E.at(2);
    const double ttbar_m = ed->reco.m.at(2);
    const double ttbar_y = PhysicsHelperFunctions::Rapidity(ed->reco, 2);

    m_hm->GetHistogram("reco/reco_h_4j2b_pseudotop_reco_lep_pt")->Fill(top_lep_pt / GeV, weight);
    m_hm->GetHistogram("reco/reco_h_4j2b_pseudotop_reco_lep_eta")->Fill(top_lep_eta, weight);
    m_hm->GetHistogram("reco/reco_h_4j2b_pseudotop_reco_lep_phi")->Fill(top_lep_phi, weight);
    m_hm->GetHistogram("reco/reco_h_4j2b_pseudotop_reco_lep_E")->Fill(top_lep_E / GeV, weight);
    m_hm->GetHistogram("reco/reco_h_4j2b_pseudotop_reco_lep_absrap")->Fill(fabs(top_lep_y), weight);

    m_hm->GetHistogram("reco/reco_h_4j2b_pseudotop_reco_had_pt")->Fill(top_had_pt / GeV, weight);
    m_hm->GetHistogram("reco/reco_h_4j2b_pseudotop_reco_had_eta")->Fill(top_had_eta, weight);
    m_hm->GetHistogram("reco/reco_h_4j2b_pseudotop_reco_had_phi")->Fill(top_had_phi, weight);
    m_hm->GetHistogram("reco/reco_h_4j2b_pseudotop_reco_had_E")->Fill(top_had_E / GeV, weight);
    m_hm->GetHistogram("reco/reco_h_4j2b_pseudotop_reco_had_absrap")->Fill(fabs(top_had_y), weight);

    m_hm->GetHistogram("reco/reco_h_4j2b_pseudottbar_reco_pt")->Fill(ttbar_pt / GeV, weight);
    m_hm->GetHistogram("reco/reco_h_4j2b_pseudottbar_reco_eta")->Fill(ttbar_eta, weight);
    m_hm->GetHistogram("reco/reco_h_4j2b_pseudottbar_reco_phi")->Fill(ttbar_phi, weight);
    m_hm->GetHistogram("reco/reco_h_4j2b_pseudottbar_reco_E")->Fill(ttbar_E / GeV, weight);
    m_hm->GetHistogram("reco/reco_h_4j2b_pseudottbar_reco_m")->Fill(ttbar_m / GeV, weight);
    m_hm->GetHistogram("reco/reco_h_4j2b_pseudottbar_reco_absrap")->Fill(fabs(ttbar_y), weight);
}


/////////////////////////////////////////

void CutFlowTTbarResolved::FillHistogramsPseudotopParticle( EventData * ed, const double weight) {
    const double top_lep_pt = ed->reco.pT.at(3);
    const double top_lep_eta = ed->reco.eta.at(3);
    const double top_lep_phi = ed->reco.phi.at(3);
    const double top_lep_E = ed->reco.E.at(3);
    const double top_lep_y = PhysicsHelperFunctions::Rapidity(ed->reco, 3);

    const double top_had_pt = ed->reco.pT.at(4);
    const double top_had_eta = ed->reco.eta.at(4);
    const double top_had_phi = ed->reco.phi.at(4);
    const double top_had_E = ed->reco.E.at(4);
    const double top_had_y = PhysicsHelperFunctions::Rapidity(ed->reco, 4);

    const double ttbar_pt = ed->reco.pT.at(5);
    const double ttbar_eta = ed->reco.eta.at(5);
    const double ttbar_phi = ed->reco.phi.at(5);
    const double ttbar_E = ed->reco.E.at(5);
    const double ttbar_m = ed->reco.m.at(5);
    const double ttbar_y = PhysicsHelperFunctions::Rapidity(ed->reco, 5);

    m_hm->GetHistogram("particle/particle_h_4j2b_pseudotop_lep_pt")->Fill(top_lep_pt / GeV, weight);
    m_hm->GetHistogram("particle/particle_h_4j2b_pseudotop_lep_eta")->Fill(top_lep_eta, weight);
    m_hm->GetHistogram("particle/particle_h_4j2b_pseudotop_lep_phi")->Fill(top_lep_phi, weight);
    m_hm->GetHistogram("particle/particle_h_4j2b_pseudotop_lep_E")->Fill(top_lep_E / GeV, weight);
    m_hm->GetHistogram("particle/particle_h_4j2b_pseudotop_lep_absrap")->Fill(fabs(top_lep_y), weight);

    m_hm->GetHistogram("particle/particle_h_4j2b_pseudotop_had_pt")->Fill(top_had_pt / GeV, weight);
    m_hm->GetHistogram("particle/particle_h_4j2b_pseudotop_had_eta")->Fill(top_had_eta, weight);
    m_hm->GetHistogram("particle/particle_h_4j2b_pseudotop_had_phi")->Fill(top_had_phi, weight);
    m_hm->GetHistogram("particle/particle_h_4j2b_pseudotop_had_E")->Fill(top_had_E / GeV, weight);
    m_hm->GetHistogram("particle/particle_h_4j2b_pseudotop_had_absrap")->Fill(fabs(top_had_y), weight);

    m_hm->GetHistogram("particle/particle_h_4j2b_pseudottbar_pt")->Fill(ttbar_pt / GeV, weight);
    m_hm->GetHistogram("particle/particle_h_4j2b_pseudottbar_eta")->Fill(ttbar_eta, weight);
    m_hm->GetHistogram("particle/particle_h_4j2b_pseudottbar_phi")->Fill(ttbar_phi, weight);
    m_hm->GetHistogram("particle/particle_h_4j2b_pseudottbar_E")->Fill(ttbar_E / GeV, weight);
    m_hm->GetHistogram("particle/particle_h_4j2b_pseudottbar_m")->Fill(ttbar_m / GeV, weight);
    m_hm->GetHistogram("particle/particle_h_4j2b_pseudottbar_absrap")->Fill(fabs(ttbar_y), weight);
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
    
    const double top_lep_pt = ed->mctruth.pT.at(ilep);
    const double top_lep_eta = ed->mctruth.eta.at(ilep);
    const double top_lep_phi = ed->mctruth.phi.at(ilep);
    const double top_lep_E = ed->mctruth.E.at(ilep);
    const double top_lep_y = PhysicsHelperFunctions::Rapidity(ed->mctruth, ilep);

    const double top_had_pt = ed->mctruth.pT.at(ihad);
    const double top_had_eta = ed->mctruth.eta.at(ihad);
    const double top_had_phi = ed->mctruth.phi.at(ihad);
    const double top_had_E = ed->mctruth.E.at(ihad);
    const double top_had_y = PhysicsHelperFunctions::Rapidity(ed->mctruth, ihad);

    const double ttbar_pt = ed->mctruth.pT.at(itt);
    const double ttbar_eta = ed->mctruth.eta.at(itt);
    const double ttbar_phi = ed->mctruth.phi.at(itt);
    const double ttbar_E = ed->mctruth.E.at(itt);
    const double ttbar_m = ed->mctruth.m.at(itt);
    const double ttbar_y = PhysicsHelperFunctions::Rapidity(ed->mctruth, itt);

    m_hm->GetHistogram("parton/parton_h_4j2b_pseudotop_lep_pt")->Fill(top_lep_pt / GeV, weight);
    m_hm->GetHistogram("parton/parton_h_4j2b_pseudotop_lep_eta")->Fill(top_lep_eta, weight);
    m_hm->GetHistogram("parton/parton_h_4j2b_pseudotop_lep_phi")->Fill(top_lep_phi, weight);
    m_hm->GetHistogram("parton/parton_h_4j2b_pseudotop_lep_E")->Fill(top_lep_E / GeV, weight);
    m_hm->GetHistogram("parton/parton_h_4j2b_pseudotop_lep_absrap")->Fill(fabs(top_lep_y), weight);

    m_hm->GetHistogram("parton/parton_h_4j2b_pseudotop_had_pt")->Fill(top_had_pt / GeV, weight);
    m_hm->GetHistogram("parton/parton_h_4j2b_pseudotop_had_eta")->Fill(top_had_eta, weight);
    m_hm->GetHistogram("parton/parton_h_4j2b_pseudotop_had_phi")->Fill(top_had_phi, weight);
    m_hm->GetHistogram("parton/parton_h_4j2b_pseudotop_had_E")->Fill(top_had_E / GeV, weight);
    m_hm->GetHistogram("parton/parton_h_4j2b_pseudotop_had_absrap")->Fill(fabs(top_had_y), weight);

    m_hm->GetHistogram("parton/parton_h_4j2b_pseudottbar_pt")->Fill(ttbar_pt / GeV, weight);
    m_hm->GetHistogram("parton/parton_h_4j2b_pseudottbar_eta")->Fill(ttbar_eta, weight);
    m_hm->GetHistogram("parton/parton_h_4j2b_pseudottbar_phi")->Fill(ttbar_phi, weight);
    m_hm->GetHistogram("parton/parton_h_4j2b_pseudottbar_E")->Fill(ttbar_E / GeV, weight);
    m_hm->GetHistogram("parton/parton_h_4j2b_pseudottbar_m")->Fill(ttbar_m / GeV, weight);
    m_hm->GetHistogram("parton/parton_h_4j2b_pseudottbar_absrap")->Fill(fabs(ttbar_y), weight);

}

void CutFlowTTbarResolved::FillHistogramsPseudotopResponse( EventData * ed, const double weight) 
{
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

    m_hm->Get2DHistogram("response/h_4j2b_pseudotop_response_lep_pt")->Fill(particle_top_lep_pt / GeV, reco_top_lep_pt / GeV, weight);
    m_hm->Get2DHistogram("response/h_4j2b_pseudotop_response_lep_eta")->Fill(particle_top_lep_eta, reco_top_lep_eta, weight);
    m_hm->Get2DHistogram("response/h_4j2b_pseudotop_response_lep_phi")->Fill(particle_top_lep_phi, reco_top_lep_phi, weight);
    m_hm->Get2DHistogram("response/h_4j2b_pseudotop_response_lep_E")->Fill(particle_top_lep_E / GeV, reco_top_lep_E / GeV, weight);
    m_hm->Get2DHistogram("response/h_4j2b_pseudotop_response_lep_absrap")->Fill(fabs(particle_top_lep_y), fabs(reco_top_lep_y), weight);

    m_hm->Get2DHistogram("response/h_4j2b_pseudotop_response_had_pt")->Fill(particle_top_had_pt / GeV, reco_top_had_pt / GeV, weight);
    m_hm->Get2DHistogram("response/h_4j2b_pseudotop_response_had_eta")->Fill(particle_top_had_eta, reco_top_had_eta, weight);
    m_hm->Get2DHistogram("response/h_4j2b_pseudotop_response_had_phi")->Fill(particle_top_had_phi, reco_top_had_phi, weight);
    m_hm->Get2DHistogram("response/h_4j2b_pseudotop_response_had_E")->Fill(particle_top_had_E / GeV, reco_top_had_E / GeV, weight);
    m_hm->Get2DHistogram("response/h_4j2b_pseudotop_response_had_absrap")->Fill(fabs(particle_top_had_y), fabs(reco_top_had_y), weight);

    m_hm->Get2DHistogram("response/h_4j2b_pseudottbar_response_pt")->Fill(particle_ttbar_pt / GeV, reco_ttbar_pt / GeV, weight);
    m_hm->Get2DHistogram("response/h_4j2b_pseudottbar_response_eta")->Fill(particle_ttbar_eta, reco_ttbar_eta, weight);
    m_hm->Get2DHistogram("response/h_4j2b_pseudottbar_response_phi")->Fill(particle_ttbar_phi, reco_ttbar_phi, weight);
    m_hm->Get2DHistogram("response/h_4j2b_pseudottbar_response_E")->Fill(particle_ttbar_E / GeV, reco_ttbar_E / GeV, weight);
    m_hm->Get2DHistogram("response/h_4j2b_pseudottbar_response_m")->Fill(particle_ttbar_m / GeV, reco_ttbar_m / GeV, weight);
    m_hm->Get2DHistogram("response/h_4j2b_pseudottbar_response_absrap")->Fill(fabs(particle_ttbar_y), fabs(reco_ttbar_y), weight);
}


/////////////////////////////////////////
// Plugin

extern "C" {

    CutFlowPluginFactory_TTbarResolved * MakeCutFlowPlugin() {
        return new CutFlowPluginFactory_TTbarResolved("TTbarResolved");
    };
}

