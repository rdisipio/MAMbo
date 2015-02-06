#include "CutFlowDummy.h"

CutFlowDummy::CutFlowDummy() 
{   
}

CutFlowDummy::~CutFlowDummy() {
}

/////////////////////////////////////////

bool CutFlowDummy::Initialize() {
    bool success = true;

    AddChannel("ALL");

    AddCounterName( "ALL", "reco_unweight", 1 );
    SetCutName( "ALL", "reco_unweight", 0, "All Events");

    return success;
}


/////////////////////////////////////////

bool FillHistograms(int cutN) {
    bool success = true;

    return success;
}


/////////////////////////////////////////

bool CutFlowDummy::Apply(EventData * ed) {
    bool success = true;

    CutFlow::Start();

    double weight_reco_level     = 1.;

    ed->property["weight_reco_level"]     = weight_reco_level;

    PassedCut( "ALL", "reco_unweight");

    const int jet_n = ed->jets.n;

    m_hm->FillHistograms( "reco/cutflow/beforeCuts/jet_n", jet_n, weight_reco_level );
    for( int i = 0 ; i < jet_n ; ++i ) {
       const double pt = ed->jets.pT.at( i ) / GeV;

       m_hm->FillHistograms( "reco/cutflow/beforeCuts/jet_pt", pt, weight_reco_level );

//       cout << "INFO: event " << ed->info.eventNumber << " jet " << i << " pT = " << pt << " GeV" << endl;

    }

    return success;
}


/////////////////////////////////////////

  
/////////////////////////////////////////
// Plugin

extern "C" {

    CutFlowPluginFactory_Dummy * MakeCutFlowPlugin() {
        return new CutFlowPluginFactory_Dummy("Dummy");
    };
}

