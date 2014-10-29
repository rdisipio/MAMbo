#ifndef __EVENTDUMPER_MCTRUTH_TOPMINISL_RESOLVED_H__
#define __EVENTDUMPER_MCTRUTH_TOPMINISL_RESOLVED_H__

template< class NTUP_PARTICLE, class NTUP_PARTON >
class EventDumperMCTruthTopMiniSLResolved
{
 public:
    EventDumperMCTruthTopMiniSLResolved() : m_ntuple_particle(NULL), m_ntuple_parton(NULL) {};
    virtual ~EventDumperMCTruthTopMiniSLResolved() {};

 protected:
    NTUP_PARTICLE * m_ntuple_particle;
    NTUP_PARTON   * m_ntuple_parton;

 public: 
    void SetNtupleParticle( NTUPL_PARTICLE * ntuple ) { 
        m_ntuple_particle = ntuple; 
 	m_ntuple_particle->BuildIndex( "eventNumber" );
    };
    
    void SetNtupleParton( NTUPL_PARTON * ntuple ) {
        m_ntuple_parton = ntuple;
        m_ntuple_parton->BuildIndex( "eventNumber" );
    };


    ///////////////////////////////////////////////


    virtual bool DumpEventLeptons( EventData * ed )
    {

    };

 
    ///////////////////////////////////////////////


    virtual bool DumpEventJets( EventData * ed ) {};
    {

    };


    ///////////////////////////////////////////////


    virtual bool DumpeEventMCTruth( EventData * ed )
};

#endif /** __EVENTDUMPER_MCTRUTH_TOPMINISL_RESOLVED_H__ */
