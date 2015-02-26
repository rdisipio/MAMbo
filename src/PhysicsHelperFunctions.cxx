#include "PhysicsHelperFunctions.h"

#include <exception>

namespace PhysicsHelperFunctions {

  double Phi_mphi_phi( double x ) {
    while ( x >= M_PI) x -= 2*M_PI;
    while ( x < -M_PI) x += 2*M_PI;
    return x;
  }

  /////////////////////////////////////////
  // Pseudo Top Reconstruction
  /////////////////////////////////////////

  PseudoTopReconstruction::PseudoTopReconstruction() : 
    m_target( kReco ), m_channel( kElectron ), m_lepton_index( 0 ), m_p_ed(NULL)
  {
  }

  PseudoTopReconstruction::PseudoTopReconstruction( EventData * p_ed ) :
    m_target( kReco ), m_channel( kElectron ), m_lepton_index( 0 ), m_p_ed( p_ed )
  {
  }

  PseudoTopReconstruction::~PseudoTopReconstruction()
  {
    m_p_ed = NULL;
  }


  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

  void PseudoTopReconstruction::SetTarget( const PseudoTopTarget target )
  {
    m_target = target;
  }


  void PseudoTopReconstruction::SetChargedLepton( const LeptonFlavor channel, const int index )
  {
    m_channel      = channel;
    m_lepton_index = index;
  }


