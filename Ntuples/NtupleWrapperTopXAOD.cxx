#include "NtupleWrapperTopXAOD.h"

#include "PhysicsHelperFunctions.h"

NtupleWrapperTopXAOD::NtupleWrapperTopXAOD( const AnalysisParams_t analysisParameters ):
  NtupleWrapper< TopXAOD >( analysisParameters )
{
#ifdef __MOMA__
   m_moma = MoMATool::GetHandle();
   cout << "INFO: ATLAS ROOTCORE detected. MoMA tool initialized." << endl;
#endif
  unsigned long isData = m_config.custom_params_flag[ "isRealData" ];
  m_ntuple_particle = NULL;
  m_ntuple_parton = NULL;
  m_dumper_mctruth = NULL;
  m_treeName = m_config.treeName;

  if( isData ) return;
    
   m_lumi = 1;
   m_lumiWeight = 1;
   m_doLumiReweight = m_config.custom_params_flag["lumi_reweight"] ;
   if( m_doLumiReweight ) 
   {   
  	  const string nEventsFilename        = m_config.custom_params_string["lumifile"]; 
  	  if( nEventsFilename == "" )
  	  {
  	  	cout << "Error: asking for lumi_reweight, but the file containing the number of events has not been provided\n";
  	  	cout << "Lumi reweight will not be applied\n";
  	  	m_doLumiReweight = false;
  	  }
  	  else
  	  {
  	  	m_lumi = m_config.custom_params_numeric[ "luminosity" ];
  	  	ifstream in( nEventsFilename );
  	  	int id;
  	  	in >> id >> m_nEvents;
	 	 cout << "Sample " << id << " contains " << m_nEvents << " events\n"; 
	 }	  
 	
   }

   

  unsigned long isMCSignal = m_config.custom_params_flag["isMCSignal"];
   if( !isMCSignal ) return;
  const string mcfilename        = m_config.custom_params_string["mcfile"]; 
 
   // open truth ntuples
   const string treename_particle = m_config.custom_params_string["treename_particle"];
   const string	treename_parton   = m_config.custom_params_string["treename_parton"];

   cout << "INFO: MC partons " << treename_parton << " tree read from " << mcfilename << endl;
   m_partons   = HelperFunctions::LoadChain( mcfilename.c_str(), treename_parton.c_str() );
   cout << "INFO: MC partons tree has " << m_partons->GetEntries() << " entries" << endl;

   cout << "INFO: MC particles " <<  treename_particle << " tree read from " << mcfilename << endl;
   m_particles = HelperFunctions::LoadChain( mcfilename.c_str(), treename_particle.c_str() );
   cout	<< "INFO: MC particles tree has " << m_particles->GetEntries() << " entries" << endl;

   m_ntuple_particle = new TopXAODParticles( m_particles );
   m_ntuple_parton   = new TopXAODPartons( m_partons );

   m_dumper_mctruth = new EventDumperMCTruthTopXAOD<TopXAODParticles, TopXAODPartons>(); 
   m_dumper_mctruth->SetNtupleParticle( m_ntuple_particle ); 
   m_dumper_mctruth->SetNtupleParton( m_ntuple_parton ); 
   m_dumper_mctruth->SetAnalysisParameters( analysisParameters );
   
   
   
}

/////////////////////////////////////////////


NtupleWrapperTopXAOD::~NtupleWrapperTopXAOD()
{
	SAFE_DELETE( m_ntuple_particle );
	SAFE_DELETE( m_ntuple_parton );
	SAFE_DELETE( m_dumper_mctruth );
}

/////////////////////////////////////////////


