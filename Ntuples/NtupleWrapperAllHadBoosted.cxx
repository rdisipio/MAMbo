#include "NtupleWrapperAllHadBoosted.h"

#include "PhysicsHelperFunctions.h"

NtupleWrapperAllHadBoosted::NtupleWrapperAllHadBoosted( const AnalysisParams_t analysisParameters ):
  NtupleWrapper< AllHadBoosted >( analysisParameters )
{
}

/////////////////////////////////////////////


NtupleWrapperAllHadBoosted::~NtupleWrapperAllHadBoosted()
{

}

/////////////////////////////////////////////


bool NtupleWrapperAllHadBoosted::MakeEventInfo( EventData * ed )
{
  bool success = true;

  ed->info.eventNumber     = GET_VALUE( eventNumber );
  ed->info.runNumber	   = GET_VALUE( runNumber );
  ed->info.mcChannelNumber = GET_VALUE( mcChannelNumber );
  ed->info.mcWeight        = GET_VALUE( weight_mc );

  return success;
}


/////////////////////////////////////////////


bool NtupleWrapperAllHadBoosted::MakeEventTrigger( EventData * ed )
{ 
  bool success = true;

// CHECK_TRIGGER( "EF_mu18i" );

  return success;
}


/////////////////////////////////////////////


bool NtupleWrapperAllHadBoosted::MakeEventMET( EventData * ed )
{
  bool success = true;

  ed->MET.et    = GET_VALUE( met_met );
  ed->MET.phi   = GET_VALUE( met_phi );

  return success;
}


/////////////////////////////////////////////


bool NtupleWrapperAllHadBoosted::MakeEventLeptons( EventData * ed )
{
  bool success = true;

  ed->electrons.n = m_ntuple->el_pt->size();
   //if( m_ntuple->el_isTight) cout << "Debug: el isTight size is " <<  m_ntuple->el_isTight->size() << endl;
  for( int i = 0 ; i < ed->electrons.n ; ++i ) {
    ed->electrons.pT.push_back(  GET_VALUE_VECTOR( el_pt,  i ) );
    ed->electrons.eta.push_back( GET_VALUE_VECTOR( el_eta, i ) );
    ed->electrons.phi.push_back( GET_VALUE_VECTOR( el_phi, i ) );
    ed->electrons.E.push_back(   GET_VALUE_VECTOR( el_e,   i ) );
    ed->electrons.q.push_back(   GET_VALUE_VECTOR( el_charge, i ) );
//    if( m_ntuple->el_isTight ) ed->electrons.property[ "tight" ].push_back( (int)GET_VALUE_VECTOR( el_isTight, i ) );
//    if( m_ntuple->el_cl_eta )  ed->electrons.property[ "el_cl_eta" ].push_back(GET_VALUE_VECTOR( el_cl_eta, i ) );

    ed->leptons.pT.push_back(  GET_VALUE_VECTOR( el_pt,  i ) );
    ed->leptons.eta.push_back( GET_VALUE_VECTOR( el_eta, i ) );
    ed->leptons.phi.push_back( GET_VALUE_VECTOR( el_phi, i ) );
    ed->leptons.E.push_back(   GET_VALUE_VECTOR( el_e,   i ) );
    ed->leptons.q.push_back(   GET_VALUE_VECTOR( el_charge, i ) );
   // cout << "Debug: electron " << i+1 << " is tight = " << (int) GET_VALUE_VECTOR( el_isTight, i ) << endl;
//    if( m_ntuple->el_isTight ) ed->leptons.property[ "tight" ].push_back( (int)GET_VALUE_VECTOR( el_isTight, i ) );
//    if( m_ntuple->el_cl_eta )  ed->leptons.property[ "el_cl_eta" ].push_back(GET_VALUE_VECTOR( el_cl_eta, i ) );
  }


  ed->muons.n = m_ntuple->mu_pt->size();

  for( int i = 0 ; i < ed->muons.n ; ++i ) {
    ed->muons.pT.push_back(  GET_VALUE_VECTOR( mu_pt,  i ) );
    ed->muons.eta.push_back( GET_VALUE_VECTOR( mu_eta, i ) );
    ed->muons.phi.push_back( GET_VALUE_VECTOR( mu_phi, i ) );
    ed->muons.E.push_back(   GET_VALUE_VECTOR( mu_e,   i ) );
    ed->muons.q.push_back(   GET_VALUE_VECTOR( mu_charge, i     ) );
//    if( m_ntuple->mu_isTight ) ed->muons.property[ "tight" ].push_back( (int)GET_VALUE_VECTOR( mu_isTight, i ) );

    ed->leptons.pT.push_back(  GET_VALUE_VECTOR( mu_pt,  i ) );
    ed->leptons.eta.push_back( GET_VALUE_VECTOR( mu_eta, i ) );
    ed->leptons.phi.push_back( GET_VALUE_VECTOR( mu_phi, i ) );
    ed->leptons.E.push_back(   GET_VALUE_VECTOR( mu_e,   i ) );
    ed->leptons.q.push_back(   GET_VALUE_VECTOR( mu_charge, i ) );
//    if( m_ntuple->mu_isTight ) ed->leptons.property[ "tight" ].push_back( (int)GET_VALUE_VECTOR( mu_isTight, i ) );

  }
  // should be re-ordered by pT. Or there is just one lepton, either el or mu?

//  cout << "DEBUG: el_n=" << ed->electrons.n << " mu_n=" << ed->muons.n << endl;

  return success;
}


