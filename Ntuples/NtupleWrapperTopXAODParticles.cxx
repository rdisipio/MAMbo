#include "NtupleWrapperTopXAODParticles.h"

NtupleWrapperTopXAODParticles::NtupleWrapperTopXAODParticles( const AnalysisParams_t analysisParameters ) :
  NtupleWrapper< TopXAODParticles >( analysisParameters ), 
  m_partons(NULL), m_ntuple_parton(NULL)
{

#ifdef __MOMA__
   m_moma = MoMATool::GetHandle();
   cout << "INFO: ATLAS ROOTCORE detected. MoMA tool initialized." << endl;
#endif

   m_dumper_mctruth = new EventDumperMCTruthTopXAOD<TopXAODParticles, TopXAODPartons>();    
   m_dumper_mctruth->SetAnalysisParameters( analysisParameters );
   m_dumper_mctruth->SetNtupleParticle( this->m_ntuple, false );

   unsigned long isMCSignal = m_config.custom_params_flag["isMCSignal"];
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

   if( isMCSignal ) {
      // open truth ntuples
      const string mcfilename        = m_config.custom_params_string["mcfile"];
      const string treename_parton   = m_config.custom_params_string["treename_parton"];

      cout << "INFO: MC tree read from " << mcfilename << endl;
      // JK && JK      m_partons = HelperFunctions::LoadChain( mcfilename.c_str(), treename_parton.c_str() ); // this line is responsible for empty parton tree, flanked by next line 
      m_partons = HelperFunctions::LoadChain( analysisParameters.fileListName, treename_parton );
   }
   // else {
      // m_partons = HelperFunctions::LoadChain( analysisParameters.fileListName, treename_parton );
   // }

   if( !m_partons ) {
     cout << "WARNING: no partons tree found in the file list" << endl;
 
     return;
   }

   cout << "INFO: MC partons tree has " << m_partons->GetEntries() << " entries" << endl;
   m_ntuple_parton   = new TopXAODPartons( m_partons );

   if( !m_ntuple_parton )   throw std::runtime_error( "ERROR: NtupleWrapperTopXAODParticles: invalid partons ROOT tree." );

   m_dumper_mctruth->SetNtupleParton( m_ntuple_parton ); 
   
      
   m_doPDFReweight = false;
   if(  m_config.custom_params_string.count( "scale_syst" ) )
   {
	    const string syst = m_config.custom_params_string["scale_syst"];
		m_doPDFReweight = syst.find("PDF") != string::npos ;
   }

//   cout<<"Event Number "<<m_ntuple_particle->eventNumber<<endl;

}

/////////////////////////////////////////////


NtupleWrapperTopXAODParticles::~NtupleWrapperTopXAODParticles()
{
   SAFE_DELETE( m_partons );    
   SAFE_DELETE( m_dumper_mctruth );
   SAFE_DELETE( m_ntuple_parton );
}

/////////////////////////////////////////////


