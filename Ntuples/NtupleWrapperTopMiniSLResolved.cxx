#include "NtupleWrapperTopMiniSLResolved.h"

NtupleWrapperTopMiniSLResolved::NtupleWrapperTopMiniSLResolved( const AnalysisParams_t analysisParameters ) :
  NtupleWrapper< TopMiniSLResolved >( analysisParameters ), 
  m_mcfile(NULL), m_ntuple_particle(NULL), m_ntuple_parton(NULL)
{
   m_dumper_leptons = new EventDumperLeptons<TopMiniSLResolved>();
   m_dumper_leptons->SetNtuple( m_ntuple );
   m_dumper_leptons->SetAnalysisParameters( analysisParameters );

   m_dumper_jets = new EventDumperJets<TopMiniSLResolved>();
   m_dumper_jets->SetNtuple( m_ntuple );
   m_dumper_jets->SetAnalysisParameters( analysisParameters );

   unsigned long isMCSignal = m_config.custom_params_flag["isMCSignal"];
   if( !isMCSignal ) return;

   // open truth ntuples
   const string mcfilename        = m_config.custom_params_string["mcfile"];
   const string treename_particle = m_config.custom_params_string["treename_particle"];
   const string	treename_parton   = m_config.custom_params_string["treename_parton"];

   cout << "INFO: MC tree read from " << mcfilename << endl;

   m_mcfile = TFile::Open( mcfilename.c_str() ); 
   if( !m_mcfile ) throw std::runtime_error( "ERROR: NtupleWrapperTopMiniSLResolved: invalid MC file" );

   m_ntuple_particle = new TopMiniSLResolvedParticles( (TTree*)m_mcfile->Get(treename_particle.c_str()) );
   m_ntuple_parton   = new TopMiniSLResolvedPartons( (TTree*)m_mcfile->Get(treename_parton.c_str()) );

   if( !m_ntuple_particle ) throw std::runtime_error( "ERROR: NtupleWrapperTopMiniSLResolved: invalid particle tree." );
   if( !m_ntuple_parton )   throw std::runtime_error( "ERROR: NtupleWrapperTopMiniSLResolved: invalid parton tree." );

   m_dumper_mctruth = new EventDumperMCTruthTopMiniSLResolved<TopMiniSLResolvedParticles, TopMiniSLResolvedPartons>(); 
   m_dumper_mctruth->SetNtupleParticle( m_ntuple_particle ); 
   m_dumper_mctruth->SetNtupleParton( m_ntuple_parton ); 
   m_dumper_mctruth->SetAnalysisParameters( analysisParameters );
}

/////////////////////////////////////////////


NtupleWrapperTopMiniSLResolved::~NtupleWrapperTopMiniSLResolved()
{
   if( m_mcfile ) {
     m_mcfile->Close();
     SAFE_DELETE( m_mcfile );
     SAFE_DELETE( m_dumper_mctruth );
     SAFE_DELETE( m_ntuple_particle );
     SAFE_DELETE( m_ntuple_parton );
   }

   SAFE_DELETE( m_dumper_leptons );
   SAFE_DELETE( m_dumper_jets );

}

/////////////////////////////////////////////


bool NtupleWrapperTopMiniSLResolved::MakeEventInfo( EventData * ed )
{
  bool success = true;

  ed->info.eventNumber     = GET_VALUE( eventNumber );
  ed->info.runNumber       = GET_VALUE( runNumber );
  ed->info.mcChannelNumber = GET_VALUE( channelNumber );
  ed->info.mcWeight        = GET_VALUE( eventWeight );

  SET_PROPERTY( dataPeriod );
  SET_PROPERTY( mu );

  SET_PROPERTY( pvxp_n );
  SET_PROPERTY( vxp_z );

  SET_PROPERTY( hfor );

  ed->property["scaleFactor_PILEUP"]     = GET_VALUE( scaleFactor_PILEUP     );
  ed->property["scaleFactor_ELE"]        = GET_VALUE( scaleFactor_ELE        );
  ed->property["scaleFactor_MUON"]	 = GET_VALUE( scaleFactor_MUON       );
  ed->property["scaleFactor_BTAG"]	 = GET_VALUE( scaleFactor_BTAG       );
  ed->property["scaleFactor_TRIGGER"]    = GET_VALUE( scaleFactor_TRIGGER    );
  ed->property["scaleFactor_WJETSNORM"]  = GET_VALUE( scaleFactor_WJETSNORM  );
  ed->property["scaleFactor_WJETSSHAPE"] = GET_VALUE( scaleFactor_WJETSSHAPE );
  ed->property["scaleFactor_JVFSF"]	 = GET_VALUE( scaleFactor_JVFSF      );
  ed->property["scaleFactor_ZVERTEX"]    = GET_VALUE( scaleFactor_ZVERTEX    );

  // truth switched on? get event by index here.

  return success;
}


/////////////////////////////////////////////


bool NtupleWrapperTopMiniSLResolved::MakeEventTrigger( EventData * ed )
{ 
  bool success = true;

// CHECK_TRIGGER( "EF_mu18i" );

  return success;
}


/////////////////////////////////////////////


bool NtupleWrapperTopMiniSLResolved::MakeEventMET( EventData * ed )
{
  bool success = true;

  ed->MET.et    = GET_VALUE( met_et );
  ed->MET.phi   = GET_VALUE( met_phi );
  //  ed->MET.etx   = 0.;
  //  ed->MET.ety   = 0.;
  ed->MET.sumet = GET_VALUE( met_sumet  );
  ed->MET.mwt   = GET_VALUE( mwt );
  //  SET_PROPERTY( mwt );

  return success;
}


/////////////////////////////////////////////

bool NtupleWrapperTopMiniSLResolved::MakeEventLeptons( EventData * ed )
{
  return m_dumper_leptons->DumpEventLeptons( ed );
}


/////////////////////////////////////////////


bool NtupleWrapperTopMiniSLResolved::MakeEventJets( EventData * ed )
{
  return m_dumper_jets->DumpEventJets( ed );
}


/////////////////////////////////////////////


bool NtupleWrapperTopMiniSLResolved::MakeEventTruth( EventData * ed )
{
  bool success = true;

  unsigned long isMCSignal = m_config.custom_params_flag["isMCSignal"];
  if( !isMCSignal ) return success;
  
  m_dumper_mctruth->GetEntryWithIndex( ed->info.eventNumber );

  m_dumper_mctruth->DumpEventLeptons( ed );
  m_dumper_mctruth->DumpEventMET( ed );
  m_dumper_mctruth->DumpEventJets( ed );
  m_dumper_mctruth->DumpEventMCTruth( ed );

  return success;
}


/////////////////////////////////////////
// Plugin

extern "C" {
  NtupleWrapperPluginFactory_TopMiniSLResolved * MakeNtupleWrapperPlugin() {
    return new NtupleWrapperPluginFactory_TopMiniSLResolved( "TopMiniSLResolved" );
  };
}
