#include "ScalerWjets.h"
#include "Commons.h"
#include "EventData.h"

using namespace PhysicsHelperFunctions;



ScalerWjets * ScalerWjets::m_instance = NULL;
ScalerWjets::ScalerWjets( int channel, string syst )
{
        m_channel = channel;
        m_systematic = syst;
        cout << "DEBUG: initializing wjets weights interface for channel " << (channel == 0 ? "el" : "mu") << " and systematic " << syst << "\n";
	bool isEl(m_channel == 0);
	m_weights = GetWJetsSF(m_systematic,isEl);
        
        cout << "ScalerWjets: adding runs to light run list\n";
        
        m_lightList.push_back(361300);
        m_lightList.push_back(361303);
        m_lightList.push_back(361306);
        m_lightList.push_back(361309);
        m_lightList.push_back(361312);
        m_lightList.push_back(361315);
        m_lightList.push_back(361318);
        m_lightList.push_back(361321);
        m_lightList.push_back(361324);
        m_lightList.push_back(361327);
        m_lightList.push_back(361330);
        m_lightList.push_back(361333);
        m_lightList.push_back(361336);
        m_lightList.push_back(361339);
        m_lightList.push_back(361342);
        m_lightList.push_back(361345);
        m_lightList.push_back(361348);
        m_lightList.push_back(361351);
        m_lightList.push_back(361354);
        m_lightList.push_back(361357);
        m_lightList.push_back(361360);
        m_lightList.push_back(361363);
        m_lightList.push_back(361366);
        m_lightList.push_back(361369);
        cout << "Added " << m_lightList.size() << " runs\n";
        
        
        cout << "ScalerWjets: adding runs to b run list\n";

        m_bList.push_back(361302);
        m_bList.push_back(361305);
        m_bList.push_back(361308);
        m_bList.push_back(361311);
        m_bList.push_back(361314);
        m_bList.push_back(361317);
        m_bList.push_back(361320);
        m_bList.push_back(361323);
        m_bList.push_back(361326);
        m_bList.push_back(361329);
        m_bList.push_back(361332);
        m_bList.push_back(361335);
        m_bList.push_back(361338);
        m_bList.push_back(361341);
        m_bList.push_back(361344);
        m_bList.push_back(361347);
        m_bList.push_back(361350);
        m_bList.push_back(361353);
        m_bList.push_back(361356);
        m_bList.push_back(361359);
        m_bList.push_back(361362);
        m_bList.push_back(361365);
        m_bList.push_back(361368);
        m_bList.push_back(361371);        
        cout << "Added " << m_bList.size() << " runs\n";
        
        
}


ScalerWjets::~ScalerWjets( )
{
        //delete m_tightEff;
}

ScalerWjets * ScalerWjets::GetHandle( int channel, string syst )
{
        if( m_instance == NULL ) m_instance = new ScalerWjets( channel, syst );
        else
        {
                if( channel != m_instance->GetChannel()  || syst != m_instance->GetSystematic() ) 
                {
                        char msg[100];
                        sprintf( msg,"ScalerWjets requested  with channel == %i and syst == %s \
but an instance already exists with channel == %i and syst == %si\n", channel, syst.c_str(),  m_instance->GetChannel(),  m_instance->GetSystematic().c_str() );
                        throw std::runtime_error( msg );
                }
        }
        return m_instance;
}
/*
double ScalerWjets::GetWjetsWeight( int njets, int nbjets){

        int x = njets <= 4 ? njets+1 : 5;
        int y = nbjets <= 1 ? nbjets+1 : 2;
        return m_weights->GetBinContent( x, y );

}
*/
double ScalerWjets::GetWjetsWeight( EventData * ed){

        int njets = ed->jets.n;
        int nbjets = ed->bjets.n;
        int is_WplusC = (int) ed->property[ "is_WplusC"];
        int is_WplusCC = (int) ed->property[ "is_WplusCC"];
        int isB     = ( std::find(m_bList.begin(), m_bList.end(),  ed->info.mcChannelNumber) != m_bList.end() );
        int isLight = ( std::find(m_lightList.begin(), m_lightList.end(),  ed->info.mcChannelNumber) != m_lightList.end() );
        //check coherence of the flags
        if( ( is_WplusC && is_WplusCC ) || (isLight && (is_WplusC || is_WplusCC || isB )  ) )
        {
                 //char msg[100];
                printf(  "ScalerWjets::GetWjetsWeight - WARNING: inconsistent HF flags for event %i, run number %i.\n is_WplusC = %i, is_WplusCC = %i, is_WplusB = %i, isLight = %i. Only one of these flags can be true.\n",  ed->info.eventNumber, ed->info.mcChannelNumber, is_WplusC, is_WplusCC, isB, isLight );
                // throw runtime_error( msg );
				//print only a warning
				

        }
        int x = njets < 4 ? 3*(1+njets%2) : 9;
	int xCA = njets <= 4 ? njets-2 : 2;
	std::cout<<"Njet "<<njets<<" Nbjet"<<nbjets<<std::endl;
	
	std::vector<double> EventWeights = m_weights;
	
	if( nbjets < 1 || njets < 2 ) 
	{ 
	   if( m_systematic == "CA_up" ) return 1.5;
           if( m_systematic == "CA_down" ) return 0.5;
           return 1; 
	}
	
	double CA_weight = EventWeights[xCA];
        double HF_weight = 1;
        if( is_WplusC ) HF_weight = EventWeights[m_Kc+x];
        else if( is_WplusCC || isB ) HF_weight = EventWeights[m_Kbb+x];
        else if( isLight ) HF_weight = EventWeights[m_Klight+x];
	
	m_CA_weight=CA_weight;
	m_HF_weight=HF_weight;
	std::cout<<std::endl<<"Weights "<<CA_weight<<" "<<HF_weight<<std::endl;
        return CA_weight * HF_weight;
}

