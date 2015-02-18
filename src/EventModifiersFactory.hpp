#ifndef __EventModifiersFACTORY_H__
#define __EventModifiersFACTORY_H__

#include "Commons.h"

#include "IEventModifier.h"

struct EventModifierParams_t;
class  IEventModifier;

/////////////////////////////////


template< typename T >
IEventModifier * CreateEM( const EventModifierParams_t& params ) {
  IEventModifier * em = new T();
  em->Configure( params );
//  em->RegisterOutputHistogramsNames();
  return em;
}

// function pointer to create and configure a EM
typedef IEventModifier * (*fp_CreateEventModifier)( const EventModifierParams_t& params );

typedef map< string, fp_CreateEventModifier > EventModifiersConfiguratorCollection_t;

/////////////////////////////////


class EventModifiersFactory // NB: it's a singleton
{
 public:

  static EventModifiersFactory * GetHandle() {
    static EventModifiersFactory instance;
    return &instance;
  }

  virtual ~EventModifiersFactory() {};


  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


  IEventModifier * Create( const string& name, const EventModifierParams_t& params ) {
      if( m_configurators.find( name ) == m_configurators.end() ) {
         throw runtime_error( "EventModifierFactory: Create: unknown EM " +  name );
      }

      IEventModifier * em = m_configurators[name]( params );
      return em;
  };


  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

 
  // fill configurator map: name-config_function association  
  template< class T >
  bool Register( const string& name ) {
    if( m_configurators.find( name ) != m_configurators.end() ) return false;
    m_configurators[name] = &CreateEM<T>;
    return true;
  }; 


  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


  bool Unregister( const string& name )
  {
    return ( m_configurators.erase( name ) == 1 );
  };


  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


  void Dump() const {
    cout << "Registered event modifiers: " << m_configurators.size() << endl;

    for( EventModifiersConfiguratorCollection_t::const_iterator itr = m_configurators.begin() ; itr != m_configurators.end() ; ++itr ) {
      cout << "* " << itr->first << endl;
    }
    cout << endl;
  };


  private:
    EventModifiersFactory() {}; // singleton
    
  private:
    EventModifiersConfiguratorCollection_t m_configurators;

	 
}; // end class EventModifiersFactory


///////////////////////////////////////////////


#ifndef __EventModifiers_PLUGIN_FACTORY__
#define __EventModifiers_PLUGIN_FACTORY__

// PLUGIN MECHANISM

class IEventModifiersPluginFactory
{
 public:
  IEventModifiersPluginFactory( const string& name ) : m_name( name ) {};
  virtual ~IEventModifiersPluginFactory() {};

  virtual IEventModifier * Create() = 0;
  virtual void Register() = 0;

 protected:
  string m_name;
};

typedef IEventModifiersPluginFactory* (*pf_MakeEventModifierPlugin)();


template < class T >
class EventModifiersPluginFactory : public IEventModifiersPluginFactory
{
 public:
  EventModifiersPluginFactory( const string& name ) : IEventModifiersPluginFactory( name ) {};
  virtual ~EventModifiersPluginFactory() {};

  virtual IEventModifier * Create() { return new T(); };

  virtual void     Register() { 
    EventModifiersFactory * p_factory = EventModifiersFactory::GetHandle();
    p_factory->Register<T>( m_name ); 
  };
};

#endif /** __emILLER_PLUGIN_FACTORY__ */

#endif /** __EventModifiersFACTORY_H__ */
