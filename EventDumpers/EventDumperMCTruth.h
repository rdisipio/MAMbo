#ifndef __EVENTDUMPER_MCTRUTH_H__
#define __EVENTDUMPER_MCTRUTH_H__

#include "IEventDumper.h"

template< class NTUPLE >
class EventDumperMCTruth : public IEventDumper<NTUPLE>
{
 public:
    EventDumperMCTruth() {};
    virtual ~EventDumperMCTruth() {};

 public: 
    virtual bool DumpEventInfo( EventData * ed ) {};
    virtual bool DumpEventTrigger( EventData * ed ) {};
    virtual bool DumpEventMET( EventData * ed ) {};
    virtual bool DumpEventLeptons( EventData * ed ) {};
    virtual bool DumpEventJets( EventData * ed ) {};
 
    virtual bool DumpEventMCTruth( EventData * ed ) 
    { 
  bool success = true;

  TLorentzVector etmiss;
  TLorentzVector top, antitop, thad, tlep, ttbar;

  int isMCSignal = (int)( this->m_config.custom_params["isMCSignal"] );
  if( !isMCSignal ) return success;

  int ntops = 0;

  for( int i = 0 ; i < this->m_ntuple->mc_n ; ++i ) {
    const int barcode = this->m_ntuple->mc_barcode->at(i);
    const int pid     = this->m_ntuple->mc_pdgId->at(i);
    const int apid    = abs(pid);
    const int status  = this->m_ntuple->mc_status->at(i);
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
      const double t_pT  = this->m_ntuple->mc_pt->at(i);
      const double t_eta = this->m_ntuple->mc_eta->at(i);
      const double t_phi = this->m_ntuple->mc_phi->at(i);
      const double t_m   = this->m_ntuple->mc_m->at(i);
      const double t_pz  = t_pT * sinh( t_eta );
      const double t_E   = sqrt( t_pT*t_pT + t_pz*t_pz + t_m*t_m );

      //assert( t_pT > 0 );

      TLorentzVector tquark;
      tquark.SetPtEtaPhiM( t_pT, t_eta, t_phi, t_m );
      HelperFunctions::DumpTruthParticleToEventData( tquark, pid, status, barcode, q, &ed->mctruth );

      const PhysicsHelperFunctions::TOP_QUARK_DECAY_CLASS topdecay =
        PhysicsHelperFunctions::ClassifyTopDecay( i, this->m_ntuple->mc_child_index, this->m_ntuple->mc_pdgId );
      const bool isHadronic = ( topdecay == PhysicsHelperFunctions::kTopDecayHadronic );
      ed->mctruth.property["isHadronic"].push_back( isHadronic );

      //printf( "DEBUG: event %i: parton %i pid=%i pT=%4.1f isHad=%i\n", 
       //         ed->info.eventNumber, i, pid, t_pT, isHadronic );

      if( isHadronic ) thad = tquark;
      else tlep = tquark;

      if( q > 0 ) top = tquark;
      else antitop = tquark;
      ntops++;
    }
    else if( ( apid == 11 ) || ( apid == 13 ) ) {
      // dressed FS leptons

      TLorentzVector dressed_lepton;

      if( status != 1 ) continue;

      if( PhysicsHelperFunctions::IsFromHadronicDecay( i, &this->m_ntuple->mc_parent_index->at(i), this->m_ntuple->mc_pdgId ) ) continue;

      TLorentzVector naked_lepton;
      naked_lepton.SetPtEtaPhiM(
                                  this->m_ntuple->mc_pt->at(i),
                                  this->m_ntuple->mc_eta->at(i),
                                  this->m_ntuple->mc_phi->at(i),
                                  this->m_ntuple->mc_m->at(i)
                           );

      // now dress the lepton with a cone of fixed aperture 0.1
      dressed_lepton = PhysicsHelperFunctions::MakeDressedLepton( naked_lepton, 0.1, this->m_ntuple->mc_n,
                                                            this->m_ntuple->mc_pdgId, this->m_ntuple->mc_status, this->m_ntuple->mc_parent_index,
                                                            this->m_ntuple->mc_pt, this->m_ntuple->mc_eta, this->m_ntuple->mc_phi, this->m_ntuple->mc_m );

      HelperFunctions::DumpTruthParticleToEventData( dressed_lepton, pid, status, barcode, q, &ed->truth_leptons );

      if( apid == 11 ) {
        HelperFunctions::DumpTruthParticleToEventData( dressed_lepton, pid, status, barcode, q, &ed->truth_electrons );
      }
      else if( apid == 13 ) {
        HelperFunctions::DumpTruthParticleToEventData( dressed_lepton, pid, status, barcode, q, &ed->truth_muons );
      }
    }
    else if( ( apid == 12 ) || ( apid == 14 ) || ( apid == 16 ) ) {
      if( status != 1 ) continue;
      //if( barcode > 20 ) continue;

      TLorentzVector neutrino;
      neutrino.SetPtEtaPhiM(
                            this->m_ntuple->mc_pt->at(i),
                            this->m_ntuple->mc_eta->at(i),
                            this->m_ntuple->mc_phi->at(i),
                            0.
                            );

      etmiss += neutrino;
    }
  } // end loop over MC particles
  
  if( ntops >= 2 ) {
    // Create ttbar object and dump it
    ttbar = top + antitop;
    HelperFunctions::DumpTruthParticleToEventData( ttbar, 166, 2, 0, 0.0, &ed->mctruth );
    ed->mctruth.property["isHadronic"].push_back( 3 ); // 0x11
  }
  else {
      cout << "WARNING: no top quarks found in event " << ed->info.eventNumber << endl;
  }
  
