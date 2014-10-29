#include "NtupleWrapperTopMiniSLResolved.h"

NtupleWrapperTopMiniSLResolved::NtupleWrapperTopMiniSLResolved( const AnalysisParams_t analysisParameters ) :
  NtupleWrapper< TopMiniSLResolved >( analysisParameters )
{
   m_dumper_leptons = new EventDumperLeptons<TopMiniSLResolved>();
   m_dumper_leptons->SetNtuple( m_ntuple );
   m_dumper_leptons->SetAnalysisParameters( analysisParameters );

   m_dumper_jets = new EventDumperJets<TopMiniSLResolved>();
   m_dumper_jets->SetNtuple( m_ntuple );
   m_dumper_jets->SetAnalysisParameters( analysisParameters );

//   m_dumper_mctruth = new EventDumperMCTruth<TopMiniSLResolved>();
//   m_dumper_mctruth->SetNtuple( m_ntuple );
//   m_dumper_mctruth->SetAnalysisParameters( analysisParameters );
}

/////////////////////////////////////////////


NtupleWrapperTopMiniSLResolved::~NtupleWrapperTopMiniSLResolved()
{
   if( m_dumper_leptons ) delete m_dumper_leptons;
   if( m_dumper_jets    ) delete m_dumper_jets;
//   if( m_dumper_mctruth ) delete m_dumper_mctruth;
}

/////////////////////////////////////////////


bool NtupleWrapperTopMiniSLResolved::MakeEventInfo( EventData * ed )
{
  bool success = true;

//  ed->info.eventNumber     = GET_VALUE( eventNumber );
//  ed->info.runNumber       = GET_VALUE( runNumber );

//  ed->info.mcChannelNumber = GET_VALUE( channelNumber );
//  ed->info.mcWeight        = GET_VALUE( eventWeight );
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

  return success;
}


/////////////////////////////////////////
// Plugin

extern "C" {
  NtupleWrapperPluginFactory_TopMiniSLResolved * MakeNtupleWrapperPlugin() {
    return new NtupleWrapperPluginFactory_TopMiniSLResolved( "TopMiniSLResolved" );
  };
}
