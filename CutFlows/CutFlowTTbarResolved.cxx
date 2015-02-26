#include "CutFlowTTbarResolved.h"
CutFlowTTbarResolved::CutFlowTTbarResolved() 
{
    m_pseudotop_reco = new PseudoTopReconstruction();
    m_pseudotop_particle = new PseudoTopReconstruction();
    
    m_pseudotop_matching_reco2particle   = new PseudoTopMatching( PseudoTopMatching::kRecoToParticle );
    m_pseudotop_matching_reco2parton     = new PseudoTopMatching( PseudoTopMatching::kRecoToParton );
    m_pseudotop_matching_particle2parton = new PseudoTopMatching( PseudoTopMatching::kParticleToParton );
    
    alias = {
        "beforeCuts", "trig", "pvtx", "lep", "pTlep", "met", "mtw", "3j0b", "4j0b", "4j1b", "afterCuts"
    };

#ifdef __MOMA__
   m_moma = MoMATool::GetHandle();
   cout << "INFO: ATLAS ROOTCORE detected. MoMA tool initialized." << endl;
#endif
   
}

CutFlowTTbarResolved::~CutFlowTTbarResolved() {
    SAFE_DELETE( m_pseudotop_reco )
    SAFE_DELETE( m_pseudotop_particle )
    
    SAFE_DELETE( m_pseudotop_matching_reco2particle )
    SAFE_DELETE( m_pseudotop_matching_reco2parton )
    SAFE_DELETE( m_pseudotop_matching_particle2parton )

#ifdef __MOMA__
    SAFE_DELETE( m_moma );
#endif

}

/////////////////////////////////////////

