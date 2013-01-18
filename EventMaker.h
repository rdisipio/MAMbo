#ifndef __EVENTMAKER_H__
#define __EVENTMAKER_H__

#include "EventData.h"
#include "MiniSLBoost.h"

#define GET_VALUE(X) m_ntuple-> X
#define GET_VALUE_ARRAY(X,N) m_ntuple-> X ->at( N )
#define MAKE_OBJECT(OBJ, ED) if( !Make##OBJ( ED ) ) throw runtime_error( "Cannot create " # OBJ )

typedef MiniSLBoost NTUPLE;

class EventMaker 
{
 public:
  static EventMaker * GetHandle();

  virtual ~EventMaker();
  
  virtual bool SetNtuple( NTUPLE * ntuple );
   
  virtual EventData * MakeEvent( Long64_t i );

 protected:
   EventMaker();

   virtual bool MakeInfo( EventData * ed );
   virtual bool MakeMET( EventData * ed );
   virtual bool MakeElectrons( EventData * ed );
   virtual bool MakeMuons( EventData * ed );
   virtual bool MakeJets( EventData * ed );

 protected:
   NTUPLE * m_ntuple;
};

#endif /** _EVENTMAKER_H__ */
