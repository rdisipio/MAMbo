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
    else if( xmlStrEqual( nodeParam->name, BAD_CAST "channel" ) ) {
        string ch = (const char*)xmlNodeListGetString( doc, nodeParam->xmlChildrenNode, 1 );                
        if (ch == "electron" || ch == "kElectron") {
            analysisParams.channel = kElectron;
	}
        else if (ch == "muon" || ch == "kMuon") {
            analysisParams.channel = kMuon;
	}
        cout<< "Analysing channel: " << analysisParams.channel<< endl;
    }
    else if( xmlStrEqual( nodeParam->name, BAD_CAST "ntuple" ) ) {
      analysisParams.ntupleName = (const char*)xmlNodeListGetString( doc, nodeParam->xmlChildrenNode, 1 );
    }
    else if(  xmlStrEqual( nodeParam->name, BAD_CAST "parameters" ) ) {
      xmlXPathContext * xpathCtx = xmlXPathNewContext( doc );
      xmlXPathObject  * xpathObj = xmlXPathEvalExpression( (xmlChar*)"/analysis/parameters/param", xpathCtx );

      for( int inode = 0 ; inode < xpathObj->nodesetval->nodeNr ; ++inode ) {
	xmlNode *node = xpathObj->nodesetval->nodeTab[inode];
      
	string name;
	double value = 0;

	xmlAttr *attr = node->properties;
	while ( attr ){
	  if( xmlStrEqual( attr->name, BAD_CAST "name" ) )  name  = (const char*) attr->children->content;
	  if( xmlStrEqual( attr->name, BAD_CAST "value" ) ) value = atof( (const char*)attr->children->content );

	  // std::cout << "Attribute name: " << attr->name << "  value: " << attr->children->content << std::endl;
	  attr = attr->next;
	}
	analysisParams.custom_params[name] = value;

	cout << "INFO: parameter " << name << " values = " << analysisParams.custom_params[name] << endl;
      }

      xmlXPathFreeObject( xpathObj );
      xmlXPathFreeContext( xpathCtx );
    }
    /*
    else if(  xmlStrEqual( nodeParam->name, BAD_CAST "parameters" ) ) {
      xmlNodePtr nodeCustomParams = nodeParam->children;

      cout << "INFO: found some parameters" << endl;

      for( xmlNodePtr aCustomParam = nodeCustomParams->children ; aCustomParam != NULL ; aCustomParam = aCustomParam->next ) {

	string name( (const char *)xmlGetProp( aCustomParam, BAD_CAST "name" ) );
	double val = atof( (const char*)xmlGetProp( aCustomParam, BAD_CAST "value" ) );

	analysisParams.custom_params[name] = val;

	cout << "INFO: parameter " << name << " values = " << analysisParams.custom_params[name] << endl;
      }
    }
    */
  }
  xmlFreeDoc( doc );
  xmlCleanupParser();

  m_params = analysisParams;

  return success;
}
