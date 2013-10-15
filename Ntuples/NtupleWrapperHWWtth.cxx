#include "NtupleWrapperHWWtth.h"

NtupleWrapperHWWtth::NtupleWrapperHWWtth( const char * fileListName, const char * branchListName, const char * treeName ) : 
  NtupleWrapper< HWWtth >( fileListName, branchListName, treeName )
{
}

/////////////////////////////////////////////


NtupleWrapperHWWtth::~NtupleWrapperHWWtth()
{

}

/////////////////////////////////////////////


bool NtupleWrapperHWWtth::MakeEventInfo( EventData * ed )
{
  bool success = true;

  ed->info.eventNumber     = GET_VALUE( EventNumber );
  ed->info.runNumber       = GET_VALUE( RunNumber );

  ed->info.mcChannelNumber = GET_VALUE( mc_channel_number );
  ed->info.mcWeight        = GET_VALUE( mcEventWeight );

  return success;
}


/////////////////////////////////////////////


bool NtupleWrapperHWWtth::MakeEventTrigger( EventData * ed )
{ 
  bool success = true;

  CHECK_TRIGGER( EF_e24vhi_medium1 );
  CHECK_TRIGGER( EF_e60_medium1 );
  CHECK_TRIGGER( EF_mu24i_tight );
  CHECK_TRIGGER( EF_mu36_tight );

  return success;
}


/////////////////////////////////////////////


bool NtupleWrapperHWWtth::MakeEventMET( EventData * ed )
{
  bool success = true;

  ed->MET.et    = GET_VALUE( MET );
  ed->MET.phi   = GET_VALUE( MET_phi );
//  ed->MET.etx   = 0.;
//  ed->MET.ety   = 0.;
//  ed->MET.sumet = GET_VALUE( met_sumet  );

  return success;
}


/////////////////////////////////////////////


bool NtupleWrapperHWWtth::MakeEventElectrons( EventData * ed )
{
  bool success = true;

  ed->electrons.n = GET_VALUE( electron_pt )->size();

  for( int i = 0 ; i < ed->electrons.n ; ++i ) {
    ed->electrons.pT.push_back( GET_VALUE_VECTOR( electron_pt, i ) );
    ed->electrons.eta.push_back( GET_VALUE_VECTOR( electron_eta, i ) );
    ed->electrons.phi.push_back( GET_VALUE_VECTOR( electron_phi, i ) );
    ed->electrons.E.push_back( GET_VALUE_VECTOR( electron_E, i ) );
  }
 

  return success;
}


/////////////////////////////////////////////


bool NtupleWrapperHWWtth::MakeEventMuons( EventData * ed )
{
  bool success = true;

  ed->muons.n = GET_VALUE( muon_pt )->size();

  for( int i = 0 ; i < ed->muons.n ; ++i ) {
    ed->muons.pT.push_back( GET_VALUE_VECTOR( muon_pt, i ) );
    ed->muons.eta.push_back( GET_VALUE_VECTOR( muon_eta, i ) );
    ed->muons.phi.push_back( GET_VALUE_VECTOR( muon_phi, i ) );
    ed->muons.E.push_back( GET_VALUE_VECTOR( muon_E, i ) );
  }

  return success;
}


/////////////////////////////////////////////


bool NtupleWrapperHWWtth::MakeEventJets( EventData * ed )
{
  bool success = true;

  ed->jets.n = GET_VALUE( m_jet_n );

  for( int i = 0 ; i < ed->jets.n ; ++i ) {
    ed->jets.pT.push_back( GET_VALUE_VECTOR( m_jet_pt, i ) );
    ed->jets.eta.push_back( GET_VALUE_VECTOR( m_jet_eta, i ) );
    ed->jets.phi.push_back( GET_VALUE_VECTOR( m_jet_phi, i ) );
    ed->jets.E.push_back( GET_VALUE_VECTOR( m_jet_E, i ) );
  }

  return success;
}


/////////////////////////////////////////////


bool NtupleWrapperHWWtth::MakeEventTruth( EventData * ed )
{
  bool success = true;

  return success;
}


/////////////////////////////////////////
// Plugin

extern "C" {
  NtupleWrapperPluginFactory_HWWtth * MakeNtupleWrapperPlugin() {
    return new NtupleWrapperPluginFactory_HWWtth( "HWWtth" );
  };
}
