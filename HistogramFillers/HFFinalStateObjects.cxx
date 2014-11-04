#include "HFFinalStateObjects.h"

HFFinalStateObjects::HFFinalStateObjects()
{
}


HFFinalStateObjects::~HFFinalStateObjects()
{
}


/////////////////////////////////////////


void HFFinalStateObjects::Configure( const HistogramFillerParams_t& params )
{
}


/////////////////////////////////////////


void HFFinalStateObjects::Fill( const EventData& ed )
{
}


/////////////////////////////////////////
// Plugin

extern "C" {

    HistogramFillerPluginFactory_FinalStateObjects * MakeHistogramFillerPlugin() {
        return new HistogramFillerPluginFactory_FinalStateObjects("FinalStateObjects");
    };
}
