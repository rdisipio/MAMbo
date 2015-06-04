#ifndef __TopXAOD_WRAPPER_H__
#define __TopXAOD_WRAPPER_H__

#include "NtupleWrapper.h"

#include "TopXAOD.h"

#include "EventDumperEventInfo.h"
#include "EventDumperLeptons.h"
#include "EventDumperJets.h"

class NtupleWrapperTopXAOD : public NtupleWrapper< TopXAOD > 
{
 public:
  NtupleWrapperTopXAOD( const AnalysisParams_t analysisParameters );
  virtual ~NtupleWrapperTopXAOD();


 protected:
  virtual bool MakeEventInfo( EventData * ed );
  virtual bool MakeEventTrigger( EventData * ed );
  virtual bool MakeEventMET( EventData * ed );
  virtual bool MakeEventElectrons( EventData * ed );
  virtual bool MakeEventMuons( EventData * ed );
  virtual bool MakeEventJets( EventData * ed );
  virtual bool MakeEventTruth( EventData * ed );

private:
   EventDumperEventInfo<TopXAOD>   * m_dumper_info;
   EventDumperLeptons<TopXAOD>     * m_dumper_leptons;
   EventDumperJets<TopXAOD>        * m_dumper_jets;

};

typedef NtupleWrapperPluginFactory< NtupleWrapperTopXAOD > NtupleWrapperPluginFactory_TopXAOD;

extern "C" {
  NtupleWrapperPluginFactory_TopXAOD * MakeNtupleWrapperPlugin();
}

#endif /** __MINISLBOOST_WRAPPER_H__ */
