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

double MoMATool::GetFakesWeight( int channel, bool tight, double lep_pt, double lep_eta, double el_cl_eta, double dR_lj_min,
                                   double pTdR_lj_min, double jet_pt0, int jet_n, int nJet_tagged, int trigger)
{
   if( channel == FakesWeights::EJETS ) {
      return m_fakes_weighter_el->GetFakesWeightLJetsDefault( tight, lep_pt, el_cl_eta, fabs(el_cl_eta), dR_lj_min, pTdR_lj_min, jet_pt0, jet_n, nJet_tagged, trigger ); 
   }
   else {
      return m_fakes_weighter_mu->GetFakesWeightLJetsDefault( tight, lep_pt, lep_eta, std::fabs(lep_eta)/*unused*/, dR_lj_min, pTdR_lj_min, jet_pt0, jet_n, nJet_tagged, trigger );
   }
}


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
