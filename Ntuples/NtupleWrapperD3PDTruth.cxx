#include "NtupleWrapperD3PDTruth.h"

NtupleWrapperD3PDTruth::NtupleWrapperD3PDTruth( const char * fileListName, const char * branchListName, const char * treeName ) : 
  NtupleWrapper< D3PDTruth >( fileListName, branchListName, treeName )
{
}

/////////////////////////////////////////////


NtupleWrapperD3PDTruth::~NtupleWrapperD3PDTruth()
{

}

/////////////////////////////////////////////


bool NtupleWrapperD3PDTruth::MakeEventInfo( EventData * ed )
{
  bool success = true;

//  ed->info.eventNumber     = GET_VALUE( eventNumber );
//  ed->info.runNumber       = GET_VALUE( runNumber );

//  ed->info.mcChannelNumber = GET_VALUE( channelNumber );
//  ed->info.mcWeight        = GET_VALUE( eventWeight );

  return success;
}


/////////////////////////////////////////////


bool NtupleWrapperD3PDTruth::MakeEventTrigger( EventData * ed )
{ 
  bool success = true;

// CHECK_TRIGGER( "EF_mu18i" );

  return success;
}


/////////////////////////////////////////////


bool NtupleWrapperD3PDTruth::MakeEventMET( EventData * ed )
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


bool NtupleWrapperD3PDTruth::MakeEventElectrons( EventData * ed )
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


bool NtupleWrapperD3PDTruth::MakeEventMuons( EventData * ed )
{
  bool success = true;

  return success;
}


/////////////////////////////////////////////


bool NtupleWrapperD3PDTruth::MakeEventJets( EventData * ed )
{
  bool success = true;


/*  
  ed->jets.n = GET_VALUE( jet_n );
  for( int i = 0 ; i < ed->jets.n ; ++i ) {
    ed->jets.pT.push_back(  m_ntuple->jet_pt[i]  );
    ed->jets.eta.push_back( m_ntuple->jet_eta[i] );
    ed->jets.phi.push_back( m_ntuple->jet_phi[i] );
    ed->jets.E.push_back(   m_ntuple->jet_E[i]   );
  }

  ed->fjet.n   = m_ntuple->fjet_n;
  ed->fjet.pT  = m_ntuple->fjet_pt[0];
  ed->fjet.eta = m_ntuple->fjet_eta[0];
  ed->fjet.phi = m_ntuple->fjet_phi[0];
  ed->fjet.E   = m_ntuple->fjet_E[0];

  ed->fjet.d12     =  m_ntuple->fjet_d12[0];
  ed->fjet.dR_lj   =  m_ntuple->fjet_DeltaPhi_Lap_FatJet[0];
  ed->fjet.dPhi_lj =  m_ntuple->fjet_DeltaR_LapJet_Fatjet[0];
*/
  return success;
}


/////////////////////////////////////////////


bool NtupleWrapperD3PDTruth::MakeEventTruth( EventData * ed )
{
  bool success = true;

  return success;
}


/////////////////////////////////////////
// Plugin

extern "C" {
  NtupleWrapperPluginFactory_D3PDTruth * MakeNtupleWrapperPlugin() {
    return new NtupleWrapperPluginFactory_D3PDTruth( "D3PDTruth" );
  };
}
