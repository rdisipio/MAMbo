#ifndef __CUTFLOW_FACTORY_H__
#define __CUTFLOW_FACTORY_H__

#include "CutFlow.h"

class CutFlow;

template< class T >
CutFlow * CreateCutFlow() {
  CutFlow * cf = new T();
  //config?
  return cf;
};
typedef CutFlow* (*fp_CreateCutFlow)();
typedef map< string, fp_CreateCutFlow > CutFlowConfiguratorsCollection;

class CutFlowFactory
{
  public: 
     static CutFlowFactory * GetHandle() { static CutFlowFactory instance; return &instance; };
     virtual ~CutFlowFactory() {};

     CutFlow * Create( const string& type ) {
        CutFlow * cf = m_configurators[type]();
        if( !cf ) throw runtime_error( "Invalid pointer to cut flow object.\n" );
        return cf;
     };


    ////////////////////////////////////////////////


    template< class T >
    bool Register(   const string& type ) {
       if( m_configurators.find( type ) !=  m_configurators.end() ) return false; 
       m_configurators[type] = &CreateCutFlow<T>;
       return true;
    };


    inline bool Unregister( const string& type ) { return ( m_configurators.erase( type ) == 1 ); };

 
    ////////////////////////////////////////////////


    void Dump() {
       cout << "Registered cut flows:" << endl;
       for( CutFlowConfiguratorsCollection::const_iterator itr = m_configurators.begin() ; itr != m_configurators.end() ; ++itr ) {
          cout << "* " << itr->first << endl;
       }
       cout << endl;
    };

private:
  CutFlowFactory() {};
    
private:
  CutFlowConfiguratorsCollection m_configurators;
};


//////////////////////////////////////////////
// Factory
//////////////////////////////////////////////


class ICutFlowPluginFactory {
 public:
   ICutFlowPluginFactory( const string& name ) : m_name( name ) {};
   virtual ~ICutFlowPluginFactory() {};

   virtual CutFlow * Create()   = 0;
   virtual bool      Register() = 0;

 protected:
   string m_name; 
};

typedef ICutFlowPluginFactory * (*fp_MakeCutFlowPlugin)();


template < class T >
class CutFlowPluginFactory : public ICutFlowPluginFactory {
 public:
    CutFlowPluginFactory( const	string&	name ) : ICutFlowPluginFactory( name ) {};
    virtual ~CutFlowPluginFactory() {};
 
    virtual CutFlow * Create() { return new T(); };

    virtual bool      Register() { 
      CutFlowFactory * p_factory = CutFlowFactory::GetHandle();
      return p_factory->Register<T>( m_name ); 
    };
};


#endif /** __CUTFLOW_FACTORY_H__ */
