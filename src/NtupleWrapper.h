#ifndef __NTUP_TOP_WRAPPER_H__
#define __NTUP_TOP_WRAPPER_H__

#define GET_VALUE(X) m_ntuple-> X
#define GET_VALUE_VECTOR(X,N) m_ntuple-> X ->at( N )
#define GET_VALUE_ARRAY(X,N) m_ntuple-> X[N]
#define CHECK_TRIGGER(T) if( GET_VALUE( T ) ) ed->trigger[ #T ] = 1
#define MAKE_OBJECT(OBJ, ED) if( !MakeEvent##OBJ( ED ) ) throw runtime_error( "Cannot create " # OBJ )
#define SET_PROPERTY(P) ed->property[ #P ] = GET_VALUE( P )

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

      TChain * chain = new TChain( m_treeName );

      ifstream input( fileListName.c_str(), ios_base::in );
      string fName;
      while( std::getline( input, fName ) ) {
	if( fName.empty() ) continue;

	cout << "INFO: Input file: " << fName << '\n';
	chain->AddFile( fName.c_str() );
      }

      m_ntuple->Init( chain );
       
      input.close();

      return success;
    };

    UInt_t        SetActiveBranches( const string listFileName = "branch_list.txt" )
    {  
      if( !m_ntuple->fChain ) throw runtime_error( "Ntuple chain has not been created\n" );

      m_ntuple->fChain->SetBranchStatus( "*", 0 );

      UInt_t Nbranches = 0;

      cout << "DEBUG: list of active branches from " << listFileName << endl;

      ifstream input( listFileName, ios_base::in );
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
      ed->property = m_config.custom_params;
  
      MAKE_OBJECT( Info, ed );
      MAKE_OBJECT( Truth, ed );    
      MAKE_OBJECT( Trigger, ed );
      MAKE_OBJECT( MET, ed );
      MAKE_OBJECT( Electrons, ed );
      MAKE_OBJECT( Leptons, ed );

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

