#ifndef __CONFIGMANAGER_H__
#define __CONFIGMANAGER_H__

#include <libxml/xmlmemory.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <libxml/xpath.h>

#include "Commons.h"

/////////////////////////////

struct AnalysisParams_t {
    string fileListName;
    string histoFileName;
    string cutflowName;
    string treeName;
    string branchFileName;
    string ntupleName;
    map< string, double >        custom_params_numeric;
    map< string, unsigned long > custom_params_flag;
    map< string, string >        custom_params_string;
    LeptonFlavor channel;
};

/////////////////////////////

class ConfigManager
{
 public:
  virtual ~ConfigManager() {};
  static ConfigManager * GetHandle() { static ConfigManager instance; return &instance; };

  bool Configure( const char * configFileName, AnalysisParams_t& analysisParams );

  inline AnalysisParams_t  * GetConfiguration() { return &m_params; };

 private:
  ConfigManager();

  AnalysisParams_t m_params;
};

#endif /** __CONFIGMANAGER_H__ */
