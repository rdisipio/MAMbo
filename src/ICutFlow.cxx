#include <sstream>

#include "ICutFlow.h"

CutFlow::CutFlow( const string& name ) : m_name( name ), m_hm(NULL)
{
   m_hm = HistogramManager::GetHandle();
   m_config = ConfigManager::GetHandle()->GetConfiguration();
}

CutFlow::~CutFlow()
{
}


///////////////////////////////////////


bool CutFlow::Initialize()
{
   bool success = true;

   return success;
}


///////////////////////////////////////


bool CutFlow::Start()
{
  bool success = true;

  for( map<string,int>::iterator itr = m_lastCutPassed.begin() ; itr != m_lastCutPassed.end() ; ++itr ) {
    (*itr).second = 0;
  }

  return success;
}


///////////////////////////////////////


void CutFlow::AddChannel( const string& name ) 
{
  m_channelName.push_back( name ); 

  cout << "INFO: Added analysis channel " << name << endl;
};


///////////////////////////////////////


void CutFlow::AddCounterName( const string& channelName, const string& counterName, unsigned int nbins ) 
{
  m_counter2channel[counterName] = channelName;
  m_counterName[channelName].push_back( counterName );

  cout << "INFO: Channel " << channelName << " | added counter " << counterName << endl;

  if( nbins == 0 ) return;

  stringstream histName;
  histName << channelName << "_cutflow_" << counterName;

  stringstream histTitle;
  histTitle << "Cutflow " << channelName << " " << counterName;

  m_hm->Book1DHistogram( histName.str(), histTitle.str(), nbins, -0.5, nbins-0.5 );

};


///////////////////////////////////////


void CutFlow::PassedCut( const string& channelName, const string& counterName, const double weight )
{
  stringstream histName;
  histName << channelName << "_" << counterName;

  m_lastCutPassed[counterName] += 1;
  const int bin = m_lastCutPassed[counterName];

  TH1 * p_h = m_hm->GetHistogram( histName.str() );

  double old_count = p_h->GetBinContent( bin );
  p_h->SetBinContent( bin, old_count + weight );
  
}


///////////////////////////////////////


void CutFlow::PrintOutStats()
{
  for( vector< string >::const_iterator itrCh = m_channelName.begin() ; itrCh != m_channelName.end() ; ++itrCh ) {
    vector< string > * counters = &( m_counterName[(*itrCh)] );
    
    for( vector< string >::const_iterator itrCt = counters->begin() ; itrCt != counters->end() ; ++itrCt ) {
      stringstream histName;
      histName << (*itrCh) << "_" << (*itrCt);
      
      TH1 * p_cfh = m_hm->GetHistogram( histName.str() );
      const int ncuts = p_cfh->GetNbinsX();

      cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
      cout << " * Cut flow: " << p_cfh->GetTitle() << endl << endl;

      for( int nc = 0 ; nc < ncuts ; ++nc ) {
	printf( "%2i) %-20s %10.0f\n", nc, p_cfh->GetXaxis()->GetBinLabel(nc+1), p_cfh->GetBinContent(nc+1) );
      } 

      cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    }
  }
  

  
 
   
}


///////////////////////////////////////


void CutFlow::SetCutName( const string& channelName, const string& counterName, int n, const char * cutName )
{
  stringstream histName;
  histName << channelName << "_" << counterName;

  TH1 * p_cfh = m_hm->GetHistogram( histName.str() );
  if( !p_cfh ) {
    cout << "WARNING: no cut flow histogram defined with name " << histName << endl;
    return;
  } 

  TAxis * p_x = (TAxis*)p_cfh->GetXaxis();
  
  p_x->SetBinLabel( n+1, cutName );
}
