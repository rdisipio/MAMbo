#include "ScalerFakes.h"
#include "Commons.h"
#include "EventData.h"

//Rafal Code
#include "FakeEffProvider.h"
using namespace PhysicsHelperFunctions;



ScalerFakes * ScalerFakes::m_instance = NULL;
ScalerFakes::ScalerFakes( int channel, int nParameters, string method)
{
  m_channel = channel;
  m_method = method;
  m_nParameters = nParameters;
  m_fakeEff = new  FakeEffProvider(m_channel,FakeEffProvider::Type::fakeEff);
  m_realEff = new  FakeEffProvider(m_channel,FakeEffProvider::Type::realEff);
  m_tightEff = new FakeEffProvider(m_channel,FakeEffProvider::Type::tightEff);

  
}


ScalerFakes::~ScalerFakes( )
{
  delete m_fakeEff;
  delete m_realEff;
  delete m_tightEff;
}

ScalerFakes * ScalerFakes::GetHandle( int channel, int nParameters, string method )
{
  if( m_instance == NULL ) m_instance = new ScalerFakes( channel, nParameters, method );
  else
  {
    if( channel != m_instance->GetChannel()  || nParameters !=  m_instance->GetNParameters()) 
    {
      char msg[100];
      sprintf( msg,"ScalerFakes requested  with channel == %i and nParameters == %i \
      but an instance already exists with channel == %i and nParameters == %i\n", channel, nParameters,  m_instance->GetChannel(),  m_instance->GetNParameters() );
      throw std::runtime_error( msg );
    }
  }
  return m_instance;
}


//OLD PARAMETRIZATION
// double ScalerFakes::GetFakesWeightMM( EventData * ed)
// {
//     //get dphi lep met	
// 	double qcd_weight = 1;
//     if( m_channel == 0 && ed->electrons.n < 1 ) return qcd_weight;
//     if( m_channel == 1 && ed->muons.n < 1 ) return qcd_weight;
// 	const bool tight = ( m_channel == 0 ) ? ed->electrons.property["tight"].at(0) : ed->muons.property["tight"].at(0);
// 	double phi_lep = ed->electrons.phi.at(0);
// 	double phi_met = ed->MET.phi;		
// 	double dPhi_met_lep = deltaPhi( phi_met, phi_lep );
// 	double delta = 0, ef = 0, er = 0;
// 	if( m_channel == 0 ) //electrons case
// 	{
// 		int ntag = ed->bjets.n;
// 		if( tight ) delta = 1;
// 		if( m_nParameters == 2)
// 		{
// 			ef = m_fakeEff->GetEfficiency( FakeEffProvider::Var::DPHILMET,dPhi_met_lep ) ;
// 			ef *= m_fakeEff->GetEfficiency( FakeEffProvider::Var::NBTAG, ntag, true );
// 			ef = TMath::Sqrt( ef );
// 			er = m_realEff->GetEfficiency( FakeEffProvider::Var::DPHILMET,dPhi_met_lep ) ;
// 			er *= m_realEff->GetEfficiency( FakeEffProvider::Var::NBTAG, ntag, true );
// 			er = TMath::Sqrt( er );
// 			
// 		}
// 		else if( m_nParameters == 4 )
// 		{
// 			double pt_lep = ed->electrons.pT.at(0);
// 			double eta_lep = ed->electrons.eta.at(0);
// 		   	ef = m_fakeEff->GetEfficiency( FakeEffProvider::Var::DPHILMET,dPhi_met_lep ) ;
// 			ef *= m_fakeEff->GetEfficiency( FakeEffProvider::Var::NBTAG, ntag, true );
// 			ef *= m_fakeEff->GetEfficiency( FakeEffProvider::Var::LPT, pt_lep);
// 			ef *= m_fakeEff->GetEfficiency( FakeEffProvider::Var::LETA, eta_lep,true);
// 			ef = TMath::Power( ef, 0.25 );
// 			er = m_realEff->GetEfficiency( FakeEffProvider::Var::DPHILMET,dPhi_met_lep ) ;
// 			er *= m_realEff->GetEfficiency( FakeEffProvider::Var::NBTAG, ntag, true );
// 			er *= m_realEff->GetEfficiency( FakeEffProvider::Var::LPT, pt_lep);
// 			er *= m_realEff->GetEfficiency( FakeEffProvider::Var::LETA, eta_lep, true);
// 			er = TMath::Power( er, 0.25 );
// 		}
// 	}
// 	else if( m_channel == 1)
// 	{
// 		if (tight) delta = 1.0;
// 		double met = ed->MET.et;		
// 		ef =  m_fakeEff->GetEfficiency( FakeEffProvider::Var::DPHILMET, dPhi_met_lep);
// 		ef *= m_fakeEff->GetEfficiency( FakeEffProvider::Var::MET, met*1e-3);
// 		ef =  TMath::Sqrt(ef);
// 
// 		er =  m_realEff->GetEfficiency( FakeEffProvider::Var::DPHILMET, dPhi_met_lep);
// 		er *= m_realEff->GetEfficiency( FakeEffProvider::Var::MET, met*1e-3);
// 		er =  TMath::Sqrt(er);
// 	}
// 	qcd_weight = ef * ( er - delta ) / ( er - ef );
// 	return qcd_weight;
// }

