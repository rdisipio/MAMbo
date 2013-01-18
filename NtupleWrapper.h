#ifndef __NTUP_TOP_WRAPPER_H__
#define __NTUP_TOP_WRAPPER_H__

#include "Commons.h"

#include "MiniSLBoost.h"

#include "EventData.h"
#include "EventMaker.h"
#include "CutFlowFactory.hpp"
#include "HistogramManager.h"

typedef MiniSLBoost NTUPLE;

typedef map< string, CutFlow * > CutFlowCollection_t;

//template< class T>
class NtupleWrapper 
{
 public:
   NtupleWrapper( TTree * tree );
   NtupleWrapper( const char * fileListName, const char * branchListName = "branch_list.txt", const char * treeName = "physics" );
   virtual ~NtupleWrapper();


 public:
   inline Long64_t GetEntries() { return m_ntuple->fChain->GetEntries(); };

   void Loop( Long64_t nEventsMax );

   CutFlow * AddCutFlow( const string& name );

 protected:
   bool          SetupTools();
   bool          LoadChain( const char * fileListName, const char * treeName = "physics" );
   UInt_t        SetActiveBranches( const char * listFileName = "branch_list.txt" );

   EventData   * NextEvent();


 protected:
   NTUPLE           * m_ntuple;
   EventMaker       * m_eventMaker;
   HistogramManager * m_hm;

   const char       * m_treeName;
   set<string>        m_activeBranches;

   Long64_t           m_thisEventNumber;
   Long64_t           m_maxEvents;
   EventData        * m_thisEvent;

   CutFlowCollection_t m_cutFlows;
};


#endif /** __NTUP_TOP_WRAPPER_H__ */
