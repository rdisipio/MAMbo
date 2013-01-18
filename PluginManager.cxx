#include "PluginManager.h"

PluginManager * PluginManager::GetHandle()
{
  static PluginManager instance;
  return &instance;
}


///////////////////////////////////


void * PluginManager::LoadPlugin( const string& name )
{
  if( name.empty() ) throw runtime_error( "Please specify plugin name\n" );

  cout << "Looking for " << name << " ..." << endl;

  void * handle = dlopen( name.c_str(), RTLD_LAZY );
  if( !handle ) throw runtime_error( "Cannot load plugin\n" );

  cout << "INFO: Loaded plugin: " << name << endl;
  
  return handle;
}


///////////////////////////////////


bool PluginManager::LoadCutFlowPlugin( const string& name )
{
  bool success = true;

  char libCutFlowFileName[128];
  sprintf( libCutFlowFileName,  "%s/libCutFlow%s.so", getenv( "PWD" ), name.c_str() );
  void* handle = LoadPlugin( libCutFlowFileName );
  
  ICutFlowPluginFactory * pluginFactory     = NULL;

  fp_MakeCutFlowPlugin    MakeCutFlowPlugin = (fp_MakeCutFlowPlugin)dlsym( handle, "MakeCutFlowPlugin" );
  if( !MakeCutFlowPlugin ) throw runtime_error( "Invalid pointer to function to create cut flow plugin\n" );

  pluginFactory = MakeCutFlowPlugin();

  pluginFactory->Register();

  return success;
}
