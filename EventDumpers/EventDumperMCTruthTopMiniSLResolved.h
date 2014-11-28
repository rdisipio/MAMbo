#ifndef __EVENTDUMPER_MCTRUTH_TOPMINISL_RESOLVED_H__
#define __EVENTDUMPER_MCTRUTH_TOPMINISL_RESOLVED_H__

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
    void SetNtupleParticle( NTUP_PARTICLE * ntuple ) { 
        m_ntuple_particle = ntuple; 
	cout << "INFO: building index for particles chain..." << endl;
 	int res = m_ntuple_particle->fChain->BuildIndex( "runNumber", "eventNumber" );
	cout << "INFO: particles tree index: returned value: " << res << endl;
    };
    
    void SetNtupleParton( NTUP_PARTON * ntuple ) {
        m_ntuple_parton = ntuple;
 	cout << "INFO: building index for partons chain..." << endl;
        int res = m_ntuple_parton->fChain->BuildIndex( "runNumber", "eventNumber" );
	cout << "INFO: partons tree index: returned value: " << res << endl;
    };

    void GetEntryWithIndex( unsigned long major, unsigned long minor = 0 ) { 
        m_ntuple_particle->fChain->GetEntryWithIndex( major, minor );
        m_ntuple_parton->fChain->GetEntryWithIndex( major, minor );
    };

    ///////////////////////////////////////////////


    virtual bool DumpEventLeptons( EventData * ed )
    {
       const int el_n = this->m_ntuple_particle->part_el_n;
       for( int i = 0 ; i < el_n ; ++i ) {
	 TLorentzVector el;
	 el.SetPtEtaPhiE( this->m_ntuple_particle->part_el_pt[i],
			  this->m_ntuple_particle->part_el_eta[i],
			  this->m_ntuple_particle->part_el_phi[i],
			  this->m_ntuple_particle->part_el_E[i] );
	 HelperFunctions::DumpParticleToEventData( el, &ed->truth_electrons );
       }

       const int mu_n = this->m_ntuple_particle->part_mu_n;
       for( int i = 0 ; i < mu_n ; ++i ) {
         TLorentzVector	mu;
         mu.SetPtEtaPhiE( this->m_ntuple_particle->part_mu_pt[i],
                          this->m_ntuple_particle->part_mu_eta[i],
                          this->m_ntuple_particle->part_mu_phi[i],
                          this->m_ntuple_particle->part_mu_E[i]	);
         HelperFunctions::DumpParticleToEventData( mu, &ed->truth_muons );
       }
    };


    /////////////////////////////////////////////////////////////////////////


    virtual bool DumpEventMET( EventData * ed )   
    {
       TLorentzVector etmiss;
       for( int i = 0 ; i < this->m_ntuple_particle->part_nu_n ; ++i ) {
           TLorentzVector nu;
	   const double nu_pt  = this->m_ntuple_particle->part_nu_pt[i];
	   const double	nu_eta = this->m_ntuple_particle->part_nu_eta[i];
           const double nu_phi = this->m_ntuple_particle->part_nu_phi[i]; 
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


    virtual bool DumpEventJets( EventData * ed )
    {
       const int jet_n = this->m_ntuple_particle->part_jet_n;
       for( int i = 0 ; i < jet_n ; ++i ) {
//	 ed->truth_jets.n++;
         ed->truth_jets.index.push_back( i );

	 TLorentzVector jet;
	 jet.SetPtEtaPhiE( this->m_ntuple_particle->part_jet_pt[i],
			   this->m_ntuple_particle->part_jet_eta[i],
			   this->m_ntuple_particle->part_jet_phi[i],
			   this->m_ntuple_particle->part_jet_E[i] );
	 HelperFunctions::DumpParticleToEventData( jet, &ed->truth_jets );

	 const int flavor = this->m_ntuple_particle->part_jet_flavour_pdgId[i];
	 if( abs(flavor) == 5 ) { 
	    HelperFunctions::DumpParticleToEventData( jet, &ed->truth_bjets );
	    ed->truth_bjets.index.push_back( i );
         }
       }
    };


    ///////////////////////////////////////////////


    virtual bool DumpEventMCTruth( EventData * ed )
    {
       TLorentzVector t1, t2, ttbar;

       for( int i = 0 ; i < this->m_ntuple_parton->parton_topQuark_n ; ++i ) {
	  const double t_pT  = this->m_ntuple_parton->parton_topQuark_pt[i];
	  const double t_eta = this->m_ntuple_parton->parton_topQuark_eta[i];
	  const double t_phi = this->m_ntuple_parton->parton_topQuark_phi[i];
	  const double t_m   = this->m_ntuple_parton->parton_topQuark_m[i];

	  const int pid     = this->m_ntuple_parton->parton_topQuark_pdgId[i];
	  const int status  = this->m_ntuple_parton->parton_topQuark_status[i];
	  const int barcode = 0;
	  const float t_q   = ( pid >= 0 ) ? 1 : -1;

          TLorentzVector t;
	  t.SetPtEtaPhiM( t_pT, t_eta, t_phi, t_m );
	  HelperFunctions::DumpTruthParticleToEventData( t, pid, status, barcode, t_q, &ed->mctruth );	

	  bool isHadronic = false;
          if( this->m_ntuple_parton->parton_topQuark_isHadronic[i] ) {
		t1 = t;
          }
          else {
	        t2 = t;
          }
	  ed->mctruth.property["isHadronic"].push_back( isHadronic );

       }
       ttbar = t1 + t2;
       HelperFunctions::DumpTruthParticleToEventData( ttbar, 166, 2, 0, 0, &ed->mctruth );
    };
};

#endif /** __EVENTDUMPER_MCTRUTH_TOPMINISL_RESOLVED_H__ */
