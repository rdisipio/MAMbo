#include "NtupleWrapperTopMini.h"

NtupleWrapperTopMini::NtupleWrapperTopMini( const AnalysisParams_t analysisParameters ) : 
  NtupleWrapper< TopMini >( analysisParameters )
{
/*
   m_dumper = new EventDumperBoostedMiniSL();
   m_dumper->SetNtuple( m_ntuple );
   m_dumper->SetAnalysisParameters( analysisParameters );
*/
   m_dumper_info = new EventDumperEventInfo();
   m_dumper_info->SetNtuple( m_ntuple );
   m_dumper_info->SetAnalysisParameters( analysisParameters );

 
   m_dumper_leptons = new EventDumperLeptons();
   m_dumper_leptons->SetNtuple( m_ntuple );
   m_dumper_leptons->SetAnalysisParameters( analysisParameters );

   m_dumper_jets = new EventDumperJets();
   m_dumper_jets->SetNtuple( m_ntuple );
   m_dumper_jets->SetAnalysisParameters( analysisParameters );

   m_dumper_mctruth = new EventDumperMCTruth<TopMini>();
   m_dumper_mctruth->SetNtuple( m_ntuple );
   m_dumper_mctruth->SetAnalysisParameters( analysisParameters );

}

/////////////////////////////////////////////


NtupleWrapperTopMini::~NtupleWrapperTopMini()
{
   if( m_dumper_leptons ) delete m_dumper_leptons;
   if( m_dumper_jets    ) delete m_dumper_jets;
   if( m_dumper_mctruth ) delete m_dumper_mctruth;
}

/////////////////////////////////////////////


bool NtupleWrapperTopMini::MakeEventInfo( EventData * ed )
{
  return m_dumper_info->DumpEventInfo( ed );
}


/////////////////////////////////////////////


bool NtupleWrapperTopMini::MakeEventTrigger( EventData * ed )
{ 
  return m_dumper_info->DumpEventTrigger( ed );
}


/////////////////////////////////////////////


bool NtupleWrapperTopMini::MakeEventMET( EventData * ed )
{
  return m_dumper_info->DumpEventMET( ed );
}


/////////////////////////////////////////////


bool NtupleWrapperTopMini::MakeEventLeptons( EventData * ed )
{ 
  return m_dumper_leptons->DumpEventLeptons( ed );
}
  

/////////////////////////////////////////////


bool NtupleWrapperTopMini::MakeEventJets( EventData * ed )
{
   return m_dumper_jets->DumpEventJets( ed );
}


/////////////////////////////////////////////


bool NtupleWrapperTopMini::MakeEventTruth( EventData * ed )
{
  return m_dumper_mctruth->DumpEventMCTruth( ed );
}


/////////////////////////////////////////
// Plugin

extern "C" {
  NtupleWrapperPluginFactory_TopMini * MakeNtupleWrapperPlugin() {
    return new NtupleWrapperPluginFactory_TopMini( "TopMini" );
  };
}
