#include "NtupleWrapperMiniSLBoost.h"

NtupleWrapperMiniSLBoost::NtupleWrapperMiniSLBoost( const char * fileListName, const char * branchListName, const char * treeName ) : 
  NtupleWrapper< MiniSLBoost >( fileListName, branchListName, treeName )
{
}

/////////////////////////////////////////////


NtupleWrapperMiniSLBoost::~NtupleWrapperMiniSLBoost()
{

}

/////////////////////////////////////////////


bool NtupleWrapperMiniSLBoost::MakeEventInfo( EventData * ed )
{
  bool success = true;

  ed->info.eventNumber     = GET_VALUE( eventNumber );
  ed->info.runNumber       = GET_VALUE( runNumber );

  ed->info.mcChannelNumber = GET_VALUE( channelNumber );
  ed->info.mcWeight        = GET_VALUE( eventWeight );

  return success;
}


/////////////////////////////////////////////


bool NtupleWrapperMiniSLBoost::MakeEventMET( EventData * ed )
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


bool NtupleWrapperMiniSLBoost::MakeEventElectrons( EventData * ed )
{
  bool success = true;

  ed->electrons.n = 1;
  ed->electrons.pT.push_back( GET_VALUE( lep_pt ) );
  ed->electrons.eta.push_back( GET_VALUE( lep_eta ) );
  ed->electrons.phi.push_back( GET_VALUE( lep_phi ) );
  ed->electrons.E.push_back( GET_VALUE( lep_E ) );

  /*
  ed->electrons.n = GET_VALUE( el_n );
  for( int i = 0 ; i < ed->electrons.n ; ++i ) {
    ed->electrons.pT.push_back( GET_VALUE_ARRAY( el_pt, i ) );
  }
  */

  return success;
}


/////////////////////////////////////////////


bool NtupleWrapperMiniSLBoost::MakeEventMuons( EventData * ed )
{
  bool success = true;

  return success;
}


/////////////////////////////////////////////


bool NtupleWrapperMiniSLBoost::MakeEventJets( EventData * ed )
{
  bool success = true;
  
  ed->jets.n = GET_VALUE( jet_n );
  for( int i = 0 ; i < ed->jets.n ; ++i ) {
    ed->jets.pT.push_back(  m_ntuple->jet_pt[i]  );
    ed->jets.eta.push_back( m_ntuple->jet_eta[i] );
    ed->jets.phi.push_back( m_ntuple->jet_phi[i] );
    ed->jets.E.push_back(   m_ntuple->jet_E[i]   );
  }

  ed->fjets.n = GET_VALUE( jet_n );
  for( int i = 0 ; i < ed->jets.n ; ++i ) {
    ed->fjets.pT.push_back(  m_ntuple->jet_pt[i]  );
    ed->fjets.eta.push_back( m_ntuple->jet_eta[i] );
    ed->fjets.phi.push_back( m_ntuple->jet_phi[i] );
    ed->fjets.E.push_back(   m_ntuple->jet_E[i]   );

    ed->fjets.d12.push_back( m_ntuple->fjet_d12[i] );
    ed->fjets.dR_lj.push_back( m_ntuple->fjet_DeltaPhi_Lap_FatJet[i] );
    ed->fjets.dPhi_lj.push_back( m_ntuple->fjet_DeltaR_LapJet_Fatjet[i] );
  }

  return success;
}


/////////////////////////////////////////////


/////////////////////////////////////////
// Plugin

extern "C" {
  NtupleWrapperPluginFactory_MiniSLBoost * MakeNtupleWrapperPlugin() {
    return new NtupleWrapperPluginFactory_MiniSLBoost( "MiniSLBoost" );
  };
}
