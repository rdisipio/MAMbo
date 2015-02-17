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

   virtual void PrintOutStats();

 protected:
   virtual void PassedCut( const string& channelName, const string& counterName, const double weight = 1. );
   
   virtual void AddChannel( const string& name );
   virtual void AddCounterName( const string& channelName, const string& counterName, unsigned int ncuts = 0 );

   virtual bool Start();
   
   virtual void SetCutName( const string& channelName, const string& counterName, int n, const string& cutName, const string& cutAlias = "" );
   virtual void SetCutAlias( const string& channelName, const string& counterName, int n, const string& cutAlias );

   virtual bool IncreaseCount( const string& histName, unsigned int cut, double weight = 1., double * new_value = NULL );
   
   int GetLastPassedCut( const string& channelName, const string& counterName ) const;
   
 protected:
   vector< string > m_channelName;
   string m_name;
   map< string, string >           m_counter2channel;
   map< string, vector< string > > m_counterName;
   map< string, int >              m_lastCutPassed;

   map< string, StringVector_t >   m_cutAlias;

   HistogramManager * m_hm;
   AnalysisParams_t * m_config;
};

#define PASSED_TRIGGER(T) ( ed->trigger[ T ] == 1 )

#endif /** __CUTFLOW_H__ */

