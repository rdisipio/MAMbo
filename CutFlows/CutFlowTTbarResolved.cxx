#include "CutFlowTTbarResolved.h"
CutFlowTTbarResolved::CutFlowTTbarResolved() 
{
    m_pseudotop_reco = new PseudoTopReconstruction();
    m_pseudotop_particle = new PseudoTopReconstruction();
    
    m_pseudotop_matching_reco2particle   = new PseudoTopMatching( PseudoTopMatching::kRecoToParticle );
    m_pseudotop_matching_reco2parton     = new PseudoTopMatching( PseudoTopMatching::kRecoToParton );
    m_pseudotop_matching_particle2parton = new PseudoTopMatching( PseudoTopMatching::kParticleToParton );
    
    m_alias = {
      "beforeCuts", "trig", "pvtx", "lep", "pTlep", "met", "mtw", "3j0b", "4j0b", "4j1b", "afterCuts"
    };


#ifdef __MOMA__
   m_moma = MoMATool::GetHandle();
   cout << "INFO: ATLAS ROOTCORE detected. MoMA tool initialized." << endl;
#endif

#ifdef __USE_LHAPDF__
   m_pdf = NULL;
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

#ifdef __USE_LHAPDF__
   SAFE_DELETE( m_pdf );
#endif

}  

/////////////////////////////////////////

