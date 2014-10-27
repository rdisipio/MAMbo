#ifndef __TopMiniSLResolved_WRAPPER_H__
#define __TopMiniSLResolved_WRAPPER_H__

#include "NtupleWrapper.h"

#include "TopMiniSLResolved.h"

class NtupleWrapperTopMiniSLResolved : public NtupleWrapper< TopMiniSLResolved > 
{
 public:
  NtupleWrapperTopMiniSLResolved( const AnalysisParams_t analysisParameters );
  virtual ~NtupleWrapperTopMiniSLResolved();


 protected:
  virtual bool MakeEventInfo( EventData * ed );
  virtual bool MakeEventTrigger( EventData * ed );
  virtual bool MakeEventMET( EventData * ed );
  virtual bool MakeEventElectrons( EventData * ed );
  virtual bool MakeEventMuons( EventData * ed );
  virtual bool MakeEventJets( EventData * ed );
  virtual bool MakeEventTruth( EventData * ed );
};

typedef NtupleWrapperPluginFactory< NtupleWrapperTopMiniSLResolved > NtupleWrapperPluginFactory_TopMiniSLResolved;

extern "C" {
  NtupleWrapperPluginFactory_TopMiniSLResolved * MakeNtupleWrapperPlugin();
}

#endif /** __MINISLBOOST_WRAPPER_H__ */
