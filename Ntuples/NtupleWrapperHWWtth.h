#ifndef __HWWtth_WRAPPER_H__
#define __HWWtth_WRAPPER_H__

#include "NtupleWrapper.h"

#include "HWWtth.h"

class NtupleWrapperHWWtth : public NtupleWrapper< HWWtth > 
{
 public:
  NtupleWrapperHWWtth( const char * fileListName, const char * branchListName = "branch_list.txt", const char * treeName = "physics" );
  virtual ~NtupleWrapperHWWtth();


 protected:
  virtual bool MakeEventInfo( EventData * ed );
  virtual bool MakeEventTrigger( EventData * ed );
  virtual bool MakeEventMET( EventData * ed );
  virtual bool MakeEventElectrons( EventData * ed );
  virtual bool MakeEventMuons( EventData * ed );
  virtual bool MakeEventJets( EventData * ed );
  virtual bool MakeEventTruth( EventData * ed );
};

typedef NtupleWrapperPluginFactory< NtupleWrapperHWWtth > NtupleWrapperPluginFactory_HWWtth;

extern "C" {
  NtupleWrapperPluginFactory_HWWtth * MakeNtupleWrapperPlugin();
}

#endif /** __MINISLBOOST_WRAPPER_H__ */
