#ifndef __CF_TTbarResolved_H__
#define __CF_TTbarResolved_H__

#include "TRandom3.h"

#include "ICutFlow.h"

#include "PhysicsHelperFunctions.h"
#include "ControlPlotValues.h"
#include "EventData.h"
#include "Particle.h"

#ifdef __MOMA__
#include "MoMA/MoMA.h"
#endif 

using namespace PhysicsHelperFunctions;

class CutFlowTTbarResolved : public CutFlow
{
 public:
  CutFlowTTbarResolved();
  virtual ~CutFlowTTbarResolved();

  virtual bool Initialize();
  virtual bool Apply( EventData * ed );

 protected:
  bool PassedCutFlowReco(     EventData * ed );
  bool PassedCutFlowParticle( EventData * ed );

  double GetFakesWeight( EventData * ed );

  void FillHistogramsControlPlotsReco( ControlPlotValues& values );
  void FillHistogramsControlPlotsParticle( ControlPlotValues& values );
  
  void FillHistogramsPseudotopReco(      EventData * ed, const double weight = 1., string level = "reco" );
  void FillHistogramsPseudotopParticle(  EventData * ed, const double weight = 1., string level = "particle" );
  void FillHistogramsPseudotopParton(    EventData * ed, const double weight = 1. );
  
  void FillHistogramsPseudotopResponseRecoToParticle(    EventData * ed, const double weight = 1. );
  void FillHistogramsPseudotopResponseRecoToParton(      EventData * ed, const double weight = 1. );
  void FillHistogramsPseudotopResponseParticleToParton(  EventData * ed, const double weight = 1. );
  
  void FillHistogramsMatchingRecoToParticle(   double weight = 1. );   
  void FillHistogramsMatchingRecoToParton(     double weight = 1. ); 
  void FillHistogramsMatchingParticleToParton( double weight = 1. ); 
  
  void FillHistograms(string path, ControlPlotValues& values);
  void FillMatrix(string path, Particle& px, Particle& py, double weight);
  
  void FillHistogramsTopPairs(string path, TLorentzVector &topL, TLorentzVector &topH, TLorentzVector &ttSystem, double v_pz, double D, const double weight);

  void FillHistogramsPartonTop(EventData::Truth_t& particle, int index, string level, string topType, const double weight);
  void FillHistogramsPartonTopPairs(EventData::Truth_t& particle, int indexL, int indexH, int indextt, string level, const double weight);

  void FillHistogramsPseudoTop(EventData::Reco_t& particle, int index, string level, string topType, const double weight, const double mlb = -1);
  void FillHistogramsPseudoTopPairs(EventData::Reco_t& particle, int indexL, int indexH, int indextt, string level, double v_pz, double D, const double weight);


 protected:
    PseudoTopReconstruction * m_pseudotop_reco;
    PseudoTopReconstruction * m_pseudotop_particle;
    
    PseudoTopMatching       * m_pseudotop_matching_reco2particle;
    PseudoTopMatching       * m_pseudotop_matching_reco2parton;
    PseudoTopMatching       * m_pseudotop_matching_particle2parton;

#ifdef __MOMA__
    MoMATool                * m_moma;
    SYSTEMATIC_TYPE           m_syst_type;
#endif
    
private:

    vector<string> alias;
    TRandom3 *m_rand;    

};

typedef CutFlowPluginFactory< CutFlowTTbarResolved > CutFlowPluginFactory_TTbarResolved;

extern "C" {
  CutFlowPluginFactory_TTbarResolved * MakeCutFlowPlugin();
}

#endif /** __CF_TTbarResolved_H__ */
