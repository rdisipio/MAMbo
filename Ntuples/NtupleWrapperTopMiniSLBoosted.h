#ifndef __TopMiniSLBoosted_WRAPPER_H__
#define __TopMiniSLBoosted_WRAPPER_H__

// see also:
// https://rivet.hepforge.org/trac/browser/src/Analyses/ATLAS_2014_I1304688.cc

#include "NtupleWrapper.h"
#include "TopMiniSLBoosted.h"

#include "EventDumperEventInfo.h"
#include "EventDumperLeptons.h"
#include "EventDumperJets.h"
#include "EventDumperMCTruth.h"

#define DUMP_FATJETS

class NtupleWrapperTopMiniSLBoosted : public NtupleWrapper< TopMiniSLBoosted >
{
 public:
  NtupleWrapperTopMiniSLBoosted( const AnalysisParams_t analysisParameters );
  virtual ~NtupleWrapperTopMiniSLBoosted();


 protected:
  virtual bool MakeEventInfo( EventData * ed );
  virtual bool MakeEventTrigger( EventData * ed );
  virtual bool MakeEventMET( EventData * ed );
  virtual bool MakeEventLeptons(  EventData * ed );
  virtual bool MakeEventJets( EventData * ed );
  virtual bool MakeEventTruth( EventData * ed );

 private:
   EventDumperEventInfo<TopMiniSLBoosted>   * m_dumper_info;
   EventDumperLeptons<TopMiniSLBoosted>     * m_dumper_leptons;
   EventDumperJets<TopMiniSLBoosted>        * m_dumper_jets;
   EventDumperMCTruth<TopMiniSLBoosted>     * m_dumper_mctruth;
};

typedef NtupleWrapperPluginFactory< NtupleWrapperTopMiniSLBoosted > NtupleWrapperPluginFactory_TopMiniSLBoosted;

extern "C" {
  NtupleWrapperPluginFactory_TopMiniSLBoosted * MakeNtupleWrapperPlugin();
}

#endif /** __TopMiniSLBoosted_WRAPPER_H__ */
