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

  // Electrons
  ed->electrons.n = 1;
  ed->electrons.pT.push_back( GET_VALUE( lep_pt ) );
  ed->electrons.eta.push_back( GET_VALUE( lep_eta ) );
  ed->electrons.phi.push_back( GET_VALUE( lep_phi ) );
  ed->electrons.E.push_back( GET_VALUE( lep_E ) );
  ed->electrons.q.push_back( GET_VALUE( lep_charge ) );

  ed->electrons.property["charge"].push_back( GET_VALUE( lep_charge ) );
  //ed->electrons.property["trigMatch"].push_back( GET_VALUE( lep_trigMatch ) );

  //ed->electrons.property["tight"].push_back( GET_VALUE( tight ) );
  ed->electrons.property["el_cl_eta"].push_back( GET_VALUE( el_cl_eta ) );
  ed->electrons.property["eptcone30"].push_back( GET_VALUE( eptcone30 ) );
  ed->electrons.property["eetcone20"].push_back( GET_VALUE( eetcone20 ) );
  ed->electrons.property["eminiIso10_4"].push_back( GET_VALUE( m_eminiIso10_4 ) );


  // Muons
  ed->muons.n = 1;
  ed->muons.pT.push_back( GET_VALUE( lep_pt ) );
  ed->muons.eta.push_back( GET_VALUE( lep_eta ) );
  ed->muons.phi.push_back( GET_VALUE( lep_phi ) );
  ed->muons.E.push_back( GET_VALUE( lep_E ) );
  ed->muons.q.push_back( GET_VALUE( lep_charge ) );

  ed->muons.property["charge"].push_back( GET_VALUE( lep_charge ) );


  return success;
    }

 protected:

};


#endif /** __EVENTDUMPER_LEPTONS_H__ */
