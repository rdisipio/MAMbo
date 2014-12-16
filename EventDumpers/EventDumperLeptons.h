#ifndef __EVENTDUMPER_LEPTONS_H__
#define __EVENTDUMPER_LEPTONS_H__

#include "IEventDumper.h"

template< class NTUPLE >
class EventDumperLeptons : public IEventDumper< NTUPLE >
{
 public:
    EventDumperLeptons() {};
    virtual ~EventDumperLeptons() {};

 public:
    virtual bool DumpEventLeptons( EventData * ed )
    { 
        bool success = true;

  // All leptons
  ed->leptons.n = 1;
  ed->leptons.pT.push_back( GET_VALUE( lep_pt ) );
  ed->leptons.eta.push_back( GET_VALUE( lep_eta ) );
  ed->leptons.phi.push_back( GET_VALUE( lep_phi ) );
  ed->leptons.E.push_back( GET_VALUE( lep_E ) );
  ed->leptons.q.push_back( GET_VALUE( lep_charge ) );

  // Electrons
  ed->electrons.n = 1;
  ed->electrons.pT.push_back( GET_VALUE( lep_pt ) );
  ed->electrons.eta.push_back( GET_VALUE( lep_eta ) );
  ed->electrons.phi.push_back( GET_VALUE( lep_phi ) );
  ed->electrons.E.push_back( GET_VALUE( lep_E ) );
  ed->electrons.q.push_back( GET_VALUE( lep_charge ) );

  ed->electrons.property["charge"].push_back( GET_VALUE( lep_charge ) );

  //ed->electrons.property["tight"].push_back( GET_VALUE( tight ) );
  ed->electrons.property["el_cl_eta"].push_back( GET_VALUE( el_cl_eta ) );
  ed->electrons.property["eptcone30"].push_back( GET_VALUE( eptcone30 ) );
  ed->electrons.property["eetcone20"].push_back( GET_VALUE( eetcone20 ) );
//  ed->electrons.property["eminiIso10_4"].push_back( GET_VALUE( m_eminiIso10_4 ) );


  // Muons
  ed->muons.n = 1;
  ed->muons.pT.push_back( GET_VALUE( lep_pt ) );
  ed->muons.eta.push_back( GET_VALUE( lep_eta ) );
  ed->muons.phi.push_back( GET_VALUE( lep_phi ) );
  ed->muons.E.push_back( GET_VALUE( lep_E ) );
  ed->muons.q.push_back( GET_VALUE( lep_charge ) );

  ed->muons.property["charge"].push_back( GET_VALUE( lep_charge ) );


  // TRACK SIGNIFICANCE
#ifdef TopMiniSLResolved_h
   const double trackd0 = GET_VALUE( lep_trackd0pvunbiased );
   const double tracksigd0 = GET_VALUE( lep_tracksigd0pvunbiased );
   const double d0sig = trackd0pv / tracksigd0pv;
   ed->leptons.property["trackd0"].push_back( trackd0 );
   ed->leptons.property["tracksigd0"].push_back( tracksigd0pv );
   ed->leptons.property["d0sig"].push_back( d0sig );
#endif

  // TRIGGER MATCHING
#ifdef TopMiniSLResolved_h
  ed->leptons.property["trigMatch"].push_back( GET_VALUE( lep_trigMatch ) );
  ed->electrons.property["trigMatch"].push_back( GET_VALUE( lep_trigMatch ) );
  ed->muons.property["trigMatch"].push_back( GET_VALUE( lep_trigMatch ) );
#endif
#ifdef TopMiniSLBoosted_h
#endif


  // TIGHT SELECTION?
#ifdef TopMiniSLResolved_h
  ed->electrons.property["tight"].push_back( GET_VALUE(tight) );
  bool tight = ( GET_VALUE(mminiIso10_4)/GET_VALUE(lep_pt) < 0.05 ) ? true : false;
  ed->muons.property["tight"].push_back( tight );
#endif
#ifdef TopMiniSLBoosted_h
#endif

  return success;
    }

 protected:

};


#endif /** __EVENTDUMPER_LEPTONS_H__ */
