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

#ifdef __USE_LHAPDF__
#include <LHAPDF/LHAPDF.h>
#endif

#include "ScalerFakes.h"
#include "ScalerWjets.h"
using namespace PhysicsHelperFunctions;

class CutFlowTTbarResolved : public CutFlow
{
 public:
  CutFlowTTbarResolved();
  virtual ~CutFlowTTbarResolved();

  virtual bool Initialize();
  virtual bool Apply( EventData * ed = NULL );
  virtual bool Finalize();

 protected:
  bool PassedCutFlowReco(     EventData * ed = NULL );
  bool PassedCutFlowParticle( EventData * ed = NULL );

  //double GetFakesWeight( EventData * ed = NULL );
  double GetPDFWeight( EventData * ed = NULL );

  void MoreCRFillHistogramsControlPlotsReco( string mystr, ControlPlotValues& values );
  void FillHistogramsControlPlotsReco( ControlPlotValues& values );
  void FillHistogramsControlPlotsParticle( ControlPlotValues& values );
  void FillHistogramsDiagnostics( ControlPlotValues& values );
  
  void FillHistogramsPseudotopReco(      EventData * ed = NULL, const double weight = 1., string level = "reco" );
  void FillHistogramsPseudotopParticle(  EventData * ed = NULL, const double weight = 1., string level = "particle" );
  void FillHistogramsPseudotopParton(    EventData * ed = NULL, const double weight = 1. );
  
  void FillHistogramsPseudotopResponseRecoToParticle(    EventData * ed = NULL, const double weight = 1. );
  void FillHistogramsPseudotopResponseRecoToParton(      EventData * ed = NULL, const double weight = 1. );
  void FillHistogramsPseudotopResponseParticleToParton(  EventData * ed = NULL, const double weight = 1. );
  
  void FillHistogramsMatchingRecoToParticle(   double weight = 1. );   
  void FillHistogramsMatchingRecoToParton(     double weight = 1. ); 
  void FillHistogramsMatchingParticleToParton( double weight = 1. ); 
  
  void FillHistograms(string path, ControlPlotValues& values);
  void FillMatrix(string path, Particle& px, Particle& py, double weight);
  
  void FillHistogramsTopPairs(string level, TLorentzVector &topL, TLorentzVector &topH, TLorentzVector &ttSystem, TLorentzVector &WL, TLorentzVector &WH, NuData nudata, const double weight);

  void FillHistogramsPartonTop(EventData::Truth_t& particle, int index, string level, string topType, const double weight);
  void FillHistogramsPartonTopPairs(EventData::Truth_t& particle, int indexL, int indexH, int indextt, string level, const double weight);

  void FillHistogramsPseudoTop(EventData::Reco_t& particle, int index, string level, string topType, const double weight,const double mlb = -1);
  void FillHistogramsPseudoTopPairs(EventData::Reco_t& particle, int indexL, int indexH, int indextt, string level, NuData nudata, const double weight);


 protected:
    PseudoTopReconstruction * m_pseudotop_reco;
    PseudoTopReconstruction * m_pseudotop_particle;
    
    PseudoTopMatching       * m_pseudotop_matching_reco2particle;
    PseudoTopMatching       * m_pseudotop_matching_reco2parton;
    PseudoTopMatching       * m_pseudotop_matching_particle2parton;
    string m_bTagSF_name;
    string m_leptonSF_name;
    string m_pileupSF_name;
    string m_jvtSF_name;
    string m_PDFSF_name;
#ifdef __MOMA__
    MoMATool                * m_moma;
    SYSTEMATIC_TYPE           m_syst_type;
#endif

#ifdef __USE_LHAPDF__
    enum Sets { CT10, MSTW, NNPDF, NSETS };

    LHAPDF::PDF * m_pdf;
#endif 
	ScalerFakes * m_scalerFakes;
	ScalerWjets * m_scalerWjets;
    
private:

    vector<string> m_alias;
    TRandom3 *m_rand; 
    std::map < string, double > m_VarField;
    

};

typedef CutFlowPluginFactory< CutFlowTTbarResolved > CutFlowPluginFactory_TTbarResolved;

extern "C" {
  CutFlowPluginFactory_TTbarResolved * MakeCutFlowPlugin();
}

#endif /** __CF_TTbarResolved_H__ */
