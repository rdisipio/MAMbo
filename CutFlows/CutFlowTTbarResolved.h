#ifndef __CF_TTbarResolved_H__
#define __CF_TTbarResolved_H__

#include "ICutFlow.h"

#include "PhysicsHelperFunctions.h"

using namespace PhysicsHelperFunctions;

class CutFlowTTbarResolved : public CutFlow
{
 public:
  CutFlowTTbarResolved();
  virtual ~CutFlowTTbarResolved();

  virtual bool Initialize();
  virtual bool Apply( EventData * ed );

 protected:
    PseudoTopReconstruction * m_pseudotop;

 // bool FillHistograms( int cutN );
};

typedef CutFlowPluginFactory< CutFlowTTbarResolved > CutFlowPluginFactory_TTbarResolved;

extern "C" {
  CutFlowPluginFactory_TTbarResolved * MakeCutFlowPlugin();
}

#endif /** __CF_TTbarResolved_H__ */
