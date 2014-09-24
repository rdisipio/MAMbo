#ifndef __CF_TTbarResolved_H__
#define __CF_TTbarResolved_H__

#include "ICutFlow.h"

#include "PhysicsHelperFunctions.h"

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

  void FillHistogramsControlPlotsReco( EventData * ed, const double weight = 1. );
  void FillHistogramsControlPlotsParticle( EventData * ed, const double weight = 1. );
  
  void FillHistogramsPseudotopReco(      EventData * ed, const double weight = 1. );
  void FillHistogramsPseudotopParticle(  EventData * ed, const double weight = 1. );
  void FillHistogramsPseudotopParton(    EventData * ed, const double weight = 1. );
  
  void FillHistogramsPseudotopResponseRecoToParticle(    EventData * ed, const double weight = 1. );
  void FillHistogramsPseudotopResponseRecoToParton(      EventData * ed, const double weight = 1. );
  void FillHistogramsPseudotopResponseParticleToParton(  EventData * ed, const double weight = 1. );
  
  void FillHistogramsMatchingRecoToParticle(   double weight = 1. );   
  void FillHistogramsMatchingRecoToParton(     double weight = 1. ); 
  void FillHistogramsMatchingParticleToParton( double weight = 1. ); 
  
 protected:
    PseudoTopReconstruction * m_pseudotop_reco;
    PseudoTopReconstruction * m_pseudotop_particle;
    
    PseudoTopMatching       * m_pseudotop_matching_reco2particle;
    PseudoTopMatching       * m_pseudotop_matching_reco2parton;
    PseudoTopMatching       * m_pseudotop_matching_particle2parton;
 // bool FillHistograms( int cutN );
};

typedef CutFlowPluginFactory< CutFlowTTbarResolved > CutFlowPluginFactory_TTbarResolved;

extern "C" {
  CutFlowPluginFactory_TTbarResolved * MakeCutFlowPlugin();
}

#endif /** __CF_TTbarResolved_H__ */
