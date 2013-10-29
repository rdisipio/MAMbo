#ifndef __D3PDTruth_WRAPPER_H__
#define __D3PDTruth_WRAPPER_H__

#include "NtupleWrapper.h"

#include "D3PDTruth.h"

class NtupleWrapperD3PDTruth : public NtupleWrapper< D3PDTruth > 
{
 public:
  NtupleWrapperD3PDTruth( const char * fileListName, const char * branchListName = "branch_list.txt", const char * treeName = "physics" );
  virtual ~NtupleWrapperD3PDTruth();


 protected:
  virtual bool MakeEventInfo( EventData * ed );
  virtual bool MakeEventTrigger( EventData * ed );
  virtual bool MakeEventMET( EventData * ed );
  virtual bool MakeEventElectrons( EventData * ed );
  virtual bool MakeEventMuons( EventData * ed );
  virtual bool MakeEventJets( EventData * ed );
  virtual bool MakeEventTruth( EventData * ed );
};

typedef NtupleWrapperPluginFactory< NtupleWrapperD3PDTruth > NtupleWrapperPluginFactory_D3PDTruth;

extern "C" {
  NtupleWrapperPluginFactory_D3PDTruth * MakeNtupleWrapperPlugin();
}

#endif /** __MINISLBOOST_WRAPPER_H__ */
