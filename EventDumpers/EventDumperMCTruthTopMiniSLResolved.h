#ifndef __EVENTDUMPER_MCTRUTH_TOPMINISL_RESOLVED_H__
#define __EVENTDUMPER_MCTRUTH_TOPMINISL_RESOLVED_H__

#include "TTreeIndex.h"

template< class NTUP_PARTICLE, class NTUP_PARTON >
class EventDumperMCTruthTopMiniSLResolved
{
 public:
    EventDumperMCTruthTopMiniSLResolved() : m_ntuple_particle(NULL), m_ntuple_parton(NULL) {};
    virtual ~EventDumperMCTruthTopMiniSLResolved() {};

    inline void SetAnalysisParameters( AnalysisParams_t params ) { m_config = params; };

 protected:
    AnalysisParams_t   m_config;
    NTUP_PARTICLE    * m_ntuple_particle;
    NTUP_PARTON      * m_ntuple_parton;

 public: 
    void SetNtupleParticle( NTUP_PARTICLE * ntuple, bool buildIndex = true, std::string outIndexFileName = "index_particle.root" ) { 
        m_ntuple_particle = ntuple; 

        if( !buildIndex ) return ;

	cout << "INFO: building index for particles chain..." << endl;
        TTree * p_c = m_ntuple_particle->fChain;
        if( !p_c ) throw runtime_error( "EventDumperMCTruthTopMiniSLResolved::SetNtupleParticle(): Invalid pointer to particle chain.\n" );

 	int res = m_ntuple_particle->fChain->BuildIndex( "runNumber", "eventNumber" );
	cout << "INFO: particles tree index: returned value: " << res << endl;

	// TEST: Marino, JK:
	/*
	  TFile * test = TFile::Open( outIndexFileName.c_str(), "recreate" );
	  TTreeIndex *index = (TTreeIndex*) p_c->GetTreeIndex();
	  index->Write( "index" );
	  test->Write();
	  test->Close();
	*/
	
    };
    
    void SetNtupleParton( NTUP_PARTON * ntuple, bool buildIndex = true, std::string outIndexFileName = "index_parton.root" ) {
        m_ntuple_parton = ntuple;

        if( !buildIndex	) return ;

 	cout << "INFO: building index for partons chain..." << endl;
        int res = m_ntuple_parton->fChain->BuildIndex( "runNumber", "eventNumber" );
	cout << "INFO: partons tree index: returned value: " << res << endl;

	// TEST: Marino, JK:
	/*
	  TFile * test = TFile::Open( outIndexFileName.c_str(), "recreate" );
	  TTreeIndex *index = (TTreeIndex*) m_ntuple_parton->fChain->GetTreeIndex();
	  index->Write( "index" );
	  test->Write();
	  test->Close();
	*/
    };

    void GetEntryWithIndex( unsigned long major, unsigned long minor = 0 ) { 
        if( m_ntuple_particle ) m_ntuple_particle->fChain->GetEntryWithIndex( major, minor );
        if( m_ntuple_parton )   m_ntuple_parton->fChain->GetEntryWithIndex( major, minor );
    };


    ///////////////////////////////////////////////

    template< class T > 
    bool DumpEventLeptons( const T * ntuple, EventData * ed )
    {
       const int el_n = ntuple->part_el_n;
       for( int i = 0 ; i < el_n ; ++i ) {
	 TLorentzVector el;
	 el.SetPtEtaPhiE( ntuple->part_el_pt[i],
			  ntuple->part_el_eta[i],
			  ntuple->part_el_phi[i],
			  ntuple->part_el_E[i] );
	 HelperFunctions::DumpParticleToEventData( el, &ed->truth_electrons );
       }

       const int mu_n = ntuple->part_mu_n;
       for( int i = 0 ; i < mu_n ; ++i ) {
         TLorentzVector	mu;
         mu.SetPtEtaPhiE( ntuple->part_mu_pt[i],
                          ntuple->part_mu_eta[i],
                          ntuple->part_mu_phi[i],
                          ntuple->part_mu_E[i]	);
         HelperFunctions::DumpParticleToEventData( mu, &ed->truth_muons );
       }
    };


