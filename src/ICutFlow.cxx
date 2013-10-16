#include "ICutFlow.h"

CutFlow::CutFlow( const string& name ) : m_name( name ), m_counterName(""), m_lastCutPassed(-1), m_hm(NULL)
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

  m_lastCutPassed = 0;

  return success;
}


///////////////////////////////////////


void CutFlow::Connect( const string& name, int cutN )
{
}


///////////////////////////////////////


void CutFlow::PassedCut( const double weight )
{
  ++m_lastCutPassed;

  if( !m_counterName.empty() ) {
    double val = m_hm->GetHistogram( m_counterName )->GetBinContent( m_lastCutPassed );
    m_hm->GetHistogram( m_counterName )->SetBinContent( m_lastCutPassed, val + weight );
  }
}


///////////////////////////////////////


void CutFlow::PrintOutStats()
{
   if( m_counterName.empty() ) return;
 
   TH1 * p_cfh = m_hm->GetHistogram( m_counterName );
   const int ncuts = p_cfh->GetNbinsX();

   cout	<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
   cout << " * Cut flow: " << p_cfh->GetTitle() << endl << endl;

   for( int nc = 0 ; nc < ncuts ; ++nc ) {
        printf( "%2i) %-20s %10.0f\n", nc, p_cfh->GetXaxis()->GetBinLabel(nc+1), p_cfh->GetBinContent(nc+1) );
   } 

   cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
}


///////////////////////////////////////


void CutFlow::SetCutName( int n, const char * name )
{
   if( m_counterName.empty() ) return;

   TH1 * p_cfh = m_hm->GetHistogram( m_counterName );
   if( !p_cfh ) {
       cout << "WARNING: no cut flow histogram defined with name " << m_counterName << endl;
       return;
   } 

   TAxis * p_x = (TAxis*)p_cfh->GetXaxis();

   p_x->SetBinLabel( n+1, name );
}
