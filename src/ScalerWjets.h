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
		static ScalerWjets * m_instance;
		string m_systematic;
		std::vector<double> m_weights;
                std::vector<int> m_lightList;
                std::vector<int> m_bList;
		
		unsigned const int m_CA=0;
		unsigned const int m_Kbb=0;
                unsigned const int m_Kc=1;
		unsigned const int m_Klight=2;
		double m_HF_weight = 0.;
                double m_CA_weight = 0.;
		
	public:
		virtual ~ScalerWjets();
		static ScalerWjets * GetHandle( int channel, std::string syst = "nominal" );
		int GetChannel() { return m_channel;};
		std::string GetSystematic() { return m_systematic;};
		double GetWjetsWeight(  EventData *);
		std::vector<double> GetWJetsSF(std::string Folder, bool isEl);
		double GetCA(){return m_CA_weight;};
		double GetHF(){return m_HF_weight;};
};



#endif
