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


bool NtupleWrapperHWWtth::MakeEventMET( EventData * ed )
{
  bool success = true;

  ed->MET.et    = GET_VALUE( MET );
  ed->MET.phi   = GET_VALUE( MET_phi );
  ed->MET.etx   = GET_VALUE( MET_x );
  ed->MET.ety   = GET_VALUE( MET_y );
 // ed->MET.sumet = GET_VALUE( MET_sumet  );

  return success;
}


/////////////////////////////////////////////


bool NtupleWrapperHWWtth::MakeEventElectrons( EventData * ed )
{
  bool success = true;

//  ed->electrons.n = 1;
//  ed->electrons.pT.push_back( GET_VALUE( lep_pt ) );
//  ed->electrons.eta.push_back( GET_VALUE( lep_eta ) );
//  ed->electrons.phi.push_back( GET_VALUE( lep_phi ) );
//  ed->electrons.E.push_back( GET_VALUE( lep_E ) );


  const size_t nl = GET_VALUE( lepton_Pt )->size();
  ed->electrons.n = 0;
  for( size_t i = 0 ; i < nl ; ++i ) {
    if( abs( GET_VALUE_VECTOR( lepton_ID, i ) ) == 11 ) { 
      ed->electrons.n += 1;
 
      ed->electrons.pT.push_back( GET_VALUE_VECTOR( lepton_Pt, i ) );
      ed->electrons.eta.push_back( GET_VALUE_VECTOR( lepton_Eta, i ) );
      ed->electrons.phi.push_back( GET_VALUE_VECTOR( lepton_Phi, i ) );
     }
  }  

  return success;
}


/////////////////////////////////////////////


bool NtupleWrapperHWWtth::MakeEventMuons( EventData * ed )
{
  bool success = true;
  
  const size_t nl = GET_VALUE( lepton_Pt )->size();
  ed->muons.n  = 0;
  for( size_t i = 0 ; i < nl ; ++i ) {
    if( abs( GET_VALUE_VECTOR( lepton_ID, i ) ) == 13 ) { 
      ed->muons.n += 1;

      ed->muons.pT.push_back( GET_VALUE_VECTOR( lepton_Pt, i ) );
      ed->muons.eta.push_back( GET_VALUE_VECTOR( lepton_Eta, i ) );
      ed->muons.phi.push_back( GET_VALUE_VECTOR( lepton_Phi, i ) );
     }
  }  

  return success;
}


/////////////////////////////////////////////


bool NtupleWrapperHWWtth::MakeEventJets( EventData * ed )
{
  bool success = true;

  ed->jets.n = GET_VALUE( m_jet_n );
  for( int i = 0 ; i < ed->jets.n ; ++i ) {
    ed->jets.pT.push_back(  GET_VALUE_VECTOR( m_jet_pt, i )  );
    ed->jets.eta.push_back( GET_VALUE_VECTOR( m_jet_eta, i ) );
    ed->jets.phi.push_back( GET_VALUE_VECTOR( m_jet_phi, i ) );
    ed->jets.E.push_back(   GET_VALUE_VECTOR( m_jet_E, i   ) );
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
