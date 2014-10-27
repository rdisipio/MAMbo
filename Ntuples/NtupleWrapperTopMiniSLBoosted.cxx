#include "NtupleWrapperTopMiniSLBoosted.h"

NtupleWrapperTopMiniSLBoosted::NtupleWrapperTopMiniSLBoosted( const AnalysisParams_t analysisParameters ) : 
  NtupleWrapper< TopMiniSLBoosted >( analysisParameters )
{
   m_dumper_info = new EventDumperEventInfo<TopMiniSLBoosted>();
   m_dumper_info->SetNtuple( m_ntuple );
   m_dumper_info->SetAnalysisParameters( analysisParameters );
 
   m_dumper_leptons = new EventDumperLeptons<TopMiniSLBoosted>();
   m_dumper_leptons->SetNtuple( m_ntuple );
   m_dumper_leptons->SetAnalysisParameters( analysisParameters );

   m_dumper_jets = new EventDumperJets<TopMiniSLBoosted>();
   m_dumper_jets->SetNtuple( m_ntuple );
   m_dumper_jets->SetAnalysisParameters( analysisParameters );

   m_dumper_mctruth = new EventDumperMCTruth<TopMiniSLBoosted>();
   m_dumper_mctruth->SetNtuple( m_ntuple );
   m_dumper_mctruth->SetAnalysisParameters( analysisParameters );

}

/////////////////////////////////////////////


NtupleWrapperTopMiniSLBoosted::~NtupleWrapperTopMiniSLBoosted()
{
   if( m_dumper_leptons ) delete m_dumper_leptons;
   if( m_dumper_jets    ) delete m_dumper_jets;
   if( m_dumper_mctruth ) delete m_dumper_mctruth;
}

/////////////////////////////////////////////


bool NtupleWrapperTopMiniSLBoosted::MakeEventInfo( EventData * ed )
{
  return m_dumper_info->DumpEventInfo( ed );
}


/////////////////////////////////////////////


bool NtupleWrapperTopMiniSLBoosted::MakeEventTrigger( EventData * ed )
{ 
  return m_dumper_info->DumpEventTrigger( ed );
}


/////////////////////////////////////////////


bool NtupleWrapperTopMiniSLBoosted::MakeEventMET( EventData * ed )
{
  return m_dumper_info->DumpEventMET( ed );
}


/////////////////////////////////////////////


bool NtupleWrapperTopMiniSLBoosted::MakeEventLeptons( EventData * ed )
{ 
  return m_dumper_leptons->DumpEventLeptons( ed );
}
  

/////////////////////////////////////////////


bool NtupleWrapperTopMiniSLBoosted::MakeEventJets( EventData * ed )
{
   return m_dumper_jets->DumpEventJets( ed );
}


/////////////////////////////////////////////


bool NtupleWrapperTopMiniSLBoosted::MakeEventTruth( EventData * ed )
{
  return m_dumper_mctruth->DumpEventMCTruth( ed );
}


/////////////////////////////////////////
// Plugin

extern "C" {
  NtupleWrapperPluginFactory_TopMiniSLBoosted * MakeNtupleWrapperPlugin() {
    return new NtupleWrapperPluginFactory_TopMiniSLBoosted( "TopMiniSLBoosted" );
  };
}
