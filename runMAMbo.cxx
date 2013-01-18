#include <unistd.h>
#include <stdlib.h>

#include <libxml/xmlmemory.h>
#include <libxml/parser.h>
#include <libxml/tree.h>

using namespace std;

#include "HistogramManager.h"
#include "CutFlowFactory.hpp"
#include "PluginManager.h"

#include "MiniSLBoostWrapper.h"

/////////////////////////////


struct globalArgs_t {
  char     * listFileName;
  char     * paramsFileName;
  char     * outFileName;
  Long64_t   eventMax;
} globalArgs;

static const char * options = "p:o:f:b:t:n:vh?";


struct analysisParams_t {
  string histoFileName;
  string cutflowName;
  string treeName;
  string branchFileName;
} analysisParams;


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
  xmlDocPtr doc = xmlParseFile( globalArgs.paramsFileName );
  xmlNodePtr nodeRoot = doc->children;
  for( xmlNodePtr nodeParam = nodeRoot->children; nodeParam != NULL; nodeParam = nodeParam->next ) {
    if( xmlStrEqual( nodeParam->name, BAD_CAST "histograms" ) ) {
      analysisParams.histoFileName = (const char*)xmlNodeListGetString( doc, nodeParam->xmlChildrenNode, 1 );
    }
    else if( xmlStrEqual( nodeParam->name, BAD_CAST "cutflow" ) ) {
      analysisParams.cutflowName = (const char*)xmlNodeListGetString( doc, nodeParam->xmlChildrenNode, 1 );
    }
    else if( xmlStrEqual( nodeParam->name, BAD_CAST "tree" ) ) {
      analysisParams.treeName = (const char*)xmlNodeListGetString( doc, nodeParam->xmlChildrenNode, 1 );
    }
    else if( xmlStrEqual( nodeParam->name, BAD_CAST "branches" ) ) {
      analysisParams.branchFileName = (const char*)xmlNodeListGetString( doc, nodeParam->xmlChildrenNode, 1 );
	//string( (const char*) nodeParam->children->name );
    }
  }
  xmlFreeDoc( doc );
  // XML config
  
  PluginManager * pluginManager = PluginManager::GetHandle();
  pluginManager->LoadCutFlowPlugin( analysisParams.cutflowName );

  CutFlowFactory * CF_Factory = CutFlowFactory::GetHandle();
  CF_Factory->Dump();

  MiniSLBoostWrapper * wrapper = new MiniSLBoostWrapper( globalArgs.listFileName, analysisParams.branchFileName.c_str(), analysisParams.treeName.c_str() );

  if( !wrapper->AddCutFlow( analysisParams.cutflowName ) )
    throw runtime_error( "Cannot add cutflow\n" );

  HistogramManager * hm = HistogramManager::GetHandle();
  if( !hm->SetOutFileName( globalArgs.outFileName ) ) throw runtime_error( "Cannot initialize histogram manager\n" );
  hm->ConfigureFromXML( analysisParams.histoFileName );
 
  const Long64_t nEntries = wrapper->GetEntries();
 
  cout << "Event found in ntuple: " << nEntries << endl;

  if( globalArgs.eventMax == -1 ) globalArgs.eventMax = nEntries;
  if( globalArgs.eventMax > nEntries ) globalArgs.eventMax = nEntries;

  cout << "Loop on " << globalArgs.eventMax << " events" << endl;

  wrapper->Loop( globalArgs.eventMax );

  hm->WriteToFile();

  delete wrapper;

  return status;
}
