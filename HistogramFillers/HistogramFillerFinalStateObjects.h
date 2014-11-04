#ifndef __HF_FinalStateObjects_H__
#define __HF_FinalStateObjects_H__

#include "HistogramFillersFactory.hpp"

class HistogramFillerFinalStateObjects : public IHistogramFiller
{
 public:
   HistogramFillerFinalStateObjects();
   virtual ~HistogramFillerFinalStateObjects();

   virtual void Configure( const HistogramFillerParams_t& params );
   virtual void Fill( const EventData& ed );
};

typedef HistogramFillerPluginFactory< HistogramFillerFinalStateObjects > HistogramFillerPluginFactory_FinalStateObjects;

extern "C" {
  HistogramFillerPluginFactory_FinalStateObjects * MakeHistogramFillerPlugin();
}


#endif /** __HF_FinalStateObjects_H__ */
