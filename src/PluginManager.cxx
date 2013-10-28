#include "PluginManager.h"

PluginManager * PluginManager::GetHandle()
{
  static PluginManager instance;
  return &instance;
}


///////////////////////////////////


int PluginManager::FindPlugins( const string& dir, const string& pattern, PluginMap& pluginFound )
{
  cout << "DEBUG: Looking for plugins in directory " << dir << endl;

  vector<string> files = vector<string>();
  HelperFunctions::ListDirectory( dir, files );
    
  for( vector<string>::const_iterator itr = files.begin() ; itr != files.end() ; ++itr ) {
    const string fileName = (*itr);
    if( fileName.find( ".so" ) == string::npos ) continue;
      
    if( fileName.find( pattern ) != string::npos ) {
      const string& pluginName = fileName.substr( 10, fileName.size() - 13 );
      pluginFound[pluginName] = dir + fileName;
    }
  }

  return pluginFound.size();
}


//~~~~~~~~~~~~~~~~~~~~~~~~~


int PluginManager::FindPlugins( const string& pattern, PluginMap& pluginFound )
{
  const string& pwd = string( getenv( "PWD" ) ) + "/";

  return FindPlugins( pwd, pattern, pluginFound );
}

///////////////////////////////////


void * PluginManager::LoadPlugin( const string& name )
{
  if( name.empty() ) throw runtime_error( "Please specify plugin name\n" );

  //cout << "DEBUG: Looking for " << name << " ..." << endl;

  void * handle = dlopen( name.c_str(), RTLD_LAZY );
  if( !handle ) throw runtime_error( "Cannot load plugin\n" );

  cout << "INFO: Loaded plugin: " << name << endl;
  
  return handle;
}


///////////////////////////////////


int PluginManager::LoadCutFlows()
{ 
  ICutFlowPluginFactory * pluginFactory = NULL;

  FindPlugins( "CutFlow", m_cutflows );

  const string mambodir = string( getenv( "MAMBODIR" ) ) + "/lib/";
  FindPlugins( mambodir, "CutFlow", m_cutflows );

  for( PluginMap::const_iterator pair = m_cutflows.begin() ; pair != m_cutflows.end() ; ++pair ) {
    //cout << "INFO: Found cutflow wrapper " << (*pair).first << endl;

    void* handle = LoadPlugin( (*pair).second );

    fp_MakeCutFlowPlugin    MakeCutFlowPlugin = (fp_MakeCutFlowPlugin)dlsym( handle, "MakeCutFlowPlugin" );
    if( !MakeCutFlowPlugin ) throw runtime_error( "Invalid pointer to function to create cut flow plugin\n" );

    pluginFactory = MakeCutFlowPlugin();
    
    pluginFactory->Register();
  }
}


///////////////////////////////////


bool PluginManager::LoadCutFlowPlugin( const string& name, const string& path )
{
  bool success = true;

  stringstream fullpath;
  if( path.empty() ) fullpath << getenv( "MAMBODIR" ) << "/lib";
  else {
     fullpath << path;
  } 

  char libCutFlowFileName[128];
  sprintf( libCutFlowFileName,  "%s/libCutFlow%s.so", fullpath.str().c_str(), name.c_str() );
  void* handle = LoadPlugin( libCutFlowFileName );
  
  ICutFlowPluginFactory * pluginFactory     = NULL;

  fp_MakeCutFlowPlugin    MakeCutFlowPlugin = (fp_MakeCutFlowPlugin)dlsym( handle, "MakeCutFlowPlugin" );
  if( !MakeCutFlowPlugin ) throw runtime_error( "Invalid pointer to function to create cut flow plugin\n" );

  pluginFactory = MakeCutFlowPlugin();

  pluginFactory->Register();

  return success;
}


///////////////////////////////////


bool PluginManager::LoadNtupleWrapperPlugin( const string& name, const string& path )
{
  bool success = true;

  stringstream fullpath;
  if( path.empty() ) fullpath << getenv( "MAMBODIR" ) << "/lib";
  else {
     fullpath << path;
  } 

  char libNtupleWrapperFileName[128];
  sprintf( libNtupleWrapperFileName,  "%s/libNtupleWrapper%s.so", fullpath.str().c_str(), name.c_str() );
  void* handle = LoadPlugin( libNtupleWrapperFileName );

  INtupleWrapperPluginFactory * pluginFactory     = NULL;

  fp_MakeNtupleWrapperPlugin    MakeNtupleWrapperPlugin = (fp_MakeNtupleWrapperPlugin)dlsym( handle, "MakeNtupleWrapperPlugin" );
  if( !MakeNtupleWrapperPlugin ) throw runtime_error( "Invalid pointer to function to create ntuple wrapper plugin\n" );

  pluginFactory = MakeNtupleWrapperPlugin();

  pluginFactory->Register();

  return success;
}

