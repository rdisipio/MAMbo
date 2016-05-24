#include "ScalerFakes.h"
#include "Commons.h"
#include "EventData.h"

//Rafal Code
#include "FakeEffProvider.h"
using namespace PhysicsHelperFunctions;
using namespace std;


ScalerFakes * ScalerFakes::m_instance = NULL;
ScalerFakes::ScalerFakes( int channel, string systematic)
{
  m_channel = channel;
  m_systematic = systematic;


  int syst_fakeEff = FakeEffProvider::Systematic::nominal;
  int syst_realEff = FakeEffProvider::Systematic::nominal;
  if (m_systematic.compare("fakes_realEff_stat_D")==0)
    syst_realEff = FakeEffProvider::Systematic::stat_D;
  else if (m_systematic.compare("fakes_realEff_stat_U")==0)
    syst_realEff = FakeEffProvider::Systematic::stat_U;
  else if (m_systematic.compare("fakes_fakeEff_stat_D")==0)
    syst_fakeEff = FakeEffProvider::Systematic::stat_D;
  else if (m_systematic.compare("fakes_fakeEff_stat_U")==0)
    syst_fakeEff = FakeEffProvider::Systematic::stat_U;
  else if (m_systematic.compare("fakes_fakeEff_MCscale_D")==0)
    syst_fakeEff = FakeEffProvider::Systematic::fakeEff_MCscale_D;
  else if (m_systematic.compare("fakes_fakeEff_MCscale_U")==0)
    syst_fakeEff = FakeEffProvider::Systematic::fakeEff_MCscale_U;
  else if (m_systematic.compare("fakes_fakeEff_CR_S")==0)
    syst_fakeEff = FakeEffProvider::Systematic::fakeEff_CR_S;
  else if (m_systematic.compare("nominal")!=0)
    Warning("NominalSelector::Begin", "Unrecognised NominalSelector Systematic option! Nominal will be used.");
  
  cout << "Calling new FakeEffProvider(m_channel, FakeEffProvider::Type::fakeEff, syst_fakeEff) with paramters " << m_channel << " " << FakeEffProvider::Type::fakeEff << " " <<   syst_fakeEff << endl;
  m_fakeEff  = new FakeEffProvider(m_channel, FakeEffProvider::Type::fakeEff, syst_fakeEff);
  m_realEff  = new FakeEffProvider(m_channel, FakeEffProvider::Type::realEff, syst_realEff);
  
}


ScalerFakes::~ScalerFakes( )
{
  delete m_fakeEff;
  delete m_realEff;
  //delete m_tightEff;
}

ScalerFakes * ScalerFakes::GetHandle( int channel, string systematic )
{
  if( m_instance == NULL ) m_instance = new ScalerFakes( channel, systematic );
  else
  {
    if( channel != m_instance->GetChannel()  || systematic !=  m_instance->GetSystematic()) 
    {
      char msg[100];
      sprintf( msg,"ScalerFakes requested  with channel == %i and systematic == %s \
      but an instance already exists with channel == %i and systematic == %s\n", channel, systematic.c_str(),  m_instance->GetChannel(),  m_instance->GetSystematic().c_str() );
      throw std::runtime_error( msg );
    }
  }
  return m_instance;
}


ScalerFakes * ScalerFakes::GetHandle( int channel, int nParamters, string systematic )
{
	cerr << "WARNING: calling depreacted function\nScalerFakes * ScalerFakes::GetHandle( int channel, int nParamters, string systematic ).\n Falling back to ScalerFakes * ScalerFakes::GetHandle( int channel, string systematic )\n";
	return GetHandle( channel, systematic );
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
  
  return GetFakesWeightMM(ed);

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
  double dPhi_met_lep = -1;
  double pt_lep = -1;
  double eta_lep = -1000;
  
  if( m_channel == 0 ) //electrons case
  {
    
    if (tight) delta = 1.0;
	pt_lep = ed->electrons.pT.at(0);
    eta_lep =ed->electrons.eta.at(0);
    double phi_lep = ed->electrons.phi.at(0);
    dPhi_met_lep = deltaPhi( phi_met, phi_lep );
    double ef_highpt=0;
    double er_highpt=0;
       
    ef = m_fakeEff->GetEfficiency2D(FakeEffProvider::Var::TWODIM_PT_NBTAG_G1J, pt_lep*1e-3, nbtag, true);
    ef *= m_fakeEff->GetEfficiency2D(FakeEffProvider::Var::TWODIM_DPHI_ETA_G1J, abs(dPhi_met_lep), abs(eta_lep), true);
    ef *= m_fakeEff->GetEfficiency2D(FakeEffProvider::Var::TWODIM_PT_DPHI_G1J, pt_lep*1e-3, abs(dPhi_met_lep), true);
    ef  = TMath::Power(ef,1./3);
           
    er = m_realEff->GetEfficiency(FakeEffProvider::Var::LPT, pt_lep*1e-3, true);
	
	
	
	
    
  // END OF ELECTRON EFFICIENCIES
    
  }
  

  else if( m_channel == 1)
  {
    if (tight) delta = 1.0;
    pt_lep = ed->muons.pT.at(0);
    double phi_lep = ed->muons.phi.at(0);
    eta_lep =ed->muons.eta.at(0);
    dPhi_met_lep = deltaPhi( phi_met, phi_lep );
    
 // HIGH-PT EFFICIENCIES
    double ef_highpt=0;
    double er_highpt=0;
    ef = m_fakeEff->GetEfficiency(FakeEffProvider::Var::LPT_G1J, pt_lep*1e-3, true);
    ef_highpt = ef;
    
    er = m_realEff->GetEfficiency(FakeEffProvider::Var::LPT, pt_lep*1e-3, true);
    er_highpt = er;
    
    // LOW-PT EFFICIENCIES
    double ef_lowpt=0;
    double er_lowpt=0;
    ef  = m_fakeEff->GetEfficiency(FakeEffProvider::Var::MET_G1J, met*1e-3, true);
    ef *= m_fakeEff->GetEfficiency2D(FakeEffProvider::Var::TWODIM_PT_DPHI_G1J, pt_lep*1e-3, abs(dPhi_met_lep), true);
    ef =  TMath::Sqrt(ef);
    ef_lowpt = ef;
    
    
    er =  m_realEff->GetEfficiency(FakeEffProvider::Var::DPHILMET, abs(dPhi_met_lep),true);
    er *= m_realEff->GetEfficiency(FakeEffProvider::Var::LPT, pt_lep*1e-3, true);
    er =  TMath::Sqrt(er);
    er_lowpt = er;
    
    // MERGE LOW- AND HIGH-PT
    double x = pt_lep*1e-3;
    double fhigh = 1./(1+exp(-(x-60.)/10.));
    ef = (1.-fhigh)*ef_lowpt + fhigh*ef_highpt;
    er = (1.-fhigh)*er_lowpt + fhigh*er_highpt;
    
  // END OF MUON EFFICIENCIES
    
  // END OF MUON EFFICIENCIES

  }
  
    // some tricks to correct unphysical efficiency values -- should be rare!
  if (ef>1) {
    ef = 1;
  }
  if (er>1) {
    er = 1;
  }
  if (ef>=0.99*er) {
    ef = 0.99*er;
  }
  double fakesWeight = (ef)*(er-delta)/(er-ef);
  //cout << "Debug: " << ed->info.runNumber << " " << ed->info.eventNumber <<
//" " << tight << " " << njets << " " << nbtag << " " << pt_lep*1e-3 << " " << abs(eta_lep) << " " <<  abs(dPhi_met_lep) <<  " " << ef <<  " " << er << " "  <<fakesWeight << endl;
  if(fakesWeight == 0) {
    cout<<ed->electrons.eta.at(0)<<endl;
    cout<<" er "<<er<<" ef "<<ef<<endl;
    
  }
  return fakesWeight;
}

