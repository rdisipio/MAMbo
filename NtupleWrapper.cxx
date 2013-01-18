#include "NtupleWrapper.h"

NtupleWrapper::NtupleWrapper( TTree * tree ) : m_ntuple(NULL), m_eventMaker(NULL), m_hm(NULL),
						   m_treeName( "default" ), 
						   m_thisEvent(NULL), m_thisEventNumber(-1), m_maxEvents(-1)
{
  if( !SetupTools() ) throw runtime_error( "Cannot setup wrapper tools\n" );
  
  m_eventMaker->SetNtuple( m_ntuple );
}


NtupleWrapper::NtupleWrapper( const char * fileListName, const char * branchListName, const char * treeName ) : 
  m_eventMaker(NULL), m_ntuple(NULL ), m_hm(NULL),
  m_treeName( treeName ), m_thisEvent(NULL), m_thisEventNumber(-1), m_maxEvents(-1)
{
  if( !SetupTools() ) throw runtime_error( "Cannot setup wrapper tools\n" );
  
  m_eventMaker->SetNtuple( m_ntuple );

  if( !LoadChain( fileListName, treeName ) ) throw runtime_error( "Cannot load file chain\n" );

  SetActiveBranches( branchListName );
}
 

NtupleWrapper::~NtupleWrapper()
{
  delete m_ntuple;
}


//////////////////////////////////////////


bool NtupleWrapper::SetupTools()
{
  bool success = true;

  m_ntuple     = new MiniSLBoost(); //T ?

  m_eventMaker = EventMaker::GetHandle();

  m_hm         = HistogramManager::GetHandle();

  return success;
}


//////////////////////////////////////////


bool NtupleWrapper::LoadChain( const char * fileListName, const char * treeName )
{
  bool success = true;

  TChain * chain = new TChain( m_treeName );

  ifstream input( fileListName, ios_base::in );
  string fName;
  while( std::getline( input, fName ) ) {
    if( fName.empty() ) continue;

    cout << "INFO: Input file: " << fName << '\n';
    chain->AddFile( fName.c_str() );
  }

  m_ntuple->Init( chain );

  input.close();

  return success;
}


//////////////////////////////////////////


UInt_t NtupleWrapper::SetActiveBranches( const char * listFileName )
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

  if( Nbranches == 0 ) throw runtime_error( "No actived branch\n" );

  cout << "DEBUG: No. of active branches = " << Nbranches << endl;

  return Nbranches;
}


//////////////////////////////////////////


CutFlow * NtupleWrapper::AddCutFlow( const string& name )
{
  CutFlowFactory * factory = CutFlowFactory::GetHandle();

  if( !factory ) throw runtime_error( "Cannot get handle to cutflow factory\n" );

  CutFlow * p_cf = factory->Create( name );

  if( !p_cf ) {
    char err[128];
    sprintf( err, "Cannot cutflow %s not registered\n", name.c_str() );
  }

  m_cutFlows[name] = p_cf;

  return m_cutFlows[name];
}


//////////////////////////////////////////


void NtupleWrapper::Loop( Long64_t nEventsMax )
{
  m_maxEvents = nEventsMax - 1;

  m_thisEventNumber = 0; // default = uninitialized = -1

  for( Long64_t i = 0 ; i < m_maxEvents ; ++i ) {
    m_thisEvent = NextEvent();

    if( !m_thisEvent ) throw runtime_error( "Cannot create event\n" );

    for( CutFlowCollection_t::const_iterator itr = m_cutFlows.begin() ; itr != m_cutFlows.end() ; ++itr ) {
      itr->second->Apply( m_thisEvent );
    }
  }

}

//////////////////////////////////////////



EventData * NtupleWrapper::NextEvent()
{
   if( m_thisEvent ) delete m_thisEvent;

   m_thisEvent = m_eventMaker->MakeEvent( ++m_thisEventNumber );

   if( ( m_thisEventNumber % int(m_maxEvents/10) ) == 0 ) {
     double perc = 100. * m_thisEventNumber / m_maxEvents;
     printf( "INFO: Event %i (n = %i, r = %i ) (%3.0f %%)\n", m_thisEventNumber, m_thisEvent->info.eventNumber, m_thisEvent->info.runNumber, perc );
   }

   return m_thisEvent;
}
