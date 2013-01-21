#ifndef __MiniML_WRAPPER_H__
#define __MiniML_WRAPPER_H__

#include "NtupleWrapper.h"

#include "MiniML.h"

class NtupleWrapperMiniML : public NtupleWrapper< MiniML > 
{
 public:
  NtupleWrapperMiniML( const char * fileListName, const char * branchListName = "branch_list.txt", const char * treeName = "physics" );
  virtual ~NtupleWrapperMiniML();


 protected:
  virtual bool MakeEventInfo( EventData * ed );
  virtual bool MakeEventMET( EventData * ed );
  virtual bool MakeEventElectrons( EventData * ed );
  virtual bool MakeEventMuons( EventData * ed );
  virtual bool MakeEventJets( EventData * ed );

};

typedef NtupleWrapperPluginFactory< NtupleWrapperMiniML > NtupleWrapperPluginFactory_MiniML;

extern "C" {
  NtupleWrapperPluginFactory_MiniML * MakeNtupleWrapperPlugin();
}

#endif /** __MINISLBOOST_WRAPPER_H__ */
