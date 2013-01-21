#ifndef __CUTFLOW_H__
#define __CUTFLOW_H__

#include "Commons.h"
#include "CutFlowFactory.hpp"
#include "EventData.h"
#include "HistogramManager.h"

class CutFlow;
typedef map< string, CutFlow * > CutFlowCollection_t;

class CutFlow
{
 public:
   CutFlow( const string& name = "" );
   virtual ~CutFlow();

   virtual bool Apply( EventData * ed, int * lastCutPassed = NULL ) = 0;
   virtual void Connect( const string& name, int cutN );
   virtual void PassedCut();

   virtual bool Start();

 protected:
   string m_name;
   int    m_lastCutPassed;

   HistogramManager * m_hm;
};

#endif /** __CUTFLOW_H__ */

