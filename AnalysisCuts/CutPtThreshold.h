#ifndef __AnalysisCut_PtThreshold__
#define __AnalysisCut_PtThreshold__

#include "AnalysisCutsFactory.hpp"

class CutPtThreshold : public IAnalysisCut
{  
 public:
    CutPtThreshold();
    virtual ~CutPtThreshold();

    virtual void Configure( const AnalysisCutParams_t& params );
    virtual bool Apply( EventData * ed );

 protected:

};


/////////////////////////
// Plugin mechanism

typedef AnalysisCutPluginFactory< CutPtThreshold > AnalysisCutPluginFactory_PtThreshold;

extern "C" {
  AnalysisCutPluginFactory_PtThreshold * MakeAnalysisCutPlugin();
}

#endif /** __AnalysisCut_PtThreshold__ */