bool CutFlowTTbarResolved::Initialize() {
    bool success = true;

    // just for info purposes here:
    int isMCSignal = (int) m_config->custom_params_flag["isMCSignal"];
    int isDilepton = (int) m_config->custom_params_flag["isDilepton"];
    cout << "INFO: signal flags: " << " isMCSignal=" << isMCSignal << " isDilepton=" << isDilepton << endl;

    unsigned long isRealData = m_config->custom_params_flag["isRealData"];
    unsigned long isWjets    = m_config->custom_params_flag["isWjets"];
    unsigned long isQCD      = m_config->custom_params_flag["isQCD"];

	
    if( m_config->custom_params_string.count( "scale_syst" ) ) {

        const string syst = m_config->custom_params_string["scale_syst"];

        cout << "INFO: Scale factor systematic: " << syst << endl;

#ifdef __MOMA__
        m_syst_type = NOMINAL;

        if( syst == "NOMINAL" )            m_syst_type = NOMINAL;
        else if( syst == "BTAGSFUP" )      m_syst_type = BTAGSFUP;
        else if( syst == "BTAGSFDOWN" )    m_syst_type = BTAGSFDOWN;
        else if( syst == "CTAUTAGSFUP" )   m_syst_type = CTAUTAGSFUP;
        else if( syst == "CTAUTAGSFDOWN" ) m_syst_type = CTAUTAGSFDOWN;    
        else if( syst == "MISTAGSFUP" )    m_syst_type = MISTAGSFUP;
        else if( syst == "MISTAGSFDOWN" )  m_syst_type = MISTAGSFDOWN;    
        else if( syst == "QCD_MM_EL_FAKE_MC_UP" )     m_syst_type = QCD_MM_EL_FAKE_MC_UP;
        else if( syst == "QCD_MM_EL_FAKE_MC_DOWN" )   m_syst_type = QCD_MM_EL_FAKE_MC_DOWN;
      	else if( syst == "QCD_MM_EL_FAKE_ALTERNATE" ) m_syst_type = QCD_MM_EL_FAKE_ALTERNATE;
      	else if( syst == "QCD_MM_EL_REAL_ALTERNATE" ) m_syst_type = QCD_MM_EL_REAL_ALTERNATE;
      	else if( syst == "QCD_MM_EL_PAR_ALTERNATE" )  m_syst_type = QCD_MM_EL_PAR_ALTERNATE;    
      	else if( syst == "QCD_MM_MU_FAKE_MC_UP" )     m_syst_type = QCD_MM_MU_FAKE_MC_UP;    
      	else if( syst == "QCD_MM_MU_FAKE_MC_DOWN" )   m_syst_type = QCD_MM_MU_FAKE_MC_DOWN;    
      	else if( syst == "QCD_MM_MU_FAKE_ALTERNATE" ) m_syst_type = QCD_MM_MU_FAKE_ALTERNATE;    
      	else if( syst == "QCD_MM_MU_REAL_ALTERNATE" ) m_syst_type = QCD_MM_MU_REAL_ALTERNATE;      
      	else if( syst == "QCD_MM_MU_PAR_ALTERNATE" )  m_syst_type = QCD_MM_MU_PAR_ALTERNATE;     

//	else throw runtime_error( "CutFlowTTbarResolved::Initialize(): Invalid scale factor systematic\n" );

        m_moma->SetSystematicType( m_syst_type );

#endif /* __MOMA__ */

        if( syst.find("PDF") == 0 ) {
#ifndef __USE_LHAPDF__
             throw runtime_error( "Requested systematic shift of type PDF but LHAPDF is not set. Please recompile against LHAPDF.\n" );
#else
             StringVector_t params_pdf;
             HelperFunctions::Tokenize( syst, params_pdf, ":" );
 	     if( params_pdf.size() != 3 ) throw runtime_error( "PDF parameters malformed. Format should be PDF:SET:VARIATION\n" ); 

             cout << "INFO: PDF reweighting on-the-fly: set: " << params_pdf[1] << " variation: " << params_pdf[2]  << endl; 

             int imem = atoi( params_pdf[2].c_str() );
             m_pdf = LHAPDF::mkPDF( params_pdf[1], imem );

#endif /* __USE_LHAPDF__ */
        } // PDF

    }    

    //m_rand = new TRandom3(12345);
    m_rand = new TRandom3( 0 );
 
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
    const unsigned long isDilepton = m_config->custom_params_flag["isDilepton"];
    const unsigned long isRealData = m_config->custom_params_flag["isRealData"];
    const unsigned long isWjets    = m_config->custom_params_flag["isWjets"];
    const unsigned long isQCD      = m_config->custom_params_flag["isQCD"];
    unsigned long isStressTest = 0;
    string stressTestType = "none";
	
    if( m_config->custom_params_string.count( "stressTest" ) ) //mr
	{
        stressTestType = m_config->custom_params_string["stressTest"];
		if( stressTestType != "none" && stressTestType != "tt_pt" && stressTestType != "tt_m" && stressTestType != "tt_rapidity" && stressTestType != "top_pt" )
		{
			cout << "Warning: stress test type " << stressTestType << " is unknown, setting it to \"none\"\n";
			stressTestType = "none";
		}
		else if(  stressTestType != "none" ) isStressTest = 1;
	}

    double weight_reco_level     = 1.;
    double weight_particle_level = 1.;

    if( !isRealData && !isQCD ) {
         weight_reco_level     = ed->info.mcWeight;
         weight_particle_level = ed->info.mcWeight;

		 if( isStressTest )//mr
		 {
              TLorentzVector t1 = Particle(ed->mctruth, 0).MakeLorentz();
              TLorentzVector t2 = Particle(ed->mctruth, 1).MakeLorentz();
              TLorentzVector tt = t1 + t2;
			  if( stressTestType == "tt_rapidity" )
			  {
				  //Rapidity gaussian reweight
				  weight_reco_level *= 1 - 0.4 * TMath::Exp( -1 * pow( tt.Rapidity()/0.3, 2) );
				  weight_particle_level *= 1 - 0.4 * TMath::Exp( -1 * pow( tt.Rapidity()/0.3, 2) );
			  }
			  else if( stressTestType == "tt_m" )
			  {
				  //         Mass bump"
				  double delta = tt.M() - 800000;
				  double sigma = 100000;
				  weight_reco_level *= 1 + 2 * TMath::Exp( -1 * pow( delta/sigma, 2) );
				  weight_particle_level *= 1 + 2*TMath::Exp( -1 *  pow( delta/sigma, 2) );
			  }
			  else if( stressTestType == "tt_pt" )
			  {
				  // tt pt slope
				  weight_particle_level *= 1 + tt.Pt() / 400000;
				  weight_reco_level *= 1 + tt.Pt() / 400000;
			  }
			  else
			  {
				  //top pt slope
				  weight_particle_level *= 1 + ( t1.Pt() + t2.Pt())/ 1500000; //average of the pt
				  weight_reco_level *= 1 + ( t1.Pt() + t2.Pt())/ 1500000; //average of the pt
			  }
		 }

         ROOT_TH1_t * h = (ROOT_TH1_t*)m_hm->GetHistogram( "reco/cutflow/3j0b/MC_gen_weights" );
         h->Fill( weight_reco_level );
         h = (ROOT_TH1_t*)m_hm->GetHistogram( "particle/cutflow/3j0b/MC_gen_weights" );
         h->Fill( weight_particle_level );
 	 h = NULL;

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
//         const double scaleFactor_BTAG       = ( m_syst_type == NOMINAL ) ? ed->property["scaleFactor_BTAG"] : m_moma->GetBTagWeight( ed, 0.7892, m_syst_type ); 
//         const double scaleFactor_BTAG_ntup  = ed->property["scaleFactor_BTAG"]; 
//         cout << "DEBUG: btagsf(OTF) = " << scaleFactor_BTAG << "  |  btagsf(NTUP) = " << scaleFactor_BTAG_ntup << endl;
#else 
         const double scaleFactor_BTAG       = ed->property["scaleFactor_BTAG"];
#endif

         
#ifdef __USE_LHAPDF__
         const double scaleFactor_PDF  = GetPDFWeight( ed );
         weight_reco_level     *= scaleFactor_PDF;
         weight_particle_level *= scaleFactor_PDF;
#else 
        const double scaleFactor_PDF = 1.0;
#endif


       weight_reco_level *=
            scaleFactor_PILEUP * scaleFactor_TRIGGER * scaleFactor_JVFSF * scaleFactor_ZVERTEX *
            scaleFactor_ELE * scaleFactor_MUON *
            scaleFactor_BTAG;

   	 // as boosted guys do
         // weight_particle_level *= scaleFactor_PILEUP * scaleFactor_ZVERTEX;
    }

    //if( isWjets ) { }

    if( isQCD ) {
      double qcd_weight = GetFakesWeight( ed );
      m_hm->GetHistogram( "reco/cutflow/3j0b/fakes_weights" )->Fill( qcd_weight );
      m_hm->GetHistogram( "reco/cutflow/3j0b/fakes_weights_1" )->Fill( qcd_weight );

      if( fabs(qcd_weight) > 3.0 ) qcd_weight = 0.; // see https://twiki.cern.ch/twiki/bin/view/AtlasProtected/TopMatrixMethod

      weight_reco_level     *= qcd_weight;
      weight_particle_level *= qcd_weight; // should we?
    }

// @ BOOTSTRAP
//    double pw = -1.;
//    while( pw <= 0. ) pw = m_rand->Poisson( 1. );
//    weight_reco_level     *= pw;
//    weight_particle_level *= pw;
//    cout << "DEBUG: bootstrap event " << ed->info.eventNumber << "  poiss w = " << pw << endl;
// @ BOOTSTRAP


    ed->property["weight_particle_level"] = weight_particle_level;
    ed->property["weight_reco_level"]     = weight_reco_level;

#ifdef __CHECKDUPLICATES__
    if( m_eventIds.count( ed->info.eventNumber ) == 0 ) {
       m_eventIds.insert( ed->info.eventNumber );
    }
    else {
       cout << "WARNING: duplicated event " << ed->info.eventNumber << endl;
       return success;
    }
#endif


    // dileptonic filter; JK, RDS
    // flag set in EventDumpers/EventDumperMCTruthTopMiniSLResolved.h
    int EventIsDileptonic = ed->property["isDileptonic"];
    //cout << "DEBUG: EventIsDileptonic = " << EventIsDileptonic << endl;

    if( isMCSignal ) {
       if( ( isDilepton == 0 ) && ( EventIsDileptonic == 1 ) ) return success;
    }

    /*
    // ljets filter
    if( isMCSignal && ( isDilepton >= 0 ) ) {
      if ( EventIsDileptonic < 0 ) {
	cout << "WARNING: event " << ed->info.eventNumber << " isDileptonic flag not initialized" << endl;
	return 0; 
      }
      if( ( isDilepton == 0 ) && ( EventIsDileptonic == 1 ) ) { 
	// cout << "INFO: event " << ed->info.eventNumber << " isDileptonic" << endl; 
	return success; 
      }
      if( ( isDilepton == 1 ) && ( EventIsDileptonic != 1 ) ) { 
	// cout << "INFO: event " << ed->info.eventNumber << " isDileptonic" << endl; 
	return success; 
      }
    }
*/

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
    bool splitSample =  m_config->custom_params_string.count("splitSample");

    if (isMCSignal) {
      if (ed->mctruth.n <= 0) {
	cout << "ERROR: CutFlowTTbarResolved::FillHistogramsPseudotopParton event has too few top quarks in the MC event record!" << endl;
	return success;
      }
    }

    bool isMonoJetW_particle = false;
    bool isMonoJetW_reco = false;
    
    if (isMCSignal and splitSample) {
      bool splitSampleInvert =  false;
      if (m_config->custom_params_string.count("splitSampleInvert"))
	splitSampleInvert = not (m_config->custom_params_string["splitSampleInvert"] == "0" or m_config->custom_params_string["splitSampleInvert"] == "false");
      // cout << "splitSample and Invert? " << splitSample << " " << splitSampleInvert << endl;
      fillHistos =   (m_rand -> Integer(2)); // this or not;)
      if (splitSampleInvert)
	fillHistos = not fillHistos;

      //      fillCorrections = not fillHistos;
      // we cannot simply fill EITHER corrections or histograms, as some variables needed fro corrections are COMPUTED and CACHED only in histograms filling!
      // jk April 2015
      // so we need to KEEP or SKIP:
      if (not fillHistos)
	return success;
    }


    if( passedRecoSelection ) {
     
      //     need to repeat... ???
      m_pseudotop_reco->SetEventData(ed);
      m_pseudotop_reco->SetTarget(PseudoTopReconstruction::kReco);
      
      m_pseudotop_reco->SetChargedLepton(m_config->channel, 0);
      isMonoJetW_reco = m_pseudotop_reco->Run();
      m_VarField["reco_HT_pseudo"] = m_pseudotop_reco->GetHt();
      m_VarField["reco_R_lb"] = m_pseudotop_reco->GetR_lb();
      m_VarField["reco_R_Wb_had"] = m_pseudotop_reco->GetR_Wb_had();
      m_VarField["reco_R_Wb_lep"] = m_pseudotop_reco->GetR_Wb_lep();

      // naming conventions:

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

    if( (!isMCSignal) || (isDilepton==1) )
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
      isMonoJetW_particle = m_pseudotop_particle->Run(); 
      m_VarField["particle_HT_pseudo"] = m_pseudotop_particle->GetHt();
      m_VarField["particle_R_lb"] = m_pseudotop_particle->GetR_lb();
      m_VarField["particle_R_Wb_had"] = m_pseudotop_particle->GetR_Wb_had();
      m_VarField["particle_R_Wb_lep"] = m_pseudotop_particle->GetR_Wb_lep();
     
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
	    m_VarField["reco_and_particle_r_HT_pseudo"] = m_pseudotop_reco->GetHt();
	    m_VarField["reco_and_particle_r_R_lb"] = m_pseudotop_reco->GetR_lb();
	    m_VarField["reco_and_particle_r_R_Wb_had"] = m_pseudotop_reco->GetR_Wb_had();
	    m_VarField["reco_and_particle_r_R_Wb_lep"] = m_pseudotop_reco->GetR_Wb_lep();
	    
	  if (passedDRMatching) {
	    m_VarField["matched_r_HT_pseudo"] = m_pseudotop_reco->GetHt();
	    m_VarField["matched_r_R_lb"] = m_pseudotop_reco->GetR_lb();
	    m_VarField["matched_r_R_Wb_had"] = m_pseudotop_reco->GetR_Wb_had();
	    m_VarField["matched_r_R_Wb_lep"] = m_pseudotop_reco->GetR_Wb_lep();

	    m_VarField["matched_p_HT_pseudo"] = m_pseudotop_particle->GetHt();
	    m_VarField["matched_p_R_lb"] = m_pseudotop_particle->GetR_lb();
	    m_VarField["matched_p_R_Wb_had"] = m_pseudotop_particle->GetR_Wb_had();
	    m_VarField["matched_p_R_Wb_lep"] = m_pseudotop_particle->GetR_Wb_lep();
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


bool CutFlowTTbarResolved::Finalize()
{
   bool success = true;

/*
   unsigned long isQCD = m_config->custom_params_flag["isQCD"];
   if( !isQCD ) return success;
*/

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
    values.lep_q   = ed->leptons.q.at(0);
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
    //if( ETmiss < met_cut ) return !passed;
    PassedCut("LPLUSJETS", "reco_weighted", weight );
    PassedCut("LPLUSJETS", "reco_unweight");

    // 6 mTW > 30 GeV or mTW+ETmiss>60 GeV
/*
    if( m_config->channel == kElectron ) {
       if( mwt < 30 * GeV) return !passed;
    }
    else {
       if( (mwt + ETmiss) < 60 * GeV ) return !passed;
    }
*/
    PassedCut("LPLUSJETS", "reco_weighted", weight );
    PassedCut("LPLUSJETS", "reco_unweight");

    FillHistogramsDiagnostics( values );

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

    if (jet_n >= 5 && bjet_n >= 0) {
    MoreCRFillHistogramsControlPlotsReco( "5j_incl_0b_incl", values );
    }
 
    if (jet_n >= 5 && bjet_n >= 1) {
    MoreCRFillHistogramsControlPlotsReco( "5j_incl_1b_incl", values );
    }
        
    if (jet_n >= 5 && bjet_n >= 2) {
    MoreCRFillHistogramsControlPlotsReco( "5j_incl_2b_incl", values );
    }

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

    // flush jet values
    for(auto &it:values.jets) delete it; values.jets.clear();
    for(auto &it:values.bJets) delete it; values.bJets.clear();

    return passed;
}

/////////////////////////////////////////

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
    if ((el_n > 0) && (mu_n == 0)) {
      values.lep_pt  = ( ed->truth_electrons.n > 0 ) ?  ed->truth_electrons.pT.at(0)  : 0.;
      values.lep_eta = ( ed->truth_electrons.n > 0 ) ?  ed->truth_electrons.eta.at(0) : 0.;
      values.lep_phi = ( ed->truth_electrons.n > 0 ) ?  ed->truth_electrons.phi.at(0) : 0.;
      values.lep_E   = ( ed->truth_electrons.n > 0 ) ?  ed->truth_electrons.E.at(0)   : 0.;}
    else if ((el_n == 0) && (mu_n > 0)) {
      values.lep_pt  = ( ed->truth_muons.n > 0 ) ?  ed->truth_muons.pT.at(0)  : 0.;
      values.lep_eta = ( ed->truth_muons.n > 0 ) ?  ed->truth_muons.eta.at(0) : 0.;
      values.lep_phi = ( ed->truth_muons.n > 0 ) ?  ed->truth_muons.phi.at(0) : 0.;
      values.lep_E   = ( ed->truth_muons.n > 0 ) ?  ed->truth_muons.E.at(0)   : 0.;
    } else {
      //      cerr << "CutFlowTTbarResolved::PassedCutFlowParticle: THIS SHOULD NEVER HAPPEN!" << endl;
    }

    values.jet_n   = ed->truth_jets.n;
    values.bjet_n  = ed->truth_bjets.n; 
    values.fjet_n  = ed->truth_fjets.n;
    values.ETmiss  = ed->MET_truth.et;
    values.mwt     = ed->MET_truth.mwt;

    for (int j = 0; j < ed->truth_jets.n; ++j) {
        JetValues* jet = new JetValues();
        jet->pt  = ed->truth_jets.pT.at(j);
        jet->eta = ed->truth_jets.eta.at(j);
        jet->phi = ed->truth_jets.phi.at(j);
        jet->E   = ed->truth_jets.E.at(j);
        jet->m   = ed->truth_jets.m.at(j); 
        values.jets.push_back(jet);
    }
    for (int bj = 0; bj < ed->truth_bjets.n; ++bj) {
        JetValues* jet = new JetValues();
        jet->pt  = ed->truth_bjets.pT.at(bj);
        jet->eta = ed->truth_bjets.eta.at(bj);
        jet->phi = ed->truth_bjets.phi.at(bj);
        jet->E   = ed->truth_bjets.E.at(bj);
        jet->m   = ed->truth_bjets.m.at(bj);
        values.bJets.push_back(jet);
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
//    if( ETmiss < met_cut ) return !passed;
    PassedCut("LPLUSJETS", "particle_weighted", weight );
    PassedCut("LPLUSJETS", "particle_unweight");

    // 6 mTW > 30 GeV or mTW+ETmiss>60 GeV
/* 
    if( m_config->channel == kElectron ) {
       if( mwt < 30 * GeV) return !passed;
    }
    else {
       if( (mwt + ETmiss) < 60 * GeV ) return !passed;
    }
*/
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

    // flush jet values
    for(auto &it:values.jets) delete it; values.jets.clear();
    for(auto &it:values.bJets) delete it; values.bJets.clear();
    
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

        double dR_lj = ( rc_channel == FakesWeights::EJETS ) ? 
                       PhysicsHelperFunctions::DeltaR( ed->electrons, 0, ed->jets, j ) :
                       PhysicsHelperFunctions::DeltaR( ed->muons, 0, ed->jets, j );                       
 
        //cout << "Nj = " << ed->jets.n  << " j_ind = " << j << " dR_lj = " << dR_lj << " dR_lj_min = " << dR_lj_min << endl;

        if( dR_lj < dR_lj_min ) {
          dR_lj_min   = dR_lj;
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


////////////////////////////////////////////////


double CutFlowTTbarResolved::GetPDFWeight( EventData * ed )
{
   double weight = 1.0;

#ifndef __USE_LHAPDF__
   cout << "WARNING: You asked to calculate the PDF weight but MAMbo was not compiled against LHAPDF." << endl;
   return weight;
#else

   if( m_pdf == NULL ) return weight;
   
   const double pdf1 = ed->property["pdf_pdf1"];
   const double	id1  = ed->property["pdf_id1"];
   const double  x1  = ed->property["pdf_x1"];
   const double	pdf2 = ed->property["pdf_pdf2"];
   const double	id2  = ed->property["pdf_id2"];
   const double x2   = ed->property["pdf_x2"];
   const double q    = ed->property["pdf_scale"];

   const double new_pdf1 = m_pdf->xfxQ( id1, x1, q );
   const double new_pdf2 = m_pdf->xfxQ( id2, x2, q );

   weight = (new_pdf1*new_pdf2) / (pdf1*pdf2);

#endif

   return weight;
}


////////////////////////////////////////////////


void CutFlowTTbarResolved::FillHistogramsControlPlotsReco( ControlPlotValues& values )
{
    const int cut = GetLastPassedCut( "LPLUSJETS", "reco_weighted" ) - 1;    
    string path = "reco/cutflow/" + m_alias[cut] + "/";    
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
    string path = "particle/cutflow/" + m_alias[cut] + "/";
    FillHistograms(path, values);
}

void CutFlowTTbarResolved::FillHistogramsDiagnostics( ControlPlotValues& values )
{
    const int cut = GetLastPassedCut( "LPLUSJETS", "reco_weighted" ) - 1;
    if( cut > 8 ) return;

    string hpath = "reco/cutflow/3j0b/flav_comp";

    int nj_min = 2;
    int nb_min = 0;
    int nj_max = 4;
    int nb_max = 2;

    int kj = ( nj_max - nj_min + 1 );

    int nb  = min( values.bjet_n, nb_max );
    int nj  = min( values.jet_n,  nj_max );
    int lq  = ( values.lep_q > 0 ) ? 1 : 10;

   
    // q  1 1 1 1 1 1 1 1 1 -1 -1 -1 -1 -1 -1 -1 -1 -1
    // j  2 2 2 3 3 3 4 4 4  2  2  2  3  3  3  4  4  4
    // b  0 1 2 0 1 2 0 1 2  0  1  2  0  1  2  0  1  2
    // -----------------------------------------------
    // i  1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 

    // q=1 nj=3 nb=1 -> i=5
    // q=-1 nj=4 nb=0 -> i=16

    int bin = lq + ( nj - nj_min ) * kj + ( nb - nb_min ); 

//    cout << "DEBUG: wjets diagnostics: l=" << values.lep_q << " nb=" << values.bjet_n << " nj=" << values.jet_n << " -> bin=" << bin << endl;

    ROOT_TH1_t * h = (ROOT_TH1_t*)m_hm->GetHistogram( hpath );
    if( !h ) throw runtime_error("CutFlowTTbarResolved::FillHistogramsDiagnostics(): Invalid path to histogram flav_comp");

    h->Fill( bin, values.weight );

    hpath = "reco/cutflow/3j0b/flav_comp_excl";
    h = (ROOT_TH1_t*)m_hm->GetHistogram( hpath );
    if( !h ) throw runtime_error("CutFlowTTbarResolved::FillHistogramsDiagnostics(): Invalid path to histogram flav_comp_excl");
    nj_max = 5;
    lq  = ( values.lep_q > 0 ) ? 1 : nj_max;
    nj = min( values.jet_n, nj_max );
    bin = lq + ( nj - nj_min );
    h->Fill( bin, values.weight );

    hpath = "reco/cutflow/3j0b/flav_comp_incl";
    if( !h ) throw runtime_error("CutFlowTTbarResolved::FillHistogramsDiagnostics(): Invalid path to histogram flav_comp_incl");
    h = (ROOT_TH1_t*)m_hm->GetHistogram( hpath );
    for( int z = nj_min ; z <= nj_max ; ++z ) {
       if( z > nj ) continue;

       bin = lq + ( z - nj_min );
       h->Fill( bin, values.weight );
    }
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
void CutFlowTTbarResolved::FillHistogramsPseudoTop(EventData::Reco_t& particle, int index, string level, string topType, const double weight,const double mlb){   
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
void CutFlowTTbarResolved::FillHistogramsTopPairs(string level, TLorentzVector &topL, TLorentzVector &topH, TLorentzVector &ttSystem,TLorentzVector &WL,TLorentzVector &WH, NuData nudata, const double weight){
  
  string path = level + "/4j2b/difference/";
  // neutrino and discriminant diagnostics:
  if (nudata.v_pz > -KinemEdge) {
    //    cout << " v_pz=" << v_pz/GeV << " sign*D^{1/6}=" <<  D/TMath::Abs(D)*pow(TMath::Abs(D),1/6.) / GeV << endl;
    m_hm->FillHistograms(path + "neutrino_pz", nudata.v_pz / GeV, weight);
    m_hm->FillHistograms(path + "Discriminant", nudata.D / GeV, weight); // fill sixth-root of D, keep sign
    m_hm->FillMatrices(path + "neutrino_pz_vs_neutrino_pz_truth", nudata.v_pz_truth / GeV, nudata.v_pz / GeV, weight);
  }

   double topH_pT = topH.Pt();
   double topL_pT = topL.Pt();
   double topH_y  = topH.Rapidity();
   double topL_y  = topL.Rapidity();

   m_VarField[level+"_topH_pt"] = topH_pT / GeV;
   m_VarField[level+"_topL_pt"] = topL_pT / GeV;
   m_VarField[level+"_topH_y"] = topH_y;
   m_VarField[level+"_topL_y"] = topL_y;

   // Out-of-plane momentum Pout
   TVector3 top1 = topL.Vect();
   TVector3 top2 = topH.Vect();

   TVector3 zUnit(0., 0., 1.);
   TVector3 perp = zUnit.Cross( top1 );

   const double pout = top2.Dot( perp ) / perp.Mag();

   m_VarField[level+"_Pout"] = pout;
   m_hm->FillHistograms( path + "Pout", pout / GeV, weight );
     //    if (_fillSpecial2D) m_hm->FillHistograms(path + "SystemPtVsPout", pout, ttSystem.Pt());
   
   // top quark pT ratio
   const double z_ttbar = topH_pT / topL_pT;
   m_VarField[level+"_z_ttbar"] = z_ttbar;
   m_hm->FillHistograms(path + "z_ttbar", z_ttbar, weight);

   // top pT dPt as function of pT average:
   m_hm->FillMatrices( path + "dTopPt_vs_AverTopPt",   0.5*(topH_pT + topL_pT) / GeV, (topH_pT - topL_pT) / GeV, weight );
   m_hm->FillMatrices( path + "dTopPt_vs_AverTopPt",   0.5*(topH_pT + topL_pT) / GeV, (topL_pT - topH_pT) / GeV, weight );
   m_hm->FillMatrices( path + "dTopPtLH_vs_AverTopPt", 0.5*(topH_pT + topL_pT) / GeV, (topL_pT - topH_pT) / GeV, weight );
   m_hm->FillMatrices( path + "dTopPtLH_vs_TopLPt",    topL_pT / GeV,                 (topL_pT - topH_pT) / GeV, weight );
   m_hm->FillMatrices( path + "dTopPtLH_vs_TopHPt",    topH_pT / GeV,                 (topL_pT - topH_pT) / GeV, weight );
    
   // chi = exp |y1-y2|
   // alison lister: leading top - subleading top
   const double ystar    = ( topH_pT > topL_pT ) ? 0.5 * ( topH_y - topL_y ) : 0.5 * ( topL_y - topH_y );
   const double chittbar = exp( 2. * fabs( ystar ) );
   m_hm->FillHistograms(path + "Chi_ttbar", chittbar , weight);
   m_VarField[level+"_Chi_ttbar"]=chittbar;
   //  if (_fillSpecial2D) m_hm->FillHistograms(path + "SystemPtVsChittbar", chittbar, ttSystem.Pt());
   m_hm->FillMatrices( path + "Chi_ttbar_vs_mtt", ttSystem.M()/GeV, chittbar, weight );  
   m_hm->FillHistograms(path + "Ystar_ttbar", ystar, weight );
   m_hm->FillMatrices( path + "Ystar_ttbar_vs_mtt", ttSystem.M()/GeV, ystar, weight );
   //cout << "DEBUG: mtt = " << ttSystem.M()/GeV << " Xtt = " << chittbar << " w = " << weight << endl;

   // y_boost
   const double yboost = 0.5*(TMath::Abs(topL_y + topH_y));
   m_VarField[level+"_Yboost"]=yboost;
   m_hm->FillHistograms(path + "Yboost", yboost , weight);
   // if (_fillSpecial2D) m_hm->FillHistograms(path + "SystemPtVsYboost", yboost, ttSystem.Pt());

   // ttbar cos theta *
   TVector3 SystemVec = ttSystem.Vect(); // need this for the boost
   TLorentzVector TopLCMS;
   TopLCMS.SetPtEtaPhiE(topL_pT, topL.Eta(), topL.Phi(), topL.E());
   TLorentzVector TopHCMS;
   TopHCMS.SetPtEtaPhiE(topH_pT, topH.Eta(), topH.Phi(), topH.E());

   // w.r.t. beam axis:
   TVector3 boostVec = - (ttSystem.BoostVector()); // boost back to the original frame
   TopLCMS.Boost(0., 0., boostVec.Z());
   TopHCMS.Boost(0., 0., boostVec.Z());
   const double TopLCosThetaStar = cos(TopLCMS.Theta());
   const double TopHCosThetaStar = cos(TopHCMS.Theta());
   // JK: fill just one of these? Should be complements to Pi, anyway...
   m_hm->FillHistograms(path + "topLCosThetaStar", TopLCosThetaStar, weight);
   m_hm->FillHistograms(path + "topHCosThetaStar", TopHCosThetaStar, weight);

   // opening angle in lab:
   TVector3 TopLVec = topL.Vect();
   TVector3 TopHVec = topH.Vect();
   const double TopCosAngle = TopLVec.Dot(TopHVec) / ((TopHVec.Mag())*(TopLVec.Mag()));
   m_hm->FillHistograms(path + "TopCosOpeningAngle", TopCosAngle, weight);


   // variables by Gavin Salam:
   double HT_ttbar = topH_pT + topL_pT;
   m_VarField[level+"_HT_ttbar"] = HT_ttbar;
   m_hm->FillHistograms( path + "HT_ttbar", HT_ttbar / GeV, weight );

   const double S_ttbar  = ( topH_pT > topL_pT ) ? ( 3 * topH_pT - topL_pT ) / HT_ttbar : ( 3 * topL_pT - topH_pT ) / HT_ttbar;
   m_VarField[level+"_Salam_ttbar"] = S_ttbar;
   m_hm->FillHistograms(path + "Salam_ttbar", S_ttbar, weight);

   double DeltaPhi = TMath::Abs(topL.DeltaPhi(topH));
   m_VarField[level+"_dPhi"] = DeltaPhi;
   m_hm->FillHistograms(path + "dPhi_ttbar", DeltaPhi, weight);

   // dPhi_ttbar vs S_ttbar (boost regions)
   m_hm->FillMatrices(path + "Salam_ttbar_vs_dPhi_ttbar", DeltaPhi, S_ttbar, weight );

   // pT asymmetry
//   const double PtAsymm_ttbar = ( topH_pT > topL_pT ) ? ( topH_pT - topL_pT ) / HT_ttbar : ( topL_pT - topH_pT ) / HT_ttbar;
   const double PtAsymm_ttbar = ( topH_pT - topL_pT ) / HT_ttbar;
   m_VarField[level+"_PtAsymm_ttbar"] = PtAsymm_ttbar;
   m_hm->FillHistograms(path + "PtAsymm_ttbar", PtAsymm_ttbar, weight );   

   //px, py, pz
   m_VarField[level+"_pxL"] = topL.Px();
   m_VarField[level+"_pyL"] = topL.Py();
   m_VarField[level+"_pzL"] = topL.Pz();

   m_VarField[level+"_pxH"] = topH.Px();
   m_VarField[level+"_pyH"] = topH.Py();
   m_VarField[level+"_pzH"] = topH.Pz();
   
   //W gymnastics
   if (!(level=="parton")){
     m_VarField[level+"_R_Wt_lep"] = WL.Pt()/topL_pT;
     m_VarField[level+"_R_Wt_had"] = WH.Pt()/topH_pT;
     m_hm->FillHistograms(path+"R_Wt_had",m_VarField.find(level + "_R_Wt_had")->second, weight);
     m_hm->FillHistograms(path+"R_Wt_lep",m_VarField.find(level + "_R_Wt_lep")->second, weight);
     m_hm->FillHistograms(path+"R_lb",m_VarField.find(level + "_R_lb")->second, weight);
     m_hm->FillHistograms(path+"mlb",m_VarField.find(level + "_mlb")->second, weight);
     m_hm->FillHistograms(path+"R_Wb_had",m_VarField.find(level + "_R_Wb_had")->second, weight);
     m_hm->FillHistograms(path+"R_Wb_lep",m_VarField.find(level + "_R_Wb_lep")->second, weight);
     m_hm->FillHistograms(path+"HT_pseudo",m_VarField.find(level + "_HT_pseudo")->second / GeV, weight);
 }
}

/////////////////////////////////////////
void CutFlowTTbarResolved::FillHistogramsPseudoTopPairs(EventData::Reco_t& particle, int indexL, int indexH, int indextt, string level, NuData nudata, const double weight){
 
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
  
  FillHistogramsTopPairs(level, topL, topH, ttSystem, WL, WH, nudata, weight);
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
  TLorentzVector WL;
  TLorentzVector WH;

  NuData nudata;
  
  FillHistogramsTopPairs(level, topL, topH, ttSystem, WL, WH, nudata, weight);

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
    m_VarField["reco_mlb"] = lb.M();
  // fill mbl = m_{bl}
      //  cout << " RECO mlb: " << lb.M()/GeV<< endl;
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
    
    Particle pTopL(ed->reco,0);
    Particle pTopH(ed->reco,1);
    Particle pWL(ed->reco,3);
    Particle pWH(ed->reco,4);
    
    
    
    m_hm->FillMatrices("reco/4j2b/difference/WL_m_vs_WH_m", pWH.m / GeV, pWL.m / GeV, weight );
    m_hm->FillMatrices("reco/4j2b/difference/TopL_m_vs_TopH_m", pTopH.m / GeV, pTopL.m / GeV, weight );
    m_hm->FillMatrices("reco/4j2b/difference/TopH_m_vs_WH_m", pWH.m / GeV, pTopH.m / GeV, weight );
    m_hm->FillMatrices("reco/4j2b/difference/TopL_m_vs_WL_m", pWL.m / GeV, pTopL.m / GeV, weight );
 //   m_hm->FillMatrices("reco/4j2b/difference/TopHPt_vs_Numjets", ed->jets.n, pTopH.pt / GeV, weight );
 //   m_hm->FillMatrices("reco/4j2b/difference/TopLPt_vs_Numjets", ed->jets.n, pTopL.pt / GeV, weight );

    NuData nudata;
    nudata.v_pz = ed->property["reco_v_pz"];
    nudata.v_pz_1 = ed->property["reco_v_pz_1"];
    nudata.v_pz_2 = ed->property["reco_v_pz_2"];
    nudata.D = ed->property["reco_D"];
    nudata.D = nudata.D/TMath::Abs(nudata.D)*pow(TMath::Abs(nudata.D),1/6.);
    m_VarField[level + "_" + "Discriminant"] = nudata.D;

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
    m_VarField["particle_mlb"] = lb.M();
     //   cout << " PTCL mlb: " << lb.M() << endl;
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
    
    
    
    Particle pTopL(ed->reco,5);
    Particle pTopH(ed->reco,6);
    Particle pWL(ed->reco,8);
    Particle pWH(ed->reco,9);
    
    m_hm->FillMatrices("particle/4j2b/difference/WL_m_vs_WH_m", pWH.m / GeV, pWL.m / GeV, weight );
    m_hm->FillMatrices("particle/4j2b/difference/TopL_m_vs_TopH_m", pTopH.m / GeV, pTopL.m / GeV, weight );
    m_hm->FillMatrices("particle/4j2b/difference/TopH_m_vs_WH_m", pWH.m / GeV, pTopH.m / GeV, weight );
    m_hm->FillMatrices("particle/4j2b/difference/TopL_m_vs_WL_m", pWL.m / GeV, pTopL.m / GeV, weight );
   // m_hm->FillMatrices("particle/4j2b/difference/TopHPt_vs_Numjets", ed->jets.n, pTopH.pt / GeV, weight );
  //  m_hm->FillMatrices("particle/4j2b/difference/TopLPt_vs_Numjets", ed->jets.n, pTopL.pt / GeV, weight );

    NuData nudata;
    nudata.v_pz = ed->property["ptcl_v_pz"];
    nudata.v_pz_1 = ed->property["ptcl_v_pz_1"];
    nudata.v_pz_2 = ed->property["ptcl_v_pz_2"];
    nudata.v_pz_truth = ed->property["ptcl_v_pz_truth"];
    nudata.D = ed->property["ptcl_D"];
    nudata.D = nudata.D/TMath::Abs(nudata.D)*pow(TMath::Abs(nudata.D),1/6.);
    m_VarField[level + "_" + "Discriminant"] = nudata.D;

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

   const bool isHadronicW = ed->mctruth.property["isHadronicW"].at(0);
   int ilepW, ihadW;
    if( isHadronicW ) {
        ihadW = 3;
        ilepW = 4;
    }
    else {
        ihadW = 4;
        ilepW = 3;
    }

    FillHistogramsPartonTop(ed->mctruth, ilep, "parton", "topL", weight);
    FillHistogramsPartonTop(ed->mctruth, ihad, "parton", "topH", weight);
    FillHistogramsPartonTop(ed->mctruth, itt, "parton", "tt", weight);   
    FillHistogramsPartonTop(ed->mctruth, ilepW, "parton", "WL", weight);
    FillHistogramsPartonTop(ed->mctruth, ihadW, "parton", "WH", weight);
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
    Particle recoWL(ed->reco, 3);
    Particle recoWH(ed->reco, 4);

    Particle particleTopL(ed->reco, 5);
    Particle particleTopH(ed->reco, 6);
    Particle particleTT(ed->reco, 7);
    Particle particleWL(ed->reco, 8);
    Particle particleWH(ed->reco, 9);

    FillMatrix("reco/4j2b/topL/Matrix_reco_particle", recoTopL, particleTopL, weight);
    FillMatrix("reco/4j2b/topH/Matrix_reco_particle", recoTopH, particleTopH, weight);
    FillMatrix("reco/4j2b/tt/Matrix_reco_particle", recoTT, particleTT, weight);
    FillMatrix("reco/4j2b/WL/Matrix_reco_particle", recoWL, particleWL, weight);
    FillMatrix("reco/4j2b/WH/Matrix_reco_particle", recoWH, particleWH, weight);    

    FillMatrix("particle/4j2b/topL/Matrix_particle_reco", particleTopL, recoTopL, weight);
    FillMatrix("particle/4j2b/topH/Matrix_particle_reco", particleTopH, recoTopH, weight);
    FillMatrix("particle/4j2b/tt/Matrix_particle_reco", particleTT, recoTT, weight);
    FillMatrix("particle/4j2b/WL/Matrix_particle_reco", particleWL, recoWL, weight);
    FillMatrix("particle/4j2b/WH/Matrix_particle_reco", particleWH, recoWH, weight);
   
    m_hm->FillMatrices("reco/4j2b/difference/Matrix_reco_particle_Discriminant", m_VarField.find("reco_Discriminant")->second / GeV, m_VarField.find("particle_Discriminant")->second / GeV, weight);
    m_hm->FillMatrices("reco/4j2b/difference/Matrix_reco_particle_Pout",m_VarField.find("reco_Pout")->second / GeV, m_VarField.find("particle_Pout")->second / GeV, weight);
    m_hm->FillMatrices("reco/4j2b/difference/Matrix_reco_particle_z_ttbar",m_VarField.find("reco_z_ttbar")->second, m_VarField.find("particle_z_ttbar")->second, weight);
    m_hm->FillMatrices("reco/4j2b/difference/Matrix_reco_particle_Yboost",m_VarField.find("reco_Yboost")->second ,m_VarField.find("particle_Yboost")->second, weight);
    m_hm->FillMatrices("reco/4j2b/difference/Matrix_reco_particle_dPhi_ttbar",m_VarField.find("reco_dPhi")->second ,m_VarField.find("particle_dPhi")->second, weight);
    m_hm->FillMatrices("reco/4j2b/difference/Matrix_reco_particle_HT_ttbar",m_VarField.find("reco_HT_ttbar")->second / GeV, m_VarField.find("particle_HT_ttbar")->second / GeV, weight);
    m_hm->FillMatrices("reco/4j2b/difference/Matrix_reco_particle_HT_pseudo",m_VarField.find("reco_HT_pseudo")->second / GeV, m_VarField.find("particle_HT_pseudo")->second / GeV, weight);
    m_hm->FillMatrices("reco/4j2b/difference/Matrix_reco_particle_Chi_ttbar",m_VarField.find("reco_Chi_ttbar")->second, m_VarField.find("particle_Chi_ttbar")->second, weight);
    m_hm->FillMatrices("reco/4j2b/difference/Matrix_reco_particle_Salam_ttbar",m_VarField.find("reco_Salam_ttbar")->second, m_VarField.find("particle_Salam_ttbar")->second, weight);
    m_hm->FillMatrices("reco/4j2b/topL/Matrix_reco_particle_px",m_VarField.find("reco_pxL")->second / GeV, m_VarField.find("particle_pxL")->second / GeV, weight);
    m_hm->FillMatrices("reco/4j2b/topH/Matrix_reco_particle_px",m_VarField.find("reco_pxH")->second / GeV, m_VarField.find("particle_pxH")->second / GeV, weight);
    m_hm->FillMatrices("reco/4j2b/topL/Matrix_reco_particle_py",m_VarField.find("reco_pyL")->second / GeV, m_VarField.find("particle_pyL")->second / GeV, weight);
    m_hm->FillMatrices("reco/4j2b/topH/Matrix_reco_particle_py",m_VarField.find("reco_pyH")->second / GeV, m_VarField.find("particle_pyH")->second / GeV, weight);
    m_hm->FillMatrices("reco/4j2b/topL/Matrix_reco_particle_pz",m_VarField.find("reco_pzL")->second / GeV, m_VarField.find("particle_pzL")->second / GeV, weight);
    m_hm->FillMatrices("reco/4j2b/topH/Matrix_reco_particle_pz",m_VarField.find("reco_pzH")->second / GeV, m_VarField.find("particle_pzH")->second / GeV, weight);
    m_hm->FillMatrices("reco/4j2b/difference/Matrix_reco_particle_R_Wt_lep", m_VarField.find("reco_R_Wt_lep")->second, m_VarField.find("particle_R_Wt_lep")->second, weight);
    m_hm->FillMatrices("reco/4j2b/difference/Matrix_reco_particle_R_Wt_had", m_VarField.find("reco_R_Wt_had")->second, m_VarField.find("particle_R_Wt_had")->second, weight);
    m_hm->FillMatrices("reco/4j2b/topL/Matrix_reco_particle_mlb", m_VarField.find("reco_mlb")->second / GeV, m_VarField.find("particle_mlb")->second / GeV, weight);
    m_hm->FillMatrices("reco/4j2b/difference/Matrix_reco_particle_R_lb", m_VarField.find("reco_R_lb")->second, m_VarField.find("particle_R_lb")->second, weight);
    m_hm->FillMatrices("reco/4j2b/difference/Matrix_reco_particle_R_Wb_had", m_VarField.find("reco_R_Wb_had")->second, m_VarField.find("particle_R_Wb_had")->second, weight);
    m_hm->FillMatrices("reco/4j2b/difference/Matrix_reco_particle_R_Wb_lep", m_VarField.find("reco_R_Wb_lep")->second, m_VarField.find("particle_R_Wb_lep")->second, weight);

    
    m_hm->FillMatrices("particle/4j2b/difference/Matrix_particle_reco_Discriminant", m_VarField.find("particle_Discriminant")->second / GeV, m_VarField.find("reco_Discriminant")->second / GeV, weight);    
    m_hm->FillMatrices("particle/4j2b/difference/Matrix_particle_reco_Pout",m_VarField.find("particle_Pout")->second / GeV, m_VarField.find("reco_Pout")->second / GeV, weight);
    m_hm->FillMatrices("particle/4j2b/difference/Matrix_particle_reco_z_ttbar",m_VarField.find("particle_z_ttbar")->second, m_VarField.find("reco_z_ttbar")->second, weight);
    m_hm->FillMatrices("particle/4j2b/difference/Matrix_particle_reco_Yboost",m_VarField.find("particle_Yboost")->second, m_VarField.find("reco_Yboost")->second, weight);
    m_hm->FillMatrices("particle/4j2b/difference/Matrix_particle_reco_dPhi_ttbar",m_VarField.find("particle_dPhi")->second, m_VarField.find("reco_dPhi")->second, weight);
    m_hm->FillMatrices("particle/4j2b/difference/Matrix_particle_reco_HT_ttbar",m_VarField.find("particle_HT_ttbar")->second / GeV, m_VarField.find("reco_HT_ttbar")->second / GeV, weight);
    m_hm->FillMatrices("particle/4j2b/difference/Matrix_particle_reco_HT_pseudo",m_VarField.find("particle_HT_pseudo")->second / GeV, m_VarField.find("reco_HT_pseudo")->second / GeV, weight);
    m_hm->FillMatrices("particle/4j2b/difference/Matrix_particle_reco_Chi_ttbar",m_VarField.find("particle_Chi_ttbar")->second, m_VarField.find("reco_Chi_ttbar")->second, weight);
    m_hm->FillMatrices("particle/4j2b/difference/Matrix_particle_reco_Salam_ttbar",m_VarField.find("particle_Salam_ttbar")->second, m_VarField.find("reco_Salam_ttbar")->second, weight);
    m_hm->FillMatrices("particle/4j2b/topL/Matrix_particle_reco_px",m_VarField.find("particle_pxL")->second / GeV, m_VarField.find("reco_pxL")->second / GeV, weight);
    m_hm->FillMatrices("particle/4j2b/topH/Matrix_particle_reco_px",m_VarField.find("particle_pxH")->second / GeV, m_VarField.find("reco_pxH")->second / GeV, weight);
    m_hm->FillMatrices("particle/4j2b/topL/Matrix_particle_reco_py",m_VarField.find("particle_pyL")->second / GeV, m_VarField.find("reco_pyL")->second / GeV, weight);
    m_hm->FillMatrices("particle/4j2b/topH/Matrix_particle_reco_py",m_VarField.find("particle_pyH")->second / GeV, m_VarField.find("reco_pyH")->second / GeV, weight);
    m_hm->FillMatrices("particle/4j2b/topL/Matrix_particle_reco_pz",m_VarField.find("particle_pzL")->second / GeV, m_VarField.find("reco_pzL")->second / GeV, weight);
    m_hm->FillMatrices("particle/4j2b/topH/Matrix_particle_reco_pz",m_VarField.find("particle_pzH")->second / GeV, m_VarField.find("reco_pzH")->second / GeV, weight);
    m_hm->FillMatrices("particle/4j2b/difference/Matrix_particle_reco_R_Wt_lep", m_VarField.find("particle_R_Wt_lep")->second, m_VarField.find("reco_R_Wt_lep")->second, weight);
    m_hm->FillMatrices("particle/4j2b/difference/Matrix_particle_reco_R_Wt_had", m_VarField.find("particle_R_Wt_had")->second, m_VarField.find("reco_R_Wt_had")->second, weight);
    m_hm->FillMatrices("particle/4j2b/topL/Matrix_particle_reco_mlb", m_VarField.find("particle_mlb")->second / GeV, m_VarField.find("reco_mlb")->second / GeV, weight);
    m_hm->FillMatrices("particle/4j2b/difference/Matrix_particle_reco_R_lb", m_VarField.find("particle_R_lb")->second, m_VarField.find("reco_R_lb")->second, weight);
    m_hm->FillMatrices("particle/4j2b/difference/Matrix_particle_reco_R_Wb_had", m_VarField.find("particle_R_Wb_had")->second, m_VarField.find("reco_R_Wb_had")->second, weight);
    m_hm->FillMatrices("particle/4j2b/difference/Matrix_particle_reco_R_Wb_lep", m_VarField.find("particle_R_Wb_lep")->second, m_VarField.find("reco_R_Wb_lep")->second, weight);

}
 
  void CutFlowTTbarResolved::FillMatrix(string path, Particle& px, Particle& py, double weight){
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
     Particle recoWL(ed->reco, 3);
     Particle recoWH(ed->reco, 4);

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

   const bool isHadronicW = ed->mctruth.property["isHadronicW"].at(0);
   int ilepW, ihadW;
    if( isHadronicW ) {
        ihadW = 3;
        ilepW = 4;
    }
    else {
        ihadW = 4;
        ilepW = 3;
    }
    
     Particle partonTopL(ed->mctruth, ilep);
     Particle partonTopH(ed->mctruth, ihad);
     Particle partonTT(ed->mctruth, itt);
     Particle partonWL(ed->mctruth, ilepW);
     Particle partonWH(ed->mctruth, ihadW);

    
    //  reco > parton
     FillMatrix("reco/4j2b/topL/Matrix_reco_parton", recoTopL, partonTopL, weight);
     FillMatrix("reco/4j2b/topH/Matrix_reco_parton", recoTopH, partonTopH, weight);
     FillMatrix("reco/4j2b/tt/Matrix_reco_parton", recoTT, partonTT, weight);
//     FillMatrix("reco/4j2b/tt/Matrix_reco_parton", recoTT, partonTT, weight); // was filled twice??
     FillMatrix("reco/4j2b/WL/Matrix_reco_parton", recoWL, partonWL, weight);
     FillMatrix("reco/4j2b/WH/Matrix_reco_parton", recoWH, partonWH, weight);

     FillMatrix("parton/4j2b/topL/Matrix_parton_reco", partonTopL, recoTopL, weight);
     FillMatrix("parton/4j2b/topH/Matrix_parton_reco", partonTopH, recoTopH, weight);
     FillMatrix("parton/4j2b/tt/Matrix_parton_reco", partonTT, recoTT, weight);
     FillMatrix("parton/4j2b/WL/Matrix_parton_reco", partonWL, recoWL, weight);
     FillMatrix("parton/4j2b/WH/Matrix_parton_reco", partonWH, recoWH, weight);
     
     m_hm->FillMatrices("reco/4j2b/difference/Matrix_reco_parton_Pout",m_VarField.find("reco_Pout")->second / GeV, m_VarField.find("parton_Pout")->second / GeV, weight);
     m_hm->FillMatrices("reco/4j2b/difference/Matrix_reco_parton_z_ttbar",m_VarField.find("reco_z_ttbar")->second, m_VarField.find("parton_z_ttbar")->second, weight);
     m_hm->FillMatrices("reco/4j2b/difference/Matrix_reco_parton_Yboost",m_VarField.find("reco_Yboost")->second, m_VarField.find("parton_Yboost")->second, weight);
     m_hm->FillMatrices("reco/4j2b/difference/Matrix_reco_parton_dPhi_ttbar",m_VarField.find("reco_dPhi")->second, m_VarField.find("parton_dPhi")->second, weight);
     m_hm->FillMatrices("reco/4j2b/difference/Matrix_reco_parton_HT_ttbar",m_VarField.find("reco_HT_ttbar")->second / GeV, m_VarField.find("parton_HT_ttbar")->second / GeV, weight);
     m_hm->FillMatrices("reco/4j2b/difference/Matrix_reco_parton_Chi_ttbar",m_VarField.find("reco_Chi_ttbar")->second, m_VarField.find("parton_Chi_ttbar")->second, weight);
     m_hm->FillMatrices("reco/4j2b/difference/Matrix_reco_parton_Salam_ttbar",m_VarField.find("reco_Salam_ttbar")->second, m_VarField.find("parton_Salam_ttbar")->second, weight);
     m_hm->FillMatrices("reco/4j2b/topH/Matrix_reco_parton_px",m_VarField.find("reco_pxH")->second / GeV, m_VarField.find("parton_pxH")->second / GeV, weight);
     m_hm->FillMatrices("reco/4j2b/topL/Matrix_reco_parton_py",m_VarField.find("reco_pyL")->second / GeV, m_VarField.find("parton_pyL")->second / GeV, weight);
     m_hm->FillMatrices("reco/4j2b/topH/Matrix_reco_parton_py",m_VarField.find("reco_pyH")->second / GeV, m_VarField.find("parton_pyH")->second / GeV, weight);
     m_hm->FillMatrices("reco/4j2b/topL/Matrix_reco_parton_pz",m_VarField.find("reco_pzL")->second / GeV, m_VarField.find("parton_pzL")->second / GeV, weight);
     m_hm->FillMatrices("reco/4j2b/topH/Matrix_reco_parton_pz",m_VarField.find("reco_pzH")->second / GeV, m_VarField.find("parton_pzH")->second / GeV, weight);
    
    m_hm->FillMatrices("parton/4j2b/difference/Matrix_parton_reco_Pout",m_VarField.find("parton_Pout")->second / GeV, m_VarField.find("reco_Pout")->second / GeV, weight);
    m_hm->FillMatrices("parton/4j2b/difference/Matrix_parton_reco_z_ttbar",m_VarField.find("parton_z_ttbar")->second, m_VarField.find("reco_z_ttbar")->second, weight);
    m_hm->FillMatrices("parton/4j2b/difference/Matrix_parton_reco_Yboost",m_VarField.find("parton_Yboost")->second ,m_VarField.find("reco_Yboost")->second, weight);
    m_hm->FillMatrices("parton/4j2b/difference/Matrix_parton_reco_dPhi_ttbar",m_VarField.find("parton_dPhi")->second, m_VarField.find("reco_dPhi")->second, weight);
    m_hm->FillMatrices("parton/4j2b/difference/Matrix_parton_reco_HT_ttbar",m_VarField.find("parton_HT_ttbar")->second / GeV, m_VarField.find("reco_HT_ttbar")->second / GeV, weight);
    m_hm->FillMatrices("parton/4j2b/difference/Matrix_parton_reco_Chi_ttbar",m_VarField.find("parton_Chi_ttbar")->second, m_VarField.find("reco_Chi_ttbar")->second, weight);
    m_hm->FillMatrices("parton/4j2b/difference/Matrix_parton_reco_Salam_ttbar",m_VarField.find("parton_Salam_ttbar")->second, m_VarField.find("reco_Salam_ttbar")->second, weight);
    m_hm->FillMatrices("parton/4j2b/topL/Matrix_parton_reco_px",m_VarField.find("parton_pxL")->second / GeV, m_VarField.find("reco_pxL")->second / GeV, weight);
    m_hm->FillMatrices("parton/4j2b/topH/Matrix_parton_reco_px",m_VarField.find("parton_pxH")->second / GeV, m_VarField.find("reco_pxH")->second / GeV, weight);
    m_hm->FillMatrices("parton/4j2b/topL/Matrix_parton_reco_py",m_VarField.find("parton_pyL")->second / GeV, m_VarField.find("reco_pyL")->second / GeV, weight);
    m_hm->FillMatrices("parton/4j2b/topH/Matrix_parton_reco_py",m_VarField.find("parton_pyH")->second / GeV, m_VarField.find("reco_pyH")->second / GeV, weight);
    m_hm->FillMatrices("parton/4j2b/topL/Matrix_parton_reco_pz",m_VarField.find("parton_pzL")->second / GeV, m_VarField.find("reco_pzL")->second / GeV, weight);
    m_hm->FillMatrices("parton/4j2b/topH/Matrix_parton_reco_pz",m_VarField.find("parton_pzH")->second / GeV, m_VarField.find("reco_pzH")->second / GeV, weight);    
    

 }
  
  void CutFlowTTbarResolved::FillHistogramsPseudotopResponseParticleToParton(  EventData * ed, const double weight )
  {
    // particle level
    Particle particleTopL(ed->reco, 5);
    Particle particleTopH(ed->reco, 6);
    Particle particleTT(ed->reco, 7);
    Particle particleWL(ed->reco, 8);
    Particle particleWH(ed->reco, 9);

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

  const bool isHadronicW = ed->mctruth.property["isHadronicW"].at(0);
   int ilepW, ihadW;
    if( isHadronicW ) {
        ihadW = 3;
        ilepW = 4;
    }
    else {
        ihadW = 4;
        ilepW = 3;
    }

    Particle partonTopL(ed->mctruth, ilep);
    Particle partonTopH(ed->mctruth, ihad);
    Particle partonTT(ed->mctruth, itt);
    Particle partonWL(ed->mctruth, ilepW);
    Particle partonWH(ed->mctruth, ihadW);
    
    // particle > parton
    FillMatrix("particle/4j2b/topL/Matrix_particle_parton", particleTopL, partonTopL, weight);
    FillMatrix("particle/4j2b/topH/Matrix_particle_parton", particleTopH, partonTopH, weight);
    FillMatrix("particle/4j2b/tt/Matrix_particle_parton", particleTT, partonTT, weight);
    FillMatrix("particle/4j2b/WL/Matrix_particle_parton", particleWL, partonWL, weight);
    FillMatrix("particle/4j2b/WH/Matrix_particle_parton", particleWH, partonWH, weight);

    FillMatrix("parton/4j2b/topL/Matrix_parton_particle", partonTopL, particleTopL, weight);
    FillMatrix("parton/4j2b/topH/Matrix_parton_particle", partonTopH, particleTopH, weight);
    FillMatrix("parton/4j2b/tt/Matrix_parton_particle", partonTT, particleTT, weight);
    FillMatrix("parton/4j2b/WL/Matrix_parton_particle", partonWL, particleWL, weight);
    FillMatrix("parton/4j2b/WH/Matrix_parton_particle", partonWH, particleWH, weight);
    
    m_hm->FillMatrices("parton/4j2b/difference/Matrix_parton_particle_Pout",m_VarField.find("parton_Pout")->second / GeV, m_VarField.find("particle_Pout")->second / GeV, weight);
    m_hm->FillMatrices("parton/4j2b/difference/Matrix_parton_particle_z_ttbar",m_VarField.find("parton_z_ttbar")->second, m_VarField.find("particle_z_ttbar")->second, weight);
    m_hm->FillMatrices("parton/4j2b/difference/Matrix_parton_particle_Yboost",m_VarField.find("parton_Yboost")->second ,m_VarField.find("particle_Yboost")->second, weight);
    m_hm->FillMatrices("parton/4j2b/difference/Matrix_parton_particle_dPhi_ttbar",m_VarField.find("parton_dPhi")->second, m_VarField.find("particle_dPhi")->second, weight);
    m_hm->FillMatrices("parton/4j2b/difference/Matrix_parton_particle_HT_ttbar",m_VarField.find("parton_HT_ttbar")->second / GeV, m_VarField.find("particle_HT_ttbar")->second / GeV, weight);
    m_hm->FillMatrices("parton/4j2b/difference/Matrix_parton_particle_Chi_ttbar",m_VarField.find("parton_Chi_ttbar")->second, m_VarField.find("particle_Chi_ttbar")->second, weight);
    m_hm->FillMatrices("parton/4j2b/difference/Matrix_parton_particle_Salam_ttbar",m_VarField.find("parton_Salam_ttbar")->second, m_VarField.find("particle_Salam_ttbar")->second, weight);
    m_hm->FillMatrices("parton/4j2b/topL/Matrix_parton_particle_px",m_VarField.find("parton_pxL")->second / GeV, m_VarField.find("particle_pxL")->second / GeV, weight);
    m_hm->FillMatrices("parton/4j2b/topH/Matrix_parton_particle_px",m_VarField.find("parton_pxH")->second / GeV, m_VarField.find("particle_pxH")->second / GeV, weight);
    m_hm->FillMatrices("parton/4j2b/topL/Matrix_parton_particle_py",m_VarField.find("parton_pyL")->second / GeV, m_VarField.find("particle_pyL")->second / GeV, weight);
    m_hm->FillMatrices("parton/4j2b/topH/Matrix_parton_particle_py",m_VarField.find("parton_pyH")->second / GeV, m_VarField.find("particle_pyH")->second / GeV, weight);
    m_hm->FillMatrices("parton/4j2b/topL/Matrix_parton_particle_pz",m_VarField.find("parton_pzL")->second / GeV, m_VarField.find("particle_pzL")->second / GeV, weight);
    m_hm->FillMatrices("parton/4j2b/topH/Matrix_parton_particle_pz",m_VarField.find("parton_pzH")->second / GeV, m_VarField.find("particle_pzH")->second / GeV, weight);    
    
    m_hm->FillMatrices("particle/4j2b/difference/Matrix_particle_parton_Pout",m_VarField.find("particle_Pout")->second / GeV, m_VarField.find("parton_Pout")->second / GeV, weight);
    m_hm->FillMatrices("particle/4j2b/difference/Matrix_particle_parton_z_ttbar",m_VarField.find("particle_z_ttbar")->second, m_VarField.find("parton_z_ttbar")->second, weight);
    m_hm->FillMatrices("particle/4j2b/difference/Matrix_particle_parton_Yboost",m_VarField.find("particle_Yboost")->second, m_VarField.find("parton_Yboost")->second, weight);
    m_hm->FillMatrices("particle/4j2b/difference/Matrix_particle_parton_dPhi_ttbar",m_VarField.find("particle_dPhi")->second, m_VarField.find("parton_dPhi")->second, weight);
    m_hm->FillMatrices("particle/4j2b/difference/Matrix_particle_parton_HT_ttbar",m_VarField.find("particle_HT_ttbar")->second / GeV, m_VarField.find("parton_HT_ttbar")->second / GeV, weight);
    m_hm->FillMatrices("particle/4j2b/difference/Matrix_particle_parton_Chi_ttbar",m_VarField.find("particle_Chi_ttbar")->second, m_VarField.find("parton_Chi_ttbar")->second, weight);
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

    CutFlowPluginFactory_TTbarResolved * MakeCutFlowPlugin() {
        return new CutFlowPluginFactory_TTbarResolved("TTbarResolved");
    };
}

