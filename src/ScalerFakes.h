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
		ScalerFakes( int channel, int m_nParameters );
		int m_channel;
		FakeEffProvider * m_fakeEff, * m_realEff;
		int m_nParameters;
		static ScalerFakes * m_instance;
		
	public:
		virtual ~ScalerFakes();
		static ScalerFakes * GetHandle( int channel, int m_nParameters = 2);
		int GetChannel() { return m_channel;};
		int GetNParameters(){ return m_nParameters;};
		double GetFakesWeight(  EventData * ed );		
};



#endif