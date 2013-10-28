#ifndef __PLUGINMANAGER_H__
#define __PLUGINMANAGER_H__

#include <dlfcn.h>

#include <string>
#include <map>

#include "CutFlowFactory.hpp"
#include "NtupleWrapperFactory.hpp"

typedef map< string, string > PluginMap;
typedef map< string, void* >  HandleMap;

class PluginManager
{
public:
  virtual ~PluginManager() {};

  static PluginManager * GetHandle();

  int FindPlugins( const string& pattern, PluginMap& pluginFound );
  int FindPlugins( const string& dir, const string& pattern, PluginMap& pluginFound );

  int LoadCutFlows();

  bool LoadCutFlowPlugin( const string& name, const string& path = "" );
  bool LoadNtupleWrapperPlugin( const string& name, const string& path = "" );

 private:
  PluginManager() {};

  void * LoadPlugin( const string& name );

 private:
  HandleMap m_handles;
  PluginMap m_cutflows;
  PluginMap m_ntuples;
};


#endif /** __PLUGINMANAGER_H__ */
