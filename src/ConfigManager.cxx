#include "ConfigManager.h"

ConfigManager::ConfigManager()
{

}


bool ConfigManager::Configure( const char * configFileName, AnalysisParams_t& analysisParams )
{
  bool success = true;

  xmlDocPtr doc = xmlParseFile( configFileName );
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
    else if( xmlStrEqual( nodeParam->name, BAD_CAST "ntuple" ) ) {
      analysisParams.ntupleName = (const char*)xmlNodeListGetString( doc, nodeParam->xmlChildrenNode, 1 );
    }
    else if(  xmlStrEqual( nodeParam->name, BAD_CAST "cuts" ) ) {
      xmlNodePtr nodeCuts = nodeParam->children;

      for( xmlNodePtr aCut = nodeCuts->children ; aCut != NULL ; aCut = aCut->next ) {
	string name( (const char *)xmlGetProp( aCut, BAD_CAST "name" ) );
	double val = atof( (const char*)xmlGetProp( aCut, BAD_CAST "value" ) );

	analysisParams.cuts[name] = val;
      }
    }
  }
  xmlFreeDoc( doc );
  
  m_params = analysisParams;

  return success;
}
