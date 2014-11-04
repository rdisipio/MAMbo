#ifndef __HISTOGRAMFILLER_H__
#define __HISTOGRAMFILLER_H__

#include "Commons.h"
//#include "HistogramFillersFactory.hpp"

#include "EventData.h"
#include "HistogramManager.h"


struct HistogramFillerParams_t
{
    map< string, double >        params_numeric;
    map< string, unsigned long > params_flag;
    map< string, string >        params_string;
};


class IHistogramFiller;
typedef map< string, IHistogramFiller * > HistogramFillerCollection_t;


class IHistogramFiller
{ 
 public: 
    IHistogramFiller();
    virtual ~IHistogramFiller();

    virtual void Configure( const HistogramFillerParams_t& params );
    
    virtual void Fill( const EventData& ed ); // to be defined downstream    

 protected:
    HistogramFillerParams_t   m_params;   
    HistogramManager        * m_hm;
};


#endif /** __HISTOGRAMFILLER_H__ */
