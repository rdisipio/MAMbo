#include "NtupleWrapperLHEF.h"

NtupleWrapperLHEF::NtupleWrapperLHEF( const AnalysisParams_t analysisParameters ):
  NtupleWrapper< LHEF >( analysisParameters )
{
}

/////////////////////////////////////////////


NtupleWrapperLHEF::~NtupleWrapperLHEF()
{

}

/////////////////////////////////////////////


bool NtupleWrapperLHEF::MakeEventInfo( EventData * ed )
{
  bool success = true;

//  ed->info.eventNumber     = GET_VALUE( eventNumber );
//  ed->info.runNumber       = GET_VALUE( runNumber );

//  ed->info.mcChannelNumber = GET_VALUE( channelNumber );
//  ed->info.mcWeight        = GET_VALUE( eventWeight );

  return success;
}


/////////////////////////////////////////////


bool NtupleWrapperLHEF::MakeEventTrigger( EventData * ed )
{ 
  bool success = true;

// CHECK_TRIGGER( "EF_mu18i" );

  return success;
}


/////////////////////////////////////////////


bool NtupleWrapperLHEF::MakeEventMET( EventData * ed )
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


bool NtupleWrapperLHEF::MakeEventElectrons( EventData * ed )
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


bool NtupleWrapperLHEF::MakeEventMuons( EventData * ed )
{
  bool success = true;

  return success;
}


/////////////////////////////////////////////


bool NtupleWrapperLHEF::MakeEventJets( EventData * ed )
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


bool NtupleWrapperLHEF::MakeEventTruth( EventData * ed )
{
  bool success = true;

  const size_t np = GET_VALUE( Particle_size );
  for( size_t ip = 0 ; ip < np ; ++ip ) {

      const int barcode = GET_VALUE_ARRAY( Particle_fUniqueID, ip );
      if( barcode > 2e5 ) continue; //skip GEANT particles

      const int status = GET_VALUE_ARRAY( Particle_Status, ip );
      const int    pid = GET_VALUE_ARRAY( Particle_PID, ip );
      const int   apid = abs(pid);


      if( (apid!=6) || (apid!=25) ) continue;

      const double pT  = GET_VALUE_ARRAY( Particle_PT, ip );
      const double eta = GET_VALUE_ARRAY( Particle_Eta, ip );
      const double phi = GET_VALUE_ARRAY( Particle_Phi, ip );
//      const double E   = GET_VALUE_ARRAY( Particle_E, ip );
      const double m   = GET_VALUE_ARRAY( Particle_M, ip );

      const int q = ( apid == 0 ) ? 0 : pid / apid;

      TLorentzVector p;
      p.SetPtEtaPhiM( pT, eta, phi, m );
      HelperFunctions::DumpTruthParticleToEventData( p, pid, status, barcode, q, &ed->mctruth );

/*
      const PhysicsHelperFunctions::TOP_QUARK_DECAY_CLASS topdecay =
        PhysicsHelperFunctions::ClassifyTopDecay( ip, this->m_truth_ntuple->mc_child_index, this->m_truth_ntuple->mc_pdgId );
      const bool isHadronic = ( topdecay == PhysicsHelperFunctions::kTopDecayHadronic );
      ed->mctruth.property["isHadronic"].push_back( isHadronic );
*/
  } 

  return success;
}


/////////////////////////////////////////
// Plugin

extern "C" {
  NtupleWrapperPluginFactory_LHEF * MakeNtupleWrapperPlugin() {
    return new NtupleWrapperPluginFactory_LHEF( "LHEF" );
  };
}
