#ifndef __CF_Dummy_H__
#define __CF_Dummy_H__

#include "ICutFlow.h"

#include "PhysicsHelperFunctions.h"
#include "EventData.h"
#include "Particle.h"

#ifdef __MOMA__
#include "MoMA/MoMA.h"
#endif 

using namespace PhysicsHelperFunctions;

class CutFlowDummy : public CutFlow
{
 public:
  CutFlowDummy();
  virtual ~CutFlowDummy();

  virtual bool Initialize();
  virtual bool Apply( EventData * ed );

 protected:

 protected:

#ifdef __MOMA__
    MoMATool                * m_moma;
    SYSTEMATIC_TYPE           m_syst_type;
#endif
    
private:
};

typedef CutFlowPluginFactory< CutFlowDummy > CutFlowPluginFactory_Dummy;

extern "C" {
  CutFlowPluginFactory_Dummy * MakeCutFlowPlugin();
}

#endif /** __CF_Dummy_H__ */
