#ifndef __EventModifier_DUMMY__
#define __EventModifier_DUMMY__

#include "EventModifiersFactory.hpp"

class EMDummy : public IEventModifier
{  
 public:
    EMDummy();
    virtual ~EMDummy();

    virtual void Configure( const EventModifierParams_t& params );
    virtual bool Apply( EventData * ed );
    void SetTargetLumi( float );
    void GetLumiSF( int runNumber);

 protected:
 	float m_lumi;
 	float m_nEvents;
 	float m_lumiWeight;
        std::string m_nEventsFile; 
   
   #ifdef __MOMA__
    MoMATool                * m_moma;
    SYSTEMATIC_TYPE           m_syst_type;
#endif
   	

};


/////////////////////////
// Plugin mechanism

typedef EventModifiersPluginFactory< EMDummy > EventModifiersPluginFactory_Dummy;

extern "C" {
  EventModifiersPluginFactory_Dummy * MakeEventModifierPlugin();
}

#endif /** __EventModifier_DUMMY__ */
