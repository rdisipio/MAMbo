#include "NtupleWrapperXAOD.h"

NtupleWrapperXAOD::NtupleWrapperXAOD( const AnalysisParams_t analysisParameters ):
  NtupleWrapperTransient( analysisParameters )
{
}

/////////////////////////////////////////////


NtupleWrapperXAOD::~NtupleWrapperXAOD()
{

}

/////////////////////////////////////////////


bool NtupleWrapperXAOD::MakeEventInfo( EventData * ed )
{
  bool success = true;

//  ed->info.eventNumber     = GET_VALUE( eventNumber );
//  ed->info.runNumber       = GET_VALUE( runNumber );

//  ed->info.mcChannelNumber = GET_VALUE( channelNumber );
//  ed->info.mcWeight        = GET_VALUE( eventWeight );

  const xAOD::EventInfo* ei = 0;
  m_xAODevent->retrieve( ei, "EventInfo" );

  ed->info.eventNumber  = ei->eventNumber();
  ed->info.runNumber    = ei->runNumber();

  return success;
}


/////////////////////////////////////////////


bool NtupleWrapperXAOD::MakeEventTrigger( EventData * ed )
{ 
  bool success = true;

// CHECK_TRIGGER( "EF_mu18i" );

  return success;
}


/////////////////////////////////////////////


bool NtupleWrapperXAOD::MakeEventMET( EventData * ed )
{
  bool success = true;

//  ed->MET.et    = GET_VALUE( met_et );
//  ed->MET.phi   = GET_VALUE( met_phi );
//  ed->MET.etx   = 0.;
//  ed->MET.ety   = 0.;
//  ed->MET.sumet = GET_VALUE( met_sumet  );

  return success;
}


/////////////////////////////////////////////


bool NtupleWrapperXAOD::MakeEventElectrons( EventData * ed )
{
  bool success = true;

//  ed->electrons.n = 1;
//  ed->electrons.pT.push_back( GET_VALUE( lep_pt ) );
//  ed->electrons.eta.push_back( GET_VALUE( lep_eta ) );
//  ed->electrons.phi.push_back( GET_VALUE( lep_phi ) );
//  ed->electrons.E.push_back( GET_VALUE( lep_E ) );

  /*
  ed->electrons.n = GET_VALUE( el_n );
  for( int i = 0 ; i < ed->electrons.n ; ++i ) {
    ed->electrons.pT.push_back( GET_VALUE_ARRAY( el_pt, i ) );
  }
  */

  return success;
}


/////////////////////////////////////////////


bool NtupleWrapperXAOD::MakeEventMuons( EventData * ed )
{
  bool success = true;

  return success;
}


/////////////////////////////////////////////


bool NtupleWrapperXAOD::MakeEventJets( EventData * ed )
{
  bool success = true;

  const xAOD::JetContainer * akt4Jets;
  m_xAODevent->retrieve( akt4Jets, "AntiKt4LCTopoJets" );

  xAOD::JetContainer::const_iterator jetItr  = akt4Jets->begin();
  xAOD::JetContainer::const_iterator jetItrE = akt4Jets->end(); 
  for( ; jetItr != jetItrE ; ++jetItr ) {
      const double pT = (*jetItr)->pt();
      const double eta = (*jetItr)->eta();

      if( pT < 25*GeV ) continue;
      if( fabs(eta) > 2.5 ) continue;

      ed->jets.pT.push_back(  pT );
      ed->jets.eta.push_back( eta );
      ed->jets.phi.push_back( (*jetItr)->phi() );
      ed->jets.E.push_back(   (*jetItr)->e() ); 
      ed->jets.n++;
  }

  return success;
}


/////////////////////////////////////////////


bool NtupleWrapperXAOD::MakeEventTruth( EventData * ed )
{
  bool success = true;

  return success;
}


/////////////////////////////////////////
// Plugin

extern "C" {
  NtupleWrapperPluginFactory_XAOD * MakeNtupleWrapperPlugin() {
    return new NtupleWrapperPluginFactory_XAOD( "XAOD" );
  };
}
