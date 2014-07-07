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

};

#endif /**  __PHYSICSHELPERFUNCTIONS_H__ */
