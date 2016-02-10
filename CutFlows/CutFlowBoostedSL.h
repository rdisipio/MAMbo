#ifndef __CF_BOOSTED_SL_H__
#define __CF_BOOSTED_SL_H__

#include "ICutFlow.h"
#include "TRandom3.h"
#include "PhysicsHelperFunctions.h"

#include "EventData.h"
#include "Particle.h"

#ifdef __MOMA__
#include "MoMA/MoMA.h"
#endif 

#include "ScalerFakes.h"

using namespace PhysicsHelperFunctions;

class CutFlowBoostedSL : public CutFlow
{
 public:
  CutFlowBoostedSL();
  virtual ~CutFlowBoostedSL();

  virtual bool Initialize();
  //  virtual bool Apply( EventData * ed, int * lastCutPassed = NULL );
  virtual bool Apply( EventData * ed);

 protected:
  bool PassedCutFlowReco( EventData * ed  = NULL); 
  bool PassedCutFlowParticle(EventData * ed = NULL);
  bool PassedCutFlowRecoControlWjets(EventData * ed = NULL);
  void FillHistogramsReco(EventData * ed = NULL, const double weight = 1., std::string selection = "1fj1b" );
  void FillHistogramsParticle(EventData * ed = NULL, const double weight = 1. );
  void FillMatrixRecoToParticle(EventData * ed = NULL, const double weight = 1. );
  void FillMatrixRecoToParton(EventData * ed = NULL, const double weight = 1. );
 protected:
#ifdef __MOMA__
    MoMATool                * m_moma;
    SYSTEMATIC_TYPE           m_syst_type;
#endif
    
private:

    TRandom3 *m_rand; 
    string m_bTagSF_name;
    string m_leptonSF_name;
    string m_pileupSF_name;
	ScalerFakes * m_scalerFakes;
    

};

typedef CutFlowPluginFactory< CutFlowBoostedSL > CutFlowPluginFactory_BoostedSL;

extern "C" {
  CutFlowPluginFactory_BoostedSL * MakeCutFlowPlugin();
}

#endif /** __CF_BOOSTED_SL_H__ */
