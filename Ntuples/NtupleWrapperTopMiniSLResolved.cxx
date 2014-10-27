#include "NtupleWrapperTopMiniSLResolved.h"

NtupleWrapperTopMiniSLResolved::NtupleWrapperTopMiniSLResolved( const AnalysisParams_t analysisParameters ) :
  NtupleWrapper< TopMiniSLResolved >( analysisParameters )
{
   m_dumper_leptons = new EventDumperLeptons<TopMiniSLResolved>();
   m_dumper_leptons->SetNtuple( m_ntuple );
   m_dumper_leptons->SetAnalysisParameters( analysisParameters );

   m_dumper_jets = new EventDumperJets<TopMiniSLResolved>();
   m_dumper_jets->SetNtuple( m_ntuple );
   m_dumper_jets->SetAnalysisParameters( analysisParameters );

//   m_dumper_mctruth = new EventDumperMCTruth<TopMiniSLResolved>();
//   m_dumper_mctruth->SetNtuple( m_ntuple );
//   m_dumper_mctruth->SetAnalysisParameters( analysisParameters );
}

/////////////////////////////////////////////


NtupleWrapperTopMiniSLResolved::~NtupleWrapperTopMiniSLResolved()
{
   if( m_dumper_leptons ) delete m_dumper_leptons;
   if( m_dumper_jets    ) delete m_dumper_jets;
//   if( m_dumper_mctruth ) delete m_dumper_mctruth;
}

/////////////////////////////////////////////


bool NtupleWrapperTopMiniSLResolved::MakeEventInfo( EventData * ed )
{
  bool success = true;

//  ed->info.eventNumber     = GET_VALUE( eventNumber );
//  ed->info.runNumber       = GET_VALUE( runNumber );

//  ed->info.mcChannelNumber = GET_VALUE( channelNumber );
//  ed->info.mcWeight        = GET_VALUE( eventWeight );
  ed->info.eventNumber     = GET_VALUE( eventNumber );
  ed->info.runNumber       = GET_VALUE( runNumber );

  ed->info.mcChannelNumber = GET_VALUE( channelNumber );
  ed->info.mcWeight        = GET_VALUE( eventWeight );

  SET_PROPERTY( dataPeriod );
  SET_PROPERTY( mu );

  SET_PROPERTY( pvxp_n );
  SET_PROPERTY( vxp_z );

  SET_PROPERTY( hfor );

  ed->property["scaleFactor_PILEUP"]     = GET_VALUE( scaleFactor_PILEUP     );
  ed->property["scaleFactor_ELE"]        = GET_VALUE( scaleFactor_ELE        );
  ed->property["scaleFactor_MUON"]	 = GET_VALUE( scaleFactor_MUON       );
  ed->property["scaleFactor_BTAG"]	 = GET_VALUE( scaleFactor_BTAG       );
  ed->property["scaleFactor_TRIGGER"]    = GET_VALUE( scaleFactor_TRIGGER    );
  ed->property["scaleFactor_WJETSNORM"]  = GET_VALUE( scaleFactor_WJETSNORM  );
  ed->property["scaleFactor_WJETSSHAPE"] = GET_VALUE( scaleFactor_WJETSSHAPE );
  ed->property["scaleFactor_JVFSF"]	 = GET_VALUE( scaleFactor_JVFSF      );
  ed->property["scaleFactor_ZVERTEX"]    = GET_VALUE( scaleFactor_ZVERTEX    );

  return success;
}


/////////////////////////////////////////////


bool NtupleWrapperTopMiniSLResolved::MakeEventTrigger( EventData * ed )
{ 
  bool success = true;

// CHECK_TRIGGER( "EF_mu18i" );

  return success;
}


/////////////////////////////////////////////


bool NtupleWrapperTopMiniSLResolved::MakeEventMET( EventData * ed )
{
  bool success = true;

  ed->MET.et    = GET_VALUE( met_et );
  ed->MET.phi   = GET_VALUE( met_phi );
  //  ed->MET.etx   = 0.;
  //  ed->MET.ety   = 0.;
  ed->MET.sumet = GET_VALUE( met_sumet  );
  ed->MET.mwt   = GET_VALUE( mwt );
  //  SET_PROPERTY( mwt );

  return success;
}


/////////////////////////////////////////////


bool NtupleWrapperTopMiniSLResolved::MakeEventElectrons( EventData * ed )
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


bool NtupleWrapperTopMiniSLResolved::MakeEventMuons( EventData * ed )
{
  bool success = true;

  return success;
}


/////////////////////////////////////////////


bool NtupleWrapperTopMiniSLResolved::MakeEventJets( EventData * ed )
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


bool NtupleWrapperTopMiniSLResolved::MakeEventTruth( EventData * ed )
{
  bool success = true;

  return success;
}


/////////////////////////////////////////
// Plugin

extern "C" {
  NtupleWrapperPluginFactory_TopMiniSLResolved * MakeNtupleWrapperPlugin() {
    return new NtupleWrapperPluginFactory_TopMiniSLResolved( "TopMiniSLResolved" );
  };
}
