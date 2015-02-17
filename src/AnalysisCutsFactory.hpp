#ifndef __AnalysisCutsFACTORY_H__
#define __AnalysisCutsFACTORY_H__

#include "Commons.h"

#include "IAnalysisCut.h"

struct AnalysisCutParams_t;
class  IAnalysisCut;

/////////////////////////////////


template< typename T >
IAnalysisCut * CreateCut( const AnalysisCutParams_t& params ) {
  IAnalysisCut * hf = new T();
  hf->Configure( params );
//  hf->RegisterOutputHistogramsNames();
  return hf;
}

// function pointer to create and configure a cut
typedef IAnalysisCut * (*fp_CreateAnalysisCut)( const AnalysisCutParams_t& params );

typedef map< string, fp_CreateAnalysisCut > AnalysisCutsConfiguratorCollection_t;

/////////////////////////////////


class AnalysisCutsFactory // NB: it's a singleton
{
 public:

  static AnalysisCutsFactory * GetHandle() {
    static AnalysisCutsFactory instance;
    return &instance;
  }

  virtual ~AnalysisCutsFactory() {};


  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


  IAnalysisCut * Create( const string& name, const AnalysisCutParams_t& params ) {
      if( m_configurators.find( name ) == m_configurators.end() ) {
         throw runtime_error( "AnalysisCutFactory: Create: unknown cut " +  name );
      }

      IAnalysisCut * hf = m_configurators[name]( params );
      return hf;
  };


  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

 
  // fill configurator map: name-config_function association  
  template< class T >
  bool Register( const string& name ) {
    if( m_configurators.find( name ) != m_configurators.end() ) return false;
    m_configurators[name] = &CreateCut<T>;
    return true;
  }; 


  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


  bool Unregister( const string& name )
  {
    return ( m_configurators.erase( name ) == 1 );
  };


  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


  void Dump() const {
    cout << "Registered Cuts: " << m_configurators.size() << endl;

    for( AnalysisCutsConfiguratorCollection_t::const_iterator itr = m_configurators.begin() ; itr != m_configurators.end() ; ++itr ) {
      cout << "* " << itr->first << endl;
    }
    cout << endl;
  };


  private:
    AnalysisCutsFactory() {}; // singleton
    
  private:
    AnalysisCutsConfiguratorCollection_t m_configurators;

	 
}; // end class AnalysisCutsFactory


///////////////////////////////////////////////


#ifndef __AnalysisCuts_PLUGIN_FACTORY__
#define __AnalysisCuts_PLUGIN_FACTORY__

// PLUGIN MECHANISM

class IAnalysisCutPluginFactory
{
 public:
  IAnalysisCutPluginFactory( const string& name ) : m_name( name ) {};
  virtual ~IAnalysisCutPluginFactory() {};

  virtual IAnalysisCut * Create() = 0;
  virtual void Register() = 0;

 protected:
  string m_name;
};

typedef IAnalysisCutPluginFactory* (*pf_MakeAnalysisCutPlugin)();


template < class T >
class AnalysisCutPluginFactory : public IAnalysisCutPluginFactory
{
 public:
  AnalysisCutPluginFactory( const string& name ) : IAnalysisCutPluginFactory( name ) {};
  virtual ~AnalysisCutPluginFactory() {};

  virtual IAnalysisCut * Create() { return new T(); };

  virtual void     Register() { 
    AnalysisCutsFactory * p_factory = AnalysisCutsFactory::GetHandle();
    p_factory->Register<T>( m_name ); 
  };
};

#endif /** __HFILLER_PLUGIN_FACTORY__ */

#endif /** __AnalysisCutsFACTORY_H__ */
