#include "NtupleWrapperTopMini.h"

#include "PhysicsHelperFunctions.h"

NtupleWrapperTopMini::NtupleWrapperTopMini( const char * fileListName, const char * branchListName, const char * treeName ) : 
  NtupleWrapper< TopMini >( fileListName, branchListName, treeName )
{
}

/////////////////////////////////////////////


NtupleWrapperTopMini::~NtupleWrapperTopMini()
{

}

/////////////////////////////////////////////


bool NtupleWrapperTopMini::MakeEventInfo( EventData * ed )
{
  bool success = true;

  ed->info.eventNumber     = GET_VALUE( eventNumber );
  ed->info.runNumber       = GET_VALUE( runNumber );

  ed->info.mcChannelNumber = GET_VALUE( channelNumber );
  ed->info.mcWeight        = GET_VALUE( mcevt_weight ); /*eventWeight );*/

  SET_PROPERTY( dataPeriod );
  SET_PROPERTY( mu );

  SET_PROPERTY( pvxp_n );
  SET_PROPERTY( vxp_z );

  SET_PROPERTY( hfor );

/*
  bool goodPV = false;
  const int ntrx = m_ntuple->m_vxp_nTracks->at(0);      
  if( ntrx >= 5 ) {
    goodPV = true;
    // break;
  }
  ed->property["goodPV"] = goodPV;
*/

/*
  ed->property["scaleFactor_PILEUP"]     = GET_VALUE( scaleFactor_PILEUP     );
  ed->property["scaleFactor_ELE"]        = GET_VALUE( scaleFactor_ELE        );
  ed->property["scaleFactor_MUON"]       = GET_VALUE( scaleFactor_MUON       );
  ed->property["scaleFactor_BTAG"]       = GET_VALUE( scaleFactor_BTAG       );
  ed->property["scaleFactor_TRIGGER"]    = GET_VALUE( scaleFactor_TRIGGER    );
  ed->property["scaleFactor_WJETSNORM"]  = GET_VALUE( scaleFactor_WJETSNORM  );
  ed->property["scaleFactor_WJETSSHAPE"] = GET_VALUE( scaleFactor_WJETSSHAPE );
  ed->property["scaleFactor_JVFSF"]      = GET_VALUE( scaleFactor_JVFSF      );
  ed->property["scaleFactor_ZVERTEX"]    = GET_VALUE( scaleFactor_ZVERTEX    );
*/
  ed->property["scaleFactor_PILEUP"]     = GET_VALUE( PUweight     );
  ed->property["scaleFactor_ELE"]        = GET_VALUE( elecScale  );
  ed->property["scaleFactor_MUON"]       = GET_VALUE( muonScale     );
  ed->property["scaleFactor_BTAG"]       = GET_VALUE( BTagSFweight     );
  ed->property["scaleFactor_TRIGGER"]    = GET_VALUE( trigScale    );
  ed->property["scaleFactor_WJETSNORM"]  = GET_VALUE( WJetsScale );
  ed->property["scaleFactor_WJETSSHAPE"] = GET_VALUE( WJetsShapeScale );
  ed->property["scaleFactor_JVFSF"]      = GET_VALUE( JVFSFweight    );
  ed->property["scaleFactor_ZVERTEX"]    = GET_VALUE( ZVxpWeight   );
  ed->property["scaleFactor_KFactor"]    = GET_VALUE( KFactor  );

  return success;
}


/////////////////////////////////////////////


bool NtupleWrapperTopMini::MakeEventTrigger( EventData * ed )
{ 
  bool success = true;

// CHECK_TRIGGER( "EF_mu18i" );

  return success;
}


/////////////////////////////////////////////


bool NtupleWrapperTopMini::MakeEventMET( EventData * ed )
{
  bool success = true;

  ed->MET.et    = GET_VALUE( met_et );
  ed->MET.phi   = GET_VALUE( met_phi );
//  ed->MET.etx   = 0.;
//  ed->MET.ety   = 0.;
  ed->MET.sumet = GET_VALUE( met_sumet  );

  SET_PROPERTY( mwt );

  return success;
}


/////////////////////////////////////////////


