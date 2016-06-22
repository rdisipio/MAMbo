//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Tue Nov 10 14:23:14 2015 by ROOT version 6.02/12
// from TTree nominal/tree
// found on file: ljets.output.root
//////////////////////////////////////////////////////////

#ifndef TopXAOD_h
#define TopXAOD_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>


// Header file for the classes stored in the TTree if any.
#include "vector"

using namespace std;

class TopXAOD {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.


// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   vector<float>   *PDFinfo_X1;
   vector<float>   *PDFinfo_X2;
   vector<int>     *PDFinfo_PDGID1;
   vector<int>     *PDFinfo_PDGID2;
   vector<float>   *PDFinfo_Q;
   vector<float>   *PDFinfo_XF1;
   vector<float>   *PDFinfo_XF2;
   Float_t         weight_mc;
   Float_t         weight_pileup;
   Float_t         weight_leptonSF;
   Float_t         weight_bTagSF_85;
   Float_t         weight_bTagSF_77;
   Float_t         weight_bTagSF_70;
   Float_t         weight_jvt;
   Float_t         weight_pileup_UP;
   Float_t         weight_pileup_DOWN;
   Float_t         weight_leptonSF_EL_SF_Trigger_UP;
   Float_t         weight_leptonSF_EL_SF_Trigger_DOWN;
   Float_t         weight_leptonSF_EL_SF_Reco_UP;
   Float_t         weight_leptonSF_EL_SF_Reco_DOWN;
   Float_t         weight_leptonSF_EL_SF_ID_UP;
   Float_t         weight_leptonSF_EL_SF_ID_DOWN;
   Float_t         weight_leptonSF_EL_SF_Isol_UP;
   Float_t         weight_leptonSF_EL_SF_Isol_DOWN;
   Float_t         weight_leptonSF_MU_SF_Trigger_STAT_UP;
   Float_t         weight_leptonSF_MU_SF_Trigger_STAT_DOWN;
   Float_t         weight_leptonSF_MU_SF_Trigger_SYST_UP;
   Float_t         weight_leptonSF_MU_SF_Trigger_SYST_DOWN;
   Float_t         weight_leptonSF_MU_SF_ID_STAT_UP;
   Float_t         weight_leptonSF_MU_SF_ID_STAT_DOWN;
   Float_t         weight_leptonSF_MU_SF_ID_SYST_UP;
   Float_t         weight_leptonSF_MU_SF_ID_SYST_DOWN;
   Float_t         weight_leptonSF_MU_SF_Isol_STAT_UP;
   Float_t         weight_leptonSF_MU_SF_Isol_STAT_DOWN;
   Float_t         weight_leptonSF_MU_SF_Isol_SYST_UP;
   Float_t         weight_leptonSF_MU_SF_Isol_SYST_DOWN;
   Float_t         weight_leptonSF_MU_SF_TTVA_STAT_UP;
   Float_t         weight_leptonSF_MU_SF_TTVA_STAT_DOWN;
   Float_t         weight_leptonSF_MU_SF_TTVA_SYST_UP;
   Float_t         weight_leptonSF_MU_SF_TTVA_SYST_DOWN;
   Float_t         weight_indiv_SF_EL_Trigger;
   Float_t         weight_indiv_SF_EL_Trigger_UP;
   Float_t         weight_indiv_SF_EL_Trigger_DOWN;
   Float_t         weight_indiv_SF_EL_Reco;
   Float_t         weight_indiv_SF_EL_Reco_UP;
   Float_t         weight_indiv_SF_EL_Reco_DOWN;
   Float_t         weight_indiv_SF_EL_ID;
   Float_t         weight_indiv_SF_EL_ID_UP;
   Float_t         weight_indiv_SF_EL_ID_DOWN;
   Float_t         weight_indiv_SF_EL_Isol;
   Float_t         weight_indiv_SF_EL_Isol_UP;
   Float_t         weight_indiv_SF_EL_Isol_DOWN;
   Float_t         weight_indiv_SF_MU_Trigger;
   Float_t         weight_indiv_SF_MU_Trigger_STAT_UP;
   Float_t         weight_indiv_SF_MU_Trigger_STAT_DOWN;
   Float_t         weight_indiv_SF_MU_Trigger_SYST_UP;
   Float_t         weight_indiv_SF_MU_Trigger_SYST_DOWN;
   Float_t         weight_indiv_SF_MU_ID;
   Float_t         weight_indiv_SF_MU_ID_STAT_UP;
   Float_t         weight_indiv_SF_MU_ID_STAT_DOWN;
   Float_t         weight_indiv_SF_MU_ID_SYST_UP;
   Float_t         weight_indiv_SF_MU_ID_SYST_DOWN;
   Float_t         weight_indiv_SF_MU_Isol;
   Float_t         weight_indiv_SF_MU_Isol_STAT_UP;
   Float_t         weight_indiv_SF_MU_Isol_STAT_DOWN;
   Float_t         weight_indiv_SF_MU_Isol_SYST_UP;
   Float_t         weight_indiv_SF_MU_Isol_SYST_DOWN;
   Float_t         weight_indiv_SF_MU_TTVA;
   Float_t         weight_indiv_SF_MU_TTVA_STAT_UP;
   Float_t         weight_indiv_SF_MU_TTVA_STAT_DOWN;
   Float_t         weight_indiv_SF_MU_TTVA_SYST_UP;
   Float_t         weight_indiv_SF_MU_TTVA_SYST_DOWN;
   vector<float>   *weight_bTagSF_85_eigenvars_B_up;
   vector<float>   *weight_bTagSF_85_eigenvars_C_up;
   vector<float>   *weight_bTagSF_85_eigenvars_Light_up;
   vector<float>   *weight_bTagSF_85_eigenvars_B_down;
   vector<float>   *weight_bTagSF_85_eigenvars_C_down;
   vector<float>   *weight_bTagSF_85_eigenvars_Light_down;
   Float_t         weight_bTagSF_85_extrapolation_up;
   Float_t         weight_bTagSF_85_extrapolation_down;
   Float_t         weight_bTagSF_85_extrapolation_from_charm_up;
   Float_t         weight_bTagSF_85_extrapolation_from_charm_down;
   vector<float>   *weight_bTagSF_77_eigenvars_B_up;
   vector<float>   *weight_bTagSF_77_eigenvars_C_up;
   vector<float>   *weight_bTagSF_77_eigenvars_Light_up;
   vector<float>   *weight_bTagSF_77_eigenvars_B_down;
   vector<float>   *weight_bTagSF_77_eigenvars_C_down;
   vector<float>   *weight_bTagSF_77_eigenvars_Light_down;
   Float_t         weight_bTagSF_77_extrapolation_up;
   Float_t         weight_bTagSF_77_extrapolation_down;
   Float_t         weight_bTagSF_77_extrapolation_from_charm_up;
   Float_t         weight_bTagSF_77_extrapolation_from_charm_down;
   vector<float>   *weight_bTagSF_70_eigenvars_B_up;
   vector<float>   *weight_bTagSF_70_eigenvars_C_up;
   vector<float>   *weight_bTagSF_70_eigenvars_Light_up;
   vector<float>   *weight_bTagSF_70_eigenvars_B_down;
   vector<float>   *weight_bTagSF_70_eigenvars_C_down;
   vector<float>   *weight_bTagSF_70_eigenvars_Light_down;
   Float_t         weight_bTagSF_70_extrapolation_up;
   Float_t         weight_bTagSF_70_extrapolation_down;
   Float_t         weight_bTagSF_70_extrapolation_from_charm_up;
   Float_t         weight_bTagSF_70_extrapolation_from_charm_down;
   Float_t         weight_jvt_UP;
   Float_t         weight_jvt_DOWN;
   ULong64_t       eventNumber;
   UInt_t          runNumber;
   UInt_t          mcChannelNumber;
   Float_t         mu;
   
