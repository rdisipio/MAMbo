#ifndef __CF_TTHBoosted_H__
#define __CF_TTHBoosted_H__

#include "ICutFlow.h"

class CutFlowTTHBoosted : public CutFlow
{
 public:
  CutFlowTTHBoosted();
  virtual ~CutFlowTTHBoosted();

  virtual bool Initialize();
  virtual bool Apply( EventData * ed );

 protected:
    bool PassedCutFlow_emu_2t( EventData * ed );

 protected:
    vector< string > m_cutAlias;
};

typedef CutFlowPluginFactory< CutFlowTTHBoosted > CutFlowPluginFactory_TTHBoosted;

extern "C" {
  CutFlowPluginFactory_TTHBoosted * MakeCutFlowPlugin();
}

#endif /** __CF_TTHBoosted_H__ */
