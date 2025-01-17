#ifndef __@NAME@_WRAPPER_H__
#define __@NAME@_WRAPPER_H__

#include "NtupleWrapper.h"

#include "@NAME@.h"

class NtupleWrapper@NAME@ : public NtupleWrapper< @NAME@ > 
{
 public:
  NtupleWrapper@NAME@( const AnalysisParams_t analysisParameters );
  virtual ~NtupleWrapper@NAME@();


 protected:
  virtual bool MakeEventInfo( EventData * ed );
  virtual bool MakeEventTrigger( EventData * ed );
  virtual bool MakeEventMET( EventData * ed );
  virtual bool MakeEventElectrons( EventData * ed );
  virtual bool MakeEventMuons( EventData * ed );
  virtual bool MakeEventJets( EventData * ed );
  virtual bool MakeEventTruth( EventData * ed );
};

typedef NtupleWrapperPluginFactory< NtupleWrapper@NAME@ > NtupleWrapperPluginFactory_@NAME@;

extern "C" {
  NtupleWrapperPluginFactory_@NAME@ * MakeNtupleWrapperPlugin();
}

#endif /** __MINISLBOOST_WRAPPER_H__ */