bool NtupleWrapperTopXAOD::MakeEventInfo( EventData * ed )
{
  bool success = true;

  ed->info.eventNumber     = GET_VALUE( eventNumber );
  ed->info.runNumber       = GET_VALUE( runNumber );
  ed->info.mcChannelNumber = GET_VALUE( mcChannelNumber );
  ed->info.mcWeight        = GET_VALUE( weight_mc );
//  ed->info.mcWeight        = 1.0; // no mcWeight??

 #ifdef __MOMA__
   
   if( m_doLumiReweight ) 
   {

   	m_lumiWeight = m_moma->GetLumiWeight( ed->info.mcChannelNumber, m_nEvents, m_lumi);
   	if(!(ed->info.eventNumber%100)) cout << "Debug: lumiweight for event " << ed->info.eventNumber << ", run " << ed->info.runNumber << " is " << m_lumiWeight << endl;
   	ed->info.mcWeight *= m_lumiWeight;
   }
#endif  


  SET_PROPERTY( passed_resolved_ejets_4j2b );
  SET_PROPERTY( passed_resolved_mujets_4j2b );
  SET_PROPERTY( passed_boosted_ejets_1fj0b );
  SET_PROPERTY( passed_boosted_mujets_1fj0b );

  SET_PROPERTY( HLT_mu20_iloose_L1MU15 );
  SET_PROPERTY( HLT_mu50 );
  SET_PROPERTY( HLT_e60_lhmedium );
  SET_PROPERTY( HLT_e24_lhmedium_L1EM18VH );
  SET_PROPERTY( HLT_e120_lhloose );

  ed->property["scaleFactor_BTAG_77"]  = GET_VALUE( weight_bTagSF_77 );
  ed->property["scaleFactor_BTAG_85"]  = GET_VALUE( weight_bTagSF_85 );
  ed->property["scaleFactor_LEPTON"]   = GET_VALUE( weight_leptonSF );
  ed->property["scaleFactor_PILEUP"]   = GET_VALUE( weight_pileup );
 
//temporary
  if( m_treeName == "nominal" )
  {
	ed->property["scaleFactor_pileup_UP"] = GET_VALUE( weight_pileup_UP );
	ed->property["scaleFactor_pileup_DOWN"] = GET_VALUE( weight_pileup_DOWN );
	ed->property["scaleFactor_leptonSF_EL_SF_Trigger_UP"] = GET_VALUE( weight_leptonSF_EL_SF_Trigger_UP );
	ed->property["scaleFactor_leptonSF_EL_SF_Trigger_DOWN"] = GET_VALUE( weight_leptonSF_EL_SF_Trigger_DOWN );
	ed->property["scaleFactor_leptonSF_EL_SF_Reco_UP"] = GET_VALUE( weight_leptonSF_EL_SF_Reco_UP );
	ed->property["scaleFactor_leptonSF_EL_SF_Reco_DOWN"] = GET_VALUE( weight_leptonSF_EL_SF_Reco_DOWN );
	ed->property["scaleFactor_leptonSF_EL_SF_ID_UP"] = GET_VALUE( weight_leptonSF_EL_SF_ID_UP );
	ed->property["scaleFactor_leptonSF_EL_SF_ID_DOWN"] = GET_VALUE( weight_leptonSF_EL_SF_ID_DOWN );
	ed->property["scaleFactor_leptonSF_EL_SF_Isol_UP"] = GET_VALUE( weight_leptonSF_EL_SF_Isol_UP );
	ed->property["scaleFactor_leptonSF_EL_SF_Isol_DOWN"] = GET_VALUE( weight_leptonSF_EL_SF_Isol_DOWN );
	ed->property["scaleFactor_leptonSF_MU_SF_Trigger_STAT_UP"] = GET_VALUE( weight_leptonSF_MU_SF_Trigger_STAT_UP );
	ed->property["scaleFactor_leptonSF_MU_SF_Trigger_STAT_DOWN"] = GET_VALUE( weight_leptonSF_MU_SF_Trigger_STAT_DOWN );
	ed->property["scaleFactor_leptonSF_MU_SF_Trigger_SYST_UP"] = GET_VALUE( weight_leptonSF_MU_SF_Trigger_SYST_UP );
	ed->property["scaleFactor_leptonSF_MU_SF_Trigger_SYST_DOWN"] = GET_VALUE( weight_leptonSF_MU_SF_Trigger_SYST_DOWN );
	ed->property["scaleFactor_leptonSF_MU_SF_ID_STAT_UP"] = GET_VALUE( weight_leptonSF_MU_SF_ID_STAT_UP );
	ed->property["scaleFactor_leptonSF_MU_SF_ID_STAT_DOWN"] = GET_VALUE( weight_leptonSF_MU_SF_ID_STAT_DOWN );
	ed->property["scaleFactor_leptonSF_MU_SF_ID_SYST_UP"] = GET_VALUE( weight_leptonSF_MU_SF_ID_SYST_UP );
	ed->property["scaleFactor_leptonSF_MU_SF_ID_SYST_DOWN"] = GET_VALUE( weight_leptonSF_MU_SF_ID_SYST_DOWN );
	ed->property["scaleFactor_leptonSF_MU_SF_Isol_STAT_UP"] = GET_VALUE( weight_leptonSF_MU_SF_Isol_STAT_UP );
	ed->property["scaleFactor_leptonSF_MU_SF_Isol_STAT_DOWN"] = GET_VALUE( weight_leptonSF_MU_SF_Isol_STAT_DOWN );
	ed->property["scaleFactor_leptonSF_MU_SF_Isol_SYST_UP"] = GET_VALUE( weight_leptonSF_MU_SF_Isol_SYST_UP );
	ed->property["scaleFactor_leptonSF_MU_SF_Isol_SYST_DOWN"] = GET_VALUE( weight_leptonSF_MU_SF_Isol_SYST_DOWN );
	ed->property["scaleFactor_indiv_SF_EL_Trigger"] = GET_VALUE( weight_indiv_SF_EL_Trigger );
	ed->property["scaleFactor_indiv_SF_EL_Trigger_UP"] = GET_VALUE( weight_indiv_SF_EL_Trigger_UP );
	ed->property["scaleFactor_indiv_SF_EL_Trigger_DOWN"] = GET_VALUE( weight_indiv_SF_EL_Trigger_DOWN );
	ed->property["scaleFactor_indiv_SF_EL_Reco"] = GET_VALUE( weight_indiv_SF_EL_Reco );
	ed->property["scaleFactor_indiv_SF_EL_Reco_UP"] = GET_VALUE( weight_indiv_SF_EL_Reco_UP );
	ed->property["scaleFactor_indiv_SF_EL_Reco_DOWN"] = GET_VALUE( weight_indiv_SF_EL_Reco_DOWN );
	ed->property["scaleFactor_indiv_SF_EL_ID"] = GET_VALUE( weight_indiv_SF_EL_ID );
	ed->property["scaleFactor_indiv_SF_EL_ID_UP"] = GET_VALUE( weight_indiv_SF_EL_ID_UP );
	ed->property["scaleFactor_indiv_SF_EL_ID_DOWN"] = GET_VALUE( weight_indiv_SF_EL_ID_DOWN );
	ed->property["scaleFactor_indiv_SF_EL_Isol"] = GET_VALUE( weight_indiv_SF_EL_Isol );
	ed->property["scaleFactor_indiv_SF_EL_Isol_UP"] = GET_VALUE( weight_indiv_SF_EL_Isol_UP );
	ed->property["scaleFactor_indiv_SF_EL_Isol_DOWN"] = GET_VALUE( weight_indiv_SF_EL_Isol_DOWN );
	ed->property["scaleFactor_indiv_SF_MU_Trigger"] = GET_VALUE( weight_indiv_SF_MU_Trigger );
	ed->property["scaleFactor_indiv_SF_MU_Trigger_STAT_UP"] = GET_VALUE( weight_indiv_SF_MU_Trigger_STAT_UP );
	ed->property["scaleFactor_indiv_SF_MU_Trigger_STAT_DOWN"] = GET_VALUE( weight_indiv_SF_MU_Trigger_STAT_DOWN );
	ed->property["scaleFactor_indiv_SF_MU_Trigger_SYST_UP"] = GET_VALUE( weight_indiv_SF_MU_Trigger_SYST_UP );
	ed->property["scaleFactor_indiv_SF_MU_Trigger_SYST_DOWN"] = GET_VALUE( weight_indiv_SF_MU_Trigger_SYST_DOWN );
	ed->property["scaleFactor_indiv_SF_MU_ID"] = GET_VALUE( weight_indiv_SF_MU_ID );
	ed->property["scaleFactor_indiv_SF_MU_ID_STAT_UP"] = GET_VALUE( weight_indiv_SF_MU_ID_STAT_UP );
	ed->property["scaleFactor_indiv_SF_MU_ID_STAT_DOWN"] = GET_VALUE( weight_indiv_SF_MU_ID_STAT_DOWN );
	ed->property["scaleFactor_indiv_SF_MU_ID_SYST_UP"] = GET_VALUE( weight_indiv_SF_MU_ID_SYST_UP );
	ed->property["scaleFactor_indiv_SF_MU_ID_SYST_DOWN"] = GET_VALUE( weight_indiv_SF_MU_ID_SYST_DOWN );
	ed->property["scaleFactor_indiv_SF_MU_Isol"] = GET_VALUE( weight_indiv_SF_MU_Isol );
	ed->property["scaleFactor_indiv_SF_MU_Isol_STAT_UP"] = GET_VALUE( weight_indiv_SF_MU_Isol_STAT_UP );
	ed->property["scaleFactor_indiv_SF_MU_Isol_STAT_DOWN"] = GET_VALUE( weight_indiv_SF_MU_Isol_STAT_DOWN );
	ed->property["scaleFactor_indiv_SF_MU_Isol_SYST_UP"] = GET_VALUE( weight_indiv_SF_MU_Isol_SYST_UP );
	ed->property["scaleFactor_indiv_SF_MU_Isol_SYST_DOWN"] = GET_VALUE( weight_indiv_SF_MU_Isol_SYST_DOWN );
	ed->property["scaleFactor_bTagSF_77_eigenvars_B_0_up"] = GET_VALUE_VECTOR( weight_bTagSF_77_eigenvars_B_up, 0 );
	ed->property["scaleFactor_bTagSF_77_eigenvars_B_0_down"] = GET_VALUE_VECTOR( weight_bTagSF_77_eigenvars_B_down, 0 );
	ed->property["scaleFactor_bTagSF_77_eigenvars_B_1_up"] = GET_VALUE_VECTOR( weight_bTagSF_77_eigenvars_B_up, 1 );
	ed->property["scaleFactor_bTagSF_77_eigenvars_B_1_down"] = GET_VALUE_VECTOR( weight_bTagSF_77_eigenvars_B_down, 1 );
	ed->property["scaleFactor_bTagSF_77_eigenvars_B_2_up"] = GET_VALUE_VECTOR( weight_bTagSF_77_eigenvars_B_up, 2 );
	ed->property["scaleFactor_bTagSF_77_eigenvars_B_2_down"] = GET_VALUE_VECTOR( weight_bTagSF_77_eigenvars_B_down, 2 );
	ed->property["scaleFactor_bTagSF_77_eigenvars_B_3_up"] = GET_VALUE_VECTOR( weight_bTagSF_77_eigenvars_B_up, 3 );
	ed->property["scaleFactor_bTagSF_77_eigenvars_B_3_down"] = GET_VALUE_VECTOR( weight_bTagSF_77_eigenvars_B_down, 3 );
	ed->property["scaleFactor_bTagSF_77_eigenvars_B_4_up"] = GET_VALUE_VECTOR( weight_bTagSF_77_eigenvars_B_up, 4 );
	ed->property["scaleFactor_bTagSF_77_eigenvars_B_4_down"] = GET_VALUE_VECTOR( weight_bTagSF_77_eigenvars_B_down, 4 );
	ed->property["scaleFactor_bTagSF_77_eigenvars_B_5_up"] = GET_VALUE_VECTOR( weight_bTagSF_77_eigenvars_B_up, 5 );
	ed->property["scaleFactor_bTagSF_77_eigenvars_B_5_down"] = GET_VALUE_VECTOR( weight_bTagSF_77_eigenvars_B_down, 5 );
	ed->property["scaleFactor_bTagSF_77_eigenvars_C_0_up"] = GET_VALUE_VECTOR( weight_bTagSF_77_eigenvars_C_up, 0 );
	ed->property["scaleFactor_bTagSF_77_eigenvars_C_0_down"] = GET_VALUE_VECTOR( weight_bTagSF_77_eigenvars_C_down, 0 );
	ed->property["scaleFactor_bTagSF_77_eigenvars_C_1_up"] = GET_VALUE_VECTOR( weight_bTagSF_77_eigenvars_C_up, 1 );
	ed->property["scaleFactor_bTagSF_77_eigenvars_C_1_down"] = GET_VALUE_VECTOR( weight_bTagSF_77_eigenvars_C_down, 1 );
	ed->property["scaleFactor_bTagSF_77_eigenvars_C_2_up"] = GET_VALUE_VECTOR( weight_bTagSF_77_eigenvars_C_up, 2 );
	ed->property["scaleFactor_bTagSF_77_eigenvars_C_2_down"] = GET_VALUE_VECTOR( weight_bTagSF_77_eigenvars_C_down, 2 );
	ed->property["scaleFactor_bTagSF_77_eigenvars_C_3_up"] = GET_VALUE_VECTOR( weight_bTagSF_77_eigenvars_C_up, 3 );
	ed->property["scaleFactor_bTagSF_77_eigenvars_C_3_down"] = GET_VALUE_VECTOR( weight_bTagSF_77_eigenvars_C_down, 3 );
	ed->property["scaleFactor_bTagSF_77_eigenvars_Light_0_up"] = GET_VALUE_VECTOR( weight_bTagSF_77_eigenvars_Light_up, 0 );
	ed->property["scaleFactor_bTagSF_77_eigenvars_Light_0_down"] = GET_VALUE_VECTOR( weight_bTagSF_77_eigenvars_Light_down, 0 );
	ed->property["scaleFactor_bTagSF_77_eigenvars_Light_1_up"] = GET_VALUE_VECTOR( weight_bTagSF_77_eigenvars_Light_up, 1 );
	ed->property["scaleFactor_bTagSF_77_eigenvars_Light_1_down"] = GET_VALUE_VECTOR( weight_bTagSF_77_eigenvars_Light_down, 1 );
	ed->property["scaleFactor_bTagSF_77_eigenvars_Light_2_up"] = GET_VALUE_VECTOR( weight_bTagSF_77_eigenvars_Light_up, 2 );
	ed->property["scaleFactor_bTagSF_77_eigenvars_Light_2_down"] = GET_VALUE_VECTOR( weight_bTagSF_77_eigenvars_Light_down, 2 );
	ed->property["scaleFactor_bTagSF_77_eigenvars_Light_3_up"] = GET_VALUE_VECTOR( weight_bTagSF_77_eigenvars_Light_up, 3 );
	ed->property["scaleFactor_bTagSF_77_eigenvars_Light_3_down"] = GET_VALUE_VECTOR( weight_bTagSF_77_eigenvars_Light_down, 3 );
	ed->property["scaleFactor_bTagSF_77_eigenvars_Light_4_up"] = GET_VALUE_VECTOR( weight_bTagSF_77_eigenvars_Light_up, 4 );
	ed->property["scaleFactor_bTagSF_77_eigenvars_Light_4_down"] = GET_VALUE_VECTOR( weight_bTagSF_77_eigenvars_Light_down, 4 );
	ed->property["scaleFactor_bTagSF_77_eigenvars_Light_5_up"] = GET_VALUE_VECTOR( weight_bTagSF_77_eigenvars_Light_up, 5 );
	ed->property["scaleFactor_bTagSF_77_eigenvars_Light_5_down"] = GET_VALUE_VECTOR( weight_bTagSF_77_eigenvars_Light_down, 5 );
	ed->property["scaleFactor_bTagSF_77_eigenvars_Light_6_up"] = GET_VALUE_VECTOR( weight_bTagSF_77_eigenvars_Light_up, 6 );
	ed->property["scaleFactor_bTagSF_77_eigenvars_Light_6_down"] = GET_VALUE_VECTOR( weight_bTagSF_77_eigenvars_Light_down, 6 );
	ed->property["scaleFactor_bTagSF_77_eigenvars_Light_7_up"] = GET_VALUE_VECTOR( weight_bTagSF_77_eigenvars_Light_up, 7 );
	ed->property["scaleFactor_bTagSF_77_eigenvars_Light_7_down"] = GET_VALUE_VECTOR( weight_bTagSF_77_eigenvars_Light_down, 7 );
	ed->property["scaleFactor_bTagSF_77_eigenvars_Light_8_up"] = GET_VALUE_VECTOR( weight_bTagSF_77_eigenvars_Light_up, 8 );
	ed->property["scaleFactor_bTagSF_77_eigenvars_Light_8_down"] = GET_VALUE_VECTOR( weight_bTagSF_77_eigenvars_Light_down, 8 );
	ed->property["scaleFactor_bTagSF_77_eigenvars_Light_9_up"] = GET_VALUE_VECTOR( weight_bTagSF_77_eigenvars_Light_up, 9 );
	ed->property["scaleFactor_bTagSF_77_eigenvars_Light_9_down"] = GET_VALUE_VECTOR( weight_bTagSF_77_eigenvars_Light_down, 9 );
	ed->property["scaleFactor_bTagSF_77_eigenvars_Light_10_up"] = GET_VALUE_VECTOR( weight_bTagSF_77_eigenvars_Light_up, 10 );
	ed->property["scaleFactor_bTagSF_77_eigenvars_Light_10_down"] = GET_VALUE_VECTOR( weight_bTagSF_77_eigenvars_Light_down, 10 );
	ed->property["scaleFactor_bTagSF_77_eigenvars_Light_11_up"] = GET_VALUE_VECTOR( weight_bTagSF_77_eigenvars_Light_up, 11 );
	ed->property["scaleFactor_bTagSF_77_eigenvars_Light_11_down"] = GET_VALUE_VECTOR( weight_bTagSF_77_eigenvars_Light_down, 11 );
	ed->property["scaleFactor_bTagSF_77_eigenvars_Light_12_up"] = GET_VALUE_VECTOR( weight_bTagSF_77_eigenvars_Light_up, 12 );
	ed->property["scaleFactor_bTagSF_77_eigenvars_Light_12_down"] = GET_VALUE_VECTOR( weight_bTagSF_77_eigenvars_Light_down, 12 );
	ed->property["scaleFactor_bTagSF_77_eigenvars_Light_13_up"] = GET_VALUE_VECTOR( weight_bTagSF_77_eigenvars_Light_up, 13 );
	ed->property["scaleFactor_bTagSF_77_eigenvars_Light_13_down"] = GET_VALUE_VECTOR( weight_bTagSF_77_eigenvars_Light_down, 13 );
	ed->property["scaleFactor_bTagSF_77_extrapolation_up"] = GET_VALUE( weight_bTagSF_77_extrapolation_up );
	ed->property["scaleFactor_bTagSF_77_extrapolation_down"] = GET_VALUE( weight_bTagSF_77_extrapolation_down );
	ed->property["scaleFactor_bTagSF_77_extrapolation_from_charm_up"] = GET_VALUE( weight_bTagSF_77_extrapolation_from_charm_up );
	ed->property["scaleFactor_bTagSF_77_extrapolation_from_charm_down"] = GET_VALUE( weight_bTagSF_77_extrapolation_from_charm_down );
	/*ed->property["scaleFactor_bTagSF_85_eigenvars_B_0_up"] = GET_VALUE_VECTOR( weight_bTagSF_85_eigenvars_B_up, 0 );
	ed->property["scaleFactor_bTagSF_85_eigenvars_B_0_down"] = GET_VALUE_VECTOR( weight_bTagSF_85_eigenvars_B_down, 0 );
	ed->property["scaleFactor_bTagSF_85_eigenvars_B_1_up"] = GET_VALUE_VECTOR( weight_bTagSF_85_eigenvars_B_up, 1 );
	ed->property["scaleFactor_bTagSF_85_eigenvars_B_1_down"] = GET_VALUE_VECTOR( weight_bTagSF_85_eigenvars_B_down, 1 );
	ed->property["scaleFactor_bTagSF_85_eigenvars_B_2_up"] = GET_VALUE_VECTOR( weight_bTagSF_85_eigenvars_B_up, 2 );
	ed->property["scaleFactor_bTagSF_85_eigenvars_B_2_down"] = GET_VALUE_VECTOR( weight_bTagSF_85_eigenvars_B_down, 2 );
	ed->property["scaleFactor_bTagSF_85_eigenvars_B_3_up"] = GET_VALUE_VECTOR( weight_bTagSF_85_eigenvars_B_up, 3 );
	ed->property["scaleFactor_bTagSF_85_eigenvars_B_3_down"] = GET_VALUE_VECTOR( weight_bTagSF_85_eigenvars_B_down, 3 );
	ed->property["scaleFactor_bTagSF_85_eigenvars_B_4_up"] = GET_VALUE_VECTOR( weight_bTagSF_85_eigenvars_B_up, 4 );
	ed->property["scaleFactor_bTagSF_85_eigenvars_B_4_down"] = GET_VALUE_VECTOR( weight_bTagSF_85_eigenvars_B_down, 4 );
	ed->property["scaleFactor_bTagSF_85_eigenvars_B_5_up"] = GET_VALUE_VECTOR( weight_bTagSF_85_eigenvars_B_up, 5 );
	ed->property["scaleFactor_bTagSF_85_eigenvars_B_5_down"] = GET_VALUE_VECTOR( weight_bTagSF_85_eigenvars_B_down, 5 );
	ed->property["scaleFactor_bTagSF_85_eigenvars_C_0_up"] = GET_VALUE_VECTOR( weight_bTagSF_85_eigenvars_C_up, 0 );
	ed->property["scaleFactor_bTagSF_85_eigenvars_C_0_down"] = GET_VALUE_VECTOR( weight_bTagSF_85_eigenvars_C_down, 0 );
	ed->property["scaleFactor_bTagSF_85_eigenvars_C_1_up"] = GET_VALUE_VECTOR( weight_bTagSF_85_eigenvars_C_up, 1 );
	ed->property["scaleFactor_bTagSF_85_eigenvars_C_1_down"] = GET_VALUE_VECTOR( weight_bTagSF_85_eigenvars_C_down, 1 );
	ed->property["scaleFactor_bTagSF_85_eigenvars_C_2_up"] = GET_VALUE_VECTOR( weight_bTagSF_85_eigenvars_C_up, 2 );
	ed->property["scaleFactor_bTagSF_85_eigenvars_C_2_down"] = GET_VALUE_VECTOR( weight_bTagSF_85_eigenvars_C_down, 2 );
	ed->property["scaleFactor_bTagSF_85_eigenvars_C_3_up"] = GET_VALUE_VECTOR( weight_bTagSF_85_eigenvars_C_up, 3 );
	ed->property["scaleFactor_bTagSF_85_eigenvars_C_3_down"] = GET_VALUE_VECTOR( weight_bTagSF_85_eigenvars_C_down, 3 );
	ed->property["scaleFactor_bTagSF_85_eigenvars_Light_0_up"] = GET_VALUE_VECTOR( weight_bTagSF_85_eigenvars_Light_up, 0 );
	ed->property["scaleFactor_bTagSF_85_eigenvars_Light_0_down"] = GET_VALUE_VECTOR( weight_bTagSF_85_eigenvars_Light_down, 0 );
	ed->property["scaleFactor_bTagSF_85_eigenvars_Light_1_up"] = GET_VALUE_VECTOR( weight_bTagSF_85_eigenvars_Light_up, 1 );
	ed->property["scaleFactor_bTagSF_85_eigenvars_Light_1_down"] = GET_VALUE_VECTOR( weight_bTagSF_85_eigenvars_Light_down, 1 );
	ed->property["scaleFactor_bTagSF_85_eigenvars_Light_2_up"] = GET_VALUE_VECTOR( weight_bTagSF_85_eigenvars_Light_up, 2 );
	ed->property["scaleFactor_bTagSF_85_eigenvars_Light_2_down"] = GET_VALUE_VECTOR( weight_bTagSF_85_eigenvars_Light_down, 2 );
	ed->property["scaleFactor_bTagSF_85_eigenvars_Light_3_up"] = GET_VALUE_VECTOR( weight_bTagSF_85_eigenvars_Light_up, 3 );
	ed->property["scaleFactor_bTagSF_85_eigenvars_Light_3_down"] = GET_VALUE_VECTOR( weight_bTagSF_85_eigenvars_Light_down, 3 );
	ed->property["scaleFactor_bTagSF_85_eigenvars_Light_4_up"] = GET_VALUE_VECTOR( weight_bTagSF_85_eigenvars_Light_up, 4 );
	ed->property["scaleFactor_bTagSF_85_eigenvars_Light_4_down"] = GET_VALUE_VECTOR( weight_bTagSF_85_eigenvars_Light_down, 4 );
	ed->property["scaleFactor_bTagSF_85_eigenvars_Light_5_up"] = GET_VALUE_VECTOR( weight_bTagSF_85_eigenvars_Light_up, 5 );
	ed->property["scaleFactor_bTagSF_85_eigenvars_Light_5_down"] = GET_VALUE_VECTOR( weight_bTagSF_85_eigenvars_Light_down, 5 );
	ed->property["scaleFactor_bTagSF_85_eigenvars_Light_6_up"] = GET_VALUE_VECTOR( weight_bTagSF_85_eigenvars_Light_up, 6 );
	ed->property["scaleFactor_bTagSF_85_eigenvars_Light_6_down"] = GET_VALUE_VECTOR( weight_bTagSF_85_eigenvars_Light_down, 6 );
	ed->property["scaleFactor_bTagSF_85_eigenvars_Light_7_up"] = GET_VALUE_VECTOR( weight_bTagSF_85_eigenvars_Light_up, 7 );
	ed->property["scaleFactor_bTagSF_85_eigenvars_Light_7_down"] = GET_VALUE_VECTOR( weight_bTagSF_85_eigenvars_Light_down, 7 );
	ed->property["scaleFactor_bTagSF_85_eigenvars_Light_8_up"] = GET_VALUE_VECTOR( weight_bTagSF_85_eigenvars_Light_up, 8 );
	ed->property["scaleFactor_bTagSF_85_eigenvars_Light_8_down"] = GET_VALUE_VECTOR( weight_bTagSF_85_eigenvars_Light_down, 8 );
	ed->property["scaleFactor_bTagSF_85_eigenvars_Light_9_up"] = GET_VALUE_VECTOR( weight_bTagSF_85_eigenvars_Light_up, 9 );
	ed->property["scaleFactor_bTagSF_85_eigenvars_Light_9_down"] = GET_VALUE_VECTOR( weight_bTagSF_85_eigenvars_Light_down, 9 );
	ed->property["scaleFactor_bTagSF_85_eigenvars_Light_10_up"] = GET_VALUE_VECTOR( weight_bTagSF_85_eigenvars_Light_up, 10 );
	ed->property["scaleFactor_bTagSF_85_eigenvars_Light_10_down"] = GET_VALUE_VECTOR( weight_bTagSF_85_eigenvars_Light_down, 10 );
	ed->property["scaleFactor_bTagSF_85_eigenvars_Light_11_up"] = GET_VALUE_VECTOR( weight_bTagSF_85_eigenvars_Light_up, 11 );
	ed->property["scaleFactor_bTagSF_85_eigenvars_Light_11_down"] = GET_VALUE_VECTOR( weight_bTagSF_85_eigenvars_Light_down, 11 );
	ed->property["scaleFactor_bTagSF_85_eigenvars_Light_12_up"] = GET_VALUE_VECTOR( weight_bTagSF_85_eigenvars_Light_up, 12 );
	ed->property["scaleFactor_bTagSF_85_eigenvars_Light_12_down"] = GET_VALUE_VECTOR( weight_bTagSF_85_eigenvars_Light_down, 12 );
	ed->property["scaleFactor_bTagSF_85_eigenvars_Light_13_up"] = GET_VALUE_VECTOR( weight_bTagSF_85_eigenvars_Light_up, 13 );
	ed->property["scaleFactor_bTagSF_85_eigenvars_Light_13_down"] = GET_VALUE_VECTOR( weight_bTagSF_85_eigenvars_Light_down, 13 );
	ed->property["scaleFactor_bTagSF_85_extrapolation_up"] = GET_VALUE( weight_bTagSF_85_extrapolation_up );
	ed->property["scaleFactor_bTagSF_85_extrapolation_down"] = GET_VALUE( weight_bTagSF_85_extrapolation_down );
	ed->property["scaleFactor_bTagSF_85_extrapolation_from_charm_up"] = GET_VALUE( weight_bTagSF_85_extrapolation_from_charm_up );
	ed->property["scaleFactor_bTagSF_85_extrapolation_from_charm_down"] = GET_VALUE( weight_bTagSF_85_extrapolation_from_charm_down );*///Commented out until we get the new ntuples
}
  

  return success;
}


