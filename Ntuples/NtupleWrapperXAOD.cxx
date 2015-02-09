#include "NtupleWrapperXAOD.h"
#include "PhysicsHelperFunctions.h"

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

  const xAOD::MissingETContainer* METFinals = 0;
  if( !m_xAODevent->retrieve(METFinals, "MET_RefFinal") ) throw runtime_error( "Cannot retrieve MET_RefFinal container\n" );
  
  const xAOD::MissingET* metRefFinal = 0;
  if( METFinals ) metRefFinal = (*METFinals)["Final"];

  ed->MET.et    = metRefFinal->met();
  ed->MET.sumet = metRefFinal->sumet();

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

  const xAOD::ElectronContainer* electrons;
  if( !m_xAODevent->retrieve( electrons, "ElectronCollection" ) ) throw runtime_error( "No electrons collection" );

  xAOD::ElectronContainer::const_iterator elItr  = electrons->begin();
  xAOD::ElectronContainer::const_iterator elItrE = electrons->end();
  for( ; elItr != elItrE ; ++elItr ) {
      const double pT = (*elItr)->pt();
      const double eta = (*elItr)->eta();

      if( pT < 20*GeV ) continue;
      if( fabs(eta) > 2.5 ) continue;

      ed->electrons.pT.push_back(  pT );
      ed->electrons.eta.push_back( eta );
      ed->electrons.phi.push_back( (*elItr)->phi() );
      ed->electrons.E.push_back(   (*elItr)->e() );
      ed->electrons.n++;
  }

  return success;
}


/////////////////////////////////////////////


bool NtupleWrapperXAOD::MakeEventMuons( EventData * ed )
{
  bool success = true;

  const xAOD::MuonContainer* muons;
  if( !m_xAODevent->retrieve( muons, "Muons" ) ) throw runtime_error( "No muons collection" );

  xAOD::MuonContainer::const_iterator muItr  = muons->begin();
  xAOD::MuonContainer::const_iterator muItrE = muons->end();
  for( ; muItr != muItrE ; ++muItr ) {
      const double pT = (*muItr)->pt();
      const double eta = (*muItr)->eta();

      if( pT < 20*GeV ) continue;
      if( fabs(eta) > 2.5 ) continue;

      ed->muons.pT.push_back(  pT );
      ed->muons.eta.push_back( eta );
      ed->muons.phi.push_back( (*muItr)->phi() );
      ed->muons.E.push_back(   (*muItr)->e() );
      ed->muons.n++;
  }

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
      const double phi = (*jetItr)->phi();
      const double E   = (*jetItr)->e();

      if( pT < 25*GeV ) continue;
      if( fabs(eta) > 2.5 ) continue;

      ed->jets.pT.push_back(  pT  );
      ed->jets.eta.push_back( eta );
      ed->jets.phi.push_back( phi );
      ed->jets.E.push_back(   E   ); 

      const double jet_m = PhysicsHelperFunctions::Mass( ed->jets, ed->jets.n );
      ed->jets.m.push_back( jet_m );
      ed->jets.n++;

      const xAOD::BTagging* btag =(*jetItr)->btagging();
      const double mv1 = btag->MV1_discriminant();
      ed->jets.property["MV1"].push_back( mv1 );      

      if( mv1 > 0.7892 ) {
          ed->bjets.n++;
          ed->bjets.pT.push_back(  pT  );
          ed->bjets.eta.push_back( eta );
          ed->bjets.phi.push_back( phi );
          ed->bjets.E.push_back(   E   );
          ed->bjets.m.push_back(   jet_m );
          ed->bjets.property["MV1"].push_back( mv1 );
      }      
  }


  const xAOD::JetContainer * akt10Jets;
  if( !m_xAODevent->retrieve( akt10Jets, "AntiKt10LCTopoJets" ) ) {
    cout << "WARNING: no akt10 jets collection found." << endl;
  }

  xAOD::JetContainer::const_iterator fjetItr  = akt10Jets->begin();
  xAOD::JetContainer::const_iterator fjetItrE = akt10Jets->end();
  for( ; fjetItr != fjetItrE ; ++fjetItr ) {
      const double pT = (*fjetItr)->pt();
      const double eta = (*fjetItr)->eta();
      const double phi = (*fjetItr)->phi();
      const double E   = (*fjetItr)->e();

      if( pT < 25*GeV ) continue;
      if( fabs(eta) > 2.5 ) continue;

      ed->fjets.pT.push_back(  pT  );
      ed->fjets.eta.push_back( eta );
      ed->fjets.phi.push_back( phi );
      ed->fjets.E.push_back(   E   );

      const double fjet_m = PhysicsHelperFunctions::Mass( ed->fjets, ed->fjets.n );
      ed->fjets.m.push_back( fjet_m );
      ed->fjets.n++;
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
