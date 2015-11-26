#ifndef __TopXAODParticles_WRAPPER_H__
#define __TopXAODParticles_WRAPPER_H__

#include "NtupleWrapper.h"

#include "TopXAODParticles.h"
#include "TopXAODPartons.h"

#include "EventDumperEventInfo.h"
#include "EventDumperLeptons.h"
#include "EventDumperJets.h"
#include "EventDumperMCTruthTopXAOD.h"

#define DUMP_RESOLVED

class NtupleWrapperTopXAODParticles : public NtupleWrapper< TopXAODParticles > 
{
 public:
  NtupleWrapperTopXAODParticles( const AnalysisParams_t analysisParameters );
  virtual ~NtupleWrapperTopXAODParticles();


 protected:
  virtual bool MakeEventInfo( EventData * ed );
  virtual bool MakeEventTrigger( EventData * ed );
  virtual bool MakeEventMET( EventData * ed );
  virtual bool MakeEventLeptons( EventData * ed );
  virtual bool MakeEventJets( EventData * ed );
  virtual bool MakeEventTruth( EventData * ed );

 private:
//   EventDumperEventInfo<TopXAOD>   * m_dumper_info;
   EventDumperMCTruthTopXAOD<TopXAODParticles, TopXAODPartons>  * m_dumper_mctruth;

   TChain                     * m_partons;
   TopXAODPartons   * m_ntuple_parton;
};

typedef NtupleWrapperPluginFactory< NtupleWrapperTopXAODParticles > NtupleWrapperPluginFactory_TopXAODParticles;

extern "C" {
  NtupleWrapperPluginFactory_TopXAODParticles * MakeNtupleWrapperPlugin();
}

#endif /** __MINISLBOOST_WRAPPER_H__ */