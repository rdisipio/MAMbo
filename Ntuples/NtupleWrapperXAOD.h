#ifndef __XAOD_WRAPPER_H__
#define __XAOD_WRAPPER_H__

#include "NtupleWrapperTransient.h"

//#include "XAOD.h"

//#include "xAODRootAccess/Init.h"
//#include "xAODRootAccess/TEvent.h"
//#include "xAODRootAccess/TStore.h"

// EDM include(s):
#include "xAODEventInfo/EventInfo.h"
#include "xAODMuon/MuonContainer.h"
#include "xAODMuon/MuonAuxContainer.h"
#include "xAODTruth/TruthParticleContainer.h"
#include "xAODTruth/TruthVertexContainer.h"
#include "xAODPrimitives/IsolationType.h"
#include "xAODJet/JetContainer.h"
#include "xAODJet/JetAuxContainer.h"
#include "xAODJet/JetAttributes.h"
#include "xAODJet/JetTypes.h"
#include "xAODBTagging/BTagging.h"
#include "xAODEgamma/ElectronContainer.h"
#include "xAODEgamma/ElectronAuxContainer.h"
#include "xAODMissingET/MissingETContainer.h"
#include "xAODMissingET/MissingETAuxContainer.h"
#include "xAODTracking/TrackParticleContainer.h"
#include "xAODTracking/VertexContainer.h"
#include "xAODTracking/TrackingPrimitives.h"
#include "xAODTau/TauJetContainer.h"
#include "xAODTau/TauJetAuxContainer.h"

#include "xAODCore/ShallowCopy.h"


class NtupleWrapperXAOD : public NtupleWrapperTransient 
{
 public:
  NtupleWrapperXAOD( const AnalysisParams_t analysisParameters );
  virtual ~NtupleWrapperXAOD();


 protected:
  virtual bool MakeEventInfo( EventData * ed );
  virtual bool MakeEventTrigger( EventData * ed );
  virtual bool MakeEventMET( EventData * ed );
  virtual bool MakeEventElectrons( EventData * ed );
  virtual bool MakeEventMuons( EventData * ed );
  virtual bool MakeEventJets( EventData * ed );
  virtual bool MakeEventTruth( EventData * ed );

  const xAOD::MuonContainer*      m_muons;
  const xAOD::ElectronContainer*  m_electrons;
  const xAOD::TauJetContainer*    m_tauJets;
  const xAOD::JetContainer*       m_akt4Jets;
  const xAOD::JetContainer*       m_akt4TruthJets;
  const xAOD::MissingETContainer* m_metFinals;
  const xAOD::MissingETContainer* m_metTruths;

};

typedef NtupleWrapperPluginFactory< NtupleWrapperXAOD > NtupleWrapperPluginFactory_XAOD;

extern "C" {
  NtupleWrapperPluginFactory_XAOD * MakeNtupleWrapperPlugin();
}

#endif /** __MINISLBOOST_WRAPPER_H__ */
