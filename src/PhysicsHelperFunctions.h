#ifndef __PHYSICSHELPERFUNCTIONS_H__
#define __PHYSICSHELPERFUNCTIONS_H__

#include "HelperFunctions.h"

namespace PhysicsHelperFunctions {

  const double KinemEdge = 13.9e6;

  const double mWPDG =  80.399*GeV;

  struct NuData {
    double v_pz = -KinemEdge, D = -KinemEdge, v_pz_truth = -KinemEdge;
    double v_pz_1 = -KinemEdge, v_pz_2 = -KinemEdge;
  };

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
    int Run(bool Run7TevPseudotopAlgo = false );
    void MakeDummyPseudotops();
    double GetHt(), GetR_lb(), GetR_Wb_had(), GetR_Wb_lep();

  protected:
    int MakeChargedLepton();
    int MakeNeutrino(NuData &nudata, bool FitAlsoParticle = true, int option = 0, const double mW = mWPDG );

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
    double         m_ht,m_R_lb,m_R_Wb_had,m_R_Wb_lep;
  };

  
  /////////////////////////////////////////
  // Pseudo Top Matching
  /////////////////////////////////////////
  
  class PseudoTopMatching
  {
  public:
      enum MatchingType { kUnspecifiedMatching, kRecoToParticle, kRecoToParton, kParticleToParton };
      
      struct MatchingResult {
          double delta_R;
          double delta_pT;
          double delta_eta;
          double delta_rapidity;
          double delta_phi;
          double delta_m;
	  bool DRmatched;
      };
      typedef map< string, MatchingResult > MatchingResultCollection_t;
      
      PseudoTopMatching( MatchingType type = kUnspecifiedMatching );
      virtual ~PseudoTopMatching();
      
      void SetEventData( EventData * ed );
      
      bool DoObjectsMatching( int debug = 0 );
      void DoMatching( unsigned int i1, unsigned int i2, const string& label = "" );
      
      inline void SetDeltaR( double dR )               { m_dR_max = dR; };
      inline void SetMatchingType( MatchingType type ) { m_matching_type = type; };
      
      inline const MatchingResult& GetResults( const string& label ) const { return m_results.at( label ); };
      
  protected:
      MatchingType m_matching_type;
      EventData * m_p_ed;
      MatchingResultCollection_t m_results;
      double m_dR_max;
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


  //////////////////////////////////

  template< class T >
  double Mass( const T& coll, const int i )
  {
     const double pT  = coll.pT.at( i );
     const double eta = coll.eta.at( i );
     const double pz  = pT * sinh( eta );
     const double E   = coll.E.at( i );
     const double m2  = E*E - pT*pT - pz*pz;
     
     return ( m2 >= 0 ) ? sqrt(m2) : -1.*sqrt(-m2);
  }
  
  
  /////////////////////////////////////////////////

  double Phi_mphi_phi( double x );
  
  /////////////////////////////////////////////////
  
   
  template< class T >
  double DeltaR( const T& coll, const int i, const int j ) {
      const double eta1 = coll.eta[i];
      const double phi1 = coll.phi[i];

      const double eta2 = coll.eta[j];
      const double phi2 = coll.phi[j];
      
      const double dEta = eta1 - eta2;
      const double dPhi = Phi_mphi_phi( phi1 - phi2 );
      
      const double dR = sqrt( dEta*dEta + dPhi*dPhi );
      
      return dR;
  }
  
  
  /////////////////////////////////////////////////


  template< class T1, class T2 >
  double DeltaR( const T1& coll1, const int i, const T2& coll2, const int j ) {
      const double eta1 = coll1.eta[i];
      const double phi1 = coll1.phi[i];

      const double eta2 = coll2.eta[j];
      const double phi2 = coll2.phi[j];

      const double dEta = eta1 - eta2;
      const double dPhi = Phi_mphi_phi( phi1 - phi2 );

      const double dR = sqrt( dEta*dEta + dPhi*dPhi );

      return dR;
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

  ////////////////////////
    double deltaPhi(double phi1, double phi2) {
    double dPhi=std::fabs(phi1-phi2);
    if (dPhi>M_PI) dPhi=2*M_PI-dPhi;
    return dPhi;
  }
  
  double deltaR(double eta1, double eta2, double phi1, double phi2) {
    double dPhi=deltaPhi(phi1,phi2);
    double dEta=std::fabs(eta1-eta2);
    double dR=std::sqrt(std::pow(dEta,2)+std::pow(dPhi,2));
    return dR;
  }
  ///////////////////////
};

#endif /**  __PHYSICSHELPERFUNCTIONS_H__ */
