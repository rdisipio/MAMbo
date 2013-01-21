#ifndef __CONFIGMANAGER_H__
#define __CONFIGMANAGER_H__

#include <libxml/xmlmemory.h>
#include <libxml/parser.h>
#include <libxml/tree.h>

#include "Commons.h"


/////////////////////////////


struct AnalysisParams_t {
  string histoFileName;
  string cutflowName;
  string treeName;
  string branchFileName;
  string ntupleName;
};


/////////////////////////////


class ConfigManager
{
 public:
  virtual ~ConfigManager() {};
  static ConfigManager * GetHandle() { static ConfigManager instance; return &instance; };

  bool Configure( const char * configFileName, AnalysisParams_t& analysisParams );

 private:
  ConfigManager();

};

#endif /** __CONFIGMANAGER_H__ */
