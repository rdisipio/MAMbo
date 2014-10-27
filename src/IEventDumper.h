#ifndef __IEVENTDUMPER_H__
#define __IEVENTDUMPER_H__

#include "Commons.h"
#include "ConfigManager.h"
#include "EventData.h"
#include "PhysicsHelperFunctions.h"


template< class NTUPLE >
class IEventDumper 
{
 public:
    IEventDumper() : m_ntuple(NULL) {};
    virtual ~IEventDumper() {};

 public:
    inline void SetNtuple( NTUPLE * ntuple )    { m_ntuple = ntuple;  };
    inline void SetAnalysisParameters( AnalysisParams_t params ) { m_config = params; };

 public: 
    virtual bool DumpEventInfo( EventData * ed )      { return true; };
    virtual bool DumpEventTrigger( EventData * ed )   { return true; };
    virtual bool DumpEventMET( EventData * ed )       { return true; };
    virtual bool DumpEventLeptons( EventData * ed )   { return true; };
    virtual bool DumpEventJets( EventData * ed )      { return true; };
    virtual bool DumpEventMCTruth( EventData * ed )   { return true; };
    
 protected:
    AnalysisParams_t m_config;
    NTUPLE    * m_ntuple;
};

#endif /** __IEVENTDUMPER_H__ */
