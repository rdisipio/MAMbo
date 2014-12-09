#include "NtupleWrapperTopMiniSLResolvedParticles.h"

NtupleWrapperTopMiniSLResolvedParticles::NtupleWrapperTopMiniSLResolvedParticles( const AnalysisParams_t analysisParameters ) :
  NtupleWrapper< TopMiniSLResolvedParticles >( analysisParameters ), 
  m_partons(NULL), m_ntuple_parton(NULL)
{
   m_dumper_mctruth = new EventDumperMCTruthTopMiniSLResolved<TopMiniSLResolvedParticles, TopMiniSLResolvedPartons>();    
   m_dumper_mctruth->SetAnalysisParameters( analysisParameters );
   m_dumper_mctruth->SetNtupleParticle( this->m_ntuple, false );

   unsigned long isMCSignal = m_config.custom_params_flag["isMCSignal"];
   if( !isMCSignal ) return;

   // open truth ntuples
   const string mcfilename        = m_config.custom_params_string["mcfile"];
   const string	treename_parton   = m_config.custom_params_string["treename_parton"];

   cout << "INFO: MC tree read from " << mcfilename << endl;

   m_partons   = new TChain( treename_parton.c_str() );

   ifstream input( mcfilename.c_str(), ios_base::in );
   string fName;
   while( std::getline( input, fName ) ) {
     //     cout << "INFO: File list: " << mcfilename.c_str() << endl;
      if( fName.empty() ) continue;
      cout << "INFO: Input file: " << fName << '\n';
      m_partons->AddFile( fName.c_str() );
   }
   input.close();

   m_ntuple_parton   = new TopMiniSLResolvedPartons( m_partons );

   if( !m_ntuple_parton )   throw std::runtime_error( "ERROR: NtupleWrapperTopMiniSLResolvedParticles: invalid partons ROOT tree." );

   m_dumper_mctruth->SetNtupleParton( m_ntuple_parton ); 

//   cout<<"Event Number "<<m_ntuple_particle->eventNumber<<endl;

}

/////////////////////////////////////////////


NtupleWrapperTopMiniSLResolvedParticles::~NtupleWrapperTopMiniSLResolvedParticles()
{
   SAFE_DELETE( m_partons );    
   SAFE_DELETE( m_dumper_mctruth );
   SAFE_DELETE( m_ntuple_parton );
}

/////////////////////////////////////////////


bool NtupleWrapperTopMiniSLResolvedParticles::MakeEventInfo( EventData * ed )
{
  bool success = true;

  ed->info.eventNumber     = GET_VALUE( eventNumber );
  ed->info.runNumber       = GET_VALUE( runNumber );
  ed->info.mcChannelNumber = GET_VALUE( channelNumber );
  ed->info.mcWeight        = 1.; //GET_VALUE( eventWeight ); //MC@NLO ??

  return success;
}


/////////////////////////////////////////////


bool NtupleWrapperTopMiniSLResolvedParticles::MakeEventTrigger( EventData * ed )
{ 
  bool success = true;

// CHECK_TRIGGER( "EF_mu18i" );

  return success;
}


/////////////////////////////////////////////


bool NtupleWrapperTopMiniSLResolvedParticles::MakeEventMET( EventData * ed )
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

bool NtupleWrapperTopMiniSLResolvedParticles::MakeEventLeptons( EventData * ed )
{
   return true;
}


/////////////////////////////////////////////


bool NtupleWrapperTopMiniSLResolvedParticles::MakeEventJets( EventData * ed )
{
   return true;
}


/////////////////////////////////////////////


bool NtupleWrapperTopMiniSLResolvedParticles::MakeEventTruth( EventData * ed )
{
  bool success = true;

  //m_dumper_mctruth->GetEntryWithIndex( ed->info.runNumber, ed->info.eventNumber );
//  m_ntuple_parton->fChain->GetEntryWithIndex( ed->info.runNumber, ed->info.eventNumber );
 
  m_dumper_mctruth->DumpEventLeptons( this->m_ntuple, ed );
  m_dumper_mctruth->DumpEventMET( this->m_ntuple, ed );
  m_dumper_mctruth->DumpEventJets( this->m_ntuple, ed );
//  m_dumper_mctruth->DumpEventMCTruth( this->m_ntuple_parton, ed );

  return success;
}


/////////////////////////////////////////
// Plugin

extern "C" {
  NtupleWrapperPluginFactory_TopMiniSLResolvedParticles * MakeNtupleWrapperPlugin() {
    return new NtupleWrapperPluginFactory_TopMiniSLResolvedParticles( "TopMiniSLResolvedParticles" );
  };
}