   vector<char>    *el_isTight;
   vector<float>   *el_pt;
   vector<float>   *el_eta;
   vector<float>   *el_cl_eta;
   vector<float>   *el_phi;
   vector<float>   *el_e;
   vector<float>   *el_charge;
   vector<float>   *el_topoetcone20;
   vector<float>   *el_ptvarcone20;
   vector<float>   *el_d0sig;
   vector<float>   *el_delta_z0_sintheta;
   vector<char>   *mu_isTight;
   vector<float>   *mu_pt;
   vector<float>   *mu_eta;
   vector<float>   *mu_phi;
   vector<float>   *mu_e;
   vector<float>   *mu_charge;
   vector<float>   *mu_topoetcone20;
   vector<float>   *mu_ptvarcone30;
   vector<float>   *mu_d0sig;
   vector<float>   *mu_delta_z0_sintheta;
   vector<float>   *jet_pt;
   vector<float>   *jet_eta;
   vector<float>   *jet_phi;
   vector<float>   *jet_e;
   vector<float>   *jet_mv1;
   vector<float>   *jet_mvb;
   vector<float>   *jet_mv1c;
   vector<float>   *jet_mv2c00;
   vector<float>   *jet_mv2c10;
   vector<float>   *jet_mv2c20;
   vector<float>   *jet_ip3dsv1;
   vector<float>   *jet_jvt;
   vector<float>   *ljet_pt;
   vector<float>   *ljet_eta;
   vector<float>   *ljet_phi;
   vector<float>   *ljet_e;
   vector<float>   *ljet_m;
   vector<float>   *ljet_sd12;
   Float_t         met_met;
   Float_t         met_phi;
   Int_t           passed_resolved_ejets_2j0b;
   Int_t           passed_resolved_mujets_2j0b;
   Int_t           passed_resolved_ejets_4j0b;
   Int_t           passed_resolved_ejets_4j1b;
   Int_t           passed_resolved_ejets_4j2b;
   Int_t           passed_resolved_mujets_4j0b;
   Int_t           passed_resolved_mujets_4j1b;
   Int_t           passed_resolved_mujets_4j2b;
   Int_t           passed_boosted_ejets_1fj0b_noMET;
   Int_t           passed_boosted_ejets_1fj0b;
   Int_t           passed_boosted_ejets_1fj1b;
   Int_t           passed_boosted_mujets_1fj0b_noMET;
   Int_t           passed_boosted_mujets_1fj0b;
   Int_t           passed_boosted_mujets_1fj1b;
   Int_t           passed_resolved_ejets_5je2be;
   Int_t           passed_resolved_mujets_5je2be;
   Int_t           passed_resolved_ejets_5je3be;
   Int_t           passed_resolved_mujets_5je3be;
   Int_t           passed_resolved_ejets_5ji2be;
   Int_t           passed_resolved_mujets_5ji2be;
   Int_t           passed_resolved_ejets_5ji3bi;
   Int_t           passed_resolved_mujets_5ji3bi;
   Char_t          HLT_mu20_iloose_L1MU15;
   Char_t          HLT_mu50;
   Char_t          HLT_e60_lhmedium;
   Char_t          HLT_e24_lhmedium_L1EM18VH;
   Char_t          HLT_e120_lhloose;
   vector<char>    *el_trigMatch_HLT_e60_lhmedium;
   vector<char>    *el_trigMatch_HLT_e24_lhmedium_L1EM18VH;
   vector<char>    *el_trigMatch_HLT_e120_lhloose;
   vector<char>    *mu_trigMatch_HLT_mu50;
   vector<char>    *mu_trigMatch_HLT_mu20_iloose_L1MU15;
   UInt_t          lumiblock;
   UInt_t          npv;
   Float_t         vtxz;
   vector<float>   *ljet_tau32;
   vector<float>   *ljet_tau21;
   vector<float>   *ljet_sd23;
   vector<int>     *ljet_topTag50;
   vector<int>     *ljet_topTag80;
   
   Bool_t          is_WplusC;
   Bool_t          is_WplusCC;
   

