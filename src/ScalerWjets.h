#ifndef __SCALER_Wjets_H__
#define __SCALER_Wjets_H__

#include "Commons.h"
#include "EventData.h"
#include "PhysicsHelperFunctions.h"

class ScalerWjets
{
	private:
		ScalerWjets( int channel, std::string syst = "nominal" );
		int m_channel;
		TFile * m_weightsFile;
		std::string  m_weightsFilename;
		TH2D * m_weights;
		static ScalerWjets * m_instance;
		string m_systematic;
		
	public:
		virtual ~ScalerWjets();
		static ScalerWjets * GetHandle( int channel, std::string syst = "nominal" );
		int GetChannel() { return m_channel;};
		std::string GetSystematic() { return m_systematic;};
		double GetWjetsWeight(  int njets, int nbjets );
};



#endif