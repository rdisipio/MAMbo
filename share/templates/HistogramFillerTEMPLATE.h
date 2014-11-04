#ifndef __HF_@NAME@_H__
#define __HF_@NAME@_H__

#include "HistogramFillersFactory.hpp"

class HistogramFiller@NAME@ : public IHistogramFiller
{
 public:
   HistogramFiller@NAME@();
   virtual ~HistogramFiller@NAME@();

   virtual void Configure( const HistogramFillerParams_t& params );
   virtual void Fill( const EventData& ed );
};

typedef HistogramFillerPluginFactory< HistogramFiller@NAME@ > HistogramFillerPluginFactory_@NAME@;

extern "C" {
  HistogramFillerPluginFactory_@NAME@ * MakeHistogramFillerPlugin();
}


#endif /** __HF_@NAME@_H__ */
