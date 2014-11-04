#ifndef __HF_FINALSTATEOBJECTS_H__
#define __HF_FINALSTATEOBJECTS_H__

//#include "IHistogramFiller.h"
#include "HistogramFillersFactory.hpp"

class HFFinalStateObjects : public IHistogramFiller
{
 public:
   HFFinalStateObjects();
   virtual ~HFFinalStateObjects();

   virtual void Configure( const HistogramFillerParams_t& params );
   virtual void Fill( const EventData& ed );
};

typedef HistogramFillerPluginFactory< HFFinalStateObjects > HistogramFillerPluginFactory_FinalStateObjects;

extern "C" {
  HistogramFillerPluginFactory_FinalStateObjects * MakeHistogramFillerPlugin();
}


#endif /** __HF_FINALSTATEOBJECTS_H__ */
