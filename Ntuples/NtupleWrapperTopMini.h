#ifndef __TopMini_WRAPPER_H__
#define __TopMini_WRAPPER_H__

#include "NtupleWrapper.h"

#include "TopMini.h"

class NtupleWrapperTopMini : public NtupleWrapper< TopMini > 
{
 public:
  NtupleWrapperTopMini( const char * fileListName, const char * branchListName = "branch_list.txt", const char * treeName = "physics" );
  virtual ~NtupleWrapperTopMini();


 protected:
  virtual bool MakeEventInfo( EventData * ed );
  virtual bool MakeEventTrigger( EventData * ed );
  virtual bool MakeEventMET( EventData * ed );
  virtual bool MakeEventElectrons( EventData * ed );
  virtual bool MakeEventMuons( EventData * ed );
  virtual bool MakeEventJets( EventData * ed );
  virtual bool MakeEventTruth( EventData * ed );

 private:
  bool HadronicDecay( const int parent_index ) const;
  bool IsTopHadronic( const int parent_index ) const;
};

typedef NtupleWrapperPluginFactory< NtupleWrapperTopMini > NtupleWrapperPluginFactory_TopMini;

extern "C" {
  NtupleWrapperPluginFactory_TopMini * MakeNtupleWrapperPlugin();
}

#endif /** __MINISLBOOST_WRAPPER_H__ */
