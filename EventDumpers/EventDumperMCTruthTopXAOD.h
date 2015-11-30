#ifndef __eVENTDUMPER_MCTRUTH_TOPXAOD_H__
#define __eVENTDUMPER_MCTRUTH_TOPXAOD_H__

#include "TTreeIndex.h"

template< class NTUP_PARTICLE, class NTUP_PARTON >
class EventDumperMCTruthTopXAOD
{
 public:
    EventDumperMCTruthTopXAOD() : m_ntuple_particle(NULL), m_ntuple_parton(NULL) {};
    virtual ~EventDumperMCTruthTopXAOD() {};

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
        if( !p_c ) throw runtime_error( "EventDumperMCTruthTopXAOD::SetNtupleParticle(): Invalid pointer to particle chain.\n" );

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
       const int el_n = ntuple->el_pt->size();
       for( int i = 0 ; i < el_n ; ++i ) {
	 TLorentzVector el;
	 el.SetPtEtaPhiE( ntuple->el_pt->at(i),
			  ntuple->el_eta->at(i),
			  ntuple->el_phi->at(i),
			  ntuple->el_e->at(i) );
	 HelperFunctions::DumpParticleToEventData( el, &ed->truth_electrons );
       }

       const int mu_n = ntuple->mu_pt->size();
       for( int i = 0 ; i < mu_n ; ++i ) {
         TLorentzVector	mu;
         mu.SetPtEtaPhiE( ntuple->mu_pt->at(i),
                          ntuple->mu_eta->at(i),
                          ntuple->mu_phi->at(i),
                          ntuple->mu_e->at(i)	);
         HelperFunctions::DumpParticleToEventData( mu, &ed->truth_muons );
       }
    };


    /////////////////////////////////////////////////////////////////////////


    template< class T >
    bool DumpEventMET( const T * ntuple, EventData * ed )   
    {
       TLorentzVector etmiss;
       etmiss.SetPtEtaPhiM( ntuple->met_met, 0, ntuple->met_phi, 0 );
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
        const int jet_n = ntuple->jet_pt->size();
	int jindex = 0;
	ed->truth_jets.n = 0;
	ed->truth_bjets.n = 0;
        for( int i = 0 ; i < jet_n ; ++i ) 
        {
   	     if( ntuple->jet_pt->at(i) < 25 * GeV ) continue;
   	     if( fabs(ntuple->jet_eta->at(i)) > 2.5 ) continue;
	     /* cout << "ed->truth_jets.n " << ed->truth_jets.n << endl; */
	     TLorentzVector jet;
	     jet.SetPtEtaPhiE( ntuple->jet_pt->at(i),
	     ntuple->jet_eta->at(i),
	     ntuple->jet_phi->at(i),
	     ntuple->jet_e->at(i) );
	     HelperFunctions::DumpParticleToEventData( jet, &ed->truth_jets );
	     /* cout << "ed->truth_jets.pT.size() " << ed->truth_jets.pT.size() << endl; */
	     ed->truth_jets.index.push_back( jindex );
	   
	     const int nBhadrons = ntuple->jet_nGhosts_bHadron->at(i);
	     if( nBhadrons > 0 ) 
	     { 
	    	HelperFunctions::DumpParticleToEventData( jet, &ed->truth_bjets );
	    	ed->truth_bjets.index.push_back( jindex );
	     }
	     jindex++;
        }
	if( ed->truth_jets.n != ed->truth_jets.index.size() )
	{
		cout << "Error: ed->truth_jets.n is " << ed->truth_jets.n << ", while ed->truth_jets.index.size() is " << ed->truth_jets.index.size() << endl;
	}

	const int fjet_n = ntuple->ljet_pt->size();
	jindex = 0;
        for( int i = 0 ; i < fjet_n ; ++i ) 
        {

        	ed->truth_fjets.index.push_back( jindex );

		TLorentzVector jet;
		jet.SetPtEtaPhiE( ntuple->ljet_pt->at(i),
			   ntuple->ljet_eta->at(i),
			   ntuple->ljet_phi->at(i),
			   ntuple->ljet_e->at(i) );
		HelperFunctions::DumpParticleToEventData( jet, &ed->truth_fjets );
		jindex++;

		////--Tagging and substructures properties of the Large-R jet--/////
		const double sd12 = ntuple->ljet_sd12->at(i);
		ed->truth_fjets.property["sd12"].push_back( sd12 );
		
		const double tau32 = ntuple->ljet_tau32->at(i);
		ed->truth_fjets.property["tau32"].push_back( tau32 );
		
		const double tau21 = ntuple->ljet_tau21->at(i);
		ed->truth_fjets.property["tau21"].push_back( tau21 );
		
		const int topTag50 = ntuple->ljet_topTag50->at(i);
		ed->truth_fjets.property["topTag50"].push_back(topTag50 );
		
		const int topTag80 = ntuple->ljet_topTag80->at(i);
		ed->truth_fjets.property["topTag80"].push_back(topTag80);
		
		
		/*	 const int nBhadrons = ntuple->ljet_nGhosts_bHadron->at(i);
	 if( nBhadrons > 0 ) { 
	    HelperFunctions::DumpParticleToEventData( jet, &ed->truth_bjets );
	    ed->truth_bjets.index.push_back( i );
         }*/
       }


    };


    ///////////////////////////////////////////////


    template< class T >
    bool DumpEventMCTruth( const T * ntuple_partons, EventData * ed )
    {
       int success = true;

       int isDileptonic = -1;
       int ntops = 2;

       if( ntops < 2 ) {
          cout << "WARNING: event " << ntuple_partons->eventNumber << " has too few top quarks in the MC event record: " << ntops << endl;
          ed->property["isDileptonic"] = isDileptonic;
          return success;  
       }

  //     if( ntops > 2 ) cout << "WARNING: event " << ntuple_partons->eventNumber << " has too many top quarks in the MC event record: " << ntops << endl;

       int nthad = 0;
       TLorentzVector ttbar, t, tbar;
       int n_good_tops = 0;

	double t_pt = ntuple_partons->MC_t_beforeFSR_pt;
	double t_eta = ntuple_partons->MC_t_beforeFSR_eta;
	double t_phi = ntuple_partons->MC_t_beforeFSR_phi;
	double t_m = ntuple_partons->MC_t_beforeFSR_m;
	float t_q = 1;
	int t_isHadronic = fabs( ntuple_partons->MC_Wdecay2_from_t_pdgId ) < 6 ? true : false; //if one decay product of the W is a quark, the other decay product has to be a quark
  	n_good_tops++;
	t.SetPtEtaPhiM( t_pt, t_eta, t_phi, t_m );
	HelperFunctions::DumpTruthParticleToEventData( t, 6, 2, 0, t_q, &ed->mctruth );
	ed->mctruth.property["isHadronic"].push_back( t_isHadronic );

	double tbar_pt = ntuple_partons->MC_tbar_beforeFSR_pt;
	double tbar_eta = ntuple_partons->MC_tbar_beforeFSR_eta;
	double tbar_phi = ntuple_partons->MC_tbar_beforeFSR_phi;
	double tbar_m = ntuple_partons->MC_tbar_beforeFSR_m;
	float tbar_q = -1;
	int tbar_isHadronic = fabs( ntuple_partons->MC_Wdecay2_from_tbar_pdgId ) < 6 ? true : false; //if one decay product of the W is a quark, the other decay product has to be a quark
  	n_good_tops++;
	tbar.SetPtEtaPhiM( tbar_pt, tbar_eta, tbar_phi, tbar_m );
	HelperFunctions::DumpTruthParticleToEventData( t, -6, 2, 0, tbar_q, &ed->mctruth );
	ed->mctruth.property["isHadronic"].push_back( tbar_isHadronic );


       ttbar = t + tbar;
/*
       if( ntops > 2 ) {
         cout << "DEBUG: top     pT=" << top.Pt()/GeV << " eta=" << top.Eta() << " m=" << top.M()/GeV << endl;
         cout << "DEBUG: antitop pT=" << antitop.Pt()/GeV << " eta=" << antitop.Eta() << " m=" << antitop.M()/GeV << endl;
         cout << "DEBUG: ttbar   pT=" << ttbar.Pt()/GeV << " eta=" << ttbar.Eta() << " m=" << ttbar.M()/GeV << endl;
       }
*/
       if( t.Pt() <= 0. ) {
           cout << "ERROR: event " << ntuple_partons->eventNumber << " could not find a good t " << endl;
       }
       if( t.Pt() <= 0. ) {
           cout << "ERROR: event " << ntuple_partons->eventNumber << " could not find a good tbar." << endl;
       }

       if( ttbar.M() < 225*GeV ) cout << "WARNING: EventDumperMCTruthTopXAOD: event " << ntuple_partons->eventNumber << " low ttbar m = " << ttbar.M()/GeV << " pT = " << ttbar.Pt()/GeV << endl;

       HelperFunctions::DumpTruthParticleToEventData( ttbar, 166, 2, 0, 0, &ed->mctruth );

       nthad = t_isHadronic + tbar_isHadronic;
       isDileptonic = ( nthad == 0 ) ? 1 : 0;
       ed->property["isDileptonic"] = isDileptonic;

       /* cout << "DEBUG: isDileptonic: " << isDileptonic << endl; */


// JK and now also W bosons:
       int nWs = 2;

       if( nWs < 2 ) {
          cout << "WARNING: event " << ntuple_partons->eventNumber << " has too few Ws in the MC event record: " << nWs << endl;
          return success;  
       }

  //     if( nWs > 2 ) cout << "WARNING: event " << ntuple_partons->eventNumber << " has too many W in the MC event record: " << nWs << endl;
	int nWhad = 0;
	double W_from_t_pt = ntuple_partons->MC_W_from_t_pt;
	double W_from_t_eta = ntuple_partons->MC_W_from_t_eta;
	double W_from_t_phi = ntuple_partons->MC_W_from_t_phi;
	double W_from_t_m = ntuple_partons->MC_W_from_t_m;
	float W_from_t_q = 1;
	int W_from_t_isHadronic = fabs( ntuple_partons->MC_Wdecay2_from_t_pdgId ) < 6 ? true : false; //if one decay product of the W is a quark, the other decay product has to be a quark
        TLorentzVector W;
	W.SetPtEtaPhiM( W_from_t_pt, W_from_t_eta, W_from_t_phi, W_from_t_m );
	HelperFunctions::DumpTruthParticleToEventData( W, 24, 2, 0, W_from_t_q, &ed->mctruth );	
        ed->mctruth.property["isHadronicW"].push_back( W_from_t_isHadronic );
        if( W_from_t_isHadronic == 1 ) nWhad++;

	double W_from_tbar_pt = ntuple_partons->MC_W_from_tbar_pt;
	double W_from_tbar_eta = ntuple_partons->MC_W_from_tbar_eta;
	double W_from_tbar_phi = ntuple_partons->MC_W_from_tbar_phi;
	double W_from_tbar_m = ntuple_partons->MC_W_from_tbar_m;
	float W_from_tbar_q = -1;
	int W_from_tbar_isHadronic = fabs( ntuple_partons->MC_Wdecay2_from_tbar_pdgId ) < 6 ? true : false; //if one decay product of the W is a quark, the other decay product has to be a quark
	W.SetPtEtaPhiM( W_from_tbar_pt, W_from_tbar_eta, W_from_tbar_phi, W_from_tbar_m );
	HelperFunctions::DumpTruthParticleToEventData( W, -24, 2, 0, W_from_tbar_q, &ed->mctruth );	
        ed->mctruth.property["isHadronicW"].push_back( W_from_tbar_isHadronic );
        if( W_from_tbar_isHadronic == 1 ) nWhad++;


//          cout << "DEBUG: is hadronicW: " << isHadronic << endl;
       

       isDileptonic = ( nWhad == 0 ) ? 1 : 0;
       ed->property["isDileptonicW"] = isDileptonic;


  ed->property["passed_particle_resolved_ejets_4j2b" ] = ntuple_particle-> passed_resolved_ejets_4j2b;
  ed->property["passed_particle_resolved_mujets_4j2b" ] = ntuple_particle-> passed_resolved_mujets_4j2b;
  ed->property["passed_particle_boosted_ejets_1fj0b" ] = ntuple_particle-> passed_boosted_ejets_1fj0b;  
  ed->property["passed_particle_boosted_mujets_1fj0b" ] = ntuple_particle-> passed_boosted_mujets_1fj0b;

       return success;
    };
};

#endif /** __eVENTDUMPER_MCTRUTH_TOPMINISL_RESOLVED_H__ */
