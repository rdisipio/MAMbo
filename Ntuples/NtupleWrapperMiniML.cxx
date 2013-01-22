#include "NtupleWrapperMiniML.h"

NtupleWrapperMiniML::NtupleWrapperMiniML( const char * fileListName, const char * branchListName, const char * treeName ) : 
  NtupleWrapper< MiniML >( fileListName, branchListName, treeName )
{
}

/////////////////////////////////////////////


NtupleWrapperMiniML::~NtupleWrapperMiniML()
{

}

/////////////////////////////////////////////


bool NtupleWrapperMiniML::MakeEventInfo( EventData * ed )
{
  bool success = true;

  ed->info.eventNumber     = GET_VALUE( eventNumber );
  ed->info.runNumber       = GET_VALUE( runNumber );

  ed->info.mcChannelNumber = GET_VALUE( channelNumber );
  ed->info.mcWeight        = GET_VALUE( mcWeight );
  ed->info.eventWeight     = GET_VALUE( eventWeight_PRETAG );

  return success;
}


/////////////////////////////////////////////


bool NtupleWrapperMiniML::MakeEventMET( EventData * ed )
{
  bool success = true;

  ed->MET.et    = GET_VALUE( met_et );
  ed->MET.phi   = GET_VALUE( met_phi );
  ed->MET.etx   = 0.;
  ed->MET.ety   = 0.;
  ed->MET.sumet = GET_VALUE( met_sumet  );

  return success;
}


/////////////////////////////////////////////


bool NtupleWrapperMiniML::MakeEventElectrons( EventData * ed )
{
  bool success = true;

  int lep_n = GET_VALUE( lep_n );
  for( int i = 0 ; i < lep_n ; ++i ) {
    UInt_t type = GET_VALUE_ARRAY( lep_type, i );

    if( type != 11 ) continue;

    ed->electrons.pT.push_back( GET_VALUE_ARRAY( lep_pt, i ) );
    ed->electrons.eta.push_back( GET_VALUE_ARRAY( lep_eta, i ) );
    ed->electrons.phi.push_back( GET_VALUE_ARRAY( lep_phi, i ) );
    ed->electrons.E.push_back( GET_VALUE_ARRAY( lep_E, i ) );
  }
  ed->electrons.n = ed->electrons.pT.size();

  return success;
}


/////////////////////////////////////////////


bool NtupleWrapperMiniML::MakeEventMuons( EventData * ed )
{
  bool success = true;

  int lep_n = GET_VALUE( lep_n );
  for( int i = 0 ; i < lep_n ; ++i ) {
    UInt_t type = GET_VALUE_ARRAY( lep_type, i );

    if( type != 13 ) continue;

    ed->muons.pT.push_back( GET_VALUE_ARRAY( lep_pt, i ) );
    ed->muons.eta.push_back( GET_VALUE_ARRAY( lep_eta, i ) );
    ed->muons.phi.push_back( GET_VALUE_ARRAY( lep_phi, i ) );
    ed->muons.E.push_back( GET_VALUE_ARRAY( lep_E, i ) );
  }
  ed->muons.n = ed->muons.pT.size();
  
  return success;
}


/////////////////////////////////////////////


bool NtupleWrapperMiniML::MakeEventJets( EventData * ed )
{
  bool success = true;
 
  ed->jets.n = GET_VALUE( jet_n );
  for( int i = 0 ; i < ed->jets.n ; ++i ) {
    ed->jets.pT.push_back(  m_ntuple->jet_pt[i]  );
    ed->jets.eta.push_back( m_ntuple->jet_eta[i] );
    ed->jets.phi.push_back( m_ntuple->jet_phi[i] );
    ed->jets.E.push_back(   m_ntuple->jet_E[i]   );
    ed->jets.m.push_back(   m_ntuple->jet_m[i]   );
  }

  return success;
}


/////////////////////////////////////////////


/////////////////////////////////////////
// Plugin

extern "C" {
  NtupleWrapperPluginFactory_MiniML * MakeNtupleWrapperPlugin() {
    return new NtupleWrapperPluginFactory_MiniML( "MiniML" );
  };
}
