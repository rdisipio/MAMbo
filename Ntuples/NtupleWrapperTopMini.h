#ifndef __TopMini_WRAPPER_H__
#define __TopMini_WRAPPER_H__

// see also:
// https://rivet.hepforge.org/trac/browser/src/Analyses/ATLAS_2014_I1304688.cc

#include "NtupleWrapper.h"

#include "TopMini.h"

class NtupleWrapperTopMini : public NtupleWrapper< TopMini > 
{
 public:
  NtupleWrapperTopMini( const AnalysisParams_t analysisParameters );
  virtual ~NtupleWrapperTopMini();


 protected:
  virtual bool MakeEventInfo( EventData * ed );
  virtual bool MakeEventTrigger( EventData * ed );
  virtual bool MakeEventMET( EventData * ed );
  virtual bool MakeEventElectrons( EventData * ed );
  virtual bool MakeEventMuons( EventData * ed );
  virtual bool MakeEventJets( EventData * ed );
  virtual bool MakeEventTruth( EventData * ed );

 private:
};

typedef NtupleWrapperPluginFactory< NtupleWrapperTopMini > NtupleWrapperPluginFactory_TopMini;

extern "C" {
  NtupleWrapperPluginFactory_TopMini * MakeNtupleWrapperPlugin();
}

#endif /** __MINISLBOOST_WRAPPER_H__ */
