#ifndef __PHYSICSHELPERFUNCTIONS_H__
#define __PHYSICSHELPERFUNCTIONS_H__

#include "HelperFunctions.h"

namespace PhysicsHelperFunctions {

  /////////////////////////////////////////
  // Pseudo Top Reconstruction
  /////////////////////////////////////////

  class PseudoTopReconstruction
  {
  public:
    enum PseudoTopTarget  { kReco, kTruth };

  public:
    PseudoTopReconstruction();
    PseudoTopReconstruction( EventData * p_ed );
    virtual ~PseudoTopReconstruction();

    void SetTarget( const PseudoTopTarget target = kReco );
    void SetChargedLepton( const LeptonFlavor channel = kElectron, const int index = 0 );
    void SetEventData( EventData * p_ed ) { m_p_ed = p_ed; };
    int Run( );

  protected:
    int MakeChargedLepton();
    int MakeNeutrino( const double mW = 80.4*GeV );

  protected:
    PseudoTopTarget       m_target;
    LeptonFlavor          m_channel;
    int                   m_lepton_index;

    EventData           * m_p_ed;

    TLorentzVector m_lepton;
    TLorentzVector m_neutrino;
    TLorentzVector m_W_lep;
    TLorentzVector m_top_lep;
    TLorentzVector m_W_had;
    TLorentzVector m_top_had;
    TLorentzVector m_ttbar;
  };

  
  //////////////////////////////////

  template< class T >
  double Rapidity( const T& coll, const int i )
  {
     const double pT  = coll.pT.at( i );
     const double eta = coll.eta.at( i );
     const double pz  = pT * sinh( eta );
     const double E   = coll.E.at( i );
     const double Y   = 0.5 * log( (E+pz)/(E-pz) );

     return Y;
  }


  /////////////////////////////////////////////////


  template< class INDEX_COLL, class PID_COLL  >
    bool HadronicDecay( const int i, const INDEX_COLL * mc_child_index, const PID_COLL * mc_pdgId )
  {
    bool isHadronic = true;

    int n_lquarks = 0;

    const int n_children = mc_child_index->at( i ).size();
    for( int ic = 0 ; ic < n_children ; ++ic ) {
	
      const int child_index = mc_child_index->at( i ).at( ic );
      const int child_pid   = mc_pdgId->at( child_index );
      const int child_apid  = abs( child_pid );

      if( child_apid < 5 ) ++n_lquarks;
    }

    if( n_lquarks < 2 ) return !isHadronic;

    return isHadronic;
  }


  /////////////////////////////////////////////////
  
  template< class INDEX_COLL, class PID_COLL  >
    bool IsFromHadronicDecay( const int i, const INDEX_COLL * mc_parent_index, const PID_COLL * mc_pdgId )
  {
    bool isFromHadron = true;
    const int nparents = mc_parent_index->size();
    for( int ip = 0 ; ip < nparents ; ++ip ) {
        const int mother_index = mc_parent_index->at(ip);
        const int mother_pid   = mc_pdgId->at( mother_index );
        const int mother_apid  = abs( mother_pid );
        
        if( mother_apid > 100 ) return isFromHadron;
    }
    
    return !isFromHadron;
  }
  
  /////////////////////////////////////////////////
  
  /////////////////////////////////////////////////
  
  typedef enum top_quark_decay_class { kTopDecayUndecayed, kTopDecayLeptonic, kTopDecayHadronic } TOP_QUARK_DECAY_CLASS;

  template< class INDEX_COLL, class PID_COLL  >
    TOP_QUARK_DECAY_CLASS ClassifyTopDecay( const unsigned int parent_index, const INDEX_COLL * mc_child_index, const PID_COLL * mc_pdgId )
  {
    const int n_children = mc_child_index->at( parent_index ).size();

    if( n_children == 0 ) return kTopDecayUndecayed;

    for( int ic = 0 ; ic < n_children ; ++ic ) {

      const int child_index = mc_child_index->at( parent_index ).at( ic );
      const int child_pid   = mc_pdgId->at( child_index );
      const int child_apid  = abs( child_pid );
      // printf( "DEBUG: mother id=%i pid=%i nchildren=%i child=%i child_pid=%i\n", 
      //	    parent_index, pid, nchildren, ic, child_pid );
    
      if( child_apid == 24 ) {
	const bool isHadronicW = PhysicsHelperFunctions::HadronicDecay( child_index, mc_child_index, mc_pdgId );

	return ( isHadronicW ? kTopDecayHadronic : kTopDecayLeptonic );
      }
    }

    throw runtime_error( "Top quark invalid decay, no W found.\n" );
  }


  /////////////////////////////////////////////////

  template< class INT_COLL, class FLOAT_COLL, class INDEX_COLL >
    TLorentzVector MakeDressedLepton( const TLorentzVector & naked_lepton, const float dR, const int mc_n, 
				const INT_COLL * mc_pdgId, const INT_COLL * mc_status, const INDEX_COLL * mc_parent_index,
				const FLOAT_COLL * mc_pt, const FLOAT_COLL * mc_eta, const FLOAT_COLL * mc_phi, const FLOAT_COLL * mc_m )
  {
    TLorentzVector dressed_lepton = naked_lepton;

    for( int y = 0 ; y < mc_n ; ++y ) {
	const int pid     = mc_pdgId->at(y);
	const int apid    = abs(pid);
	const int status  = mc_status->at(y);

	if( apid != 22 )  continue;
	if( status != 1 ) continue;

        if( PhysicsHelperFunctions::IsFromHadronicDecay( y, &mc_parent_index->at(y), mc_pdgId ) ) continue;
        
	TLorentzVector gamma;
	gamma.SetPtEtaPhiM( mc_pt->at(y),
			    mc_eta->at(y),
			    mc_phi->at(y),
			    mc_m->at(y)
			   );

	if( naked_lepton.DeltaR( gamma ) > 0.1 ) continue;
 
	dressed_lepton += gamma;
    }
    return dressed_lepton;
  }

};

#endif /**  __PHYSICSHELPERFUNCTIONS_H__ */
