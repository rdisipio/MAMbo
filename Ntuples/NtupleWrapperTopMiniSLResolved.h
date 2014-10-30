#ifndef __TopMiniSLResolved_WRAPPER_H__
#define __TopMiniSLResolved_WRAPPER_H__

#include "NtupleWrapper.h"

#include "TopMiniSLResolved.h"
#include "TopMiniSLResolvedParticles.h"
#include "TopMiniSLResolvedPartons.h"

#include "EventDumperEventInfo.h"
#include "EventDumperLeptons.h"
#include "EventDumperJets.h"
#include "EventDumperMCTruthTopMiniSLResolved.h"

#define DUMP_RESOLVED

class NtupleWrapperTopMiniSLResolved : public NtupleWrapper< TopMiniSLResolved > 
{
 public:
  NtupleWrapperTopMiniSLResolved( const AnalysisParams_t analysisParameters );
  virtual ~NtupleWrapperTopMiniSLResolved();


 protected:
  virtual bool MakeEventInfo( EventData * ed );
  virtual bool MakeEventTrigger( EventData * ed );
  virtual bool MakeEventMET( EventData * ed );
  virtual bool MakeEventLeptons( EventData * ed );
  virtual bool MakeEventJets( EventData * ed );
  virtual bool MakeEventTruth( EventData * ed );

 private:
   EventDumperEventInfo<TopMiniSLResolved>   * m_dumper_info;
   EventDumperLeptons<TopMiniSLResolved>     * m_dumper_leptons;
   EventDumperJets<TopMiniSLResolved>        * m_dumper_jets;
   EventDumperMCTruthTopMiniSLResolved<TopMiniSLResolvedParticles, TopMiniSLResolvedPartons>  * m_dumper_mctruth;

   TFile                      * m_mcfile;
   TopMiniSLResolvedParticles * m_ntuple_particle;
   TopMiniSLResolvedPartons   * m_ntuple_parton;
};

typedef NtupleWrapperPluginFactory< NtupleWrapperTopMiniSLResolved > NtupleWrapperPluginFactory_TopMiniSLResolved;

extern "C" {
  NtupleWrapperPluginFactory_TopMiniSLResolved * MakeNtupleWrapperPlugin();
}

#endif /** __MINISLBOOST_WRAPPER_H__ */
