#include "IHistogramFiller.h"

IHistogramFiller::IHistogramFiller() : m_hm(NULL)
{
   m_hm = HistogramManager::GetHandle();
}

IHistogramFiller::~IHistogramFiller()
{
}


///////////////////////////////////////////


void IHistogramFiller::Configure( const HistogramFillerParams_t& params )
{
   m_params = params;
}


///////////////////////////////////////////


void IHistogramFiller::Fill( const EventData& ed )
{
}