/////////////////////////////////////////////


bool NtupleWrapperAllHadBoosted::MakeEventJets( EventData * ed )
{
  bool success = true;

    size_t alljet_n = m_ntuple->jet_pt->size();
    ed->jets.n  = 0;
    ed->bjets.n = 0;
    ed->ljets.n = 0;
    int jindex = 0;

    for( int j = 0; j < alljet_n; ++j ) {
        const double jet_pT   = GET_VALUE_VECTOR( jet_pt, j );
        const double jet_eta  = GET_VALUE_VECTOR( jet_eta, j );
        const double jet_phi  = GET_VALUE_VECTOR( jet_phi, j );
        const double jet_E    = GET_VALUE_VECTOR( jet_e, j );

        if( jet_pT < 25 * GeV ) continue;
        if( fabs(jet_eta) > 2.5 ) continue;

            ed->jets.n++;

            ed->jets.index.push_back( jindex );

            ed->jets.pT.push_back(  jet_pT );
            ed->jets.eta.push_back( jet_eta );
            ed->jets.phi.push_back( jet_phi );
            ed->jets.E.push_back(   jet_E );

            const double jet_m = PhysicsHelperFunctions::Mass( ed->jets, (ed->jets.n-1) );
            ed->jets.m.push_back( jet_m );

            ed->jets.property["jvt"].push_back( GET_VALUE_VECTOR(jet_jvt, j)          );

            const double mv2c10 = GET_VALUE_VECTOR(jet_mv2c10, j);
            ed->jets.property["mv2c20"].push_back( mv2c10 );

            if( mv2c10 > 0.8244 ) { // 70% eff w.p.
                ed->bjets.n++;

                ed->bjets.pT.push_back( jet_pT );
                ed->bjets.eta.push_back( jet_eta );
                ed->bjets.phi.push_back( jet_phi );
                ed->bjets.E.push_back( jet_E );
                ed->bjets.m.push_back( jet_m );
                ed->bjets.index.push_back( jindex );
                ed->bjets.property["mv2c10"].push_back(mv2c10);
            } else {
                ed->ljets.n++;

                ed->ljets.pT.push_back( jet_pT );
                ed->ljets.eta.push_back( jet_eta );
                ed->ljets.phi.push_back( jet_phi );
                ed->ljets.E.push_back( jet_E );
                ed->ljets.m.push_back( jet_m );
                ed->ljets.index.push_back( jindex );
                ed->ljets.property["mv2c10"].push_back(mv2c10);
         }
        jindex++;
    }

  size_t allljet_n = m_ntuple->ljet_pt->size();
    ed->fjets.n = 0;

    for( int lj = 0; lj < allljet_n; ++lj ) {

      const double ljet_pT   = GET_VALUE_VECTOR( ljet_pt,  lj );
      const double ljet_eta  = GET_VALUE_VECTOR( ljet_eta, lj );
      const double ljet_phi  = GET_VALUE_VECTOR( ljet_phi, lj );
      const double ljet_E    = GET_VALUE_VECTOR( ljet_e, lj );
      const double ljet_m    = GET_VALUE_VECTOR( ljet_m, lj );

      if( ljet_pT < 25 * GeV ) continue;
      if( fabs(ljet_eta) > 2.5 ) continue;

      ed->fjets.n++;

      ed->fjets.index.push_back( lj );

      ed->fjets.pT.push_back(  ljet_pT );
      ed->fjets.eta.push_back( ljet_eta );
      ed->fjets.phi.push_back( ljet_phi );
      ed->fjets.E.push_back(   ljet_E );
      //      const double ljet_m = PhysicsHelperFunctions::Mass( ed->ljets, lj );  ////For the Large-Rjet the mass is in the Ntuple
      ed->fjets.m.push_back( ljet_m );

      ////--Tagging and substructures properties of the Large-R jet--/////
      const double sd12 = GET_VALUE_VECTOR(ljet_sd12, lj);
      ed->fjets.property["sd12"].push_back( sd12 );

      const double sd23 = GET_VALUE_VECTOR(ljet_sd23, lj);
      ed->fjets.property["sd23"].push_back( sd23 );

      const double tau32 = GET_VALUE_VECTOR(ljet_tau32, lj);
      ed->fjets.property["tau32"].push_back( tau32 );

      const double tau21 = GET_VALUE_VECTOR(ljet_tau21, lj);
      ed->fjets.property["tau21"].push_back( tau21 );

      const int topTag50 = GET_VALUE_VECTOR(ljet_topTag50, lj);
      ed->fjets.property["topTag50"].push_back(topTag50 );

      const int topTag80 = GET_VALUE_VECTOR(ljet_topTag80, lj);
      ed->fjets.property["topTag80"].push_back(topTag80);

    }

  return success;
}


/////////////////////////////////////////////


bool NtupleWrapperAllHadBoosted::MakeEventTruth( EventData * ed )
{
  bool success = true;

  return success;
}


/////////////////////////////////////////
// Plugin

extern "C" {
  NtupleWrapperPluginFactory_AllHadBoosted * MakeNtupleWrapperPlugin() {
    return new NtupleWrapperPluginFactory_AllHadBoosted( "AllHadBoosted" );
  };
}
