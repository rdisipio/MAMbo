#ifndef __TopXAOD_WRAPPER_H__
#define __TopXAOD_WRAPPER_H__

#include "NtupleWrapper.h"

#include "TopXAOD.h"
#include "TopXAODParticles.h"
#include "TopXAODPartons.h"

#include "EventDumperMCTruthTopXAOD.h"
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
EventDumperMCTruthTopXAOD<TopXAODParticles, TopXAODPartons>  * m_dumper_mctruth;

   TChain                     * m_particles;
   TChain                     * m_partons;
   TopXAODParticles * m_ntuple_particle;
   TopXAODPartons   * m_ntuple_parton;

};

typedef NtupleWrapperPluginFactory< NtupleWrapperTopXAOD > NtupleWrapperPluginFactory_TopXAOD;

extern "C" {
  NtupleWrapperPluginFactory_TopXAOD * MakeNtupleWrapperPlugin();
}

#endif /** __MINISLBOOST_WRAPPER_H__ */