 //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

  
  int PseudoTopReconstruction::Run()
  {
//    printf( "DEBUG: Running pseudotop reconstruction on event %i\n", m_p_ed->info.eventNumber );

    MakeChargedLepton();
    
    double v_pz, D, v_pz_truth = 0;
    NuData nudata;
    MakeNeutrino(nudata);
    v_pz = nudata.v_pz;
    D = nudata.D;
    if (m_target == kTruth) {
      v_pz_truth = nudata.v_pz_truth;
    }
    m_W_lep = m_neutrino + m_lepton;

    //    cout << " v_pz=" << v_pz/GeV << " sign*D^{1/6}=" <<  D/TMath::Abs(D)*pow(TMath::Abs(D),1/6.) / GeV << endl;
    //    cout << "Size of bjets A: " << m_p_ed->bjets.n << endl;

    TLorentzVector bj1 = ( m_target == kReco ) ? 
      HelperFunctions::MakeFourMomentum( m_p_ed->bjets, 0 ) :
      HelperFunctions::MakeFourMomentum( m_p_ed->truth_bjets, 0 );
    TLorentzVector bj2 = ( m_target == kReco ) ?
      HelperFunctions::MakeFourMomentum( m_p_ed->bjets, 1 ) :
      HelperFunctions::MakeFourMomentum( m_p_ed->truth_bjets, 1 );

    const double dR1 = m_lepton.DeltaR( bj1 );
    const double dR2 = m_lepton.DeltaR( bj2 );

    TLorentzVector bj_had;
    if( dR1 < dR2 ) {
      m_top_lep = m_W_lep + bj1;
      bj_had    = bj2;
    }
    else {
      m_top_lep = m_W_lep + bj2;
      bj_had    = bj1;
    }

      
    int Wj1_index = -1;
    int Wj2_index = -1;
    int bj1_index = ( m_target == kReco ) ? m_p_ed->bjets.index.at(0) : m_p_ed->truth_bjets.index.at(0);
    int bj2_index = ( m_target == kReco ) ? m_p_ed->bjets.index.at(1) : m_p_ed->truth_bjets.index.at(1);

    int Njets = ( m_target == kReco ) ? m_p_ed->jets.n : m_p_ed->truth_jets.n;

    for( int j = 0 ; j < Njets ; ++j ) {

      const int jindex = ( m_target == kReco ) ? m_p_ed->jets.index.at(j) : m_p_ed->truth_jets.index.at(j);

      //      printf( "DEBUG:  hadW indicesL %i,  %i\n",  Wj1_index, Wj2_index );

      if( jindex == bj1_index ) continue;
      if( jindex == bj2_index )	continue;

	if( Wj1_index == -1 ) {
	  Wj1_index = jindex;
	  continue;
	}

	if( Wj2_index == -1 ) {
	  Wj2_index = jindex;
	  break;
	}
    }

    //    printf( "  DEBUG: bjets = j%i, j%i ; hadW = j%i + j%i\n", bj1_index, bj2_index, Wj1_index, Wj2_index );

    TLorentzVector Wj1 = ( m_target == kReco ) ?
      HelperFunctions::MakeFourMomentum( m_p_ed->jets, Wj1_index ) :
      HelperFunctions::MakeFourMomentum( m_p_ed->truth_jets, Wj1_index );
    TLorentzVector Wj2 = ( m_target == kReco ) ?
      HelperFunctions::MakeFourMomentum( m_p_ed->jets, Wj2_index ) :
      HelperFunctions::MakeFourMomentum( m_p_ed->truth_jets, Wj2_index );
    
    m_W_had   = Wj1 + Wj2;
    m_top_had = bj_had + m_W_had;

    m_ttbar   = m_top_lep + m_top_had;

    const int top_lep_pid = ( m_p_ed->lepton.q > 0 ) ? 6 : -6;
    const int top_had_pid = -1 * top_lep_pid;
    const int ttbar_pid   = 611;  // ttbar "meson"
    const int W_lep_pid = ( m_p_ed->lepton.q > 0 ) ? 24 : -24;
    const int W_had_pid = -1 * W_lep_pid;
	

    // dump to event data
    const size_t top_lep_index = HelperFunctions::DumpParticleToEventData( m_top_lep, &m_p_ed->reco );
    const size_t top_had_index = HelperFunctions::DumpParticleToEventData( m_top_had, &m_p_ed->reco );
    const size_t ttbar_index   = HelperFunctions::DumpParticleToEventData( m_ttbar,   &m_p_ed->reco );
    const size_t W_lep_index = HelperFunctions::DumpParticleToEventData( m_W_lep, &m_p_ed->reco );
    const size_t W_had_index = HelperFunctions::DumpParticleToEventData( m_W_had, &m_p_ed->reco );

    m_p_ed->reco.pdgId.push_back( top_lep_pid );
    m_p_ed->reco.pdgId.push_back( top_had_pid );
    m_p_ed->reco.pdgId.push_back( ttbar_pid );
    m_p_ed->reco.pdgId.push_back( W_lep_pid );
    m_p_ed->reco.pdgId.push_back( W_had_pid );


    string prefix = ( m_target == kReco ) ? "reco_" : "ptcl_";
    m_p_ed->iproperty[prefix + "pseudotop_had_jet_1_index"] = Wj1_index;
    m_p_ed->iproperty[prefix + "pseudotop_had_jet_2_index"] = Wj2_index;
    m_p_ed->iproperty[prefix + "pseudotop_had_bjet_index"] = bj1_index;
    m_p_ed->iproperty[prefix + "pseudotop_lep_bjet_index"] = bj2_index;

    m_p_ed->property[prefix + "v_pz"] = nudata.v_pz;
    m_p_ed->property[prefix + "v_pz_1"] = nudata.v_pz_1;
    m_p_ed->property[prefix + "v_pz_2"] = nudata.v_pz_2;
    m_p_ed->property[prefix + "v_pz_truth"] = nudata.v_pz_truth;
    m_p_ed->property[prefix + "D"] = nudata.D; // discriminant of the v_pz solution

    if ( m_target == kReco ) {
      m_p_ed->lepton.pT = m_lepton.Pt();
      m_p_ed->lepton.eta = m_lepton.Eta();
      m_p_ed->lepton.phi = m_lepton.Phi();
      m_p_ed->lepton.E = m_lepton.E();
      m_p_ed->lepton.m = m_lepton.M();
      m_p_ed->lepton.q = 0; // ?
    } else {
      m_p_ed->truth_lepton.pT = m_lepton.Pt();
      m_p_ed->truth_lepton.eta = m_lepton.Eta();
      m_p_ed->truth_lepton.phi = m_lepton.Phi();
      m_p_ed->truth_lepton.E = m_lepton.E();
      m_p_ed->truth_lepton.m = m_lepton.M();
      m_p_ed->truth_lepton.q = 0; // ?
    }

    //    cout << "Size of bjets B: " << m_p_ed->bjets.n << endl;
   
  }

  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

