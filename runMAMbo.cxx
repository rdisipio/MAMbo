#include <unistd.h>
#include <stdlib.h>

using namespace std;

#include "HistogramManager.h"
#include "CutFlowFactory.hpp"
#include "PluginManager.h"
#include "ConfigManager.h"

/////////////////////////////


struct globalArgs_t {
  char     * listFileName;
  char     * paramsFileName;
  char     * outFileName;
  Long64_t   eventMax;
} globalArgs;

static const char * options = "p:o:f:b:t:n:vh?";


/////////////////////////////


int main( int argc, char ** argv )
{
  int status = 0;

  globalArgs.listFileName    = new char[1024]; strcpy( globalArgs.listFileName,   "control/file_list.txt" );
  globalArgs.paramsFileName  = new char[1024]; strcpy( globalArgs.paramsFileName, "control/analysis_params.xml" );
  globalArgs.outFileName     = new char[1024]; strcpy( globalArgs.outFileName,    "histograms.root" );
  globalArgs.eventMax        = -1;

  int opt = getopt( argc, argv, options );
  while( opt != -1 ) {
    switch( opt ) {
    case 'p':
      strcpy( globalArgs.paramsFileName, optarg );
      break;
    case 'f':
      strcpy( globalArgs.listFileName, optarg );
      break;
    case 'o':
      strcpy( globalArgs.outFileName, optarg );
      break;
    case 'n':
      globalArgs.eventMax = atol( optarg );
      break;
    default:
      break;
    };
    opt = getopt( argc, argv, options );
  }

  // XML config
  AnalysisParams_t analysisParams;
  ConfigManager * configManager = ConfigManager::GetHandle();
  configManager->Configure( globalArgs.paramsFileName, analysisParams );
  // XML config
  
  PluginManager * pluginManager = PluginManager::GetHandle();
  pluginManager->LoadCutFlowPlugin( analysisParams.cutflowName );

  CutFlowFactory * CF_Factory = CutFlowFactory::GetHandle();
  CF_Factory->Dump();
 
  pluginManager->LoadNtupleWrapperPlugin( analysisParams.ntupleName );
  NtupleWrapperFactory * NW_Factory = NtupleWrapperFactory::GetHandle();
  NW_Factory->Dump();

  INtupleWrapper * wrapper = NW_Factory->Create( analysisParams.ntupleName, 
						 globalArgs.listFileName, 
						 analysisParams.branchFileName.c_str(), 
						 analysisParams.treeName.c_str() ); 

  if( !wrapper->AddCutFlow( analysisParams.cutflowName ) )
    throw runtime_error( "Cannot add cutflow\n" );

  HistogramManager * hm = HistogramManager::GetHandle();
  if( !hm->SetOutFileName( globalArgs.outFileName ) ) throw runtime_error( "Cannot initialize histogram manager\n" );
  hm->ConfigureFromXML( analysisParams.histoFileName );
 
  const Long64_t nEntries = wrapper->GetEntries();
 
  cout << "INFO: No. of events found in ntuple: " << nEntries << endl;

  if( globalArgs.eventMax == -1 ) globalArgs.eventMax = nEntries;
  if( globalArgs.eventMax > nEntries ) globalArgs.eventMax = nEntries;

  cout << "INFO: MAMbo will loop on " << globalArgs.eventMax << " events" << endl;

  wrapper->Loop( globalArgs.eventMax );

  hm->WriteToFile();

  delete wrapper;

  return status;
}