bool NtupleWrapperTopMini::MakeEventElectrons( EventData * ed )
{
  bool success = true;

  ed->electrons.n = 1;
  ed->electrons.pT.push_back( GET_VALUE( lep_pt ) );
  ed->electrons.eta.push_back( GET_VALUE( lep_eta ) );
  ed->electrons.phi.push_back( GET_VALUE( lep_phi ) );
  ed->electrons.E.push_back( GET_VALUE( lep_E ) );
  ed->electrons.q.push_back( GET_VALUE( lep_charge ) );

  ed->electrons.property["charge"].push_back( GET_VALUE( lep_charge ) );
  //ed->electrons.property["trigMatch"].push_back( GET_VALUE( lep_trigMatch ) );

  //ed->electrons.property["tight"].push_back( GET_VALUE( tight ) );
  ed->electrons.property["el_cl_eta"].push_back( GET_VALUE( el_cl_eta ) );
  ed->electrons.property["eptcone30"].push_back( GET_VALUE( eptcone30 ) );
  ed->electrons.property["eetcone20"].push_back( GET_VALUE( eetcone20 ) );
  ed->electrons.property["eminiIso10_4"].push_back( GET_VALUE( m_eminiIso10_4 ) );

  return success;
}


/////////////////////////////////////////////


bool NtupleWrapperTopMini::MakeEventMuons( EventData * ed )
{
  bool success = true;

/*
   Float_t         mptcone30;
   Float_t         metcone20;
   Float_t         mminiIso10_4;
*/

  return success;
}


/////////////////////////////////////////////


bool NtupleWrapperTopMini::MakeEventJets( EventData * ed )
{
  bool success = true;


  ed->jets.n = GET_VALUE( jet_n );
  for( int i = 0 ; i < ed->jets.n ; ++i ) {

    ed->jets.index.push_back( i );

    ed->jets.pT.push_back(  m_ntuple->jet_pt[i]  );
    ed->jets.eta.push_back( m_ntuple->jet_eta[i] );
    ed->jets.phi.push_back( m_ntuple->jet_phi[i] );
    ed->jets.E.push_back(   m_ntuple->jet_E[i]   );

    ed->jets.property["jvf"].push_back(           GET_VALUE_ARRAY( jet_jvf, i           ) );
    ed->jets.property["trueflav"].push_back(      GET_VALUE_ARRAY( jet_trueflav, i      ) );
    ed->jets.property["truthMatched"].push_back(  GET_VALUE_ARRAY( jet_truthMatched, i  ) );
    ed->jets.property["SV0"].push_back(           GET_VALUE_ARRAY( jet_SV0, i           ) );
    ed->jets.property["COMBNN"].push_back(        GET_VALUE_ARRAY( jet_COMBNN, i        ) );
    ed->jets.property["MV1"].push_back(           GET_VALUE_ARRAY( jet_MV1, i           ) );
    ed->jets.property["MV1c"].push_back(          GET_VALUE_ARRAY( jet_MV1c, i          ) );
    ed->jets.property["isSemilep"].push_back(     GET_VALUE_ARRAY( jet_isSemilep, i     ) );
    // ed->jets.property["BadMediumBCH"].push_back(  GET_VALUE_ARRAY( jet_BadMediumBCH, i  ) );
    //ed->jets.property["BadTightBCH"].push_back(   GET_VALUE_ARRAY( jet_BadTightBCH, i   ) );
    //ed->jets.property["emfrac"].push_back(        GET_VALUE_ARRAY( jet_emfrac, i        ) );
    // ed->jets.property["BCH_CORR_CELL"].push_back( GET_VALUE_ARRAY( jet_BCH_CORR_CELL, i ) );
  }

  // not needed at the moment.
  /*
  ed->fjets.n = GET_VALUE( fjet_n );
  for( int i = 0 ; i < ed->fjets.n ; ++i ) {
    ed->fjets.index.push_back( i );

    ed->fjets.pT.push_back(  m_ntuple->fjet_pt[i]  );
    ed->fjets.eta.push_back( m_ntuple->fjet_eta[i] );
    ed->fjets.phi.push_back( m_ntuple->fjet_phi[i] );
    ed->fjets.E.push_back(   m_ntuple->fjet_E[i]   );
    ed->fjets.m.push_back(   m_ntuple->fjet_m[i]   );

    ed->fjets.d12.push_back( m_ntuple->fjet_d12[i] );
    ed->fjets.dPhi_lj.push_back( m_ntuple->fjet_DeltaPhi_Lap_FatJet[i] );
    ed->fjets.dR_lj.push_back( m_ntuple->fjet_DeltaR_LapJet_Fatjet[i] );
  }
  */

  return success;
}


/////////////////////////////////////////////


