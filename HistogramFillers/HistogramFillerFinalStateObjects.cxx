#include "HistogramFillerFinalStateObjects.h"

HistogramFillerFinalStateObjects::HistogramFillerFinalStateObjects()
{
}


HistogramFillerFinalStateObjects::~HistogramFillerFinalStateObjects()
{
}


/////////////////////////////////////////


void HistogramFillerFinalStateObjects::Configure( const HistogramFillerParams_t& params )
{
}


/////////////////////////////////////////


void HistogramFillerFinalStateObjects::Fill( const EventData& ed )
{
}


/////////////////////////////////////////
// Plugin

extern "C" {

    HistogramFillerPluginFactory_FinalStateObjects * MakeHistogramFillerPlugin() {
        return new HistogramFillerPluginFactory_FinalStateObjects("FinalStateObjects");
    };
}
