#ifndef __HISTOGRAMFILLERSFACTORY_H__
#define __HISTOGRAMFILLERSFACTORY_H__

#include "Commons.h"

#include "IHistogramFiller.h"

struct HistogramFillerParams_t;
class  IHistogramFiller;

/////////////////////////////////


template< typename T >
IHistogramFiller * CreateHistogramFiller( const HistogramFillerParams_t& params ) {
  IHistogramFiller * hf = new T();
  hf->Configure( params );
//  hf->RegisterOutputHistogramsNames();
  return hf;
}

// function pointer to create and configure a histogram filler
typedef IHistogramFiller * (*fp_CreateHistogramFiller)( const HistogramFillerParams_t& params );

typedef map< string, fp_CreateHistogramFiller > HistogramFillersConfiguratorCollection_t;

/////////////////////////////////


class HistogramFillersFactory // NB: it's a singleton
{
 public:

  static HistogramFillersFactory * GetHandle() {
    static HistogramFillersFactory instance;
    return &instance;
  }

  virtual ~HistogramFillersFactory() {};


  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


  IHistogramFiller * Create( const string& name, const HistogramFillerParams_t& params ) {
      if( m_configurators.find( name ) == m_configurators.end() ) {
         throw runtime_error( "HistogramFillerFactory: Create: unknown histogram filler " +  name );
      }

      IHistogramFiller * hf = m_configurators[name]( params );
      return hf;
  };


  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

 
  // fill configurator map: name-config_function association  
  template< class T >
  bool Register( const string& name ) {
    if( m_configurators.find( name ) != m_configurators.end() ) return false;
    m_configurators[name] = &CreateHistogramFiller<T>;
    return true;
  }; 


  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


  bool Unregister( const string& name )
  {
    return ( m_configurators.erase( name ) == 1 );
  };


  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


  void Dump() const {
    cout << "Registered Histogram Fillers: " << m_configurators.size() << endl;

    for( HistogramFillersConfiguratorCollection_t::const_iterator itr = m_configurators.begin() ; itr != m_configurators.end() ; ++itr ) {
      cout << "* " << itr->first << endl;
    }
    cout << endl;
  };


  private:
    HistogramFillersFactory() {}; // singleton
    
  private:
    HistogramFillersConfiguratorCollection_t m_configurators;

	 
}; // end class HistogramFillersFactory


///////////////////////////////////////////////


#ifndef __HFILLER_PLUGIN_FACTORY__
#define __HFILLER_PLUGIN_FACTORY__

// PLUGIN MECHANISM

class IHistogramFillerPluginFactory
{
 public:
  IHistogramFillerPluginFactory( const string& name ) : m_name( name ) {};
  virtual ~IHistogramFillerPluginFactory() {};

  virtual IHistogramFiller * Create() = 0;
  virtual void Register() = 0;

 protected:
  string m_name;
};

typedef IHistogramFillerPluginFactory* (*pf_MakeHistogramFillerPlugin)();


template < class T >
class HistogramFillerPluginFactory : public IHistogramFillerPluginFactory
{
 public:
  HistogramFillerPluginFactory( const string& name ) : IHistogramFillerPluginFactory( name ) {};
  virtual ~HistogramFillerPluginFactory() {};

  virtual IHistogramFiller * Create() { return new T(); };

  virtual void     Register() { 
    HistogramFillersFactory * p_factory = HistogramFillersFactory::GetHandle();
    p_factory->Register<T>( m_name ); 
  };
};

#endif /** __HFILLER_PLUGIN_FACTORY__ */

#endif /** __HISTOGRAMFILLERSFACTORY_H__ */
