#ifndef __CF_FakeRateZfjet_H__
#define __CF_FakeRateZfjet_H__

#include "ICutFlow.h"

class CutFlowFakeRateZfjet : public CutFlow
{
 public:
  CutFlowFakeRateZfjet();
  virtual ~CutFlowFakeRateZfjet();

  virtual bool Apply( EventData * ed, int * lastCutPassed = NULL );

 protected:

};

typedef CutFlowPluginFactory< CutFlowFakeRateZfjet > CutFlowPluginFactory_FakeRateZfjet;

extern "C" {
  CutFlowPluginFactory_FakeRateZfjet * MakeCutFlowPlugin();
}

#endif /** __CF_FakeRateZjet_H__ */
