#include "MoMA.h"

MoMATool::MoMATool() :
  m_fakes_weighter( NULL )
{
   m_fakes_weighter = new FakesWeights();

   // nominal 
   string dataDir;
   m_fakes_weighter->SetDataPath( dataDir + "data/FakesMacros" );
   m_fakes_weighter->SetupWeighterDefault( FakesWeights::MUJETS );
}

MoMATool::~MoMATool()
{
  delete m_fakes_weighter;
}


///////////////////////////////////////////


MoMATool * MoMATool::GetHandle()
{
   static MoMATool instance;

   return &instance;
}
