#ifndef __TopMiniSLResolvedParticles_WRAPPER_H__
#define __TopMiniSLResolvedParticles_WRAPPER_H__

#include "NtupleWrapper.h"

#include "TopMiniSLResolvedParticles.h"
#include "TopMiniSLResolvedPartons.h"

#include "EventDumperEventInfo.h"
#include "EventDumperLeptons.h"
#include "EventDumperJets.h"
#include "EventDumperMCTruthTopMiniSLResolved.h"

#define DUMP_RESOLVED

class NtupleWrapperTopMiniSLResolvedParticles : public NtupleWrapper< TopMiniSLResolvedParticles > 
{
 public:
  NtupleWrapperTopMiniSLResolvedParticles( const AnalysisParams_t analysisParameters );
  virtual ~NtupleWrapperTopMiniSLResolvedParticles();


 protected:
  virtual bool MakeEventInfo( EventData * ed );
  virtual bool MakeEventTrigger( EventData * ed );
  virtual bool MakeEventMET( EventData * ed );
  virtual bool MakeEventLeptons( EventData * ed );
  virtual bool MakeEventJets( EventData * ed );
  virtual bool MakeEventTruth( EventData * ed );

 private:
//   EventDumperEventInfo<TopMiniSLResolved>   * m_dumper_info;
   EventDumperMCTruthTopMiniSLResolved<TopMiniSLResolvedParticles, TopMiniSLResolvedPartons>  * m_dumper_mctruth;

   TChain                     * m_partons;
   TopMiniSLResolvedPartons   * m_ntuple_parton;
};

typedef NtupleWrapperPluginFactory< NtupleWrapperTopMiniSLResolvedParticles > NtupleWrapperPluginFactory_TopMiniSLResolvedParticles;

extern "C" {
  NtupleWrapperPluginFactory_TopMiniSLResolvedParticles * MakeNtupleWrapperPlugin();
}

#endif /** __MINISLBOOST_WRAPPER_H__ */
