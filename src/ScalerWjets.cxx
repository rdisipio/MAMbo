#include "ScalerWjets.h"
#include "Commons.h"
#include "EventData.h"

using namespace PhysicsHelperFunctions;



ScalerWjets * ScalerWjets::m_instance = NULL;
ScalerWjets::ScalerWjets( int channel, string syst )
{
  m_channel = channel;
  m_systematic = syst;
  cout << "DEBUG: initializing wjets weights interface for channel " << (channel == 0 ? "el" : "mu") << " and systematic " << syst << "\n";

  string basePath = string( getenv( "MAMBODIR" ) ) + "/share/data/WjetsScaleFactors";
	  m_weightsFilename = basePath + "/Wjets_CA_" +  ( channel == 0 ? "el.root" : "mu.root" ); 
	  cout << "DEBUG: getting weight histogram from " << m_weightsFilename << endl;
	  m_weightsFile = TFile::Open( m_weightsFilename.c_str() );
	  m_weights = (TH2D*) m_weightsFile->Get( m_systematic.c_str() );
  cout << "Tool inizialized. Weights are:\n";
  cout << "\t";
  for( int i = 0; i < 5; ++i )
  {
	  cout << i << "j\t";
  }
  cout << endl;
  for( int j = 0; j < 2; ++j )
  {
	  cout << j << "bj\t";
	  for( int i = 0; i < 5; ++i )
	  {
		cout << m_weights->GetBinContent( i+1, j+1 ) << "\t";
      }
	  cout << endl;
  }
}


ScalerWjets::~ScalerWjets( )
{
	m_weightsFile->Close();
	delete m_weightsFile;
  //delete m_tightEff;
}

ScalerWjets * ScalerWjets::GetHandle( int channel, string syst )
{
  if( m_instance == NULL ) m_instance = new ScalerWjets( channel, syst );
  else
  {
    if( channel != m_instance->GetChannel()  || syst != m_instance->GetSystematic() ) 
    {
      char msg[100];
      sprintf( msg,"ScalerWjets requested  with channel == %i and syst == %s \
      but an instance already exists with channel == %i and syst == %si\n", channel, syst.c_str(),  m_instance->GetChannel(),  m_instance->GetSystematic().c_str() );
      throw std::runtime_error( msg );
    }
  }
  return m_instance;
}

double ScalerWjets::GetWjetsWeight( int njets, int nbjets){
  
  int x = njets <= 4 ? njets+1 : 5;
  int y = nbjets <= 1 ? nbjets+1 : 2;
  return m_weights->GetBinContent( x, y );
  
}