/////////////////////////////////////////////


bool NtupleWrapperTopXAOD::MakeEventTrigger( EventData * ed )
{ 
  bool success = true;

// CHECK_TRIGGER( "EF_mu18i" );

  return success;
}


/////////////////////////////////////////////


bool NtupleWrapperTopXAOD::MakeEventMET( EventData * ed )
{
  bool success = true;

  ed->MET.et    = GET_VALUE( met_met );
  ed->MET.phi   = GET_VALUE( met_phi );
  //  ed->MET.etx   = 0.;
  //  ed->MET.ety   = 0.;
//  ed->MET.sumet = GET_VALUE( met_sumet  );
//  ed->MET.mwt   = GET_VALUE( mwt );

  return success;
}


/////////////////////////////////////////////


bool NtupleWrapperTopXAOD::MakeEventLeptons( EventData * ed )
{
  bool success = true;

  ed->electrons.n = m_ntuple->el_pt->size();
  for( int i = 0 ; i < ed->electrons.n ; ++i ) {
    ed->electrons.pT.push_back(  GET_VALUE_VECTOR( el_pt,  i ) );
    ed->electrons.eta.push_back( GET_VALUE_VECTOR( el_eta, i ) );
    ed->electrons.phi.push_back( GET_VALUE_VECTOR( el_phi, i ) );
    ed->electrons.E.push_back(   GET_VALUE_VECTOR( el_e,   i ) );
    ed->electrons.q.push_back(   GET_VALUE_VECTOR( el_charge, i ) );

    ed->leptons.pT.push_back(  GET_VALUE_VECTOR( el_pt,  i ) );
    ed->leptons.eta.push_back( GET_VALUE_VECTOR( el_eta, i ) );
    ed->leptons.phi.push_back( GET_VALUE_VECTOR( el_phi, i ) );
    ed->leptons.E.push_back(   GET_VALUE_VECTOR( el_e,   i ) );
    ed->leptons.q.push_back(   GET_VALUE_VECTOR( el_charge, i ) );
  }


  ed->muons.n = m_ntuple->mu_pt->size();
  for( int i = 0 ; i < ed->muons.n ; ++i ) {
    ed->muons.pT.push_back(  GET_VALUE_VECTOR( mu_pt,  i ) );
    ed->muons.eta.push_back( GET_VALUE_VECTOR( mu_eta, i ) );
    ed->muons.phi.push_back( GET_VALUE_VECTOR( mu_phi, i ) );
    ed->muons.E.push_back(   GET_VALUE_VECTOR( mu_e,   i ) );
    ed->muons.q.push_back(   GET_VALUE_VECTOR( mu_charge, i	) );

    ed->leptons.pT.push_back(  GET_VALUE_VECTOR( mu_pt,  i ) );
    ed->leptons.eta.push_back( GET_VALUE_VECTOR( mu_eta, i ) );
    ed->leptons.phi.push_back( GET_VALUE_VECTOR( mu_phi, i ) );
    ed->leptons.E.push_back(   GET_VALUE_VECTOR( mu_e,   i ) );
    ed->leptons.q.push_back(   GET_VALUE_VECTOR( mu_charge, i )	);

  }
  // should be re-ordered by pT. Or there is just one lepton, either el or mu?

//  cout << "DEBUG: el_n=" << ed->electrons.n << " mu_n=" << ed->muons.n << endl;

  return success;
}


