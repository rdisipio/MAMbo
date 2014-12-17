#include "MoMA.h"

MoMATool::MoMATool() :
  m_debug(false), m_fakes_weighter_el( NULL ), m_fakes_weighter_mu( NULL )
{
   m_fakes_weighter_el = new FakesWeights();
   m_fakes_weighter_mu = new FakesWeights();

   // nominal 
   string dataDir = getenv( "ROOTCOREDIR" );
   m_fakes_weighter_el->SetDataPath( dataDir + "/data/FakesMacros" );
   m_fakes_weighter_el->SetupWeighterDefault( FakesWeights::EJETS );

   m_fakes_weighter_mu->SetDataPath( dataDir + "/data/FakesMacros" );
   m_fakes_weighter_mu->SetupWeighterDefault( FakesWeights::MUJETS );

//   m_fakes_weighter_el->SetDebug(1);
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
  double w = 1.;
  double R = -666;
  double F = -666;

  if( channel == FakesWeights::EJETS ) {
    m_fakes_weighter_el->SetLepton( event, lepton );
    w = m_fakes_weighter_el->GetFakesWeightLJets( tight );
   
    if( m_debug ) {
       R = m_fakes_weighter_el->GetRealEff();
       F = m_fakes_weighter_el->GetFakeEff();
    }
  }
  else if( channel == FakesWeights::MUJETS ) {
    m_fakes_weighter_mu->SetLepton( event, lepton );
    w = m_fakes_weighter_mu->GetFakesWeightLJets( tight );
 
    if( m_debug ) {
       R = m_fakes_weighter_mu->GetRealEff();
       F = m_fakes_weighter_mu->GetFakeEff();
    }
  }
  else {
    throw runtime_error( "MoMA::FakesWeights: Invalid channel\n" );
  }

  if( m_debug )  cout << "DEBUG: r = " << R << " f = " << F << " w = " << w << endl;
  
  return w;
}


///////////////////////////////////////////


double MoMATool::GetFakesWeight( int channel, bool tight, double lep_pt, double lep_eta, double el_cl_eta, double dR_lj_min,
                                   double pTdR_lj_min, double jet_pt0, int jet_n, int nJet_tagged, int trigger)
{
   double w = 1.;
   double R = -666;
   double F = -666;

   if( channel == FakesWeights::EJETS ) {
      w = m_fakes_weighter_el->GetFakesWeightLJetsDefault( tight, lep_pt, el_cl_eta, fabs(el_cl_eta), dR_lj_min, pTdR_lj_min, jet_pt0, jet_n, nJet_tagged, trigger ); 
      R = m_fakes_weighter_el->GetRealEff();
      F = m_fakes_weighter_el->GetFakeEff();
   }
   else {
      w = m_fakes_weighter_mu->GetFakesWeightLJetsDefault( tight, lep_pt, lep_eta, std::fabs(lep_eta)/*unused*/, dR_lj_min, pTdR_lj_min, jet_pt0, jet_n, nJet_tagged, trigger );
   }

   cout << "DEBUG: r = " << R << " f = " << F << " w = " << w << endl;

   return w;
}


