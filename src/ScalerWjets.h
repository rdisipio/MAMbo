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
		TH2D * m_CA_weights;
		TH2D * m_Kbb_weights;
		TH2D * m_Kc_weights;
		TH2D * m_Klight_weights;
		static ScalerWjets * m_instance;
		string m_systematic;
		string m_CA_systematic;
		string m_Kbb_systematic;
		string m_Kc_systematic;
		string m_Klight_systematic;
                std::vector<int> m_lightList;
                std::vector<int> m_bList;


		
	public:
		virtual ~ScalerWjets();
		static ScalerWjets * GetHandle( int channel, std::string syst = "nominal" );
		int GetChannel() { return m_channel;};
		std::string GetSystematic() { return m_systematic;};
		double GetWjetsWeight(  EventData *);
};



#endif