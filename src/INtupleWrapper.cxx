#include "INtupleWrapper.h"

INtupleWrapper::INtupleWrapper( const AnalysisParams_t analysisParameters ) : 
  m_hm(NULL),
  m_treeName( analysisParameters.treeName.c_str() ), m_thisEvent(NULL), m_thisEventNumber(-1), m_maxEvents(-1)
{
  if( !SetupTools() ) throw runtime_error( "Cannot setup wrapper tools\n" );
}
 

INtupleWrapper::~INtupleWrapper()
{
}


//////////////////////////////////////////


bool INtupleWrapper::SetupTools()
{
  bool success = true;

  m_hm         = HistogramManager::GetHandle();

  return success;
}


//////////////////////////////////////////


CutFlow * INtupleWrapper::AddCutFlow( const string& name )
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


void INtupleWrapper::Loop( Long64_t nEventsMax )
{
  m_maxEvents = nEventsMax;

  m_thisEventNumber = 0; // default = uninitialized = -1

  for( CutFlowCollection_t::const_iterator itr = m_cutFlows.begin() ; itr != m_cutFlows.end() ; ++itr ) {
      itr->second->Initialize();
  }

  for( Long64_t i = 0 ; i < m_maxEvents ; ++i ) {
    m_thisEvent = NextEvent();

    if( !m_thisEvent ) {
       printf( "WARNING: Could not process event %i. Skipping..\n", i );
       continue; 
    }

    for( CutFlowCollection_t::const_iterator itr = m_cutFlows.begin() ; itr != m_cutFlows.end() ; ++itr ) {
      itr->second->Apply( m_thisEvent );
    }

  } // event loop

  for( CutFlowCollection_t::const_iterator itr = m_cutFlows.begin() ; itr != m_cutFlows.end() ; ++itr ) {
      itr->second->Finalize();
  }
}


//////////////////////////////////////////


EventData * INtupleWrapper::NextEvent()
{
   if( m_thisEvent ) delete m_thisEvent;
   m_thisEvent = NULL;

   try {
     m_thisEvent = MakeEvent( (++m_thisEventNumber-1) ); // must be implemented at some point downstream
   }
   catch( runtime_error & err ) {
     printf( "ERROR: could not process event %i due to %s\n", (++m_thisEventNumber-1), err.what() );
   }

   if( ( m_maxEvents < 10 ) || ( m_thisEventNumber % int(m_maxEvents/10) ) == 0 ) {
     double perc = 100. * m_thisEventNumber / m_maxEvents;
     printf( "INFO: Event %-9i (en = %-10i rn = %-10i )       (%3.0f %%)\n", 
             m_thisEventNumber, m_thisEvent->info.eventNumber, m_thisEvent->info.runNumber, perc );
   }

   return m_thisEvent;
}


//////////////////////////////////////////

void INtupleWrapper::Finalize()
{
   for( CutFlowCollection_t::const_iterator itr = m_cutFlows.begin() ; itr != m_cutFlows.end() ; ++itr ) {
      itr->second->PrintOutStats();
    }
}


//////////////////////////////////////////


