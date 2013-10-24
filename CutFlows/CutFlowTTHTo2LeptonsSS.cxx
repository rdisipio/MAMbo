#include "CutFlowTTHTo2LeptonsSS.h"

CutFlowTTHTo2LeptonsSS::CutFlowTTHTo2LeptonsSS()
{
  AddChannel( "ELEL" );
  AddChannel( "MUMU" );

  AddCounterName( "ELEL", "ee_weighted" );
  AddCounterName( "ELEL", "ee_unweight" );
  AddCounterName( "MUMU", "mumu_unweight" );
}

CutFlowTTHTo2LeptonsSS::~CutFlowTTHTo2LeptonsSS()
{
}


/////////////////////////////////////////


bool CutFlowTTHTo2LeptonsSS::Initialize()
{
  bool success = true;

  SetCutName( "ELEL", "ee_weighted", 0, "All Events" );
  SetCutName( "ELEL", "ee_weighted", 1, "Trigger" );
  SetCutName( "ELEL", "ee_weighted", 2, "Prim. Vtx" );
  SetCutName( "ELEL", "ee_weighted", 3, "Cleaning" );
  SetCutName( "ELEL", "ee_weighted", 4, "2 leptons" );
  SetCutName( "ELEL", "ee_weighted", 5, "2 electrons" );
  SetCutName( "ELEL", "ee_weighted", 6, ">= 1 SS pair" );
  SetCutName( "ELEL", "ee_weighted", 7, "Z mass veto" );
  SetCutName( "ELEL", "ee_weighted", 8, ">= 2 jet" );

  SetCutName( "ELEL", "ee_unweight", 0, "All Events" );
  SetCutName( "ELEL", "ee_unweight", 1, "Trigger" );
  SetCutName( "ELEL", "ee_unweight", 2, "Prim. Vtx" );
  SetCutName( "ELEL", "ee_unweight", 3, "Cleaning" );
  SetCutName( "ELEL", "ee_unweight", 4, "2 leptons" );
  SetCutName( "ELEL", "ee_unweight", 5, "2 electrons" );
  SetCutName( "ELEL", "ee_unweight", 6, ">= 1 SS pair" );
  SetCutName( "ELEL", "ee_unweight", 7, "Z mass veto" );
  SetCutName( "ELEL", "ee_unweight", 8, ">= 2 jet" );

  SetCutName( "MUMU", "mumu_unweight", 0, "All Events" );
  SetCutName( "MUMU", "mumu_unweight", 1, "Trigger" );
  SetCutName( "MUMU", "mumu_unweight", 2, "Prim. Vtx" );
  SetCutName( "MUMU", "mumu_unweight", 3, "Cleaning" );
  SetCutName( "MUMU", "mumu_unweight", 4, "2 leptons" );
  SetCutName( "MUMU", "mumu_unweight", 5, "2 muons" );
  SetCutName( "MUMU", "mumu_unweight", 6, ">= 1 SS pair" );
  SetCutName( "MUMU", "mumu_unweight", 7, "Z mass veto" );
  SetCutName( "MUMU", "mumu_unweight", 8, ">= 2 jet" );

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

  for( int j = 0 ; j < el_n ; ++j ) {

    double el_pt = ed->electrons.pT.at( j )/GeV;

    m_hm->GetHistogram( "el_pt" )->Fill( el_pt, weight );
    m_hm->GetHistogram( "el_eta" )->Fill( ed->electrons.eta.at( j ), weight );
    m_hm->GetHistogram( "el_phi" )->Fill( ed->electrons.phi.at( j ), weight );
    m_hm->GetHistogram( "el_E" )->Fill( ed->electrons.E.at( j ) / GeV, weight );

    double etcone20_o_pT = ed->electrons.property["Etcone20"].at(j) / el_pt;
    m_hm->GetHistogram( "el_Etcone20_over_pT" )->Fill( etcone20_o_pT, weight );

    // CutFlow GOOD electrons
    m_hm->GetHistogram("el_Good_CutFlow")->Fill(0);
    // CutAuthor
    double el_author = ed->electrons.property["author"].at(j);
    if (!(el_author ==1 || el_author==3 ))
      continue;
    m_hm->GetHistogram("el_Good_CutFlow")->Fill(1);
    //CutEta
    if (fabs(ed->electrons.property["ClEta"].at(j)) > 2.47)
      continue;
    m_hm->GetHistogram("el_Good_CutFlow")->Fill(2); 
    //CutEtaCrack
    if (!(fabs(ed->electrons.property["ClEta"].at(j))<1.37 || fabs(ed->electrons.property["ClEta"].at(j))>1.52))
      continue;
    m_hm->GetHistogram("el_Good_CutFlow")->Fill(3);
    //CutPt
    if (el_pt < 10)
      continue;
    m_hm->GetHistogram("el_Good_CutFlow")->Fill(4);
    //CutPID
    if (ed->electrons.property["isMediumPP"].at(j)!=1)
      continue;
    m_hm->GetHistogram("el_Good_CutFlow")->Fill(5);
    //CutZ0Sin
    if (ed->electrons.property["z0PV"].at(j)>= 0.4)
      continue;
    m_hm->GetHistogram("el_Good_CutFlow")->Fill(6);
    //CutD0Sig
    if (ed->electrons.property["sigd0PV"].at(j)>=3)
      continue;
    m_hm->GetHistogram("el_Good_CutFlow")->Fill(7);
    //CutEtIso1
    if (!(el_pt <20 || etcone20_o_pT<0.1))
      continue;
    m_hm->GetHistogram("el_Good_CutFlow")->Fill(8);
    //CutEtIso2
    if (!(el_pt >= 20 || etcone20_o_pT <0.05))
      continue;
    m_hm->GetHistogram("el_Good_CutFlow")->Fill(9);
    //CutPtIso
    double ptcone20_o_pT = ed->electrons.property["ptcone20"].at(j) / el_pt;
    if (ptcone20_o_pT > 0.05)
      continue;
    m_hm->GetHistogram("el_Good_CutFlow")->Fill(10);

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
    m_hm->GetHistogram("mu_Good_CutFlow")->Fill(0);
    // CutEta
    if (fabs(mu_eta)>2.5)
      continue;
    m_hm->GetHistogram("mu_Good_CutFlow")->Fill(1);
    // CutPt
    if (mu_pt<10)
      continue;
    m_hm->GetHistogram("mu_Good_CutFlow")->Fill(2);
    // CutCombined
    if (ed->muons.property["isCombined"].at(j)!=1)
      continue;
    m_hm->GetHistogram("mu_Good_CutFlow")->Fill(3);
    // CutPID
    if (ed->muons.property["isTight"].at(j)!=1)
      continue;
    m_hm->GetHistogram("mu_Good_CutFlow")->Fill(4);
     //CutZ0Sin
    if (ed->muons.property["z0PV"].at(j)>=1)
      continue;
    m_hm->GetHistogram("mu_Good_CutFlow")->Fill(5);
    //CutD0Sig
    if (ed->muons.property["sigd0PV"].at(j)>=3)
      continue;
    m_hm->GetHistogram("mu_Good_CutFlow")->Fill(6);
    //CutEtIso1
    if (!(mu_pt <20 || etcone20_o_pT<0.1))
      continue;
    m_hm->GetHistogram("mu_Good_CutFlow")->Fill(7);
    //CutEtIso2
    if (!(mu_pt >= 20 || etcone20_o_pT <0.05))
      continue;
    m_hm->GetHistogram("mu_Good_CutFlow")->Fill(8);
    //CutPtIso
    double ptcone20_o_pT = ed->muons.property["ptcone20"].at(j) / mu_pt;
    if (ptcone20_o_pT >= 0.05)
      continue;
    m_hm->GetHistogram("mu_Good_CutFlow")->Fill(9);

  }

  for( int j = 0 ; j < jet_n ; ++j ) {

    double jet_pt = ed->jets.pT.at( j ) / GeV;
    double jet_eta = ed->jets.eta.at( j );

    m_hm->GetHistogram( "jet_pt" )->Fill( jet_pt, weight );
    m_hm->GetHistogram( "jet_eta" )->Fill( jet_eta, weight );
    m_hm->GetHistogram( "jet_phi" )->Fill( ed->jets.phi.at( j ), weight );
    m_hm->GetHistogram( "jet_E" )->Fill( ed->jets.E.at( j ) / GeV, weight );

    // CutFlow GOOD jets
    m_hm->GetHistogram("jet_Good_CutFlow")->Fill(0);
    // CutPt1
    if (jet_pt<25)
      continue;
    m_hm->GetHistogram("jet_Good_CutFlow")->Fill(1);
    // CutPt2
    if (!(jet_pt>30 || fabs(jet_eta)<2.4))
      continue;
    m_hm->GetHistogram("jet_Good_CutFlow")->Fill(2);

  }

  PassedCut( "ELEL", "ee_weighted", weight );
  PassedCut( "ELEL", "ee_unweight" );
  PassedCut( "MUMU", "mumu_unweight" );
 
  // Pass electron trigger
  bool trigflag = 
    ( PASSED_TRIGGER( "EF_e24vhi_medium1" ) || PASSED_TRIGGER( "EF_e24vhi_medium1" ) ) ||
    ( PASSED_TRIGGER( "EF_e60_medium1" )    || PASSED_TRIGGER( "EF_mu24i_tight" ) );
  if( !trigflag ) 
    return success;
  PassedCut( "ELEL", "ee_weighted", weight );
  PassedCut( "ELEL", "ee_unweight" );
  PassedCut( "MUMU", "mumu_unweight" );

  // PV
  if( int(ed->property["goodPV"]) == 0 ) 
    return success;
  PassedCut( "ELEL", "ee_weighted", weight );
  PassedCut( "ELEL", "ee_unweight" );
  PassedCut( "MUMU", "mumu_unweight" );

  // Event cleaning
  if( int( ed->property["passEventCleaning"] ) != 1 ) 
    return success;
  PassedCut( "ELEL", "ee_weighted", weight );
  PassedCut( "ELEL", "ee_unweight" );
  PassedCut( "MUMU", "mumu_unweight" );

  // At least 2 electrons, or 2 muons, or 1e1mu
  if( ( el_n + mu_n ) < 2 ) 
    return success;
  PassedCut( "ELEL", "ee_weighted", weight );
  PassedCut( "ELEL", "ee_unweight" );
  PassedCut( "MUMU", "mumu_unweight" );

  // 2 el
  if( el_n < 2 ) 
    return success;
  PassedCut( "ELEL", "ee_weighted", weight );
  PassedCut( "ELEL", "ee_unweight" );

  // 2 mu
  if( mu_n < 2 ) 
    return success;
  PassedCut( "MUMU", "mumu_unweight" );

  // Same-sign
  const double q1 = ed->electrons.q[0];
  const double q2 = ed->electrons.q[1];
  if( q1*q2 < 0 ) 
    return success;
  PassedCut( "ELEL", "ee_weighted", weight );
  PassedCut( "ELEL", "ee_unweight" );

  const double q1_mu = ed->muons.q[0];
  const double q2_mu = ed->muons.q[1];
  if( q1_mu*q2_mu < 0 ) 
    return success;
  PassedCut( "MUMU", "mumu_unweight" );

  // Z mass veto
  TLorentzVector Z = HelperFunctions::MakeFourMomentum( ed->electrons, 0 ) + HelperFunctions::MakeFourMomentum( ed->electrons, 1 );
  if( fabs( Z.M()/GeV - 91.2 ) <= 10. ) 
    return success;
  PassedCut( "ELEL", "ee_weighted", weight );
  PassedCut( "ELEL", "ee_unweight" );

  // Z mass veto
  TLorentzVector Z_mu = HelperFunctions::MakeFourMomentum( ed->muons, 0 ) + HelperFunctions::MakeFourMomentum( ed->muons, 1 );
  if( fabs( Z_mu.M()/GeV - 91.2 ) <= 10. ) 
    return success;
  PassedCut( "MUMU", "mumu_unweight" );

  // jet count
  if( jet_n < 2 ) 
    return success;
  PassedCut( "ELEL", "ee_weighted", weight );
  PassedCut( "ELEL", "ee_unweight" );
  PassedCut( "MUMU", "mumu_unweight" );

  return success;
}


/////////////////////////////////////////
// Plugin

extern "C" {
  CutFlowPluginFactory_TTHTo2LeptonsSS * MakeCutFlowPlugin() {
    return new CutFlowPluginFactory_TTHTo2LeptonsSS( "TTHTo2LeptonsSS" );
  };
}