double ScalerFakes::GetFakesWeightMMM( EventData * ed)
{
	throw std::runtime_error( "Function GetFakesWeightMMM is depecrated" );
	return 1;
  //get dphi lep met	
 
  // double qcd_weight = 1;
  // if( m_channel == 0 && ed->electrons.n < 1 ) return qcd_weight;
  // if( m_channel == 1 && ed->muons.n < 1 ) return qcd_weight;
  
  
  // double phi_met = ed->MET.phi;		
  // double met = ed->MET.et;		
  
  // int ntag = ed->bjets.n;
  // double ef = 0, er = 0, et = 0;
  // if( m_channel == 0 ) //electrons case
  // {
    
    // ef =  m_fakeEff->GetEfficiency(FakeEffProvider::Var::NBTAG, ntag, true);
    // ef *= m_fakeEff->GetEfficiency(FakeEffProvider::Var::MET, met*1e-3, true);
    // ef =  TMath::Sqrt(ef);
    
    // er =  m_realEff->GetEfficiency(FakeEffProvider::Var::NBTAG, ntag, true);
    // er *= m_realEff->GetEfficiency(FakeEffProvider::Var::MET, met*1e-3, true);
    // er =  TMath::Sqrt(er);
   
    
    // et =  m_tightEff->GetEfficiency(FakeEffProvider::Var::NBTAG, ntag, true);
    // et *= m_tightEff->GetEfficiency(FakeEffProvider::Var::MET, met*1e-3, true);
    // et =  TMath::Sqrt(et);
   
  // }
  // else if( m_channel == 1)
  // {
    
    // double pt_lep = ed->muons.pT.at(0);
    // double phi_lep = ed->muons.phi.at(0);
    // double dPhi_met_lep = deltaPhi( phi_met, phi_lep );
    
    // ef =  m_fakeEff->GetEfficiency(FakeEffProvider::Var::DPHILMET, dPhi_met_lep, true);
    // ef *= m_fakeEff->GetEfficiency(FakeEffProvider::Var::MET, met*1e-3, true);
    // ef *= m_fakeEff->GetEfficiency(FakeEffProvider::Var::LPT, pt_lep*1e-3, true);
    // ef *= m_fakeEff->GetEfficiency(FakeEffProvider::Var::NBTAG, ntag, true);
    // ef =  TMath::Power(ef,0.25);
    
    // er =  m_realEff->GetEfficiency(FakeEffProvider::Var::DPHILMET, dPhi_met_lep, true);
    // er *= m_realEff->GetEfficiency(FakeEffProvider::Var::MET, met*1e-3, true);
    // er *= m_realEff->GetEfficiency(FakeEffProvider::Var::LPT, pt_lep*1e-3, true);
    // er *= m_realEff->GetEfficiency(FakeEffProvider::Var::NBTAG, ntag, true);
    // er =  TMath::Power(er,0.25);
    
    // et =  m_tightEff->GetEfficiency(FakeEffProvider::Var::DPHILMET, dPhi_met_lep, true);
    // et *= m_tightEff->GetEfficiency(FakeEffProvider::Var::MET, met*1e-3, true);
    // et *= m_tightEff->GetEfficiency(FakeEffProvider::Var::LPT, pt_lep*1e-3, true);
    // et *= m_tightEff->GetEfficiency(FakeEffProvider::Var::NBTAG, ntag, true);
    // et =  TMath::Power(et,0.25);
  // }
  // double fakesWeight = (ef/et)*(er-et)/(er-ef);
 
  // return qcd_weight*=fakesWeight;
}
