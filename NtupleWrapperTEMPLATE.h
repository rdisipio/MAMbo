#ifndef __@NAME@_WRAPPER_H__
#define __@NAME@_WRAPPER_H__

#include "NtupleWrapper.h"

#include "@NAME@.h"

class NtupleWrapper@NAME@ : public NtupleWrapper< @NAME@ > 
{
 public:
  NtupleWrapper@NAME@( const char * fileListName, const char * branchListName = "branch_list.txt", const char * treeName = "physics" );
  virtual ~NtupleWrapper@NAME@();


 protected:
  virtual bool MakeEventInfo( EventData * ed );
  virtual bool MakeEventMET( EventData * ed );
  virtual bool MakeEventElectrons( EventData * ed );
  virtual bool MakeEventMuons( EventData * ed );
  virtual bool MakeEventJets( EventData * ed );

};

typedef NtupleWrapperPluginFactory< NtupleWrapper@NAME@ > NtupleWrapperPluginFactory_@NAME@;

extern "C" {
  NtupleWrapperPluginFactory_@NAME@ * MakeNtupleWrapperPlugin();
}

#endif /** __MINISLBOOST_WRAPPER_H__ */
