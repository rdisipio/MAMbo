#ifndef __AnalysisCut_DUMMY__
#define __AnalysisCut_DUMMY__

#include "AnalysisCutsFactory.hpp"

class CutDummy : public IAnalysisCut
{  
 public:
    CutDummy();
    virtual ~CutDummy();

    virtual void Configure( const AnalysisCutParams_t& params );
    virtual bool Apply( EventData * ed );

 protected:

};


/////////////////////////
// Plugin mechanism

typedef AnalysisCutPluginFactory< CutDummy > AnalysisCutPluginFactory_Dummy;

extern "C" {
  AnalysisCutPluginFactory_Dummy * MakeAnalysisCutPlugin();
}

#endif /** __AnalysisCut_DUMMY__ */
