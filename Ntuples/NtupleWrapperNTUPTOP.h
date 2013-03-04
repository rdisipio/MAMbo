#ifndef __NTUPTOP_WRAPPER_H__
#define __NTUPTOP_WRAPPER_H__

#include "NtupleWrapper.h"

#include "NTUPTOP.h"

class NtupleWrapperNTUPTOP : public NtupleWrapper< NTUPTOP > 
{
 public:
  NtupleWrapperNTUPTOP( const char * fileListName, const char * branchListName = "branch_list.txt", const char * treeName = "physics" );
  virtual ~NtupleWrapperNTUPTOP();


 protected:
  virtual bool MakeEventInfo( EventData * ed );
  virtual bool MakeEventMET( EventData * ed );
  virtual bool MakeEventElectrons( EventData * ed );
  virtual bool MakeEventMuons( EventData * ed );
  virtual bool MakeEventJets( EventData * ed );
  virtual bool MakeEventTruth( EventData * ed );
};

typedef NtupleWrapperPluginFactory< NtupleWrapperNTUPTOP > NtupleWrapperPluginFactory_NTUPTOP;

extern "C" {
  NtupleWrapperPluginFactory_NTUPTOP * MakeNtupleWrapperPlugin();
}

#endif /** __MINISLBOOST_WRAPPER_H__ */