bool CutFlowTTbarResolved::Initialize() {
    bool success = true;

//    int isMCSignal = (int) m_config->custom_params["isMCSignal"];
    unsigned long isRealData = m_config->custom_params_flag["isRealData"];
    unsigned long isWjets    = m_config->custom_params_flag["isWjets"];
    unsigned long isQCD      = m_config->custom_params_flag["isQCD"];

#ifdef __MOMA__
    m_syst_type = NOMINAL;

    if( m_config->custom_params_string.count( "scale_syst" ) ) {
        const string syst = m_config->custom_params_string["scale_syst"];

        if( syst == "BTAGSFUP" )      m_syst_type = BTAGSFUP;
        if( syst == "BTAGSFDOWN" )    m_syst_type = BTAGSFDOWN;
        if( syst == "CTAUTAGSFUP" )   m_syst_type = CTAUTAGSFUP;
        if( syst == "CTAUTAGSFDOWN" ) m_syst_type = CTAUTAGSFDOWN;    
        if( syst == "MISTAGSFUP" )    m_syst_type = MISTAGSFUP;
        if( syst == "MISTAGSFDOWN" )  m_syst_type = MISTAGSFDOWN;    

        cout << "INFO: Scale factor systematic: " << syst << endl;
    }    

#endif

    m_rand = new TRandom3(12345);

    AddChannel("LPLUSJETS");

    AddCounterName("LPLUSJETS", "reco_unweight", 10 );
    SetCutName("LPLUSJETS", "reco_unweight", 0, "All Events");
    SetCutName("LPLUSJETS", "reco_unweight", 1, "Trigger");
    SetCutName("LPLUSJETS", "reco_unweight", 2, "Prim. Vtx");
    SetCutName("LPLUSJETS", "reco_unweight", 3, "SingleLepton");
    SetCutName("LPLUSJETS", "reco_unweight", 4, "Lep pT > 25 GeV" );
    if( m_config->channel == kElectron ) {
       SetCutName("LPLUSJETS", "reco_unweight", 5, "ETmiss > 30 GeV");
       SetCutName("LPLUSJETS", "reco_unweight", 6, "mTW > 30 GeV");
    }
    else {
       SetCutName("LPLUSJETS", "reco_unweight", 5, "ETmiss > 20 GeV");
       SetCutName("LPLUSJETS", "reco_unweight", 6, "mTW + ETmiss > 60 GeV");
    }
    SetCutName("LPLUSJETS", "reco_unweight", 7, "NJets >= 3");
    SetCutName("LPLUSJETS", "reco_unweight", 8, "NJets >= 4");
    SetCutName("LPLUSJETS", "reco_unweight", 9, "Nbtags >= 1");
    SetCutName("LPLUSJETS", "reco_unweight", 10, "Nbtags >= 2");

    AddCounterName("LPLUSJETS", "reco_weighted", 10);
    SetCutName("LPLUSJETS", "reco_weighted", 0, "All Events");
    SetCutName("LPLUSJETS", "reco_weighted", 1, "Trigger");
    SetCutName("LPLUSJETS", "reco_weighted", 2, "Prim. Vtx");
    SetCutName("LPLUSJETS", "reco_weighted", 3, "SingleLepton");
    SetCutName("LPLUSJETS", "reco_weighted", 4, "Lep pT > 25 GeV" );
    if( m_config->channel == kElectron ) {
       SetCutName("LPLUSJETS", "reco_weighted", 5, "ETmiss > 30 GeV");
       SetCutName("LPLUSJETS", "reco_weighted", 6, "mTW > 30 GeV");
    }
    else {
       SetCutName("LPLUSJETS", "reco_weighted", 5, "ETmiss > 20 GeV");
       SetCutName("LPLUSJETS", "reco_weighted", 6, "mTW + ETmiss > 60 GeV");
    }    
    SetCutName("LPLUSJETS", "reco_weighted", 7, "NJets >= 3" );
    SetCutName("LPLUSJETS", "reco_weighted", 8, "NJets >= 4" );
    SetCutName("LPLUSJETS", "reco_weighted", 9, "Nbtags >= 1");
    SetCutName("LPLUSJETS", "reco_weighted", 10, "Nbtags >= 2");



    if( isRealData || isWjets || isQCD ) return success;

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

bool FillHistograms(int cutN) {
    bool success = true;

    return success;
}


/////////////////////////////////////////

bool CutFlowTTbarResolved::Apply(EventData * ed) {
    bool success = true;

    CutFlow::Start();

    const unsigned long isMCSignal = m_config->custom_params_flag["isMCSignal"];
    const unsigned long isRealData = m_config->custom_params_flag["isRealData"];
    const unsigned long isWjets    = m_config->custom_params_flag["isWjets"];
    const unsigned long isQCD      = m_config->custom_params_flag["isQCD"];

    double weight_reco_level     = 1.;
    double weight_particle_level = 1.;

    if( !isRealData && !isQCD ) {
   	 weight_reco_level     = ed->info.mcWeight;
         weight_particle_level = ed->info.mcWeight;

	 // some Single Top samples have buggy mc weight 
         if( fabs(weight_reco_level) < 1e-5 )     weight_reco_level     /= fabs(weight_reco_level);
         if( fabs(weight_particle_level) < 1e-5 ) weight_particle_level /= fabs(weight_particle_level);

         const double scaleFactor_PILEUP     = ed->property["scaleFactor_PILEUP"];
         const double scaleFactor_ELE        = ed->property["scaleFactor_ELE"];
         const double scaleFactor_MUON       = ed->property["scaleFactor_MUON"];
         const double scaleFactor_TRIGGER    = ed->property["scaleFactor_TRIGGER"];
//         const double scaleFactor_WJETSNORM  = ed->property["scaleFactor_WJETSNORM"];
//         const double scaleFactor_WJETSSHAPE = ed->property["scaleFactor_WJETSSHAPE"];
         const double scaleFactor_JVFSF      = ed->property["scaleFactor_JVFSF"]; // should be always 1 now!
         const double scaleFactor_ZVERTEX    = ed->property["scaleFactor_ZVERTEX"];
//         const double scaleFactor_BTAG       = ed->property["scaleFactor_BTAG"];
 
#ifdef __MOMA__
         const double scaleFactor_BTAG       = m_moma->GetBTagWeight( ed, 0.7892, m_syst_type ); 
//         const double scaleFactor_BTAG_ntup  = ed->property["scaleFactor_BTAG"]; 
//         cout << "DEBUG: btagsf(OTF) = " << scaleFactor_BTAG << "  |  btagsf(NTUP) = " << scaleFactor_BTAG_ntup << endl;
#else 
         const double scaleFactor_BTAG       = ed->property["scaleFactor_BTAG"];
#endif

         
//      cout << "DEBUG: sf: " << scaleFactor_PILEUP << " " << scaleFactor_ELE << " " << scaleFactor_MUON << " " << scaleFactor_TRIGGER << " " << scaleFactor_JVFSF << " " << scaleFactor_ZVERTEX << " " << scaleFactor_BTAG << endl;

       weight_reco_level *=
            scaleFactor_PILEUP * scaleFactor_TRIGGER * scaleFactor_JVFSF * scaleFactor_ZVERTEX *
            scaleFactor_ELE * scaleFactor_MUON *
            scaleFactor_BTAG;

   	 // as boosted guys do
         // weight_particle_level *= scaleFactor_PILEUP * scaleFactor_ZVERTEX;
    }

    //if( isWjets ) { }

    if( isQCD ) {
      const double qcd_weight = GetFakesWeight( ed );
      weight_reco_level     *= qcd_weight;
      weight_particle_level *= qcd_weight; // should we?
    }

    ed->property["weight_particle_level"] = weight_particle_level;
    ed->property["weight_reco_level"]     = weight_reco_level;

//    if (fabs(weight_reco_level) > 5.) printf("WARNING: event %i has large weight_reco_level w = %f\n", ed->info.eventNumber, weight_reco_level);

    // Apply selections and fill control histograms (pt, eta, etc..)
    const bool passedRecoSelection     = PassedCutFlowReco( ed );
    const bool passedParticleSelection = ( isRealData || isWjets || isQCD ) ? false : PassedCutFlowParticle( ed );

   
    int Debug = 0;
    if (Debug) cout << "Passed Reco: " << passedRecoSelection << " Particle: " << passedParticleSelection << endl;

    if (!passedParticleSelection && !passedRecoSelection)
      return success;


    // Have fun with pseudo tops!

    // yup, this line really needs to be here:
    m_pseudotop_reco->SetEventData(ed);


    bool fillHistos = true;
    bool fillCorrections = true;
    bool splitSample = false; // HACK!
    if (isMCSignal and splitSample) {
      fillHistos =  (m_rand -> Integer(2)); // this or not;)
      fillCorrections = not fillHistos;
    }


    if( passedRecoSelection ) {
     
      //     need to repeat... ???
      m_pseudotop_reco->SetEventData(ed);
      m_pseudotop_reco->SetTarget(PseudoTopReconstruction::kReco);
      
      m_pseudotop_reco->SetChargedLepton(m_config->channel, 0);
      m_pseudotop_reco->Run();

      // OLD, w/o W's:
      // reco                : 0=t_lep 1=t_had 2=ttbar
      // truth (particle lvl): 3=t_lep 4=t_had 5=ttbar
      // truth (parton lvl)  : 6=t_lep 7=t_had 8=ttbar

      // NEW:
      // dumped indices:
      // reco                : 0=t_lep 1=t_had 2=ttbar 3=W_lep 4=W_had
      // truth (particle lvl): 5=t_lep 6=t_had 7=ttbar 8=W_lep 9=W_had
      // truth (parton lvl)  : 10=t_lep 11=t_had 12=ttbar

      if (fillHistos)
	FillHistogramsPseudotopReco(ed, weight_reco_level);

    } else {
      // ugly hack, due to pseudotop indices in ed required to be, e.g.,
      // reco: 0,1; particle is 5,6
      // needed later for passed particle not reco
      m_pseudotop_reco->MakeDummyPseudotops();
    }

    if( !isMCSignal)
      return success;

    // there is always a parton-level top
    // but fill it only when also passed the reco so that to have reco to parton migration
    if(passedRecoSelection) {

      if (fillHistos) {
	// NOW: we should think whether we want to fill this only when passed reco, I'd think so? JK
	FillHistogramsPseudotopParton(ed, weight_particle_level);
	FillHistogramsMatchingRecoToParton(weight_reco_level);
      }
      // makes sense only when passed reco:
      if (fillCorrections)
      FillHistogramsPseudotopResponseRecoToParton(ed, weight_reco_level);
    } 
    
    // nb: events could NOT pass the particle-level selection
    //     but you could still be able to reconstruct pseudotops (i.e. 1l4j2b)

    if( !passedParticleSelection ) {
      // need to fill histograms binned in reco quantities,
      // standing for passed: reco!part
      
      if(passedRecoSelection and fillHistos) {
	//	FillHistogramsPseudotopReco(ed, weight_reco_level, "reco_not_particle");
      }
      return success;
      
    } else { // passed particle

      m_pseudotop_particle->SetEventData(ed);
      m_pseudotop_particle->SetTarget(PseudoTopReconstruction::kTruth);
      m_pseudotop_particle->SetChargedLepton(m_config->channel, 0);

      if (Debug) {
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
      if (fillHistos) {
	FillHistogramsPseudotopParticle(ed, weight_particle_level);
      }

      // if in addition passed also reco, we can fill response matrices:
      if(passedParticleSelection && passedRecoSelection) { // this is slightly over-ifed;-)
       
	// rds:
	m_pseudotop_matching_reco2particle->SetEventData(ed);
	m_pseudotop_matching_reco2particle->DoMatching(0, 5, "pseudotop_lep");
	m_pseudotop_matching_reco2particle->DoMatching(1, 6, "pseudotop_had");
	m_pseudotop_matching_reco2particle->DoMatching(2, 7, "pseudottbar");

	// matching:
	FillHistogramsMatchingRecoToParticle(weight_reco_level);
	FillHistogramsMatchingParticleToParton(weight_particle_level);

	// JK:
	bool passedDRMatching = m_pseudotop_matching_reco2particle->DoObjectsMatching(0); // 0 = no debug

	if (fillCorrections) {

	  // fill reco && particle for the denumerator of the f_'missassign' and numerator for f_{r!p} (acceptance)
	  // this is WITHOUT the matching condition!
	  FillHistogramsPseudotopReco(ed, weight_reco_level, "reco_and_particle_r"); // YES, with reco weight! _r as binned in reco

	  // fill response matrix:
	  // NEW: added here the matching condition!!! JK 3.12.2014

	  if (passedDRMatching) {
	    // N.B.: migration matrices for unfolding filled only when also the matching passed!!!
	    FillHistogramsPseudotopResponseRecoToParticle(ed, weight_reco_level); 
	    FillHistogramsPseudotopResponseParticleToParton(ed, weight_particle_level);
	    //  fill numerator for the matching eff (f_'missassign')
	    // reco && particle && matched:
	    FillHistogramsPseudotopReco(ed, weight_reco_level, "matched_r"); // YES, binned in reco, and with reco weight! _r as binned in reco
	    FillHistogramsPseudotopParticle(ed, weight_reco_level, "matched_p"); // YES, binned in particle, but weighted in reco! _p as binned in particle
	  }
	}

	
      } // passed particle and reco
    } // passed particle

    if (passedParticleSelection && !passedRecoSelection && fillCorrections) {
      // did not pass reco
      //      FillHistogramsPseudotopParticle(ed, weight_particle_level, "particle_not_reco");
    }

    return success;
}


/////////////////////////////////////////

bool CutFlowTTbarResolved::PassedCutFlowReco(EventData * ed) {
    bool passed = true;
   
//    const int hfor = int( ed->property["hfor"] );

    int    jet_n  = ed->jets.n;
    int    bjet_n = ed->bjets.n;
    double ETmiss = ed->MET.et;
    double mwt    = ed->MET.mwt;
    
    const double weight = ed->property["weight_reco_level"];
 
    ControlPlotValues values;
    values.weight = weight;
    values.mu      = ed->property["mu"];
    values.pvxp_n  = ed->property["pvxp_n"];
    values.vxp_z   = ed->property["vxp_z"];
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
    for (int bj = 0; bj < ed->bjets.n; ++bj) {
        JetValues* jet = new JetValues();
        jet->pt  = ed->bjets.pT.at(bj);
        jet->eta = ed->bjets.eta.at(bj);
        jet->phi = ed->bjets.phi.at(bj);
        jet->E   = ed->bjets.E.at(bj);
        jet->m   = ed->bjets.m.at(bj);
        values.bJets.push_back(jet);
    }   

/*
    if( (hfor<0) || (hfor>3) ) {
      cout << "discarded event: hfor = " << hfor << endl;
      return passed; 
    }
*/

    // 0 all events
    PassedCut( "LPLUSJETS", "reco_weighted", weight );
    PassedCut( "LPLUSJETS", "reco_unweight");
//    FillHistogramsControlPlotsReco( values );
    
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

    // 5 ETmiss cut
    const double met_cut = ( m_config->channel == kElectron ) ? 30*GeV : 20*GeV;
    if( ETmiss < met_cut ) return !passed;
    PassedCut("LPLUSJETS", "reco_weighted", weight );
    PassedCut("LPLUSJETS", "reco_unweight");

    // 6 mTW > 30 GeV or mTW+ETmiss>60 GeV
    if( m_config->channel == kElectron ) {
       if( mwt < 30 * GeV) return !passed;
    }
    else {
       if( (mwt + ETmiss) < 60 * GeV ) return !passed;
    }
    PassedCut("LPLUSJETS", "reco_weighted", weight );
    PassedCut("LPLUSJETS", "reco_unweight");

    // 7 Njets >= 3
    if ( jet_n < 3 ) return !passed;
    PassedCut("LPLUSJETS", "reco_weighted", weight );
    PassedCut("LPLUSJETS", "reco_unweight");
    FillHistogramsControlPlotsReco( values );

//VS More Control Regions
    if (jet_n == 3 && bjet_n == 0) {
    MoreCRFillHistogramsControlPlotsReco( "3j_excl_0b_excl", values );
    }
    
    if (jet_n == 3 && bjet_n == 1) {
    MoreCRFillHistogramsControlPlotsReco( "3j_excl_1b_excl", values );
    }
    
    if (jet_n == 3 && bjet_n >= 2) {
    MoreCRFillHistogramsControlPlotsReco( "3j_excl_2b_incl", values );
    }


    if (jet_n >= 3 && bjet_n >= 0) {
    MoreCRFillHistogramsControlPlotsReco( "3j_incl_0b_incl", values );
    }

    if (jet_n >= 3 && bjet_n >= 1) {
    MoreCRFillHistogramsControlPlotsReco( "3j_incl_1b_incl", values );
    }

    if (jet_n >= 3 && bjet_n >= 2) {
    MoreCRFillHistogramsControlPlotsReco( "3j_incl_2b_incl", values );
    }

    
    if (jet_n == 4 && bjet_n == 0) {
    MoreCRFillHistogramsControlPlotsReco( "4j_excl_0b_excl", values );
    }
    
    if (jet_n == 4 && bjet_n == 1) {
    MoreCRFillHistogramsControlPlotsReco( "4j_excl_1b_excl", values );
    }

    if (jet_n == 4 && bjet_n >= 2) {
    MoreCRFillHistogramsControlPlotsReco( "4j_excl_2b_incl", values );
    }

    // 8 Njets >= 4    
    if ( jet_n < 4) return !passed;
    PassedCut("LPLUSJETS", "reco_weighted", weight );
    PassedCut("LPLUSJETS", "reco_unweight");
    FillHistogramsControlPlotsReco( values );

    // 9 Nbtags >= 1
    if (bjet_n < 1) return !passed;
    PassedCut("LPLUSJETS", "reco_weighted", weight );
    PassedCut("LPLUSJETS", "reco_unweight");

    FillHistogramsControlPlotsReco( values );

    // 10 Nbtags >= 2
    if (bjet_n < 2) return !passed;
    
    PassedCut("LPLUSJETS", "reco_weighted", weight );
    PassedCut("LPLUSJETS", "reco_unweight");

    FillHistogramsControlPlotsReco( values );

    if (jet_n >= 5 && bjet_n >= 0) {
    MoreCRFillHistogramsControlPlotsReco( "5j_incl_0b_incl", values );
    }

    if (jet_n >= 5 && bjet_n >= 1) {
    MoreCRFillHistogramsControlPlotsReco( "5j_incl_1b_incl", values );
    }

    if (jet_n >= 5 && bjet_n >= 2) {
    MoreCRFillHistogramsControlPlotsReco( "5j_incl_2b_incl", values );
    }

    return passed;
}

bool CutFlowTTbarResolved::PassedCutFlowParticle(EventData * ed) {    
    bool passed = true;

    const double weight = ed->property["weight_particle_level"];

    // const int hfor = int( ed->property["hfor"] );

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
    values.lep_pt  = ( ed->truth_leptons.n > 0 ) ?  ed->truth_leptons.pT.at(0)  : 0.;
    values.lep_eta = ( ed->truth_leptons.n > 0 ) ?  ed->truth_leptons.eta.at(0) : 0.;
    values.lep_phi = ( ed->truth_leptons.n > 0 ) ?  ed->truth_leptons.phi.at(0) : 0.;
    values.lep_E   = ( ed->truth_leptons.n > 0 ) ?  ed->truth_leptons.E.at(0)   : 0.;
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

    // if( (hfor<0) || (hfor>3) ) return passed;
    
    // 0 All events
    PassedCut( "LPLUSJETS", "particle_unweight" );
    PassedCut( "LPLUSJETS", "particle_weighted", weight );
//    FillHistogramsControlPlotsParticle( values );
    
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
    if (jet_n < 4) return !passed;
    PassedCut( "LPLUSJETS", "particle_unweight" );
    PassedCut( "LPLUSJETS", "particle_weighted", weight );
    FillHistogramsControlPlotsParticle( values );
  
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

double CutFlowTTbarResolved::GetFakesWeight( EventData * ed ) {

    double qcd_weight = 1.;
 
#ifndef __MOMA__

    cout << "WARNING: Cannot assign fake weights without ATLAS ROOTCORE. Please setup ROOTCORE and compile the MoMA extension." << endl;

#else
    int rc_channel = m_config->channel;

    MMEvent  rc_event;
    rc_event.njets = ed->jets.n;

    rc_event.ntag  = ed->bjets.n;
//    rc_event.ntag  = 0;
//    rc_event.ntag  = ( ed->bjets.n > 0 ) ? 1 : 0;

    rc_event.jetpt = ed->jets.pT.at(0) / GeV ; // leading jet (used only by electrons)
    rc_event.sumet = ed->MET.sumet / GeV;
    rc_event.met   = ed->MET.et / GeV;

    MMLepton rc_lepton;
    rc_lepton.pt  = ed->leptons.pT.at(0) / GeV;
    rc_lepton.eta = ( rc_channel == FakesWeights::EJETS ) ? ed->electrons.property["el_cl_eta"].at(0) : ed->muons.eta.at(0);
    rc_lepton.eta = fabs( rc_lepton.eta ); 
    
    double hthad        = 0.;
    double dR_lj_min    = 1e10; // distance between the electron and the closest jet
    double pTdR_lj_min  = 0.; //pT/dR (lepton-closest jet)
    for( size_t j = 0 ; j < ed->jets.n ; ++j ) {
	const double jet_pT = ed->jets.pT.at(j) / GeV;

	hthad += jet_pT;

        double dR_lj = PhysicsHelperFunctions::DeltaR( ed->leptons, 0, ed->jets, j );

        //cout << "Nj = " << ed->jets.n  << " j_ind = " << j << " dR_lj = " << dR_lj << " dR_lj_min = " << dR_lj_min << endl;

        if( dR_lj < dR_lj_min ) {
          dR_lj_min = dR_lj;

          pTdR_lj_min = jet_pT / dR_lj;
        }
    }
    rc_event.hthad    = hthad;
    rc_lepton.dR      = dR_lj_min;
    rc_lepton.dRpt    = pTdR_lj_min; 

    const double lep_phi = ed->leptons.phi.at(0);
    const double met_phi = ed->MET.phi;
    double dPhi          = PhysicsHelperFunctions::Phi_mphi_phi( lep_phi - met_phi );
    rc_lepton.dPhi       = fabs( dPhi );

    int trigger = ed->leptons.property["trigMatch"].at(0); // which trigger the lepton is mathced to, and it's value should be (use lep_trigMatch in MiniSL)
    rc_lepton.trigger = trigger;    // 1,2 or 3, or even adding the info on the prescaled trigger (so +4)

    bool tight = ( rc_channel == FakesWeights::EJETS ) ? ed->electrons.property["tight"].at(0) : ed->muons.property["tight"].at(0);

    // Finally..
    qcd_weight = m_moma->GetFakesWeight( rc_channel, rc_event, rc_lepton, tight );
//    qcd_weight = m_moma->GetFakesWeight( rc_channel, tight, rc_lepton.pt, rc_lepton.eta, fabs(rc_lepton.eta), rc_lepton.dR, rc_lepton.dRpt, rc_event.jetpt, rc_event.njets, rc_event.ntag, rc_lepton.trigger );

//    cout << "ch: " << rc_channel << " tight = " << tight << " pT = " << rc_lepton.pt << " |eta_l| = " << rc_lepton.eta << " dR_lj_min = " << rc_lepton.dR << " dPhi_l_MET = " << rc_lepton.dPhi << " trigger = " << rc_lepton.trigger << " SumET = " << rc_event.sumet << " QCD_w = " << qcd_weight << endl;
#endif  

    return qcd_weight;
}


void CutFlowTTbarResolved::FillHistogramsControlPlotsReco( ControlPlotValues& values )
{
    const int cut = GetLastPassedCut( "LPLUSJETS", "reco_weighted" ) - 1;    
    string path = "reco/cutflow/" + alias[cut] + "/";    
    FillHistograms(path, values);   
} 
  
//VS
void CutFlowTTbarResolved::MoreCRFillHistogramsControlPlotsReco( string mystr, ControlPlotValues& values )
{
    string path = "reco/cutflow/" + mystr + "/";
    FillHistograms(path, values);
}

void CutFlowTTbarResolved::FillHistogramsControlPlotsParticle( ControlPlotValues& values )
{    
    const int cut = GetLastPassedCut( "LPLUSJETS", "particle_weighted" ) - 1;    
    string path = "parton/cutflow/" + alias[cut] + "/";
    FillHistograms(path, values);
}

void CutFlowTTbarResolved::FillHistograms(string path, ControlPlotValues& values ){

    m_hm->FillHistograms( path + "mu",     values.mu,     values.weight );
    m_hm->FillHistograms( path + "pvxp_n", values.pvxp_n, values.weight );
    m_hm->FillHistograms( path + "vxp_z",  values.vxp_z,  values.weight );

    m_hm->FillHistograms( path + "lep_pt" , values.lep_pt / GeV, values.weight );
    m_hm->FillHistograms( path + "lep_eta", values.lep_eta, values.weight);
    m_hm->FillHistograms( path + "lep_phi", values.lep_phi,      values.weight );
    m_hm->FillHistograms( path + "lep_E" ,  values.lep_E / GeV,  values.weight );    
    m_hm->FillHistograms( path + "met_pt" ,  values.ETmiss / GeV, values.weight );
    m_hm->FillHistograms( path + "mtw" , values.mwt  / GeV, values.weight );

    double meff   = values.ETmiss + values.lep_pt;
    double jet_ht = 0.;

    m_hm->FillHistograms( path + "jet_n",  values.jet_n, values.weight );
    for (int j = 0; j < values.jets.size(); ++j) {
        JetValues* jet = values.jets.at(j);
        m_hm->FillHistograms( path + "jet_eta" ,  jet->eta, values.weight );
        m_hm->FillHistograms( path + "jet_pt",  jet->pt / GeV, values.weight );
        m_hm->FillHistograms( path + "jet_phi" , jet->phi, values.weight );
        m_hm->FillHistograms( path + "jet_E", jet->E / GeV, values.weight );
        m_hm->FillHistograms( path + "jet_m" ,  jet->m / GeV, values.weight );
       
        jet_ht += jet->pt;
        if( j < 4 ) meff += jet->pt;

//VS Jets classification Filling histos
        if (j==0){
        JetValues* jet1 = values.jets.at(j);
        m_hm->FillHistograms( path + "jet1_eta" ,  jet1->eta, values.weight );
        m_hm->FillHistograms( path + "jet1_pt",  jet1->pt / GeV, values.weight );  
        m_hm->FillHistograms( path + "jet1_m" ,  jet1->m / GeV, values.weight ); 
        }
        if (j==1){
        JetValues* jet2 = values.jets.at(j);
        m_hm->FillHistograms( path + "jet2_eta" ,  jet2->eta, values.weight );
        m_hm->FillHistograms( path + "jet2_pt",  jet2->pt / GeV, values.weight );
        m_hm->FillHistograms( path + "jet2_m" ,  jet2->m / GeV, values.weight );
        }
        if (j==2){
        JetValues* jet3 = values.jets.at(j);
        m_hm->FillHistograms( path + "jet3_eta" ,  jet3->eta, values.weight );
        m_hm->FillHistograms( path + "jet3_pt",  jet3->pt / GeV, values.weight );
        m_hm->FillHistograms( path + "jet3_m" ,  jet3->m / GeV, values.weight );
        }
        if (j==3){
        JetValues* jet1 = values.jets.at(0);
        JetValues* jet4 = values.jets.at(j);
        if (jet4->pt == jet1->pt){
        break;
        }
        m_hm->FillHistograms( path + "jet4_eta" ,  jet4->eta, values.weight );
        m_hm->FillHistograms( path + "jet4_pt",  jet4->pt / GeV, values.weight );
        m_hm->FillHistograms( path + "jet4_m" ,  jet4->m / GeV, values.weight ); 
       }        
    }
    double ht = values.ETmiss + values.lep_pt + jet_ht;

//    if( values.jets.size() > 0 )    m_hm->FillHistograms( path + "jet1_pt",  values.jets.at(0)->pt / GeV, values.weight );
    m_hm->FillHistograms( path + "jet_ht", jet_ht / GeV,   values.weight );
    m_hm->FillHistograms( path + "meff",   meff / GeV,     values.weight );
    m_hm->FillHistograms( path + "ht",     ht / GeV,       values.weight );

    m_hm->FillHistograms( path + "bjet_n", values.bjet_n, values.weight );
    for (int bj = 0; bj < values.bJets.size(); ++bj) {
        JetValues* jet = values.bJets.at(bj);
        m_hm->FillHistograms( path + "bjet_eta",  jet->eta, values.weight );
        m_hm->FillHistograms( path + "bjet_pt",  jet->pt / GeV, values.weight );
        m_hm->FillHistograms( path + "bjet_phi",  jet->phi, values.weight );
        m_hm->FillHistograms( path + "bjet_E",  jet->E / GeV, values.weight );
        m_hm->FillHistograms( path + "bjet_m",  jet->m / GeV, values.weight );
        if (bj==0){
        JetValues* jet1 = values.bJets.at(bj);
        m_hm->FillHistograms( path + "bjet1_eta" ,  jet1->eta, values.weight );   
        m_hm->FillHistograms( path + "bjet1_pt",  jet1->pt / GeV, values.weight );
        }
        if (bj==1){
        JetValues* jet2 = values.bJets.at(bj);
        m_hm->FillHistograms( path + "bjet2_eta" ,  jet2->eta, values.weight );
        m_hm->FillHistograms( path + "bjet2_pt",  jet2->pt / GeV, values.weight );
        }

    }   
//    if(	values.bJets.size() > 0 ) m_hm->FillHistograms( path + "bjet1_pt",  values.bJets.at(0)->pt / GeV, values.weight );
}

/////////////////////////////////////////



/////////////////////////////////////////
void CutFlowTTbarResolved::FillHistogramsPseudoTop(EventData::Reco_t& particle, int index, string level, string topType, const double weight, const double mlb){   
    Particle p(particle, index);
    m_hm->FillHistograms(level + "/4j2b/" + topType + "/pt", p.pt / GeV, weight);
    m_hm->FillHistograms(level + "/4j2b/" + topType + "/eta", p.eta, weight);
    m_hm->FillHistograms(level + "/4j2b/" + topType + "/phi", p.phi, weight);
    m_hm->FillHistograms(level + "/4j2b/" + topType + "/E", p.E / GeV, weight);
    m_hm->FillHistograms(level + "/4j2b/" + topType + "/m", p.m / GeV, weight);
    m_hm->FillHistograms(level + "/4j2b/" + topType + "/absrap", fabs(p.y), weight);
    m_hm->FillHistograms(level + "/4j2b/" + topType + "/rapidity", p.y, weight);

    if ( (index == 5 || index == 0) && mlb >= 0.){
        m_hm->FillHistograms(level + "/4j2b/" + topType + "/mlb", mlb / GeV , weight );
    }
}

/////////////////////////////////////////
void CutFlowTTbarResolved::FillHistogramsTopPairs(string path, TLorentzVector &topL, TLorentzVector &topH, TLorentzVector &ttSystem, NuData nudata, const double weight){
   
  // neutrino and discriminant diagnostics:
  if (nudata.v_pz > -KinemEdge) {
    //    cout << " v_pz=" << v_pz/GeV << " sign*D^{1/6}=" <<  D/TMath::Abs(D)*pow(TMath::Abs(D),1/6.) / GeV << endl;
    m_hm->FillHistograms(path + "neutrino_pz", nudata.v_pz / GeV, weight);
    m_hm->FillHistograms(path + "Discriminant", nudata.D/TMath::Abs(nudata.D)*pow(TMath::Abs(nudata.D),1/6.) / GeV, weight); // fill sixth-root of D, keep sign

    if (nudata.v_pz_truth > -KinemEdge)
      m_hm->FillMatrices(path + "neutrino_pz_vs_neutrino_pz_truth", nudata.v_pz_truth / GeV, nudata.v_pz / GeV, weight);
    
  }

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

   // top pT dPt as function of pT average:
   m_hm->FillMatrices(path + "dTopPt_vs_AverTopPt", 0.5*(topH.Pt() + topL.Pt()) / GeV, (topH.Pt() - topL.Pt()) / GeV, weight);
   m_hm->FillMatrices(path + "dTopPt_vs_AverTopPt", 0.5*(topH.Pt() + topL.Pt()) / GeV, (topL.Pt() - topH.Pt()) / GeV, weight);
   m_hm->FillMatrices(path + "dTopPtLH_vs_AverTopPt", 0.5*(topH.Pt() + topL.Pt()) / GeV, (topL.Pt() - topH.Pt()) / GeV, weight);
   m_hm->FillMatrices(path + "dTopPtLH_vs_TopLPt", topL.Pt() / GeV, (topL.Pt() - topH.Pt()) / GeV, weight);
   m_hm->FillMatrices(path + "dTopPtLH_vs_TopHPt", topH.Pt() / GeV, (topL.Pt() - topH.Pt()) / GeV, weight);
 
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

   m_hm->FillHistograms(path + "dPhi_ttbar", DeltaPhi, weight);
   // two entries per event:
   m_hm->FillMatrices(path + "Salam_ttbar_vs_dPhi_ttbar", DeltaPhi, Delta1, weight);
   m_hm->FillMatrices(path + "Salam_ttbar_vs_dPhi_ttbar", DeltaPhi, Delta2, weight);
   m_hm->FillHistograms(path + "Salam_ttbar", Delta1, weight);
   m_hm->FillHistograms(path + "Salam_ttbar", Delta2, weight);

   // TODO: fill HT!


 }

/////////////////////////////////////////
void CutFlowTTbarResolved::FillHistogramsPseudoTopPairs(EventData::Reco_t& particle, int indexL, int indexH, int indextt, string level, NuData nudata, const double weight){

  Particle ptopL(particle, indexL);
  Particle ptopH(particle, indexH);
  Particle pttSystem(particle, indextt);
  
  TLorentzVector topL = ptopL.MakeLorentz();
  TLorentzVector topH = ptopH.MakeLorentz();
  TLorentzVector ttSystem = pttSystem.MakeLorentz();
  
  string path = level + "/4j2b/difference/";

  FillHistogramsTopPairs(path, topL, topH, ttSystem, nudata, weight);

 
  

}
/////////////////////////////////////////
void CutFlowTTbarResolved::FillHistogramsPartonTop(EventData::Truth_t& particle, int index, string level, string topType, const double weight){   
  Particle p(particle, index);
  m_hm->FillHistograms(level + "/4j2b/" + topType + "/pt", p.pt / GeV, weight);
  m_hm->FillHistograms(level + "/4j2b/" + topType + "/eta", p.eta, weight);
  m_hm->FillHistograms(level + "/4j2b/" + topType + "/phi", p.phi, weight);
  m_hm->FillHistograms(level + "/4j2b/" + topType + "/E", p.E / GeV, weight);
  m_hm->FillHistograms(level + "/4j2b/" + topType + "/m", p.m / GeV, weight);
  m_hm->FillHistograms(level + "/4j2b/" + topType + "/absrap", fabs(p.y), weight);
  m_hm->FillHistograms(level + "/4j2b/" + topType + "/rapidity", p.y, weight);
}


void CutFlowTTbarResolved::FillHistogramsPartonTopPairs(EventData::Truth_t& particle, int indexL, int indexH, int indextt, string level, const double weight){   
  Particle ptopL(particle, indexL);
  Particle ptopH(particle, indexH);
  Particle pttSystem(particle, indextt);

  TLorentzVector topL = ptopL.MakeLorentz();
  TLorentzVector topH = ptopH.MakeLorentz();
  TLorentzVector ttSystem = pttSystem.MakeLorentz();

  string path = level + "/4j2b/difference/";
  // dummy zeros for neutrino pz and discriminant...
  NuData nudata;
  FillHistogramsTopPairs(path, topL, topH, ttSystem, nudata, weight);

}

/////////////////////////////////////////
void CutFlowTTbarResolved::FillHistogramsPseudotopReco( EventData * ed, const double weight, string level) {

  if ( ((m_config->channel == kElectron and ed->electrons.n > 0) or (m_config->channel == kMuon and ed->muons.n > 0))
       and ed->jets.n > ed->iproperty["reco_pseudotop_lep_bjet_index"]) {
    TLorentzVector lep_bjet = HelperFunctions::MakeFourMomentum(ed->jets, ed->iproperty["reco_pseudotop_lep_bjet_index"]);
    TLorentzVector lep;
    if (m_config->channel == kElectron)
      lep = HelperFunctions::MakeFourMomentum( ed->electrons, 0 );
    else
      lep = HelperFunctions::MakeFourMomentum( ed->muons, 0 );
    TLorentzVector lb = lep + lep_bjet;
    // fill mbl = m_{bl}
    //    cout << " RECO mlb: " << lb.M() << endl;
    FillHistogramsPseudoTop(ed->reco, 0, level, "topL", weight, lb.M());
  } else {
    cout << " CAN'T FILL RECO mlb! n_el: " << ed->electrons.n << " n_mu: " <<  ed->muons.n 
	 << " n_bjets: " <<  ed->bjets.n 
	 << " b_index: " << ed->iproperty["reco_pseudotop_lep_bjet_index"]
	 << endl;
    FillHistogramsPseudoTop(ed->reco, 0, level, "topL", weight, -1);
  }
    FillHistogramsPseudoTop(ed->reco, 1, level, "topH", weight);
    FillHistogramsPseudoTop(ed->reco, 2, level, "tt", weight);
    FillHistogramsPseudoTop(ed->reco, 3, level, "WL", weight);
    FillHistogramsPseudoTop(ed->reco, 4, level, "WH", weight);

    NuData nudata;
    nudata.v_pz = ed->property["reco_v_pz"];
    nudata.v_pz_1 = ed->property["reco_v_pz_1"];
    nudata.v_pz_2 = ed->property["reco_v_pz_2"];
    nudata.D = ed->property["reco_D"];

    FillHistogramsPseudoTopPairs(ed->reco, 0, 1, 2, level, nudata, weight);

}


/////////////////////////////////////////

void CutFlowTTbarResolved::FillHistogramsPseudotopParticle( EventData * ed, const double weight, string level) {


  if ( ( (m_config->channel == kMuon and ed->truth_muons.n > 0) or (m_config->channel == kElectron and ed->truth_electrons.n > 0))
       and ed->truth_jets.n > ed->iproperty["ptcl_pseudotop_lep_bjet_index"])
    {
    TLorentzVector lep_bjet = HelperFunctions::MakeFourMomentum(ed->truth_jets, ed->iproperty["ptcl_pseudotop_lep_bjet_index"]);
    TLorentzVector lep;
    if (m_config->channel == kElectron) {
      if (ed->truth_electrons.n > 0)
	lep = HelperFunctions::MakeFourMomentum(ed->truth_electrons, 0);
    } else {
      if (ed->truth_muons.n > 0)
	lep = HelperFunctions::MakeFourMomentum(ed->truth_muons, 0);
    }
    TLorentzVector lb = lep + lep_bjet;
    //    cout << " PTCL mlb: " << lb.M() << endl;
    FillHistogramsPseudoTop(ed->reco, 5, level, "topL", weight, lb.M());
  } else {
    cout << " CAN'T FILL PTCL mlb! n_el: " << ed->truth_electrons.n << " n_mu: " <<  ed->truth_muons.n 
	 << " n_bjets: " <<  ed->truth_bjets.n
	 << " b_index: " << ed->iproperty["ptcl_pseudotop_lep_bjet_index"]
	 << endl;
    
    FillHistogramsPseudoTop(ed->reco, 5, level, "topL", weight, -1);
  }
    FillHistogramsPseudoTop(ed->reco, 6, level, "topH", weight);
    FillHistogramsPseudoTop(ed->reco, 7, level, "tt", weight);
    FillHistogramsPseudoTop(ed->reco, 8, level, "WL", weight);
    FillHistogramsPseudoTop(ed->reco, 9, level, "WH", weight);


    NuData nudata;
    nudata.v_pz = ed->property["ptcl_v_pz"];
    nudata.v_pz_1 = ed->property["ptcl_v_pz_1"];
    nudata.v_pz_2 = ed->property["ptcl_v_pz_2"];
    nudata.v_pz_truth = ed->property["ptcl_v_pz_truth"];
    nudata.D = ed->property["ptcl_D"];

    /*
      cout << "Particle: "
      << " v_pz=" << v_pz
      << " D=" << D
      << endl;
    */

    FillHistogramsPseudoTopPairs(ed->reco, 5, 6, 7, level, nudata, weight);

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
    
    FillHistogramsPartonTop(ed->mctruth, ilep, "parton", "topL", weight);
    FillHistogramsPartonTop(ed->mctruth, ihad, "parton", "topH", weight);
    FillHistogramsPartonTop(ed->mctruth, itt, "parton", "tt", weight);   
    FillHistogramsPartonTopPairs(ed->mctruth, ilep, ihad, itt, "parton", weight);   

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

    Particle particleTopL(ed->reco, 5);
    Particle particleTopH(ed->reco, 6);
    Particle particleTT(ed->reco, 7);

    //    m_hm->FillHistograms("reco/4j2b/difference/topH/ptdiff", (recoTopH.pt - particleTopH.pt) / GeV, weight);
    
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
    m_hm->FillMatrices( path + "_m", px.m  / GeV, py.m  / GeV, weight);
    m_hm->FillMatrices( path + "_absrap", fabs(px.y), fabs(py.y), weight);
    m_hm->FillMatrices( path + "_rapidity", px.y, py.y, weight);
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
    Particle particleTopL(ed->reco, 5);
    Particle particleTopH(ed->reco, 6);
    Particle particleTT(ed->reco, 7);

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