    /////////////////////////////////////////////////////////////////////////


    template< class T >
    bool DumpEventMET( const T * ntuple, EventData * ed )   
    {
       TLorentzVector etmiss;
       for( int i = 0 ; i < ntuple->part_nu_n ; ++i ) {
           TLorentzVector nu;
	   const double nu_pt  = ntuple->part_nu_pt[i];
	   const double	nu_eta = ntuple->part_nu_eta[i];
           const double nu_phi = ntuple->part_nu_phi[i]; 
	   nu.SetPtEtaPhiM( nu_pt, nu_eta, nu_phi, 0 );
           etmiss += nu;
       }
       ed->MET_truth.et  = etmiss.Pt();
       ed->MET_truth.etx = etmiss.Px();
       ed->MET_truth.ety = etmiss.Py();
       ed->MET_truth.etz = etmiss.Pz();
       ed->MET_truth.phi = etmiss.Phi();

       // assuming it is a single lepton, build mTW
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

       const double dPhi_lv = dressed_lepton.DeltaPhi( etmiss );
       ed->MET_truth.mwt = sqrt( 2. * etmiss.Pt() * dressed_lepton.Pt() * ( 1. - cos( dPhi_lv ) ) );
    };

 
    ///////////////////////////////////////////////


    template< class T >
    bool DumpEventJets( const T * ntuple, EventData * ed )
    {
       const int jet_n = ntuple->part_jet_n;
       for( int i = 0 ; i < jet_n ; ++i ) {
//	 ed->truth_jets.n++;
         ed->truth_jets.index.push_back( i );

	 TLorentzVector jet;
	 jet.SetPtEtaPhiE( ntuple->part_jet_pt[i],
			   ntuple->part_jet_eta[i],
			   ntuple->part_jet_phi[i],
			   ntuple->part_jet_E[i] );
	 HelperFunctions::DumpParticleToEventData( jet, &ed->truth_jets );

	 const int flavor = ntuple->part_jet_flavour_pdgId[i];
	 if( abs(flavor) == 5 ) { 
	    HelperFunctions::DumpParticleToEventData( jet, &ed->truth_bjets );
	    ed->truth_bjets.index.push_back( i );
         }
       }
    };


    ///////////////////////////////////////////////


