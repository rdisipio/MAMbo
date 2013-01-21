#ifndef __CF_FakeRateZjet_H__
#define __CF_FakeRateZjet_H__

#include "ICutFlow.h"

class CutFlowFakeRateZjet : public CutFlow
{
 public:
  CutFlowFakeRateZjet();
  virtual ~CutFlowFakeRateZjet();

  virtual bool Apply( EventData * ed, int * lastCutPassed = NULL );

 protected:

};

typedef CutFlowPluginFactory< CutFlowFakeRateZjet > CutFlowPluginFactory_FakeRateZjet;

extern "C" {
  CutFlowPluginFactory_FakeRateZjet * MakeCutFlowPlugin();
}

#endif /** __CF_FakeRateZjet_H__ */