double ScalerFakes::GetFakesWeight( EventData * ed){
  
  if( m_method == "MM" ) return GetFakesWeightMM(ed);
  if( m_method == "MMM" ) return GetFakesWeightMMM(ed);
  
  std::cout<<"WARNING::Fakes weight method wrongly defined: " <<m_method<<endl;
  return 1.;
  
}
//Two version of the scale factor evaluation
double ScalerFakes::GetFakesWeightMM( EventData * ed)
{
  //get dphi lep met	
  double qcd_weight = 1;
  if( m_channel == 0 && ed->electrons.n < 1 ) return qcd_weight;
  if( m_channel == 1 && ed->muons.n < 1 ) return qcd_weight;
  
  const bool tight = ( m_channel == 0 ) ? ed->electrons.property["tight"].at(0) : ed->muons.property["tight"].at(0);
  
  double phi_met = ed->MET.phi;		
  double met = ed->MET.et;		
  
  int nbtag = ed->bjets.n;
  int njets = ed->jets.n; 
  double jet_pt = ed->jets.pT.at(0);
  double delta = 0, ef = 0, er = 0, et = 0;

  
  
  
  if( m_channel == 0 ) //electrons case
  {
    
    if (tight) delta = 1.0;
    
    double pt_lep = ed->electrons.pT.at(0);
    double eta_lep =ed->electrons.eta.at(0);
    double phi_lep = ed->electrons.phi.at(0);
    double dPhi_met_lep = deltaPhi( phi_met, phi_lep );
	double ef_highpt=0;
    double er_highpt=0;
    ef = m_fakeEff->GetEfficiency2D(FakeEffProvider::Var::TWODIM_PT_DPHI, pt_lep*1e-3, abs(dPhi_met_lep), true);
    ef *= m_fakeEff->GetEfficiency2D(FakeEffProvider::Var::TWODIM_PT_ETA, pt_lep*1e-3, abs(eta_lep), true);
    ef *= m_fakeEff->GetEfficiency2D(FakeEffProvider::Var::TWODIM_JET1PT_DPHI, jet_pt*1e-3, abs(dPhi_met_lep), true);
    ef  = TMath::Power(ef,0.3333333333);
    ef *= m_fakeEff->GetEfficiency2D(FakeEffProvider::Var::TWODIM_NJETS_NBTAG, njets, nbtag, true);
    ef /= m_fakeEff->GetAverageEfficiency();
    ef_highpt = ef;
    
    er =  m_realEff->GetEfficiency(FakeEffProvider::Var::DPHILMET, abs(dPhi_met_lep), true);
    er *= m_realEff->GetEfficiency(FakeEffProvider::Var::LPT, pt_lep*1e-3, true);
    er = TMath::Sqrt(er);
    er_highpt = er;
    
    // LOW-PT EFFICIENCIES
    double ef_lowpt=0;
    double er_lowpt=0;
    if (abs(eta_lep) < 1.5)  {
      ef = m_fakeEff->GetEfficiency2D(FakeEffProvider::Var::TWODIM_PT_DPHI, pt_lep*1e-3, abs(dPhi_met_lep), true);
      ef *= m_fakeEff->GetEfficiency2D(FakeEffProvider::Var::TWODIM_PT_ETA, pt_lep*1e-3, abs(eta_lep), true);
      ef  = TMath::Sqrt(ef);
      ef *= m_fakeEff->GetEfficiency2D(FakeEffProvider::Var::TWODIM_NJETS_NBTAG, njets, nbtag, true);
      ef /= m_fakeEff->GetAverageEfficiency();
      
      er =  m_realEff->GetEfficiency(FakeEffProvider::Var::DPHILMET, abs(dPhi_met_lep), true);
      er *= m_realEff->GetEfficiency(FakeEffProvider::Var::LPT, pt_lep*1e-3, true);
      er = TMath::Sqrt(er);
    } else {
      ef = m_fakeEff->GetEfficiency2D(FakeEffProvider::Var::TWODIM_PT_ETA, pt_lep*1e-3, abs(eta_lep), true);
      ef *= m_fakeEff->GetEfficiency2D(FakeEffProvider::Var::TWODIM_DPHI_ETA, abs(dPhi_met_lep), abs(eta_lep), true);
      ef  = TMath::Sqrt(ef);
      ef *= m_fakeEff->GetEfficiency(FakeEffProvider::Var::NJETS, njets, true);
      ef /= m_fakeEff->GetAverageEfficiency();
      
      er = m_realEff->GetEfficiency(FakeEffProvider::Var::LPT, pt_lep*1e-3, true);
    }
    ef_lowpt = ef;
    er_lowpt = er;
    
    // MERGE LOW- AND HIGH-PT
    double x = pt_lep*1e-3;
    double fhigh = 1./(1+exp(-(x-150.)/20.));
    ef = (1.-fhigh)*ef_lowpt + fhigh*ef_highpt;
    er = (1.-fhigh)*er_lowpt + fhigh*er_highpt;
    
  // END OF ELECTRON EFFICIENCIES
    
  }
  

  else if( m_channel == 1)
  {
    if (tight) delta = 1.0;
    double pt_lep = ed->muons.pT.at(0);
    double phi_lep = ed->muons.phi.at(0);
    double dPhi_met_lep = deltaPhi( phi_met, phi_lep );
    
    ef  = m_fakeEff->GetEfficiency(FakeEffProvider::Var::DPHILMET, abs(dPhi_met_lep),true);
    ef *= m_fakeEff->GetEfficiency(FakeEffProvider::Var::LPT, pt_lep*1e-3, true);
    ef =  TMath::Sqrt(ef);
    
    er =  m_realEff->GetEfficiency(FakeEffProvider::Var::DPHILMET, abs(dPhi_met_lep),true);
    er *= m_realEff->GetEfficiency(FakeEffProvider::Var::LPT, pt_lep*1e-3, true);
    er =  TMath::Sqrt(er);
    
  // END OF MUON EFFICIENCIES

  }
  double fakesWeight = (ef)*(er-delta)/(er-ef);
  if(fakesWeight == 0) {
    cout<<ed->electrons.eta.at(0)<<endl;
    cout<<" er "<<er<<" ef "<<ef<<endl;
    
  }
  return fakesWeight;
}

