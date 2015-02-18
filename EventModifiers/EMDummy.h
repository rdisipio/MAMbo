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

 protected:

};


/////////////////////////
// Plugin mechanism

typedef EventModifiersPluginFactory< EMDummy > EventModifiersPluginFactory_Dummy;

extern "C" {
  EventModifiersPluginFactory_Dummy * MakeEventModifierPlugin();
}

#endif /** __EventModifier_DUMMY__ */
