#include "CutFlowTTHTo2LeptonsSS.h"

CutFlowTTHTo2LeptonsSS::CutFlowTTHTo2LeptonsSS()
{
}

CutFlowTTHTo2LeptonsSS::~CutFlowTTHTo2LeptonsSS()
{
}


/////////////////////////////////////////


bool CutFlowTTHTo2LeptonsSS::Initialize()
{
  bool success = true;

  AddChannel( "ALL" );
  AddCounterName( "ALL", "good_el",  10 );
  AddCounterName( "ALL", "good_mu",  9 );
  AddCounterName( "ALL", "good_jet", 2 );

  AddChannel( "ELEL" );
  AddCounterName( "ELEL", "weighted",   8 );
  AddCounterName( "ELEL", "unweight",   8 );

  AddChannel( "MUMU" );
  AddCounterName( "MUMU", "weighted", 8 );
  AddCounterName( "MUMU", "unweight", 8 );

  // di-electron channel
  SetCutName( "ELEL", "weighted", 0, "All Events" );
  SetCutName( "ELEL", "weighted", 1, "Trigger" );
  SetCutName( "ELEL", "weighted", 2, "Prim. Vtx" );
  SetCutName( "ELEL", "weighted", 3, "Cleaning" );
  SetCutName( "ELEL", "weighted", 4, "2 leptons" );
  SetCutName( "ELEL", "weighted", 5, "2 electrons" );
  SetCutName( "ELEL", "weighted", 6, ">= 1 SS pair" );
  SetCutName( "ELEL", "weighted", 7, "Z mass veto" );
  SetCutName( "ELEL", "weighted", 8, ">= 2 jet" );

  SetCutName( "ELEL", "unweight", 0, "All Events" );
  SetCutName( "ELEL", "unweight", 1, "Trigger" );
  SetCutName( "ELEL", "unweight", 2, "Prim. Vtx" );
  SetCutName( "ELEL", "unweight", 3, "Cleaning" );
  SetCutName( "ELEL", "unweight", 4, "2 leptons" );
  SetCutName( "ELEL", "unweight", 5, "2 electrons" );
  SetCutName( "ELEL", "unweight", 6, ">= 1 SS pair" );
  SetCutName( "ELEL", "unweight", 7, "Z mass veto" );
  SetCutName( "ELEL", "unweight", 8, ">= 2 jet" );

  // di-muon channel
  SetCutName( "MUMU", "weighted", 0, "All Events" );
  SetCutName( "MUMU", "weighted", 1, "Trigger" );
  SetCutName( "MUMU", "weighted", 2, "Prim. Vtx" );
  SetCutName( "MUMU", "weighted", 3, "Cleaning" );
  SetCutName( "MUMU", "weighted", 4, "2 leptons" );
  SetCutName( "MUMU", "weighted", 5, "2 muons" );
  SetCutName( "MUMU", "weighted", 6, ">= 1 SS pair" );
  SetCutName( "MUMU", "weighted", 7, "Z mass veto" );
  SetCutName( "MUMU", "weighted", 8, ">= 2 jet" );

  SetCutName( "MUMU", "unweight", 0, "All Events" );
  SetCutName( "MUMU", "unweight", 1, "Trigger" );
  SetCutName( "MUMU", "unweight", 2, "Prim. Vtx" );
  SetCutName( "MUMU", "unweight", 3, "Cleaning" );
  SetCutName( "MUMU", "unweight", 4, "2 leptons" );
  SetCutName( "MUMU", "unweight", 5, "2 muons" );
  SetCutName( "MUMU", "unweight", 6, ">= 1 SS pair" );
  SetCutName( "MUMU", "unweight", 7, "Z mass veto" );
  SetCutName( "MUMU", "unweight", 8, ">= 2 jet" );

  //  good electron channel
  SetCutName( "ALL", "good_el", 0, "Input" );
  SetCutName( "ALL", "good_el", 1, "CutAuthor" );
  SetCutName( "ALL", "good_el", 2, "CutEta" );
  SetCutName( "ALL", "good_el", 3, "CutEtaCrack" );
  SetCutName( "ALL", "good_el", 4, "CutPt" );
  SetCutName( "ALL", "good_el", 5, "CutPID" );
  SetCutName( "ALL", "good_el", 6, "CutZ0Sin" );
  SetCutName( "ALL", "good_el", 7, "CutD0SIg" );
  SetCutName( "ALL", "good_el", 8, "CutEtIso1" );
  SetCutName( "ALL", "good_el", 9, "CutEtIso2" );
  SetCutName( "ALL", "good_el", 10, "CutPtIso" );

  //  good muon channel
  SetCutName( "ALL", "good_mu", 0, "Input" );
  SetCutName( "ALL", "good_mu", 1, "CutEta" );
  SetCutName( "ALL", "good_mu", 2, "CutPt" );
  SetCutName( "ALL", "good_mu", 3, "CutCombined" );
  SetCutName( "ALL", "good_mu", 4, "CutPID" );
  SetCutName( "ALL", "good_mu", 5, "CutZ0Sin" );
  SetCutName( "ALL", "good_mu", 6, "CutD0Sig" );
  SetCutName( "ALL", "good_mu", 7, "CutEtIso1" );
  SetCutName( "ALL", "good_mu", 8, "CutEtIso2" );
  SetCutName( "ALL", "good_mu", 9, "CutPtIso" );

  SetCutName( "ALL", "good_jet", 0, "Input" );
  SetCutName( "ALL", "good_jet", 1, "CutPt1" );
  SetCutName( "ALL", "good_jet", 2, "CutPt2" );

  return success;
}


