#ifndef __LHEF_WRAPPER_H__
#define __LHEF_WRAPPER_H__

#include "NtupleWrapper.h"

#include "LHEF.h"

class NtupleWrapperLHEF : public NtupleWrapper< LHEF > 
{
 public:
  NtupleWrapperLHEF( const AnalysisParams_t analysisParameters );
  virtual ~NtupleWrapperLHEF();


 protected:
  virtual bool MakeEventInfo( EventData * ed );
  virtual bool MakeEventTrigger( EventData * ed );
  virtual bool MakeEventMET( EventData * ed );
  virtual bool MakeEventElectrons( EventData * ed );
  virtual bool MakeEventMuons( EventData * ed );
  virtual bool MakeEventJets( EventData * ed );
  virtual bool MakeEventTruth( EventData * ed );
};

typedef NtupleWrapperPluginFactory< NtupleWrapperLHEF > NtupleWrapperPluginFactory_LHEF;

extern "C" {
  NtupleWrapperPluginFactory_LHEF * MakeNtupleWrapperPlugin();
}

#endif /** __MINISLBOOST_WRAPPER_H__ */
