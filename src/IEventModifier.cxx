#include "IEventModifier.h"

IEventModifier::IEventModifier( const string& name ) : m_name( name )
{

}


IEventModifier::~IEventModifier()
{
}


//////////////////////////////////////////


void IEventModifier::Configure( const EventModifierParams_t& params )
{
   m_params = params;
}