    template< class T >
    bool DumpEventMCTruth( const T * ntuple_partons, EventData * ed )
    {
       int success = true;

       int isDileptonic = -1;
       int ntops = ntuple_partons->parton_topQuark_n;

       if( ntops < 2 ) {
          cout << "WARNING: event " << ntuple_partons->eventNumber << " has too few top quarks in the MC event record: " << ntops << endl;
          ed->property["isDileptonic"] = isDileptonic;
          return success;  
       }

  //     if( ntops > 2 ) cout << "WARNING: event " << ntuple_partons->eventNumber << " has too many top quarks in the MC event record: " << ntops << endl;

       int nthad = 0;
       TLorentzVector ttbar;

       for( int i = 0 ; i < ntops ; ++i ) {
	  const double t_pT  = ntuple_partons->parton_topQuark_pt[i];
	  const double t_eta = ntuple_partons->parton_topQuark_eta[i];
	  const double t_phi = ntuple_partons->parton_topQuark_phi[i];
	  const double t_m   = ntuple_partons->parton_topQuark_m[i];

	  const int pid     = ntuple_partons->parton_topQuark_pdgId[i];
	  const int status  = ntuple_partons->parton_topQuark_status[i];
	  const int barcode = 0;
	  const float t_q   = ( pid >= 0 ) ? 1 : -1;
	  const int isHadronic = ntuple_partons->parton_topQuark_isHadronic[i];

/* 
          if( ntops > 2 ) {
                cout << "DEBUG: event=" << ntuple_partons->eventNumber << " topq bc=" << barcode << " pid=" << pid 
                     << " status=" << status << " pT=" << t_pT/GeV << " eta=" << t_eta << " m=" << t_m/GeV << " isHad=" << isHadronic << endl;
          }
*/

          if( abs(pid) != 6 ) continue;

          TLorentzVector t;
	  t.SetPtEtaPhiM( t_pT, t_eta, t_phi, t_m );
	  HelperFunctions::DumpTruthParticleToEventData( t, pid, status, barcode, t_q, &ed->mctruth );	

	  ed->mctruth.property["isHadronic"].push_back( isHadronic );

          if( ntops > 2 ) {
//            if( status == 155 ) ttbar += t; // HERWIG
//            if( status == 3 )   ttbar += t; // PYTHIA
              if( ( status > 2 ) && ( isHadronic >= 0 ) ) ttbar += t;
          }
          else {
              ttbar += t;
          }

          if( isHadronic == 1 ) nthad++;
//          cout << "DEBUG: is hadronic: " << isHadronic << endl;
       }
       HelperFunctions::DumpTruthParticleToEventData( ttbar, 166, 2, 0, 0, &ed->mctruth );

       isDileptonic = ( nthad == 0 ) ? 1 : 0;
       ed->property["isDileptonic"] = isDileptonic;
//       cout << "DEBUG: isDileptonic: " << isDileptonic << endl;


// JK and now also W bosons:
       int nWs = ntuple_partons->parton_Wboson_n;

       if( nWs < 2 ) {
          cout << "WARNING: event " << ntuple_partons->eventNumber << " has too few Ws in the MC event record: " << nWs << endl;
          return success;  
       }

  //     if( nWs > 2 ) cout << "WARNING: event " << ntuple_partons->eventNumber << " has too many W in the MC event record: " << nWs << endl;

       int nWhad = 0;

       for( int i = 0 ; i < nWs ; ++i ) {
	  const double W_pT  = ntuple_partons->parton_Wboson_pt[i];
	  const double W_eta = ntuple_partons->parton_Wboson_eta[i];
	  const double W_phi = ntuple_partons->parton_Wboson_phi[i];
	  const double W_m   = ntuple_partons->parton_Wboson_m[i];

	  const int pid     = ntuple_partons->parton_Wboson_pdgId[i];
	  const int status  = ntuple_partons->parton_Wboson_status[i];
	  const int barcode = 0;
	  const float W_q   = ( pid >= 0 ) ? 1 : -1;
	  const int isHadronic = ntuple_partons->parton_Wboson_isHadronic[i];

/* 
          if( nWs > 2 ) {
                cout << "DEBUG: event=" << ntuple_partons->eventNumber << " W bc=" << barcode << " pid=" << pid 
                     << " status=" << status << " pT=" << W_pT/GeV << " eta=" << W_eta << " m=" << W_m/GeV << " isHad=" << isHadronic << endl;
          }
*/

          if( abs(pid) != 24 ) continue;

          TLorentzVector W;
	  W.SetPtEtaPhiM( W_pT, W_eta, W_phi, W_m );
	  HelperFunctions::DumpTruthParticleToEventData( W, pid, status, barcode, W_q, &ed->mctruth );	

	  ed->mctruth.property["isHadronicW"].push_back( isHadronic );

          if( isHadronic == 1 ) nWhad++;
//          cout << "DEBUG: is hadronicW: " << isHadronic << endl;
       }

       isDileptonic = ( nWhad == 0 ) ? 1 : 0;
       ed->property["isDileptonicW"] = isDileptonic;




       return success;
    };
};

#endif /** __EVENTDUMPER_MCTRUTH_TOPMINISL_RESOLVED_H__ */
