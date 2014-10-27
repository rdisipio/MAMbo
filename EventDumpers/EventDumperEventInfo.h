#ifndef __EVENTDUMPER_EVENTINFO_H__
#define __EVENTDUMPER_EVENTINFO_H__

#include "IEventDumper.h"

template< class NTUPLE >
class EventDumperEventInfo : public IEventDumper< NTUPLE >
{
 public:
    EventDumperEventInfo() {};
    virtual ~EventDumperEventInfo() {};

 public: 
    virtual bool DumpEventInfo( EventData * ed )
    {
       bool success = true;

  ed->info.eventNumber     = GET_VALUE( eventNumber );
  ed->info.runNumber       = GET_VALUE( runNumber );

  ed->info.mcChannelNumber = GET_VALUE( channelNumber );
  ed->info.mcWeight        = GET_VALUE( mcevt_weight ); /*eventWeight );*/

  SET_PROPERTY( dataPeriod );
  SET_PROPERTY( mu );

  SET_PROPERTY( pvxp_n );
  SET_PROPERTY( vxp_z );

  SET_PROPERTY( hfor );

  ed->property["scaleFactor_PILEUP"]     = GET_VALUE( PUweight     );
  ed->property["scaleFactor_ELE"]        = GET_VALUE( elecScale  );
  ed->property["scaleFactor_MUON"]	 = GET_VALUE( muonScale     );
  ed->property["scaleFactor_BTAG"]	 = GET_VALUE( BTagSFweight     );
  ed->property["scaleFactor_TRIGGER"]    = GET_VALUE( trigScale    );
  ed->property["scaleFactor_WJETSNORM"]  = GET_VALUE( WJetsScale );
  ed->property["scaleFactor_WJETSSHAPE"] = GET_VALUE( WJetsShapeScale );
  ed->property["scaleFactor_JVFSF"]	 = GET_VALUE( JVFSFweight    );
  ed->property["scaleFactor_ZVERTEX"]    = GET_VALUE( ZVxpWeight   );
  ed->property["scaleFactor_KFactor"]    = GET_VALUE( KFactor  );

  return success;
    };

    virtual bool DumpEventTrigger( EventData * ed )
    { 
        return true;
    };

    virtual bool DumpEventMET( EventData * ed )
    { 
       bool success = true;
  
  ed->MET.et    = GET_VALUE( met_et );
  ed->MET.phi   = GET_VALUE( met_phi );
//  ed->MET.etx   = 0.;
//  ed->MET.ety   = 0.;
  ed->MET.sumet = GET_VALUE( met_sumet  );
  ed->MET.mwt   = GET_VALUE( mwt );
//  SET_PROPERTY( mwt );

  return success;
    };

 protected:

};


#endif /** __EVENTDUMPER_EVENTINFO_H__ */
