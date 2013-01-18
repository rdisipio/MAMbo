#ifndef __PLUGINMANAGER_H__
#define __PLUGINMANAGER_H__

#include <dlfcn.h>

#include <string>
#include <map>

#include "CutFlowFactory.hpp"

typedef map< string, string > PluginMap;
typedef map< string, void* >  HandleMap;

class PluginManager
{
public:
  virtual ~PluginManager() {};

  static PluginManager * GetHandle();

  bool LoadCutFlowPlugin( const string& name );

 private:
  PluginManager() {};

  void * LoadPlugin( const string& name );

 private:
  HandleMap m_handles;
  PluginMap m_cutflows;
  
};


#endif /** __PLUGINMANAGER_H__ */
