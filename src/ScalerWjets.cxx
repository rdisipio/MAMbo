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
        int x = njets <= 4 ? njets-2 : 2;
	std::cout<<"Njet "<<njets<<" Nbjet"<<nbjets<<std::endl;
	
	std::vector<double> EventWeights = m_weights;
	
	if( nbjets < 1 || x < 0 ) 
	{ 
	   x=0;
	   std::vector<double> tmp{1.,1.,1.,1.,1.,1.,1.,1.,1.,1.,1.,1.};
	   EventWeights = tmp;
	}
	
	double CA_weight = EventWeights[m_CA+x];
        double HF_weight = 1;
        if( is_WplusC ) HF_weight = EventWeights[m_Kc+x];
        else if( is_WplusCC || isB ) HF_weight = EventWeights[m_Kbb+x];
        else if( isLight ) HF_weight = EventWeights[m_Klight+x];
	
	
	std::cout<<std::endl<<"Weights "<<CA_weight<<" "<<HF_weight<<std::endl;
        return CA_weight * HF_weight;
}

std::vector<double> ScalerWjets::GetWJetsSF(std::string Folder, bool isEl){

  // info is stored in the following order:  [CA_btag_2excl, CA_btag_3excl, CA_btag_4incl, Fcc_2excl, Fcc_3excl, Fcc_4incl, Fc_2excl, Fc_3excl, Fc_4incl, Flight_2excl, Flight_3excl, Flight_4incl]

  std::vector<double> Output(6);

  if(isEl){

    if(Folder == "MET_SoftTrk_ResoPara")
      Output = {1.174, 1.0104, 1.1609, 0.741, 0.703, 1.137, 0.762, 0.722, 1.169, 0.787, 0.747, 1.208};
    else if(Folder == "MET_SoftTrk_ResoPerp")
      Output = {1.1828, 1.0106, 1.1762, 0.676, 0.723, 1.141, 0.697, 0.745, 1.176, 0.725, 0.775, 1.223};
    else if(Folder == "MET_SoftTrk_ScaleUp")
      Output = {1.181, 1.0081, 1.1661, 0.69, 0.719, 1.14, 0.711, 0.74, 1.175, 0.738, 0.769, 1.22};
    else if(Folder == "MET_SoftTrk_ScaleDown")
      Output = {1.1761, 1.002, 1.1683, 0.707, 0.699, 1.144, 0.728, 0.72, 1.178, 0.755, 0.747, 1.222};
    else if(Folder == "EG_SCALE_ALL__1up")
      Output = {1.1687, 0.9989, 1.1667, 0.669, 0.728, 1.14, 0.69, 0.75, 1.176, 0.718, 0.781, 1.223};
    else if(Folder == "EG_SCALE_ALL__1down")
      Output = {1.184, 1.0134, 1.1772, 0.723, 0.697, 1.142, 0.745, 0.718, 1.175, 0.771, 0.743, 1.217};
    else if(Folder == "EG_RESOLUTION_ALL__1up")
      Output = {1.1926, 1.0097, 1.1806, 0.558, 0.773, 1.144, 0.578, 0.801, 1.185, 0.607, 0.841, 1.244};
    else if(Folder == "EG_RESOLUTION_ALL__1down")
      Output = {1.1821, 1.0143, 1.1786, 0.642, 0.74, 1.141, 0.662, 0.764, 1.177, 0.691, 0.797, 1.228};
    else if(Folder == "MUONS_ID__1up")
      Output = {1.1839, 1.0087, 1.1786, 0.636, 0.741, 1.142, 0.657, 0.765, 1.179, 0.685, 0.798, 1.23};
    else if(Folder == "MUONS_ID__1down")
      Output = {1.1853, 1.0099, 1.1797, 0.634, 0.74, 1.142, 0.655, 0.764, 1.179, 0.683, 0.797, 1.231};
    else if(Folder == "MUONS_MS__1up")
      Output = {1.1829, 1.0077, 1.1771, 0.637, 0.742, 1.141, 0.658, 0.766, 1.178, 0.686, 0.799, 1.229};
    else if(Folder == "MUONS_MS__1down")
      Output = {1.1812, 1.007, 1.1736, 0.689, 0.709, 1.143, 0.71, 0.731, 1.178, 0.737, 0.76, 1.224};
    else if(Folder == "MUONS_SCALE__1up")
      Output = {1.1839, 1.0086, 1.1786, 0.636, 0.741, 1.142, 0.657, 0.765, 1.179, 0.685, 0.798, 1.23};
    else if(Folder == "MUONS_SCALE__1down")
      Output = {1.1853, 1.01, 1.1795, 0.635, 0.74, 1.142, 0.655, 0.764, 1.179, 0.684, 0.797, 1.231};
    else if(Folder == "JET_19NP_JET_BJES_Response__1up")
      Output = {1.1854, 1.0042, 1.2008, 0.508, 0.797, 1.144, 0.527, 0.827, 1.188, 0.556, 0.873, 1.253};
    else if(Folder == "JET_19NP_JET_BJES_Response__1down")
      Output = {1.1887, 1.0087, 1.2026, 0.579, 0.764, 1.143, 0.599, 0.79, 1.183, 0.628, 0.829, 1.241};
    else if(Folder == "JET_19NP_JET_EffectiveNP_1__1up")
      Output = {1.173, 0.9562, 1.0609, 0.324, 0.851, 1.152, 0.339, 0.89, 1.205, 0.363, 0.953, 1.29};
    else if(Folder == "JET_19NP_JET_EffectiveNP_1__1down")
      Output = {1.2147, 1.1518, 1.4378, 0.234, 0.971, 1.137, 0.245, 1.018, 1.192, 0.265, 1.101, 1.288};
    else if(Folder == "JET_19NP_JET_EffectiveNP_2__1up")
      Output = {1.1718, 1.057, 1.227, 0.625, 0.769, 1.135, 0.645, 0.794, 1.172, 0.673, 0.829, 1.223};
    else if(Folder == "JET_19NP_JET_EffectiveNP_2__1down")
      Output = {1.1962, 0.9998, 1.1689, 0.409, 0.831, 1.149, 0.426, 0.866, 1.196, 0.454, 0.921, 1.274};
    else if(Folder == "JET_19NP_JET_EffectiveNP_3__1up")
      Output = {1.1948, 1.0031, 1.1994, 0.464, 0.81, 1.147, 0.482, 0.842, 1.192, 0.511, 0.892, 1.263};
    else if(Folder == "JET_19NP_JET_EffectiveNP_3__1down")
      Output = {1.1934, 1.0124, 1.2053, 0.571, 0.765, 1.145, 0.591, 0.792, 1.185, 0.62, 0.831, 1.244};
    else if(Folder == "JET_19NP_JET_EffectiveNP_4__1up")
      Output = {1.192, 1.012, 1.1989, 0.548, 0.777, 1.144, 0.568, 0.805, 1.186, 0.597, 0.846, 1.247};
    else if(Folder == "JET_19NP_JET_EffectiveNP_4__1down")
      Output = {1.1941, 1.0037, 1.203, 0.479, 0.805, 1.146, 0.498, 0.836, 1.191, 0.527, 0.884, 1.26};
    else if(Folder == "JET_19NP_JET_EffectiveNP_5__1up")
      Output = {1.1911, 1.0035, 1.2038, 0.514, 0.79, 1.145, 0.534, 0.819, 1.189, 0.563, 0.864, 1.253};
    else if(Folder == "JET_19NP_JET_EffectiveNP_5__1down")
      Output = {1.1861, 1.0042, 1.1901, 0.573, 0.767, 1.143, 0.593, 0.794, 1.183, 0.622, 0.833, 1.242};
    else if(Folder == "JET_19NP_JET_EffectiveNP_6restTerm__1up")
      Output = {1.1911, 1.0063, 1.2101, 0.497, 0.8, 1.145, 0.516, 0.83, 1.189, 0.545, 0.877, 1.255};
    else if(Folder == "JET_19NP_JET_EffectiveNP_6restTerm__1down")
      Output = {1.1872, 1.0062, 1.1953, 0.562, 0.771, 1.144, 0.582, 0.798, 1.185, 0.612, 0.838, 1.244};
    else if(Folder == "JET_19NP_JET_EtaIntercalibration_Modelling__1up")
      Output = {1.1811, 0.9886, 1.1731, 0.482, 0.801, 1.145, 0.501, 0.833, 1.19, 0.53, 0.88, 1.259};
    else if(Folder == "JET_19NP_JET_EtaIntercalibration_Modelling__1down")
      Output = {1.1922, 1.0908, 1.2768, 0.334, 0.911, 1.137, 0.349, 0.952, 1.188, 0.373, 1.017, 1.269};
    else if(Folder == "JET_19NP_JET_EtaIntercalibration_NonClosure__1up")
      Output = {1.1806, 1.0437, 1.2009, 0.543, 0.79, 1.141, 0.563, 0.819, 1.182, 0.592, 0.861, 1.242};
    else if(Folder == "JET_19NP_JET_EtaIntercalibration_NonClosure__1down")
      Output = {1.1882, 1.0046, 1.2019, 0.539, 0.782, 1.144, 0.559, 0.811, 1.185, 0.588, 0.853, 1.248};
    else if(Folder == "JET_19NP_JET_EtaIntercalibration_TotalStat__1up")
      Output = {1.2, 1.0023, 1.1877, 0.394, 0.838, 1.149, 0.41, 0.874, 1.197, 0.437, 0.931, 1.276};
    else if(Folder == "JET_19NP_JET_EtaIntercalibration_TotalStat__1down")
      Output = {1.1764, 1.0547, 1.2336, 0.615, 0.769, 1.136, 0.635, 0.795, 1.174, 0.663, 0.83, 1.226};
    else if(Folder == "JET_19NP_JET_Flavor_Response__1up")
      Output = {1.1843, 1.0756, 1.2552, 0.423, 0.865, 1.137, 0.44, 0.9, 1.184, 0.467, 0.956, 1.257};
    else if(Folder == "JET_19NP_JET_Flavor_Response__1down")
      Output = {1.1925, 0.9942, 1.1763, 0.383, 0.844, 1.148, 0.399, 0.879, 1.196, 0.426, 0.938, 1.277};
    else if(Folder == "JET_19NP_JET_Flavor_Composition__1up")
      Output = {1.1807, 0.9652, 1.0806, 0.315, 0.853, 1.153, 0.329, 0.892, 1.205, 0.353, 0.956, 1.291};
    else if(Folder == "JET_19NP_JET_Flavor_Composition__1down")
      Output = {1.1948, 1.1452, 1.3732, 0.376, 0.906, 1.135, 0.392, 0.945, 1.184, 0.418, 1.008, 1.263};
    else if(Folder == "JET_19NP_JET_PunchThrough_MC15__1up")
      Output = {1.1878, 1.0066, 1.2025, 0.534, 0.784, 1.144, 0.554, 0.813, 1.186, 0.583, 0.856, 1.248};
    else if(Folder == "JET_19NP_JET_PunchThrough_MC15__1down")
      Output = {1.1878, 1.0066, 1.2025, 0.534, 0.784, 1.144, 0.554, 0.813, 1.186, 0.583, 0.856, 1.248};
    else if(Folder == "JET_19NP_JET_Pileup_PtTerm__1up")
      Output = {1.1911, 1.015, 1.2088, 0.508, 0.794, 1.145, 0.527, 0.824, 1.188, 0.556, 0.869, 1.254};
    else if(Folder == "JET_19NP_JET_Pileup_PtTerm__1down")
      Output = {1.1868, 1.0071, 1.1945, 0.559, 0.772, 1.144, 0.579, 0.799, 1.185, 0.609, 0.84, 1.245};
    else if(Folder == "JET_19NP_JET_Pileup_OffsetNPV__1up")
      Output = {1.1933, 1.0202, 1.1886, 0.578, 0.758, 1.145, 0.599, 0.785, 1.186, 0.628, 0.823, 1.243};
    else if(Folder == "JET_19NP_JET_Pileup_OffsetNPV__1down")
      Output = {1.1708, 1.0408, 1.2137, 0.566, 0.79, 1.137, 0.586, 0.818, 1.177, 0.614, 0.858, 1.234};
    else if(Folder == "JET_19NP_JET_Pileup_OffsetMu__1up")
      Output = {1.1914, 1.0175, 1.2071, 0.566, 0.772, 1.143, 0.586, 0.799, 1.183, 0.615, 0.839, 1.243};
    else if(Folder == "JET_19NP_JET_Pileup_OffsetMu__1down")
      Output = {1.1975, 1.0051, 1.2096, 0.425, 0.826, 1.148, 0.443, 0.86, 1.195, 0.471, 0.914, 1.271};
    else if(Folder == "JET_19NP_JET_Pileup_RhoTopology__1up")
      Output = {1.1945, 0.9912, 1.1726, 0.293, 0.881, 1.15, 0.307, 0.921, 1.203, 0.33, 0.992, 1.295};
    else if(Folder == "JET_19NP_JET_Pileup_RhoTopology__1down")
      Output = {1.1959, 1.0839, 1.281, 0.336, 0.901, 1.14, 0.351, 0.942, 1.191, 0.375, 1.007, 1.274};
    else if(Folder == "JET_19NP_JET_SingleParticle_HighPt__1up")
      Output = {1.1878, 1.0066, 1.2025, 0.534, 0.784, 1.144, 0.554, 0.813, 1.186, 0.583, 0.856, 1.248};
    else if(Folder == "JET_19NP_JET_SingleParticle_HighPt__1down")
      Output = {1.1878, 1.0066, 1.2025, 0.534, 0.784, 1.144, 0.554, 0.813, 1.186, 0.583, 0.856, 1.248};
    else if(Folder == "JET_JER_SINGLE_NP__1up")
      Output = {1.2026, 1.044, 1.19, 0.069, 0.989, 1.152, 0.072, 1.043, 1.215, 0.079, 1.14, 1.328};
    else if(Folder == "scaleFactor_leptonSF_EL_SF_Trigger_UP")
      Output = {1.1837, 0.9997, 1.1685, 0.626, 0.732, 1.145, 0.647, 0.757, 1.184, 0.676, 0.791, 1.237};
    else if(Folder == "scaleFactor_leptonSF_EL_SF_Trigger_DOWN")
      Output = {1.2016, 1.015, 1.1872, 0.63, 0.735, 1.144, 0.652, 0.76, 1.182, 0.68, 0.793, 1.234};
    else if(Folder == "scaleFactor_leptonSF_EL_SF_Reco_UP")
      Output = {1.1878, 1.0027, 1.1726, 0.63, 0.73, 1.145, 0.652, 0.755, 1.184, 0.68, 0.788, 1.236};
    else if(Folder == "scaleFactor_leptonSF_EL_SF_Reco_DOWN")
      Output = {1.1974, 1.0119, 1.183, 0.626, 0.737, 1.144, 0.647, 0.762, 1.182, 0.676, 0.796, 1.235};
    else if(Folder == "scaleFactor_leptonSF_EL_SF_ID_UP")
      Output = {1.1804, 0.9966, 1.165, 0.627, 0.729, 1.146, 0.649, 0.754, 1.185, 0.678, 0.788, 1.238};
    else if(Folder == "scaleFactor_leptonSF_EL_SF_ID_DOWN")
      Output = {1.2051, 1.0182, 1.1904, 0.629, 0.738, 1.143, 0.65, 0.763, 1.181, 0.679, 0.796, 1.233};
    else if(Folder == "scaleFactor_leptonSF_EL_SF_Isol_UP")
      Output = {1.1887, 1.0037, 1.1739, 0.63, 0.731, 1.145, 0.651, 0.756, 1.184, 0.68, 0.789, 1.236};
    else if(Folder == "scaleFactor_leptonSF_EL_SF_Isol_DOWN")
      Output = {1.1966, 1.0104, 1.1817, 0.626, 0.737, 1.144, 0.647, 0.762, 1.182, 0.676, 0.795, 1.235};
    else if(Folder == "scaleFactor_leptonSF_MU_SF_Trigger_STAT_UP")
      Output = {1.1927, 1.0072, 1.1779, 0.628, 0.734, 1.144, 0.649, 0.758, 1.183, 0.678, 0.792, 1.235};
    else if(Folder == "scaleFactor_leptonSF_MU_SF_Trigger_STAT_DOWN")
      Output = {1.1927, 1.0072, 1.1779, 0.628, 0.734, 1.144, 0.649, 0.758, 1.183, 0.678, 0.792, 1.235};
    else if(Folder == "scaleFactor_leptonSF_MU_SF_Trigger_SYST_UP")
      Output = {1.1927, 1.0072, 1.1779, 0.628, 0.734, 1.144, 0.649, 0.758, 1.183, 0.678, 0.792, 1.235};
    else if(Folder == "scaleFactor_leptonSF_MU_SF_Trigger_SYST_DOWN")
      Output = {1.1927, 1.0072, 1.1779, 0.628, 0.734, 1.144, 0.649, 0.758, 1.183, 0.678, 0.792, 1.235};
    else if(Folder == "scaleFactor_leptonSF_MU_SF_ID_STAT_UP")
      Output = {1.1927, 1.0072, 1.1779, 0.628, 0.734, 1.144, 0.649, 0.758, 1.183, 0.678, 0.792, 1.235};
    else if(Folder == "scaleFactor_leptonSF_MU_SF_ID_STAT_DOWN")
      Output = {1.1927, 1.0072, 1.1779, 0.628, 0.734, 1.144, 0.649, 0.758, 1.183, 0.678, 0.792, 1.235};
    else if(Folder == "scaleFactor_leptonSF_MU_SF_ID_SYST_UP")
      Output = {1.1927, 1.0072, 1.1779, 0.628, 0.734, 1.144, 0.649, 0.758, 1.183, 0.678, 0.792, 1.235};
    else if(Folder == "scaleFactor_leptonSF_MU_SF_ID_SYST_DOWN")
      Output = {1.1927, 1.0072, 1.1779, 0.628, 0.734, 1.144, 0.649, 0.758, 1.183, 0.678, 0.792, 1.235};
    else if(Folder == "scaleFactor_leptonSF_MU_SF_Isol_STAT_UP")
      Output = {1.1927, 1.0072, 1.1779, 0.628, 0.734, 1.144, 0.649, 0.758, 1.183, 0.678, 0.792, 1.235};
    else if(Folder == "scaleFactor_leptonSF_MU_SF_Isol_STAT_DOWN")
      Output = {1.1927, 1.0072, 1.1779, 0.628, 0.734, 1.144, 0.649, 0.758, 1.183, 0.678, 0.792, 1.235};
    else if(Folder == "scaleFactor_leptonSF_MU_SF_Isol_SYST_UP")
      Output = {1.1927, 1.0072, 1.1779, 0.628, 0.734, 1.144, 0.649, 0.758, 1.183, 0.678, 0.792, 1.235};
    else if(Folder == "scaleFactor_leptonSF_MU_SF_Isol_SYST_DOWN")
      Output = {1.1927, 1.0072, 1.1779, 0.628, 0.734, 1.144, 0.649, 0.758, 1.183, 0.678, 0.792, 1.235};
    else if(Folder == "scaleFactor_leptonSF_MU_SF_TTVA_STAT_UP")
      Output = {1.1927, 1.0072, 1.1779, 0.628, 0.734, 1.144, 0.649, 0.758, 1.183, 0.678, 0.792, 1.235};
    else if(Folder == "scaleFactor_leptonSF_MU_SF_TTVA_STAT_DOWN")
      Output = {1.1927, 1.0072, 1.1779, 0.628, 0.734, 1.144, 0.649, 0.758, 1.183, 0.678, 0.792, 1.235};
    else if(Folder == "scaleFactor_leptonSF_MU_SF_TTVA_SYST_UP")
      Output = {1.1927, 1.0072, 1.1779, 0.628, 0.734, 1.144, 0.649, 0.758, 1.183, 0.678, 0.792, 1.235};
    else if(Folder == "scaleFactor_leptonSF_MU_SF_TTVA_SYST_DOWN")
      Output = {1.1927, 1.0072, 1.1779, 0.628, 0.734, 1.144, 0.649, 0.758, 1.183, 0.678, 0.792, 1.235};
    else if(Folder == "scaleFactor_bTagSF_77_extrapolation_up")
      Output = {1.1847, 1.0086, 1.1787, 0.634, 0.74, 1.142, 0.655, 0.764, 1.18, 0.684, 0.797, 1.231};
    else if(Folder == "scaleFactor_bTagSF_77_extrapolation_down")
      Output = {1.1859, 1.0104, 1.1809, 0.635, 0.74, 1.142, 0.656, 0.764, 1.179, 0.684, 0.797, 1.23};
    else if(Folder == "scaleFactor_bTagSF_77_extrapolation_from_charm_up")
      Output = {1.1856, 1.0099, 1.1813, 0.617, 0.747, 1.143, 0.637, 0.772, 1.181, 0.666, 0.807, 1.234};
    else if(Folder == "scaleFactor_bTagSF_77_extrapolation_from_charm_down")
      Output = {1.1847, 1.0097, 1.179, 0.653, 0.733, 1.141, 0.674, 0.756, 1.178, 0.702, 0.788, 1.227};
    else if(Folder == "scaleFactor_jvt_UP")
      Output = {1.1402, 0.9536, 1.0964, 0.658, 0.705, 1.15, 0.679, 0.728, 1.187, 0.708, 0.758, 1.238};
    else if(Folder == "scaleFactor_jvt_DOWN")
      Output = {1.2422, 1.0668, 1.2682, 0.603, 0.766, 1.139, 0.624, 0.792, 1.177, 0.652, 0.828, 1.23};
    else if(Folder == "scaleFactor_bTagSF_77_eigenvars_B_up_0")
      Output = {1.205, 1.0262, 1.1983, 0.634, 0.746, 1.14, 0.655, 0.77, 1.177, 0.683, 0.803, 1.228};
    else if(Folder == "scaleFactor_bTagSF_77_eigenvars_B_up_1")
      Output = {1.1889, 1.0121, 1.1829, 0.634, 0.742, 1.141, 0.655, 0.767, 1.179, 0.683, 0.8, 1.23};
    else if(Folder == "scaleFactor_bTagSF_77_eigenvars_B_up_2")
      Output = {1.1805, 1.0058, 1.1752, 0.639, 0.736, 1.143, 0.66, 0.76, 1.18, 0.688, 0.793, 1.231};
    else if(Folder == "scaleFactor_bTagSF_77_eigenvars_B_up_3")
      Output = {1.1855, 1.01, 1.1803, 0.635, 0.739, 1.142, 0.656, 0.763, 1.18, 0.684, 0.797, 1.231};
    else if(Folder == "scaleFactor_bTagSF_77_eigenvars_B_up_4")
      Output = {1.1852, 1.0098, 1.1802, 0.635, 0.74, 1.142, 0.656, 0.764, 1.179, 0.684, 0.797, 1.23};
    else if(Folder == "scaleFactor_bTagSF_77_eigenvars_B_down_0")
      Output = {1.1659, 0.9939, 1.1615, 0.637, 0.733, 1.144, 0.657, 0.757, 1.181, 0.686, 0.79, 1.233};
    else if(Folder == "scaleFactor_bTagSF_77_eigenvars_B_down_1")
      Output = {1.1816, 1.0067, 1.1766, 0.636, 0.737, 1.143, 0.657, 0.761, 1.18, 0.685, 0.794, 1.231};
    else if(Folder == "scaleFactor_bTagSF_77_eigenvars_B_down_2")
      Output = {1.1899, 1.0139, 1.1854, 0.631, 0.743, 1.142, 0.652, 0.768, 1.179, 0.68, 0.801, 1.23};
    else if(Folder == "scaleFactor_bTagSF_77_eigenvars_B_down_3")
      Output = {1.1851, 1.0097, 1.1794, 0.634, 0.74, 1.142, 0.655, 0.764, 1.179, 0.683, 0.798, 1.231};
    else if(Folder == "scaleFactor_bTagSF_77_eigenvars_B_down_4")
      Output = {1.1853, 1.0099, 1.1795, 0.635, 0.74, 1.142, 0.656, 0.764, 1.179, 0.684, 0.797, 1.231};
    else if(Folder == "scaleFactor_bTagSF_77_eigenvars_C_up_0")
      Output = {1.2807, 1.0893, 1.2828, 0.533, 0.785, 1.144, 0.553, 0.814, 1.186, 0.581, 0.856, 1.248};
    else if(Folder == "scaleFactor_bTagSF_77_eigenvars_C_up_1")
      Output = {1.1691, 0.9961, 1.1634, 0.647, 0.735, 1.142, 0.667, 0.758, 1.179, 0.696, 0.791, 1.228};
    else if(Folder == "scaleFactor_bTagSF_77_eigenvars_C_up_2")
      Output = {1.1768, 1.003, 1.1705, 0.655, 0.731, 1.142, 0.676, 0.754, 1.178, 0.704, 0.786, 1.227};
    else if(Folder == "scaleFactor_bTagSF_77_eigenvars_C_up_3")
      Output = {1.1905, 1.0137, 1.1854, 0.628, 0.743, 1.142, 0.649, 0.767, 1.18, 0.677, 0.801, 1.232};
    else if(Folder == "scaleFactor_bTagSF_77_eigenvars_C_down_0")
      Output = {1.1032, 0.9412, 1.0928, 0.721, 0.704, 1.14, 0.742, 0.725, 1.173, 0.768, 0.751, 1.215};
    else if(Folder == "scaleFactor_bTagSF_77_eigenvars_C_down_1")
      Output = {1.2018, 1.0235, 1.1966, 0.623, 0.745, 1.142, 0.643, 0.77, 1.18, 0.672, 0.804, 1.233};
    else if(Folder == "scaleFactor_bTagSF_77_eigenvars_C_down_2")
      Output = {1.1937, 1.0168, 1.1898, 0.614, 0.749, 1.143, 0.635, 0.774, 1.181, 0.664, 0.809, 1.234};
    else if(Folder == "scaleFactor_bTagSF_77_eigenvars_C_down_3")
      Output = {1.1801, 1.0053, 1.1746, 0.641, 0.737, 1.142, 0.662, 0.761, 1.179, 0.69, 0.793, 1.229};
    else if(Folder == "scaleFactor_bTagSF_77_eigenvars_Light_up_0")
      Output = {1.3139, 1.1213, 1.2991, 0.799, 0.717, 1.123, 0.818, 0.734, 1.15, 0.84, 0.755, 1.181};
    else if(Folder == "scaleFactor_bTagSF_77_eigenvars_Light_up_1")
      Output = {1.1838, 1.0074, 1.1739, 0.678, 0.721, 1.141, 0.699, 0.743, 1.177, 0.727, 0.773, 1.223};
    else if(Folder == "scaleFactor_bTagSF_77_eigenvars_Light_up_2")
      Output = {1.174, 1.0007, 1.1699, 0.632, 0.736, 1.144, 0.653, 0.761, 1.181, 0.681, 0.794, 1.233};
    else if(Folder == "scaleFactor_bTagSF_77_eigenvars_Light_up_3")
      Output = {1.1885, 1.013, 1.1856, 0.617, 0.749, 1.142, 0.637, 0.774, 1.18, 0.666, 0.808, 1.233};
    else if(Folder == "scaleFactor_bTagSF_77_eigenvars_Light_up_4")
      Output = {1.1839, 1.009, 1.1796, 0.623, 0.744, 1.143, 0.644, 0.769, 1.18, 0.672, 0.803, 1.233};
    else if(Folder == "scaleFactor_bTagSF_77_eigenvars_Light_up_5")
      Output = {1.1856, 1.0098, 1.1797, 0.644, 0.736, 1.142, 0.665, 0.76, 1.179, 0.693, 0.792, 1.229};
    else if(Folder == "scaleFactor_bTagSF_77_eigenvars_Light_up_6")
      Output = {1.1857, 1.0101, 1.1801, 0.643, 0.736, 1.142, 0.664, 0.76, 1.179, 0.692, 0.793, 1.229};
    else if(Folder == "scaleFactor_bTagSF_77_eigenvars_Light_up_7")
      Output = {1.1865, 1.0104, 1.1814, 0.631, 0.742, 1.142, 0.652, 0.766, 1.18, 0.68, 0.799, 1.231};
    else if(Folder == "scaleFactor_bTagSF_77_eigenvars_Light_up_8")
      Output = {1.1851, 1.0092, 1.18, 0.628, 0.742, 1.142, 0.649, 0.767, 1.18, 0.677, 0.801, 1.232};
    else if(Folder == "scaleFactor_bTagSF_77_eigenvars_Light_up_9")
      Output = {1.1854, 1.01, 1.18, 0.635, 0.74, 1.142, 0.656, 0.764, 1.179, 0.685, 0.797, 1.23};
    else if(Folder == "scaleFactor_bTagSF_77_eigenvars_Light_up_10")
      Output = {1.1852, 1.0092, 1.1794, 0.634, 0.74, 1.142, 0.654, 0.765, 1.179, 0.683, 0.798, 1.231};
    else if(Folder == "scaleFactor_bTagSF_77_eigenvars_Light_up_11")
      Output = {1.1852, 1.0098, 1.1797, 0.634, 0.74, 1.142, 0.655, 0.764, 1.179, 0.683, 0.797, 1.231};
    else if(Folder == "scaleFactor_bTagSF_77_eigenvars_Light_down_0")
      Output = {1.0788, 0.9169, 1.081, 0.472, 0.759, 1.162, 0.491, 0.79, 1.211, 0.521, 0.838, 1.284};
    else if(Folder == "scaleFactor_bTagSF_77_eigenvars_Light_down_1")
      Output = {1.1868, 1.0117, 1.1857, 0.592, 0.758, 1.143, 0.612, 0.785, 1.182, 0.641, 0.822, 1.238};
    else if(Folder == "scaleFactor_bTagSF_77_eigenvars_Light_down_2")
      Output = {1.1967, 1.02, 1.1904, 0.638, 0.743, 1.141, 0.658, 0.767, 1.177, 0.687, 0.8, 1.228};
    else if(Folder == "scaleFactor_bTagSF_77_eigenvars_Light_down_3")
      Output = {1.182, 1.0061, 1.1742, 0.653, 0.731, 1.142, 0.674, 0.754, 1.179, 0.702, 0.786, 1.228};
    else if(Folder == "scaleFactor_bTagSF_77_eigenvars_Light_down_4")
      Output = {1.1864, 1.0112, 1.1806, 0.647, 0.735, 1.142, 0.668, 0.759, 1.178, 0.696, 0.791, 1.228};
    else if(Folder == "scaleFactor_bTagSF_77_eigenvars_Light_down_5")
      Output = {1.1848, 1.0091, 1.1798, 0.626, 0.743, 1.142, 0.646, 0.768, 1.18, 0.675, 0.802, 1.232};
    else if(Folder == "scaleFactor_bTagSF_77_eigenvars_Light_down_6")
      Output = {1.1848, 1.0091, 1.1796, 0.627, 0.743, 1.142, 0.647, 0.768, 1.18, 0.676, 0.801, 1.232};
    else if(Folder == "scaleFactor_bTagSF_77_eigenvars_Light_down_7")
      Output = {1.1841, 1.0086, 1.1783, 0.638, 0.738, 1.142, 0.659, 0.762, 1.179, 0.688, 0.794, 1.23};
    else if(Folder == "scaleFactor_bTagSF_77_eigenvars_Light_down_8")
      Output = {1.1854, 1.0099, 1.1798, 0.642, 0.737, 1.142, 0.662, 0.761, 1.179, 0.691, 0.793, 1.229};
    else if(Folder == "scaleFactor_bTagSF_77_eigenvars_Light_down_9")
      Output = {1.1851, 1.0097, 1.1796, 0.634, 0.74, 1.142, 0.655, 0.764, 1.179, 0.683, 0.797, 1.231};
    else if(Folder == "scaleFactor_bTagSF_77_eigenvars_Light_down_10")
      Output = {1.1851, 1.0097, 1.18, 0.636, 0.739, 1.142, 0.657, 0.763, 1.179, 0.685, 0.796, 1.23};
    else if(Folder == "scaleFactor_bTagSF_77_eigenvars_Light_down_11")
      Output = {1.1852, 1.0097, 1.1796, 0.635, 0.74, 1.142, 0.656, 0.764, 1.179, 0.685, 0.797, 1.23};
    else if(Folder == "CA_up")
      Output = {1.195, 1.0223, 1.1977, 0.675, 0.698, 1.149, 0.697, 0.721, 1.186, 0.725, 0.75, 1.234};
    else if (Folder == "CA_down")
      Output = {1.1674, 0.9917, 1.1487, 0.703, 0.721, 1.137, 0.724, 0.742, 1.171, 0.75, 0.769, 1.214};
    else if(Folder == "Fcc_up")
      Output = {1.1723, 0.9991, 1.1655, 0.704, 0.657, 1.158, 0.727, 0.678, 1.195, 0.755, 0.705, 1.242};
    else if(Folder == "Fcc_down")
      Output = {1.1901, 1.0149, 1.1814, 0.674, 0.761, 1.129, 0.694, 0.783, 1.162, 0.721, 0.814, 1.207};
    else if(Folder == "Flight_up")
      Output = {1.1809, 1.0051, 1.1781, 0.607, 0.707, 1.157, 0.629, 0.733, 1.198, 0.659, 0.767, 1.255};
    else if(Folder == "Flight_down")
      Output = {1.1816, 1.0088, 1.169, 0.773, 0.712, 1.129, 0.793, 0.73, 1.158, 0.817, 0.752, 1.193};
    else
      Output = {1.1812, 1.007, 1.1732, 0.689, 0.709, 1.143, 0.71, 0.731, 1.178, 0.738, 0.76, 1.224};  // default back to nominal
    
    
  }
  else{
    
    if(Folder == "MET_SoftTrk_ResoPara")
      Output = {1.2733, 1.132, 1.131, 0.429, 1.096, 1.062, 0.442, 1.128, 1.092, 0.465, 1.188, 1.151};
    else if(Folder == "MET_SoftTrk_ResoPerp")
      Output = {1.2709, 1.1284, 1.1369, 0.411, 1.108, 1.062, 0.422, 1.14, 1.092, 0.446, 1.203, 1.153};
    else if(Folder == "MET_SoftTrk_ScaleUp")
      Output = {1.2701, 1.1334, 1.1317, 0.435, 1.096, 1.061, 0.447, 1.127, 1.091, 0.471, 1.186, 1.149};
    else if(Folder == "MET_SoftTrk_ScaleDown")
      Output = {1.264, 1.1346, 1.1316, 0.465, 1.079, 1.062, 0.478, 1.108, 1.091, 0.502, 1.164, 1.146};
    else if(Folder == "EG_SCALE_ALL__1up")
      Output = {1.2664, 1.1328, 1.1315, 0.474, 1.074, 1.062, 0.486, 1.103, 1.091, 0.51, 1.158, 1.144};
    else if(Folder == "EG_SCALE_ALL__1down")
      Output = {1.2664, 1.1327, 1.1319, 0.474, 1.074, 1.062, 0.487, 1.103, 1.091, 0.511, 1.158, 1.144};
    else if(Folder == "EG_RESOLUTION_ALL__1up")
      Output = {1.2688, 1.1343, 1.1333, 0.454, 1.086, 1.061, 0.467, 1.116, 1.091, 0.49, 1.173, 1.146};
    else if(Folder == "EG_RESOLUTION_ALL__1down")
      Output = {1.2702, 1.1364, 1.1347, 0.452, 1.085, 1.062, 0.465, 1.115, 1.091, 0.489, 1.172, 1.147};
    else if(Folder == "MUONS_ID__1up")
      Output = {1.261, 1.1313, 1.1338, 0.481, 1.081, 1.058, 0.494, 1.11, 1.086, 0.518, 1.163, 1.139};
    else if(Folder == "MUONS_ID__1down")
      Output = {1.2668, 1.1381, 1.1356, 0.472, 1.079, 1.061, 0.485, 1.108, 1.089, 0.509, 1.163, 1.143};
    else if(Folder == "MUONS_MS__1up")
      Output = {1.2671, 1.1334, 1.1329, 0.463, 1.084, 1.061, 0.475, 1.114, 1.089, 0.499, 1.17, 1.144};
    else if(Folder == "MUONS_MS__1down")
      Output = {1.2683, 1.138, 1.1361, 0.464, 1.077, 1.063, 0.477, 1.106, 1.092, 0.501, 1.162, 1.147};
    else if(Folder == "MUONS_SCALE__1up")
      Output = {1.2696, 1.1359, 1.1345, 0.453, 1.087, 1.061, 0.466, 1.117, 1.091, 0.49, 1.174, 1.146};
    else if(Folder == "MUONS_SCALE__1down")
      Output = {1.2681, 1.1369, 1.1327, 0.45, 1.088, 1.061, 0.463, 1.118, 1.091, 0.486, 1.175, 1.147};
    else if(Folder == "JET_19NP_JET_BJES_Response__1up")
      Output = {1.2719, 1.1563, 1.1426, 0.341, 1.137, 1.064, 0.351, 1.173, 1.098, 0.373, 1.245, 1.165};
    else if(Folder == "JET_19NP_JET_BJES_Response__1down")
      Output = {1.2805, 1.1665, 1.1521, 0.355, 1.128, 1.064, 0.366, 1.163, 1.097, 0.388, 1.233, 1.163};
    else if(Folder == "JET_19NP_JET_EffectiveNP_1__1up")
      Output = {1.2377, 1.1126, 1.0304, 0.227, 1.166, 1.07, 0.235, 1.208, 1.109, 0.252, 1.291, 1.185};
    else if(Folder == "JET_19NP_JET_EffectiveNP_1__1down")
      Output = {1.3323, 1.2578, 1.2365, 0.42, 1.104, 1.063, 0.433, 1.138, 1.096, 0.456, 1.199, 1.155};
    else if(Folder == "JET_19NP_JET_EffectiveNP_2__1up")
      Output = {1.2756, 1.203, 1.1793, 0.355, 1.146, 1.059, 0.366, 1.181, 1.091, 0.388, 1.252, 1.157};
    else if(Folder == "JET_19NP_JET_EffectiveNP_2__1down")
      Output = {1.271, 1.1491, 1.1333, 0.299, 1.149, 1.066, 0.309, 1.187, 1.102, 0.329, 1.264, 1.173};
    else if(Folder == "JET_19NP_JET_EffectiveNP_3__1up")
      Output = {1.2812, 1.1485, 1.1347, 0.36, 1.116, 1.067, 0.371, 1.151, 1.101, 0.393, 1.22, 1.167};
    else if(Folder == "JET_19NP_JET_EffectiveNP_3__1down")
      Output = {1.2786, 1.1762, 1.1516, 0.339, 1.143, 1.062, 0.35, 1.179, 1.096, 0.371, 1.251, 1.163};
    else if(Folder == "JET_19NP_JET_EffectiveNP_4__1up")
      Output = {1.2819, 1.1648, 1.1546, 0.307, 1.153, 1.064, 0.317, 1.19, 1.099, 0.337, 1.267, 1.17};
    else if(Folder == "JET_19NP_JET_EffectiveNP_4__1down")
      Output = {1.2797, 1.1539, 1.1354, 0.359, 1.12, 1.066, 0.37, 1.155, 1.1, 0.392, 1.224, 1.166};
    else if(Folder == "JET_19NP_JET_EffectiveNP_5__1up")
      Output = {1.2738, 1.1556, 1.1402, 0.393, 1.112, 1.063, 0.405, 1.145, 1.095, 0.428, 1.21, 1.157};
    else if(Folder == "JET_19NP_JET_EffectiveNP_5__1down")
      Output = {1.2775, 1.1616, 1.1511, 0.344, 1.135, 1.064, 0.354, 1.171, 1.097, 0.376, 1.242, 1.165};
    else if(Folder == "JET_19NP_JET_EffectiveNP_6restTerm__1up")
      Output = {1.2743, 1.1621, 1.1401, 0.369, 1.123, 1.063, 0.38, 1.158, 1.096, 0.403, 1.226, 1.16};
    else if(Folder == "JET_19NP_JET_EffectiveNP_6restTerm__1down")
      Output = {1.2747, 1.1597, 1.1467, 0.374, 1.122, 1.063, 0.386, 1.156, 1.095, 0.408, 1.223, 1.159};
    else if(Folder == "JET_19NP_JET_EtaIntercalibration_Modelling__1up")
      Output = {1.2782, 1.1485, 1.122, 0.153, 1.2, 1.073, 0.159, 1.247, 1.116, 0.171, 1.345, 1.203};
    else if(Folder == "JET_19NP_JET_EtaIntercalibration_Modelling__1down")
      Output = {1.2887, 1.1906, 1.1875, 0.492, 1.067, 1.062, 0.505, 1.096, 1.09, 0.529, 1.147, 1.142};
    else if(Folder == "JET_19NP_JET_EtaIntercalibration_NonClosure__1up")
      Output = {1.2695, 1.1684, 1.1391, 0.402, 1.115, 1.061, 0.414, 1.147, 1.091, 0.437, 1.211, 1.152};
    else if(Folder == "JET_19NP_JET_EtaIntercalibration_NonClosure__1down")
      Output = {1.2728, 1.1594, 1.1444, 0.377, 1.12, 1.063, 0.389, 1.154, 1.095, 0.411, 1.221, 1.159};
    else if(Folder == "JET_19NP_JET_EtaIntercalibration_TotalStat__1up")
      Output = {1.2716, 1.148, 1.1306, 0.301, 1.148, 1.066, 0.311, 1.186, 1.101, 0.332, 1.263, 1.173};
    else if(Folder == "JET_19NP_JET_EtaIntercalibration_TotalStat__1down")
      Output = {1.2707, 1.1964, 1.1696, 0.413, 1.121, 1.057, 0.425, 1.153, 1.087, 0.448, 1.216, 1.146};
    else if(Folder == "JET_19NP_JET_Flavor_Response__1up")
      Output = {1.2742, 1.2119, 1.1913, 0.421, 1.117, 1.058, 0.433, 1.149, 1.088, 0.456, 1.211, 1.147};
    else if(Folder == "JET_19NP_JET_Flavor_Response__1down")
      Output = {1.2803, 1.1531, 1.1275, 0.165, 1.198, 1.072, 0.171, 1.244, 1.113, 0.185, 1.341, 1.2};
    else if(Folder == "JET_19NP_JET_Flavor_Composition__1up")
      Output = {1.2467, 1.115, 1.0463, 0.295, 1.132, 1.069, 0.304, 1.17, 1.105, 0.323, 1.243, 1.174};
    else if(Folder == "JET_19NP_JET_Flavor_Composition__1down")
      Output = {1.3114, 1.2494, 1.2241, 0.483, 1.086, 1.058, 0.497, 1.117, 1.088, 0.521, 1.171, 1.141};
    else if(Folder == "JET_19NP_JET_PunchThrough_MC15__1up")
      Output = {1.2754, 1.161, 1.1462, 0.362, 1.126, 1.064, 0.373, 1.161, 1.096, 0.396, 1.23, 1.162};
    else if(Folder == "JET_19NP_JET_PunchThrough_MC15__1down")
      Output = {1.2754, 1.161, 1.1461, 0.362, 1.126, 1.064, 0.373, 1.161, 1.096, 0.396, 1.23, 1.162};
    else if(Folder == "JET_19NP_JET_Pileup_PtTerm__1up")
      Output = {1.2775, 1.1696, 1.1509, 0.309, 1.151, 1.064, 0.319, 1.189, 1.099, 0.34, 1.266, 1.17};
    else if(Folder == "JET_19NP_JET_Pileup_PtTerm__1down")
      Output = {1.2745, 1.1469, 1.1407, 0.409, 1.103, 1.063, 0.421, 1.135, 1.094, 0.444, 1.198, 1.155};
    else if(Folder == "JET_19NP_JET_Pileup_OffsetNPV__1up")
      Output = {1.2659, 1.1623, 1.1388, 0.44, 1.098, 1.06, 0.453, 1.129, 1.089, 0.476, 1.187, 1.145};
    else if(Folder == "JET_19NP_JET_Pileup_OffsetNPV__1down")
      Output = {1.2923, 1.1658, 1.1563, 0.225, 1.177, 1.07, 0.233, 1.22, 1.109, 0.25, 1.309, 1.19};
    else if(Folder == "JET_19NP_JET_Pileup_OffsetMu__1up")
      Output = {1.2717, 1.1826, 1.153, 0.388, 1.125, 1.06, 0.399, 1.158, 1.091, 0.422, 1.224, 1.153};
    else if(Folder == "JET_19NP_JET_Pileup_OffsetMu__1down")
      Output = {1.2781, 1.1465, 1.132, 0.375, 1.11, 1.066, 0.387, 1.145, 1.099, 0.409, 1.212, 1.163};
    else if(Folder == "JET_19NP_JET_Pileup_RhoTopology__1up")
      Output = {1.2783, 1.1431, 1.1122, 0.151, 1.196, 1.075, 0.157, 1.244, 1.117, 0.169, 1.343, 1.206};
    else if(Folder == "JET_19NP_JET_Pileup_RhoTopology__1down")
      Output = {1.2845, 1.2151, 1.1986, 0.429, 1.11, 1.058, 0.441, 1.141, 1.089, 0.465, 1.202, 1.146};
    else if(Folder == "JET_19NP_JET_SingleParticle_HighPt__1up")
      Output = {1.2754, 1.161, 1.1461, 0.362, 1.126, 1.064, 0.373, 1.161, 1.096, 0.396, 1.23, 1.162};
    else if(Folder == "JET_19NP_JET_SingleParticle_HighPt__1down")
      Output = {1.2754, 1.161, 1.1461, 0.362, 1.126, 1.064, 0.373, 1.161, 1.096, 0.396, 1.23, 1.162};
    else if(Folder == "JET_JER_SINGLE_NP__1up")
      Output = {1.304, 1.1327, 1.1, 0.165, 1.162, 1.083, 0.172, 1.21, 1.128, 0.185, 1.302, 1.213};
    else if(Folder == "scaleFactor_leptonSF_EL_SF_Trigger_UP")
     Output = {1.2701, 1.1365, 1.1349, 0.453, 1.085, 1.062, 0.465, 1.115, 1.091, 0.489, 1.172, 1.147};
    else if(Folder == "scaleFactor_leptonSF_EL_SF_Trigger_DOWN")
      Output = {1.2701, 1.1365, 1.1349, 0.453, 1.085, 1.062, 0.465, 1.115, 1.091, 0.489, 1.172, 1.147};
    else if(Folder == "scaleFactor_leptonSF_EL_SF_Reco_UP")
      Output = {1.2701, 1.1365, 1.1349, 0.453, 1.085, 1.062, 0.465, 1.115, 1.091, 0.489, 1.172, 1.147};
    else if(Folder == "scaleFactor_leptonSF_EL_SF_Reco_DOWN")
      Output = {1.2701, 1.1365, 1.1349, 0.453, 1.085, 1.062, 0.465, 1.115, 1.091, 0.489, 1.172, 1.147};
    else if(Folder == "scaleFactor_leptonSF_EL_SF_ID_UP")
      Output = {1.2701, 1.1365, 1.1349, 0.453, 1.085, 1.062, 0.465, 1.115, 1.091, 0.489, 1.172, 1.147};
    else if(Folder == "scaleFactor_leptonSF_EL_SF_ID_DOWN")
      Output = {1.2701, 1.1365, 1.1349, 0.453, 1.085, 1.062, 0.465, 1.115, 1.091, 0.489, 1.172, 1.147};
    else if(Folder == "scaleFactor_leptonSF_EL_SF_Isol_UP")
      Output = {1.2701, 1.1365, 1.1349, 0.453, 1.085, 1.062, 0.465, 1.115, 1.091, 0.489, 1.172, 1.147};
    else if(Folder == "scaleFactor_leptonSF_EL_SF_Isol_DOWN")
      Output = {1.2701, 1.1365, 1.1349, 0.453, 1.085, 1.062, 0.465, 1.115, 1.091, 0.489, 1.172, 1.147};
    else if(Folder == "scaleFactor_leptonSF_MU_SF_Trigger_STAT_UP")
      Output = {1.2521, 1.1204, 1.1189, 0.455, 1.081, 1.063, 0.468, 1.111, 1.092, 0.492, 1.168, 1.148};
    else if(Folder == "scaleFactor_leptonSF_MU_SF_Trigger_STAT_DOWN")
      Output = {1.2891, 1.1533, 1.1515, 0.45, 1.09, 1.061, 0.462, 1.12, 1.09, 0.486, 1.177, 1.146};
    else if(Folder == "scaleFactor_leptonSF_MU_SF_Trigger_SYST_UP")
      Output = {1.2623, 1.1286, 1.1277, 0.456, 1.082, 1.062, 0.469, 1.112, 1.092, 0.493, 1.168, 1.147};
    else if(Folder == "scaleFactor_leptonSF_MU_SF_Trigger_SYST_DOWN")
      Output = {1.2779, 1.1431, 1.1418, 0.449, 1.088, 1.061, 0.461, 1.119, 1.091, 0.485, 1.176, 1.147};
    else if(Folder == "scaleFactor_leptonSF_MU_SF_ID_STAT_UP")
      Output = {1.2674, 1.1332, 1.1322, 0.454, 1.084, 1.062, 0.466, 1.114, 1.092, 0.49, 1.171, 1.147};
    else if(Folder == "scaleFactor_leptonSF_MU_SF_ID_STAT_DOWN")
      Output = {1.2728, 1.1389, 1.1372, 0.451, 1.086, 1.062, 0.464, 1.116, 1.091, 0.488, 1.174, 1.147};
    else if(Folder == "scaleFactor_leptonSF_MU_SF_ID_SYST_UP")
      Output = {1.2647, 1.1309, 1.1292, 0.455, 1.083, 1.062, 0.467, 1.113, 1.092, 0.491, 1.17, 1.148};
    else if(Folder == "scaleFactor_leptonSF_MU_SF_ID_SYST_DOWN")
      Output = {1.2756, 1.1412, 1.1399, 0.45, 1.087, 1.062, 0.463, 1.118, 1.091, 0.487, 1.175, 1.147};
    else if(Folder == "scaleFactor_leptonSF_MU_SF_Isol_STAT_UP")
      Output = {1.2694, 1.1359, 1.1343, 0.453, 1.085, 1.062, 0.465, 1.115, 1.091, 0.489, 1.172, 1.147};
    else if(Folder == "scaleFactor_leptonSF_MU_SF_Isol_STAT_DOWN")
      Output = {1.2708, 1.1368, 1.1352, 0.452, 1.085, 1.062, 0.465, 1.116, 1.091, 0.489, 1.173, 1.147};
    else if(Folder == "scaleFactor_leptonSF_MU_SF_Isol_SYST_UP")
      Output = {1.2665, 1.1324, 1.1316, 0.454, 1.084, 1.062, 0.466, 1.114, 1.092, 0.49, 1.171, 1.147};
    else if(Folder == "scaleFactor_leptonSF_MU_SF_Isol_SYST_DOWN")
      Output = {1.2738, 1.1396, 1.1379, 0.451, 1.086, 1.062, 0.464, 1.116, 1.091, 0.488, 1.174, 1.147};
    else if(Folder == "scaleFactor_leptonSF_MU_SF_TTVA_STAT_UP")
      Output = {1.2687, 1.1342, 1.1333, 0.453, 1.084, 1.062, 0.466, 1.114, 1.092, 0.49, 1.171, 1.147};
    else if(Folder == "scaleFactor_leptonSF_MU_SF_TTVA_STAT_DOWN")
      Output = {1.2715, 1.1378, 1.1363, 0.452, 1.086, 1.062, 0.464, 1.116, 1.091, 0.488, 1.173, 1.147};
    else if(Folder == "scaleFactor_leptonSF_MU_SF_TTVA_SYST_UP")
     Output = {1.2692, 1.1357, 1.1342, 0.453, 1.085, 1.062, 0.465, 1.115, 1.091, 0.489, 1.172, 1.147};
    else if(Folder == "scaleFactor_leptonSF_MU_SF_TTVA_SYST_DOWN")
      Output = {1.271, 1.1371, 1.1355, 0.452, 1.085, 1.062, 0.465, 1.115, 1.091, 0.489, 1.172, 1.147};
    else if(Folder == "scaleFactor_bTagSF_77_extrapolation_up")
      Output = {1.2696, 1.1358, 1.1344, 0.452, 1.085, 1.062, 0.465, 1.115, 1.091, 0.488, 1.173, 1.147};
    else if(Folder == "scaleFactor_bTagSF_77_extrapolation_down")
      Output = {1.2706, 1.1368, 1.1353, 0.453, 1.085, 1.062, 0.466, 1.115, 1.091, 0.489, 1.172, 1.147};
    else if(Folder == "scaleFactor_bTagSF_77_extrapolation_from_charm_up")
      Output = {1.2679, 1.1343, 1.1336, 0.464, 1.08, 1.062, 0.477, 1.11, 1.091, 0.501, 1.165, 1.145};
    else if(Folder == "scaleFactor_bTagSF_77_extrapolation_from_charm_down")
      Output = {1.2723, 1.1376, 1.1362, 0.441, 1.09, 1.062, 0.454, 1.121, 1.092, 0.477, 1.179, 1.149};
    else if(Folder == "scaleFactor_jvt_UP")
      Output = {1.2168, 1.0774, 1.0576, 0.459, 1.073, 1.065, 0.472, 1.103, 1.094, 0.496, 1.159, 1.15};
    else if(Folder == "scaleFactor_jvt_DOWN")
      Output = {1.3262, 1.1984, 1.2174, 0.446, 1.097, 1.059, 0.459, 1.128, 1.089, 0.482, 1.186, 1.145};
    else if(Folder == "scaleFactor_bTagSF_77_eigenvars_B_up_0")
      Output = {1.2904, 1.1553, 1.1532, 0.452, 1.085, 1.062, 0.465, 1.115, 1.091, 0.489, 1.172, 1.147};
    else if(Folder == "scaleFactor_bTagSF_77_eigenvars_B_up_1")
      Output = {1.2736, 1.1393, 1.1379, 0.453, 1.085, 1.062, 0.466, 1.116, 1.091, 0.489, 1.173, 1.147};
    else if(Folder == "scaleFactor_bTagSF_77_eigenvars_B_up_2")
      Output = {1.2655, 1.1314, 1.1305, 0.453, 1.084, 1.062, 0.466, 1.115, 1.091, 0.49, 1.172, 1.147};
    else if(Folder == "scaleFactor_bTagSF_77_eigenvars_B_up_3")
      Output = {1.2703, 1.1367, 1.1351, 0.453, 1.085, 1.062, 0.465, 1.115, 1.091, 0.489, 1.172, 1.147};
    else if(Folder == "scaleFactor_bTagSF_77_eigenvars_B_up_4")
      Output = {1.27, 1.1365, 1.1348, 0.453, 1.085, 1.062, 0.465, 1.115, 1.091, 0.489, 1.172, 1.147};
    else if(Folder == "scaleFactor_bTagSF_77_eigenvars_B_down_0")
      Output = {1.2503, 1.1179, 1.1167, 0.453, 1.085, 1.062, 0.466, 1.115, 1.091, 0.49, 1.172, 1.147};
    else if(Folder == "scaleFactor_bTagSF_77_eigenvars_B_down_1")
      Output = {1.2666, 1.1325, 1.1312, 0.452, 1.085, 1.062, 0.465, 1.115, 1.092, 0.488, 1.172, 1.148};
    else if(Folder == "scaleFactor_bTagSF_77_eigenvars_B_down_2")
      Output = {1.2747, 1.1407, 1.1392, 0.452, 1.086, 1.062, 0.464, 1.116, 1.091, 0.488, 1.173, 1.147};
    else if(Folder == "scaleFactor_bTagSF_77_eigenvars_B_down_3")
      Output = {1.2699, 1.136, 1.1343, 0.452, 1.085, 1.062, 0.465, 1.116, 1.091, 0.489, 1.173, 1.147};
    else if(Folder == "scaleFactor_bTagSF_77_eigenvars_B_down_4")
      Output = {1.2701, 1.1365, 1.1349, 0.453, 1.085, 1.062, 0.465, 1.115, 1.091, 0.489, 1.172, 1.147};
    else if(Folder == "scaleFactor_bTagSF_77_eigenvars_C_up_0")
      Output = {1.379, 1.2325, 1.2294, 0.283, 1.167, 1.064, 0.292, 1.207, 1.099, 0.312, 1.287, 1.173};
    else if(Folder == "scaleFactor_bTagSF_77_eigenvars_C_up_1")
      Output = {1.2509, 1.1186, 1.1175, 0.481, 1.071, 1.062, 0.494, 1.1, 1.09, 0.518, 1.153, 1.143};
    else if(Folder == "scaleFactor_bTagSF_77_eigenvars_C_up_2")
      Output = {1.2618, 1.1287, 1.1273, 0.468, 1.078, 1.062, 0.481, 1.107, 1.09, 0.505, 1.163, 1.145};
    else if(Folder == "scaleFactor_bTagSF_77_eigenvars_C_up_3")
      Output = {1.2762, 1.1411, 1.1396, 0.441, 1.09, 1.062, 0.454, 1.121, 1.092, 0.477, 1.18, 1.149};
    else if(Folder == "scaleFactor_bTagSF_77_eigenvars_C_down_0")
      Output = {1.177, 1.0542, 1.0537, 0.608, 1.016, 1.058, 0.622, 1.038, 1.082, 0.645, 1.077, 1.122};
    else if(Folder == "scaleFactor_bTagSF_77_eigenvars_C_down_1")
      Output = {1.2901, 1.1533, 1.1512, 0.423, 1.099, 1.062, 0.435, 1.131, 1.093, 0.459, 1.192, 1.152};
    else if(Folder == "scaleFactor_bTagSF_77_eigenvars_C_down_2")
      Output = {1.2785, 1.1433, 1.1416, 0.437, 1.092, 1.062, 0.449, 1.123, 1.092, 0.473, 1.182, 1.15};
    else if(Folder == "scaleFactor_bTagSF_77_eigenvars_C_down_3")
      Output = {1.264, 1.1309, 1.1294, 0.464, 1.08, 1.062, 0.476, 1.11, 1.091, 0.5, 1.165, 1.146};
    else if(Folder == "scaleFactor_bTagSF_77_eigenvars_Light_up_0")
      Output = {1.3955, 1.2522, 1.251, 0.716, 0.992, 1.048, 0.728, 1.009, 1.066, 0.748, 1.036, 1.095};
    else if(Folder == "scaleFactor_bTagSF_77_eigenvars_Light_up_1")
      Output = {1.2705, 1.136, 1.1344, 0.468, 1.079, 1.061, 0.481, 1.108, 1.09, 0.505, 1.163, 1.144};
    else if(Folder == "scaleFactor_bTagSF_77_eigenvars_Light_up_2")
      Output = {1.2594, 1.1259, 1.1241, 0.426, 1.094, 1.063, 0.438, 1.126, 1.094, 0.462, 1.186, 1.153};
    else if(Folder == "scaleFactor_bTagSF_77_eigenvars_Light_up_3")
      Output = {1.2715, 1.1373, 1.1366, 0.458, 1.083, 1.062, 0.471, 1.113, 1.091, 0.494, 1.169, 1.146};
    else if(Folder == "scaleFactor_bTagSF_77_eigenvars_Light_up_4")
      Output = {1.2686, 1.1344, 1.1334, 0.447, 1.087, 1.062, 0.46, 1.117, 1.092, 0.483, 1.175, 1.148};
    else if(Folder == "scaleFactor_bTagSF_77_eigenvars_Light_up_5")
      Output = {1.2712, 1.1372, 1.1356, 0.454, 1.085, 1.062, 0.467, 1.115, 1.091, 0.49, 1.172, 1.147};
    else if(Folder == "scaleFactor_bTagSF_77_eigenvars_Light_up_6")
      Output = {1.2709, 1.137, 1.1352, 0.452, 1.085, 1.062, 0.465, 1.116, 1.091, 0.489, 1.173, 1.147};
    else if(Folder == "scaleFactor_bTagSF_77_eigenvars_Light_up_7")
      Output = {1.2711, 1.1373, 1.1355, 0.456, 1.084, 1.062, 0.468, 1.114, 1.091, 0.492, 1.171, 1.147};
    else if(Folder == "scaleFactor_bTagSF_77_eigenvars_Light_up_8")
      Output = {1.2699, 1.1356, 1.1343, 0.449, 1.087, 1.062, 0.462, 1.117, 1.092, 0.485, 1.175, 1.148};
    else if(Folder == "scaleFactor_bTagSF_77_eigenvars_Light_up_9")
      Output = {1.2703, 1.1364, 1.1346, 0.454, 1.084, 1.062, 0.467, 1.114, 1.091, 0.49, 1.171, 1.147};
    else if(Folder == "scaleFactor_bTagSF_77_eigenvars_Light_up_10")
      Output = {1.2701, 1.1355, 1.134, 0.452, 1.086, 1.062, 0.464, 1.116, 1.091, 0.488, 1.173, 1.147};
    else if(Folder == "scaleFactor_bTagSF_77_eigenvars_Light_up_11")
      Output = {1.2701, 1.1362, 1.1348, 0.452, 1.085, 1.062, 0.465, 1.116, 1.091, 0.488, 1.173, 1.147};
    else if(Folder == "scaleFactor_bTagSF_77_eigenvars_Light_down_0")
      Output = {1.1653, 1.0383, 1.0372, 0.207, 1.166, 1.076, 0.215, 1.211, 1.118, 0.232, 1.302, 1.202};
    else if(Folder == "scaleFactor_bTagSF_77_eigenvars_Light_down_1")
      Output = {1.2697, 1.1361, 1.1352, 0.437, 1.091, 1.062, 0.449, 1.122, 1.093, 0.473, 1.182, 1.15};
    else if(Folder == "scaleFactor_bTagSF_77_eigenvars_Light_down_2")
      Output = {1.2811, 1.1464, 1.145, 0.479, 1.076, 1.061, 0.492, 1.104, 1.089, 0.516, 1.158, 1.142};
    else if(Folder == "scaleFactor_bTagSF_77_eigenvars_Light_down_3")
      Output = {1.2687, 1.1346, 1.1331, 0.447, 1.087, 1.062, 0.459, 1.118, 1.092, 0.483, 1.176, 1.148};
    else if(Folder == "scaleFactor_bTagSF_77_eigenvars_Light_down_4")
      Output = {1.2716, 1.1377, 1.1365, 0.458, 1.083, 1.062, 0.471, 1.113, 1.091, 0.494, 1.169, 1.146};
    else if(Folder == "scaleFactor_bTagSF_77_eigenvars_Light_down_5")
      Output = {1.269, 1.1345, 1.1334, 0.451, 1.085, 1.062, 0.464, 1.116, 1.092, 0.488, 1.173, 1.148};
    else if(Folder == "scaleFactor_bTagSF_77_eigenvars_Light_down_6")
      Output = {1.2693, 1.1349, 1.1342, 0.453, 1.085, 1.062, 0.465, 1.115, 1.092, 0.489, 1.172, 1.147};
    else if(Folder == "scaleFactor_bTagSF_77_eigenvars_Light_down_7")
      Output = {1.2691, 1.1346, 1.1333, 0.449, 1.086, 1.062, 0.462, 1.117, 1.092, 0.486, 1.174, 1.148};
    else if(Folder == "scaleFactor_bTagSF_77_eigenvars_Light_down_8")
      Output = {1.2703, 1.1363, 1.1346, 0.456, 1.084, 1.062, 0.469, 1.114, 1.091, 0.493, 1.17, 1.147};
    else if(Folder == "scaleFactor_bTagSF_77_eigenvars_Light_down_9")
      Output = {1.2701, 1.1356, 1.1344, 0.451, 1.086, 1.062, 0.464, 1.116, 1.092, 0.487, 1.173, 1.148};
    else if(Folder == "scaleFactor_bTagSF_77_eigenvars_Light_down_10")
      Output = {1.2701, 1.1363, 1.1346, 0.453, 1.085, 1.062, 0.466, 1.115, 1.091, 0.49, 1.172, 1.147};
    else if(Folder == "scaleFactor_bTagSF_77_eigenvars_Light_down_11")
      Output = {1.2701, 1.1363, 1.1346, 0.453, 1.085, 1.062, 0.466, 1.115, 1.091, 0.49, 1.172, 1.147};
    else if (Folder == "CA_up")
      Output = {1.2832, 1.1512, 1.1528, 0.452, 1.061, 1.07, 0.465, 1.092, 1.101, 0.489, 1.149, 1.158};
    else if(Folder == "CA_down")
      Output = {1.2546, 1.1192, 1.1162, 0.489, 1.084, 1.056, 0.502, 1.111, 1.084, 0.526, 1.164, 1.135};
    else if (Folder == "Fcc_up")
      Output = {1.2631, 1.1306, 1.1302, 0.487, 1.041, 1.07, 0.501, 1.07, 1.1, 0.525, 1.123, 1.154};
    else if (Folder == "Fcc_down")
      Output = {1.2748, 1.1393, 1.1379, 0.453, 1.103, 1.056, 0.465, 1.133, 1.085, 0.489, 1.19, 1.139};
    else if (Folder == "Flight_up")
      Output = {1.2696, 1.1353, 1.134, 0.389, 1.073, 1.076, 0.402, 1.107, 1.111, 0.425, 1.172, 1.176};
    else if (Folder == "Flight_down")
      Output = {1.2684, 1.1347, 1.134, 0.552, 1.072, 1.05, 0.565, 1.096, 1.074, 0.588, 1.141, 1.118};
    else
      Output = {1.2689, 1.1352, 1.1345, 0.47, 1.072, 1.063, 0.483, 1.102, 1.092, 0.507, 1.156, 1.146}; // default back to nominal
    

  }

  return Output;
  
  
}

