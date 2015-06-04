#ifndef __TopXAOD_WRAPPER_H__
#define __TopXAOD_WRAPPER_H__

#include "NtupleWrapper.h"

#include "TopXAOD.h"

class NtupleWrapperTopXAOD : public NtupleWrapper< TopXAOD > 
{
 public:
  NtupleWrapperTopXAOD( const AnalysisParams_t analysisParameters );
  virtual ~NtupleWrapperTopXAOD();


 protected:
  virtual bool MakeEventInfo( EventData * ed );
  virtual bool MakeEventTrigger( EventData * ed );
  virtual bool MakeEventMET( EventData * ed );
  virtual bool MakeEventLeptons( EventData * ed );
  virtual bool MakeEventJets( EventData * ed );
  virtual bool MakeEventTruth( EventData * ed );

};

typedef NtupleWrapperPluginFactory< NtupleWrapperTopXAOD > NtupleWrapperPluginFactory_TopXAOD;

extern "C" {
  NtupleWrapperPluginFactory_TopXAOD * MakeNtupleWrapperPlugin();
}

#endif /** __MINISLBOOST_WRAPPER_H__ */
