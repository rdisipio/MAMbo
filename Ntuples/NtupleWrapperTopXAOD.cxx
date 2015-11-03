#include "NtupleWrapperTopXAOD.h"

#include "PhysicsHelperFunctions.h"

NtupleWrapperTopXAOD::NtupleWrapperTopXAOD( const AnalysisParams_t analysisParameters ):
  NtupleWrapper< TopXAOD >( analysisParameters )
{
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
  ed->info.mcChannelNumber = GET_VALUE( mcChannelNumber );
  ed->info.mcWeight        = GET_VALUE( weight_mc );
//  ed->info.mcWeight        = 1.0; // no mcWeight??

  SET_PROPERTY( passed_resolved_ejets );
  SET_PROPERTY( passed_resolved_mujets );
  SET_PROPERTY( passed_boosted_ejets );
  SET_PROPERTY( passed_boosted_mujets );

  SET_PROPERTY( HLT_mu20_iloose_L1MU15 );
  SET_PROPERTY( HLT_mu50 );
  SET_PROPERTY( HLT_e60_lhmedium );
  SET_PROPERTY( HLT_e24_lhmedium_L1EM18VH );
  SET_PROPERTY( HLT_e120_lhloose );

  ed->property["scaleFactor_BTAG"]   = GET_VALUE( weight_bTagSF_77 );

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

  ed->MET.et    = GET_VALUE( met_met );
  ed->MET.phi   = GET_VALUE( met_phi );
  //  ed->MET.etx   = 0.;
  //  ed->MET.ety   = 0.;
//  ed->MET.sumet = GET_VALUE( met_sumet  );
//  ed->MET.mwt   = GET_VALUE( mwt );

  return success;
}


/////////////////////////////////////////////


bool NtupleWrapperTopXAOD::MakeEventLeptons( EventData * ed )
{
  bool success = true;

  ed->electrons.n = m_ntuple->el_pt->size();
  for( int i = 0 ; i < ed->electrons.n ; ++i ) {
    ed->electrons.pT.push_back(  GET_VALUE_VECTOR( el_pt,  i ) );
    ed->electrons.eta.push_back( GET_VALUE_VECTOR( el_eta, i ) );
    ed->electrons.phi.push_back( GET_VALUE_VECTOR( el_phi, i ) );
    ed->electrons.E.push_back(   GET_VALUE_VECTOR( el_e,   i ) );
    ed->electrons.q.push_back(   GET_VALUE_VECTOR( el_charge, i ) );

    ed->leptons.pT.push_back(  GET_VALUE_VECTOR( el_pt,  i ) );
    ed->leptons.eta.push_back( GET_VALUE_VECTOR( el_eta, i ) );
    ed->leptons.phi.push_back( GET_VALUE_VECTOR( el_phi, i ) );
    ed->leptons.E.push_back(   GET_VALUE_VECTOR( el_e,   i ) );
    ed->leptons.q.push_back(   GET_VALUE_VECTOR( el_charge, i ) );
  }


  ed->muons.n = m_ntuple->mu_pt->size();
  for( int i = 0 ; i < ed->muons.n ; ++i ) {
    ed->muons.pT.push_back(  GET_VALUE_VECTOR( mu_pt,  i ) );
    ed->muons.eta.push_back( GET_VALUE_VECTOR( mu_eta, i ) );
    ed->muons.phi.push_back( GET_VALUE_VECTOR( mu_phi, i ) );
    ed->muons.E.push_back(   GET_VALUE_VECTOR( mu_e,   i ) );
    ed->muons.q.push_back(   GET_VALUE_VECTOR( mu_charge, i	) );

    ed->leptons.pT.push_back(  GET_VALUE_VECTOR( mu_pt,  i ) );
    ed->leptons.eta.push_back( GET_VALUE_VECTOR( mu_eta, i ) );
    ed->leptons.phi.push_back( GET_VALUE_VECTOR( mu_phi, i ) );
    ed->leptons.E.push_back(   GET_VALUE_VECTOR( mu_e,   i ) );
    ed->leptons.q.push_back(   GET_VALUE_VECTOR( mu_charge, i )	);

  }
  // should be re-ordered by pT. Or there is just one lepton, either el or mu?

//  cout << "DEBUG: el_n=" << ed->electrons.n << " mu_n=" << ed->muons.n << endl;

  return success;
}


/////////////////////////////////////////////


bool NtupleWrapperTopXAOD::MakeEventJets( EventData * ed )
{
  bool success = true;

    size_t alljet_n = m_ntuple->jet_pt->size();
    ed->jets.n  = 0;
    ed->bjets.n = 0;
    ed->ljets.n = 0;
    ed->fjets.n = 0;

    for( int j = 0; j < alljet_n; ++j ) {
        const double jet_pT   = GET_VALUE_VECTOR( jet_pt, j );
        const double jet_eta  = GET_VALUE_VECTOR( jet_eta, j );
        const double jet_phi  = GET_VALUE_VECTOR( jet_phi, j );
        const double jet_E    = GET_VALUE_VECTOR( jet_e, j );

        if( jet_pT < 25 * GeV ) continue;
        if( fabs(jet_eta) > 2.5 ) continue;

            ed->jets.n++;

            ed->jets.index.push_back( j );

            ed->jets.pT.push_back(  jet_pT );
            ed->jets.eta.push_back( jet_eta );
            ed->jets.phi.push_back( jet_phi );
            ed->jets.E.push_back(   jet_E );

            const double jet_m = PhysicsHelperFunctions::Mass( ed->jets, j );
            ed->jets.m.push_back( jet_m );

            ed->jets.property["jvt"].push_back(          GET_VALUE_VECTOR(jet_jvt, j)          );

            const double mv2c20 = GET_VALUE_VECTOR(jet_mv2c20, j);
            ed->jets.property["mv2c20"].push_back( mv2c20 );

            if( mv2c20 > -0.0436 ) { // 70% eff w.p.
                ed->bjets.n++;

                ed->bjets.pT.push_back( jet_pT );
                ed->bjets.eta.push_back( jet_eta );
                ed->bjets.phi.push_back( jet_phi );
                ed->bjets.E.push_back( jet_E );
                ed->bjets.m.push_back( jet_m );
                ed->bjets.index.push_back( j );
                ed->bjets.property["mv2c20"].push_back(mv2c20);
            } else {
                ed->ljets.n++;

                ed->ljets.pT.push_back( jet_pT );
                ed->ljets.eta.push_back( jet_eta );
                ed->ljets.phi.push_back( jet_phi );
                ed->ljets.E.push_back( jet_E );
                ed->ljets.m.push_back( jet_m );
                ed->ljets.index.push_back( j );
                ed->ljets.property["mv2c20"].push_back(mv2c20);
            }
    }

  return success;
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
