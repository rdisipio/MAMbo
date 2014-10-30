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
 	m_ntuple_particle->fChain->BuildIndex( "eventNumber" );
    };
    
    void SetNtupleParton( NTUP_PARTON * ntuple ) {
        m_ntuple_parton = ntuple;
        m_ntuple_parton->fChain->BuildIndex( "eventNumber" );
    };


    ///////////////////////////////////////////////


    virtual bool DumpEventLeptons( EventData * ed )
    {
       const int el_n = this->m_ntuple_particle->part_el_n;
       for( int i = 0 ; i < el_n ; ++i ) {
         ed->truth_electrons.pT.push_back( this->m_ntuple_particle->part_el_pt[i] );
         ed->truth_electrons.eta.push_back( this->m_ntuple_particle->part_el_eta[i] );
         ed->truth_electrons.phi.push_back( this->m_ntuple_particle->part_el_phi[i] );
         ed->truth_electrons.E.push_back( this->m_ntuple_particle->part_el_E[i] );
         ed->truth_electrons.m.push_back( 0 );  
       }

       const int mu_n = this->m_ntuple_particle->part_mu_n;
       for( int i = 0 ; i < mu_n ; ++i ) {
         ed->truth_muons.pT.push_back( this->m_ntuple_particle->part_mu_pt[i] );
         ed->truth_muons.eta.push_back( this->m_ntuple_particle->part_mu_eta[i] );
         ed->truth_muons.phi.push_back( this->m_ntuple_particle->part_mu_phi[i] );
         ed->truth_muons.E.push_back( this->m_ntuple_particle->part_mu_E[i] );
         ed->truth_muons.m.push_back( 0 );
       }

    };


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
         ed->truth_jets.pT.push_back( this->m_ntuple_particle->part_jet_pt[i] );
         ed->truth_jets.eta.push_back( this->m_ntuple_particle->part_jet_eta[i] );
         ed->truth_jets.phi.push_back( this->m_ntuple_particle->part_jet_phi[i] );
         ed->truth_jets.E.push_back( this->m_ntuple_particle->part_jet_E[i] );
         ed->truth_jets.m.push_back( 0 );
       }
    };


    ///////////////////////////////////////////////


    virtual bool DumpEventMCTruth( EventData * ed )
    {
        return true;
    };
};

#endif /** __EVENTDUMPER_MCTRUTH_TOPMINISL_RESOLVED_H__ */