  void PseudoTopReconstruction::MakeDummyPseudotops() {
    
    const int top_lep_pid = 6;
    const int top_had_pid = -6;
    const int ttbar_pid   = 611;  // ttbar "meson"
    const int W_lep_pid = 24;
    const int W_had_pid = -24;

    // sooooo dummyyy...
    m_top_lep.SetPtEtaPhiE(1000, 0, 0, 2000);
    m_top_had.SetPtEtaPhiE(1000, 0, -3.14, 2000);
    m_ttbar =  m_top_had + m_top_lep;
    m_W_lep.SetPtEtaPhiE(500, 0, 0, 1000);
    m_W_had.SetPtEtaPhiE(500, 0, -3.14, 1000);


    // dump to event data
    const size_t top_lep_index = HelperFunctions::DumpParticleToEventData( m_top_lep, &m_p_ed->reco );
    const size_t top_had_index = HelperFunctions::DumpParticleToEventData( m_top_had, &m_p_ed->reco );
    const size_t ttbar_index   = HelperFunctions::DumpParticleToEventData( m_ttbar,   &m_p_ed->reco );
    const size_t W_lep_index = HelperFunctions::DumpParticleToEventData( m_W_lep, &m_p_ed->reco );
    const size_t W_had_index = HelperFunctions::DumpParticleToEventData( m_W_had, &m_p_ed->reco );


    m_p_ed->reco.pdgId.push_back( top_lep_pid );
    m_p_ed->reco.pdgId.push_back( top_had_pid );
    m_p_ed->reco.pdgId.push_back( ttbar_pid );
    m_p_ed->reco.pdgId.push_back( W_lep_pid );
    m_p_ed->reco.pdgId.push_back( W_had_pid );


  }

  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


  int PseudoTopReconstruction::MakeChargedLepton()
  {
    int status = 0;

    double l_pT  = 0.;
    double l_eta = 0.;
    double l_phi = 0.;
    double l_E   = 0.;
    if( m_target == kReco ) {
      
      if( m_channel == kElectron ) {
        if( m_p_ed->electrons.n == 0 ) throw runtime_error( "ERROR: PseudoTopReconstruction::MakeChargedLepton(): no reco electrons" );
	l_pT  = m_p_ed->electrons.pT.at( m_lepton_index );
	l_eta = m_p_ed->electrons.eta.at( m_lepton_index );
	l_phi = m_p_ed->electrons.phi.at( m_lepton_index );
	l_E   = m_p_ed->electrons.E.at( m_lepton_index );
      }
      else if( m_channel == kMuon ) {
        if( m_p_ed->muons.n == 0 ) throw runtime_error( "ERROR: PseudoTopReconstruction::MakeChargedLepton(): no reco muons" );
	l_pT  = m_p_ed->muons.pT.at( m_lepton_index );
	l_eta = m_p_ed->muons.eta.at( m_lepton_index );
	l_phi = m_p_ed->muons.phi.at( m_lepton_index );
	l_E   = m_p_ed->muons.E.at( m_lepton_index );
      }
      else {
	throw runtime_error( "PseudoTopReconstruction: tau-lepton channel at reco level not yet implemented\n" );
      }
    }
    else {
        if( m_channel == kElectron ) {
        if( m_p_ed->truth_electrons.n == 0 ) throw runtime_error( "ERROR: PseudoTopReconstruction::MakeChargedLepton(): no particle electrons" );
//    cout << "DEBUG: lepton i=" << m_lepton_index << " el coll size = " << m_p_ed->truth_electrons.pT.size() << endl;
	l_pT  = m_p_ed->truth_electrons.pT.at( m_lepton_index );
	l_eta = m_p_ed->truth_electrons.eta.at( m_lepton_index );
	l_phi = m_p_ed->truth_electrons.phi.at( m_lepton_index );
	l_E   = m_p_ed->truth_electrons.E.at( m_lepton_index );
      }
      else if( m_channel == kMuon ) {
        if( m_p_ed->truth_muons.n == 0 ) throw runtime_error( "ERROR: PseudoTopReconstruction::MakeChargedLepton(): no particle muons" );
// cout << "DEBUG: lepton i=" << m_lepton_index << " mu coll size = " << m_p_ed->truth_electrons.pT.size() << endl;
	l_pT  = m_p_ed->truth_muons.pT.at( m_lepton_index );
	l_eta = m_p_ed->truth_muons.eta.at( m_lepton_index );
	l_phi = m_p_ed->truth_muons.phi.at( m_lepton_index );
	l_E   = m_p_ed->truth_muons.E.at( m_lepton_index );
      }
      else {
	throw runtime_error( "PseudoTopReconstruction: tau-lepton channel at reco level not yet implemented\n" );
      }
      
    }

    m_lepton.SetPtEtaPhiE( l_pT, l_eta, l_phi, l_E );

    return status;
  }


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