std::vector<double> ScalerWjets::GetWJetsSF(std::string Folder, bool isEl){

  //[CA_2excl, CA_3excl, CA_4incl, Fcc_2excl, Fc_2excl, Flight_2excl,
//Fcc_3excl, Fc_3excl, Flight_3excl, Fcc_4incl, Fc_4incl, Flight_4incl]

  std::vector<double> Output(6);

  if(isEl){

  if(Folder == "MET_SoftTrk_ResoPara")
      Output = {0.96,0.824,0.948,1.004,0.924,1.024,1.007,0.927,1.027,1.009,0.929,1.029};
    else if(Folder == "MET_SoftTrk_ResoPerp")
      Output = {0.97,0.826,0.96,0.876,0.978,1.027,0.883,0.986,1.035,0.893,0.998,1.047};
    else if(Folder == "MET_SoftTrk_ScaleUp")
      Output = {0.966,0.828,0.956,0.908,0.97,1.024,0.914,0.976,1.031,0.923,0.985,1.04};
    else if(Folder == "MET_SoftTrk_ScaleDown")
      Output = {0.963,0.825,0.959,0.898,0.96,1.029,0.905,0.967,1.037,0.914,0.977,1.048};
    else if(Folder == "EG_SCALE_ALL__1up")
      Output = {0.958,0.819,0.953,0.877,0.982,1.026,0.884,0.989,1.034,0.894,1.001,1.046};
    else if(Folder == "EG_SCALE_ALL__1down")
      Output = {0.97,0.829,0.962,0.933,0.949,1.027,0.939,0.955,1.033,0.946,0.962,1.041};
    else if(Folder == "EG_RESOLUTION_ALL__1up")
      Output = {0.97,0.827,0.958,0.81,1.004,1.029,0.819,1.015,1.04,0.833,1.032,1.058};
    else if(Folder == "EG_RESOLUTION_ALL__1down")
      Output = {0.963,0.828,0.953,0.913,0.964,1.026,0.919,0.97,1.032,0.927,0.979,1.041};
    else if(Folder == "MUONS_ID__1up")
      Output = {0.967,0.824,0.959,0.896,0.964,1.028,0.903,0.971,1.036,0.913,0.981,1.047};
    else if(Folder == "MUONS_ID__1down")
      Output = {0.967,0.824,0.959,0.895,0.964,1.028,0.902,0.972,1.036,0.912,0.982,1.047};
    else if(Folder == "MUONS_MS__1up")
      Output = {0.967,0.824,0.959,0.896,0.964,1.028,0.903,0.971,1.036,0.913,0.981,1.047};
    else if(Folder == "MUONS_MS__1down")
      Output = {0.967,0.824,0.959,0.896,0.964,1.028,0.903,0.971,1.036,0.912,0.982,1.047};
    else if(Folder == "MUONS_SCALE__1up")
      Output = {0.967,0.824,0.959,0.896,0.964,1.028,0.903,0.971,1.036,0.912,0.982,1.047};
    else if(Folder == "MUONS_SCALE__1down")
      Output = {0.967,0.824,0.959,0.896,0.964,1.028,0.903,0.971,1.036,0.912,0.982,1.047};
    else if(Folder == "JET_JER_SINGLE_NP__1up")
      Output = {0.974,0.83,0.979,0.272,1.252,1.037,0.28,1.289,1.068,0.297,1.368,1.133};
    else if(Folder == "JET_19NP_JET_BJES_Response__1up")
      Output = {0.966,0.825,0.958,0.891,0.963,1.029,0.898,0.97,1.037,0.908,0.981,1.049};
    else if(Folder == "JET_19NP_JET_BJES_Response__1down")
      Output = {0.964,0.822,0.953,0.975,0.934,1.025,0.979,0.938,1.03,0.983,0.942,1.034};
    else if(Folder == "JET_19NP_JET_EffectiveNP_1__1up")
      Output = {0.927,0.776,0.836,0.564,1.152,1.021,0.574,1.172,1.038,0.594,1.213,1.075};
    else if(Folder == "JET_19NP_JET_EffectiveNP_1__1down")
      Output = {1.028,0.952,1.156,0.597,1.07,1.044,0.609,1.092,1.066,0.632,1.133,1.106};
    else if(Folder == "JET_19NP_JET_EffectiveNP_2__1up")
      Output = {0.955,0.87,0.99,0.977,0.959,1.017,0.98,0.962,1.02,0.983,0.965,1.023};
    else if(Folder == "JET_19NP_JET_EffectiveNP_2__1down")
      Output = {0.966,0.822,0.936,0.734,1.044,1.028,0.744,1.058,1.042,0.761,1.082,1.066};
    else if(Folder == "JET_19NP_JET_EffectiveNP_3__1up")
      Output = {0.973,0.825,0.963,0.802,1.001,1.032,0.811,1.012,1.043,0.826,1.03,1.062};
    else if(Folder == "JET_19NP_JET_EffectiveNP_3__1down")
      Output = {0.969,0.828,0.957,0.952,0.937,1.028,0.957,0.942,1.034,0.963,0.948,1.04};
    else if(Folder == "JET_19NP_JET_EffectiveNP_4__1up")
      Output = {0.968,0.826,0.954,0.929,0.949,1.028,0.934,0.955,1.034,0.942,0.963,1.042};
    else if(Folder == "JET_19NP_JET_EffectiveNP_4__1down")
      Output = {0.972,0.825,0.963,0.828,0.988,1.031,0.837,0.999,1.042,0.85,1.015,1.059};
    else if(Folder == "JET_19NP_JET_EffectiveNP_5__1up")
      Output = {0.97,0.822,0.961,0.873,0.969,1.03,0.88,0.977,1.039,0.891,0.989,1.052};
    else if(Folder == "JET_19NP_JET_EffectiveNP_5__1down")
      Output = {0.965,0.819,0.948,0.957,0.937,1.027,0.962,0.941,1.032,0.968,0.947,1.038};
    else if(Folder == "JET_19NP_JET_EffectiveNP_6restTerm__1up")
      Output = {0.97,0.825,0.963,0.856,0.979,1.03,0.864,0.988,1.039,0.875,1.001,1.054};
    else if(Folder == "JET_19NP_JET_EffectiveNP_6restTerm__1down")
      Output = {0.967,0.824,0.955,0.914,0.955,1.028,0.92,0.961,1.035,0.928,0.97,1.045};
    else if(Folder == "JET_19NP_JET_EtaIntercalibration_Modelling__1up")
      Output = {0.954,0.803,0.937,0.756,1.046,1.024,0.765,1.058,1.036,0.781,1.08,1.058};
    else if(Folder == "JET_19NP_JET_EtaIntercalibration_Modelling__1down")
      Output = {0.977,0.907,1.0,0.774,1.034,1.026,0.784,1.046,1.038,0.799,1.067,1.058};
    else if(Folder == "JET_19NP_JET_EtaIntercalibration_NonClosure__1up")
      Output = {0.961,0.85,0.955,0.913,0.968,1.024,0.919,0.975,1.031,0.927,0.983,1.04};
    else if(Folder == "JET_19NP_JET_EtaIntercalibration_NonClosure__1down")
      Output = {0.965,0.825,0.961,0.901,0.966,1.027,0.907,0.973,1.034,0.916,0.983,1.044};
    else if(Folder == "JET_19NP_JET_EtaIntercalibration_TotalStat__1up")
      Output = {0.969,0.818,0.944,0.715,1.053,1.029,0.725,1.068,1.043,0.743,1.094,1.069};
    else if(Folder == "JET_19NP_JET_EtaIntercalibration_TotalStat__1down")
      Output = {0.959,0.865,0.981,1.003,0.937,1.02,1.005,0.939,1.022,1.007,0.941,1.024};
    else if(Folder == "JET_19NP_JET_Flavor_Response__1up")
      Output = {0.975,0.892,1.012,0.773,1.03,1.027,0.782,1.043,1.039,0.798,1.064,1.06};
    else if(Folder == "JET_19NP_JET_Flavor_Response__1down")
      Output = {0.963,0.802,0.932,0.697,1.066,1.027,0.707,1.081,1.042,0.725,1.109,1.069};
    else if(Folder == "JET_19NP_JET_Flavor_Composition__1up")
      Output = {0.925,0.774,0.837,0.588,1.154,1.016,0.597,1.172,1.032,0.616,1.21,1.066};
    else if(Folder == "JET_19NP_JET_Flavor_Composition__1down")
      Output = {1.024,0.965,1.134,0.702,1.0,1.05,0.715,1.018,1.069,0.735,1.047,1.099};
    else if(Folder == "JET_19NP_JET_PunchThrough_MC15__1up")
      Output = {0.967,0.824,0.959,0.897,0.964,1.028,0.903,0.971,1.036,0.913,0.981,1.047};
    else if(Folder == "JET_19NP_JET_PunchThrough_MC15__1down")
      Output = {0.967,0.824,0.959,0.896,0.964,1.028,0.903,0.971,1.036,0.913,0.981,1.047};
    else if(Folder == "JET_19NP_JET_Pileup_PtTerm__1up")
      Output = {0.968,0.832,0.962,0.867,0.976,1.029,0.875,0.984,1.038,0.886,0.997,1.051};
    else if(Folder == "JET_19NP_JET_Pileup_PtTerm__1down")
      Output = {0.965,0.824,0.948,0.94,0.945,1.027,0.946,0.95,1.033,0.952,0.957,1.041};
    else if(Folder == "JET_19NP_JET_Pileup_OffsetNPV__1up")
      Output = {0.967,0.83,0.942,0.97,0.93,1.027,0.974,0.934,1.032,0.979,0.939,1.037};
    else if(Folder == "JET_19NP_JET_Pileup_OffsetNPV__1down")
      Output = {0.958,0.845,0.976,0.9,0.98,1.022,0.906,0.987,1.029,0.915,0.996,1.039};
    else if(Folder == "JET_19NP_JET_Pileup_OffsetMu__1up")
      Output = {0.967,0.834,0.958,0.942,0.947,1.026,0.948,0.953,1.032,0.954,0.959,1.039};
    else if(Folder == "JET_19NP_JET_Pileup_OffsetMu__1down")
      Output = {0.973,0.833,0.964,0.754,1.023,1.032,0.764,1.037,1.045,0.781,1.059,1.068};
    else if(Folder == "JET_19NP_JET_Pileup_RhoTopology__1up")
      Output = {0.966,0.808,0.937,0.59,1.107,1.031,0.601,1.128,1.05,0.622,1.168,1.087};
    else if(Folder == "JET_19NP_JET_Pileup_RhoTopology__1down")
      Output = {0.982,0.893,1.02,0.712,1.055,1.029,0.722,1.071,1.044,0.741,1.098,1.07};
    else if(Folder == "JET_19NP_JET_SingleParticle_HighPt__1up")
      Output = {0.967,0.824,0.959,0.896,0.964,1.028,0.903,0.971,1.036,0.913,0.981,1.047};
    else if(Folder == "JET_19NP_JET_SingleParticle_HighPt__1down")
      Output = {0.967,0.824,0.959,0.896,0.964,1.028,0.903,0.971,1.036,0.913,0.981,1.047};
    else if(Folder == "leptonSF_EL_SF_Trigger_UP")
      Output = {0.96,0.819,0.953,0.894,0.961,1.03,0.901,0.968,1.038,0.91,0.979,1.049};
    else if(Folder == "leptonSF_EL_SF_Trigger_DOWN")
      Output = {0.973,0.829,0.965,0.899,0.967,1.027,0.906,0.974,1.034,0.915,0.984,1.044};
    else if(Folder == "leptonSF_EL_SF_Reco_UP")
      Output = {0.963,0.821,0.955,0.899,0.959,1.029,0.905,0.966,1.037,0.915,0.976,1.048};
    else if(Folder == "leptonSF_EL_SF_Reco_DOWN")
      Output = {0.97,0.827,0.962,0.894,0.969,1.027,0.901,0.976,1.034,0.91,0.986,1.045};
    else if(Folder == "leptonSF_EL_SF_ID_UP")
      Output = {0.958,0.817,0.951,0.895,0.956,1.031,0.902,0.964,1.039,0.912,0.974,1.05};
    else if(Folder == "leptonSF_EL_SF_ID_DOWN")
      Output = {0.975,0.831,0.967,0.898,0.972,1.025,0.904,0.979,1.033,0.913,0.988,1.043};
    else if(Folder == "leptonSF_EL_SF_ID_DOWN")
      Output = {0.975,0.831,0.967,0.898,0.972,1.025,0.904,0.979,1.033,0.913,0.988,1.043};
    else if(Folder == "leptonSF_EL_SF_Isol_UP")
      Output = {0.964,0.822,0.956,0.898,0.96,1.029,0.905,0.967,1.037,0.914,0.977,1.048};
    else if(Folder == "leptonSF_EL_SF_Isol_DOWN")
      Output = {0.969,0.826,0.961,0.895,0.968,1.027,0.901,0.975,1.035,0.911,0.986,1.046};
    else if(Folder == "leptonSF_MU_SF_Trigger_STAT_UP")
      Output = {0.967,0.824,0.959,0.896,0.964,1.028,0.903,0.971,1.036,0.913,0.981,1.047};
    else if(Folder == "leptonSF_MU_SF_Trigger_STAT_DOWN")
      Output = {0.967,0.824,0.959,0.896,0.964,1.028,0.903,0.971,1.036,0.913,0.981,1.047};
    else if(Folder == "leptonSF_MU_SF_Trigger_SYST_UP")
      Output = {0.967,0.824,0.959,0.896,0.964,1.028,0.903,0.971,1.036,0.913,0.981,1.047};
    else if(Folder == "leptonSF_MU_SF_Trigger_SYST_DOWN")
      Output = {0.967,0.824,0.959,0.896,0.964,1.028,0.903,0.971,1.036,0.913,0.981,1.047};
    else if(Folder == "leptonSF_MU_SF_ID_STAT_UP")
      Output = {0.967,0.824,0.959,0.896,0.964,1.028,0.903,0.971,1.036,0.913,0.981,1.047};
    else if(Folder == "leptonSF_MU_SF_ID_STAT_DOWN")
      Output = {0.967,0.824,0.959,0.896,0.964,1.028,0.903,0.971,1.036,0.913,0.981,1.047};
    else if(Folder == "leptonSF_MU_SF_ID_SYST_UP")
      Output = {0.967,0.824,0.959,0.896,0.964,1.028,0.903,0.971,1.036,0.913,0.981,1.047};
    else if(Folder == "leptonSF_MU_SF_ID_SYST_DOWN")
      Output = {0.967,0.824,0.959,0.896,0.964,1.028,0.903,0.971,1.036,0.913,0.981,1.047};
    else if(Folder == "leptonSF_MU_SF_Isol_STAT_UP")
      Output = {0.967,0.824,0.959,0.896,0.964,1.028,0.903,0.971,1.036,0.913,0.981,1.047};
    else if(Folder == "leptonSF_MU_SF_Isol_STAT_DOWN")
      Output = {0.967,0.824,0.959,0.896,0.964,1.028,0.903,0.971,1.036,0.913,0.981,1.047};
    else if(Folder == "leptonSF_MU_SF_Isol_SYST_UP")
      Output = {0.967,0.824,0.959,0.896,0.964,1.028,0.903,0.971,1.036,0.913,0.981,1.047};
    else if(Folder == "leptonSF_MU_SF_Isol_SYST_DOWN")
      Output = {0.967,0.824,0.959,0.896,0.964,1.028,0.903,0.971,1.036,0.913,0.981,1.047};
    else if(Folder == "leptonSF_MU_SF_TTVA_STAT_UP")
      Output = {0.967,0.824,0.959,0.896,0.964,1.028,0.903,0.971,1.036,0.913,0.981,1.047};
    else if(Folder == "leptonSF_MU_SF_TTVA_STAT_DOWN")
      Output = {0.967,0.824,0.959,0.896,0.964,1.028,0.903,0.971,1.036,0.913,0.981,1.047};
    else if(Folder == "leptonSF_MU_SF_TTVA_SYST_UP")
      Output = {0.967,0.824,0.959,0.896,0.964,1.028,0.903,0.971,1.036,0.913,0.981,1.047};
    else if(Folder == "leptonSF_MU_SF_TTVA_SYST_DOWN")
      Output = {0.967,0.824,0.959,0.896,0.964,1.028,0.903,0.971,1.036,0.913,0.981,1.047};
    else if(Folder == "bTagSF_77_extrapolation_up")
      Output = {0.967,0.824,0.959,0.895,0.963,1.029,0.902,0.971,1.036,0.912,0.981,1.047};
    else if(Folder == "bTagSF_77_extrapolation_down")
      Output = {0.967,0.824,0.959,0.898,0.965,1.028,0.904,0.972,1.035,0.914,0.982,1.046};
    else if(Folder == "bTagSF_77_extrapolation_from_charm_up")
      Output = {0.967,0.825,0.961,0.874,0.972,1.029,0.881,0.98,1.038,0.892,0.992,1.051};
    else if(Folder == "bTagSF_77_extrapolation_from_charm_down")
      Output = {0.966,0.823,0.956,0.919,0.956,1.027,0.925,0.962,1.034,0.933,0.97,1.043};
    else if(Folder == "jvt_UP")
      Output = {0.929,0.781,0.898,0.923,0.924,1.037,0.93,0.931,1.045,0.939,0.939,1.055};
    else if(Folder == "jvt_DOWN")
      Output = {1.006,0.87,1.024,0.87,1.004,1.02,0.876,1.011,1.027,0.887,1.023,1.039};
    else if(Folder == "bTagSF_77_eigenvars_B_up_0")
      Output = {0.97,0.827,0.958,0.918,0.987,1.017,0.923,0.993,1.023,0.93,1.0,1.031};
    else if(Folder == "bTagSF_77_eigenvars_B_up_1")
      Output = {0.967,0.825,0.959,0.899,0.97,1.026,0.905,0.977,1.033,0.914,0.987,1.044};
    else if(Folder == "bTagSF_77_eigenvars_B_up_2")
      Output = {0.965,0.823,0.958,0.897,0.956,1.031,0.904,0.964,1.039,0.913,0.974,1.05};
    else if(Folder == "bTagSF_77_eigenvars_B_up_3")
      Output = {0.967,0.824,0.959,0.897,0.964,1.028,0.904,0.971,1.036,0.913,0.981,1.046};
    else if(Folder == "bTagSF_77_eigenvars_B_up_4")
	 Output = {0.967,0.824,0.959,0.896,0.964,1.028,0.903,0.971,1.036,0.912,0.982,1.047};
    else if(Folder == "bTagSF_77_eigenvars_B_down_0")
      Output = {0.963,0.821,0.959,0.877,0.941,1.039,0.886,0.95,1.049,0.897,0.962,1.062};
    else if(Folder == "bTagSF_77_eigenvars_B_down_1")
      Output = {0.966,0.823,0.958,0.894,0.958,1.03,0.901,0.966,1.038,0.911,0.976,1.05};
    else if(Folder == "bTagSF_77_eigenvars_B_down_2")
      Output = {0.968,0.825,0.96,0.896,0.972,1.026,0.902,0.979,1.033,0.912,0.989,1.044};
    else if(Folder == "bTagSF_77_eigenvars_B_down_3")
      Output = {0.967,0.824,0.959,0.895,0.964,1.028,0.902,0.972,1.036,0.912,0.982,1.047};
    else if(Folder == "bTagSF_77_eigenvars_B_down_4")
      Output = {0.967,0.824,0.959,0.897,0.964,1.028,0.903,0.971,1.036,0.913,0.981,1.047};
    else if(Folder == "bTagSF_77_eigenvars_C_up_0")
      Output = {0.988,0.843,0.977,0.841,1.108,0.991,0.845,1.113,0.995,0.854,1.125,1.006};
    else if(Folder == "bTagSF_77_eigenvars_C_up_1")
      Output = {0.964,0.821,0.957,0.896,0.943,1.035,0.904,0.951,1.043,0.914,0.962,1.055};
    else if(Folder == "bTagSF_77_eigenvars_C_up_2")
      Output = {0.964,0.822,0.956,0.915,0.947,1.031,0.922,0.954,1.038,0.93,0.962,1.048};
    else if(Folder == "bTagSF_77_eigenvars_C_up_3")
      Output = {0.968,0.825,0.96,0.893,0.972,1.026,0.899,0.979,1.034,0.909,0.99,1.045};
    else if(Folder == "bTagSF_77_eigenvars_C_down_0")
      Output = {0.95,0.809,0.946,0.922,0.852,1.06,0.932,0.861,1.072,0.943,0.871,1.084};
    else if(Folder == "bTagSF_77_eigenvars_C_down_1")
      Output = {0.97,0.827,0.961,0.896,0.986,1.021,0.902,0.992,1.028,0.911,1.002,1.038};
    else if(Folder == "bTagSF_77_eigenvars_C_down_2")
      Output = {0.969,0.826,0.962,0.877,0.982,1.026,0.884,0.989,1.034,0.894,1.001,1.046};
    else if(Folder == "bTagSF_77_eigenvars_C_down_3")
      Output = {0.966,0.823,0.957,0.9,0.956,1.03,0.907,0.963,1.038,0.916,0.973,1.049};
    else if(Folder == "bTagSF_77_eigenvars_Light_up_0")
      Output = {0.971,0.83,0.946,1.193,1.02,0.963,1.179,1.008,0.951,1.159,0.991,0.935};
    else if(Folder == "bTagSF_77_eigenvars_Light_up_1")
      Output = {0.965,0.822,0.954,0.936,0.949,1.027,0.941,0.955,1.033,0.948,0.962,1.04};
    else if(Folder == "bTagSF_77_eigenvars_Light_up_2")
      Output = {0.966,0.823,0.96,0.883,0.953,1.034,0.89,0.962,1.043,0.901,0.973,1.055};
    else if(Folder == "bTagSF_77_eigenvars_Light_up_3")
      Output = {0.968,0.825,0.961,0.884,0.972,1.028,0.891,0.98,1.036,0.901,0.991,1.047};
    else if(Folder == "bTagSF_77_eigenvars_Light_up_4")
      Output = {0.967,0.824,0.96,0.883,0.967,1.029,0.89,0.975,1.038,0.901,0.986,1.05};
    else if(Folder == "bTagSF_77_eigenvars_Light_up_5")
      Output = {0.966,0.824,0.958,0.906,0.961,1.027,0.912,0.968,1.035,0.921,0.978,1.045};
    else if(Folder == "bTagSF_77_eigenvars_Light_up_6")
      Output = {0.966,0.824,0.958,0.906,0.962,1.027,0.912,0.968,1.035,0.921,0.978,1.045};
    else if(Folder == "bTagSF_77_eigenvars_Light_up_7")
      Output = {0.967,0.824,0.959,0.894,0.966,1.028,0.901,0.974,1.035,0.91,0.984,1.046};
    else if(Folder == "bTagSF_77_eigenvars_Light_up_8")
      Output = {0.967,0.824,0.959,0.89,0.966,1.029,0.897,0.973,1.036,0.907,0.984,1.048};
    else if(Folder == "bTagSF_77_eigenvars_Light_up_9")
      Output = {0.967,0.824,0.959,0.897,0.964,1.028,0.904,0.971,1.036,0.913,0.981,1.046};
    else if(Folder == "bTagSF_77_eigenvars_Light_up_10")
      Output = {0.967,0.824,0.959,0.895,0.965,1.028,0.902,0.972,1.036,0.911,0.982,1.047};
    else if(Folder == "bTagSF_77_eigenvars_Light_up_11")
      Output = {0.967,0.824,0.959,0.896,0.964,1.028,0.903,0.971,1.036,0.912,0.982,1.047};
    else if(Folder == "bTagSF_77_eigenvars_Light_down_0")
      Output = {0.961,0.817,0.969,0.616,0.898,1.095,0.633,0.922,1.124,0.658,0.959,1.169};
    else if(Folder == "bTagSF_77_eigenvars_Light_down_1")
      Output = {0.969,0.826,0.964,0.857,0.979,1.03,0.865,0.988,1.039,0.877,1.001,1.053};
    else if(Folder == "bTagSF_77_eigenvars_Light_down_2")
      Output = {0.968,0.825,0.958,0.91,0.975,1.023,0.916,0.981,1.029,0.924,0.989,1.038};
    else if(Folder == "bTagSF_77_eigenvars_Light_down_3")
      Output = {0.966,0.823,0.956,0.909,0.956,1.029,0.915,0.963,1.036,0.924,0.972,1.046};
    else if(Folder == "bTagSF_77_eigenvars_Light_down_4")
      Output = {0.966,0.824,0.958,0.91,0.961,1.027,0.916,0.968,1.034,0.925,0.977,1.043};
    else if(Folder == "bTagSF_77_eigenvars_Light_down_5")
      Output = {0.967,0.824,0.96,0.887,0.967,1.029,0.894,0.974,1.037,0.904,0.985,1.049};
    else if(Folder == "bTagSF_77_eigenvars_Light_down_6")
      Output = {0.967,0.824,0.959,0.887,0.966,1.029,0.894,0.974,1.037,0.904,0.985,1.049};
    else if(Folder == "bTagSF_77_eigenvars_Light_down_7")
      Output = {0.966,0.824,0.958,0.899,0.962,1.029,0.905,0.969,1.036,0.915,0.979,1.047};
    else if(Folder == "bTagSF_77_eigenvars_Light_down_8")
      Output = {0.966,0.824,0.958,0.903,0.962,1.028,0.909,0.969,1.035,0.918,0.979,1.045};
    else if(Folder == "bTagSF_77_eigenvars_Light_down_9")
      Output = {0.967,0.824,0.959,0.896,0.964,1.028,0.903,0.971,1.036,0.912,0.981,1.047};
    else if(Folder == "bTagSF_77_eigenvars_Light_down_10")
      Output = {0.967,0.824,0.959,0.898,0.963,1.028,0.905,0.971,1.036,0.914,0.981,1.046};
    else if(Folder == "bTagSF_77_eigenvars_Light_down_11")
      Output = {0.967,0.824,0.959,0.897,0.964,1.028,0.904,0.971,1.036,0.913,0.981,1.047};
//     else if(Folder == "CA_up")
//       Output = {1.195, 1.0223, 1.1977, 0.675, 0.698, 1.149, 0.697, 0.721, 1.186, 0.725, 0.75, 1.234};
//     else if (Folder == "CA_down")
//       Output = {1.1674, 0.9917, 1.1487, 0.703, 0.721, 1.137, 0.724, 0.742, 1.171, 0.75, 0.769, 1.214};
//     else if(Folder == "Fcc_up")
//       Output = {1.1723, 0.9991, 1.1655, 0.704, 0.657, 1.158, 0.727, 0.678, 1.195, 0.755, 0.705, 1.242};
//     else if(Folder == "Fcc_down")
//       Output = {1.1901, 1.0149, 1.1814, 0.674, 0.761, 1.129, 0.694, 0.783, 1.162, 0.721, 0.814, 1.207};
//     else if(Folder == "Flight_up")
//       Output = {1.1809, 1.0051, 1.1781, 0.607, 0.707, 1.157, 0.629, 0.733, 1.198, 0.659, 0.767, 1.255};
//     else if(Folder == "Flight_down")
//       Output = {1.1816, 1.0088, 1.169, 0.773, 0.712, 1.129, 0.793, 0.73, 1.158, 0.817, 0.752, 1.193};
     else if(Folder == "CA_2ex_up")
      Output = {0.999,0.824,0.959,0.896,0.964,1.028,0.903,0.971,1.036,0.913,0.981,1.047};
    else if(Folder == "CA_2ex_down")
      Output = {0.935,0.824,0.959,0.896,0.964,1.028,0.903,0.971,1.036,0.913,0.981,1.047};
    else if(Folder == "CA_3ex_up")
      Output = {0.967,0.843,0.959,0.896,0.964,1.028,0.903,0.971,1.036,0.913,0.981,1.047};
    else if(Folder == "CA_3ex_down")
      Output = {0.967,0.805,0.959,0.896,0.964,1.028,0.903,0.971,1.036,0.913,0.981,1.047};
    else if(Folder == "CA_4incl_up")
      Output = {0.967,0.824,0.994,0.896,0.964,1.028,0.903,0.971,1.036,0.913,0.981,1.047};
    else if(Folder == "CA_4incl_down")
      Output = {0.967,0.824,0.924,0.896,0.964,1.028,0.903,0.971,1.036,0.913,0.981,1.047};
    else if(Folder == "Fcc_up")
      Output = {0.967,0.824,0.959,1.337,0.964,1.028,1.347,0.971,1.036,1.362,0.981,1.047};
    else if(Folder == "Fcc_down")
      Output = {0.967,0.824,0.959,0.455,0.964,1.028,0.459,0.971,1.036,0.464,0.981,1.047};
    else if(Folder == "Fc_up")
      Output = {0.967,0.824,0.959,0.896,1.225,1.028,0.903,1.234,1.036,0.913,1.247,1.047};
    else if(Folder == "Fc_down")
      Output = {0.967,0.824,0.959,0.896,0.703,1.028,0.903,0.708,1.036,0.913,0.715,1.047};
    else if(Folder == "Flight_up")
      Output = {0.967,0.824,0.959,0.896,0.964,1.039,0.903,0.971,1.047,0.913,0.981,1.059};
    else if(Folder == "Flight_down")
      Output = {0.967,0.824,0.959,0.896,0.964,1.017,0.903,0.971,1.025,0.913,0.981,1.035};
    else if(Folder == "MCNorm_zjets" || Folder == "Zjets_up")
      Output = {0.954,0.81,0.955,0.907,0.88,1.053,0.916,0.889,1.064,0.928,0.9,1.077};
    else if(Folder == "MCNorm_diboson" || Folder == "Diboson_up")
      Output = {0.966,0.824,0.96,0.899,0.962,1.028,0.905,0.969,1.036,0.915,0.979,1.047};
    else if(Folder == "MCNorm_ttV" || Folder == "ttV_up")
      Output = {0.967,0.824,0.959,0.896,0.964,1.028,0.903,0.971,1.036,0.913,0.981,1.047};
    else if(Folder == "MCNorm_singleTop" || Folder == "Stop_up" )
      Output={0.967,0.824,0.959,0.896,0.964,1.028,0.903,0.971,1.036,0.913,0.981,1.047};
    else if(Folder == "fakeEff_CR_S")
      Output = {0.954,0.814,0.945,0.996,0.875,1.041,1.001,0.88,1.046,1.005,0.884,1.051};
    else if(Folder == "fakeEff_MCscale_U")
      Output = {1.012,0.86,1.01,0.584,1.263,0.982,0.591,1.279,0.995,0.609,1.319,1.025};
    else if(Folder == "fakeEff_MCscale_D")
      Output = {0.923,0.789,0.912,1.224,0.651,1.076,1.226,0.653,1.078,1.214,0.646,1.068};
    else if(Folder == "fakes_fakeEff_stat_D")
      Output = {0.979,0.834,0.972,0.811,1.048,1.015,0.818,1.057,1.024,0.831,1.074,1.04};
    else if(Folder == "fakes_fakeEff_stat_U")
      Output = {0.954,0.814,0.945,0.986,0.876,1.042,0.992,0.881,1.048,0.997,0.885,1.054};
//     else if(Folder == "fakes_realEff_stat_D")
//       Output = {1.1819, 1.0075, 1.174, 0.687, 0.713, 1.142, 0.708, 0.735, 1.177, 0.736, 0.763, 1.223} ;
//     else if(Folder == "fakes_realEff_stat_U")
//       Output = {1.1807, 1.0066, 1.1731, 0.69, 0.706, 1.144, 0.711, 0.728, 1.179, 0.739, 0.756, 1.225} ;
//     else if(Folder == "fakes_MTWModelling")
//       Output = {0.8656, 0.7539, 0.8667, 3.185, -1.817, 1.554, 3.166, -1.807, 1.545, 2.848, -1.625, 1.39} ;
    else if(Folder == "QCDNorm_down_30")
        Output =  {1.061,0.9,1.071,0.267,1.56,0.938,0.272,1.588,0.955,0.286,1.672,1.005};
   else if(Folder == "QCDNorm_down_50")
         Output = {1.124,0.951,1.155,-0.093,1.901,0.886,-0.096,1.948,0.908,-0.103,2.101,0.98};
   else if(Folder == "QCDNorm_up_30")
       Output = {0.872,0.749,0.86,1.662,0.239,1.138,1.653,0.238,1.132,1.595,0.23,1.092};
   else if(Folder == "QCDNorm_up_50")
       Output = {0.809,0.699,0.801,2.273,-0.338,1.226,2.237,-0.333,1.206,2.084,-0.31,1.124};
    else
      Output = {0.967,0.824,0.959,0.896,0.964,1.028,0.903,0.971,1.036,0.913,0.981,1.047};  // default back to nominal
    
    
  }
  else{
    
if(Folder == "MET_SoftTrk_ResoPara")
      Output = {1.044,0.942,0.925,0.797,1.315,0.934,0.794,1.31,0.931,0.802,1.324,0.941};
    else if(Folder == "MET_SoftTrk_ResoPerp")
      Output = {1.044,0.936,0.928,0.742,1.346,0.933,0.74,1.344,0.932,0.751,1.364,0.946};
    else if(Folder == "MET_SoftTrk_ScaleUp")
      Output = {1.044,0.943,0.927,0.77,1.332,0.933,0.768,1.328,0.93,0.778,1.345,0.942};
    else if(Folder == "MET_SoftTrk_ScaleDown")
      Output = {1.04,0.944,0.926,0.801,1.313,0.934,0.798,1.308,0.931,0.806,1.321,0.94};
    else if(Folder == "EG_SCALE_ALL__1up")
      Output = {1.042,0.944,0.925,0.813,1.307,0.934,0.81,1.302,0.93,0.817,1.314,0.939};
    else if(Folder == "EG_SCALE_ALL__1down")
      Output = {1.042,0.944,0.925,0.813,1.307,0.934,0.81,1.302,0.93,0.817,1.313,0.939};
    else if(Folder == "EG_RESOLUTION_ALL__1up")
      Output = {1.042,0.944,0.925,0.813,1.307,0.934,0.81,1.302,0.93,0.817,1.314,0.939};
    else if(Folder == "EG_RESOLUTION_ALL__1down")
      Output = {1.042,0.944,0.925,0.813,1.307,0.934,0.81,1.302,0.93,0.817,1.314,0.939};
    else if(Folder == "MUONS_ID__1up")
      Output = {1.035,0.942,0.925,0.845,1.301,0.931,0.84,1.294,0.926,0.845,1.302,0.932};
    else if(Folder == "MUONS_ID__1down")
      Output = {1.038,0.944,0.926,0.845,1.297,0.932,0.84,1.29,0.927,0.846,1.299,0.933};
    else if(Folder == "MUONS_MS__1up")
      Output = {1.041,0.944,0.926,0.825,1.303,0.934,0.822,1.297,0.929,0.828,1.307,0.937};
    else if(Folder == "MUONS_MS__1down")
      Output = {1.041,0.945,0.926,0.808,1.311,0.934,0.804,1.306,0.93,0.812,1.318,0.939};
    else if(Folder == "MUONS_SCALE__1up")
      Output = {1.042,0.945,0.926,0.815,1.307,0.934,0.811,1.301,0.93,0.819,1.313,0.939};
    else if(Folder == "MUONS_SCALE__1down")
      Output = {1.04,0.945,0.924,0.811,1.309,0.934,0.807,1.304,0.93,0.815,1.316,0.939};
    else if(Folder == "JET_JER_SINGLE_NP__1up")
      Output = {1.045,0.91,0.898,0.488,1.442,0.946,0.491,1.453,0.953,0.508,1.502,0.986};
    else if(Folder == "JET_19NP_JET_BJES_Response__1up")
      Output = {1.043,0.944,0.926,0.771,1.317,0.938,0.77,1.315,0.936,0.78,1.331,0.948};
    else if(Folder == "JET_19NP_JET_BJES_Response__1down")
      Output = {1.042,0.946,0.927,0.824,1.309,0.932,0.82,1.303,0.928,0.826,1.313,0.935};
    else if(Folder == "JET_19NP_JET_EffectiveNP_1__1up")
      Output = {0.973,0.872,0.805,0.704,1.423,0.918,0.7,1.416,0.913,0.71,1.436,0.926};
    else if(Folder == "JET_19NP_JET_EffectiveNP_1__1down")
      Output = {1.127,1.052,1.035,0.808,1.233,0.957,0.809,1.234,0.958,0.819,1.249,0.97};
    else if(Folder == "JET_19NP_JET_EffectiveNP_2__1up")
      Output = {1.046,0.976,0.96,0.821,1.31,0.932,0.817,1.304,0.927,0.824,1.315,0.936};
    else if(Folder == "JET_19NP_JET_EffectiveNP_2__1down")
      Output = {1.033,0.927,0.912,0.736,1.346,0.934,0.735,1.344,0.933,0.746,1.364,0.947};
    else if(Folder == "JET_19NP_JET_EffectiveNP_3__1up")
      Output = {1.045,0.93,0.917,0.803,1.302,0.937,0.801,1.298,0.934,0.809,1.311,0.944};
    else if(Folder == "JET_19NP_JET_EffectiveNP_3__1down")
      Output = {1.041,0.959,0.934,0.804,1.323,0.931,0.8,1.317,0.927,0.808,1.33,0.936};
    else if(Folder == "JET_19NP_JET_EffectiveNP_4__1up")
      Output = {1.045,0.95,0.933,0.766,1.333,0.934,0.764,1.329,0.931,0.774,1.346,0.944};
    else if(Folder == "JET_19NP_JET_EffectiveNP_4__1down")
      Output = {1.044,0.938,0.919,0.804,1.303,0.937,0.801,1.299,0.934,0.809,1.312,0.943};
    else if(Folder == "JET_19NP_JET_EffectiveNP_5__1up")
      Output = {1.04,0.94,0.921,0.843,1.293,0.934,0.839,1.287,0.929,0.845,1.295,0.935};
    else if(Folder == "JET_19NP_JET_EffectiveNP_5__1down")
      Output = {1.043,0.944,0.929,0.801,1.313,0.934,0.798,1.308,0.931,0.806,1.322,0.94};
    else if(Folder == "JET_19NP_JET_EffectiveNP_6restTerm__1up")
      Output = {1.041,0.944,0.92,0.817,1.305,0.934,0.813,1.299,0.93,0.82,1.311,0.939};
    else if(Folder == "JET_19NP_JET_EffectiveNP_6restTerm__1down")
      Output = {1.04,0.944,0.926,0.83,1.302,0.933,0.826,1.296,0.929,0.833,1.306,0.936};
    else if(Folder == "JET_19NP_JET_EtaIntercalibration_Modelling__1up")
      Output = {1.029,0.918,0.888,0.616,1.401,0.937,0.617,1.404,0.939,0.632,1.438,0.962};
    else if(Folder == "JET_19NP_JET_EtaIntercalibration_Modelling__1down")
      Output = {1.07,0.981,0.974,0.909,1.227,0.943,0.904,1.221,0.938,0.907,1.224,0.941};
    else if(Folder == "JET_19NP_JET_EtaIntercalibration_NonClosure__1up")
      Output = {1.038,0.949,0.923,0.85,1.296,0.932,0.846,1.289,0.926,0.851,1.297,0.932};
    else if(Folder == "JET_19NP_JET_EtaIntercalibration_NonClosure__1down")
      Output = {1.04,0.944,0.924,0.835,1.298,0.933,0.831,1.292,0.929,0.837,1.301,0.936};
    else if(Folder == "JET_19NP_JET_EtaIntercalibration_TotalStat__1up")
      Output = {1.034,0.925,0.908,0.741,1.342,0.935,0.74,1.34,0.933,0.751,1.36,0.947};
    else if(Folder == "JET_19NP_JET_EtaIntercalibration_TotalStat__1down")
      Output = {1.042,0.978,0.953,0.869,1.293,0.929,0.863,1.284,0.923,0.868,1.29,0.928};
    else if(Folder == "JET_19NP_JET_Flavor_Response__1up")
      Output = {1.058,0.989,0.972,0.848,1.273,0.939,0.844,1.267,0.935,0.851,1.277,0.942};
    else if(Folder == "JET_19NP_JET_Flavor_Response__1down")
      Output = {1.03,0.921,0.897,0.641,1.397,0.934,0.642,1.398,0.935,0.656,1.429,0.956};
    else if(Folder == "JET_19NP_JET_Flavor_Composition__1up")
      Output = {0.967,0.859,0.806,0.822,1.399,0.907,0.814,1.385,0.897,0.817,1.391,0.901};
    else if(Folder == "JET_19NP_JET_Flavor_Composition__1down")
      Output = {1.126,1.062,1.032,0.844,1.196,0.963,0.845,1.197,0.963,0.853,1.209,0.973};
    else if(Folder == "JET_19NP_JET_PunchThrough_MC15__1up")
      Output = {1.042,0.944,0.925,0.813,1.307,0.934,0.81,1.302,0.93,0.817,1.314,0.939};
    else if(Folder == "JET_19NP_JET_PunchThrough_MC15__1down")
      Output = {1.042,0.944,0.925,0.813,1.307,0.934,0.81,1.302,0.93,0.817,1.314,0.939};
    else if(Folder == "JET_19NP_JET_Pileup_PtTerm__1up")
      Output = {1.044,0.951,0.928,0.758,1.33,0.936,0.757,1.327,0.934,0.767,1.346,0.947};
    else if(Folder == "JET_19NP_JET_Pileup_PtTerm__1down")
      Output = {1.04,0.933,0.924,0.858,1.286,0.933,0.853,1.279,0.928,0.858,1.286,0.933};
    else if(Folder == "JET_19NP_JET_Pileup_OffsetNPV__1up")
      Output = {1.032,0.945,0.919,0.899,1.28,0.929,0.892,1.271,0.922,0.894,1.273,0.923};
    else if(Folder == "JET_19NP_JET_Pileup_OffsetNPV__1down")
      Output = {1.052,0.949,0.929,0.69,1.353,0.94,0.69,1.354,0.94,0.704,1.38,0.959};
    else if(Folder == "JET_19NP_JET_Pileup_OffsetMu__1up")
      Output = {1.039,0.964,0.935,0.839,1.308,0.93,0.835,1.3,0.925,0.84,1.309,0.931};
    else if(Folder == "JET_19NP_JET_Pileup_OffsetMu__1down")
      Output = {1.042,0.932,0.912,0.82,1.297,0.936,0.817,1.292,0.933,0.824,1.303,0.941};
    else if(Folder == "JET_19NP_JET_Pileup_RhoTopology__1up")
      Output = {1.032,0.918,0.884,0.603,1.397,0.94,0.605,1.402,0.943,0.621,1.437,0.968};
    else if(Folder == "JET_19NP_JET_Pileup_RhoTopology__1down")
      Output = {1.063,0.99,0.974,0.855,1.273,0.937,0.851,1.267,0.933,0.857,1.276,0.939};
    else if(Folder == "JET_19NP_JET_SingleParticle_HighPt__1up")
      Output = {1.042,0.944,0.925,0.813,1.307,0.934,0.81,1.302,0.93,0.817,1.314,0.939};
    else if(Folder == "JET_19NP_JET_SingleParticle_HighPt__1down")
      Output = {1.042,0.944,0.925,0.813,1.307,0.934,0.81,1.302,0.93,0.817,1.314,0.939};
    else if(Folder == "leptonSF_EL_SF_Trigger_UP")
      Output = {1.042,0.944,0.925,0.813,1.307,0.934,0.81,1.302,0.93,0.817,1.314,0.939};
    else if(Folder == "leptonSF_EL_SF_Trigger_DOWN")
      Output = {1.042,0.944,0.925,0.813,1.307,0.934,0.81,1.302,0.93,0.817,1.314,0.939};
    else if(Folder == "leptonSF_EL_SF_Reco_UP")
      Output = {1.042,0.944,0.925,0.813,1.307,0.934,0.81,1.302,0.93,0.817,1.314,0.939};
    else if(Folder == "leptonSF_EL_SF_Reco_DOWN")
      Output = {1.042,0.944,0.925,0.813,1.307,0.934,0.81,1.302,0.93,0.817,1.314,0.939};
    else if(Folder == "leptonSF_EL_SF_ID_UP")
      Output = {1.042,0.944,0.925,0.813,1.307,0.934,0.81,1.302,0.93,0.817,1.314,0.939};
    else if(Folder == "leptonSF_EL_SF_ID_DOWN")
      Output = {1.042,0.944,0.925,0.813,1.307,0.934,0.81,1.302,0.93,0.817,1.314,0.939};
    else if(Folder == "leptonSF_EL_SF_Isol_UP")
      Output = {1.042,0.944,0.925,0.813,1.307,0.934,0.81,1.302,0.93,0.817,1.314,0.939};
    else if(Folder == "leptonSF_EL_SF_Isol_DOWN")
      Output = {1.042,0.944,0.925,0.813,1.307,0.934,0.81,1.302,0.93,0.817,1.314,0.939};
    else if(Folder == "leptonSF_MU_SF_Trigger_STAT_UP")
      Output = {1.03,0.934,0.915,0.812,1.298,0.937,0.809,1.293,0.934,0.817,1.306,0.943};
    else if(Folder == "leptonSF_MU_SF_Trigger_STAT_DOWN")
      Output = {1.054,0.956,0.936,0.815,1.317,0.931,0.811,1.311,0.927,0.818,1.322,0.935};
    else if(Folder == "leptonSF_MU_SF_Trigger_SYST_UP")
      Output = {1.036,0.94,0.921,0.816,1.302,0.935,0.812,1.296,0.932,0.82,1.308,0.94};
    else if(Folder == "leptonSF_MU_SF_Trigger_SYST_DOWN")
      Output = {1.047,0.949,0.93,0.811,1.313,0.933,0.807,1.307,0.929,0.815,1.319,0.938};
    else if(Folder == "leptonSF_MU_SF_ID_STAT_UP")
      Output = {1.04,0.943,0.924,0.814,1.305,0.935,0.811,1.3,0.931,0.818,1.312,0.939};
    else if(Folder == "leptonSF_MU_SF_ID_STAT_DOWN")
      Output = {1.043,0.946,0.927,0.812,1.309,0.934,0.809,1.304,0.93,0.817,1.316,0.938};
    else if(Folder == "leptonSF_MU_SF_ID_SYST_UP")
      Output = {1.038,0.941,0.922,0.815,1.303,0.935,0.811,1.298,0.931,0.819,1.31,0.94};
    else if(Folder == "leptonSF_MU_SF_ID_SYST_DOWN")
      Output = {1.045,0.947,0.928,0.812,1.311,0.933,0.809,1.305,0.929,0.816,1.317,0.938};
    else if(Folder == "leptonSF_MU_SF_Isol_STAT_UP")
      Output = {1.041,0.944,0.925,0.813,1.307,0.934,0.81,1.301,0.93,0.817,1.313,0.939};
    else if(Folder == "leptonSF_MU_SF_Isol_STAT_DOWN")
      Output = {1.042,0.945,0.926,0.813,1.307,0.934,0.81,1.302,0.93,0.817,1.314,0.939};
    else if(Folder == "leptonSF_MU_SF_Isol_SYST_UP")
      Output = {1.039,0.942,0.923,0.814,1.305,0.935,0.811,1.3,0.931,0.818,1.312,0.939};
    else if(Folder == "leptonSF_MU_SF_Isol_SYST_DOWN")
      Output = {1.044,0.947,0.927,0.813,1.309,0.934,0.809,1.304,0.93,0.817,1.316,0.938};
    else if(Folder == "leptonSF_MU_SF_TTVA_STAT_UP")
      Output = {1.041,0.944,0.924,0.814,1.306,0.934,0.811,1.3,0.931,0.818,1.312,0.939};
    else if(Folder == "leptonSF_MU_SF_TTVA_STAT_DOWN")
      Output = {1.042,0.945,0.926,0.813,1.308,0.934,0.809,1.303,0.93,0.817,1.315,0.939};
    else if(Folder == "leptonSF_MU_SF_TTVA_SYST_UP")
      Output = {1.041,0.944,0.925,0.813,1.307,0.934,0.81,1.302,0.93,0.817,1.313,0.939};
    else if(Folder == "leptonSF_MU_SF_TTVA_SYST_DOWN")
      Output = {1.042,0.945,0.926,0.813,1.307,0.934,0.81,1.302,0.93,0.817,1.314,0.939};
    else if(Folder == "bTagSF_77_extrapolation_up")
      Output = {1.042,0.944,0.925,0.812,1.307,0.934,0.808,1.302,0.931,0.816,1.314,0.939};
    else if(Folder == "bTagSF_77_extrapolation_down")
      Output = {1.042,0.944,0.925,0.815,1.307,0.934,0.811,1.302,0.93,0.819,1.314,0.938};
    else if(Folder == "bTagSF_77_extrapolation_from_charm_up")
      Output = {1.041,0.943,0.925,0.826,1.3,0.934,0.822,1.294,0.93,0.829,1.305,0.938};
    else if(Folder == "bTagSF_77_extrapolation_from_charm_down")
      Output = {1.043,0.946,0.926,0.801,1.314,0.934,0.798,1.309,0.931,0.806,1.322,0.94};
    else if(Folder == "jvt_UP")
      Output = {1.003,0.9,0.866,0.815,1.285,0.941,0.812,1.281,0.938,0.82,1.293,0.947};
    else if(Folder == "jvt_DOWN")
      Output = {1.083,0.991,0.989,0.812,1.329,0.928,0.808,1.322,0.923,0.815,1.334,0.931};
    else if(Folder == "bTagSF_77_eigenvars_B_up_0")
      Output = {1.044,0.947,0.926,0.848,1.323,0.924,0.842,1.314,0.917,0.847,1.321,0.922};
    else if(Folder == "bTagSF_77_eigenvars_B_up_1")
      Output = {1.042,0.945,0.926,0.819,1.31,0.932,0.815,1.304,0.928,0.822,1.316,0.936};
    else if(Folder == "bTagSF_77_eigenvars_B_up_2")
      Output = {1.041,0.944,0.925,0.808,1.303,0.937,0.805,1.298,0.933,0.813,1.311,0.942};
    else if(Folder == "bTagSF_77_eigenvars_B_up_3")
      Output = {1.042,0.944,0.925,0.814,1.307,0.934,0.811,1.302,0.93,0.818,1.313,0.939};
    else if(Folder == "bTagSF_77_eigenvars_B_up_4")
      Output = {1.042,0.944,0.925,0.813,1.307,0.934,0.81,1.302,0.93,0.817,1.314,0.939};
    else if(Folder == "bTagSF_77_eigenvars_B_down_0")
      Output = {1.039,0.942,0.924,0.781,1.291,0.944,0.78,1.289,0.943,0.79,1.305,0.955};
    else if(Folder == "bTagSF_77_eigenvars_B_down_1")
      Output = {1.041,0.944,0.925,0.807,1.304,0.936,0.805,1.299,0.933,0.812,1.312,0.942};
    else if(Folder == "bTagSF_77_eigenvars_B_down_2")
      Output = {1.042,0.945,0.926,0.819,1.312,0.932,0.815,1.306,0.928,0.822,1.317,0.935};
    else if(Folder == "bTagSF_77_eigenvars_B_down_3")
      Output = {1.042,0.944,0.925,0.812,1.307,0.934,0.809,1.302,0.931,0.816,1.314,0.939};
    else if(Folder == "bTagSF_77_eigenvars_B_down_4")
      Output = {1.042,0.944,0.925,0.813,1.307,0.934,0.81,1.302,0.93,0.818,1.314,0.939};
    else if(Folder == "bTagSF_77_eigenvars_C_up_0")
      Output = {1.069,0.966,0.943,0.722,1.485,0.893,0.717,1.474,0.887,0.726,1.493,0.898};
    else if(Folder == "bTagSF_77_eigenvars_C_up_1")
      Output = {1.037,0.941,0.923,0.824,1.277,0.942,0.821,1.273,0.939,0.829,1.284,0.947};
    else if(Folder == "bTagSF_77_eigenvars_C_up_2")
      Output = {1.039,0.943,0.923,0.824,1.293,0.937,0.821,1.287,0.933,0.828,1.298,0.941};
    else if(Folder == "bTagSF_77_eigenvars_C_up_3")
      Output = {1.043,0.946,0.926,0.807,1.318,0.932,0.804,1.312,0.928,0.811,1.324,0.937};
    else if(Folder == "bTagSF_77_eigenvars_C_down_0")
      Output = {1.02,0.928,0.911,0.88,1.16,0.969,0.879,1.159,0.968,0.885,1.167,0.975};
    else if(Folder == "bTagSF_77_eigenvars_C_down_1")
      Output = {1.046,0.948,0.928,0.802,1.338,0.926,0.798,1.332,0.922,0.805,1.344,0.93};
    else if(Folder == "bTagSF_77_eigenvars_C_down_2")
      Output = {1.044,0.946,0.927,0.802,1.322,0.931,0.799,1.316,0.927,0.807,1.329,0.936};
    else if(Folder == "bTagSF_77_eigenvars_C_down_3")
      Output = {1.04,0.943,0.924,0.819,1.297,0.936,0.816,1.292,0.933,0.823,1.303,0.941};
    else if(Folder == "bTagSF_77_eigenvars_Light_up_0")
      Output = {1.038,0.944,0.92,1.197,1.32,0.868,1.166,1.286,0.846,1.137,1.254,0.825};
    else if(Folder == "bTagSF_77_eigenvars_Light_up_1")
      Output = {1.041,0.944,0.924,0.83,1.302,0.933,0.826,1.296,0.928,0.832,1.306,0.936};
    else if(Folder == "bTagSF_77_eigenvars_Light_up_2")
      Output = {1.042,0.945,0.926,0.775,1.306,0.941,0.773,1.304,0.939,0.783,1.32,0.951};
    else if(Folder == "bTagSF_77_eigenvars_Light_up_3")
      Output = {1.041,0.944,0.925,0.82,1.307,0.933,0.816,1.301,0.929,0.823,1.312,0.937};
    else if(Folder == "bTagSF_77_eigenvars_Light_up_4")
      Output = {1.042,0.944,0.925,0.806,1.307,0.935,0.803,1.303,0.932,0.811,1.315,0.941};
    else if(Folder == "bTagSF_77_eigenvars_Light_up_5")
      Output = {1.042,0.944,0.925,0.816,1.308,0.934,0.812,1.302,0.93,0.82,1.314,0.938};
    else if(Folder == "bTagSF_77_eigenvars_Light_up_6")
      Output = {1.042,0.945,0.925,0.814,1.308,0.934,0.811,1.303,0.93,0.818,1.314,0.938};
    else if(Folder == "bTagSF_77_eigenvars_Light_up_7")
      Output = {1.042,0.944,0.925,0.818,1.307,0.934,0.814,1.301,0.93,0.821,1.313,0.938};
    else if(Folder == "bTagSF_77_eigenvars_Light_up_8")
      Output = {1.042,0.945,0.925,0.809,1.308,0.935,0.806,1.303,0.931,0.814,1.315,0.94};
    else if(Folder == "bTagSF_77_eigenvars_Light_up_9")
      Output = {1.041,0.944,0.925,0.815,1.307,0.934,0.812,1.301,0.93,0.819,1.313,0.939};
    else if(Folder == "bTagSF_77_eigenvars_Light_up_10")
      Output = {1.042,0.944,0.925,0.812,1.307,0.934,0.809,1.302,0.93,0.816,1.314,0.939};
    else if(Folder == "bTagSF_77_eigenvars_Light_up_11")
      Output = {1.042,0.944,0.925,0.813,1.307,0.934,0.809,1.302,0.93,0.817,1.314,0.939};
    else if(Folder == "bTagSF_77_eigenvars_Light_down_0")
      Output = {1.044,0.944,0.93,0.429,1.289,1.002,0.437,1.314,1.021,0.458,1.376,1.069};
    else if(Folder == "bTagSF_77_eigenvars_Light_down_1")
      Output = {1.042,0.945,0.926,0.796,1.312,0.935,0.794,1.307,0.932,0.802,1.321,0.942};
    else if(Folder == "bTagSF_77_eigenvars_Light_down_2")
      Output = {1.041,0.944,0.925,0.852,1.308,0.928,0.846,1.3,0.922,0.851,1.307,0.927};
    else if(Folder == "bTagSF_77_eigenvars_Light_down_3")
      Output = {1.042,0.945,0.925,0.807,1.307,0.935,0.804,1.303,0.932,0.811,1.315,0.941};
    else if(Folder == "bTagSF_77_eigenvars_Light_down_4")
      Output = {1.041,0.944,0.925,0.82,1.307,0.933,0.817,1.301,0.929,0.824,1.312,0.937};
    else if(Folder == "bTagSF_77_eigenvars_Light_down_5")
      Output = {1.042,0.944,0.925,0.811,1.307,0.935,0.808,1.301,0.931,0.815,1.314,0.94};
    else if(Folder == "bTagSF_77_eigenvars_Light_down_6")
      Output = {1.041,0.944,0.925,0.813,1.306,0.935,0.809,1.301,0.931,0.817,1.313,0.939};
    else if(Folder == "bTagSF_77_eigenvars_Light_down_7")
      Output = {1.042,0.944,0.925,0.809,1.307,0.935,0.806,1.302,0.931,0.814,1.315,0.94};
    else if(Folder == "bTagSF_77_eigenvars_Light_down_8")
      Output = {1.041,0.944,0.925,0.817,1.306,0.934,0.814,1.301,0.93,0.821,1.312,0.938};
    else if(Folder == "bTagSF_77_eigenvars_Light_down_9")
      Output = {1.042,0.944,0.925,0.812,1.307,0.934,0.808,1.302,0.931,0.816,1.314,0.939};
    else if(Folder == "bTagSF_77_eigenvars_Light_down_10")
      Output = {1.042,0.944,0.925,0.814,1.307,0.934,0.811,1.301,0.93,0.818,1.313,0.939};
    else if(Folder == "bTagSF_77_eigenvars_Light_down_11")
      Output = {1.042,0.944,0.925,0.814,1.307,0.934,0.811,1.301,0.93,0.818,1.313,0.939};
//     else if (Folder == "CA_up")
//       Output = {1.2832, 1.1512, 1.1528, 0.452, 1.061, 1.07, 0.465, 1.092, 1.101, 0.489, 1.149, 1.158};
//     else if(Folder == "CA_down")
//       Output = {1.2546, 1.1192, 1.1162, 0.489, 1.084, 1.056, 0.502, 1.111, 1.084, 0.526, 1.164, 1.135};
//     else if (Folder == "Fcc_up")
//       Output = {1.2631, 1.1306, 1.1302, 0.487, 1.041, 1.07, 0.501, 1.07, 1.1, 0.525, 1.123, 1.154};
//     else if (Folder == "Fcc_down")
//       Output = {1.2748, 1.1393, 1.1379, 0.453, 1.103, 1.056, 0.465, 1.133, 1.085, 0.489, 1.19, 1.139};
//     else if (Folder == "Flight_up")
//       Output = {1.2696, 1.1353, 1.134, 0.389, 1.073, 1.076, 0.402, 1.107, 1.111, 0.425, 1.172, 1.176};
//     else if (Folder == "Flight_down")
//       Output = {1.2684, 1.1347, 1.134, 0.552, 1.072, 1.05, 0.565, 1.096, 1.074, 0.588, 1.141, 1.118};
    else if(Folder == "CA_2ex_up")
      Output = {1.063,0.944,0.925,0.813,1.307,0.934,0.810,1.302,0.930,0.817,1.314,0.939};
    else if(Folder == "CA_2ex_down")
      Output = {1.021,0.944,0.925,0.813,1.307,0.934,0.810,1.302,0.930,0.817,1.314,0.939};
    else if(Folder == "CA_3ex_up")
      Output = {1.042,0.959,0.925,0.813,1.307,0.934,0.810,1.302,0.930,0.817,1.314,0.939};
    else if(Folder == "CA_3ex_down")
      Output = {1.042,0.929,0.925,0.813,1.307,0.934,0.810,1.302,0.930,0.817,1.314,0.939};
    else if(Folder == "CA_4incl_up")
      Output = {1.042,0.944,0.961,0.813,1.307,0.934,0.810,1.302,0.930,0.817,1.314,0.939};
    else if(Folder == "CA_4incl_down")
      Output = {1.042,0.944,0.889,0.813,1.307,0.934,0.810,1.302,0.930,0.817,1.314,0.939};
    else if(Folder == "Fcc_up")
      Output = {1.042,0.944,0.925,1.136,1.307,0.934,1.132,1.302,0.930,1.141,1.314,0.939};
    else if(Folder == "Fcc_down")
      Output = {1.042,0.944,0.925,0.490,1.307,0.934,0.488,1.302,0.930,0.493,1.314,0.939};
    else if(Folder == "Fc_up")
      Output = {1.042,0.944,0.925,0.813,1.460,0.934,0.810,1.454,0.930,0.817,1.468,0.939};
    else if(Folder == "Fc_down")
      Output = {1.042,0.944,0.925,0.813,1.154,0.934,0.810,1.150,0.930,0.817,1.160,0.939};
    else if(Folder == "Flight_up")
      Output = {1.042,0.944,0.925,0.813,1.307,0.944,0.810,1.302,0.940,0.817,1.314,0.949};
    else if(Folder == "Flight_down")
      Output = {1.042,0.944,0.925,0.813,1.307,0.924,0.810,1.302,0.920,0.817,1.314,0.929};
    else if(Folder == "MCNorm_zjets" || Folder == "Zjets_up" )
      Output = {1.024,0.937,0.915,0.909,1.223,0.945,0.904,1.216,0.94,0.906,1.219,0.943} ;
    else if(Folder == "MCNorm_diboson"  || Folder == "Diboson_up" )
      Output = {1.041,0.944,0.926,0.814,1.306,0.934,0.811,1.301,0.931,0.818,1.312,0.939} ;
    else if(Folder == "MCNorm_ttV"  || Folder == "ttV_up" )
      Output = {1.042,0.944,0.925,0.813,1.307,0.934,0.81,1.302,0.93,0.817,1.314,0.939} ;
    else if(Folder == "MCNorm_singleTop" || Folder == "Stop_up" )
      Output = {1.042,0.944,0.925,0.813,1.307,0.934,0.81,1.302,0.93,0.817,1.314,0.939} ;
    else if(Folder == "fakeEff_CR_S")
      Output = {1.022,0.93,0.914,0.929,1.184,0.954,0.924,1.178,0.95,0.926,1.18,0.951};
    else if(Folder == "fakeEff_MCscale_U")
      Output = {1.043,0.945,0.926,0.805,1.315,0.933,0.802,1.309,0.929,0.81,1.322,0.938};
    else if(Folder == "fakeEff_MCscale_D")
      Output = {1.04,0.944,0.925,0.821,1.3,0.935,0.818,1.294,0.931,0.825,1.305,0.939};
    else if(Folder == "fakes_fakeEff_stat_D")
      Output = {1.044,0.946,0.926,0.799,1.319,0.933,0.796,1.314,0.929,0.804,1.328,0.939};
    else if(Folder == "fakes_fakeEff_stat_U")
     Output = {1.039,0.943,0.924,0.831,1.294,0.936,0.827,1.288,0.931,0.834,1.298,0.939};
//     else if(Folder == "fakes_realEff_stat_D")
//       Output = {1.2693, 1.1355, 1.1343, 0.471, 1.074, 1.062, 0.484, 1.103, 1.091, 0.508, 1.158, 1.145} ;
//     else if(Folder == "fakes_realEff_stat_U")
//       Output = {1.2685, 1.135, 1.1343, 0.47, 1.07, 1.064, 0.483, 1.1, 1.093, 0.507, 1.155, 1.147} ;
//     else if(Folder == "fakes_MTWModelling")
//       Output = {1.1745, 1.0622, 1.076, 1.008, 0.536, 1.144, 1.03, 0.548, 1.169, 1.042, 0.554, 1.183} ;
    else if(Folder == "QCDNorm_down_30")
        Output = {1.07,0.966,0.942,0.627,1.477,0.911,0.626,1.475,0.909,0.64,1.507,0.93} ;
   else if(Folder == "QCDNorm_down_50")
        Output = {1.089,0.98,0.953,0.509,1.586,0.896,0.509,1.586,0.896,0.524,1.634,0.923} ;
   else if(Folder == "QCDNorm_up_30")
        Output = {1.013,0.923,0.909,1.01,1.127,0.959,1.003,1.12,0.952,0.999,1.115,0.948};

   else if(Folder == "QCDNorm_up_50")
        Output = {0.994,0.908,0.898,1.147,1.002,0.976,1.137,0.993,0.968,1.122,0.98,0.955} ;
    else
      Output = {1.042,0.944,0.925,0.813,1.307,0.934,0.81,1.302,0.93,0.817,1.314,0.939}; // default back to nominal

  }

  return Output;
  
  
}

