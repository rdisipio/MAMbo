#ifndef __CF_TTHTo2LeptonsSS_H__
#define __CF_TTHTo2LeptonsSS_H__

#include "ICutFlow.h"

class CutFlowTTHTo2LeptonsSS : public CutFlow
{
 public:
  CutFlowTTHTo2LeptonsSS();
  virtual ~CutFlowTTHTo2LeptonsSS();

  virtual bool Initialize();
  virtual bool Apply( EventData * ed, int * lastCutPassed = NULL );

 protected:

};

typedef CutFlowPluginFactory< CutFlowTTHTo2LeptonsSS > CutFlowPluginFactory_TTHTo2LeptonsSS;

extern "C" {
  CutFlowPluginFactory_TTHTo2LeptonsSS * MakeCutFlowPlugin();
}

#endif /** __CF_TTHTo2LeptonsSS_H__ */
