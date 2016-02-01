#ifndef __SCALER_FAKES_H__
#define __SCALER_FAKES_H__

#include "Commons.h"
#include "EventData.h"
#include "PhysicsHelperFunctions.h"
//Rafal Code
#include "FakeEffProvider.h"


class ScalerFakes
{
	private:
		ScalerFakes( int channel, int m_nParameters, string m_method );
		int m_channel;
		FakeEffProvider * m_fakeEff, * m_realEff, *m_tightEff;
		int m_nParameters;
		string m_method;
		static ScalerFakes * m_instance;
		
	public:
		virtual ~ScalerFakes();
		static ScalerFakes * GetHandle( int channel, int m_nParameters = 2, string m_method = "MM" );
		int GetChannel() { return m_channel;};
		int GetNParameters(){ return m_nParameters;};
		double GetFakesWeight(  EventData * ed );
		double GetFakesWeightMM(  EventData * ed );
		double GetFakesWeightMMM(  EventData * ed );
};



#endif