   // List of branches
   TBranch        *b_PDFinfo_X1;   //!
   TBranch        *b_PDFinfo_X2;   //!
   TBranch        *b_PDFinfo_PDGID1;   //!
   TBranch        *b_PDFinfo_PDGID2;   //!
   TBranch        *b_PDFinfo_Q;   //!
   TBranch        *b_PDFinfo_XF1;   //!
   TBranch        *b_PDFinfo_XF2;   //!
   TBranch        *b_weight_mc;   //!
   TBranch        *b_weight_pileup;   //!
   TBranch        *b_weight_leptonSF;   //!
   TBranch        *b_weight_bTagSF_85;   //!
   TBranch        *b_weight_bTagSF_77;   //!
   TBranch        *b_weight_bTagSF_70;   //!
   TBranch        *b_weight_jvt;   //!
   TBranch        *b_weight_pileup_UP;   //!
   TBranch        *b_weight_pileup_DOWN;   //!
   TBranch        *b_weight_leptonSF_EL_SF_Trigger_UP;   //!
   TBranch        *b_weight_leptonSF_EL_SF_Trigger_DOWN;   //!
   TBranch        *b_weight_leptonSF_EL_SF_Reco_UP;   //!
   TBranch        *b_weight_leptonSF_EL_SF_Reco_DOWN;   //!
   TBranch        *b_weight_leptonSF_EL_SF_ID_UP;   //!
   TBranch        *b_weight_leptonSF_EL_SF_ID_DOWN;   //!
   TBranch        *b_weight_leptonSF_EL_SF_Isol_UP;   //!
   TBranch        *b_weight_leptonSF_EL_SF_Isol_DOWN;   //!
   TBranch        *b_weight_leptonSF_MU_SF_Trigger_STAT_UP;   //!
   TBranch        *b_weight_leptonSF_MU_SF_Trigger_STAT_DOWN;   //!
   TBranch        *b_weight_leptonSF_MU_SF_Trigger_SYST_UP;   //!
   TBranch        *b_weight_leptonSF_MU_SF_Trigger_SYST_DOWN;   //!
   TBranch        *b_weight_leptonSF_MU_SF_ID_STAT_UP;   //!
   TBranch        *b_weight_leptonSF_MU_SF_ID_STAT_DOWN;   //!
   TBranch        *b_weight_leptonSF_MU_SF_ID_SYST_UP;   //!
   TBranch        *b_weight_leptonSF_MU_SF_ID_SYST_DOWN;   //!
   TBranch        *b_weight_leptonSF_MU_SF_Isol_STAT_UP;   //!
   TBranch        *b_weight_leptonSF_MU_SF_Isol_STAT_DOWN;   //!
   TBranch        *b_weight_leptonSF_MU_SF_Isol_SYST_UP;   //!
   TBranch        *b_weight_leptonSF_MU_SF_Isol_SYST_DOWN;   //!
   TBranch        *b_weight_leptonSF_MU_SF_TTVA_STAT_UP;   //!
   TBranch        *b_weight_leptonSF_MU_SF_TTVA_STAT_DOWN;   //!
   TBranch        *b_weight_leptonSF_MU_SF_TTVA_SYST_UP;   //!
   TBranch        *b_weight_leptonSF_MU_SF_TTVA_SYST_DOWN;   //!
   TBranch        *b_weight_indiv_SF_EL_Trigger;   //!
   TBranch        *b_weight_indiv_SF_EL_Trigger_UP;   //!
   TBranch        *b_weight_indiv_SF_EL_Trigger_DOWN;   //!
   TBranch        *b_weight_indiv_SF_EL_Reco;   //!
   TBranch        *b_weight_indiv_SF_EL_Reco_UP;   //!
   TBranch        *b_weight_indiv_SF_EL_Reco_DOWN;   //!
   TBranch        *b_weight_indiv_SF_EL_ID;   //!
   TBranch        *b_weight_indiv_SF_EL_ID_UP;   //!
   TBranch        *b_weight_indiv_SF_EL_ID_DOWN;   //!
   TBranch        *b_weight_indiv_SF_EL_Isol;   //!
   TBranch        *b_weight_indiv_SF_EL_Isol_UP;   //!
   TBranch        *b_weight_indiv_SF_EL_Isol_DOWN;   //!
   TBranch        *b_weight_indiv_SF_MU_Trigger;   //!
   TBranch        *b_weight_indiv_SF_MU_Trigger_STAT_UP;   //!
   TBranch        *b_weight_indiv_SF_MU_Trigger_STAT_DOWN;   //!
   TBranch        *b_weight_indiv_SF_MU_Trigger_SYST_UP;   //!
   TBranch        *b_weight_indiv_SF_MU_Trigger_SYST_DOWN;   //!
   TBranch        *b_weight_indiv_SF_MU_ID;   //!
   TBranch        *b_weight_indiv_SF_MU_ID_STAT_UP;   //!
   TBranch        *b_weight_indiv_SF_MU_ID_STAT_DOWN;   //!
   TBranch        *b_weight_indiv_SF_MU_ID_SYST_UP;   //!
   TBranch        *b_weight_indiv_SF_MU_ID_SYST_DOWN;   //!
   TBranch        *b_weight_indiv_SF_MU_Isol;   //!
   TBranch        *b_weight_indiv_SF_MU_Isol_STAT_UP;   //!
   TBranch        *b_weight_indiv_SF_MU_Isol_STAT_DOWN;   //!
   TBranch        *b_weight_indiv_SF_MU_Isol_SYST_UP;   //!
   TBranch        *b_weight_indiv_SF_MU_Isol_SYST_DOWN;   //!
   TBranch        *b_weight_indiv_SF_MU_TTVA;   //!
   TBranch        *b_weight_indiv_SF_MU_TTVA_STAT_UP;   //!
   TBranch        *b_weight_indiv_SF_MU_TTVA_STAT_DOWN;   //!
   TBranch        *b_weight_indiv_SF_MU_TTVA_SYST_UP;   //!
   TBranch        *b_weight_indiv_SF_MU_TTVA_SYST_DOWN;   //!
   TBranch        *b_weight_bTagSF_85_eigenvars_B_up;   //!
   TBranch        *b_weight_bTagSF_85_eigenvars_C_up;   //!
   TBranch        *b_weight_bTagSF_85_eigenvars_Light_up;   //!
   TBranch        *b_weight_bTagSF_85_eigenvars_B_down;   //!
   TBranch        *b_weight_bTagSF_85_eigenvars_C_down;   //!
   TBranch        *b_weight_bTagSF_85_eigenvars_Light_down;   //!
   TBranch        *b_weight_bTagSF_85_extrapolation_up;   //!
   TBranch        *b_weight_bTagSF_85_extrapolation_down;   //!
   TBranch        *b_weight_bTagSF_85_extrapolation_from_charm_up;   //!
   TBranch        *b_weight_bTagSF_85_extrapolation_from_charm_down;   //!
   TBranch        *b_weight_bTagSF_77_eigenvars_B_up;   //!
   TBranch        *b_weight_bTagSF_77_eigenvars_C_up;   //!
   TBranch        *b_weight_bTagSF_77_eigenvars_Light_up;   //!
   TBranch        *b_weight_bTagSF_77_eigenvars_B_down;   //!
   TBranch        *b_weight_bTagSF_77_eigenvars_C_down;   //!
   TBranch        *b_weight_bTagSF_77_eigenvars_Light_down;   //!
   TBranch        *b_weight_bTagSF_77_extrapolation_up;   //!
   TBranch        *b_weight_bTagSF_77_extrapolation_down;   //!
   TBranch        *b_weight_bTagSF_77_extrapolation_from_charm_up;   //!
   TBranch        *b_weight_bTagSF_77_extrapolation_from_charm_down;   //!
   TBranch        *b_weight_bTagSF_70_eigenvars_B_up;   //!
   TBranch        *b_weight_bTagSF_70_eigenvars_C_up;   //!
   TBranch        *b_weight_bTagSF_70_eigenvars_Light_up;   //!
   TBranch        *b_weight_bTagSF_70_eigenvars_B_down;   //!
   TBranch        *b_weight_bTagSF_70_eigenvars_C_down;   //!
   TBranch        *b_weight_bTagSF_70_eigenvars_Light_down;   //!
   TBranch        *b_weight_bTagSF_70_extrapolation_up;   //!
   TBranch        *b_weight_bTagSF_70_extrapolation_down;   //!
   TBranch        *b_weight_bTagSF_70_extrapolation_from_charm_up;   //!
   TBranch        *b_weight_bTagSF_70_extrapolation_from_charm_down;   //!
   TBranch        *b_weight_jvt_UP;   //!
   TBranch        *b_weight_jvt_DOWN;   //!
   TBranch        *b_eventNumber;   //!
   TBranch        *b_runNumber;   //!
   TBranch        *b_mcChannelNumber;   //!
   TBranch        *b_mu;   //!
   TBranch        *b_el_isTight;   //!   
   TBranch        *b_el_pt;   //!
   TBranch        *b_el_eta;   //!
   TBranch        *b_el_cl_eta;   //!
   TBranch        *b_el_phi;   //!
   TBranch        *b_el_e;   //!
   TBranch        *b_el_charge;   //!
   TBranch        *b_el_topoetcone20;   //!
   TBranch        *b_el_ptvarcone20;   //!
   TBranch        *b_el_d0sig;   //!
   TBranch        *b_el_delta_z0_sintheta;   //!
   TBranch        *b_mu_isTight;   //!
   TBranch        *b_mu_pt;   //!
   TBranch        *b_mu_eta;   //!
   TBranch        *b_mu_phi;   //!
   TBranch        *b_mu_e;   //!
   TBranch        *b_mu_charge;   //!
   TBranch        *b_mu_topoetcone20;   //!
   TBranch        *b_mu_ptvarcone30;   //!
   TBranch        *b_mu_d0sig;   //!
   TBranch        *b_mu_delta_z0_sintheta;   //!
   TBranch        *b_jet_pt;   //!
   TBranch        *b_jet_eta;   //!
   TBranch        *b_jet_phi;   //!
   TBranch        *b_jet_e;   //!
   TBranch        *b_jet_mv1;   //!
   TBranch        *b_jet_mvb;   //!
   TBranch        *b_jet_mv1c;   //!
   TBranch        *b_jet_mv2c00;   //!
   TBranch        *b_jet_mv2c10;   //!
   TBranch        *b_jet_mv2c20;   //!
   TBranch        *b_jet_ip3dsv1;   //!
   TBranch        *b_jet_jvt;   //!
   TBranch        *b_ljet_pt;   //!
   TBranch        *b_ljet_eta;   //!
   TBranch        *b_ljet_phi;   //!
   TBranch        *b_ljet_e;   //!
   TBranch        *b_ljet_m;   //!
   TBranch        *b_ljet_sd12;   //!
   TBranch        *b_met_met;   //!
   TBranch        *b_met_phi;   //!
   TBranch        *b_passed_resolved_ejets_2j0b;   //!
   TBranch        *b_passed_resolved_mujets_2j0b;   //!
   TBranch        *b_passed_resolved_ejets_4j0b;   //!
   TBranch        *b_passed_resolved_ejets_4j1b;   //!
   TBranch        *b_passed_resolved_ejets_4j2b;   //!
   TBranch        *b_passed_resolved_mujets_4j0b;   //!
   TBranch        *b_passed_resolved_mujets_4j1b;   //!
   TBranch        *b_passed_resolved_mujets_4j2b;   //!
   TBranch        *b_passed_boosted_ejets_1fj0b_noMET;   //!
   TBranch        *b_passed_boosted_ejets_1fj0b;   //!
   TBranch        *b_passed_boosted_ejets_1fj1b;   //!
   TBranch        *b_passed_boosted_mujets_1fj0b_noMET;   //!
   TBranch        *b_passed_boosted_mujets_1fj0b;   //!
   TBranch        *b_passed_boosted_mujets_1fj1b;   //!
   TBranch        *b_passed_resolved_ejets_5je2be;   //!
   TBranch        *b_passed_resolved_mujets_5je2be;   //!
   TBranch        *b_passed_resolved_ejets_5je3be;   //!
   TBranch        *b_passed_resolved_mujets_5je3be;   //!
   TBranch        *b_passed_resolved_ejets_5ji2be;   //!
   TBranch        *b_passed_resolved_mujets_5ji2be;   //!
   TBranch        *b_passed_resolved_ejets_5ji3bi;   //!
   TBranch        *b_passed_resolved_mujets_5ji3bi;   //!
   TBranch        *b_HLT_mu20_iloose_L1MU15;   //!
   TBranch        *b_HLT_mu50;   //!
   TBranch        *b_HLT_e60_lhmedium;   //!
   TBranch        *b_HLT_e24_lhmedium_L1EM18VH;   //!
   TBranch        *b_HLT_e120_lhloose;   //!
   TBranch        *b_el_trigMatch_HLT_e60_lhmedium;   //!
   TBranch        *b_el_trigMatch_HLT_e24_lhmedium_L1EM18VH;   //!
   TBranch        *b_el_trigMatch_HLT_e120_lhloose;   //!
   TBranch        *b_mu_trigMatch_HLT_mu50;   //!
   TBranch        *b_mu_trigMatch_HLT_mu20_iloose_L1MU15;   //!
   TBranch        *b_lumiblock;   //!
   TBranch        *b_npv;   //!
   TBranch        *b_vtxz;   //!
   TBranch        *b_ljet_tau32;   //!
   TBranch        *b_ljet_tau21;   //!
   TBranch        *b_ljet_sd23;   //!
   TBranch        *b_ljet_topTag50;   //!
   TBranch        *b_ljet_topTag80;   //!
   
   
   TBranch        *b_is_WplusC;   //!
   TBranch        *b_is_WplusCC;   //!