double ScalerFakes::GetFakesWeightMMM( EventData * ed)
{
  //get dphi lep met	
 
  double qcd_weight = 1;
  if( m_channel == 0 && ed->electrons.n < 1 ) return qcd_weight;
  if( m_channel == 1 && ed->muons.n < 1 ) return qcd_weight;
  
  
  double phi_met = ed->MET.phi;		
  double met = ed->MET.et;		
  
  int ntag = ed->bjets.n;
  double ef = 0, er = 0, et = 0;
  if( m_channel == 0 ) //electrons case
  {
    
    ef =  m_fakeEff->GetEfficiency(FakeEffProvider::Var::NBTAG, ntag, true);
    ef *= m_fakeEff->GetEfficiency(FakeEffProvider::Var::MET, met*1e-3, true);
    ef =  TMath::Sqrt(ef);
    
    er =  m_realEff->GetEfficiency(FakeEffProvider::Var::NBTAG, ntag, true);
    er *= m_realEff->GetEfficiency(FakeEffProvider::Var::MET, met*1e-3, true);
    er =  TMath::Sqrt(er);
   
    
    et =  m_tightEff->GetEfficiency(FakeEffProvider::Var::NBTAG, ntag, true);
    et *= m_tightEff->GetEfficiency(FakeEffProvider::Var::MET, met*1e-3, true);
    et =  TMath::Sqrt(et);
   
  }
  else if( m_channel == 1)
  {
    
    double pt_lep = ed->muons.pT.at(0);
    double phi_lep = ed->muons.phi.at(0);
    double dPhi_met_lep = deltaPhi( phi_met, phi_lep );
    
    ef =  m_fakeEff->GetEfficiency(FakeEffProvider::Var::DPHILMET, dPhi_met_lep, true);
    ef *= m_fakeEff->GetEfficiency(FakeEffProvider::Var::MET, met*1e-3, true);
    ef *= m_fakeEff->GetEfficiency(FakeEffProvider::Var::LPT, pt_lep*1e-3, true);
    ef *= m_fakeEff->GetEfficiency(FakeEffProvider::Var::NBTAG, ntag, true);
    ef =  TMath::Power(ef,0.25);
    
    er =  m_realEff->GetEfficiency(FakeEffProvider::Var::DPHILMET, dPhi_met_lep, true);
    er *= m_realEff->GetEfficiency(FakeEffProvider::Var::MET, met*1e-3, true);
    er *= m_realEff->GetEfficiency(FakeEffProvider::Var::LPT, pt_lep*1e-3, true);
    er *= m_realEff->GetEfficiency(FakeEffProvider::Var::NBTAG, ntag, true);
    er =  TMath::Power(er,0.25);
    
    et =  m_tightEff->GetEfficiency(FakeEffProvider::Var::DPHILMET, dPhi_met_lep, true);
    et *= m_tightEff->GetEfficiency(FakeEffProvider::Var::MET, met*1e-3, true);
    et *= m_tightEff->GetEfficiency(FakeEffProvider::Var::LPT, pt_lep*1e-3, true);
    et *= m_tightEff->GetEfficiency(FakeEffProvider::Var::NBTAG, ntag, true);
    et =  TMath::Power(et,0.25);
  }
  double fakesWeight = (ef/et)*(er-et)/(er-ef);
 
  return qcd_weight*=fakesWeight;
}