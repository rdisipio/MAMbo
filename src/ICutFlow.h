#ifndef __CUTFLOW_H__
#define __CUTFLOW_H__

#include "Commons.h"
#include "CutFlowFactory.hpp"
#include "EventData.h"
#include "HistogramManager.h"
#include "ConfigManager.h"

class CutFlow;
typedef map< string, CutFlow * > CutFlowCollection_t;

class CutFlow
{
 public:
   CutFlow( const string& name = "" );
   virtual ~CutFlow();

   virtual bool Apply( EventData * ed, int * lastCutPassed = NULL ) = 0;
   virtual void Connect( const string& name, int cutN );
   virtual void PassedCut( const double weight = 1. );

   inline virtual void SetCounterName( const string& name ) { m_counterName = name; };
   virtual bool Start();
   virtual void PrintOutStats();

 protected:
   string m_name;
   string m_counterName;
   int    m_lastCutPassed;

   HistogramManager * m_hm;
   AnalysisParams_t * m_config;
};

#define PASSED_TRIGGER(T) ( ed->trigger[ T ] == 1 )

#endif /** __CUTFLOW_H__ */

