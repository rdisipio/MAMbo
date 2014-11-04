#include "HistogramFiller@NAME@.h"

HistogramFiller@NAME@::HistogramFiller@NAME@()
{
}


HistogramFiller@NAME@::~HistogramFiller@NAME@()
{
}


/////////////////////////////////////////


void HistogramFiller@NAME@::Configure( const HistogramFillerParams_t& params )
{
}


/////////////////////////////////////////


void HistogramFiller@NAME@::Fill( const EventData& ed )
{
}


/////////////////////////////////////////
// Plugin

extern "C" {

    HistogramFillerPluginFactory_@NAME@ * MakeHistogramFillerPlugin() {
        return new HistogramFillerPluginFactory_@NAME@("@NAME@");
    };
}
