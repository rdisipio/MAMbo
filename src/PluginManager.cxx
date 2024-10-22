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
      const string& pluginName = fileName.substr( pattern.size(), fileName.size() - pattern.size() - 3 );
      pluginFound[pluginName] = dir + "/" + fileName;
    }
  }

  return pluginFound.size();
}


//~~~~~~~~~~~~~~~~~~~~~~~~~


int PluginManager::FindPlugins( const string& pattern, PluginMap& pluginFound )
{
  const string& dir = string( getenv( "MAMBODIR" ) ) + "/lib";

  return FindPlugins( dir, pattern, pluginFound );
}

///////////////////////////////////


void * PluginManager::LoadPlugin( const string& name )
{
  if( name.empty() ) throw runtime_error( "Please specify plugin name\n" );

  cout << "INFO: Loading plugin " << name << " ... ";
  void * handle = dlopen( name.c_str(), RTLD_LAZY );
  if( !handle ) {
     fprintf( stderr, "dlopen failed: %s\n", dlerror() );
     throw runtime_error( "Cannot load plugin. Invalid handler from dlopen\n" );
  }
  cout << "Ok." << endl;
  
  return handle;
}


///////////////////////////////////


int PluginManager::LoadAllCutFlows()
{ 
  ICutFlowPluginFactory * pluginFactory = NULL;

  int n_cutflows_found = 0;

  const string pwd = string( getenv( "PWD" ) );
  n_cutflows_found += FindPlugins( pwd, "CutFlow", m_cutflows );

  const string mambodir = string( getenv( "MAMBODIR" ) ) + "/lib/";
  n_cutflows_found += FindPlugins( mambodir, "CutFlow", m_cutflows );

  if( n_cutflows_found == 0 ) {
    cout << "WARNING: no cutflow plugin found" << endl;
    return 0;
  }
  else {
    cout << "INFO: Found " << n_cutflows_found << " cutflows" << endl;
  }

  int loaded = 0;
  for( PluginMap::const_iterator pair = m_cutflows.begin() ; pair != m_cutflows.end() ; ++pair ) {
    if( LoadCutFlowPlugin( (*pair).first, (*pair).second ) ) ++loaded;
  }

  return loaded;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~


bool PluginManager::LoadCutFlowPlugin( const string& name, const string& path )
{
  bool success = true;

  void* handle = LoadPlugin( path );

  ICutFlowPluginFactory * pluginFactory     = NULL;

  fp_MakeCutFlowPlugin    MakeCutFlowPlugin = (fp_MakeCutFlowPlugin)dlsym( handle, "MakeCutFlowPlugin" );
  if( !MakeCutFlowPlugin ) throw runtime_error( dlerror() );

  pluginFactory = MakeCutFlowPlugin();

  pluginFactory->Register();

  return success;
}


///////////////////////////////////


int PluginManager::LoadAllNtupleWrappers()
{
  INtupleWrapperPluginFactory * pluginFactory     = NULL;

  int n_plugins_found = 0;

  const string pwd = string( getenv( "PWD" ) );
  n_plugins_found += FindPlugins( pwd, "NtupleWrapper", m_ntuples );

  const string mambodir = string( getenv( "MAMBODIR" ) ) + "/lib/";
  n_plugins_found += FindPlugins( mambodir, "NtupleWrapper", m_ntuples );
  
  if( n_plugins_found == 0 ) {
    cout << "WARNING: No ntuple wrapper plugin found" << endl;
    return 0;
  }
  else cout << "INFO: Found " << n_plugins_found << " ntuple wrappers" << endl;

  int loaded = 0;
  for( PluginMap::const_iterator pair = m_ntuples.begin() ; pair != m_ntuples.end() ; ++pair ) {
    if( LoadNtupleWrapperPlugin( (*pair).first, (*pair).second ) ) ++loaded;
  }

  return loaded;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~


bool PluginManager::LoadNtupleWrapperPlugin( const string& name, const string& path )
{
  bool success = true;

  void* handle = LoadPlugin( path );

  INtupleWrapperPluginFactory * pluginFactory     = NULL;

  fp_MakeNtupleWrapperPlugin    MakeNtupleWrapperPlugin = (fp_MakeNtupleWrapperPlugin)dlsym( handle, "MakeNtupleWrapperPlugin" );
  if( !MakeNtupleWrapperPlugin ) throw runtime_error( dlerror() );

  pluginFactory = MakeNtupleWrapperPlugin();

  pluginFactory->Register();

  return success;
}


///////////////////////////////////////


int PluginManager::LoadAllHistogramFillers()
{
  IHistogramFillerPluginFactory * pluginFactory     = NULL;

  int n_plugins_found = 0;

  const string pwd = string( getenv( "PWD" ) );
  n_plugins_found += FindPlugins( pwd, "HistogramFillers", m_hfillers );

  const string mambodir = string( getenv( "MAMBODIR" ) ) + "/lib/";
  n_plugins_found += FindPlugins( mambodir, "HistogramFiller", m_hfillers );

  if( n_plugins_found == 0 ) {
    cout << "WARNING: No histogram filler plugin found" << endl;
    return 0;
  }
  else cout << "INFO: Found " << n_plugins_found << " histogram fillers" << endl;

  int loaded = 0;
  for( PluginMap::const_iterator pair = m_hfillers.begin() ; pair != m_hfillers.end() ; ++pair ) {
    if( LoadHistogramFillerPlugin( (*pair).first, (*pair).second ) ) ++loaded;
  }

  return loaded;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~


bool PluginManager::LoadHistogramFillerPlugin( const string& name, const string& path )
{
  bool success = true;

  void* handle = LoadPlugin( path );

  IHistogramFillerPluginFactory * pluginFactory     = NULL;

  pf_MakeHistogramFillerPlugin    MakeHistogramFillerPlugin = (pf_MakeHistogramFillerPlugin)dlsym( handle, "MakeHistogramFillerPlugin" );
  if( !MakeHistogramFillerPlugin ) throw runtime_error( dlerror() );
  pluginFactory = MakeHistogramFillerPlugin();

  pluginFactory->Register();

  return success;
}


///////////////////////////////////////


int PluginManager::LoadAllAnalysisCuts()
{
  IAnalysisCutPluginFactory * pluginFactory     = NULL;

  int n_plugins_found = 0;

  const string pwd = string( getenv( "PWD" ) );
  n_plugins_found += FindPlugins( pwd, "AnalysisCuts", m_cuts );

  const string mambodir = string( getenv( "MAMBODIR" ) ) + "/lib/";
  n_plugins_found += FindPlugins( mambodir, "AnalysisCut", m_cuts );

  if( n_plugins_found == 0 ) {
    cout << "WARNING: No analysis cuts plugin found" << endl;
    return 0;
  }
  else cout << "INFO: Found " << n_plugins_found << " analysis cuts libraries" << endl;

  int loaded = 0;
  for( PluginMap::const_iterator pair = m_cuts.begin() ; pair != m_cuts.end() ; ++pair ) {
    if( LoadAnalysisCutPlugin( (*pair).first, (*pair).second ) ) ++loaded;
  }

  return loaded;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~


bool PluginManager::LoadAnalysisCutPlugin( const string& name, const string& path )
{
  bool success = true;

  void* handle = LoadPlugin( path );

  IAnalysisCutPluginFactory * pluginFactory     = NULL;

  pf_MakeAnalysisCutPlugin    MakeAnalysisCutPlugin = (pf_MakeAnalysisCutPlugin)dlsym( handle, "MakeAnalysisCutPlugin" );
  if( !MakeAnalysisCutPlugin ) throw runtime_error( dlerror() );
  pluginFactory = MakeAnalysisCutPlugin();

  pluginFactory->Register();

  return success;
}


///////////////////////////////////////


int PluginManager::LoadAllEventModifiers()
{
  IEventModifiersPluginFactory * pluginFactory     = NULL;

  int n_plugins_found = 0;

  const string pwd = string( getenv( "PWD" ) );
  n_plugins_found += FindPlugins( pwd, "EventModifiers", m_eventmodifiers );

  const string mambodir = string( getenv( "MAMBODIR" ) ) + "/lib/";
  n_plugins_found += FindPlugins( mambodir, "EventModifier", m_eventmodifiers );

  if( n_plugins_found == 0 ) {
    cout << "WARNING: No event modifier plugin found" << endl;
    return 0;
  }
  else cout << "INFO: Found " << n_plugins_found << " event modifier libraries" << endl;

  int loaded = 0;
  for( PluginMap::const_iterator pair = m_eventmodifiers.begin() ; pair != m_eventmodifiers.end() ; ++pair ) {
    if( LoadEventModifierPlugin( (*pair).first, (*pair).second ) ) ++loaded;
  }

  return loaded;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~


bool PluginManager::LoadEventModifierPlugin( const string& name, const string& path )
{
  bool success = true;

  void* handle = LoadPlugin( path );

  IEventModifiersPluginFactory * pluginFactory     = NULL;

  pf_MakeEventModifierPlugin    MakeEventModifierPlugin = (pf_MakeEventModifierPlugin)dlsym( handle, "MakeEventModifierPlugin" );
  if( !MakeEventModifierPlugin ) throw runtime_error( dlerror() );
  pluginFactory = MakeEventModifierPlugin();

  pluginFactory->Register();

  return success;
}