  int PseudoTopReconstruction::MakeNeutrino( NuData &nudata, bool FitAlsoParticle, int option, const double mW )
  {
    int status = 0;

    double v_pz = -KinemEdge;
    double delta = -KinemEdge;
    nudata.v_pz = v_pz;
    nudata.D = delta;

    if(m_target == kTruth ) {
      nudata.v_pz_truth = m_p_ed->MET_truth.etz;
      if(!FitAlsoParticle) {
	//cout << "Setting neutrino's p_z using truth" << endl;
	m_neutrino.SetXYZM( m_p_ed->MET_truth.etx, m_p_ed->MET_truth.ety, m_p_ed->MET_truth.etz, 0. );
	return status;
      } else {
	//cout << "OK, will run MW also in particle mode..." << endl;
      }
    } else {
      nudata.v_pz_truth = v_pz;
    }

    const double v_pT = ( m_target == kReco ) ? m_p_ed->MET.et : m_p_ed->MET_truth.et;
    const double v_px = ( m_target == kReco ) ? v_pT * cos( m_p_ed->MET.phi ) : m_p_ed->MET_truth.etx;
    const double v_py = ( m_target == kReco ) ? v_pT * sin( m_p_ed->MET.phi ) : m_p_ed->MET_truth.ety;

    // lepton already made by reco or particle levels:
    const double l_px = m_lepton.Px();
    const double l_py = m_lepton.Py();
    const double l_pz = m_lepton.Pz();
    const double l_m  = m_lepton.M();
    const double l_E  = m_lepton.E();

    const double mdiff = 0.5 * ( mW*mW - l_m*l_m );
    const double pT_vl = v_px*l_px + v_py*l_py; // pT( v \cdot l )

    const double a = l_E*l_E - l_pz*l_pz; // dimension: GeV^2
    const double b = -2. * l_pz * ( mdiff + pT_vl ); // dimension : GeV^3
    const double c = v_pT*v_pT*l_E*l_E - mdiff*mdiff - pT_vl*pT_vl - 2.*mdiff*pT_vl; // dimension: GeV^4
  
    delta = b*b - 4.*a*c; // dimesion: GeV^6
    
    if( delta <= 0. ) {
      v_pz = -0.5*b/a;
      nudata.v_pz_1 = v_pz;
      nudata.v_pz_2 = v_pz;
      // hm...maybe try fixing top mass to PDG or make t,lep mass same as t,had mass?
    } else {
      const double v_pz_1 = 0.5 * ( -b - sqrt(delta) ) / a;
      const double v_pz_2 = 0.5 * ( -b + sqrt(delta) ) / a;
      nudata.v_pz_1 = v_pz_1;
      nudata.v_pz_2 = v_pz_2;
      if (option == 1) {
	// more central:
	if (fabs(v_pz_1) < fabs(v_pz_2))
	  v_pz = v_pz_1;
      } else if (option == 2) {
	// more forward:
	if (fabs(v_pz_1) < fabs(v_pz_2))
	  v_pz = v_pz_2;       
      } else {
	// default, more central neutrino preferred:
	v_pz = ( fabs(v_pz_1) > fabs(v_pz_2) ) ? v_pz_2 : v_pz_1;
      }
    }
    
    const double v_E  = sqrt( v_pT*v_pT + v_pz*v_pz ); // of course, massless

    m_neutrino.SetPxPyPzE( v_px, v_py, v_pz, v_E );
    
    nudata.v_pz = v_pz;
    nudata.D = delta;
    return status;
  }
  
  
  