  //assert( etmiss.Pt() > 0 );
  ed->MET_truth.et  = etmiss.Pt();
  ed->MET_truth.etx = etmiss.Px();
  ed->MET_truth.ety = etmiss.Py();
  ed->MET_truth.etz = etmiss.Pz();
  ed->MET_truth.phi = etmiss.Phi();

  TLorentzVector dressed_lepton;
  bool           dressed_lepton_found = false;
  if( this->m_config.channel == kElectron ) {
     if( ed->truth_electrons.n > 0 ) {
       dressed_lepton = HelperFunctions::MakeFourMomentum( ed->truth_electrons, 0 );
       dressed_lepton_found = true;
     }
  }
  else if( this->m_config.channel == kMuon ) {
     if( ed->truth_muons.n > 0 ) {
        dressed_lepton = HelperFunctions::MakeFourMomentum( ed->truth_muons, 0 );
        dressed_lepton_found = true;
     }
  }
  else throw runtime_error( "TopMini wrapper: MakeEventTruth(): invalid lepton channel, cannot choose a dressed lepton" );

  // if there is at least one dressed lepton we can build mTW
  if( dressed_lepton_found ) {
     assert( dressed_lepton.Pt() > 0. );

     ed->truth_lepton.pT  = dressed_lepton.Pt();
     ed->truth_lepton.eta = dressed_lepton.Eta();
     ed->truth_lepton.phi = dressed_lepton.Phi();
     ed->truth_lepton.E   = dressed_lepton.E();
     ed->truth_lepton.m   = dressed_lepton.M();
//  ed->truth_lepton.q   = ( pid >= 0 ) ? -1 : 1;
//  ed->truth_lepton.pdgId = pid;

     // truth M_T^W
     const double dPhi_lv = dressed_lepton.DeltaPhi( etmiss );
     ed->MET_truth.mwt = sqrt( 2. * etmiss.Pt() * dressed_lepton.Pt() * ( 1. - cos( dPhi_lv ) ) );
     //cout << "DEBUG: ETmiss = " << ed->MET_truth.et / GeV << " GeV ; mtw = " << ed->MET_truth.mwt / 1000. << " GeV ; lep_pT = " << dressed_lepton.Pt() /GeV << endl;
  }

  // truth jets (narrow)
  ed->truth_jets.n  = 0;
  ed->truth_bjets.n = 0;
  const int alljets_n = this->m_ntuple->mc_jet_AntiKt4Truth_n;
  int goodj_i = 0;
  int goodbj_i = 0;
  for( int i = 0 ; i < alljets_n ; ++i ) {

    const double jet_pt  = this->m_ntuple->mc_jet_AntiKt4Truth_pt->at(i);
    const double jet_eta = this->m_ntuple->mc_jet_AntiKt4Truth_eta->at(i);
    const double jet_phi = this->m_ntuple->mc_jet_AntiKt4Truth_phi->at(i);
    const double jet_E   = this->m_ntuple->mc_jet_AntiKt4Truth_E->at(i);
    const double jet_m   = this->m_ntuple->mc_jet_AntiKt4Truth_m->at(i);

    if( jet_pt < 25 * GeV ) continue;
    if( fabs(jet_eta) > 2.5 ) continue;

    ed->truth_jets.n += 1;

    ed->truth_jets.index.push_back( goodj_i );
    ed->truth_jets.pT.push_back(  jet_pt );
    ed->truth_jets.eta.push_back( jet_eta );
    ed->truth_jets.phi.push_back( jet_phi );
    ed->truth_jets.E.push_back(   jet_E );
    ed->truth_jets.m.push_back(   jet_m );

    goodj_i++;

    const JetTag tag = (JetTag)this->m_ntuple->mc_jet_AntiKt4Truth_flavor_truth_trueflav->at(i);
    ed->truth_jets.tag.push_back( tag  );

    if( tag == kBTagged ) {
      ed->truth_bjets.n += 1;
      ed->truth_bjets.index.push_back( goodbj_i );
      ed->truth_bjets.pT.push_back(  jet_pt );
      ed->truth_bjets.eta.push_back( jet_eta );
      ed->truth_bjets.phi.push_back( jet_phi );
      ed->truth_bjets.E.push_back(   jet_E );
      ed->truth_bjets.m.push_back(   jet_m );
      ed->truth_bjets.tag.push_back( tag  );

      goodbj_i++;
    }
  }

  bool mc_overlap = false;
  // overlap removal
  for( int i = 0 ; i < ed->truth_jets.n ; ++i ) {
      TLorentzVector jet = HelperFunctions::MakeFourMomentum( ed->truth_jets, i );

    // If dR(el,jet) < 0.4 skip the event
      for( int ie = 0 ; ie < ed->truth_electrons.n ; ++ie ) {
          TLorentzVector el = HelperFunctions::MakeFourMomentum( ed->truth_electrons, ie );
          if( jet.DeltaR(el) < 0.4 )  mc_overlap = true;
      }

    // If dR(mu,jet) < 0.4 skip the event
     for( int im = 0 ; im < ed->truth_muons.n ; ++im) {
          TLorentzVector mu = HelperFunctions::MakeFourMomentum( ed->truth_muons, im );
          if( jet.DeltaR(mu) < 0.4 )  mc_overlap = true;
      }

    // If dR(jet,jet) < 0.5 skip the event
      for( int ij = 0 ; ij < ed->truth_jets.n ; ++ij ) {
          if( ij == i ) continue;
          TLorentzVector j2 = HelperFunctions::MakeFourMomentum( ed->truth_jets, ij );

          if( jet.DeltaR( j2 ) < 0.5 ) mc_overlap = true;
      }
  }
  ed->property["mc_overlap"] = mc_overlap; 

  return success;
 

    }

 protected:

};


#endif /** __EVENTDUMPER_MCTRUTH_H__ */
