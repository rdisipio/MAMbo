#ifndef __IAnalysisCut_H__
#define __IAnalysisCut_H__

#include "Commons.h"
#include "EventData.h"
#include "HelperFunctions.h"
#include "PhysicsHelperFunctions.h"

struct AnalysisCutParams_t
{
    map< string, double >        params_numeric;
    map< string, unsigned long > params_flag;
    map< string, string >        params_string;
};


class IAnalysisCut;
typedef map< string, IAnalysisCut * > AnalysisCutCollection_t;


class IAnalysisCut
{
 public:
   IAnalysisCut( const string& name = "BaseCut" );
   virtual ~IAnalysisCut();

   virtual void Configure( const AnalysisCutParams_t& params );
   virtual bool Apply( EventData * ed ) = 0;

 protected:
   string                m_cutName;
   AnalysisCutParams_t   m_params;
};


#endif /** __IAnalysisCut_H__ */
