#ifndef __MINISLBOOST_WRAPPER_H__
#define __MINISLBOOST_WRAPPER_H__

#include "NtupleWrapper.h"

#include "MiniSLBoost.h"

class NtupleWrapperMiniSLBoost : public NtupleWrapper< MiniSLBoost > 
{
 public:
  NtupleWrapperMiniSLBoost( const char * fileListName, const char * branchListName = "branch_list.txt", const char * treeName = "physics" );
  virtual ~NtupleWrapperMiniSLBoost();


 protected:
  virtual bool MakeEventInfo( EventData * ed );
  virtual bool MakeEventMET( EventData * ed );
  virtual bool MakeEventElectrons( EventData * ed );
  virtual bool MakeEventMuons( EventData * ed );
  virtual bool MakeEventJets( EventData * ed );

};

typedef NtupleWrapperPluginFactory< NtupleWrapperMiniSLBoost > NtupleWrapperPluginFactory_MiniSLBoost;

extern "C" {
  NtupleWrapperPluginFactory_MiniSLBoost * MakeNtupleWrapperPlugin();
}

#endif /** __MINISLBOOST_WRAPPER_H__ */
