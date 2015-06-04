#include "NtupleWrapperTopXAOD.h"

NtupleWrapperTopXAOD::NtupleWrapperTopXAOD( const AnalysisParams_t analysisParameters ):
  NtupleWrapper< TopXAOD >( analysisParameters )
{
   m_dumper_leptons = new EventDumperLeptons<TopXAOD>();
   m_dumper_leptons->SetNtuple( m_ntuple );
   m_dumper_leptons->SetAnalysisParameters( analysisParameters );

   m_dumper_jets = new EventDumperJets<TopXAOD>();
   m_dumper_jets->SetNtuple( m_ntuple );
   m_dumper_jets->SetAnalysisParameters( analysisParameters );
}

/////////////////////////////////////////////


NtupleWrapperTopXAOD::~NtupleWrapperTopXAOD()
{

}

/////////////////////////////////////////////


bool NtupleWrapperTopXAOD::MakeEventInfo( EventData * ed )
{
  bool success = true;

  ed->info.eventNumber     = GET_VALUE( eventNumber );
  ed->info.runNumber       = GET_VALUE( runNumber );
  ed->info.mcChannelNumber = GET_VALUE( channelNumber );
  ed->info.mcWeight        = GET_VALUE( eventWeight );

  SET_PROPERTY( dataPeriod );
  SET_PROPERTY( mu );


  return success;
}


/////////////////////////////////////////////


bool NtupleWrapperTopXAOD::MakeEventTrigger( EventData * ed )
{ 
  bool success = true;

// CHECK_TRIGGER( "EF_mu18i" );

  return success;
}


/////////////////////////////////////////////


bool NtupleWrapperTopXAOD::MakeEventMET( EventData * ed )
{
  bool success = true;

  ed->MET.et    = GET_VALUE( met_et );
  ed->MET.phi   = GET_VALUE( met_phi );
  //  ed->MET.etx   = 0.;
  //  ed->MET.ety   = 0.;
  ed->MET.sumet = GET_VALUE( met_sumet  );
  ed->MET.mwt   = GET_VALUE( mwt );

  return success;
}


/////////////////////////////////////////////


bool NtupleWrapperTopXAOD::MakeEventElectrons( EventData * ed )
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


bool NtupleWrapperTopXAOD::MakeEventMuons( EventData * ed )
{
  bool success = true;

  return success;
}


/////////////////////////////////////////////


bool NtupleWrapperTopXAOD::MakeEventJets( EventData * ed )
{
  return m_dumper_jets->DumpEventJets( ed );
}


/////////////////////////////////////////////


bool NtupleWrapperTopXAOD::MakeEventTruth( EventData * ed )
{
  bool success = true;

  return success;
}


/////////////////////////////////////////
// Plugin

extern "C" {
  NtupleWrapperPluginFactory_TopXAOD * MakeNtupleWrapperPlugin() {
    return new NtupleWrapperPluginFactory_TopXAOD( "TopXAOD" );
  };
}
