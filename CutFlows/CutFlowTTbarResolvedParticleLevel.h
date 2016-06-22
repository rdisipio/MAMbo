#ifndef __CF_TTbarResolvedParticleLevel_H__
#define __CF_TTbarResolvedParticleLevel_H__

#include "ICutFlow.h"

#include "PhysicsHelperFunctions.h"
#include "ControlPlotValues.h"
#include "EventData.h"
#include "Particle.h"

#ifdef __USE_LHAPDF__
#include <LHAPDF/LHAPDF.h>
#endif

using namespace PhysicsHelperFunctions;

class CutFlowTTbarResolvedParticleLevel : public CutFlow
{
 public:
  CutFlowTTbarResolvedParticleLevel();
  virtual ~CutFlowTTbarResolvedParticleLevel();

  virtual bool Initialize();
  virtual bool Apply( EventData * ed = NULL );

 protected:
  bool PassedCutFlowParticle( EventData * ed  = NULL);

  double GetPDFWeight( EventData * ed = NULL );

  void FillHistogramsControlPlotsParticle( ControlPlotValues& values );

  void FillHistogramsPseudotopParticle(  EventData * ed = NULL, const double weight = 1., string level = "particle" );
  void FillHistogramsPseudotopParton(    EventData * ed = NULL, const double weight = 1. );

  void FillHistogramsPseudotopResponseParticleToParton(  EventData * ed = NULL, const double weight = 1. );

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

#ifdef __USE_LHAPDF__
    enum Sets { CT10, MSTW, NNPDF, NSETS };

    LHAPDF::PDF * m_pdf;
#endif
	string m_PDFSF_name;
 private:
 
 
 
	unsigned long m_isMCSignal ;// m_config->custom_params_flag["isMCSignal"];
	//unsigned long isDilepton ;// m_config->custom_params_flag["isDilepton"];
	std::string m_decay ;// m_config->custom_params_string["decay"];
	// dileptonic filter
	// flag set in EventDumpers/EventDumperMCTruthTopMiniSLResolved.h
	unsigned long m_EventIsDileptonic ;// ed->property["isDileptonic"];
	//cout << "DEBUG: EventIsDileptonic ;// " << EventIsDileptonic << endl;
	unsigned long m_isStressTest ;// 0;
	std::string m_stressTestType ;// "none";
 
 
   vector<string> m_alias;
   std::map < string, double > m_VarField;

};

typedef CutFlowPluginFactory< CutFlowTTbarResolvedParticleLevel > CutFlowPluginFactory_TTbarResolvedParticleLevel;

extern "C" {
  CutFlowPluginFactory_TTbarResolvedParticleLevel * MakeCutFlowPlugin();
}

#endif /** __CF_TTbarResolvedParticleLevel_H__ */
