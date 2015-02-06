#ifndef __NTUPLE_WRAPPER_H__
#define __NTUPLE_WRAPPER_H__

#include "INtupleWrapper.h"
#include "NtupleWrapperFactory.hpp"
#include "ConfigManager.h"

template <typename NTUPLE>
class NtupleWrapper : public INtupleWrapper
{
 public:

  NtupleWrapper( const AnalysisParams_t analysisParameters ) :
    INtupleWrapper( analysisParameters ), m_ntuple(NULL)
    {
      m_ntuple = new NTUPLE();
      m_config = analysisParameters;

      if( !LoadChain( m_config.fileListName, m_config.treeName ) ) throw runtime_error( "Cannot load file chain\n" );
	
      SetActiveBranches( m_config.branchFileName );
    };

    virtual ~NtupleWrapper()
      {
	delete m_ntuple;
      };

    virtual void    Init(TTree *tree)          { m_ntuple->Init(tree); };
    virtual Int_t   GetEntry( Long64_t entry ) { return m_ntuple->GetEntry( entry ); };

    TTree         * GetTree() { return m_ntuple->fChain; };


 public:
    virtual Long64_t GetEntries() { return m_ntuple->fChain->GetEntries(); };

    // virtual void Loop( Long64_t nEventsMax );
    // virtual CutFlow * AddCutFlow( const string& name );

 protected:
    bool LoadChain( const string fileListName, const string treeName = "physics" )
    {
      bool success = true;

      static string sep = "/";

      TChain * chain = HelperFunctions::LoadChain( fileListName, m_treeName );

      m_ntuple->Init( chain );
       
      return success;
    };

    UInt_t        SetActiveBranches( const string listFileName = "branch_list.txt" )
    {  
      if( !m_ntuple->fChain ) throw runtime_error( "Ntuple chain has not been created\n" );

      m_ntuple->fChain->SetBranchStatus( "*", 0 );

      UInt_t Nbranches = 0;

      cout << "DEBUG: list of active branches from " << listFileName << endl;

      ifstream input( listFileName.c_str(), ios_base::in );
      string bName;
      while( std::getline( input, bName ) ) {
	m_activeBranches.insert( bName );

	m_ntuple->fChain->SetBranchStatus( bName.c_str(), 1 );
      }

      input.close();

      Nbranches = m_activeBranches.size();
      cout << "DEBUG: No. of active branches = " << Nbranches << endl;

      if( Nbranches == 0 ) {
	 cout << "WARNING: no active branch define. All switched on, this could be SLOW!" << endl;
	 m_ntuple->fChain->SetBranchStatus( "*", 1 );
      }

      return Nbranches;
    };
     
    virtual EventData * MakeEvent( Long64_t i ) {
      EventData * ed = new EventData();

      Long64_t j = m_ntuple->LoadTree( i );

      if( j < 0 ) throw runtime_error( "Cannot load tree\n" );
	
      m_ntuple->GetEntry( i );

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
    NTUPLE            * m_ntuple;
};


#endif /** __NTUP_TOP_WRAPPER_H__ */

