#include "EMDummy.h"

EMDummy::EMDummy() : IEventModifier( "Dummy" )
{
}


EMDummy::~EMDummy()
{
}


/////////////////////////////////////


void EMDummy::Configure( const EventModifierParams_t& params )
{
}


/////////////////////////////////////


bool EMDummy::Apply( EventData * ed )
{
  bool passed = true;

  // nothing to do
  
  return passed;
}


/////////////////////////////////////////
// Plugin

extern "C" {
    EventModifiersPluginFactory_Dummy * MakeEventModifierPlugin() {
        return new EventModifiersPluginFactory_Dummy("Dummy");
    };
}

