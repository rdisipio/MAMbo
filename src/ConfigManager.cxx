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
      
	string name = "unset";
        string type = "unknown";

	xmlAttr *attr = node->properties;
	while ( attr ){
	  if( xmlStrEqual( attr->name, BAD_CAST "name" ) )  name  = (const char*) attr->children->content;

          if( xmlStrEqual( attr->name, BAD_CAST "type" ) )  type = (const char*) attr->children->content;
          
	  if( xmlStrEqual( attr->name, BAD_CAST "value" ) ) {
              if( type == "numeric" ) {
                  double value = atof( (const char*)attr->children->content );
		  analysisParams.custom_params_numeric[name] = value;
		  cout << "INFO: numeric parameter " << name << " value = " << analysisParams.custom_params_numeric[name] << endl;
	      }	      
	      else if( type == "flag" ) {
		unsigned long value = atol( (const char*)attr->children->content );
		analysisParams.custom_params_flag[name] = value;
		cout << "INFO: flag parameter " << name << " value = " << analysisParams.custom_params_flag[name] << endl;
	      }
              else if( type == "string"  ) {
		string value( (const char*) attr->children->content );
		cout << name << ": " << value << endl;
		analysisParams.custom_params_string[name] = value;
		cout << "INFO: string parameter " << name << " value = " << analysisParams.custom_params_string.at(name) << endl;
              }
	      else throw runtime_error( "Invalid paramter type. Select numeric|flag|string" );
          }

	  attr = attr->next;
          
	}
      }

      xmlXPathFreeObject( xpathObj );
      xmlXPathFreeContext( xpathCtx );
    }
  }
  xmlFreeDoc( doc );
  xmlCleanupParser();

  m_params = analysisParams;

  return success;
}
