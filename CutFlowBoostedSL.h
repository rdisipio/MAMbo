#ifndef __CF_BOOSTED_SL_H__
#define __CF_BOOSTED_SL_H__

#include "ICutFlow.h"

class CutFlowBoostedSL : public CutFlow
{
 public:
  CutFlowBoostedSL();
  virtual ~CutFlowBoostedSL();

  virtual bool Apply( EventData * ed, int * lastCutPassed = NULL );

 protected:

};

typedef CutFlowPluginFactory< CutFlowBoostedSL > CutFlowPluginFactory_BoostedSL;

extern "C" {
  CutFlowPluginFactory_BoostedSL * MakeCutFlowPlugin();
}

#endif /** __CF_BOOSTED_SL_H__ */
