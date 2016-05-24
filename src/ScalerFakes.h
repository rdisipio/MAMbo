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
		ScalerFakes( int channel, std::string systematic = "nominal" );
		ScalerFakes( int channel, int nparamters, std::string systematic = "nominal" ){};
		int m_channel;
		FakeEffProvider * m_fakeEff, * m_realEff, *m_tightEff;
		std::string m_systematic;
		static ScalerFakes * m_instance;
		
	public:
		virtual ~ScalerFakes();
		static ScalerFakes * GetHandle( int channel, std::string systematic = "nominal" );
		static ScalerFakes * GetHandle( int channel, int nParameters, std::string systematic = "nominal" );
		int GetChannel() { return m_channel;};
		string GetSystematic(){ return m_systematic;};
		double GetFakesWeight(  EventData * ed );
		double GetFakesWeightMM(  EventData * ed );
		double GetFakesWeightMMM(  EventData * ed ); //depecrated
};



#endif