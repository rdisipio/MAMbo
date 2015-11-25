#ifndef __CF_BOOSTED_SL_H__
#define __CF_BOOSTED_SL_H__

#include "ICutFlow.h"

#include "PhysicsHelperFunctions.h"

#include "EventData.h"
#include "Particle.h"

#ifdef __MOMA__
#include "MoMA/MoMA.h"
#endif 


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
 
 protected:
#ifdef __MOMA__
    MoMATool                * m_moma;
    SYSTEMATIC_TYPE           m_syst_type;
#endif
    
private:
};

typedef CutFlowPluginFactory< CutFlowBoostedSL > CutFlowPluginFactory_BoostedSL;

extern "C" {
  CutFlowPluginFactory_BoostedSL * MakeCutFlowPlugin();
}

#endif /** __CF_BOOSTED_SL_H__ */