   TopXAOD(TTree *tree=0);
   virtual ~TopXAOD();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef TopXAOD_cxx
TopXAOD::TopXAOD(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("ljets.output.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("ljets.output.root");
      }
      f->GetObject("nominal",tree);

   }
   Init(tree);
}

TopXAOD::~TopXAOD()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t TopXAOD::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t TopXAOD::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void TopXAOD::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   PDFinfo_X1 = 0;
   PDFinfo_X2 = 0;
   PDFinfo_PDGID1 = 0;
   PDFinfo_PDGID2 = 0;
   PDFinfo_Q = 0;
   PDFinfo_XF1 = 0;
   PDFinfo_XF2 = 0;
   weight_bTagSF_85_eigenvars_B_up = 0;
   weight_bTagSF_85_eigenvars_C_up = 0;
   weight_bTagSF_85_eigenvars_Light_up = 0;
   weight_bTagSF_85_eigenvars_B_down = 0;
   weight_bTagSF_85_eigenvars_C_down = 0;
   weight_bTagSF_85_eigenvars_Light_down = 0;
   weight_bTagSF_77_eigenvars_B_up = 0;
   weight_bTagSF_77_eigenvars_C_up = 0;
   weight_bTagSF_77_eigenvars_Light_up = 0;
   weight_bTagSF_77_eigenvars_B_down = 0;
   weight_bTagSF_77_eigenvars_C_down = 0;
   weight_bTagSF_77_eigenvars_Light_down = 0;
   weight_bTagSF_70_eigenvars_B_up = 0;
   weight_bTagSF_70_eigenvars_C_up = 0;
   weight_bTagSF_70_eigenvars_Light_up = 0;
   weight_bTagSF_70_eigenvars_B_down = 0;
   weight_bTagSF_70_eigenvars_C_down = 0;
   weight_bTagSF_70_eigenvars_Light_down = 0;
   el_isTight = 0;
   el_pt = 0;
   el_eta = 0;
   el_cl_eta = 0;
   el_phi = 0;
   el_e = 0;
   el_charge = 0;
   el_topoetcone20 = 0;
   el_ptvarcone20 = 0;
   el_d0sig = 0;
   el_delta_z0_sintheta = 0;
   mu_isTight = 0;
   mu_pt = 0;
   mu_eta = 0;
   mu_phi = 0;
   mu_e = 0;
   mu_charge = 0;
   mu_topoetcone20 = 0;
   mu_ptvarcone30 = 0;
   mu_d0sig = 0;
   mu_delta_z0_sintheta = 0;
   jet_pt = 0;
   jet_eta = 0;
   jet_phi = 0;
   jet_e = 0;
   jet_mv1 = 0;
   jet_mvb = 0;
   jet_mv1c = 0;
   jet_mv2c00 = 0;
   jet_mv2c10 = 0;
   jet_mv2c20 = 0;
   jet_ip3dsv1 = 0;
   jet_jvt = 0;
   ljet_pt = 0;
   ljet_eta = 0;
   ljet_phi = 0;
   ljet_e = 0;
   ljet_m = 0;
   ljet_sd12 = 0;
   el_trigMatch_HLT_e60_lhmedium = 0;
   el_trigMatch_HLT_e24_lhmedium_L1EM18VH = 0;
   el_trigMatch_HLT_e120_lhloose = 0;
   mu_trigMatch_HLT_mu50 = 0;
   mu_trigMatch_HLT_mu20_iloose_L1MU15 = 0;
   ljet_tau32 = 0;
   ljet_tau21 = 0;
   ljet_sd23 = 0;
   ljet_topTag50 = 0;
   ljet_topTag80 = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("PDFinfo_X1", &PDFinfo_X1, &b_PDFinfo_X1);
   fChain->SetBranchAddress("PDFinfo_X2", &PDFinfo_X2, &b_PDFinfo_X2);
   fChain->SetBranchAddress("PDFinfo_PDGID1", &PDFinfo_PDGID1, &b_PDFinfo_PDGID1);
   fChain->SetBranchAddress("PDFinfo_PDGID2", &PDFinfo_PDGID2, &b_PDFinfo_PDGID2);
   fChain->SetBranchAddress("PDFinfo_Q", &PDFinfo_Q, &b_PDFinfo_Q);
   fChain->SetBranchAddress("PDFinfo_XF1", &PDFinfo_XF1, &b_PDFinfo_XF1);
   fChain->SetBranchAddress("PDFinfo_XF2", &PDFinfo_XF2, &b_PDFinfo_XF2);
   fChain->SetBranchAddress("weight_mc", &weight_mc, &b_weight_mc);
   fChain->SetBranchAddress("weight_pileup", &weight_pileup, &b_weight_pileup);
   fChain->SetBranchAddress("weight_leptonSF", &weight_leptonSF, &b_weight_leptonSF);
   fChain->SetBranchAddress("weight_bTagSF_85", &weight_bTagSF_85, &b_weight_bTagSF_85);
   fChain->SetBranchAddress("weight_bTagSF_77", &weight_bTagSF_77, &b_weight_bTagSF_77);
   fChain->SetBranchAddress("weight_bTagSF_70", &weight_bTagSF_70, &b_weight_bTagSF_70);
   fChain->SetBranchAddress("weight_jvt", &weight_jvt, &b_weight_jvt);
   fChain->SetBranchAddress("weight_pileup_UP", &weight_pileup_UP, &b_weight_pileup_UP);
   fChain->SetBranchAddress("weight_pileup_DOWN", &weight_pileup_DOWN, &b_weight_pileup_DOWN);
   fChain->SetBranchAddress("weight_leptonSF_EL_SF_Trigger_UP", &weight_leptonSF_EL_SF_Trigger_UP, &b_weight_leptonSF_EL_SF_Trigger_UP);
   fChain->SetBranchAddress("weight_leptonSF_EL_SF_Trigger_DOWN", &weight_leptonSF_EL_SF_Trigger_DOWN, &b_weight_leptonSF_EL_SF_Trigger_DOWN);
   fChain->SetBranchAddress("weight_leptonSF_EL_SF_Reco_UP", &weight_leptonSF_EL_SF_Reco_UP, &b_weight_leptonSF_EL_SF_Reco_UP);
   fChain->SetBranchAddress("weight_leptonSF_EL_SF_Reco_DOWN", &weight_leptonSF_EL_SF_Reco_DOWN, &b_weight_leptonSF_EL_SF_Reco_DOWN);
   fChain->SetBranchAddress("weight_leptonSF_EL_SF_ID_UP", &weight_leptonSF_EL_SF_ID_UP, &b_weight_leptonSF_EL_SF_ID_UP);
   fChain->SetBranchAddress("weight_leptonSF_EL_SF_ID_DOWN", &weight_leptonSF_EL_SF_ID_DOWN, &b_weight_leptonSF_EL_SF_ID_DOWN);
   fChain->SetBranchAddress("weight_leptonSF_EL_SF_Isol_UP", &weight_leptonSF_EL_SF_Isol_UP, &b_weight_leptonSF_EL_SF_Isol_UP);
   fChain->SetBranchAddress("weight_leptonSF_EL_SF_Isol_DOWN", &weight_leptonSF_EL_SF_Isol_DOWN, &b_weight_leptonSF_EL_SF_Isol_DOWN);
   fChain->SetBranchAddress("weight_leptonSF_MU_SF_Trigger_STAT_UP", &weight_leptonSF_MU_SF_Trigger_STAT_UP, &b_weight_leptonSF_MU_SF_Trigger_STAT_UP);
   fChain->SetBranchAddress("weight_leptonSF_MU_SF_Trigger_STAT_DOWN", &weight_leptonSF_MU_SF_Trigger_STAT_DOWN, &b_weight_leptonSF_MU_SF_Trigger_STAT_DOWN);
   fChain->SetBranchAddress("weight_leptonSF_MU_SF_Trigger_SYST_UP", &weight_leptonSF_MU_SF_Trigger_SYST_UP, &b_weight_leptonSF_MU_SF_Trigger_SYST_UP);
   fChain->SetBranchAddress("weight_leptonSF_MU_SF_Trigger_SYST_DOWN", &weight_leptonSF_MU_SF_Trigger_SYST_DOWN, &b_weight_leptonSF_MU_SF_Trigger_SYST_DOWN);
   fChain->SetBranchAddress("weight_leptonSF_MU_SF_ID_STAT_UP", &weight_leptonSF_MU_SF_ID_STAT_UP, &b_weight_leptonSF_MU_SF_ID_STAT_UP);
   fChain->SetBranchAddress("weight_leptonSF_MU_SF_ID_STAT_DOWN", &weight_leptonSF_MU_SF_ID_STAT_DOWN, &b_weight_leptonSF_MU_SF_ID_STAT_DOWN);
   fChain->SetBranchAddress("weight_leptonSF_MU_SF_ID_SYST_UP", &weight_leptonSF_MU_SF_ID_SYST_UP, &b_weight_leptonSF_MU_SF_ID_SYST_UP);
   fChain->SetBranchAddress("weight_leptonSF_MU_SF_ID_SYST_DOWN", &weight_leptonSF_MU_SF_ID_SYST_DOWN, &b_weight_leptonSF_MU_SF_ID_SYST_DOWN);
   fChain->SetBranchAddress("weight_leptonSF_MU_SF_Isol_STAT_UP", &weight_leptonSF_MU_SF_Isol_STAT_UP, &b_weight_leptonSF_MU_SF_Isol_STAT_UP);
   fChain->SetBranchAddress("weight_leptonSF_MU_SF_Isol_STAT_DOWN", &weight_leptonSF_MU_SF_Isol_STAT_DOWN, &b_weight_leptonSF_MU_SF_Isol_STAT_DOWN);
   fChain->SetBranchAddress("weight_leptonSF_MU_SF_Isol_SYST_UP", &weight_leptonSF_MU_SF_Isol_SYST_UP, &b_weight_leptonSF_MU_SF_Isol_SYST_UP);
   fChain->SetBranchAddress("weight_leptonSF_MU_SF_Isol_SYST_DOWN", &weight_leptonSF_MU_SF_Isol_SYST_DOWN, &b_weight_leptonSF_MU_SF_Isol_SYST_DOWN);
   fChain->SetBranchAddress("weight_leptonSF_MU_SF_TTVA_STAT_UP", &weight_leptonSF_MU_SF_TTVA_STAT_UP, &b_weight_leptonSF_MU_SF_TTVA_STAT_UP);
   fChain->SetBranchAddress("weight_leptonSF_MU_SF_TTVA_STAT_DOWN", &weight_leptonSF_MU_SF_TTVA_STAT_DOWN, &b_weight_leptonSF_MU_SF_TTVA_STAT_DOWN);
   fChain->SetBranchAddress("weight_leptonSF_MU_SF_TTVA_SYST_UP", &weight_leptonSF_MU_SF_TTVA_SYST_UP, &b_weight_leptonSF_MU_SF_TTVA_SYST_UP);
   fChain->SetBranchAddress("weight_leptonSF_MU_SF_TTVA_SYST_DOWN", &weight_leptonSF_MU_SF_TTVA_SYST_DOWN, &b_weight_leptonSF_MU_SF_TTVA_SYST_DOWN);
   fChain->SetBranchAddress("weight_indiv_SF_EL_Trigger", &weight_indiv_SF_EL_Trigger, &b_weight_indiv_SF_EL_Trigger);
   fChain->SetBranchAddress("weight_indiv_SF_EL_Trigger_UP", &weight_indiv_SF_EL_Trigger_UP, &b_weight_indiv_SF_EL_Trigger_UP);
   fChain->SetBranchAddress("weight_indiv_SF_EL_Trigger_DOWN", &weight_indiv_SF_EL_Trigger_DOWN, &b_weight_indiv_SF_EL_Trigger_DOWN);
   fChain->SetBranchAddress("weight_indiv_SF_EL_Reco", &weight_indiv_SF_EL_Reco, &b_weight_indiv_SF_EL_Reco);
   fChain->SetBranchAddress("weight_indiv_SF_EL_Reco_UP", &weight_indiv_SF_EL_Reco_UP, &b_weight_indiv_SF_EL_Reco_UP);
   fChain->SetBranchAddress("weight_indiv_SF_EL_Reco_DOWN", &weight_indiv_SF_EL_Reco_DOWN, &b_weight_indiv_SF_EL_Reco_DOWN);
   fChain->SetBranchAddress("weight_indiv_SF_EL_ID", &weight_indiv_SF_EL_ID, &b_weight_indiv_SF_EL_ID);
   fChain->SetBranchAddress("weight_indiv_SF_EL_ID_UP", &weight_indiv_SF_EL_ID_UP, &b_weight_indiv_SF_EL_ID_UP);
   fChain->SetBranchAddress("weight_indiv_SF_EL_ID_DOWN", &weight_indiv_SF_EL_ID_DOWN, &b_weight_indiv_SF_EL_ID_DOWN);
   fChain->SetBranchAddress("weight_indiv_SF_EL_Isol", &weight_indiv_SF_EL_Isol, &b_weight_indiv_SF_EL_Isol);
   fChain->SetBranchAddress("weight_indiv_SF_EL_Isol_UP", &weight_indiv_SF_EL_Isol_UP, &b_weight_indiv_SF_EL_Isol_UP);
   fChain->SetBranchAddress("weight_indiv_SF_EL_Isol_DOWN", &weight_indiv_SF_EL_Isol_DOWN, &b_weight_indiv_SF_EL_Isol_DOWN);
   fChain->SetBranchAddress("weight_indiv_SF_MU_Trigger", &weight_indiv_SF_MU_Trigger, &b_weight_indiv_SF_MU_Trigger);
   fChain->SetBranchAddress("weight_indiv_SF_MU_Trigger_STAT_UP", &weight_indiv_SF_MU_Trigger_STAT_UP, &b_weight_indiv_SF_MU_Trigger_STAT_UP);
   fChain->SetBranchAddress("weight_indiv_SF_MU_Trigger_STAT_DOWN", &weight_indiv_SF_MU_Trigger_STAT_DOWN, &b_weight_indiv_SF_MU_Trigger_STAT_DOWN);
   fChain->SetBranchAddress("weight_indiv_SF_MU_Trigger_SYST_UP", &weight_indiv_SF_MU_Trigger_SYST_UP, &b_weight_indiv_SF_MU_Trigger_SYST_UP);
   fChain->SetBranchAddress("weight_indiv_SF_MU_Trigger_SYST_DOWN", &weight_indiv_SF_MU_Trigger_SYST_DOWN, &b_weight_indiv_SF_MU_Trigger_SYST_DOWN);
   fChain->SetBranchAddress("weight_indiv_SF_MU_ID", &weight_indiv_SF_MU_ID, &b_weight_indiv_SF_MU_ID);
   fChain->SetBranchAddress("weight_indiv_SF_MU_ID_STAT_UP", &weight_indiv_SF_MU_ID_STAT_UP, &b_weight_indiv_SF_MU_ID_STAT_UP);
   fChain->SetBranchAddress("weight_indiv_SF_MU_ID_STAT_DOWN", &weight_indiv_SF_MU_ID_STAT_DOWN, &b_weight_indiv_SF_MU_ID_STAT_DOWN);
   fChain->SetBranchAddress("weight_indiv_SF_MU_ID_SYST_UP", &weight_indiv_SF_MU_ID_SYST_UP, &b_weight_indiv_SF_MU_ID_SYST_UP);
   fChain->SetBranchAddress("weight_indiv_SF_MU_ID_SYST_DOWN", &weight_indiv_SF_MU_ID_SYST_DOWN, &b_weight_indiv_SF_MU_ID_SYST_DOWN);
   fChain->SetBranchAddress("weight_indiv_SF_MU_Isol", &weight_indiv_SF_MU_Isol, &b_weight_indiv_SF_MU_Isol);
   fChain->SetBranchAddress("weight_indiv_SF_MU_Isol_STAT_UP", &weight_indiv_SF_MU_Isol_STAT_UP, &b_weight_indiv_SF_MU_Isol_STAT_UP);
   fChain->SetBranchAddress("weight_indiv_SF_MU_Isol_STAT_DOWN", &weight_indiv_SF_MU_Isol_STAT_DOWN, &b_weight_indiv_SF_MU_Isol_STAT_DOWN);
   fChain->SetBranchAddress("weight_indiv_SF_MU_Isol_SYST_UP", &weight_indiv_SF_MU_Isol_SYST_UP, &b_weight_indiv_SF_MU_Isol_SYST_UP);
   fChain->SetBranchAddress("weight_indiv_SF_MU_Isol_SYST_DOWN", &weight_indiv_SF_MU_Isol_SYST_DOWN, &b_weight_indiv_SF_MU_Isol_SYST_DOWN);
   fChain->SetBranchAddress("weight_indiv_SF_MU_TTVA", &weight_indiv_SF_MU_TTVA, &b_weight_indiv_SF_MU_TTVA);
   fChain->SetBranchAddress("weight_indiv_SF_MU_TTVA_STAT_UP", &weight_indiv_SF_MU_TTVA_STAT_UP, &b_weight_indiv_SF_MU_TTVA_STAT_UP);
   fChain->SetBranchAddress("weight_indiv_SF_MU_TTVA_STAT_DOWN", &weight_indiv_SF_MU_TTVA_STAT_DOWN, &b_weight_indiv_SF_MU_TTVA_STAT_DOWN);
   fChain->SetBranchAddress("weight_indiv_SF_MU_TTVA_SYST_UP", &weight_indiv_SF_MU_TTVA_SYST_UP, &b_weight_indiv_SF_MU_TTVA_SYST_UP);
   fChain->SetBranchAddress("weight_indiv_SF_MU_TTVA_SYST_DOWN", &weight_indiv_SF_MU_TTVA_SYST_DOWN, &b_weight_indiv_SF_MU_TTVA_SYST_DOWN);
   fChain->SetBranchAddress("weight_bTagSF_85_eigenvars_B_up", &weight_bTagSF_85_eigenvars_B_up, &b_weight_bTagSF_85_eigenvars_B_up);
   fChain->SetBranchAddress("weight_bTagSF_85_eigenvars_C_up", &weight_bTagSF_85_eigenvars_C_up, &b_weight_bTagSF_85_eigenvars_C_up);
   fChain->SetBranchAddress("weight_bTagSF_85_eigenvars_Light_up", &weight_bTagSF_85_eigenvars_Light_up, &b_weight_bTagSF_85_eigenvars_Light_up);
   fChain->SetBranchAddress("weight_bTagSF_85_eigenvars_B_down", &weight_bTagSF_85_eigenvars_B_down, &b_weight_bTagSF_85_eigenvars_B_down);
   fChain->SetBranchAddress("weight_bTagSF_85_eigenvars_C_down", &weight_bTagSF_85_eigenvars_C_down, &b_weight_bTagSF_85_eigenvars_C_down);
   fChain->SetBranchAddress("weight_bTagSF_85_eigenvars_Light_down", &weight_bTagSF_85_eigenvars_Light_down, &b_weight_bTagSF_85_eigenvars_Light_down);
   fChain->SetBranchAddress("weight_bTagSF_85_extrapolation_up", &weight_bTagSF_85_extrapolation_up, &b_weight_bTagSF_85_extrapolation_up);
   fChain->SetBranchAddress("weight_bTagSF_85_extrapolation_down", &weight_bTagSF_85_extrapolation_down, &b_weight_bTagSF_85_extrapolation_down);
   fChain->SetBranchAddress("weight_bTagSF_85_extrapolation_from_charm_up", &weight_bTagSF_85_extrapolation_from_charm_up, &b_weight_bTagSF_85_extrapolation_from_charm_up);
   fChain->SetBranchAddress("weight_bTagSF_85_extrapolation_from_charm_down", &weight_bTagSF_85_extrapolation_from_charm_down, &b_weight_bTagSF_85_extrapolation_from_charm_down);
   fChain->SetBranchAddress("weight_bTagSF_77_eigenvars_B_up", &weight_bTagSF_77_eigenvars_B_up, &b_weight_bTagSF_77_eigenvars_B_up);
   fChain->SetBranchAddress("weight_bTagSF_77_eigenvars_C_up", &weight_bTagSF_77_eigenvars_C_up, &b_weight_bTagSF_77_eigenvars_C_up);
   fChain->SetBranchAddress("weight_bTagSF_77_eigenvars_Light_up", &weight_bTagSF_77_eigenvars_Light_up, &b_weight_bTagSF_77_eigenvars_Light_up);
   fChain->SetBranchAddress("weight_bTagSF_77_eigenvars_B_down", &weight_bTagSF_77_eigenvars_B_down, &b_weight_bTagSF_77_eigenvars_B_down);
   fChain->SetBranchAddress("weight_bTagSF_77_eigenvars_C_down", &weight_bTagSF_77_eigenvars_C_down, &b_weight_bTagSF_77_eigenvars_C_down);
   fChain->SetBranchAddress("weight_bTagSF_77_eigenvars_Light_down", &weight_bTagSF_77_eigenvars_Light_down, &b_weight_bTagSF_77_eigenvars_Light_down);
   fChain->SetBranchAddress("weight_bTagSF_77_extrapolation_up", &weight_bTagSF_77_extrapolation_up, &b_weight_bTagSF_77_extrapolation_up);
   fChain->SetBranchAddress("weight_bTagSF_77_extrapolation_down", &weight_bTagSF_77_extrapolation_down, &b_weight_bTagSF_77_extrapolation_down);
   fChain->SetBranchAddress("weight_bTagSF_77_extrapolation_from_charm_up", &weight_bTagSF_77_extrapolation_from_charm_up, &b_weight_bTagSF_77_extrapolation_from_charm_up);
   fChain->SetBranchAddress("weight_bTagSF_77_extrapolation_from_charm_down", &weight_bTagSF_77_extrapolation_from_charm_down, &b_weight_bTagSF_77_extrapolation_from_charm_down);
   fChain->SetBranchAddress("weight_bTagSF_70_eigenvars_B_up", &weight_bTagSF_70_eigenvars_B_up, &b_weight_bTagSF_70_eigenvars_B_up);
   fChain->SetBranchAddress("weight_bTagSF_70_eigenvars_C_up", &weight_bTagSF_70_eigenvars_C_up, &b_weight_bTagSF_70_eigenvars_C_up);
   fChain->SetBranchAddress("weight_bTagSF_70_eigenvars_Light_up", &weight_bTagSF_70_eigenvars_Light_up, &b_weight_bTagSF_70_eigenvars_Light_up);
   fChain->SetBranchAddress("weight_bTagSF_70_eigenvars_B_down", &weight_bTagSF_70_eigenvars_B_down, &b_weight_bTagSF_70_eigenvars_B_down);
   fChain->SetBranchAddress("weight_bTagSF_70_eigenvars_C_down", &weight_bTagSF_70_eigenvars_C_down, &b_weight_bTagSF_70_eigenvars_C_down);
   fChain->SetBranchAddress("weight_bTagSF_70_eigenvars_Light_down", &weight_bTagSF_70_eigenvars_Light_down, &b_weight_bTagSF_70_eigenvars_Light_down);
   fChain->SetBranchAddress("weight_bTagSF_70_extrapolation_up", &weight_bTagSF_70_extrapolation_up, &b_weight_bTagSF_70_extrapolation_up);
   fChain->SetBranchAddress("weight_bTagSF_70_extrapolation_down", &weight_bTagSF_70_extrapolation_down, &b_weight_bTagSF_70_extrapolation_down);
   fChain->SetBranchAddress("weight_bTagSF_70_extrapolation_from_charm_up", &weight_bTagSF_70_extrapolation_from_charm_up, &b_weight_bTagSF_70_extrapolation_from_charm_up);
   fChain->SetBranchAddress("weight_bTagSF_70_extrapolation_from_charm_down", &weight_bTagSF_70_extrapolation_from_charm_down, &b_weight_bTagSF_70_extrapolation_from_charm_down);
   fChain->SetBranchAddress("weight_jvt_UP", &weight_jvt_UP, &b_weight_jvt_UP);
   fChain->SetBranchAddress("weight_jvt_DOWN", &weight_jvt_DOWN, &b_weight_jvt_DOWN);
   fChain->SetBranchAddress("eventNumber", &eventNumber, &b_eventNumber);
   fChain->SetBranchAddress("runNumber", &runNumber, &b_runNumber);
   fChain->SetBranchAddress("mcChannelNumber", &mcChannelNumber, &b_mcChannelNumber);
   fChain->SetBranchAddress("mu", &mu, &b_mu);
   fChain->SetBranchAddress("el_isTight", &el_isTight, &b_el_isTight);
   fChain->SetBranchAddress("el_pt", &el_pt, &b_el_pt);
   fChain->SetBranchAddress("el_eta", &el_eta, &b_el_eta);
   fChain->SetBranchAddress("el_cl_eta", &el_cl_eta, &b_el_cl_eta);
   fChain->SetBranchAddress("el_phi", &el_phi, &b_el_phi);
   fChain->SetBranchAddress("el_e", &el_e, &b_el_e);
   fChain->SetBranchAddress("el_charge", &el_charge, &b_el_charge);
   fChain->SetBranchAddress("el_topoetcone20", &el_topoetcone20, &b_el_topoetcone20);
   fChain->SetBranchAddress("el_ptvarcone20", &el_ptvarcone20, &b_el_ptvarcone20);
   fChain->SetBranchAddress("el_d0sig", &el_d0sig, &b_el_d0sig);
   fChain->SetBranchAddress("el_delta_z0_sintheta", &el_delta_z0_sintheta, &b_el_delta_z0_sintheta);
   fChain->SetBranchAddress("mu_isTight", &mu_isTight, &b_mu_isTight);
   fChain->SetBranchAddress("mu_pt", &mu_pt, &b_mu_pt);
   fChain->SetBranchAddress("mu_eta", &mu_eta, &b_mu_eta);
   fChain->SetBranchAddress("mu_phi", &mu_phi, &b_mu_phi);
   fChain->SetBranchAddress("mu_e", &mu_e, &b_mu_e);
   fChain->SetBranchAddress("mu_charge", &mu_charge, &b_mu_charge);
   fChain->SetBranchAddress("mu_topoetcone20", &mu_topoetcone20, &b_mu_topoetcone20);
   fChain->SetBranchAddress("mu_ptvarcone30", &mu_ptvarcone30, &b_mu_ptvarcone30);
   fChain->SetBranchAddress("mu_d0sig", &mu_d0sig, &b_mu_d0sig);
   fChain->SetBranchAddress("mu_delta_z0_sintheta", &mu_delta_z0_sintheta, &b_mu_delta_z0_sintheta);
   fChain->SetBranchAddress("jet_pt", &jet_pt, &b_jet_pt);
   fChain->SetBranchAddress("jet_eta", &jet_eta, &b_jet_eta);
   fChain->SetBranchAddress("jet_phi", &jet_phi, &b_jet_phi);
   fChain->SetBranchAddress("jet_e", &jet_e, &b_jet_e);
   fChain->SetBranchAddress("jet_mv1", &jet_mv1, &b_jet_mv1);
   fChain->SetBranchAddress("jet_mvb", &jet_mvb, &b_jet_mvb);
   fChain->SetBranchAddress("jet_mv1c", &jet_mv1c, &b_jet_mv1c);
   fChain->SetBranchAddress("jet_mv2c00", &jet_mv2c00, &b_jet_mv2c00);
   fChain->SetBranchAddress("jet_mv2c10", &jet_mv2c10, &b_jet_mv2c10);
   fChain->SetBranchAddress("jet_mv2c20", &jet_mv2c20, &b_jet_mv2c20);
   fChain->SetBranchAddress("jet_ip3dsv1", &jet_ip3dsv1, &b_jet_ip3dsv1);
   fChain->SetBranchAddress("jet_jvt", &jet_jvt, &b_jet_jvt);
   fChain->SetBranchAddress("ljet_pt", &ljet_pt, &b_ljet_pt);
   fChain->SetBranchAddress("ljet_eta", &ljet_eta, &b_ljet_eta);
   fChain->SetBranchAddress("ljet_phi", &ljet_phi, &b_ljet_phi);
   fChain->SetBranchAddress("ljet_e", &ljet_e, &b_ljet_e);
   fChain->SetBranchAddress("ljet_m", &ljet_m, &b_ljet_m);
   fChain->SetBranchAddress("ljet_sd12", &ljet_sd12, &b_ljet_sd12);
   fChain->SetBranchAddress("met_met", &met_met, &b_met_met);
   fChain->SetBranchAddress("met_phi", &met_phi, &b_met_phi);
   fChain->SetBranchAddress("passed_resolved_ejets_2j0b", &passed_resolved_ejets_2j0b, &b_passed_resolved_ejets_2j0b);
   fChain->SetBranchAddress("passed_resolved_mujets_2j0b", &passed_resolved_mujets_2j0b, &b_passed_resolved_mujets_2j0b);
   fChain->SetBranchAddress("passed_resolved_ejets_4j0b", &passed_resolved_ejets_4j0b, &b_passed_resolved_ejets_4j0b);
   fChain->SetBranchAddress("passed_resolved_ejets_4j1b", &passed_resolved_ejets_4j1b, &b_passed_resolved_ejets_4j1b);
   fChain->SetBranchAddress("passed_resolved_ejets_4j2b", &passed_resolved_ejets_4j2b, &b_passed_resolved_ejets_4j2b);
   fChain->SetBranchAddress("passed_resolved_mujets_4j0b", &passed_resolved_mujets_4j0b, &b_passed_resolved_mujets_4j0b);
   fChain->SetBranchAddress("passed_resolved_mujets_4j1b", &passed_resolved_mujets_4j1b, &b_passed_resolved_mujets_4j1b);
   fChain->SetBranchAddress("passed_resolved_mujets_4j2b", &passed_resolved_mujets_4j2b, &b_passed_resolved_mujets_4j2b);
   fChain->SetBranchAddress("passed_boosted_ejets_1fj0b_noMET", &passed_boosted_ejets_1fj0b_noMET, &b_passed_boosted_ejets_1fj0b_noMET);
   fChain->SetBranchAddress("passed_boosted_ejets_1fj0b", &passed_boosted_ejets_1fj0b, &b_passed_boosted_ejets_1fj0b);
   fChain->SetBranchAddress("passed_boosted_ejets_1fj1b", &passed_boosted_ejets_1fj1b, &b_passed_boosted_ejets_1fj1b);
   fChain->SetBranchAddress("passed_boosted_mujets_1fj0b_noMET", &passed_boosted_mujets_1fj0b_noMET, &b_passed_boosted_mujets_1fj0b_noMET);
   fChain->SetBranchAddress("passed_boosted_mujets_1fj0b", &passed_boosted_mujets_1fj0b, &b_passed_boosted_mujets_1fj0b);
   fChain->SetBranchAddress("passed_boosted_mujets_1fj1b", &passed_boosted_mujets_1fj1b, &b_passed_boosted_mujets_1fj1b);
   fChain->SetBranchAddress("passed_resolved_ejets_5je2be", &passed_resolved_ejets_5je2be, &b_passed_resolved_ejets_5je2be);
   fChain->SetBranchAddress("passed_resolved_mujets_5je2be", &passed_resolved_mujets_5je2be, &b_passed_resolved_mujets_5je2be);
   fChain->SetBranchAddress("passed_resolved_ejets_5je3be", &passed_resolved_ejets_5je3be, &b_passed_resolved_ejets_5je3be);
   fChain->SetBranchAddress("passed_resolved_mujets_5je3be", &passed_resolved_mujets_5je3be, &b_passed_resolved_mujets_5je3be);
   fChain->SetBranchAddress("passed_resolved_ejets_5ji2be", &passed_resolved_ejets_5ji2be, &b_passed_resolved_ejets_5ji2be);
   fChain->SetBranchAddress("passed_resolved_mujets_5ji2be", &passed_resolved_mujets_5ji2be, &b_passed_resolved_mujets_5ji2be);
   fChain->SetBranchAddress("passed_resolved_ejets_5ji3bi", &passed_resolved_ejets_5ji3bi, &b_passed_resolved_ejets_5ji3bi);
   fChain->SetBranchAddress("passed_resolved_mujets_5ji3bi", &passed_resolved_mujets_5ji3bi, &b_passed_resolved_mujets_5ji3bi);
   fChain->SetBranchAddress("HLT_mu20_iloose_L1MU15", &HLT_mu20_iloose_L1MU15, &b_HLT_mu20_iloose_L1MU15);
   fChain->SetBranchAddress("HLT_mu50", &HLT_mu50, &b_HLT_mu50);
   fChain->SetBranchAddress("HLT_e60_lhmedium", &HLT_e60_lhmedium, &b_HLT_e60_lhmedium);
   fChain->SetBranchAddress("HLT_e24_lhmedium_L1EM18VH", &HLT_e24_lhmedium_L1EM18VH, &b_HLT_e24_lhmedium_L1EM18VH);
   fChain->SetBranchAddress("HLT_e120_lhloose", &HLT_e120_lhloose, &b_HLT_e120_lhloose);
   fChain->SetBranchAddress("el_trigMatch_HLT_e60_lhmedium", &el_trigMatch_HLT_e60_lhmedium, &b_el_trigMatch_HLT_e60_lhmedium);
   fChain->SetBranchAddress("el_trigMatch_HLT_e24_lhmedium_L1EM18VH", &el_trigMatch_HLT_e24_lhmedium_L1EM18VH, &b_el_trigMatch_HLT_e24_lhmedium_L1EM18VH);
   fChain->SetBranchAddress("el_trigMatch_HLT_e120_lhloose", &el_trigMatch_HLT_e120_lhloose, &b_el_trigMatch_HLT_e120_lhloose);
   fChain->SetBranchAddress("mu_trigMatch_HLT_mu50", &mu_trigMatch_HLT_mu50, &b_mu_trigMatch_HLT_mu50);
   fChain->SetBranchAddress("mu_trigMatch_HLT_mu20_iloose_L1MU15", &mu_trigMatch_HLT_mu20_iloose_L1MU15, &b_mu_trigMatch_HLT_mu20_iloose_L1MU15);
   fChain->SetBranchAddress("lumiblock", &lumiblock, &b_lumiblock);
   fChain->SetBranchAddress("npv", &npv, &b_npv);
   fChain->SetBranchAddress("vtxz", &vtxz, &b_vtxz);
   fChain->SetBranchAddress("ljet_tau32", &ljet_tau32, &b_ljet_tau32);
   fChain->SetBranchAddress("ljet_tau21", &ljet_tau21, &b_ljet_tau21);
   fChain->SetBranchAddress("ljet_sd23", &ljet_sd23, &b_ljet_sd23);
   fChain->SetBranchAddress("ljet_topTag50", &ljet_topTag50, &b_ljet_topTag50);
   fChain->SetBranchAddress("ljet_topTag80", &ljet_topTag80, &b_ljet_topTag80);
   fChain->SetBranchAddress("is_WplusC", &is_WplusC, &b_is_WplusC);
   fChain->SetBranchAddress("is_WplusCC", &is_WplusCC, &b_is_WplusCC);
   Notify();
}

Bool_t TopXAOD::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void TopXAOD::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t TopXAOD::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef TopXAOD_cxx
