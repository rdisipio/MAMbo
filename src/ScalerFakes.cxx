#include "ScalerFakes.h"
#include "Commons.h"
#include "EventData.h"

//Rafal Code
#include "FakeEffProvider.h"
using namespace PhysicsHelperFunctions;



ScalerFakes * ScalerFakes::m_instance = NULL;
ScalerFakes::ScalerFakes( int channel, int nParameters )
{
	m_channel = channel;
	m_nParameters = nParameters;
	m_fakeEff = new  FakeEffProvider( m_channel,  FakeEffProvider::Type::fakeEff);
	m_realEff = new  FakeEffProvider( m_channel,  FakeEffProvider::Type::realEff);
}


ScalerFakes::~ScalerFakes( )
{
	delete m_fakeEff;
	delete m_realEff;
}

ScalerFakes * ScalerFakes::GetHandle( int channel, int nParameters )
{
   if( m_instance == NULL ) m_instance = new ScalerFakes( channel, nParameters );
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



double ScalerFakes::GetFakesWeight( EventData * ed)
{
    //get dphi lep met	
	double qcd_weight = 1;
    if( m_channel == 0 && ed->electrons.n < 1 ) return qcd_weight;
    if( m_channel == 1 && ed->muons.n < 1 ) return qcd_weight;
	const bool tight = ( m_channel == 0 ) ? ed->electrons.property["tight"].at(0) : ed->muons.property["tight"].at(0);
	double phi_lep = ed->electrons.phi.at(0);
	double phi_met = ed->MET.phi;		
	double dPhi_met_lep = deltaPhi( phi_met, phi_lep );
	double delta = 0, ef = 0, er = 0;
	if( m_channel == 0 ) //electrons case
	{
		int ntag = ed->bjets.n;
		if( tight ) delta = 1;
		if( m_nParameters == 2)
		{
			ef = m_fakeEff->GetEfficiency( FakeEffProvider::Var::DPHILMET,dPhi_met_lep ) ;
			ef *= m_fakeEff->GetEfficiency( FakeEffProvider::Var::NBTAG, ntag, true );
			ef = TMath::Sqrt( ef );
			er = m_realEff->GetEfficiency( FakeEffProvider::Var::DPHILMET,dPhi_met_lep ) ;
			er *= m_realEff->GetEfficiency( FakeEffProvider::Var::NBTAG, ntag, true );
			er = TMath::Sqrt( er );
			
		}
		else if( m_nParameters == 4 )
		{
			double pt_lep = ed->electrons.pT.at(0);
			double eta_lep = ed->electrons.eta.at(0);
		   	ef = m_fakeEff->GetEfficiency( FakeEffProvider::Var::DPHILMET,dPhi_met_lep ) ;
			ef *= m_fakeEff->GetEfficiency( FakeEffProvider::Var::NBTAG, ntag, true );
			ef *= m_fakeEff->GetEfficiency( FakeEffProvider::Var::LPT, pt_lep);
			ef *= m_fakeEff->GetEfficiency( FakeEffProvider::Var::LETA, eta_lep,true);
			ef = TMath::Power( ef, 0.25 );
			er = m_realEff->GetEfficiency( FakeEffProvider::Var::DPHILMET,dPhi_met_lep ) ;
			er *= m_realEff->GetEfficiency( FakeEffProvider::Var::NBTAG, ntag, true );
			er *= m_realEff->GetEfficiency( FakeEffProvider::Var::LPT, pt_lep);
			er *= m_realEff->GetEfficiency( FakeEffProvider::Var::LETA, eta_lep, true);
			er = TMath::Power( er, 0.25 );
		}
	}
	else if( m_channel == 1)
	{
		if (tight) delta = 1.0;
		double met = ed->MET.et;		
		ef =  m_fakeEff->GetEfficiency( FakeEffProvider::Var::DPHILMET, dPhi_met_lep);
		ef *= m_fakeEff->GetEfficiency( FakeEffProvider::Var::MET, met*1e-3);
		ef =  TMath::Sqrt(ef);

		er =  m_realEff->GetEfficiency( FakeEffProvider::Var::DPHILMET, dPhi_met_lep);
		er *= m_realEff->GetEfficiency( FakeEffProvider::Var::MET, met*1e-3);
		er =  TMath::Sqrt(er);
	}
	qcd_weight = ef * ( er - delta ) / ( er - ef );
	return qcd_weight;
}