/////////////////////////////////////////


bool CutFlowTTHTo2LeptonsSS::Apply( EventData * ed )
{
  bool success = true;

  CutFlow::Start();

  int el_n  = ed->electrons.n;
  int mu_n  = ed->muons.n;
  int jet_n = ed->jets.n;
  double ETmiss = ed->MET.et;
  double weight = ed->info.mcWeight;

  if( ETmiss == 0. ) 
    ETmiss = -1e10;

  m_hm->GetHistogram( "met_pt" )->Fill( ETmiss/GeV, weight );
  m_hm->GetHistogram( "el_n" )->Fill( el_n, weight );
  m_hm->GetHistogram( "mu_n" )->Fill( mu_n, weight );
  m_hm->GetHistogram( "jet_n" )->Fill( jet_n, weight );


  //////////////////////////////
  // Start Preselection

  for( int j = 0 ; j < el_n ; ++j ) {

    double el_pt = ed->electrons.pT.at( j )/GeV;

    m_hm->GetHistogram( "el_pt" )->Fill( el_pt, weight );
    m_hm->GetHistogram( "el_eta" )->Fill( ed->electrons.eta.at( j ), weight );
    m_hm->GetHistogram( "el_phi" )->Fill( ed->electrons.phi.at( j ), weight );
    m_hm->GetHistogram( "el_E" )->Fill( ed->electrons.E.at( j ) / GeV, weight );

    double etcone20_o_pT = ed->electrons.property["Etcone20"].at(j) / el_pt;
    m_hm->GetHistogram( "el_Etcone20_over_pT" )->Fill( etcone20_o_pT, weight );

    // CutFlow GOOD electrons
    IncreaseCount( "ALL_cutflow_good_el", 0 );

    // CutAuthor
    double el_author = ed->electrons.property["author"].at(j);
    if (!(el_author ==1 || el_author==3 ))
      continue;
    IncreaseCount( "ALL_cutflow_good_el", 1 );

    //CutEta
    if (fabs(ed->electrons.property["ClEta"].at(j)) > 2.47)
      continue;
    IncreaseCount( "ALL_cutflow_good_el", 2 );

    //CutEtaCrack
    if (!(fabs(ed->electrons.property["ClEta"].at(j))<1.37 || fabs(ed->electrons.property["ClEta"].at(j))>1.52))
      continue;
    IncreaseCount( "ALL_cutflow_good_el", 3 );

    //CutPt
    if (el_pt < 10)
      continue;
    IncreaseCount( "ALL_cutflow_good_el", 4 );

    //CutPID
    if (ed->electrons.property["isMediumPP"].at(j)!=1)
      continue;
    IncreaseCount( "ALL_cutflow_good_el", 5 );

    //CutZ0Sin
    if (fabs(ed->electrons.property["z0SinTheta"].at(j))>= 0.4)
      continue;
    IncreaseCount( "ALL_cutflow_good_el", 6 );

    //CutD0Sig
    if (fabs(ed->electrons.property["sigd0PV"].at(j))>=3.)
      continue;
    IncreaseCount( "ALL_cutflow_good_el", 7 );

     //CutEtIso1
    if (!(el_pt <20 || etcone20_o_pT < 0.1))
      continue;
    IncreaseCount( "ALL_cutflow_good_el", 8 );

    //CutEtIso2
    if (!(el_pt >= 20 || etcone20_o_pT < 0.05))
      continue;
    IncreaseCount( "ALL_cutflow_good_el", 9 );

    //CutPtIso
    double ptcone20_o_pT = ed->electrons.property["ptcone20"].at(j) / el_pt;
    if (ptcone20_o_pT > 0.05)
      continue;
    IncreaseCount( "ALL_cutflow_good_el", 10 );

  }

  for( int j = 0 ; j < mu_n ; ++j ) {
    
    double mu_eta = ed->muons.eta.at( j );
    double mu_pt = ed->muons.pT.at( j )/GeV;
    double etcone20_o_pT = ed->muons.property["Etcone20"].at(j) / mu_pt;

    m_hm->GetHistogram( "mu_pt" )->Fill( mu_pt, weight );
    m_hm->GetHistogram( "mu_eta" )->Fill( mu_eta, weight );
    m_hm->GetHistogram( "mu_phi" )->Fill( ed->muons.phi.at( j ), weight );
    m_hm->GetHistogram( "mu_E" )->Fill( ed->muons.E.at( j ) / GeV, weight );

    // CutFlow GOOD muons
    IncreaseCount( "ALL_cutflow_good_mu", 0 );
    // CutEta
    if (fabs(mu_eta)>2.5)
      continue;
    IncreaseCount( "ALL_cutflow_good_mu", 1 );
    // CutPt
    if (mu_pt<10)
      continue;
    IncreaseCount( "ALL_cutflow_good_mu", 2 );
    // CutCombined
    if (ed->muons.property["isCombined"].at(j)!=1)
      continue;
    IncreaseCount( "ALL_cutflow_good_mu", 3 );
    // CutPID
    if (ed->muons.property["isTight"].at(j)!=1)
      continue;
    IncreaseCount( "ALL_cutflow_good_mu", 4 );
     //CutZ0Sin
    if (fabs(ed->muons.property["z0SinTheta"].at(j))>=1)
      continue;
    IncreaseCount( "ALL_cutflow_good_mu", 5 );
    //CutD0Sig
    if (fabs(ed->muons.property["sigd0PV"].at(j))>=3)
      continue;
    IncreaseCount( "ALL_cutflow_good_mu", 6 );
    //CutEtIso1
    if (!(mu_pt <20 || etcone20_o_pT<0.1))
      continue;
    IncreaseCount( "ALL_cutflow_good_mu", 7 );
    //CutEtIso2
    if (!(mu_pt >= 20 || etcone20_o_pT <0.05))
      continue;
    IncreaseCount( "ALL_cutflow_good_mu", 8 );
    //CutPtIso
    double ptcone20_o_pT = ed->muons.property["ptcone20"].at(j) / mu_pt;
    if (ptcone20_o_pT >= 0.05)
      continue;
    IncreaseCount( "ALL_cutflow_good_mu", 9 );

  }

  for( int j = 0 ; j < jet_n ; ++j ) {

    double jet_pt = ed->jets.pT.at( j ) / GeV;
    double jet_eta = ed->jets.eta.at( j );

    m_hm->GetHistogram( "jet_pt" )->Fill( jet_pt, weight );
    m_hm->GetHistogram( "jet_eta" )->Fill( jet_eta, weight );
    m_hm->GetHistogram( "jet_phi" )->Fill( ed->jets.phi.at( j ), weight );
    m_hm->GetHistogram( "jet_E" )->Fill( ed->jets.E.at( j ) / GeV, weight );

    // CutFlow GOOD jets
    IncreaseCount( "ALL_cutflow_good_jet", 0 );

    // CutPt1
    if (jet_pt<25)
      continue;
    IncreaseCount( "ALL_cutflow_good_jet", 1 );

    // CutPt2
    if (!(jet_pt>30 || fabs(jet_eta)<2.4))
      continue;
   IncreaseCount( "ALL_cutflow_good_jet", 2 );

  }

  //////////////////////////////
  // Start real analysis

  PassedCut( "ELEL", "weighted", weight );
  PassedCut( "ELEL", "unweight" );
  PassedCut( "MUMU", "weighted", weight );
  PassedCut( "MUMU", "unweight" );
 
  // Pass electron trigger
  bool trigflag = 
    ( PASSED_TRIGGER( "EF_e24vhi_medium1" ) || PASSED_TRIGGER( "EF_e24vhi_medium1" ) ) ||
    ( PASSED_TRIGGER( "EF_e60_medium1" )    || PASSED_TRIGGER( "EF_mu24i_tight" ) );
  if( !trigflag ) 
    return success;
  PassedCut( "ELEL", "weighted", weight );
  PassedCut( "ELEL", "unweight" );
  PassedCut( "MUMU", "weighted", weight );
  PassedCut( "MUMU", "unweight" );

  // PV
  if( int(ed->property["goodPV"]) == 0 ) 
    return success;
  PassedCut( "ELEL", "weighted", weight );
  PassedCut( "ELEL", "unweight" );
  PassedCut( "MUMU", "weighted", weight );
  PassedCut( "MUMU", "unweight" );

  // Event cleaning
  if( int( ed->property["passEventCleaning"] ) != 1 ) 
    return success;
  PassedCut( "ELEL", "weighted", weight );
  PassedCut( "ELEL", "unweight" );
  PassedCut( "MUMU", "weighted", weight );
  PassedCut( "MUMU", "unweight" );

  // At least 2 electrons, or 2 muons, or 1e1mu
  if( ( el_n + mu_n ) < 2 ) 
    return success;
  PassedCut( "ELEL", "weighted", weight );
  PassedCut( "ELEL", "unweight" );
  PassedCut( "MUMU", "weighted", weight );
  PassedCut( "MUMU", "unweight" );

  // 2 el
  if( el_n < 2 ) 
    return success;
  PassedCut( "ELEL", "weighted", weight );
  PassedCut( "ELEL", "unweight" );

  // 2 mu
  if( mu_n < 2 ) 
    return success;
  PassedCut( "MUMU", "weighted", weight );
  PassedCut( "MUMU", "unweight" );

  // Same-sign
  const double q1 = ed->electrons.q[0];
  const double q2 = ed->electrons.q[1];
  if( q1*q2 < 0 ) 
    return success;
  PassedCut( "ELEL", "weighted", weight );
  PassedCut( "ELEL", "unweight" );

  const double q1_mu = ed->muons.q[0];
  const double q2_mu = ed->muons.q[1];
  if( q1_mu*q2_mu < 0 ) 
    return success;
  PassedCut( "MUMU", "weighted", weight );
  PassedCut( "MUMU", "unweight" );

  // Z mass veto
  TLorentzVector Z = HelperFunctions::MakeFourMomentum( ed->electrons, 0 ) + HelperFunctions::MakeFourMomentum( ed->electrons, 1 );
  if( fabs( Z.M()/GeV - 91.2 ) <= 10. ) 
    return success;
  PassedCut( "ELEL", "weighted", weight );
  PassedCut( "ELEL", "unweight" );

  // Z mass veto
  TLorentzVector Z_mu = HelperFunctions::MakeFourMomentum( ed->muons, 0 ) + HelperFunctions::MakeFourMomentum( ed->muons, 1 );
  if( fabs( Z_mu.M()/GeV - 91.2 ) <= 10. ) 
    return success;
  PassedCut( "MUMU", "weighted", weight );
  PassedCut( "MUMU", "unweight" );

  // jet count
  if( jet_n < 2 ) 
    return success;
  PassedCut( "ELEL", "weighted", weight );
  PassedCut( "ELEL", "unweight" );
  PassedCut( "MUMU", "weighted", weight );
  PassedCut( "MUMU", "unweight" );

  return success;
}


/////////////////////////////////////////
// Plugin

extern "C" {
  CutFlowPluginFactory_TTHTo2LeptonsSS * MakeCutFlowPlugin() {
    return new CutFlowPluginFactory_TTHTo2LeptonsSS( "TTHTo2LeptonsSS" );
  };
}