  /////////////////////////////////////////
  // Pseudo Top Matching
  /////////////////////////////////////////
  
  PseudoTopMatching::PseudoTopMatching( MatchingType type ) :
          m_p_ed( NULL ), m_dR_max(0.2), m_matching_type( type )
  {
  }

  PseudoTopMatching::~PseudoTopMatching()
  {
  }
  
  void PseudoTopMatching::SetEventData( EventData * ed )
  {
      if( ed == NULL ) throw runtime_error( "PseudoTopMatching: invalid event data.");
      m_p_ed = ed;
  }
  

  bool PseudoTopMatching::DoObjectsMatching( int debug )
  {

      // jk:
    if (debug) {
      cout << "SIZES: " 
	   << m_p_ed->jets.n << ","
	   << m_p_ed->truth_jets.n << " "
	   << m_p_ed->bjets.n << ","
	   << m_p_ed->truth_bjets.n << ""
	   << endl;
      cout <<  "INDICES: " 
	   << m_p_ed->iproperty["reco_pseudotop_had_jet_1_index"] << ","
	   << m_p_ed->iproperty["ptcl_pseudotop_had_jet_1_index"] << " "
	   << m_p_ed->iproperty["reco_pseudotop_had_jet_2_index"] << ","
	   << m_p_ed->iproperty["ptcl_pseudotop_had_jet_2_index"] << " "
	   << m_p_ed->iproperty["reco_pseudotop_had_bjet_index"] << ","
	   << m_p_ed->iproperty["ptcl_pseudotop_had_bjet_index"] << " "
	   << m_p_ed->iproperty["reco_pseudotop_lep_bjet_index"] << ","
	   << m_p_ed->iproperty["ptcl_pseudotop_lep_bjet_index"] << " "
	   << endl;
    }

      try {

	// reco-level:
	string prefix = "reco_";
	TLorentzVector r_jet1 = HelperFunctions::MakeFourMomentum(m_p_ed->jets, m_p_ed->iproperty[prefix + "pseudotop_had_jet_1_index"]);
	TLorentzVector r_jet2 = HelperFunctions::MakeFourMomentum(m_p_ed->jets, m_p_ed->iproperty[prefix + "pseudotop_had_jet_2_index"]);
	TLorentzVector r_had_bjet = HelperFunctions::MakeFourMomentum(m_p_ed->jets, m_p_ed->iproperty[prefix + "pseudotop_had_bjet_index"]);
	TLorentzVector r_lep_bjet = HelperFunctions::MakeFourMomentum(m_p_ed->jets, m_p_ed->iproperty[prefix + "pseudotop_lep_bjet_index"]);
	TLorentzVector r_lep = HelperFunctions::MakeFourMomentum(m_p_ed->lepton);
	
	// particle level:
	prefix = "ptcl_";
	TLorentzVector p_jet1 = HelperFunctions::MakeFourMomentum(m_p_ed->truth_jets, m_p_ed->iproperty[prefix + "pseudotop_had_jet_1_index"]);
	TLorentzVector p_jet2 = HelperFunctions::MakeFourMomentum(m_p_ed->truth_jets, m_p_ed->iproperty[prefix + "pseudotop_had_jet_2_index"]);
	TLorentzVector p_had_bjet = HelperFunctions::MakeFourMomentum(m_p_ed->truth_jets, m_p_ed->iproperty[prefix + "pseudotop_had_bjet_index"]);
	TLorentzVector p_lep_bjet = HelperFunctions::MakeFourMomentum(m_p_ed->truth_jets, m_p_ed->iproperty[prefix + "pseudotop_lep_bjet_index"]);
	TLorentzVector p_lep = HelperFunctions::MakeFourMomentum(m_p_ed->truth_lepton);

	if (debug) {
	  cout << "Reco jets: ";
	  HelperFunctions::ShortPrintFourvec(r_jet1, " | ");
	  HelperFunctions::ShortPrintFourvec(r_jet2, " | ");
	  HelperFunctions::ShortPrintFourvec(r_had_bjet, " | ");
	  HelperFunctions::ShortPrintFourvec(r_lep_bjet);
	  cout << "Ptcl jets: ";
	  HelperFunctions::ShortPrintFourvec(p_jet1, " | ");
	  HelperFunctions::ShortPrintFourvec(p_jet2, " | ");
	  HelperFunctions::ShortPrintFourvec(p_had_bjet, " | ");
	  HelperFunctions::ShortPrintFourvec(p_lep_bjet);
	}

	bool passedJetDR_std = HelperFunctions::ComputeJetsDR(r_jet1, r_jet2, r_had_bjet, r_lep_bjet,
							      p_jet1, p_jet2, p_had_bjet, p_lep_bjet);
	// try had_bjet instead of light one:
	bool passedJetDR_bhj1 = HelperFunctions::ComputeJetsDR(r_had_bjet, r_jet2, r_jet1, r_lep_bjet,
							       p_jet1, p_jet2, p_had_bjet, p_lep_bjet);
	bool passedJetDR_bhj2 = HelperFunctions::ComputeJetsDR(r_jet1, r_had_bjet, r_jet2, r_lep_bjet,
							       p_jet1, p_jet2, p_had_bjet, p_lep_bjet);
	// try lep_bjet instead of light one:
	bool passedJetDR_blj1 = HelperFunctions::ComputeJetsDR(r_lep_bjet, r_jet2, r_had_bjet, r_jet1,
							       p_jet1, p_jet2, p_had_bjet, p_lep_bjet);
	bool passedJetDR_blj2 = HelperFunctions::ComputeJetsDR(r_jet1, r_lep_bjet, r_had_bjet, r_jet2,
							       p_jet1, p_jet2, p_had_bjet, p_lep_bjet);
	// try swapping bjets:
	bool passedJetDR_bs = HelperFunctions::ComputeJetsDR(r_jet1, r_jet2, r_lep_bjet, r_had_bjet,
							     p_jet1, p_jet2, p_had_bjet, p_lep_bjet);
	if (debug) {
	  cout << "Match results: "
	       << " std:" << passedJetDR_std
	       << " bhj:" << passedJetDR_bhj1
	       << " bhj:" << passedJetDR_bhj2
	       << " blj:" << passedJetDR_blj1
	       << " blj:" << passedJetDR_blj2
	       << " bs:" << passedJetDR_bs
	       << endl;
	}

	bool allObjectsMatched = passedJetDR_std;
	// tighter for leptons:
	allObjectsMatched = allObjectsMatched && r_lep.DeltaR( p_lep ) < 0.02;
	if (debug) cout << "MATCHED: " <<   allObjectsMatched << endl;
	if (debug) cout << endl;
	
	MatchingResult res;
	res.DRmatched = allObjectsMatched;
	return allObjectsMatched;

      }
      catch(...) {
	cerr << "  ERROR in jet indices!" << endl;
      }


      return false;
      

  }
  
