#ifndef __CF_@NAME@_H__
#define __CF_@NAME@_H__

#include "ICutFlow.h"

class CutFlow@NAME@ : public CutFlow
{
 public:
  CutFlow@NAME@();
  virtual ~CutFlow@NAME@();

  virtual bool Initialize();
  virtual bool Apply( EventData * ed );

 protected:

};

typedef CutFlowPluginFactory< CutFlow@NAME@ > CutFlowPluginFactory_@NAME@;

extern "C" {
  CutFlowPluginFactory_@NAME@ * MakeCutFlowPlugin();
}

#endif /** __CF_@NAME@_H__ */
