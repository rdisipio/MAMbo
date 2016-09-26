#ifndef __AllHadBoosted_WRAPPER_H__
#define __AllHadBoosted_WRAPPER_H__

#include "NtupleWrapper.h"

#include "AllHadBoosted.h"

class NtupleWrapperAllHadBoosted : public NtupleWrapper< AllHadBoosted > 
{
 public:
  NtupleWrapperAllHadBoosted( const AnalysisParams_t analysisParameters );
  virtual ~NtupleWrapperAllHadBoosted();


 protected:
  virtual bool MakeEventInfo( EventData * ed );
  virtual bool MakeEventTrigger( EventData * ed );
  virtual bool MakeEventMET( EventData * ed );
  virtual bool MakeEventLeptons( EventData * ed );
  virtual bool MakeEventJets( EventData * ed );
  virtual bool MakeEventTruth( EventData * ed );
};

typedef NtupleWrapperPluginFactory< NtupleWrapperAllHadBoosted > NtupleWrapperPluginFactory_AllHadBoosted;

extern "C" {
  NtupleWrapperPluginFactory_AllHadBoosted * MakeNtupleWrapperPlugin();
}

#endif /** __MINISLBOOST_WRAPPER_H__ */
