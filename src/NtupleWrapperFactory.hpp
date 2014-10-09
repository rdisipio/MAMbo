#ifndef __NTUPLE_FACTORY_HPP__
#define __NTUPLE_FACTORY_HPP__

#include "Commons.h"

#include "INtupleWrapper.h"

class INtupleWrapper;

template <class T>
INtupleWrapper * CreateNtuple( const char * fileListName, const char * branchListName, const char * treeName ) {
  INtupleWrapper * nw = new T( fileListName, branchListName, treeName );
  return nw;
}


typedef INtupleWrapper * (*fp_CreateNtuple)( const char * fileListName, const char * branchListName, const char * treeName  );
typedef map< string, fp_CreateNtuple > NtupleConfiguratorsCollection_t;

class NtupleWrapperFactory
{
public:
  static NtupleWrapperFactory * GetHandle() { static NtupleWrapperFactory instance; return &instance; };
  virtual ~NtupleWrapperFactory() {};
  
  INtupleWrapper * Create( const string& name, const char * fileListName, const char * branchListName, const char * treeName ) {
    INtupleWrapper * nw = m_configurators[name]( fileListName, branchListName, treeName );
    return nw;
  };


  ////////////////////////////////////////////////


  template< class T >
  bool Register( const string& type ) {
    if( m_configurators.find( type ) !=  m_configurators.end() ) return false; 
    m_configurators[type] = &CreateNtuple<T>;
    return true;
  };

  inline bool Unregister( const string& type ) { return ( m_configurators.erase( type ) == 1 ); };

  
  ////////////////////////////////////////////////

  void Dump() {
    cout << "INFO: Registered ntuples:" << endl;
    for( NtupleConfiguratorsCollection_t::const_iterator itr = m_configurators.begin() ; itr != m_configurators.end() ; ++itr ) {
      cout << "* " << itr->first << endl;
    }
    cout << endl;
  };


private:
  NtupleWrapperFactory() {};

private:
  NtupleConfiguratorsCollection_t m_configurators;
};


//////////////////////////////////////////////
// Plugin
//////////////////////////////////////////////

#ifndef __NTUP_PLUGIN_FACTORY__
#define __NTUP_PLUGIN_FACTORY__

class INtupleWrapperPluginFactory {
 public:
   INtupleWrapperPluginFactory( const string& name ) : m_name( name ) {};
   virtual ~INtupleWrapperPluginFactory() {};

   virtual INtupleWrapper * Create( const char * fileListName, const char * branchListName, const char * treeName)   = 0;
   virtual bool      Register() = 0;

 protected:
   string m_name; 
};

typedef INtupleWrapperPluginFactory * (*fp_MakeNtupleWrapperPlugin)();


template < class T >
class NtupleWrapperPluginFactory : public INtupleWrapperPluginFactory {
 public:
    NtupleWrapperPluginFactory( const string& name ) : INtupleWrapperPluginFactory( name ) {};
    virtual ~NtupleWrapperPluginFactory() {};
 
    virtual INtupleWrapper * Create( const char * fileListName, const char * branchListName, const char * treeName ) { 
      return new T( fileListName, branchListName, treeName); 
    };

    virtual bool      Register() { 
      NtupleWrapperFactory * p_factory = NtupleWrapperFactory::GetHandle();
      return p_factory->Register<T>( m_name ); 
    };
};

#endif /** __NTUP_PLUGIN_FACTORY__ */

#endif /** __NTUPLE_FACTORY_HPP__ */
