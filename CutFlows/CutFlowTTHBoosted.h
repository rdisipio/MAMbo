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

    void FillHistograms( const EventData * ed );

 protected:

};

typedef CutFlowPluginFactory< CutFlowTTHBoosted > CutFlowPluginFactory_TTHBoosted;

extern "C" {
  CutFlowPluginFactory_TTHBoosted * MakeCutFlowPlugin();
}

#endif /** __CF_TTHBoosted_H__ */
