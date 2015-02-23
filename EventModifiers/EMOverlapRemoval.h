#ifndef __EventModifier_OverlapRemoval__
#define __EventModifier_OverlapRemoval__

#include "EventModifiersFactory.hpp"

class EMOverlapRemoval : public IEventModifier
{  
 public:
    EMOverlapRemoval();
    virtual ~EMOverlapRemoval();

    virtual void Configure( const EventModifierParams_t& params );
    virtual bool Apply( EventData * ed );

 protected:
    double m_min_dR_ej;
    double m_min_dR_je;
};


/////////////////////////
// Plugin mechanism

typedef EventModifiersPluginFactory< EMOverlapRemoval > EventModifiersPluginFactory_OverlapRemoval;

extern "C" {
  EventModifiersPluginFactory_OverlapRemoval * MakeEventModifierPlugin();
}

#endif /** __EventModifier_OverlapRemoval__ */