  void PseudoTopMatching::DoMatching( unsigned int i1, unsigned int i2, const string& label )
  {
      if( !m_p_ed ) throw runtime_error( "PseudoTopMatching: cannot do matching. Invalid pointer to event data." );
      
      if( m_matching_type == kUnspecifiedMatching ) throw runtime_error( "PseudoTopMatching: unspecified matching type." );
      
      // pseudotop 4-vecs:
      TLorentzVector p1;
      TLorentzVector p2; 
      
      switch( m_matching_type ) {
          case kRecoToParticle:
              p1 = HelperFunctions::MakeFourMomentum( m_p_ed->reco, i1 );
              p2 = HelperFunctions::MakeFourMomentum( m_p_ed->reco, i2 );
              break;
          case kRecoToParton:
              break;
          case kParticleToParton:
              break;
          default:
              break;
      }
      
      MatchingResult res;
      res.delta_R   = p1.DeltaR( p2 );
      res.delta_pT  = p1.Pt() - p2.Pt();
      res.delta_eta = p1.Eta() - p2.Eta();
      res.delta_rapidity = p1.Rapidity() - p2.Rapidity();
      res.delta_phi = p1.DeltaPhi( p2 );
      res.delta_m   = p1.M() - p2.M();
      
      m_results[label] = res;
  }
  
};
