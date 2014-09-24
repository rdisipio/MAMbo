#ifndef __CF_TTbarResolvedParticleLevel_H__
#define __CF_TTbarResolvedParticleLevel_H__

#include "ICutFlow.h"

class CutFlowTTbarResolvedParticleLevel : public CutFlow
{
 public:
  CutFlowTTbarResolvedParticleLevel();
  virtual ~CutFlowTTbarResolvedParticleLevel();

  virtual bool Initialize();
  virtual bool Apply( EventData * ed );

 protected:

};

typedef CutFlowPluginFactory< CutFlowTTbarResolvedParticleLevel > CutFlowPluginFactory_TTbarResolvedParticleLevel;

extern "C" {
  CutFlowPluginFactory_TTbarResolvedParticleLevel * MakeCutFlowPlugin();
}

#endif /** __CF_TTbarResolvedParticleLevel_H__ */
