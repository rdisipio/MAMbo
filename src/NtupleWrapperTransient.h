#ifndef __NTUPLE_WRAPPER_TRANSIENT_H__
#define __NTUPLE_WRAPPER_TRANSIENT_H__

#define XAOD_STANDALONE
#define XAOD_ANALYSIS

#include "INtupleWrapper.h"
#include "NtupleWrapperFactory.hpp"
#include "ConfigManager.h"

#include <xAODRootAccess/MakeTransientTree.h>
#include "xAODRootAccess/TEvent.h"

class NtupleWrapperTransient : public INtupleWrapper
{
 public:

  NtupleWrapperTransient( const AnalysisParams_t analysisParameters ) :
    INtupleWrapper( analysisParameters ), m_xAODevent(NULL)
    {
      m_config = analysisParameters;

      m_xAODevent = new xAOD::TEvent();

      if( !LoadChain( m_config.fileListName, m_config.treeName ) ) throw runtime_error( "Cannot load file chain\n" );
    };

    virtual ~NtupleWrapperTransient() 
    {
       delete m_xAODevent;
    };

    virtual void    Init(TTree *tree)          {};
    virtual Int_t   GetEntry( Long64_t entry ) { return m_xAODevent->getEntry( entry ); };
    UInt_t          SetActiveBranches( const string listFileName = "branch_list.txt" ) { return 0; };       

    TTree         * GetTree() { return NULL; };


 public:
    virtual Long64_t GetEntries() { return m_xAODevent->getEntries(); };

 protected:
    bool LoadChain( const string fileListName, const string treeName = "physics" )
    {
      bool success = true;

      static string sep = "/";

      TTree * chain = HelperFunctions::LoadChain( fileListName, m_treeName );
      
      m_xAODevent->readFrom( chain );

      return success;
    };


    //////////////////////////////

     
    virtual EventData * MakeEvent( Long64_t i ) {
      EventData * ed = new EventData();

      //Long64_t j = m_ntuple->LoadTree( i );
      //if( j < 0 ) throw runtime_error( "Cannot load tree\n" );

      m_xAODevent->getEntry( i );

      // pass global parameters
      ed->property = m_config.custom_params_numeric; // what about the others (flag, string)?
  
      MAKE_OBJECT( Info, ed );
      MAKE_OBJECT( Truth, ed );    
      MAKE_OBJECT( Trigger, ed );
      MAKE_OBJECT( Leptons, ed );
      MAKE_OBJECT( Jets, ed );
      MAKE_OBJECT( MET, ed );

      return ed;
    };
      
    virtual bool MakeEventInfo( EventData * ed )      { return true; };
    virtual bool MakeEventTruth( EventData * ed )     { return true; };      
    virtual bool MakeEventTrigger( EventData * ed )   { return true; };
    virtual bool MakeEventMET( EventData * ed )       { return true; };
    virtual bool MakeEventJets( EventData * ed )      { return true; };
    virtual bool MakeEventElectrons( EventData * ed ) { return true; };
    virtual bool MakeEventMuons( EventData * ed )     { return true; };

    virtual bool MakeEventLeptons( EventData * ed )   { 
        MakeEventMuons(ed); 
        MakeEventElectrons(ed);
        return true;
    };

 protected:
   xAOD::TEvent * m_xAODevent;

};


#endif /** __NTUP_TOP_WRAPPER_H__ */

