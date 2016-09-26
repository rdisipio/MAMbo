#ifndef __CF_TTbarAllHadBoosted_H__
#define __CF_TTbarAllHadBoosted_H__

#include "ICutFlow.h"
#include "PhysicsHelperFunctions.h"
#include "EventData.h"
#include "Particle.h"

#include "TRandom3.h"

class CutFlowTTbarAllHadBoosted : public CutFlow
{
 public:
  CutFlowTTbarAllHadBoosted();
  virtual ~CutFlowTTbarAllHadBoosted();

  virtual bool Initialize();
  virtual bool Apply( EventData * ed );

 protected:

};

typedef CutFlowPluginFactory< CutFlowTTbarAllHadBoosted > CutFlowPluginFactory_TTbarAllHadBoosted;

extern "C" {
  CutFlowPluginFactory_TTbarAllHadBoosted * MakeCutFlowPlugin();
}

#endif /** __CF_TTbarAllHadBoosted_H__ */
