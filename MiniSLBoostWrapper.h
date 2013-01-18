#ifndef __MINISLBOOST_WRAPPER_H__
#define __MINISLBOOST_WRAPPER_H__

#include "NtupleWrapper.h"

#include "MiniSLBoost.h"

class MiniSLBoostWrapper : public NtupleWrapper< MiniSLBoost > 
{
 public:
  MiniSLBoostWrapper( const char * fileListName, const char * branchListName = "branch_list.txt", const char * treeName = "physics" );
  virtual ~MiniSLBoostWrapper();


 protected:
  virtual bool MakeEventInfo( EventData * ed );
  virtual bool MakeEventMET( EventData * ed );
  virtual bool MakeEventElectrons( EventData * ed );
  virtual bool MakeEventMuons( EventData * ed );
  virtual bool MakeEventJets( EventData * ed );

};

#endif /** __MINISLBOOST_WRAPPER_H__ */