/////////////////////////////////////////////


bool NtupleWrapperTopXAOD::MakeEventJets( EventData * ed )
{
  bool success = true;

    size_t alljet_n = m_ntuple->jet_pt->size();
    ed->jets.n  = 0;
    ed->bjets.n = 0;
    ed->ljets.n = 0;
    int jindex = 0;
    
    for( int j = 0; j < alljet_n; ++j ) {
        const double jet_pT   = GET_VALUE_VECTOR( jet_pt, j );
        const double jet_eta  = GET_VALUE_VECTOR( jet_eta, j );
        const double jet_phi  = GET_VALUE_VECTOR( jet_phi, j );
        const double jet_E    = GET_VALUE_VECTOR( jet_e, j );

        if( jet_pT < 25 * GeV ) continue;
        if( fabs(jet_eta) > 2.5 ) continue;
        
            ed->jets.n++;

            ed->jets.index.push_back( jindex );

            ed->jets.pT.push_back(  jet_pT );
            ed->jets.eta.push_back( jet_eta );
            ed->jets.phi.push_back( jet_phi );
            ed->jets.E.push_back(   jet_E );

            const double jet_m = PhysicsHelperFunctions::Mass( ed->jets, (ed->jets.n-1) );
            ed->jets.m.push_back( jet_m );

            ed->jets.property["jvt"].push_back(          GET_VALUE_VECTOR(jet_jvt, j)          );

            const double mv2c20 = GET_VALUE_VECTOR(jet_mv2c20, j);
            ed->jets.property["mv2c20"].push_back( mv2c20 );

            if( mv2c20 > -0.0436 ) { // 70% eff w.p.
                ed->bjets.n++;

                ed->bjets.pT.push_back( jet_pT );
                ed->bjets.eta.push_back( jet_eta );
                ed->bjets.phi.push_back( jet_phi );
                ed->bjets.E.push_back( jet_E );
                ed->bjets.m.push_back( jet_m );
                ed->bjets.index.push_back( jindex );
                ed->bjets.property["mv2c20"].push_back(mv2c20);
            } else {
                ed->ljets.n++;

                ed->ljets.pT.push_back( jet_pT );
                ed->ljets.eta.push_back( jet_eta );
                ed->ljets.phi.push_back( jet_phi );
                ed->ljets.E.push_back( jet_E );
                ed->ljets.m.push_back( jet_m );
                ed->ljets.index.push_back( jindex );
                ed->ljets.property["mv2c20"].push_back(mv2c20);
		
         }
	jindex++;
    }


    size_t allfjet_n = m_ntuple->ljet_pt->size();
    ed->fjets.n = 0;
    
    for( int lj = 0; lj < allfjet_n; ++lj ) {

      const double fjet_pT   = GET_VALUE_VECTOR( ljet_pt,  lj );
      const double fjet_eta  = GET_VALUE_VECTOR( ljet_eta, lj );
      const double fjet_phi  = GET_VALUE_VECTOR( ljet_phi, lj );
      const double fjet_E    = GET_VALUE_VECTOR( ljet_e, lj );
      const double fjet_m    = GET_VALUE_VECTOR( ljet_m, lj );
       
      if( fjet_pT < 25 * GeV ) continue;
      if( fabs(fjet_eta) > 2.5 ) continue;
      
      ed->fjets.n++;
      
      ed->fjets.index.push_back( lj );
      
      ed->fjets.pT.push_back(  fjet_pT );
      ed->fjets.eta.push_back( fjet_eta );
      ed->fjets.phi.push_back( fjet_phi );
      ed->fjets.E.push_back(   fjet_E );
      //      const double fjet_m = PhysicsHelperFunctions::Mass( ed->fjets, lj );  ////For the Large-Rjet the mass is in the Ntuple
      ed->fjets.m.push_back( fjet_m );
      
      ////--Tagging and substructures properties of the Large-R jet--/////
      const double sd12 = GET_VALUE_VECTOR(ljet_sd12, lj);
      ed->fjets.property["sd12"].push_back( sd12 );
      
      const double tau32 = GET_VALUE_VECTOR(ljet_tau32, lj);
      ed->fjets.property["tau32"].push_back( tau32 );
      
      const double tau21 = GET_VALUE_VECTOR(ljet_tau21, lj);
      ed->fjets.property["tau21"].push_back( tau21 );

      const int topTag50 = GET_VALUE_VECTOR(ljet_topTag50, lj);
      ed->fjets.property["topTag50"].push_back(topTag50 );

      const int topTag80 = GET_VALUE_VECTOR(ljet_topTag80, lj);
      ed->fjets.property["topTag80"].push_back(topTag80);

    }
    
    return success;
}


/////////////////////////////////////////////


bool NtupleWrapperTopXAOD::MakeEventTruth( EventData * ed )
{
  bool success = true;
 unsigned long isMCSignal = m_config.custom_params_flag["isMCSignal"];
  if( !isMCSignal ) return success;
  
  m_dumper_mctruth->GetEntryWithIndex( ed->info.runNumber, ed->info.eventNumber );

  m_dumper_mctruth->DumpEventLeptons( this->m_ntuple_particle, ed );
  m_dumper_mctruth->DumpEventMET( this->m_ntuple_particle, ed );
  m_dumper_mctruth->DumpEventJets( this->m_ntuple_particle, ed );
  m_dumper_mctruth->DumpEventMCTruth( this->m_ntuple_parton, ed );
  m_dumper_mctruth->DumpEventCutflows( this->m_ntuple_particle, ed );
 // m_ntuple_parton->MakeEventInfo( ed );
  return success;
}


/////////////////////////////////////////
// Plugin

extern "C" {
  NtupleWrapperPluginFactory_TopXAOD * MakeNtupleWrapperPlugin() {
    return new NtupleWrapperPluginFactory_TopXAOD( "TopXAOD" );
  };
}
