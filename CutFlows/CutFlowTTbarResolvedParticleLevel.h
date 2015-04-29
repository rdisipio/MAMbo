#ifndef __CF_TTbarResolvedParticleLevel_H__
#define __CF_TTbarResolvedParticleLevel_H__

#include "ICutFlow.h"

#include "PhysicsHelperFunctions.h"
#include "ControlPlotValues.h"
#include "EventData.h"
#include "Particle.h"

using namespace PhysicsHelperFunctions;

class CutFlowTTbarResolvedParticleLevel : public CutFlow
{
 public:
  CutFlowTTbarResolvedParticleLevel();
  virtual ~CutFlowTTbarResolvedParticleLevel();

  virtual bool Initialize();
  virtual bool Apply( EventData * ed );

 protected:
  bool PassedCutFlowParticle( EventData * ed );

  void FillHistogramsControlPlotsParticle( ControlPlotValues& values );

  void FillHistogramsPseudotopParticle(  EventData * ed, const double weight = 1., string level = "particle" );
  void FillHistogramsPseudotopParton(    EventData * ed, const double weight = 1. );

  void FillHistogramsPseudotopResponseParticleToParton(  EventData * ed, const double weight = 1. );

  void FillHistogramsMatchingParticleToParton( double weight = 1. );

  void FillHistograms(string path, ControlPlotValues& values);
  void FillMatrix(string path, Particle& px, Particle& py, double weight);

  void FillHistogramsTopPairs(string level, TLorentzVector &topL, TLorentzVector &topH, TLorentzVector &ttSystem, TLorentzVector &WL, TLorentzVector &WH, const double weight);

  void FillHistogramsPartonTop(EventData::Truth_t& particle, int index, string level, string topType, const double weight);
  void FillHistogramsPartonTopPairs(EventData::Truth_t& particle, int indexL, int indexH, int indextt, string level, const double weight);

  void FillHistogramsPseudoTop(EventData::Reco_t& particle, int index, string level, string topType, const double weight, const double mbl = 0);
  void FillHistogramsPseudoTopPairs(EventData::Reco_t& particle, int indexL, int indexH, int indextt, string level, const double weight);


 protected:
  PseudoTopReconstruction * m_pseudotop_particle;

  PseudoTopMatching       * m_pseudotop_matching_particle2parton;

 private:
   vector<string> alias;
   std::map < string, double > m_VarField;

};

typedef CutFlowPluginFactory< CutFlowTTbarResolvedParticleLevel > CutFlowPluginFactory_TTbarResolvedParticleLevel;

extern "C" {
  CutFlowPluginFactory_TTbarResolvedParticleLevel * MakeCutFlowPlugin();
}

#endif /** __CF_TTbarResolvedParticleLevel_H__ */
