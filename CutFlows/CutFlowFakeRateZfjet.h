#ifndef __CF_FakeRateZfjet_H__
#define __CF_FakeRateZfjet_H__

#include "ICutFlow.h"

class CutFlowFakeRateZfjet : public CutFlow
{
 public:
  CutFlowFakeRateZfjet();
  virtual ~CutFlowFakeRateZfjet();

  virtual bool Initialize();
  virtual bool Apply( EventData * ed );

 protected:
    void FillHistograms( const EventData * ed );
 
 protected:
    vector< string > m_cutAlias;

};

typedef CutFlowPluginFactory< CutFlowFakeRateZfjet > CutFlowPluginFactory_FakeRateZfjet;

extern "C" {
  CutFlowPluginFactory_FakeRateZfjet * MakeCutFlowPlugin();
}

#endif /** __CF_FakeRateZfjet_H__ */
