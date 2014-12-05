#include "MoMA.h"

MoMATool::MoMATool() :
  m_fakes_weighter_el( NULL ), m_fakes_weighter_mu( NULL )
{
   m_fakes_weighter_el = new FakesWeights();
   m_fakes_weighter_mu = new FakesWeights();

   // nominal 
   string dataDir = getenv( "ROOTCOREDIR" );
   m_fakes_weighter_el->SetDataPath( dataDir + "/data/FakesMacros" );
   m_fakes_weighter_el->SetupWeighterDefault( FakesWeights::EJETS );

   m_fakes_weighter_mu->SetDataPath( dataDir + "/data/FakesMacros" );
   m_fakes_weighter_mu->SetupWeighterDefault( FakesWeights::MUJETS, "", "" );
}

MoMATool::~MoMATool()
{
  delete m_fakes_weighter_el;
  delete m_fakes_weighter_mu;
}


///////////////////////////////////////////


MoMATool * MoMATool::GetHandle()
{
   static MoMATool instance;

   return &instance;
}


///////////////////////////////////////////


double MoMATool::GetFakesWeight( int channel, const MMEvent& event, const MMLepton& lepton, bool tight )
{
  if( channel == FakesWeights::EJETS ) {
    m_fakes_weighter_el->SetLepton( event, lepton );
    return m_fakes_weighter_el->GetFakesWeightLJets( tight );
  }
  else if( channel == FakesWeights::MUJETS ) {
    m_fakes_weighter_mu->SetLepton( event, lepton );
    return m_fakes_weighter_mu->GetFakesWeightLJets( tight );
  }
  else {
    throw runtime_error( "MoMA::FakesWeights: Invalid channel\n" );
  }
}