bool NtupleWrapperTopXAODParticles::MakeEventInfo( EventData * ed )
{
  bool success = true;

  ed->info.eventNumber     = GET_VALUE( eventNumber );
  ed->info.runNumber       = GET_VALUE( runNumber );
  ed->info.mcChannelNumber = GET_VALUE( mcChannelNumber );
  ed->info.mcWeight        = GET_VALUE( weight_mc ); //MC@NLO ??
  
  
  SET_PROPERTY( passed_resolved_ejets_2j0b );
  SET_PROPERTY( passed_resolved_mujets_2j0b );

  SET_PROPERTY( passed_resolved_ejets_4j2b );
  SET_PROPERTY( passed_resolved_mujets_4j2b );
  SET_PROPERTY( passed_boosted_ejets_1fj0b );
  SET_PROPERTY( passed_boosted_mujets_1fj0b );
  
//  ed->info.mcWeight = 1.; // bug in D3PD2MiniSL? All zeros. Can't use MC@NLO at the moment.
//  if( fabs(ed->info.mcWeight) < 1e-4 ) ed->info.mcWeight = 1.;
  
  m_dumper_mctruth->DumpEventCutflows( this->m_ntuple, ed );
/*  ed->property["passed_particle_resolved_ejets_4j2b" ] = GET_VALUE( passed_resolved_ejets_4j2b );
  ed->property["passed_particle_resolved_mujets_4j2b" ] = GET_VALUE( passed_resolved_mujets_4j2b );
  ed->property["passed_particle_boosted_ejets_1fj0b" ] = GET_VALUE( passed_boosted_ejets_1fj0b );  
  ed->property["passed_particle_boosted_mujets_1fj0b" ] = GET_VALUE( passed_boosted_mujets_1fj0b );
*/
//PDF info are currently not available at particle level (see TTDIFFXS-32)
/*
  ed->property["pdf_pdf1"]  = GET_VALUE( mcevt_pdf1 );
  ed->property["pdf_id1"]   = GET_VALUE( mcevt_pdf_id1 );
  ed->property["pdf_x1"]    = GET_VALUE( mcevt_pdf_x1 );
  ed->property["pdf_pdf2"]  = GET_VALUE( mcevt_pdf2 );
  ed->property["pdf_id2"]   = GET_VALUE( mcevt_pdf_id2 );
  ed->property["pdf_x2"]    = GET_VALUE( mcevt_pdf_x2 );
  ed->property["pdf_scale"] = GET_VALUE( mcevt_pdf_scale );
*/
 #ifdef __MOMA__
   if( m_doLumiReweight ) 
   {

   	m_lumiWeight = m_moma->GetLumiWeight( ed->info.mcChannelNumber, m_nEvents, m_lumi);
	if(!(ed->info.eventNumber % 1000)) cout << "Debug: lumiweight for event " << ed->info.eventNumber << ", run " << ed->info.runNumber << " is " << m_lumiWeight << endl;
   	ed->info.mcWeight *= m_lumiWeight;
   }
#endif 
 



  return success;
}


/////////////////////////////////////////////


bool NtupleWrapperTopXAODParticles::MakeEventTrigger( EventData * ed )
{ 
  bool success = true;

// CHECK_TRIGGER( "EF_mu18i" );

  return success;
}


/////////////////////////////////////////////


bool NtupleWrapperTopXAODParticles::MakeEventMET( EventData * ed )
{
  bool success = true;

/*
  ed->MET.et    = GET_VALUE( met_et );
  ed->MET.phi   = GET_VALUE( met_phi );
  //  ed->MET.etx   = 0.;
  //  ed->MET.ety   = 0.;
  ed->MET.sumet = GET_VALUE( met_sumet  );
  ed->MET.mwt   = GET_VALUE( mwt );
  //  SET_PROPERTY( mwt );
*/

  return success;
}


/////////////////////////////////////////////

bool NtupleWrapperTopXAODParticles::MakeEventLeptons( EventData * ed )
{
   return true;
}


/////////////////////////////////////////////


bool NtupleWrapperTopXAODParticles::MakeEventJets( EventData * ed )
{
   return true;
}


/////////////////////////////////////////////


bool NtupleWrapperTopXAODParticles::MakeEventTruth( EventData * ed )
{
  bool success = true;

  //m_dumper_mctruth->GetEntryWithIndex( ed->info.runNumber, ed->info.eventNumber );
//  m_ntuple_parton->fChain->GetEntryWithIndex( ed->info.runNumber, ed->info.eventNumber );

  m_dumper_mctruth->GetEntryWithIndex( ed->info.runNumber, ed->info.eventNumber );
 
  m_dumper_mctruth->DumpEventLeptons( this->m_ntuple, ed );
  m_dumper_mctruth->DumpEventMET( this->m_ntuple, ed );
  m_dumper_mctruth->DumpEventJets( this->m_ntuple, ed );
  m_dumper_mctruth->DumpEventMCTruth( this->m_ntuple_parton, ed );
  if( m_doPDFReweight ) //mr
  {
	  m_dumper_mctruth->DumpEventPDFWeights( this->m_ntuple_parton, ed ); //can be optimized (dumping only the selected pdf weight)
  }
 

  return success;
}


/////////////////////////////////////////
// Plugin

extern "C" {
  NtupleWrapperPluginFactory_TopXAODParticles * MakeNtupleWrapperPlugin() {
    return new NtupleWrapperPluginFactory_TopXAODParticles( "TopXAODParticles" );
  };
}
