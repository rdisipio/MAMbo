#ifndef __TopMini_WRAPPER_H__
#define __TopMini_WRAPPER_H__

// see also:
// https://rivet.hepforge.org/trac/browser/src/Analyses/ATLAS_2014_I1304688.cc

#include "NtupleWrapper.h"
#include "TopMini.h"

#include "EventDumperEventInfo.h"
#include "EventDumperLeptons.h"
#include "EventDumperJets.h"
#include "EventDumperMCTruth.h"

//template<class NTUPLE> class EventDumperEventInfo<TopMini>;

class NtupleWrapperTopMini : public NtupleWrapper< TopMini >
{
 public:
  NtupleWrapperTopMini( const AnalysisParams_t analysisParameters );
  virtual ~NtupleWrapperTopMini();


 protected:
  virtual bool MakeEventInfo( EventData * ed );
  virtual bool MakeEventTrigger( EventData * ed );
  virtual bool MakeEventMET( EventData * ed );
  virtual bool MakeEventLeptons(  EventData * ed );
  virtual bool MakeEventJets( EventData * ed );
  virtual bool MakeEventTruth( EventData * ed );

 private:
//   EventDumperBoostedMiniSL * m_dumper; 
   EventDumperEventInfo        * m_dumper_info;
   EventDumperLeptons          * m_dumper_leptons;
   EventDumperJets             * m_dumper_jets;
   EventDumperMCTruth<TopMini> * m_dumper_mctruth;
};

typedef NtupleWrapperPluginFactory< NtupleWrapperTopMini > NtupleWrapperPluginFactory_TopMini;

extern "C" {
  NtupleWrapperPluginFactory_TopMini * MakeNtupleWrapperPlugin();
}

#endif /** __MINISLBOOST_WRAPPER_H__ */