bool NtupleWrapperTopMini::MakeEventTruth( EventData * ed )
{
  bool success = true;

  TLorentzVector dressed_lepton;
  TLorentzVector etmiss;

  int isMCSignal = (int)m_config->custom_params["isMCSignal"];  
  if( !isMCSignal ) return success;

  for( int i = 0 ; i < m_ntuple->mc_n ; ++i ) {
    const int barcode = m_ntuple->mc_barcode->at(i);
    const int pid     = m_ntuple->mc_pdgId->at(i);
    const int apid    = abs(pid);
    const int status  = m_ntuple->mc_status->at(i);
    const double q    = ( pid >= 0 ) ? 1 : -1;

    if( apid == 6 ) {
/*
      printf( "INFO: branch mc_pt %i for event %i\n", m_ntuple->mc_pt, m_ntuple->eventNumber );
      if( !m_ntuple->mc_pt ) {
          printf( "ERROR: branch mc_pt %i for event %i\n", m_ntuple->mc_pt, m_ntuple->eventNumber );
          TChain * ch = (TChain*)m_ntuple->fChain;
          printf( "ERROR: file name: %s\n", ch->GetFile()->GetName() );
          throw runtime_error( "mc pt not allocated\n" );
      }
*/
      const double t_pT  = m_ntuple->mc_pt->at(i);
      const double t_eta = m_ntuple->mc_eta->at(i);
      const double t_phi = m_ntuple->mc_phi->at(i);
      const double t_m   = m_ntuple->mc_m->at(i);
      const double t_pz  = t_pT * sinh( t_eta ); 
      const double t_E   = sqrt( t_pT*t_pT + t_pz*t_pz + t_m*t_m );

      assert( t_pT > 0 );
      
      TLorentzVector tquark;
      tquark.SetPtEtaPhiM( t_pT, t_eta, t_phi, t_m );
      HelperFunctions::DumpTruthParticleToEventData( tquark, pid, status, barcode, q, &ed->mctruth );
      
      const PhysicsHelperFunctions::TOP_QUARK_DECAY_CLASS topdecay = 
	PhysicsHelperFunctions::ClassifyTopDecay( i, m_ntuple->mc_child_index, m_ntuple->mc_pdgId );
      const bool isHadronic = ( topdecay == PhysicsHelperFunctions::kTopDecayHadronic );
      ed->mctruth.property["isHadronic"].push_back( isHadronic );
      //printf( "DEBUG: event %i: parton %i pid=%i pT=%4.1f isHad=%i\n", 
      // ed->info.eventNumber, i, pid, t_pT, isHadronic );
    }
    else if( ( apid == 11 ) || ( apid == 13 ) ) {
      // dressed FS leptons
      if( status != 1 ) continue;
      
      if( PhysicsHelperFunctions::IsFromHadronicDecay( i, &m_ntuple->mc_parent_index->at(i), m_ntuple->mc_pdgId ) ) continue;

      TLorentzVector naked_lepton;
      naked_lepton.SetPtEtaPhiM( 
				  m_ntuple->mc_pt->at(i),
				  m_ntuple->mc_eta->at(i),
				  m_ntuple->mc_phi->at(i),
				  m_ntuple->mc_m->at(i)
			   );

      // now dress the lepton with a cone of fixed aperture 0.1
      dressed_lepton = PhysicsHelperFunctions::MakeDressedLepton( naked_lepton, 0.1, m_ntuple->mc_n, 
							    m_ntuple->mc_pdgId, m_ntuple->mc_status, m_ntuple->mc_parent_index,
							    m_ntuple->mc_pt, m_ntuple->mc_eta, m_ntuple->mc_phi, m_ntuple->mc_m );

      ed->truth_lepton.pT  = dressed_lepton.Pt();
      ed->truth_lepton.eta = dressed_lepton.Eta();
      ed->truth_lepton.phi = dressed_lepton.Phi();
      ed->truth_lepton.E   = dressed_lepton.E();
      ed->truth_lepton.m   = dressed_lepton.M();
      ed->truth_lepton.q   = ( pid >= 0 ) ? -1 : 1;
      ed->truth_lepton.pdgId = pid;

      if( apid == 11 ) {
	HelperFunctions::DumpTruthParticleToEventData( dressed_lepton, pid, status, barcode, q, &ed->truth_electrons );
      }
      else if( apid == 13 ) {
	HelperFunctions::DumpTruthParticleToEventData( dressed_lepton, pid, status, barcode, q, &ed->truth_muons );
      }
      else if( apid == 15 ) {
	HelperFunctions::DumpTruthParticleToEventData( dressed_lepton, pid, status, barcode, q, &ed->truth_taus );
      }
    }
    else if( ( apid == 12 ) || ( apid == 14 ) || ( apid == 16 ) ) {
      if( status != 1 ) continue;
      if( barcode > 20 ) continue;
      
      TLorentzVector neutrino;
      neutrino.SetPtEtaPhiM(
			    m_ntuple->mc_pt->at(i),
			    m_ntuple->mc_eta->at(i),
			    m_ntuple->mc_phi->at(i),
			    0.
			    );

      etmiss += neutrino;

      /*
      ed->MET_truth.et  = neutrino.Pt();
      ed->MET_truth.etx = neutrino.Px();
      ed->MET_truth.ety = neutrino.Py();
      ed->MET_truth.phi = neutrino.Phi();
      ed->MET_truth.etz = neutrino.Pz();
      ed->MET_truth.sumet = -1.;
      */
    }
  }


  // truth M_T^W
  //TLorentzVector Wlep = neutrino + dressed_lepton;
  const double dPhi_lv = dressed_lepton.DeltaPhi( etmiss );
  ed->MET_truth.mwt = sqrt( 2. * etmiss.Pt() * dressed_lepton.Pt() * ( 1. - cos( dPhi_lv ) ) );
 
  // truth jets (narrow)
  ed->truth_jets.n = GET_VALUE( mc_jet_AntiKt4Truth_n );
  for( int i = 0 ; i < ed->truth_jets.n ; ++i ) {

    const double jet_pt  = m_ntuple->mc_jet_AntiKt4Truth_pt->at(i);
    const double jet_eta = m_ntuple->mc_jet_AntiKt4Truth_eta->at(i);
    const double jet_phi = m_ntuple->mc_jet_AntiKt4Truth_phi->at(i);
    const double jet_E   = m_ntuple->mc_jet_AntiKt4Truth_E->at(i);
    const double jet_m   = m_ntuple->mc_jet_AntiKt4Truth_m->at(i);

    ed->truth_jets.index.push_back( i );
    ed->truth_jets.pT.push_back(  jet_pt );
    ed->truth_jets.eta.push_back( jet_eta );
    ed->truth_jets.phi.push_back( jet_phi );
    ed->truth_jets.E.push_back(   jet_E );
    ed->truth_jets.m.push_back(   jet_m );

    const JetTag tag = (JetTag)m_ntuple->mc_jet_AntiKt4Truth_flavor_truth_trueflav->at(i);
    ed->truth_jets.tag.push_back( tag  );

    ed->truth_bjets.n = 0;
    if( tag == kBTagged ) {
      ed->truth_bjets.n += 1;
      ed->truth_bjets.index.push_back( i );
      ed->truth_bjets.pT.push_back(  jet_pt );
      ed->truth_bjets.eta.push_back( jet_eta );
      ed->truth_bjets.phi.push_back( jet_phi );
      ed->truth_bjets.E.push_back(   jet_E );
      ed->truth_bjets.m.push_back(   jet_m );
      ed->truth_bjets.tag.push_back( tag  );
    }
  }

  // not needed now
  /*
  ed->truth_fjets.n = GET_VALUE( mc_jet_AntiKt10Truth_n );
  for( int i = 0 ; i < ed->truth_fjets.n ; ++i ) {

    ed->truth_fjets.index.push_back( i );

    ed->truth_fjets.pT.push_back(  m_ntuple->mc_jet_AntiKt10Truth_pt->at(i)  );
    ed->truth_fjets.eta.push_back( m_ntuple->mc_jet_AntiKt10Truth_eta->at(i) );
    ed->truth_fjets.phi.push_back( m_ntuple->mc_jet_AntiKt10Truth_phi->at(i) );
    ed->truth_fjets.E.push_back(   m_ntuple->mc_jet_AntiKt10Truth_E->at(i)   );
    ed->truth_fjets.m.push_back(   m_ntuple->mc_jet_AntiKt10Truth_m->at(i)   );
  }
  */

  // overlap removal
  for( int i = 0 ; i < ed->truth_jets.n ; ++i ) {
    // If dR(el,jet) < 0.4 skip the event

    // If dR(mu,jet) < 0.4 skip the event

    // If dR(jet,jet) < 0.5 skip the event
  }

  return success;
}


/////////////////////////////////////////
// Plugin

extern "C" {
  NtupleWrapperPluginFactory_TopMini * MakeNtupleWrapperPlugin() {
    return new NtupleWrapperPluginFactory_TopMini( "TopMini" );
  };
}
