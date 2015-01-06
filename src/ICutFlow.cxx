#include <sstream>

#include "ICutFlow.h"

CutFlow::CutFlow( const string& name ) : m_name( name ), m_hm(NULL)
{
   m_hm     = HistogramManager::GetHandle();
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

/*
bool CutFlow::Apply( EventData * ed )
{
   bool success = true;
   
   cout << "base class apply" << endl;

   return success;
}
*/

///////////////////////////////////////


void CutFlow::AddChannel( const string& name ) 
{
  m_channelName.push_back( name ); 

  cout << "INFO: Added analysis channel " << name << endl;
};


///////////////////////////////////////


void CutFlow::AddCounterName( const string& channelName, const string& counterName, unsigned int ncuts ) 
{
  m_counter2channel[counterName] = channelName;
  m_counterName[channelName].push_back( counterName );

  cout << "INFO: Channel " << channelName << " | added counter " << counterName << endl;

  const unsigned int nbins = ncuts + 1;

  stringstream histName;
  histName << channelName << "_cutflow_" << counterName;

  stringstream histTitle;
  histTitle << "Cutflow " << channelName << " " << counterName;
  
  m_hm->Book1DHistogramInFolder( "", histName.str(), histTitle.str(), nbins, -0.5, nbins-0.5 );

  //cout << "DEBUG: Histo created in base folder with name " << histName.str() << endl;
  SetCutName( channelName, counterName, 0, "AllEvents" );  
  char buf[32];
  for( unsigned int nc = 1 ; nc <= ncuts ; ++nc ) {
    sprintf( buf, "Cut %i", nc );
    SetCutName( channelName, counterName, nc, buf );
  }

};


///////////////////////////////////////


bool CutFlow::IncreaseCount( const string& histName, unsigned int cut, double weight, double * new_value )
{
  TH1 * p_h = m_hm->GetHistogram( histName );

  if( !p_h ) return false;

  const unsigned int bin = cut + 1;

  double old_count = p_h->GetBinContent( bin );
  double new_count = old_count + weight;
  p_h->SetBinContent( bin, new_count );

  if( new_value ) *new_value = new_count;

  return true;
}


///////////////////////////////////////


void CutFlow::PassedCut( const string& channelName, const string& counterName, const double weight )
{
  stringstream histName;
  histName << channelName << "_cutflow_" << counterName;

  m_lastCutPassed[histName.str()] += 1;
  const int cut = m_lastCutPassed[histName.str()] - 1;
  
  if( !IncreaseCount( histName.str(), cut, weight ) ) {
    histName.str("");
    histName << channelName << "_" << counterName;
    
    if( !IncreaseCount( histName.str(), cut, weight ) ) {
      cout << "ERROR: invalid cut flow " << histName.str() << endl;
      throw runtime_error( "CutFlow::PassedCut: invalid cut flow\n" );
    }
  }
}


///////////////////////////////////////


int CutFlow::GetLastPassedCut( const string& channelName, const string& counterName ) const
{
    stringstream histName;
    histName << channelName << "_cutflow_" << counterName;
  
    return m_lastCutPassed.at( histName.str() );
}


///////////////////////////////////////


void CutFlow::PrintOutStats()
{
  for( vector< string >::const_iterator itrCh = m_channelName.begin() ; itrCh != m_channelName.end() ; ++itrCh ) {
    vector< string > * counters = &( m_counterName[(*itrCh)] );
    
    for( vector< string >::const_iterator itrCt = counters->begin() ; itrCt != counters->end() ; ++itrCt ) {
      stringstream histName;
      histName << (*itrCh) << "_cutflow_" << (*itrCt);
      
      TH1 * p_h_cf = m_hm->GetHistogram( histName.str() );
      if( !p_h_cf ) {
	histName.str("");
	histName << (*itrCh) << "_" << (*itrCt);
	p_h_cf = m_hm->GetHistogram( histName.str() );
      }
      if( !p_h_cf ) {
	char buf[256];
	sprintf( buf, "Invalid histogram %s\n", histName.str().c_str() );
	throw runtime_error( buf );
      }
      const int ncuts = p_h_cf->GetNbinsX();

      cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
      cout << " * " << p_h_cf->GetTitle() << endl << endl;

      for( int nc = 0 ; nc < ncuts ; ++nc ) {
	printf( "%2i) %-30s %10.0f\n", nc, p_h_cf->GetXaxis()->GetBinLabel(nc+1), p_h_cf->GetBinContent(nc+1) );
      } 

      cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    }
  }
  

  
 
   
}


///////////////////////////////////////


void CutFlow::SetCutName( const string& channelName, const string& counterName, int n, const char * cutName )
{
  stringstream histName;
  histName << channelName << "_cutflow_" << counterName;

  //cout<< "DEBUG: histName: "<<histName.str()<< " From: "<<channelName << " " <<counterName << endl;
  
  TH1 * p_h_cf = m_hm->GetHistogram( histName.str() );
  if( !p_h_cf ) {
    histName.str("");
    histName << channelName << "_" << counterName;
    //cout<< "DEBUG: First name failed, now trying name: "<<histName.str()<<endl;
    p_h_cf = m_hm->GetHistogram( histName.str() );
  }
  if( !p_h_cf ) {
    cout << "WARNING: no cut flow histogram defined with name " << histName.str() << endl;
    return;
  } 

  TAxis * p_x = (TAxis*)p_h_cf->GetXaxis();
  
  p_x->SetBinLabel( n+1, cutName );
}
