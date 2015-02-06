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

    const int electron_n = ed->electrons.n;
    m_hm->FillHistograms( "reco/cutflow/beforeCuts/el_n", electron_n, weight_reco_level );
    for( int i = 0 ; i < electron_n ; ++i ) {
       const double pt = ed->electrons.pT.at( i ) / GeV;
       const double eta	= ed->electrons.eta.at(i);
       const double phi	= ed->electrons.phi.at(i);

       m_hm->FillHistograms( "reco/cutflow/beforeCuts/el_pt",   pt, weight_reco_level );
       m_hm->FillHistograms( "reco/cutflow/beforeCuts/el_eta", eta, weight_reco_level );
       m_hm->FillHistograms( "reco/cutflow/beforeCuts/el_phi", phi, weight_reco_level );
    }

    const int muon_n = ed->muons.n;
    m_hm->FillHistograms( "reco/cutflow/beforeCuts/mu_n", muon_n, weight_reco_level );
    for( int i = 0 ; i < muon_n ; ++i ) {
       const double pt = ed->muons.pT.at( i ) / GeV;
       const double eta	= ed->muons.eta.at(i);
       const double phi	= ed->muons.phi.at(i);

       m_hm->FillHistograms( "reco/cutflow/beforeCuts/mu_pt",   pt, weight_reco_level );
       m_hm->FillHistograms( "reco/cutflow/beforeCuts/mu_eta", eta, weight_reco_level );
       m_hm->FillHistograms( "reco/cutflow/beforeCuts/mu_phi", phi, weight_reco_level );
    }


    const int jet_n = ed->jets.n;
    m_hm->FillHistograms( "reco/cutflow/beforeCuts/jet_n", jet_n, weight_reco_level );
    for( int i = 0 ; i < jet_n ; ++i ) {
       const double pt = ed->jets.pT.at( i ) / GeV;
       const double eta = ed->jets.eta.at(i);
       const double phi = ed->jets.phi.at(i);
       const double m   = ed->jets.m.at(i) / GeV;

       m_hm->FillHistograms( "reco/cutflow/beforeCuts/jet_pt",   pt, weight_reco_level );
       m_hm->FillHistograms( "reco/cutflow/beforeCuts/jet_eta", eta, weight_reco_level );
       m_hm->FillHistograms( "reco/cutflow/beforeCuts/jet_phi", phi, weight_reco_level );
       m_hm->FillHistograms( "reco/cutflow/beforeCuts/jet_m",     m, weight_reco_level );
    }

    const int bjet_n = ed->bjets.n;
    m_hm->FillHistograms( "reco/cutflow/beforeCuts/bjet_n", bjet_n, weight_reco_level );
    for( int i = 0 ; i < bjet_n ; ++i ) {
       const double pt = ed->bjets.pT.at( i ) / GeV;
       const double eta	= ed->bjets.eta.at(i);
       const double phi	= ed->bjets.phi.at(i);
       const double m  	= ed->bjets.m.at(i) / GeV;

       m_hm->FillHistograms( "reco/cutflow/beforeCuts/bjet_pt",   pt, weight_reco_level );
       m_hm->FillHistograms( "reco/cutflow/beforeCuts/bjet_eta", eta, weight_reco_level );
       m_hm->FillHistograms( "reco/cutflow/beforeCuts/bjet_phi", phi, weight_reco_level );
       m_hm->FillHistograms( "reco/cutflow/beforeCuts/bjet_m",     m, weight_reco_level );
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

