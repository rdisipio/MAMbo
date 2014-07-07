#include "PhysicsHelperFunctions.h"


namespace PhysicsHelperFunctions {

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
    
    MakeNeutrino();

    m_W_lep = m_neutrino + m_lepton;

 
    TLorentzVector bj1 = HelperFunctions::MakeFourMomentum( m_p_ed->bjets, 0 );
    TLorentzVector bj2 = HelperFunctions::MakeFourMomentum( m_p_ed->bjets, 1 );

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
    int bj1_index = m_p_ed->bjets.index.at(0);
    int bj2_index = m_p_ed->bjets.index.at(1);
    for( int j = 0 ; j < m_p_ed->jets.n ; ++j ) {
      const int jindex = m_p_ed->jets.index.at(j);

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

    TLorentzVector Wj1 = HelperFunctions::MakeFourMomentum( m_p_ed->jets, Wj1_index );
    TLorentzVector Wj2 = HelperFunctions::MakeFourMomentum( m_p_ed->jets, Wj2_index );
    // printf( "DEBUG: bjets = j%i, j%i ; hadW = j%i + j%i\n", bj1_index, bj2_index, Wj1_index, Wj2_index );
    m_W_had   = Wj1 + Wj2;
    m_top_had = bj_had + m_W_had;

    m_ttbar   = m_top_lep + m_top_had;

    const int top_lep_pid = ( m_p_ed->lepton.q > 0 ) ? 6 : -6;
    const int top_had_pid = -1 * top_lep_pid;
    const int ttbar_pid   = 611;  // ttbar "meson"
	

    const size_t top_lep_index = HelperFunctions::DumpParticleToEventData( m_top_lep, &m_p_ed->reco );
    const size_t top_had_index = HelperFunctions::DumpParticleToEventData( m_top_had, &m_p_ed->reco );
    const size_t ttbar_index   = HelperFunctions::DumpParticleToEventData( m_ttbar,   &m_p_ed->reco );

    m_p_ed->reco.pdgId.push_back( top_lep_pid );
    m_p_ed->reco.pdgId.push_back( top_had_pid );
    m_p_ed->reco.pdgId.push_back( ttbar_pid );
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
	l_pT  = m_p_ed->electrons.pT.at( m_lepton_index );
	l_eta = m_p_ed->electrons.eta.at( m_lepton_index );
	l_phi = m_p_ed->electrons.phi.at( m_lepton_index );
	l_E   = m_p_ed->electrons.E.at( m_lepton_index );
      }
      else if( m_channel == kMuon ) {
	l_pT  = m_p_ed->electrons.pT.at( m_lepton_index );
	l_eta = m_p_ed->electrons.eta.at( m_lepton_index );
	l_phi = m_p_ed->electrons.phi.at( m_lepton_index );
	l_E   = m_p_ed->electrons.E.at( m_lepton_index );
      }
      else {
	throw runtime_error( "PseudoTopReconstruction: tau-lepton channel at reco level not yet implemented\n" );
      }
    }
    else {
      if( m_channel == kElectron ) {
      }
      else if( m_channel == kMuon ) {
      }
      else {
	throw runtime_error( "PseudoTopReconstruction: tau-lepton channel at truth level not yet implemented\n" );
      }
    }

    m_lepton.SetPtEtaPhiE( l_pT, l_eta, l_phi, l_E );

    return status;
  }


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


  int PseudoTopReconstruction::MakeNeutrino( const double mW )
  {
    int status = 0;

    const double v_pT = m_p_ed->MET.et;
    const double v_px = v_pT * cos( m_p_ed->MET.phi );
    const double v_py = v_pT * sin( m_p_ed->MET.phi );

    const double l_px = m_lepton.Px();
    const double l_py = m_lepton.Py();
    const double l_pz = m_lepton.Pz();
    const double l_m  = m_lepton.M();
    const double l_E  = m_lepton.E();

    const double mdiff = 0.5 * ( mW*mW - l_m*l_m );
    const double pT_vl = v_px*l_px + v_py*l_py; // pT( v \cdot l )

    const double a = l_E*l_E - l_pz*l_pz;
    const double b = -2. * l_pz * ( mdiff + pT_vl );
    const double c = v_pT*v_pT*l_E*l_E - mdiff*mdiff - pT_vl*pT_vl - 2.*mdiff*mdiff*pT_vl;
    
    const double delta = b*b - 4.*a*c;
    
    double v_pz = 0.;
    if( delta < 0. ) {
      v_pz = 0.5*b/a;
    }
    else {
      const double v_pz_1 = 0.5 * ( -b - sqrt(delta) ) / a;
      const double v_pz_2 = 0.5 * ( -b + sqrt(delta) ) / a;
      v_pz = ( v_pz_1 > v_pz_2 ) ? v_pz_1 : v_pz_2;
    }

    const double v_E  = sqrt( v_pT*v_pT + v_pz*v_pz ); // of course, massless

    m_neutrino.SetPxPyPzE( v_px, v_py, v_pz, v_E );
    
    return status;
  }

};
