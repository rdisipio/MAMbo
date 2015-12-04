#ifndef __CF_BOOSTED_SLPARTICLE_H__
#define __CF_BOOSTED_SLPARTICLE_H__

#include "ICutFlow.h"

#include "PhysicsHelperFunctions.h"

#include "EventData.h"
#include "Particle.h"

#ifdef __MOMA__
#include "MoMA/MoMA.h"
#endif 


using namespace PhysicsHelperFunctions;

class CutFlowBoostedSLParticle : public CutFlow
{
 public:
  CutFlowBoostedSLParticle();
  virtual ~CutFlowBoostedSLParticle();

  virtual bool Initialize();
  //  virtual bool Apply( EventData * ed, int * lastCutPassed = NULL );
  virtual bool Apply( EventData * ed);

 protected:
  bool PassedCutFlowParticle(EventData * ed = NULL);
 
 protected:
#ifdef __MOMA__
    MoMATool                * m_moma;
    SYSTEMATIC_TYPE           m_syst_type;
#endif
    
private:
};

typedef CutFlowPluginFactory< CutFlowBoostedSLParticle > CutFlowPluginFactory_BoostedSLParticle;

extern "C" {
  CutFlowPluginFactory_BoostedSLParticle * MakeCutFlowPlugin();
}

#endif /** __CF_BOOSTED_SL_H__ */