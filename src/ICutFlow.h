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

   virtual bool Initialize();
   virtual bool Apply( EventData * ed ) = 0;
   virtual void PassedCut( const string& channelName, const string& counterName, const double weight = 1. );

   virtual void AddChannel( const string& name );
   virtual void AddCounterName( const string& channelName, const string& counterName, unsigned int nbins = 0 );

   virtual bool Start();
   virtual void PrintOutStats();
   virtual void SetCutName( const string& channelName, const string& counterName, int n, const char * cutName );

 protected:
   vector< string > m_channelName;
   string m_name;
   map< string, string >           m_counter2channel;
   map< string, vector< string > > m_counterName;
   map< string, int >              m_lastCutPassed;

   HistogramManager * m_hm;
   AnalysisParams_t * m_config;
};

#define PASSED_TRIGGER(T) ( ed->trigger[ T ] == 1 )

#endif /** __CUTFLOW_H__ */

