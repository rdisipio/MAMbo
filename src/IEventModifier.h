#ifndef __IEventModifier_H__
#define __IEventModifier_H__

#include "Commons.h"
#include "EventData.h"
#include "HelperFunctions.h"
#include "PhysicsHelperFunctions.h"

struct EventModifierParams_t
{
    map< string, double >        params_numeric;
    map< string, unsigned long > params_flag;
    map< string, string >        params_string;
};


class IEventModifier;
typedef map< string, IEventModifier * > EventModifierCollection_t;


class IEventModifier
{
 public:
   IEventModifier( const string& name = "BaseEventModifier" );
   virtual ~IEventModifier();

   virtual void Configure( const EventModifierParams_t& params );
   virtual bool Apply( EventData * ed ) = 0;

 protected:
   string                  m_name;
   EventModifierParams_t   m_params;
};


#endif /** __IEventModifier_H__ */
