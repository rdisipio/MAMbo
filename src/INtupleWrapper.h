#ifndef __INTUPLE_WRAPPER_H__
#define __INTUPLE_WRAPPER_H__

#include "Commons.h"
#include "EventData.h"
#include "CutFlowFactory.hpp"
#include "HistogramManager.h"

class INtupleWrapper 
{
 public:
   INtupleWrapper( const AnalysisParams_t analysisParameters );
   virtual ~INtupleWrapper();

 public:

   virtual void        Loop( Long64_t nEventsMax );

   virtual CutFlow   * AddCutFlow( const string& name );

   virtual EventData * MakeEvent( Long64_t i ) = 0;

   virtual Long64_t    GetEntries() = 0;

   virtual void        Finalize();

 protected:
   bool                SetupTools();
   virtual bool        LoadChain( const string fileListName, const string treeName = "physics" ) = 0;
   virtual UInt_t      SetActiveBranches( const string listFileName = "branch_list.txt" )        = 0;

   virtual EventData  * NextEvent();

   virtual bool         MakeEventInfo( EventData * ed )      = 0;
   virtual bool         MakeEventMET( EventData * ed )       = 0;
   virtual bool         MakeEventLeptons( EventData * ed )   = 0;
   virtual bool         MakeEventJets( EventData * ed )      = 0;
   virtual bool         MakeEventTruth( EventData * ed )     = 0;
  
 protected:
   HistogramManager * m_hm;

   const char       * m_treeName;
   set<string>        m_activeBranches;

   Long64_t           m_thisEventNumber;
   Long64_t           m_maxEvents;
   EventData        * m_thisEvent;

   CutFlowCollection_t m_cutFlows;
   AnalysisParams_t    m_config;

};


#endif /** __INTUPLE_WRAPPER_H__ */
