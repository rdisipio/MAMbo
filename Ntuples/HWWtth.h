//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Tue Oct 15 16:42:31 2013 by ROOT version 5.34/04
// from TTree HWWTree/ttH to leptons Ntuple
// found on file: /gpfs_data/local/atlas/TTHdata/v2_21/MC/FULLSIM/161305.root
//////////////////////////////////////////////////////////

#ifndef HWWtth_h
#define HWWtth_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include <vector>
#include <vector>
#include <vector>
#include <vector>
#include <vector>

using namespace std;

// Fixed size dimensions of array or collections stored in the TTree if any.

class HWWtth {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   Float_t         higgsPt;
   Bool_t          isBlinded;
   Bool_t          hasBtaggedJets;
   Float_t         gammaStar_weight;
   Float_t         m_gammaStar;
   Int_t           RandomRunNumber;
   Double_t        WgStarEventWeight;
   Double_t        WgStarEventWeightError;
   Bool_t          overlapWZ;
   Bool_t          didEJoverlap;
   Bool_t          didMJoverlap;
   Bool_t          didEEoverlap;
   Bool_t          didEMoverlap;
   Float_t         MinDPhi;
   Float_t         MinDPhi_noJVF;
   Float_t         MET;
   Float_t         MET_phi;
   Float_t         METRel;
   Float_t         METRel_noJets;
   Float_t         MET_STVF;
   Float_t         MET_phi_STVF;
   Float_t         METRel_STVF;
   Float_t         METRel_noJets_STVF;
   Float_t         lep_PtID_0;
   Float_t         lep_PtIDuncorr_0;
   Float_t         lep_PtME_0;
   Float_t         lep_PtMEuncorr_0;
   Float_t         lep_ID_0;
   Float_t         lep_Pt_0;
   Float_t         lep_E_0;
   Float_t         lep_Eta_0;
   Float_t         lep_Phi_0;
   Float_t         lep_Etcone20Uncorr_0;
   Float_t         lep_Etcone30Uncorr_0;
   Float_t         lep_Etcone40Uncorr_0;
   Float_t         lep_Etcone20_0;
   Float_t         lep_Etcone30_0;
   Float_t         lep_Etcone40_0;
   Float_t         lep_Ptcone20_0;
   Float_t         lep_Ptcone30_0;
   Float_t         lep_Ptcone40_0;
   Int_t           lep_Nucone20_0;
   Int_t           lep_Nucone30_0;
   Int_t           lep_Nucone40_0;
   Float_t         lep_z0PV_0;
   Float_t         lep_sigd0PV_0;
   Float_t         lep_D0_0;
   Float_t         lep_Z0SinTheta_0;
   Int_t           lep_truth_parent_particle_id0;
   Int_t           lep_truth_particle_id0;
   Char_t          lep_isTightPP_0;
   Char_t          lep_isMediumPP_0;
   Char_t          lep_isLoosePP_0;
   Char_t          lep_isMultiLepton_0;
   Char_t          lep_isVeryTightLH_0;
   Char_t          lep_isTightLH_0;
   Char_t          lep_isMediumLH_0;
   Char_t          lep_isLooseLH_0;
   Char_t          lep_isLooseBLPixLH_0;
   Char_t          lep_isVeryLooseLH_0;
   Char_t          lep_isCombined_0;
   Char_t          lep_isTight_0;
   Char_t          lep_isMedium_0;
   Char_t          lep_isLoose_0;
   Char_t          lep_isHSG3Clear_0;
   Char_t          lep_isHSG3IsoClear_0;
   Char_t          lep_isTrigMatch_0;
   Char_t          lep_isFakable_0;
   Char_t          lep_BLayer_hit_0;
   Char_t          lep_conv_0;
   Int_t           lep_Author_0;
   Int_t           lep_Index_0;
   Double_t        lep_TrigSFEventWeight_0;
   Double_t        lep_TrigSFError_0;
   Double_t        lep_SFRecoEventWeight_0;
   Double_t        lep_SFIdEventWeight_0;
   Double_t        lep_SFIsoEventWeight_0;
   Double_t        lep_SFErrorIso_0;
   Double_t        lep_SFErrorSys_0;
   Double_t        lep_SFRecoError_0;
   Double_t        lep_SFRecoErrorSys_0;
   Double_t        lep_SFIdError_0;
   Double_t        lep_SFIsoError_0;
   Bool_t          lep_Match_EF_mu24i_tight_0;
   Bool_t          lep_Match_EF_mu36_tight_0;
   Bool_t          lep_Match_EF_e24vhi_medium1_0;
   Bool_t          lep_Match_EF_e60_medium1_0;
   Bool_t          lep_Match_EF_mu24_tight_0;
   Bool_t          lep_Match_EF_mu40_MSonly_barrel_tight_0;
   Bool_t          lep_Match_EF_mu18_tight_0;
   Bool_t          lep_Match_EF_mu8_EFFS_0;
   Bool_t          lep_Match_EF_mu13_0;
   Bool_t          lep_Match_EF_e22vh_medium1_0;
   Bool_t          lep_Match_EF_e45_medium1_0;
   Bool_t          lep_Match_EF_e12Tvh_loose1_0;
   Float_t         lep_PtID_1;
   Float_t         lep_PtIDuncorr_1;
   Float_t         lep_PtME_1;
   Float_t         lep_PtMEuncorr_1;
   Float_t         lep_ID_1;
   Float_t         lep_Pt_1;
   Float_t         lep_E_1;
   Float_t         lep_Eta_1;
   Float_t         lep_Phi_1;
   Float_t         lep_Etcone20Uncorr_1;
   Float_t         lep_Etcone30Uncorr_1;
   Float_t         lep_Etcone40Uncorr_1;
   Float_t         lep_Etcone20_1;
   Float_t         lep_Etcone30_1;
   Float_t         lep_Etcone40_1;
   Float_t         lep_Ptcone20_1;
   Float_t         lep_Ptcone30_1;
   Float_t         lep_Ptcone40_1;
   Int_t           lep_Nucone20_1;
   Int_t           lep_Nucone30_1;
   Int_t           lep_Nucone40_1;
   Float_t         lep_z0PV_1;
   Float_t         lep_sigd0PV_1;
   Float_t         lep_D0_1;
   Float_t         lep_Z0SinTheta_1;
   Int_t           lep_truth_parent_particle_id1;
   Int_t           lep_truth_particle_id1;
   Char_t          lep_isTightPP_1;
   Char_t          lep_isMediumPP_1;
   Char_t          lep_isLoosePP_1;
   Char_t          lep_isMultiLepton_1;
   Char_t          lep_isVeryTightLH_1;
   Char_t          lep_isTightLH_1;
   Char_t          lep_isMediumLH_1;
   Char_t          lep_isLooseLH_1;
   Char_t          lep_isLooseBLPixLH_1;
   Char_t          lep_isVeryLooseLH_1;
   Char_t          lep_isCombined_1;
   Char_t          lep_isTight_1;
   Char_t          lep_isMedium_1;
   Char_t          lep_isLoose_1;
   Char_t          lep_isHSG3Clear_1;
   Char_t          lep_isHSG3IsoClear_1;
   Char_t          lep_isTrigMatch_1;
   Char_t          lep_isFakable_1;
   Char_t          lep_BLayer_hit_1;
   Char_t          lep_conv_1;
   Int_t           lep_Author_1;
   Int_t           lep_Index_1;
   Double_t        lep_TrigSFEventWeight_1;
   Double_t        lep_TrigSFError_1;
   Double_t        lep_SFRecoEventWeight_1;
   Double_t        lep_SFIdEventWeight_1;
   Double_t        lep_SFIsoEventWeight_1;
   Double_t        lep_SFErrorIso_1;
   Double_t        lep_SFErrorSys_1;
   Double_t        lep_SFRecoError_1;
   Double_t        lep_SFRecoErrorSys_1;
   Double_t        lep_SFIdError_1;
   Double_t        lep_SFIsoError_1;
   Bool_t          lep_Match_EF_mu24i_tight_1;
   Bool_t          lep_Match_EF_mu36_tight_1;
   Bool_t          lep_Match_EF_e24vhi_medium1_1;
   Bool_t          lep_Match_EF_e60_medium1_1;
   Bool_t          lep_Match_EF_mu24_tight_1;
   Bool_t          lep_Match_EF_mu40_MSonly_barrel_tight_1;
   Bool_t          lep_Match_EF_mu18_tight_1;
   Bool_t          lep_Match_EF_mu8_EFFS_1;
   Bool_t          lep_Match_EF_mu13_1;
   Bool_t          lep_Match_EF_e22vh_medium1_1;
   Bool_t          lep_Match_EF_e45_medium1_1;
   Bool_t          lep_Match_EF_e12Tvh_loose1_1;
   Float_t         lep_PtID_2;
   Float_t         lep_PtIDuncorr_2;
   Float_t         lep_PtME_2;
   Float_t         lep_PtMEuncorr_2;
   Float_t         lep_ID_2;
   Float_t         lep_Pt_2;
   Float_t         lep_E_2;
   Float_t         lep_Eta_2;
   Float_t         lep_Phi_2;
   Float_t         lep_Etcone20Uncorr_2;
   Float_t         lep_Etcone30Uncorr_2;
   Float_t         lep_Etcone40Uncorr_2;
   Float_t         lep_Etcone20_2;
   Float_t         lep_Etcone30_2;
   Float_t         lep_Etcone40_2;
   Float_t         lep_Ptcone20_2;
   Float_t         lep_Ptcone30_2;
   Float_t         lep_Ptcone40_2;
   Int_t           lep_Nucone20_2;
   Int_t           lep_Nucone30_2;
   Int_t           lep_Nucone40_2;
   Float_t         lep_z0PV_2;
   Float_t         lep_sigd0PV_2;
   Float_t         lep_D0_2;
   Float_t         lep_Z0SinTheta_2;
   Int_t           lep_truth_parent_particle_id2;
   Int_t           lep_truth_particle_id2;
   Char_t          lep_isTightPP_2;
   Char_t          lep_isMediumPP_2;
   Char_t          lep_isLoosePP_2;
   Char_t          lep_isMultiLepton_2;
   Char_t          lep_isVeryTightLH_2;
   Char_t          lep_isTightLH_2;
   Char_t          lep_isMediumLH_2;
   Char_t          lep_isLooseLH_2;
   Char_t          lep_isLooseBLPixLH_2;
   Char_t          lep_isVeryLooseLH_2;
   Char_t          lep_isCombined_2;
   Char_t          lep_isTight_2;
   Char_t          lep_isMedium_2;
   Char_t          lep_isLoose_2;
   Char_t          lep_isHSG3Clear_2;
   Char_t          lep_isHSG3IsoClear_2;
   Char_t          lep_isTrigMatch_2;
   Char_t          lep_isFakable_2;
   Char_t          lep_BLayer_hit_2;
   Char_t          lep_conv_2;
   Int_t           lep_Author_2;
   Int_t           lep_Index_2;
   Double_t        lep_TrigSFEventWeight_2;
   Double_t        lep_TrigSFError_2;
   Double_t        lep_SFRecoEventWeight_2;
   Double_t        lep_SFIdEventWeight_2;
   Double_t        lep_SFIsoEventWeight_2;
   Double_t        lep_SFErrorIso_2;
   Double_t        lep_SFErrorSys_2;
   Double_t        lep_SFRecoError_2;
   Double_t        lep_SFRecoErrorSys_2;
   Double_t        lep_SFIdError_2;
   Double_t        lep_SFIsoError_2;
   Bool_t          lep_Match_EF_mu24i_tight_2;
   Bool_t          lep_Match_EF_mu36_tight_2;
   Bool_t          lep_Match_EF_e24vhi_medium1_2;
   Bool_t          lep_Match_EF_e60_medium1_2;
   Bool_t          lep_Match_EF_mu24_tight_2;
   Bool_t          lep_Match_EF_mu40_MSonly_barrel_tight_2;
   Bool_t          lep_Match_EF_mu18_tight_2;
   Bool_t          lep_Match_EF_mu8_EFFS_2;
   Bool_t          lep_Match_EF_mu13_2;
   Bool_t          lep_Match_EF_e22vh_medium1_2;
   Bool_t          lep_Match_EF_e45_medium1_2;
   Bool_t          lep_Match_EF_e12Tvh_loose1_2;
   Float_t         lep_PtID_3;
   Float_t         lep_PtIDuncorr_3;
   Float_t         lep_PtME_3;
   Float_t         lep_PtMEuncorr_3;
   Float_t         lep_ID_3;
   Float_t         lep_Pt_3;
   Float_t         lep_E_3;
   Float_t         lep_Eta_3;
   Float_t         lep_Phi_3;
   Float_t         lep_Etcone20Uncorr_3;
   Float_t         lep_Etcone30Uncorr_3;
   Float_t         lep_Etcone40Uncorr_3;
   Float_t         lep_Etcone20_3;
   Float_t         lep_Etcone30_3;
   Float_t         lep_Etcone40_3;
   Float_t         lep_Ptcone20_3;
   Float_t         lep_Ptcone30_3;
   Float_t         lep_Ptcone40_3;
   Int_t           lep_Nucone20_3;
   Int_t           lep_Nucone30_3;
   Int_t           lep_Nucone40_3;
   Float_t         lep_z0PV_3;
   Float_t         lep_sigd0PV_3;
   Float_t         lep_D0_3;
   Float_t         lep_Z0SinTheta_3;
   Int_t           lep_truth_parent_particle_id3;
   Int_t           lep_truth_particle_id3;
   Char_t          lep_isTightPP_3;
   Char_t          lep_isMediumPP_3;
   Char_t          lep_isLoosePP_3;
   Char_t          lep_isMultiLepton_3;
   Char_t          lep_isVeryTightLH_3;
   Char_t          lep_isTightLH_3;
   Char_t          lep_isMediumLH_3;
   Char_t          lep_isLooseLH_3;
   Char_t          lep_isLooseBLPixLH_3;
   Char_t          lep_isVeryLooseLH_3;
   Char_t          lep_isCombined_3;
   Char_t          lep_isTight_3;
   Char_t          lep_isMedium_3;
   Char_t          lep_isLoose_3;
   Char_t          lep_isHSG3Clear_3;
   Char_t          lep_isHSG3IsoClear_3;
   Char_t          lep_isTrigMatch_3;
   Char_t          lep_isFakable_3;
   Char_t          lep_BLayer_hit_3;
   Char_t          lep_conv_3;
   Int_t           lep_Author_3;
   Int_t           lep_Index_3;
   Double_t        lep_TrigSFEventWeight_3;
   Double_t        lep_TrigSFError_3;
   Double_t        lep_SFRecoEventWeight_3;
   Double_t        lep_SFIdEventWeight_3;
   Double_t        lep_SFIsoEventWeight_3;
   Double_t        lep_SFErrorIso_3;
   Double_t        lep_SFErrorSys_3;
   Double_t        lep_SFRecoError_3;
   Double_t        lep_SFRecoErrorSys_3;
   Double_t        lep_SFIdError_3;
   Double_t        lep_SFIsoError_3;
   Bool_t          lep_Match_EF_mu24i_tight_3;
   Bool_t          lep_Match_EF_mu36_tight_3;
   Bool_t          lep_Match_EF_e24vhi_medium1_3;
   Bool_t          lep_Match_EF_e60_medium1_3;
   Bool_t          lep_Match_EF_mu24_tight_3;
   Bool_t          lep_Match_EF_mu40_MSonly_barrel_tight_3;
   Bool_t          lep_Match_EF_mu18_tight_3;
   Bool_t          lep_Match_EF_mu8_EFFS_3;
   Bool_t          lep_Match_EF_mu13_3;
   Bool_t          lep_Match_EF_e22vh_medium1_3;
   Bool_t          lep_Match_EF_e45_medium1_3;
   Bool_t          lep_Match_EF_e12Tvh_loose1_3;
   Int_t           total_charge;
   Float_t         DRlep0jet;
   Float_t         DRlep1jet;
   Int_t           lep_IndexFake;
   Double_t        vertexEventWeight;
   Double_t        vertexEventWeight_Pu1;
   Double_t        vertexEventWeight_Pu088;
   Double_t        pileupEventWeight;
   Double_t        pileupEventWeight_094;
   Double_t        pileupEventWeight_080;
   Double_t        pileupEventWeight_090;
   Double_t        pileupEventWeight_088;
   Double_t        pileupEventWeight_075;
   Double_t        pileupEventWeight_103;
   Double_t        mcEventWeight;
   Double_t        mcWeightOrg;
   Double_t        trigEventWeight;
   Int_t           nJets_OR_MV1_70;
   Int_t           nJets_OR_MV1_80;
   Int_t           nJets_Pt20_MV1_70;
   Int_t           nJets_Pt20_MV1_80;
   Int_t           nJets_Pt20;
   Int_t           nJets_OR;
   vector<int>     *m_jet_selectStatus;
   Float_t         nJetsProbing_MV1_80;
   Float_t         nJetsProbing_MV1_70;
   Int_t           Nvxp;
   Float_t         jetPt0;
   Float_t         jetPt1;
   Float_t         jetEta0;
   Float_t         jetEta1;
   Float_t         jetE0;
   Float_t         jetE1;
   Float_t         jetY0;
   Float_t         jetY1;
   Float_t         jetM0;
   Float_t         jetM1;
   Float_t         jetPhi0;
   Float_t         jetPhi1;
   Float_t         jetMV10;
   Float_t         jetMV11;
   Float_t         z0Vtx;
   Int_t           bpos;
   Int_t           blen;
   Int_t           bgap;
   Double_t        DYPtllWeight;
   Double_t        DYPtllWeight_CT10;
   Double_t        DYPtllWeight_MRST;
   Int_t           onelep_type;
   Int_t           dilep_type;
   Int_t           trilep_type;
   Int_t           quadlep_type;
   Bool_t          isEEE;
   Bool_t          isEEM;
   Bool_t          isMME;
   Bool_t          isMMM;
   Float_t         Mll01;
   Float_t         Mll02;
   Float_t         Mll12;
   Float_t         Ptll01;
   Float_t         Ptll02;
   Float_t         Ptll12;
   Float_t         DPhill01;
   Float_t         DPhill02;
   Float_t         DPhill12;
   Float_t         DRll01;
   Float_t         DRll02;
   Float_t         DRll12;
   Float_t         DR012;
   Float_t         DR102;
   Float_t         DR201;
   Float_t         DPhi012;
   Float_t         DPhi102;
   Float_t         DPhi201;
   Float_t         DEtall01;
   Float_t         DEtall02;
   Float_t         DEtall12;
   Float_t         Yll01;
   Float_t         Yll02;
   Float_t         Yll12;
   Bool_t          isEEEE;
   Bool_t          isEEEM;
   Bool_t          isEEMM;
   Bool_t          isEMMM;
   Bool_t          isMMMM;
   Float_t         Mll03;
   Float_t         Mll13;
   Float_t         Mll23;
   Float_t         Mlll012;
   Float_t         Mlll013;
   Float_t         Mlll023;
   Float_t         Mlll123;
   Float_t         Mllll;
   Float_t         DPhill03;
   Float_t         DPhill13;
   Float_t         DPhill23;
   Float_t         DPhi013;
   Float_t         DPhi103;
   Float_t         DPhi301;
   Float_t         DPhi023;
   Float_t         DPhi203;
   Float_t         DPhi302;
   Float_t         DPhi123;
   Float_t         DPhi213;
   Float_t         DPhi312;
   Float_t         DRll03;
   Float_t         DRll13;
   Float_t         DRll23;
   Float_t         DR013;
   Float_t         DR103;
   Float_t         DR301;
   Float_t         DR023;
   Float_t         DR203;
   Float_t         DR302;
   Float_t         DR123;
   Float_t         DR213;
   Float_t         DR312;
   Float_t         Ptll03;
   Float_t         Ptll13;
   Float_t         Ptll23;
   Float_t         Yll03;
   Float_t         Yll13;
   Float_t         Yll23;
   Float_t         DEtall03;
   Float_t         DEtall13;
   Float_t         DEtall23;
   Bool_t          passEventCleaning;
   vector<float>   *muon_pt;
   vector<float>   *muon_eta;
   vector<float>   *muon_phi;
   vector<float>   *muon_E;
   vector<float>   *muon_Etcone20;
   vector<float>   *muon_Etcone30;
   vector<float>   *muon_Etcone40;
   vector<float>   *muon_Etcone20Uncorr;
   vector<float>   *muon_Etcone30Uncorr;
   vector<float>   *muon_Etcone40Uncorr;
   vector<float>   *muon_ptcone20;
   vector<float>   *muon_ptcone30;
   vector<float>   *muon_ptcone40;
   vector<float>   *muon_z0PV;
   vector<float>   *muon_sigd0PV;
   vector<float>   *muon_d0;
   vector<float>   *muon_z0SinTheta;
   vector<int>     *muon_author;
   vector<int>     *muon_d3pdindex;
   vector<int>     *muon_truth_parent_particle_id;
   vector<int>     *muon_truth_particle_id;
   vector<float>   *muon_ID;
   vector<int>     *muon_allAuthor;
   vector<float>   *muon_PtID;
   vector<float>   *muon_PtIDuncorr;
   vector<float>   *muon_PtME;
   vector<float>   *muon_matchchi2;
   vector<float>   *muon_PtMEuncorr;
   vector<char>    *muon_isCombined;
   vector<char>    *muon_isTight;
   vector<char>    *muon_isMedium;
   vector<char>    *muon_isLoose;
   vector<bool>    *muon_Match_EF_mu24_tight;
   vector<bool>    *muon_Match_EF_mu40_MSonly_barrel_tight;
   vector<bool>    *muon_Match_EF_mu18_tight;
   vector<bool>    *muon_Match_EF_mu8_EFFS;
   vector<bool>    *muon_Match_EF_mu13;
   vector<bool>    *muon_Match_EF_mu24i_tight;
   vector<bool>    *muon_Match_EF_mu36_tight;
   vector<float>   *electron_pt;
   vector<float>   *electron_eta;
   vector<float>   *electron_phi;
   vector<float>   *electron_E;
   vector<float>   *electron_Etcone20;
   vector<float>   *electron_Etcone30;
   vector<float>   *electron_Etcone40;
   vector<float>   *electron_Etcone20Uncorr;
   vector<float>   *electron_Etcone30Uncorr;
   vector<float>   *electron_Etcone40Uncorr;
   vector<float>   *electron_ptcone20;
   vector<float>   *electron_ptcone30;
   vector<float>   *electron_ptcone40;
   vector<float>   *electron_z0PV;
   vector<float>   *electron_sigd0PV;
   vector<float>   *electron_d0;
   vector<float>   *electron_z0SinTheta;
   vector<int>     *electron_author;
   vector<int>     *electron_d3pdindex;
   vector<int>     *electron_truth_parent_particle_id;
   vector<int>     *electron_truth_particle_id;
   vector<float>   *electron_ID;
   vector<float>   *electron_ClEta;
   vector<char>    *electron_isTightPP;
   vector<char>    *electron_isMediumPP;
   vector<char>    *electron_isLoosePP;
   vector<char>    *electron_isMultiLepton;
   vector<char>    *electron_isVeryTightLH;
   vector<char>    *electron_isTightLH;
   vector<char>    *electron_isMediumLH;
   vector<char>    *electron_isLooseLH;
   vector<char>    *electron_isLooseBLPixLH;
   vector<char>    *electron_isVeryLooseLH;
   vector<char>    *electron_conv;
   vector<char>    *electron_BLayer_hit;
   vector<bool>    *electron_Match_EF_e24vhi_medium1;
   vector<bool>    *electron_Match_EF_e60_medium1;
   vector<bool>    *electron_Match_EF_e22vh_medium1;
   vector<bool>    *electron_Match_EF_e45_medium1;
   vector<bool>    *electron_Match_EF_e12Tvh_loose1;
   UInt_t          m_track_n;
   UInt_t          m_track_nTight;
   vector<float>   *m_track_pt;
   vector<float>   *m_track_eta;
   vector<float>   *m_track_phi;
   vector<float>   *m_track_z0;
   vector<float>   *m_track_d0;
   vector<float>   *m_track_qoverp;
   vector<int>     *m_track_nPixHits;
   vector<int>     *m_track_nSCTHits;
   vector<float>   *m_track_ptcone20;
   vector<float>   *m_track_ptcone30;
   vector<float>   *m_track_ptcone40;
   vector<char>    *m_track_isTight;
   UInt_t          m_truth_n;
   vector<float>   *m_truth_pt;
   vector<float>   *m_truth_m;
   vector<float>   *m_truth_eta;
   vector<float>   *m_truth_phi;
   vector<int>     *m_truth_status;
   vector<int>     *m_truth_pdgId;
   vector<char>    *m_truth_isFamilyChain;
   vector<char>    *m_truth_isFlatChain;
   vector<vector<int> > *m_truth_childIndices;
   vector<vector<int> > *m_truth_parentIndices;
   UInt_t          trueHadronicTau_n;
   vector<int>     *trueHadronicTau_index;
   vector<float>   *trueHadronicTau_visPt;
   vector<float>   *trueHadronicTau_visEta;
   vector<float>   *trueHadronicTau_visPhi;
   UInt_t          RunNumber;
   UInt_t          EventNumber;
   UInt_t          lbn;
   UInt_t          bcid;
   Float_t         actualIntPerXing;
   Float_t         averageIntPerXing;
   UInt_t          mc_channel_number;
   UInt_t          larError;
   Float_t         MET_RefFinal_phi;
   Float_t         MET_RefFinal_et;
   Float_t         MET_RefFinal_sumet;
   Float_t         MET_Cryo_phi;
   Float_t         MET_Cryo_et;
   Float_t         MET_Cryo_sumet;
   Float_t         MET_RefEle_phi;
   Float_t         MET_RefEle_et;
   Float_t         MET_RefEle_sumet;
   Float_t         MET_RefJet_phi;
   Float_t         MET_RefJet_et;
   Float_t         MET_RefJet_sumet;
   Float_t         MET_SoftJets_phi;
   Float_t         MET_SoftJets_et;
   Float_t         MET_SoftJets_sumet;
   Float_t         MET_RefMuon_phi;
   Float_t         MET_RefMuon_et;
   Float_t         MET_RefMuon_sumet;
   Float_t         MET_RefGamma_phi;
   Float_t         MET_RefGamma_et;
   Float_t         MET_RefGamma_sumet;
   Float_t         MET_RefTau_phi;
   Float_t         MET_RefTau_et;
   Float_t         MET_RefTau_sumet;
   Float_t         MET_Track_phi;
   Float_t         MET_Track_et;
   Float_t         MET_Track_sumet;
   Float_t         MET_MuonBoy_phi;
   Float_t         MET_MuonBoy_et;
   Float_t         MET_MuonBoy_sumet;
   Float_t         MET_RefJet_JVF_phi;
   Float_t         MET_RefJet_JVF_et;
   Float_t         MET_RefJet_JVF_sumet;
   Float_t         MET_RefJet_JVFCut_phi;
   Float_t         MET_RefJet_JVFCut_et;
   Float_t         MET_RefJet_JVFCut_sumet;
   Float_t         MET_CellOut_Eflow_STVF_phi;
   Float_t         MET_CellOut_Eflow_STVF_et;
   Float_t         MET_CellOut_Eflow_STVF_sumet;
   Float_t         MET_CellOut_Eflow_JetArea_phi;
   Float_t         MET_CellOut_Eflow_JetArea_et;
   Float_t         MET_CellOut_Eflow_JetArea_sumet;
   Float_t         MET_CellOut_Eflow_JetAreaJVF_phi;
   Float_t         MET_CellOut_Eflow_JetAreaJVF_et;
   Float_t         MET_CellOut_Eflow_JetAreaJVF_sumet;
   Float_t         MET_CellOut_Eflow_JetAreaRhoEta5JVF_phi;
   Float_t         MET_CellOut_Eflow_JetAreaRhoEta5JVF_et;
   Float_t         MET_CellOut_Eflow_JetAreaRhoEta5JVF_sumet;
   Float_t         MET_RefFinal_STVF_phi;
   Float_t         MET_RefFinal_STVF_et;
   Float_t         MET_RefFinal_STVF_sumet;
   Float_t         MET_CellOut_Eflow_phi;
   Float_t         MET_CellOut_Eflow_et;
   Float_t         MET_CellOut_Eflow_sumet;
   Float_t         MET_RefMuon_Track_phi;
   Float_t         MET_RefMuon_Track_et;
   Float_t         MET_RefMuon_Track_sumet;
   Float_t         MET_Topo_phi;
   Float_t         MET_Topo_et;
   Float_t         MET_Topo_sumet;
   Float_t         MET_Truth_NonInt_phi;
   Float_t         MET_Truth_NonInt_et;
   Float_t         MET_Truth_NonInt_sumet;
   Bool_t          EF_2e12Tvh_loose1;
   Bool_t          EF_e12Tvh_medium1_mu8;
   Bool_t          EF_e24vhi_medium1;
   Bool_t          EF_e60_medium1;
   Bool_t          EF_mu18_tight_mu8_EFFS;
   Bool_t          EF_mu24i_tight;
   Bool_t          EF_mu36_tight;
   Bool_t          EF_2mu13;
   Int_t           top_hfor_type;
   Int_t           m_jet_n;
   vector<float>   *m_jet_E;
   vector<float>   *m_jet_pt;
   vector<float>   *m_jet_eta;
   vector<float>   *m_jet_phi;
   vector<float>   *m_jet_sumPtTrk;
   vector<float>   *m_jet_jvtxf;
   vector<float>   *m_jet_flavor_weight_MV1;
   vector<int>     *m_jet_flavor_truth_label;
   vector<float>   *m_jet_nTrk_pv0_500MeV;
   Int_t           m_vxp_n;
   vector<int>     *m_vxp_nTracks;
   Int_t           m_tau_n;
   vector<float>   *m_tau_pt;
   vector<float>   *m_tau_eta;
   vector<float>   *m_tau_phi;
   vector<float>   *m_tau_charge;
   vector<float>   *m_tau_BDTJetScore;
   vector<float>   *m_tau_BDTEleScore;
   vector<int>     *m_tau_muonVeto;
   vector<int>     *m_tau_JetBDTSigLoose;
   vector<int>     *m_tau_JetBDTSigMedium;
   vector<int>     *m_tau_JetBDTSigTight;
   vector<int>     *m_tau_EleBDTLoose;
   vector<int>     *m_tau_EleBDTMedium;
   vector<int>     *m_tau_EleBDTTight;
   vector<int>     *m_tau_author;
   vector<int>     *m_tau_numTrack;
   vector<int>     *m_mcevt_pdf_id1;
   vector<int>     *m_mcevt_pdf_id2;
   vector<double>  *m_mcevt_pdf_x1;
   vector<double>  *m_mcevt_pdf_x2;
   vector<double>  *m_mcevt_pdf_scale;
   Int_t           m_jetTruth_n;
   vector<float>   *m_jetTruth_E;
   vector<float>   *m_jetTruth_pt;
   vector<float>   *m_jetTruth_eta;
   vector<float>   *m_jetTruth_phi;

   // List of branches
   TBranch        *b_higgsPt;   //!
   TBranch        *b_isBlinded;   //!
   TBranch        *b_hasBtaggedJets;   //!
   TBranch        *b_gammaStar_weight;   //!
   TBranch        *b_m_gammaStar;   //!
   TBranch        *b_RandomRunNumber;   //!
   TBranch        *b_WgStarEventWeight;   //!
   TBranch        *b_WgStarEventWeightError;   //!
   TBranch        *b_overlapWZ;   //!
   TBranch        *b_didEJoverlap;   //!
   TBranch        *b_didMJoverlap;   //!
   TBranch        *b_didEEoverlap;   //!
   TBranch        *b_didEMoverlap;   //!
   TBranch        *b_MinDPhi;   //!
   TBranch        *b_MinDPhi_noJVF;   //!
   TBranch        *b_MET;   //!
   TBranch        *b_MET_phi;   //!
   TBranch        *b_METRel;   //!
   TBranch        *b_METRel_noJets;   //!
   TBranch        *b_MET_STVF;   //!
   TBranch        *b_MET_phi_STVF;   //!
   TBranch        *b_METRel_STVF;   //!
   TBranch        *b_METRel_noJets_STVF;   //!
   TBranch        *b_lep_PtID_0;   //!
   TBranch        *b_lep_PtIDuncorr_0;   //!
   TBranch        *b_lep_PtME_0;   //!
   TBranch        *b_lep_PtMEuncorr_0;   //!
   TBranch        *b_lep_ID_0;   //!
   TBranch        *b_lep_Pt_0;   //!
   TBranch        *b_lep_E_0;   //!
   TBranch        *b_lep_Eta_0;   //!
   TBranch        *b_lep_Phi_0;   //!
   TBranch        *b_lep_Etcone20Uncorr_0;   //!
   TBranch        *b_lep_Etcone30Uncorr_0;   //!
   TBranch        *b_lep_Etcone40Uncorr_0;   //!
   TBranch        *b_lep_Etcone20_0;   //!
   TBranch        *b_lep_Etcone30_0;   //!
   TBranch        *b_lep_Etcone40_0;   //!
   TBranch        *b_lep_Ptcone20_0;   //!
   TBranch        *b_lep_Ptcone30_0;   //!
   TBranch        *b_lep_Ptcone40_0;   //!
   TBranch        *b_lep_Nucone20_0;   //!
   TBranch        *b_lep_Nucone30_0;   //!
   TBranch        *b_lep_Nucone40_0;   //!
   TBranch        *b_lep_z0PV_0;   //!
   TBranch        *b_lep_sigd0PV_0;   //!
   TBranch        *b_lep_D0_0;   //!
   TBranch        *b_lep_Z0SinTheta_0;   //!
   TBranch        *b_lep_truth_parent_particle_id0;   //!
   TBranch        *b_lep_truth_particle_id0;   //!
   TBranch        *b_lep_isTightPP_0;   //!
   TBranch        *b_lep_isMediumPP_0;   //!
   TBranch        *b_lep_isLoosePP_0;   //!
   TBranch        *b_lep_isMultiLepton_0;   //!
   TBranch        *b_lep_isVeryTightLH_0;   //!
   TBranch        *b_lep_isTightLH_0;   //!
   TBranch        *b_lep_isMediumLH_0;   //!
   TBranch        *b_lep_isLooseLH_0;   //!
   TBranch        *b_lep_isLooseBLPixLH_0;   //!
   TBranch        *b_lep_isVeryLooseLH_0;   //!
   TBranch        *b_lep_isCombined_0;   //!
   TBranch        *b_lep_isTight_0;   //!
   TBranch        *b_lep_isMedium_0;   //!
   TBranch        *b_lep_isLoose_0;   //!
   TBranch        *b_lep_isHSG3Clear_0;   //!
   TBranch        *b_lep_isHSG3IsoClear_0;   //!
   TBranch        *b_lep_isTrigMatch_0;   //!
   TBranch        *b_lep_isFakable_0;   //!
   TBranch        *b_lep_BLayer_hit_0;   //!
   TBranch        *b_lep_conv_0;   //!
   TBranch        *b_lep_Author_0;   //!
   TBranch        *b_lep_Index_0;   //!
   TBranch        *b_lep_TrigSFEventWeight_0;   //!
   TBranch        *b_lep_TrigSFError_0;   //!
   TBranch        *b_lep_SFRecoEventWeight_0;   //!
   TBranch        *b_lep_SFIdEventWeight_0;   //!
   TBranch        *b_lep_SFIsoEventWeight_0;   //!
   TBranch        *b_lep_SFErrorIso_0;   //!
   TBranch        *b_lep_SFErrorSys_0;   //!
   TBranch        *b_lep_SFRecoError_0;   //!
   TBranch        *b_lep_SFRecoErrorSys_0;   //!
   TBranch        *b_lep_SFIdError_0;   //!
   TBranch        *b_lep_SFIsoError_0;   //!
   TBranch        *b_lep_Match_EF_mu24i_tight_0;   //!
   TBranch        *b_lep_Match_EF_mu36_tight_0;   //!
   TBranch        *b_lep_Match_EF_e24vhi_medium1_0;   //!
   TBranch        *b_lep_Match_EF_e60_medium1_0;   //!
   TBranch        *b_lep_Match_EF_mu24_tight_0;   //!
   TBranch        *b_lep_Match_EF_mu40_MSonly_barrel_tight_0;   //!
   TBranch        *b_lep_Match_EF_mu18_tight_0;   //!
   TBranch        *b_lep_Match_EF_mu8_EFFS_0;   //!
   TBranch        *b_lep_Match_EF_mu13_0;   //!
   TBranch        *b_lep_Match_EF_e22vh_medium1_0;   //!
   TBranch        *b_lep_Match_EF_e45_medium1_0;   //!
   TBranch        *b_lep_Match_EF_e12Tvh_loose1_0;   //!
   TBranch        *b_lep_PtID_1;   //!
   TBranch        *b_lep_PtIDuncorr_1;   //!
   TBranch        *b_lep_PtME_1;   //!
   TBranch        *b_lep_PtMEuncorr_1;   //!
   TBranch        *b_lep_ID_1;   //!
   TBranch        *b_lep_Pt_1;   //!
   TBranch        *b_lep_E_1;   //!
   TBranch        *b_lep_Eta_1;   //!
   TBranch        *b_lep_Phi_1;   //!
   TBranch        *b_lep_Etcone20Uncorr_1;   //!
   TBranch        *b_lep_Etcone30Uncorr_1;   //!
   TBranch        *b_lep_Etcone40Uncorr_1;   //!
   TBranch        *b_lep_Etcone20_1;   //!
   TBranch        *b_lep_Etcone30_1;   //!
   TBranch        *b_lep_Etcone40_1;   //!
   TBranch        *b_lep_Ptcone20_1;   //!
   TBranch        *b_lep_Ptcone30_1;   //!
   TBranch        *b_lep_Ptcone40_1;   //!
   TBranch        *b_lep_Nucone20_1;   //!
   TBranch        *b_lep_Nucone30_1;   //!
   TBranch        *b_lep_Nucone40_1;   //!
   TBranch        *b_lep_z0PV_1;   //!
   TBranch        *b_lep_sigd0PV_1;   //!
   TBranch        *b_lep_D0_1;   //!
   TBranch        *b_lep_Z0SinTheta_1;   //!
   TBranch        *b_lep_truth_parent_particle_id1;   //!
   TBranch        *b_lep_truth_particle_id1;   //!
   TBranch        *b_lep_isTightPP_1;   //!
   TBranch        *b_lep_isMediumPP_1;   //!
   TBranch        *b_lep_isLoosePP_1;   //!
   TBranch        *b_lep_isMultiLepton_1;   //!
   TBranch        *b_lep_isVeryTightLH_1;   //!
   TBranch        *b_lep_isTightLH_1;   //!
   TBranch        *b_lep_isMediumLH_1;   //!
   TBranch        *b_lep_isLooseLH_1;   //!
   TBranch        *b_lep_isLooseBLPixLH_1;   //!
   TBranch        *b_lep_isVeryLooseLH_1;   //!
   TBranch        *b_lep_isCombined_1;   //!
   TBranch        *b_lep_isTight_1;   //!
   TBranch        *b_lep_isMedium_1;   //!
   TBranch        *b_lep_isLoose_1;   //!
   TBranch        *b_lep_isHSG3Clear_1;   //!
   TBranch        *b_lep_isHSG3IsoClear_1;   //!
   TBranch        *b_lep_isTrigMatch_1;   //!
   TBranch        *b_lep_isFakable_1;   //!
   TBranch        *b_lep_BLayer_hit_1;   //!
   TBranch        *b_lep_conv_1;   //!
   TBranch        *b_lep_Author_1;   //!
   TBranch        *b_lep_Index_1;   //!
   TBranch        *b_lep_TrigSFEventWeight_1;   //!
   TBranch        *b_lep_TrigSFError_1;   //!
   TBranch        *b_lep_SFRecoEventWeight_1;   //!
   TBranch        *b_lep_SFIdEventWeight_1;   //!
   TBranch        *b_lep_SFIsoEventWeight_1;   //!
   TBranch        *b_lep_SFErrorIso_1;   //!
   TBranch        *b_lep_SFErrorSys_1;   //!
   TBranch        *b_lep_SFRecoError_1;   //!
   TBranch        *b_lep_SFRecoErrorSys_1;   //!
   TBranch        *b_lep_SFIdError_1;   //!
   TBranch        *b_lep_SFIsoError_1;   //!
   TBranch        *b_lep_Match_EF_mu24i_tight_1;   //!
   TBranch        *b_lep_Match_EF_mu36_tight_1;   //!
   TBranch        *b_lep_Match_EF_e24vhi_medium1_1;   //!
   TBranch        *b_lep_Match_EF_e60_medium1_1;   //!
   TBranch        *b_lep_Match_EF_mu24_tight_1;   //!
   TBranch        *b_lep_Match_EF_mu40_MSonly_barrel_tight_1;   //!
   TBranch        *b_lep_Match_EF_mu18_tight_1;   //!
   TBranch        *b_lep_Match_EF_mu8_EFFS_1;   //!
   TBranch        *b_lep_Match_EF_mu13_1;   //!
   TBranch        *b_lep_Match_EF_e22vh_medium1_1;   //!
   TBranch        *b_lep_Match_EF_e45_medium1_1;   //!
   TBranch        *b_lep_Match_EF_e12Tvh_loose1_1;   //!
   TBranch        *b_lep_PtID_2;   //!
   TBranch        *b_lep_PtIDuncorr_2;   //!
   TBranch        *b_lep_PtME_2;   //!
   TBranch        *b_lep_PtMEuncorr_2;   //!
   TBranch        *b_lep_ID_2;   //!
   TBranch        *b_lep_Pt_2;   //!
   TBranch        *b_lep_E_2;   //!
   TBranch        *b_lep_Eta_2;   //!
   TBranch        *b_lep_Phi_2;   //!
   TBranch        *b_lep_Etcone20Uncorr_2;   //!
   TBranch        *b_lep_Etcone30Uncorr_2;   //!
   TBranch        *b_lep_Etcone40Uncorr_2;   //!
   TBranch        *b_lep_Etcone20_2;   //!
   TBranch        *b_lep_Etcone30_2;   //!
   TBranch        *b_lep_Etcone40_2;   //!
   TBranch        *b_lep_Ptcone20_2;   //!
   TBranch        *b_lep_Ptcone30_2;   //!
   TBranch        *b_lep_Ptcone40_2;   //!
   TBranch        *b_lep_Nucone20_2;   //!
   TBranch        *b_lep_Nucone30_2;   //!
   TBranch        *b_lep_Nucone40_2;   //!
   TBranch        *b_lep_z0PV_2;   //!
   TBranch        *b_lep_sigd0PV_2;   //!
   TBranch        *b_lep_D0_2;   //!
   TBranch        *b_lep_Z0SinTheta_2;   //!
   TBranch        *b_lep_truth_parent_particle_id2;   //!
   TBranch        *b_lep_truth_particle_id2;   //!
   TBranch        *b_lep_isTightPP_2;   //!
   TBranch        *b_lep_isMediumPP_2;   //!
   TBranch        *b_lep_isLoosePP_2;   //!
   TBranch        *b_lep_isMultiLepton_2;   //!
   TBranch        *b_lep_isVeryTightLH_2;   //!
   TBranch        *b_lep_isTightLH_2;   //!
   TBranch        *b_lep_isMediumLH_2;   //!
   TBranch        *b_lep_isLooseLH_2;   //!
   TBranch        *b_lep_isLooseBLPixLH_2;   //!
   TBranch        *b_lep_isVeryLooseLH_2;   //!
   TBranch        *b_lep_isCombined_2;   //!
   TBranch        *b_lep_isTight_2;   //!
   TBranch        *b_lep_isMedium_2;   //!
   TBranch        *b_lep_isLoose_2;   //!
   TBranch        *b_lep_isHSG3Clear_2;   //!
   TBranch        *b_lep_isHSG3IsoClear_2;   //!
   TBranch        *b_lep_isTrigMatch_2;   //!
   TBranch        *b_lep_isFakable_2;   //!
   TBranch        *b_lep_BLayer_hit_2;   //!
   TBranch        *b_lep_conv_2;   //!
   TBranch        *b_lep_Author_2;   //!
   TBranch        *b_lep_Index_2;   //!
   TBranch        *b_lep_TrigSFEventWeight_2;   //!
   TBranch        *b_lep_TrigSFError_2;   //!
   TBranch        *b_lep_SFRecoEventWeight_2;   //!
   TBranch        *b_lep_SFIdEventWeight_2;   //!
   TBranch        *b_lep_SFIsoEventWeight_2;   //!
   TBranch        *b_lep_SFErrorIso_2;   //!
   TBranch        *b_lep_SFErrorSys_2;   //!
   TBranch        *b_lep_SFRecoError_2;   //!
   TBranch        *b_lep_SFRecoErrorSys_2;   //!
   TBranch        *b_lep_SFIdError_2;   //!
   TBranch        *b_lep_SFIsoError_2;   //!
   TBranch        *b_lep_Match_EF_mu24i_tight_2;   //!
   TBranch        *b_lep_Match_EF_mu36_tight_2;   //!
   TBranch        *b_lep_Match_EF_e24vhi_medium1_2;   //!
   TBranch        *b_lep_Match_EF_e60_medium1_2;   //!
   TBranch        *b_lep_Match_EF_mu24_tight_2;   //!
   TBranch        *b_lep_Match_EF_mu40_MSonly_barrel_tight_2;   //!
   TBranch        *b_lep_Match_EF_mu18_tight_2;   //!
   TBranch        *b_lep_Match_EF_mu8_EFFS_2;   //!
   TBranch        *b_lep_Match_EF_mu13_2;   //!
   TBranch        *b_lep_Match_EF_e22vh_medium1_2;   //!
   TBranch        *b_lep_Match_EF_e45_medium1_2;   //!
   TBranch        *b_lep_Match_EF_e12Tvh_loose1_2;   //!
   TBranch        *b_lep_PtID_3;   //!
   TBranch        *b_lep_PtIDuncorr_3;   //!
   TBranch        *b_lep_PtME_3;   //!
   TBranch        *b_lep_PtMEuncorr_3;   //!
   TBranch        *b_lep_ID_3;   //!
   TBranch        *b_lep_Pt_3;   //!
   TBranch        *b_lep_E_3;   //!
   TBranch        *b_lep_Eta_3;   //!
   TBranch        *b_lep_Phi_3;   //!
   TBranch        *b_lep_Etcone20Uncorr_3;   //!
   TBranch        *b_lep_Etcone30Uncorr_3;   //!
   TBranch        *b_lep_Etcone40Uncorr_3;   //!
   TBranch        *b_lep_Etcone20_3;   //!
   TBranch        *b_lep_Etcone30_3;   //!
   TBranch        *b_lep_Etcone40_3;   //!
   TBranch        *b_lep_Ptcone20_3;   //!
   TBranch        *b_lep_Ptcone30_3;   //!
   TBranch        *b_lep_Ptcone40_3;   //!
   TBranch        *b_lep_Nucone20_3;   //!
   TBranch        *b_lep_Nucone30_3;   //!
   TBranch        *b_lep_Nucone40_3;   //!
   TBranch        *b_lep_z0PV_3;   //!
   TBranch        *b_lep_sigd0PV_3;   //!
   TBranch        *b_lep_D0_3;   //!
   TBranch        *b_lep_Z0SinTheta_3;   //!
   TBranch        *b_lep_truth_parent_particle_id3;   //!
   TBranch        *b_lep_truth_particle_id3;   //!
   TBranch        *b_lep_isTightPP_3;   //!
   TBranch        *b_lep_isMediumPP_3;   //!
   TBranch        *b_lep_isLoosePP_3;   //!
   TBranch        *b_lep_isMultiLepton_3;   //!
   TBranch        *b_lep_isVeryTightLH_3;   //!
   TBranch        *b_lep_isTightLH_3;   //!
   TBranch        *b_lep_isMediumLH_3;   //!
   TBranch        *b_lep_isLooseLH_3;   //!
   TBranch        *b_lep_isLooseBLPixLH_3;   //!
   TBranch        *b_lep_isVeryLooseLH_3;   //!
   TBranch        *b_lep_isCombined_3;   //!
   TBranch        *b_lep_isTight_3;   //!
   TBranch        *b_lep_isMedium_3;   //!
   TBranch        *b_lep_isLoose_3;   //!
   TBranch        *b_lep_isHSG3Clear_3;   //!
   TBranch        *b_lep_isHSG3IsoClear_3;   //!
   TBranch        *b_lep_isTrigMatch_3;   //!
   TBranch        *b_lep_isFakable_3;   //!
   TBranch        *b_lep_BLayer_hit_3;   //!
   TBranch        *b_lep_conv_3;   //!
   TBranch        *b_lep_Author_3;   //!
   TBranch        *b_lep_Index_3;   //!
   TBranch        *b_lep_TrigSFEventWeight_3;   //!
   TBranch        *b_lep_TrigSFError_3;   //!
   TBranch        *b_lep_SFRecoEventWeight_3;   //!
   TBranch        *b_lep_SFIdEventWeight_3;   //!
   TBranch        *b_lep_SFIsoEventWeight_3;   //!
   TBranch        *b_lep_SFErrorIso_3;   //!
   TBranch        *b_lep_SFErrorSys_3;   //!
   TBranch        *b_lep_SFRecoError_3;   //!
   TBranch        *b_lep_SFRecoErrorSys_3;   //!
   TBranch        *b_lep_SFIdError_3;   //!
   TBranch        *b_lep_SFIsoError_3;   //!
   TBranch        *b_lep_Match_EF_mu24i_tight_3;   //!
   TBranch        *b_lep_Match_EF_mu36_tight_3;   //!
   TBranch        *b_lep_Match_EF_e24vhi_medium1_3;   //!
   TBranch        *b_lep_Match_EF_e60_medium1_3;   //!
   TBranch        *b_lep_Match_EF_mu24_tight_3;   //!
   TBranch        *b_lep_Match_EF_mu40_MSonly_barrel_tight_3;   //!
   TBranch        *b_lep_Match_EF_mu18_tight_3;   //!
   TBranch        *b_lep_Match_EF_mu8_EFFS_3;   //!
   TBranch        *b_lep_Match_EF_mu13_3;   //!
   TBranch        *b_lep_Match_EF_e22vh_medium1_3;   //!
   TBranch        *b_lep_Match_EF_e45_medium1_3;   //!
   TBranch        *b_lep_Match_EF_e12Tvh_loose1_3;   //!
   TBranch        *b_total_charge;   //!
   TBranch        *b_DRlep0jet;   //!
   TBranch        *b_DRlep1jet;   //!
   TBranch        *b_lep_IndexFake;   //!
   TBranch        *b_vertexEventWeight;   //!
   TBranch        *b_vertexEventWeight_Pu1;   //!
   TBranch        *b_vertexEventWeight_Pu088;   //!
   TBranch        *b_pileupEventWeight;   //!
   TBranch        *b_pileupEventWeight_094;   //!
   TBranch        *b_pileupEventWeight_080;   //!
   TBranch        *b_pileupEventWeight_090;   //!
   TBranch        *b_pileupEventWeight_088;   //!
   TBranch        *b_pileupEventWeight_075;   //!
   TBranch        *b_pileupEventWeight_103;   //!
   TBranch        *b_mcEventWeight;   //!
   TBranch        *b_mcWeightOrg;   //!
   TBranch        *b_trigEventWeight;   //!
   TBranch        *b_nJets_OR_MV1_70;   //!
   TBranch        *b_nJets_OR_MV1_80;   //!
   TBranch        *b_nJets_Pt20_MV1_70;   //!
   TBranch        *b_nJets_Pt20_MV1_80;   //!
   TBranch        *b_nJets_Pt20;   //!
   TBranch        *b_nJets_OR;   //!
   TBranch        *b_m_jet_selectStatus;   //!
   TBranch        *b_nJetsProbing_MV1_80;   //!
   TBranch        *b_nJetsProbing_MV1_70;   //!
   TBranch        *b_Nvxp;   //!
   TBranch        *b_jetPt0;   //!
   TBranch        *b_jetPt1;   //!
   TBranch        *b_jetEta0;   //!
   TBranch        *b_jetEta1;   //!
   TBranch        *b_jetE0;   //!
   TBranch        *b_jetE1;   //!
   TBranch        *b_jetY0;   //!
   TBranch        *b_jetY1;   //!
   TBranch        *b_jetM0;   //!
   TBranch        *b_jetM1;   //!
   TBranch        *b_jetPhi0;   //!
   TBranch        *b_jetPhi1;   //!
   TBranch        *b_jetMV10;   //!
   TBranch        *b_jetMV11;   //!
   TBranch        *b_z0Vtx;   //!
   TBranch        *b_bpos;   //!
   TBranch        *b_blen;   //!
   TBranch        *b_bgap;   //!
   TBranch        *b_DYPtllWeight;   //!
   TBranch        *b_DYPtllWeight_CT10;   //!
   TBranch        *b_DYPtllWeight_MRST;   //!
   TBranch        *b_onelep_type;   //!
   TBranch        *b_dilep_type;   //!
   TBranch        *b_trilep_type;   //!
   TBranch        *b_quadlep_type;   //!
   TBranch        *b_isEEE;   //!
   TBranch        *b_isEEM;   //!
   TBranch        *b_isMME;   //!
   TBranch        *b_isMMM;   //!
   TBranch        *b_Mll01;   //!
   TBranch        *b_Mll02;   //!
   TBranch        *b_Mll12;   //!
   TBranch        *b_Ptll01;   //!
   TBranch        *b_Ptll02;   //!
   TBranch        *b_Ptll12;   //!
   TBranch        *b_DPhill01;   //!
   TBranch        *b_DPhill02;   //!
   TBranch        *b_DPhill12;   //!
   TBranch        *b_DRll01;   //!
   TBranch        *b_DRll02;   //!
   TBranch        *b_DRll12;   //!
   TBranch        *b_DR012;   //!
   TBranch        *b_DR102;   //!
   TBranch        *b_DR201;   //!
   TBranch        *b_DPhi012;   //!
   TBranch        *b_DPhi102;   //!
   TBranch        *b_DPhi201;   //!
   TBranch        *b_DEtall01;   //!
   TBranch        *b_DEtall02;   //!
   TBranch        *b_DEtall12;   //!
   TBranch        *b_Yll01;   //!
   TBranch        *b_Yll02;   //!
   TBranch        *b_Yll12;   //!
   TBranch        *b_isEEEE;   //!
   TBranch        *b_isEEEM;   //!
   TBranch        *b_isEEMM;   //!
   TBranch        *b_isEMMM;   //!
   TBranch        *b_isMMMM;   //!
   TBranch        *b_Mll03;   //!
   TBranch        *b_Mll13;   //!
   TBranch        *b_Mll23;   //!
   TBranch        *b_Mlll012;   //!
   TBranch        *b_Mlll013;   //!
   TBranch        *b_Mlll023;   //!
   TBranch        *b_Mlll123;   //!
   TBranch        *b_Mllll;   //!
   TBranch        *b_DPhill03;   //!
   TBranch        *b_DPhill13;   //!
   TBranch        *b_DPhill23;   //!
   TBranch        *b_DPhi013;   //!
   TBranch        *b_DPhi103;   //!
   TBranch        *b_DPhi301;   //!
   TBranch        *b_DPhi023;   //!
   TBranch        *b_DPhi203;   //!
   TBranch        *b_DPhi302;   //!
   TBranch        *b_DPhi123;   //!
   TBranch        *b_DPhi213;   //!
   TBranch        *b_DPhi312;   //!
   TBranch        *b_DRll03;   //!
   TBranch        *b_DRll13;   //!
   TBranch        *b_DRll23;   //!
   TBranch        *b_DR013;   //!
   TBranch        *b_DR103;   //!
   TBranch        *b_DR301;   //!
   TBranch        *b_DR023;   //!
   TBranch        *b_DR203;   //!
   TBranch        *b_DR302;   //!
   TBranch        *b_DR123;   //!
   TBranch        *b_DR213;   //!
   TBranch        *b_DR312;   //!
   TBranch        *b_Ptll03;   //!
   TBranch        *b_Ptll13;   //!
   TBranch        *b_Ptll23;   //!
   TBranch        *b_Yll03;   //!
   TBranch        *b_Yll13;   //!
   TBranch        *b_Yll23;   //!
   TBranch        *b_DEtall03;   //!
   TBranch        *b_DEtall13;   //!
   TBranch        *b_DEtall23;   //!
   TBranch        *b_passEventCleaning;   //!
   TBranch        *b_muon_pt;   //!
   TBranch        *b_muon_eta;   //!
   TBranch        *b_muon_phi;   //!
   TBranch        *b_muon_E;   //!
   TBranch        *b_muon_Etcone20;   //!
   TBranch        *b_muon_Etcone30;   //!
   TBranch        *b_muon_Etcone40;   //!
   TBranch        *b_muon_Etcone20Uncorr;   //!
   TBranch        *b_muon_Etcone30Uncorr;   //!
   TBranch        *b_muon_Etcone40Uncorr;   //!
   TBranch        *b_muon_ptcone20;   //!
   TBranch        *b_muon_ptcone30;   //!
   TBranch        *b_muon_ptcone40;   //!
   TBranch        *b_muon_z0PV;   //!
   TBranch        *b_muon_sigd0PV;   //!
   TBranch        *b_muon_d0;   //!
   TBranch        *b_muon_z0SinTheta;   //!
   TBranch        *b_muon_author;   //!
   TBranch        *b_muon_d3pdindex;   //!
   TBranch        *b_muon_truth_parent_particle_id;   //!
   TBranch        *b_muon_truth_particle_id;   //!
   TBranch        *b_muon_ID;   //!
   TBranch        *b_muon_allAuthor;   //!
   TBranch        *b_muon_PtID;   //!
   TBranch        *b_muon_PtIDuncorr;   //!
   TBranch        *b_muon_PtME;   //!
   TBranch        *b_muon_matchchi2;   //!
   TBranch        *b_muon_PtMEuncorr;   //!
   TBranch        *b_muon_isCombined;   //!
   TBranch        *b_muon_isTight;   //!
   TBranch        *b_muon_isMedium;   //!
   TBranch        *b_muon_isLoose;   //!
   TBranch        *b_muon_Match_EF_mu24_tight;   //!
   TBranch        *b_muon_Match_EF_mu40_MSonly_barrel_tight;   //!
   TBranch        *b_muon_Match_EF_mu18_tight;   //!
   TBranch        *b_muon_Match_EF_mu8_EFFS;   //!
   TBranch        *b_muon_Match_EF_mu13;   //!
   TBranch        *b_muon_Match_EF_mu24i_tight;   //!
   TBranch        *b_muon_Match_EF_mu36_tight;   //!
   TBranch        *b_electron_pt;   //!
   TBranch        *b_electron_eta;   //!
   TBranch        *b_electron_phi;   //!
   TBranch        *b_electron_E;   //!
   TBranch        *b_electron_Etcone20;   //!
   TBranch        *b_electron_Etcone30;   //!
   TBranch        *b_electron_Etcone40;   //!
   TBranch        *b_electron_Etcone20Uncorr;   //!
   TBranch        *b_electron_Etcone30Uncorr;   //!
   TBranch        *b_electron_Etcone40Uncorr;   //!
   TBranch        *b_electron_ptcone20;   //!
   TBranch        *b_electron_ptcone30;   //!
   TBranch        *b_electron_ptcone40;   //!
   TBranch        *b_electron_z0PV;   //!
   TBranch        *b_electron_sigd0PV;   //!
   TBranch        *b_electron_d0;   //!
   TBranch        *b_electron_z0SinTheta;   //!
   TBranch        *b_electron_author;   //!
   TBranch        *b_electron_d3pdindex;   //!
   TBranch        *b_electron_truth_parent_particle_id;   //!
   TBranch        *b_electron_truth_particle_id;   //!
   TBranch        *b_electron_ID;   //!
   TBranch        *b_electron_ClEta;   //!
   TBranch        *b_electron_isTightPP;   //!
   TBranch        *b_electron_isMediumPP;   //!
   TBranch        *b_electron_isLoosePP;   //!
   TBranch        *b_electron_isMultiLepton;   //!
   TBranch        *b_electron_isVeryTightLH;   //!
   TBranch        *b_electron_isTightLH;   //!
   TBranch        *b_electron_isMediumLH;   //!
   TBranch        *b_electron_isLooseLH;   //!
   TBranch        *b_electron_isLooseBLPixLH;   //!
   TBranch        *b_electron_isVeryLooseLH;   //!
   TBranch        *b_electron_conv;   //!
   TBranch        *b_electron_BLayer_hit;   //!
   TBranch        *b_electron_Match_EF_e24vhi_medium1;   //!
   TBranch        *b_electron_Match_EF_e60_medium1;   //!
   TBranch        *b_electron_Match_EF_e22vh_medium1;   //!
   TBranch        *b_electron_Match_EF_e45_medium1;   //!
   TBranch        *b_electron_Match_EF_e12Tvh_loose1;   //!
   TBranch        *b_m_track_n;   //!
   TBranch        *b_m_track_nTight;   //!
   TBranch        *b_m_track_pt;   //!
   TBranch        *b_m_track_eta;   //!
   TBranch        *b_m_track_phi;   //!
   TBranch        *b_m_track_z0;   //!
   TBranch        *b_m_track_d0;   //!
   TBranch        *b_m_track_qoverp;   //!
   TBranch        *b_m_track_nPixHits;   //!
   TBranch        *b_m_track_nSCTHits;   //!
   TBranch        *b_m_track_ptcone20;   //!
   TBranch        *b_m_track_ptcone30;   //!
   TBranch        *b_m_track_ptcone40;   //!
   TBranch        *b_m_track_isTight;   //!
   TBranch        *b_m_truth_n;   //!
   TBranch        *b_m_truth_pt;   //!
   TBranch        *b_m_truth_m;   //!
   TBranch        *b_m_truth_eta;   //!
   TBranch        *b_m_truth_phi;   //!
   TBranch        *b_m_truth_status;   //!
   TBranch        *b_m_truth_pdgId;   //!
   TBranch        *b_m_truth_isFamilyChain;   //!
   TBranch        *b_m_truth_isFlatChain;   //!
   TBranch        *b_m_truth_childIndices;   //!
   TBranch        *b_m_truth_parentIndices;   //!
   TBranch        *b_trueHadronicTau_n;   //!
   TBranch        *b_trueHadronicTau_index;   //!
   TBranch        *b_trueHadronicTau_visPt;   //!
   TBranch        *b_trueHadronicTau_visEta;   //!
   TBranch        *b_trueHadronicTau_visPhi;   //!
   TBranch        *b_RunNumber;   //!
   TBranch        *b_EventNumber;   //!
   TBranch        *b_lbn;   //!
   TBranch        *b_bcid;   //!
   TBranch        *b_actualIntPerXing;   //!
   TBranch        *b_averageIntPerXing;   //!
   TBranch        *b_mc_channel_number;   //!
   TBranch        *b_larError;   //!
   TBranch        *b_MET_RefFinal_phi;   //!
   TBranch        *b_MET_RefFinal_et;   //!
   TBranch        *b_MET_RefFinal_sumet;   //!
   TBranch        *b_MET_Cryo_phi;   //!
   TBranch        *b_MET_Cryo_et;   //!
   TBranch        *b_MET_Cryo_sumet;   //!
   TBranch        *b_MET_RefEle_phi;   //!
   TBranch        *b_MET_RefEle_et;   //!
   TBranch        *b_MET_RefEle_sumet;   //!
   TBranch        *b_MET_RefJet_phi;   //!
   TBranch        *b_MET_RefJet_et;   //!
   TBranch        *b_MET_RefJet_sumet;   //!
   TBranch        *b_MET_SoftJets_phi;   //!
   TBranch        *b_MET_SoftJets_et;   //!
   TBranch        *b_MET_SoftJets_sumet;   //!
   TBranch        *b_MET_RefMuon_phi;   //!
   TBranch        *b_MET_RefMuon_et;   //!
   TBranch        *b_MET_RefMuon_sumet;   //!
   TBranch        *b_MET_RefGamma_phi;   //!
   TBranch        *b_MET_RefGamma_et;   //!
   TBranch        *b_MET_RefGamma_sumet;   //!
   TBranch        *b_MET_RefTau_phi;   //!
   TBranch        *b_MET_RefTau_et;   //!
   TBranch        *b_MET_RefTau_sumet;   //!
   TBranch        *b_MET_Track_phi;   //!
   TBranch        *b_MET_Track_et;   //!
   TBranch        *b_MET_Track_sumet;   //!
   TBranch        *b_MET_MuonBoy_phi;   //!
   TBranch        *b_MET_MuonBoy_et;   //!
   TBranch        *b_MET_MuonBoy_sumet;   //!
   TBranch        *b_MET_RefJet_JVF_phi;   //!
   TBranch        *b_MET_RefJet_JVF_et;   //!
   TBranch        *b_MET_RefJet_JVF_sumet;   //!
   TBranch        *b_MET_RefJet_JVFCut_phi;   //!
   TBranch        *b_MET_RefJet_JVFCut_et;   //!
   TBranch        *b_MET_RefJet_JVFCut_sumet;   //!
   TBranch        *b_MET_CellOut_Eflow_STVF_phi;   //!
   TBranch        *b_MET_CellOut_Eflow_STVF_et;   //!
   TBranch        *b_MET_CellOut_Eflow_STVF_sumet;   //!
   TBranch        *b_MET_CellOut_Eflow_JetArea_phi;   //!
   TBranch        *b_MET_CellOut_Eflow_JetArea_et;   //!
   TBranch        *b_MET_CellOut_Eflow_JetArea_sumet;   //!
   TBranch        *b_MET_CellOut_Eflow_JetAreaJVF_phi;   //!
   TBranch        *b_MET_CellOut_Eflow_JetAreaJVF_et;   //!
   TBranch        *b_MET_CellOut_Eflow_JetAreaJVF_sumet;   //!
   TBranch        *b_MET_CellOut_Eflow_JetAreaRhoEta5JVF_phi;   //!
   TBranch        *b_MET_CellOut_Eflow_JetAreaRhoEta5JVF_et;   //!
   TBranch        *b_MET_CellOut_Eflow_JetAreaRhoEta5JVF_sumet;   //!
   TBranch        *b_MET_RefFinal_STVF_phi;   //!
   TBranch        *b_MET_RefFinal_STVF_et;   //!
   TBranch        *b_MET_RefFinal_STVF_sumet;   //!
   TBranch        *b_MET_CellOut_Eflow_phi;   //!
   TBranch        *b_MET_CellOut_Eflow_et;   //!
   TBranch        *b_MET_CellOut_Eflow_sumet;   //!
   TBranch        *b_MET_RefMuon_Track_phi;   //!
   TBranch        *b_MET_RefMuon_Track_et;   //!
   TBranch        *b_MET_RefMuon_Track_sumet;   //!
   TBranch        *b_MET_Topo_phi;   //!
   TBranch        *b_MET_Topo_et;   //!
   TBranch        *b_MET_Topo_sumet;   //!
   TBranch        *b_MET_Truth_NonInt_phi;   //!
   TBranch        *b_MET_Truth_NonInt_et;   //!
   TBranch        *b_MET_Truth_NonInt_sumet;   //!
   TBranch        *b_EF_2e12Tvh_loose1;   //!
   TBranch        *b_EF_e12Tvh_medium1_mu8;   //!
   TBranch        *b_EF_e24vhi_medium1;   //!
   TBranch        *b_EF_e60_medium1;   //!
   TBranch        *b_EF_mu18_tight_mu8_EFFS;   //!
   TBranch        *b_EF_mu24i_tight;   //!
   TBranch        *b_EF_mu36_tight;   //!
   TBranch        *b_EF_2mu13;   //!
   TBranch        *b_top_hfor_type;   //!
   TBranch        *b_m_jet_n;   //!
   TBranch        *b_m_jet_E;   //!
   TBranch        *b_m_jet_pt;   //!
   TBranch        *b_m_jet_eta;   //!
   TBranch        *b_m_jet_phi;   //!
   TBranch        *b_m_jet_sumPtTrk;   //!
   TBranch        *b_m_jet_jvtxf;   //!
   TBranch        *b_m_jet_flavor_weight_MV1;   //!
   TBranch        *b_m_jet_flavor_truth_label;   //!
   TBranch        *b_m_jet_nTrk_pv0_500MeV;   //!
   TBranch        *b_m_vxp_n;   //!
   TBranch        *b_m_vxp_nTracks;   //!
   TBranch        *b_m_tau_n;   //!
   TBranch        *b_m_tau_pt;   //!
   TBranch        *b_m_tau_eta;   //!
   TBranch        *b_m_tau_phi;   //!
   TBranch        *b_m_tau_charge;   //!
   TBranch        *b_m_tau_BDTJetScore;   //!
   TBranch        *b_m_tau_BDTEleScore;   //!
   TBranch        *b_m_tau_muonVeto;   //!
   TBranch        *b_m_tau_JetBDTSigLoose;   //!
   TBranch        *b_m_tau_JetBDTSigMedium;   //!
   TBranch        *b_m_tau_JetBDTSigTight;   //!
   TBranch        *b_m_tau_EleBDTLoose;   //!
   TBranch        *b_m_tau_EleBDTMedium;   //!
   TBranch        *b_m_tau_EleBDTTight;   //!
   TBranch        *b_m_tau_author;   //!
   TBranch        *b_m_tau_numTrack;   //!
   TBranch        *b_m_mcevt_pdf_id1;   //!
   TBranch        *b_m_mcevt_pdf_id2;   //!
   TBranch        *b_m_mcevt_pdf_x1;   //!
   TBranch        *b_m_mcevt_pdf_x2;   //!
   TBranch        *b_m_mcevt_pdf_scale;   //!
   TBranch        *b_m_jetTruth_n;   //!
   TBranch        *b_m_jetTruth_E;   //!
   TBranch        *b_m_jetTruth_pt;   //!
   TBranch        *b_m_jetTruth_eta;   //!
   TBranch        *b_m_jetTruth_phi;   //!

   HWWtth(TTree *tree=0);
   virtual ~HWWtth();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef HWWtth_cxx
HWWtth::HWWtth(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("/gpfs_data/local/atlas/TTHdata/v2_21/MC/FULLSIM/161305.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("/gpfs_data/local/atlas/TTHdata/v2_21/MC/FULLSIM/161305.root");
      }
      f->GetObject("HWWTree",tree);

   }
   Init(tree);
}

HWWtth::~HWWtth()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t HWWtth::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t HWWtth::LoadTree(Long64_t entry)
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

void HWWtth::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   m_jet_selectStatus = 0;
   muon_pt = 0;
   muon_eta = 0;
   muon_phi = 0;
   muon_E = 0;
   muon_Etcone20 = 0;
   muon_Etcone30 = 0;
   muon_Etcone40 = 0;
   muon_Etcone20Uncorr = 0;
   muon_Etcone30Uncorr = 0;
   muon_Etcone40Uncorr = 0;
   muon_ptcone20 = 0;
   muon_ptcone30 = 0;
   muon_ptcone40 = 0;
   muon_z0PV = 0;
   muon_sigd0PV = 0;
   muon_d0 = 0;
   muon_z0SinTheta = 0;
   muon_author = 0;
   muon_d3pdindex = 0;
   muon_truth_parent_particle_id = 0;
   muon_truth_particle_id = 0;
   muon_ID = 0;
   muon_allAuthor = 0;
   muon_PtID = 0;
   muon_PtIDuncorr = 0;
   muon_PtME = 0;
   muon_matchchi2 = 0;
   muon_PtMEuncorr = 0;
   muon_isCombined = 0;
   muon_isTight = 0;
   muon_isMedium = 0;
   muon_isLoose = 0;
   muon_Match_EF_mu24_tight = 0;
   muon_Match_EF_mu40_MSonly_barrel_tight = 0;
   muon_Match_EF_mu18_tight = 0;
   muon_Match_EF_mu8_EFFS = 0;
   muon_Match_EF_mu13 = 0;
   muon_Match_EF_mu24i_tight = 0;
   muon_Match_EF_mu36_tight = 0;
   electron_pt = 0;
   electron_eta = 0;
   electron_phi = 0;
   electron_E = 0;
   electron_Etcone20 = 0;
   electron_Etcone30 = 0;
   electron_Etcone40 = 0;
   electron_Etcone20Uncorr = 0;
   electron_Etcone30Uncorr = 0;
   electron_Etcone40Uncorr = 0;
   electron_ptcone20 = 0;
   electron_ptcone30 = 0;
   electron_ptcone40 = 0;
   electron_z0PV = 0;
   electron_sigd0PV = 0;
   electron_d0 = 0;
   electron_z0SinTheta = 0;
   electron_author = 0;
   electron_d3pdindex = 0;
   electron_truth_parent_particle_id = 0;
   electron_truth_particle_id = 0;
   electron_ID = 0;
   electron_ClEta = 0;
   electron_isTightPP = 0;
   electron_isMediumPP = 0;
   electron_isLoosePP = 0;
   electron_isMultiLepton = 0;
   electron_isVeryTightLH = 0;
   electron_isTightLH = 0;
   electron_isMediumLH = 0;
   electron_isLooseLH = 0;
   electron_isLooseBLPixLH = 0;
   electron_isVeryLooseLH = 0;
   electron_conv = 0;
   electron_BLayer_hit = 0;
   electron_Match_EF_e24vhi_medium1 = 0;
   electron_Match_EF_e60_medium1 = 0;
   electron_Match_EF_e22vh_medium1 = 0;
   electron_Match_EF_e45_medium1 = 0;
   electron_Match_EF_e12Tvh_loose1 = 0;
   m_track_pt = 0;
   m_track_eta = 0;
   m_track_phi = 0;
   m_track_z0 = 0;
   m_track_d0 = 0;
   m_track_qoverp = 0;
   m_track_nPixHits = 0;
   m_track_nSCTHits = 0;
   m_track_ptcone20 = 0;
   m_track_ptcone30 = 0;
   m_track_ptcone40 = 0;
   m_track_isTight = 0;
   m_truth_pt = 0;
   m_truth_m = 0;
   m_truth_eta = 0;
   m_truth_phi = 0;
   m_truth_status = 0;
   m_truth_pdgId = 0;
   m_truth_isFamilyChain = 0;
   m_truth_isFlatChain = 0;
   m_truth_childIndices = 0;
   m_truth_parentIndices = 0;
   trueHadronicTau_index = 0;
   trueHadronicTau_visPt = 0;
   trueHadronicTau_visEta = 0;
   trueHadronicTau_visPhi = 0;
   m_jet_E = 0;
   m_jet_pt = 0;
   m_jet_eta = 0;
   m_jet_phi = 0;
   m_jet_sumPtTrk = 0;
   m_jet_jvtxf = 0;
   m_jet_flavor_weight_MV1 = 0;
   m_jet_flavor_truth_label = 0;
   m_jet_nTrk_pv0_500MeV = 0;
   m_vxp_nTracks = 0;
   m_tau_pt = 0;
   m_tau_eta = 0;
   m_tau_phi = 0;
   m_tau_charge = 0;
   m_tau_BDTJetScore = 0;
   m_tau_BDTEleScore = 0;
   m_tau_muonVeto = 0;
   m_tau_JetBDTSigLoose = 0;
   m_tau_JetBDTSigMedium = 0;
   m_tau_JetBDTSigTight = 0;
   m_tau_EleBDTLoose = 0;
   m_tau_EleBDTMedium = 0;
   m_tau_EleBDTTight = 0;
   m_tau_author = 0;
   m_tau_numTrack = 0;
   m_mcevt_pdf_id1 = 0;
   m_mcevt_pdf_id2 = 0;
   m_mcevt_pdf_x1 = 0;
   m_mcevt_pdf_x2 = 0;
   m_mcevt_pdf_scale = 0;
   m_jetTruth_E = 0;
   m_jetTruth_pt = 0;
   m_jetTruth_eta = 0;
   m_jetTruth_phi = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("higgsPt", &higgsPt, &b_higgsPt);
   fChain->SetBranchAddress("isBlinded", &isBlinded, &b_isBlinded);
   fChain->SetBranchAddress("hasBtaggedJets", &hasBtaggedJets, &b_hasBtaggedJets);
   fChain->SetBranchAddress("gammaStar_weight", &gammaStar_weight, &b_gammaStar_weight);
   fChain->SetBranchAddress("m_gammaStar", &m_gammaStar, &b_m_gammaStar);
   fChain->SetBranchAddress("RandomRunNumber", &RandomRunNumber, &b_RandomRunNumber);
   fChain->SetBranchAddress("WgStarEventWeight", &WgStarEventWeight, &b_WgStarEventWeight);
   fChain->SetBranchAddress("WgStarEventWeightError", &WgStarEventWeightError, &b_WgStarEventWeightError);
   fChain->SetBranchAddress("overlapWZ", &overlapWZ, &b_overlapWZ);
   fChain->SetBranchAddress("didEJoverlap", &didEJoverlap, &b_didEJoverlap);
   fChain->SetBranchAddress("didMJoverlap", &didMJoverlap, &b_didMJoverlap);
   fChain->SetBranchAddress("didEEoverlap", &didEEoverlap, &b_didEEoverlap);
   fChain->SetBranchAddress("didEMoverlap", &didEMoverlap, &b_didEMoverlap);
   fChain->SetBranchAddress("MinDPhi", &MinDPhi, &b_MinDPhi);
   fChain->SetBranchAddress("MinDPhi_noJVF", &MinDPhi_noJVF, &b_MinDPhi_noJVF);
   fChain->SetBranchAddress("MET", &MET, &b_MET);
   fChain->SetBranchAddress("MET_phi", &MET_phi, &b_MET_phi);
   fChain->SetBranchAddress("METRel", &METRel, &b_METRel);
   fChain->SetBranchAddress("METRel_noJets", &METRel_noJets, &b_METRel_noJets);
   fChain->SetBranchAddress("MET_STVF", &MET_STVF, &b_MET_STVF);
   fChain->SetBranchAddress("MET_phi_STVF", &MET_phi_STVF, &b_MET_phi_STVF);
   fChain->SetBranchAddress("METRel_STVF", &METRel_STVF, &b_METRel_STVF);
   fChain->SetBranchAddress("METRel_noJets_STVF", &METRel_noJets_STVF, &b_METRel_noJets_STVF);
   fChain->SetBranchAddress("lep_PtID_0", &lep_PtID_0, &b_lep_PtID_0);
   fChain->SetBranchAddress("lep_PtIDuncorr_0", &lep_PtIDuncorr_0, &b_lep_PtIDuncorr_0);
   fChain->SetBranchAddress("lep_PtME_0", &lep_PtME_0, &b_lep_PtME_0);
   fChain->SetBranchAddress("lep_PtMEuncorr_0", &lep_PtMEuncorr_0, &b_lep_PtMEuncorr_0);
   fChain->SetBranchAddress("lep_ID_0", &lep_ID_0, &b_lep_ID_0);
   fChain->SetBranchAddress("lep_Pt_0", &lep_Pt_0, &b_lep_Pt_0);
   fChain->SetBranchAddress("lep_E_0", &lep_E_0, &b_lep_E_0);
   fChain->SetBranchAddress("lep_Eta_0", &lep_Eta_0, &b_lep_Eta_0);
   fChain->SetBranchAddress("lep_Phi_0", &lep_Phi_0, &b_lep_Phi_0);
   fChain->SetBranchAddress("lep_Etcone20Uncorr_0", &lep_Etcone20Uncorr_0, &b_lep_Etcone20Uncorr_0);
   fChain->SetBranchAddress("lep_Etcone30Uncorr_0", &lep_Etcone30Uncorr_0, &b_lep_Etcone30Uncorr_0);
   fChain->SetBranchAddress("lep_Etcone40Uncorr_0", &lep_Etcone40Uncorr_0, &b_lep_Etcone40Uncorr_0);
   fChain->SetBranchAddress("lep_Etcone20_0", &lep_Etcone20_0, &b_lep_Etcone20_0);
   fChain->SetBranchAddress("lep_Etcone30_0", &lep_Etcone30_0, &b_lep_Etcone30_0);
   fChain->SetBranchAddress("lep_Etcone40_0", &lep_Etcone40_0, &b_lep_Etcone40_0);
   fChain->SetBranchAddress("lep_Ptcone20_0", &lep_Ptcone20_0, &b_lep_Ptcone20_0);
   fChain->SetBranchAddress("lep_Ptcone30_0", &lep_Ptcone30_0, &b_lep_Ptcone30_0);
   fChain->SetBranchAddress("lep_Ptcone40_0", &lep_Ptcone40_0, &b_lep_Ptcone40_0);
   fChain->SetBranchAddress("lep_Nucone20_0", &lep_Nucone20_0, &b_lep_Nucone20_0);
   fChain->SetBranchAddress("lep_Nucone30_0", &lep_Nucone30_0, &b_lep_Nucone30_0);
   fChain->SetBranchAddress("lep_Nucone40_0", &lep_Nucone40_0, &b_lep_Nucone40_0);
   fChain->SetBranchAddress("lep_z0PV_0", &lep_z0PV_0, &b_lep_z0PV_0);
   fChain->SetBranchAddress("lep_sigd0PV_0", &lep_sigd0PV_0, &b_lep_sigd0PV_0);
   fChain->SetBranchAddress("lep_D0_0", &lep_D0_0, &b_lep_D0_0);
   fChain->SetBranchAddress("lep_Z0SinTheta_0", &lep_Z0SinTheta_0, &b_lep_Z0SinTheta_0);
   fChain->SetBranchAddress("lep_truth_parent_particle_id0", &lep_truth_parent_particle_id0, &b_lep_truth_parent_particle_id0);
   fChain->SetBranchAddress("lep_truth_particle_id0", &lep_truth_particle_id0, &b_lep_truth_particle_id0);
   fChain->SetBranchAddress("lep_isTightPP_0", &lep_isTightPP_0, &b_lep_isTightPP_0);
   fChain->SetBranchAddress("lep_isMediumPP_0", &lep_isMediumPP_0, &b_lep_isMediumPP_0);
   fChain->SetBranchAddress("lep_isLoosePP_0", &lep_isLoosePP_0, &b_lep_isLoosePP_0);
   fChain->SetBranchAddress("lep_isMultiLepton_0", &lep_isMultiLepton_0, &b_lep_isMultiLepton_0);
   fChain->SetBranchAddress("lep_isVeryTightLH_0", &lep_isVeryTightLH_0, &b_lep_isVeryTightLH_0);
   fChain->SetBranchAddress("lep_isTightLH_0", &lep_isTightLH_0, &b_lep_isTightLH_0);
   fChain->SetBranchAddress("lep_isMediumLH_0", &lep_isMediumLH_0, &b_lep_isMediumLH_0);
   fChain->SetBranchAddress("lep_isLooseLH_0", &lep_isLooseLH_0, &b_lep_isLooseLH_0);
   fChain->SetBranchAddress("lep_isLooseBLPixLH_0", &lep_isLooseBLPixLH_0, &b_lep_isLooseBLPixLH_0);
   fChain->SetBranchAddress("lep_isVeryLooseLH_0", &lep_isVeryLooseLH_0, &b_lep_isVeryLooseLH_0);
   fChain->SetBranchAddress("lep_isCombined_0", &lep_isCombined_0, &b_lep_isCombined_0);
   fChain->SetBranchAddress("lep_isTight_0", &lep_isTight_0, &b_lep_isTight_0);
   fChain->SetBranchAddress("lep_isMedium_0", &lep_isMedium_0, &b_lep_isMedium_0);
   fChain->SetBranchAddress("lep_isLoose_0", &lep_isLoose_0, &b_lep_isLoose_0);
   fChain->SetBranchAddress("lep_isHSG3Clear_0", &lep_isHSG3Clear_0, &b_lep_isHSG3Clear_0);
   fChain->SetBranchAddress("lep_isHSG3IsoClear_0", &lep_isHSG3IsoClear_0, &b_lep_isHSG3IsoClear_0);
   fChain->SetBranchAddress("lep_isTrigMatch_0", &lep_isTrigMatch_0, &b_lep_isTrigMatch_0);
   fChain->SetBranchAddress("lep_isFakable_0", &lep_isFakable_0, &b_lep_isFakable_0);
   fChain->SetBranchAddress("lep_BLayer_hit_0", &lep_BLayer_hit_0, &b_lep_BLayer_hit_0);
   fChain->SetBranchAddress("lep_conv_0", &lep_conv_0, &b_lep_conv_0);
   fChain->SetBranchAddress("lep_Author_0", &lep_Author_0, &b_lep_Author_0);
   fChain->SetBranchAddress("lep_Index_0", &lep_Index_0, &b_lep_Index_0);
   fChain->SetBranchAddress("lep_TrigSFEventWeight_0", &lep_TrigSFEventWeight_0, &b_lep_TrigSFEventWeight_0);
   fChain->SetBranchAddress("lep_TrigSFError_0", &lep_TrigSFError_0, &b_lep_TrigSFError_0);
   fChain->SetBranchAddress("lep_SFRecoEventWeight_0", &lep_SFRecoEventWeight_0, &b_lep_SFRecoEventWeight_0);
   fChain->SetBranchAddress("lep_SFIdEventWeight_0", &lep_SFIdEventWeight_0, &b_lep_SFIdEventWeight_0);
   fChain->SetBranchAddress("lep_SFIsoEventWeight_0", &lep_SFIsoEventWeight_0, &b_lep_SFIsoEventWeight_0);
   fChain->SetBranchAddress("lep_SFErrorIso_0", &lep_SFErrorIso_0, &b_lep_SFErrorIso_0);
   fChain->SetBranchAddress("lep_SFErrorSys_0", &lep_SFErrorSys_0, &b_lep_SFErrorSys_0);
   fChain->SetBranchAddress("lep_SFRecoError_0", &lep_SFRecoError_0, &b_lep_SFRecoError_0);
   fChain->SetBranchAddress("lep_SFRecoErrorSys_0", &lep_SFRecoErrorSys_0, &b_lep_SFRecoErrorSys_0);
   fChain->SetBranchAddress("lep_SFIdError_0", &lep_SFIdError_0, &b_lep_SFIdError_0);
   fChain->SetBranchAddress("lep_SFIsoError_0", &lep_SFIsoError_0, &b_lep_SFIsoError_0);
   fChain->SetBranchAddress("lep_Match_EF_mu24i_tight_0", &lep_Match_EF_mu24i_tight_0, &b_lep_Match_EF_mu24i_tight_0);
   fChain->SetBranchAddress("lep_Match_EF_mu36_tight_0", &lep_Match_EF_mu36_tight_0, &b_lep_Match_EF_mu36_tight_0);
   fChain->SetBranchAddress("lep_Match_EF_e24vhi_medium1_0", &lep_Match_EF_e24vhi_medium1_0, &b_lep_Match_EF_e24vhi_medium1_0);
   fChain->SetBranchAddress("lep_Match_EF_e60_medium1_0", &lep_Match_EF_e60_medium1_0, &b_lep_Match_EF_e60_medium1_0);
   fChain->SetBranchAddress("lep_Match_EF_mu24_tight_0", &lep_Match_EF_mu24_tight_0, &b_lep_Match_EF_mu24_tight_0);
   fChain->SetBranchAddress("lep_Match_EF_mu40_MSonly_barrel_tight_0", &lep_Match_EF_mu40_MSonly_barrel_tight_0, &b_lep_Match_EF_mu40_MSonly_barrel_tight_0);
   fChain->SetBranchAddress("lep_Match_EF_mu18_tight_0", &lep_Match_EF_mu18_tight_0, &b_lep_Match_EF_mu18_tight_0);
   fChain->SetBranchAddress("lep_Match_EF_mu8_EFFS_0", &lep_Match_EF_mu8_EFFS_0, &b_lep_Match_EF_mu8_EFFS_0);
   fChain->SetBranchAddress("lep_Match_EF_mu13_0", &lep_Match_EF_mu13_0, &b_lep_Match_EF_mu13_0);
   fChain->SetBranchAddress("lep_Match_EF_e22vh_medium1_0", &lep_Match_EF_e22vh_medium1_0, &b_lep_Match_EF_e22vh_medium1_0);
   fChain->SetBranchAddress("lep_Match_EF_e45_medium1_0", &lep_Match_EF_e45_medium1_0, &b_lep_Match_EF_e45_medium1_0);
   fChain->SetBranchAddress("lep_Match_EF_e12Tvh_loose1_0", &lep_Match_EF_e12Tvh_loose1_0, &b_lep_Match_EF_e12Tvh_loose1_0);
   fChain->SetBranchAddress("lep_PtID_1", &lep_PtID_1, &b_lep_PtID_1);
   fChain->SetBranchAddress("lep_PtIDuncorr_1", &lep_PtIDuncorr_1, &b_lep_PtIDuncorr_1);
   fChain->SetBranchAddress("lep_PtME_1", &lep_PtME_1, &b_lep_PtME_1);
   fChain->SetBranchAddress("lep_PtMEuncorr_1", &lep_PtMEuncorr_1, &b_lep_PtMEuncorr_1);
   fChain->SetBranchAddress("lep_ID_1", &lep_ID_1, &b_lep_ID_1);
   fChain->SetBranchAddress("lep_Pt_1", &lep_Pt_1, &b_lep_Pt_1);
   fChain->SetBranchAddress("lep_E_1", &lep_E_1, &b_lep_E_1);
   fChain->SetBranchAddress("lep_Eta_1", &lep_Eta_1, &b_lep_Eta_1);
   fChain->SetBranchAddress("lep_Phi_1", &lep_Phi_1, &b_lep_Phi_1);
   fChain->SetBranchAddress("lep_Etcone20Uncorr_1", &lep_Etcone20Uncorr_1, &b_lep_Etcone20Uncorr_1);
   fChain->SetBranchAddress("lep_Etcone30Uncorr_1", &lep_Etcone30Uncorr_1, &b_lep_Etcone30Uncorr_1);
   fChain->SetBranchAddress("lep_Etcone40Uncorr_1", &lep_Etcone40Uncorr_1, &b_lep_Etcone40Uncorr_1);
   fChain->SetBranchAddress("lep_Etcone20_1", &lep_Etcone20_1, &b_lep_Etcone20_1);
   fChain->SetBranchAddress("lep_Etcone30_1", &lep_Etcone30_1, &b_lep_Etcone30_1);
   fChain->SetBranchAddress("lep_Etcone40_1", &lep_Etcone40_1, &b_lep_Etcone40_1);
   fChain->SetBranchAddress("lep_Ptcone20_1", &lep_Ptcone20_1, &b_lep_Ptcone20_1);
   fChain->SetBranchAddress("lep_Ptcone30_1", &lep_Ptcone30_1, &b_lep_Ptcone30_1);
   fChain->SetBranchAddress("lep_Ptcone40_1", &lep_Ptcone40_1, &b_lep_Ptcone40_1);
   fChain->SetBranchAddress("lep_Nucone20_1", &lep_Nucone20_1, &b_lep_Nucone20_1);
   fChain->SetBranchAddress("lep_Nucone30_1", &lep_Nucone30_1, &b_lep_Nucone30_1);
   fChain->SetBranchAddress("lep_Nucone40_1", &lep_Nucone40_1, &b_lep_Nucone40_1);
   fChain->SetBranchAddress("lep_z0PV_1", &lep_z0PV_1, &b_lep_z0PV_1);
   fChain->SetBranchAddress("lep_sigd0PV_1", &lep_sigd0PV_1, &b_lep_sigd0PV_1);
   fChain->SetBranchAddress("lep_D0_1", &lep_D0_1, &b_lep_D0_1);
   fChain->SetBranchAddress("lep_Z0SinTheta_1", &lep_Z0SinTheta_1, &b_lep_Z0SinTheta_1);
   fChain->SetBranchAddress("lep_truth_parent_particle_id1", &lep_truth_parent_particle_id1, &b_lep_truth_parent_particle_id1);
   fChain->SetBranchAddress("lep_truth_particle_id1", &lep_truth_particle_id1, &b_lep_truth_particle_id1);
   fChain->SetBranchAddress("lep_isTightPP_1", &lep_isTightPP_1, &b_lep_isTightPP_1);
   fChain->SetBranchAddress("lep_isMediumPP_1", &lep_isMediumPP_1, &b_lep_isMediumPP_1);
   fChain->SetBranchAddress("lep_isLoosePP_1", &lep_isLoosePP_1, &b_lep_isLoosePP_1);
   fChain->SetBranchAddress("lep_isMultiLepton_1", &lep_isMultiLepton_1, &b_lep_isMultiLepton_1);
   fChain->SetBranchAddress("lep_isVeryTightLH_1", &lep_isVeryTightLH_1, &b_lep_isVeryTightLH_1);
   fChain->SetBranchAddress("lep_isTightLH_1", &lep_isTightLH_1, &b_lep_isTightLH_1);
   fChain->SetBranchAddress("lep_isMediumLH_1", &lep_isMediumLH_1, &b_lep_isMediumLH_1);
   fChain->SetBranchAddress("lep_isLooseLH_1", &lep_isLooseLH_1, &b_lep_isLooseLH_1);
   fChain->SetBranchAddress("lep_isLooseBLPixLH_1", &lep_isLooseBLPixLH_1, &b_lep_isLooseBLPixLH_1);
   fChain->SetBranchAddress("lep_isVeryLooseLH_1", &lep_isVeryLooseLH_1, &b_lep_isVeryLooseLH_1);
   fChain->SetBranchAddress("lep_isCombined_1", &lep_isCombined_1, &b_lep_isCombined_1);
   fChain->SetBranchAddress("lep_isTight_1", &lep_isTight_1, &b_lep_isTight_1);
   fChain->SetBranchAddress("lep_isMedium_1", &lep_isMedium_1, &b_lep_isMedium_1);
   fChain->SetBranchAddress("lep_isLoose_1", &lep_isLoose_1, &b_lep_isLoose_1);
   fChain->SetBranchAddress("lep_isHSG3Clear_1", &lep_isHSG3Clear_1, &b_lep_isHSG3Clear_1);
   fChain->SetBranchAddress("lep_isHSG3IsoClear_1", &lep_isHSG3IsoClear_1, &b_lep_isHSG3IsoClear_1);
   fChain->SetBranchAddress("lep_isTrigMatch_1", &lep_isTrigMatch_1, &b_lep_isTrigMatch_1);
   fChain->SetBranchAddress("lep_isFakable_1", &lep_isFakable_1, &b_lep_isFakable_1);
   fChain->SetBranchAddress("lep_BLayer_hit_1", &lep_BLayer_hit_1, &b_lep_BLayer_hit_1);
   fChain->SetBranchAddress("lep_conv_1", &lep_conv_1, &b_lep_conv_1);
   fChain->SetBranchAddress("lep_Author_1", &lep_Author_1, &b_lep_Author_1);
   fChain->SetBranchAddress("lep_Index_1", &lep_Index_1, &b_lep_Index_1);
   fChain->SetBranchAddress("lep_TrigSFEventWeight_1", &lep_TrigSFEventWeight_1, &b_lep_TrigSFEventWeight_1);
   fChain->SetBranchAddress("lep_TrigSFError_1", &lep_TrigSFError_1, &b_lep_TrigSFError_1);
   fChain->SetBranchAddress("lep_SFRecoEventWeight_1", &lep_SFRecoEventWeight_1, &b_lep_SFRecoEventWeight_1);
   fChain->SetBranchAddress("lep_SFIdEventWeight_1", &lep_SFIdEventWeight_1, &b_lep_SFIdEventWeight_1);
   fChain->SetBranchAddress("lep_SFIsoEventWeight_1", &lep_SFIsoEventWeight_1, &b_lep_SFIsoEventWeight_1);
   fChain->SetBranchAddress("lep_SFErrorIso_1", &lep_SFErrorIso_1, &b_lep_SFErrorIso_1);
   fChain->SetBranchAddress("lep_SFErrorSys_1", &lep_SFErrorSys_1, &b_lep_SFErrorSys_1);
   fChain->SetBranchAddress("lep_SFRecoError_1", &lep_SFRecoError_1, &b_lep_SFRecoError_1);
   fChain->SetBranchAddress("lep_SFRecoErrorSys_1", &lep_SFRecoErrorSys_1, &b_lep_SFRecoErrorSys_1);
   fChain->SetBranchAddress("lep_SFIdError_1", &lep_SFIdError_1, &b_lep_SFIdError_1);
   fChain->SetBranchAddress("lep_SFIsoError_1", &lep_SFIsoError_1, &b_lep_SFIsoError_1);
   fChain->SetBranchAddress("lep_Match_EF_mu24i_tight_1", &lep_Match_EF_mu24i_tight_1, &b_lep_Match_EF_mu24i_tight_1);
   fChain->SetBranchAddress("lep_Match_EF_mu36_tight_1", &lep_Match_EF_mu36_tight_1, &b_lep_Match_EF_mu36_tight_1);
   fChain->SetBranchAddress("lep_Match_EF_e24vhi_medium1_1", &lep_Match_EF_e24vhi_medium1_1, &b_lep_Match_EF_e24vhi_medium1_1);
   fChain->SetBranchAddress("lep_Match_EF_e60_medium1_1", &lep_Match_EF_e60_medium1_1, &b_lep_Match_EF_e60_medium1_1);
   fChain->SetBranchAddress("lep_Match_EF_mu24_tight_1", &lep_Match_EF_mu24_tight_1, &b_lep_Match_EF_mu24_tight_1);
   fChain->SetBranchAddress("lep_Match_EF_mu40_MSonly_barrel_tight_1", &lep_Match_EF_mu40_MSonly_barrel_tight_1, &b_lep_Match_EF_mu40_MSonly_barrel_tight_1);
   fChain->SetBranchAddress("lep_Match_EF_mu18_tight_1", &lep_Match_EF_mu18_tight_1, &b_lep_Match_EF_mu18_tight_1);
   fChain->SetBranchAddress("lep_Match_EF_mu8_EFFS_1", &lep_Match_EF_mu8_EFFS_1, &b_lep_Match_EF_mu8_EFFS_1);
   fChain->SetBranchAddress("lep_Match_EF_mu13_1", &lep_Match_EF_mu13_1, &b_lep_Match_EF_mu13_1);
   fChain->SetBranchAddress("lep_Match_EF_e22vh_medium1_1", &lep_Match_EF_e22vh_medium1_1, &b_lep_Match_EF_e22vh_medium1_1);
   fChain->SetBranchAddress("lep_Match_EF_e45_medium1_1", &lep_Match_EF_e45_medium1_1, &b_lep_Match_EF_e45_medium1_1);
   fChain->SetBranchAddress("lep_Match_EF_e12Tvh_loose1_1", &lep_Match_EF_e12Tvh_loose1_1, &b_lep_Match_EF_e12Tvh_loose1_1);
   fChain->SetBranchAddress("lep_PtID_2", &lep_PtID_2, &b_lep_PtID_2);
   fChain->SetBranchAddress("lep_PtIDuncorr_2", &lep_PtIDuncorr_2, &b_lep_PtIDuncorr_2);
   fChain->SetBranchAddress("lep_PtME_2", &lep_PtME_2, &b_lep_PtME_2);
   fChain->SetBranchAddress("lep_PtMEuncorr_2", &lep_PtMEuncorr_2, &b_lep_PtMEuncorr_2);
   fChain->SetBranchAddress("lep_ID_2", &lep_ID_2, &b_lep_ID_2);
   fChain->SetBranchAddress("lep_Pt_2", &lep_Pt_2, &b_lep_Pt_2);
   fChain->SetBranchAddress("lep_E_2", &lep_E_2, &b_lep_E_2);
   fChain->SetBranchAddress("lep_Eta_2", &lep_Eta_2, &b_lep_Eta_2);
   fChain->SetBranchAddress("lep_Phi_2", &lep_Phi_2, &b_lep_Phi_2);
   fChain->SetBranchAddress("lep_Etcone20Uncorr_2", &lep_Etcone20Uncorr_2, &b_lep_Etcone20Uncorr_2);
   fChain->SetBranchAddress("lep_Etcone30Uncorr_2", &lep_Etcone30Uncorr_2, &b_lep_Etcone30Uncorr_2);
   fChain->SetBranchAddress("lep_Etcone40Uncorr_2", &lep_Etcone40Uncorr_2, &b_lep_Etcone40Uncorr_2);
   fChain->SetBranchAddress("lep_Etcone20_2", &lep_Etcone20_2, &b_lep_Etcone20_2);
   fChain->SetBranchAddress("lep_Etcone30_2", &lep_Etcone30_2, &b_lep_Etcone30_2);
   fChain->SetBranchAddress("lep_Etcone40_2", &lep_Etcone40_2, &b_lep_Etcone40_2);
   fChain->SetBranchAddress("lep_Ptcone20_2", &lep_Ptcone20_2, &b_lep_Ptcone20_2);
   fChain->SetBranchAddress("lep_Ptcone30_2", &lep_Ptcone30_2, &b_lep_Ptcone30_2);
   fChain->SetBranchAddress("lep_Ptcone40_2", &lep_Ptcone40_2, &b_lep_Ptcone40_2);
   fChain->SetBranchAddress("lep_Nucone20_2", &lep_Nucone20_2, &b_lep_Nucone20_2);
   fChain->SetBranchAddress("lep_Nucone30_2", &lep_Nucone30_2, &b_lep_Nucone30_2);
   fChain->SetBranchAddress("lep_Nucone40_2", &lep_Nucone40_2, &b_lep_Nucone40_2);
   fChain->SetBranchAddress("lep_z0PV_2", &lep_z0PV_2, &b_lep_z0PV_2);
   fChain->SetBranchAddress("lep_sigd0PV_2", &lep_sigd0PV_2, &b_lep_sigd0PV_2);
   fChain->SetBranchAddress("lep_D0_2", &lep_D0_2, &b_lep_D0_2);
   fChain->SetBranchAddress("lep_Z0SinTheta_2", &lep_Z0SinTheta_2, &b_lep_Z0SinTheta_2);
   fChain->SetBranchAddress("lep_truth_parent_particle_id2", &lep_truth_parent_particle_id2, &b_lep_truth_parent_particle_id2);
   fChain->SetBranchAddress("lep_truth_particle_id2", &lep_truth_particle_id2, &b_lep_truth_particle_id2);
   fChain->SetBranchAddress("lep_isTightPP_2", &lep_isTightPP_2, &b_lep_isTightPP_2);
   fChain->SetBranchAddress("lep_isMediumPP_2", &lep_isMediumPP_2, &b_lep_isMediumPP_2);
   fChain->SetBranchAddress("lep_isLoosePP_2", &lep_isLoosePP_2, &b_lep_isLoosePP_2);
   fChain->SetBranchAddress("lep_isMultiLepton_2", &lep_isMultiLepton_2, &b_lep_isMultiLepton_2);
   fChain->SetBranchAddress("lep_isVeryTightLH_2", &lep_isVeryTightLH_2, &b_lep_isVeryTightLH_2);
   fChain->SetBranchAddress("lep_isTightLH_2", &lep_isTightLH_2, &b_lep_isTightLH_2);
   fChain->SetBranchAddress("lep_isMediumLH_2", &lep_isMediumLH_2, &b_lep_isMediumLH_2);
   fChain->SetBranchAddress("lep_isLooseLH_2", &lep_isLooseLH_2, &b_lep_isLooseLH_2);
   fChain->SetBranchAddress("lep_isLooseBLPixLH_2", &lep_isLooseBLPixLH_2, &b_lep_isLooseBLPixLH_2);
   fChain->SetBranchAddress("lep_isVeryLooseLH_2", &lep_isVeryLooseLH_2, &b_lep_isVeryLooseLH_2);
   fChain->SetBranchAddress("lep_isCombined_2", &lep_isCombined_2, &b_lep_isCombined_2);
   fChain->SetBranchAddress("lep_isTight_2", &lep_isTight_2, &b_lep_isTight_2);
   fChain->SetBranchAddress("lep_isMedium_2", &lep_isMedium_2, &b_lep_isMedium_2);
   fChain->SetBranchAddress("lep_isLoose_2", &lep_isLoose_2, &b_lep_isLoose_2);
   fChain->SetBranchAddress("lep_isHSG3Clear_2", &lep_isHSG3Clear_2, &b_lep_isHSG3Clear_2);
   fChain->SetBranchAddress("lep_isHSG3IsoClear_2", &lep_isHSG3IsoClear_2, &b_lep_isHSG3IsoClear_2);
   fChain->SetBranchAddress("lep_isTrigMatch_2", &lep_isTrigMatch_2, &b_lep_isTrigMatch_2);
   fChain->SetBranchAddress("lep_isFakable_2", &lep_isFakable_2, &b_lep_isFakable_2);
   fChain->SetBranchAddress("lep_BLayer_hit_2", &lep_BLayer_hit_2, &b_lep_BLayer_hit_2);
   fChain->SetBranchAddress("lep_conv_2", &lep_conv_2, &b_lep_conv_2);
   fChain->SetBranchAddress("lep_Author_2", &lep_Author_2, &b_lep_Author_2);
   fChain->SetBranchAddress("lep_Index_2", &lep_Index_2, &b_lep_Index_2);
   fChain->SetBranchAddress("lep_TrigSFEventWeight_2", &lep_TrigSFEventWeight_2, &b_lep_TrigSFEventWeight_2);
   fChain->SetBranchAddress("lep_TrigSFError_2", &lep_TrigSFError_2, &b_lep_TrigSFError_2);
   fChain->SetBranchAddress("lep_SFRecoEventWeight_2", &lep_SFRecoEventWeight_2, &b_lep_SFRecoEventWeight_2);
   fChain->SetBranchAddress("lep_SFIdEventWeight_2", &lep_SFIdEventWeight_2, &b_lep_SFIdEventWeight_2);
   fChain->SetBranchAddress("lep_SFIsoEventWeight_2", &lep_SFIsoEventWeight_2, &b_lep_SFIsoEventWeight_2);
   fChain->SetBranchAddress("lep_SFErrorIso_2", &lep_SFErrorIso_2, &b_lep_SFErrorIso_2);
   fChain->SetBranchAddress("lep_SFErrorSys_2", &lep_SFErrorSys_2, &b_lep_SFErrorSys_2);
   fChain->SetBranchAddress("lep_SFRecoError_2", &lep_SFRecoError_2, &b_lep_SFRecoError_2);
   fChain->SetBranchAddress("lep_SFRecoErrorSys_2", &lep_SFRecoErrorSys_2, &b_lep_SFRecoErrorSys_2);
   fChain->SetBranchAddress("lep_SFIdError_2", &lep_SFIdError_2, &b_lep_SFIdError_2);
   fChain->SetBranchAddress("lep_SFIsoError_2", &lep_SFIsoError_2, &b_lep_SFIsoError_2);
   fChain->SetBranchAddress("lep_Match_EF_mu24i_tight_2", &lep_Match_EF_mu24i_tight_2, &b_lep_Match_EF_mu24i_tight_2);
   fChain->SetBranchAddress("lep_Match_EF_mu36_tight_2", &lep_Match_EF_mu36_tight_2, &b_lep_Match_EF_mu36_tight_2);
   fChain->SetBranchAddress("lep_Match_EF_e24vhi_medium1_2", &lep_Match_EF_e24vhi_medium1_2, &b_lep_Match_EF_e24vhi_medium1_2);
   fChain->SetBranchAddress("lep_Match_EF_e60_medium1_2", &lep_Match_EF_e60_medium1_2, &b_lep_Match_EF_e60_medium1_2);
   fChain->SetBranchAddress("lep_Match_EF_mu24_tight_2", &lep_Match_EF_mu24_tight_2, &b_lep_Match_EF_mu24_tight_2);
   fChain->SetBranchAddress("lep_Match_EF_mu40_MSonly_barrel_tight_2", &lep_Match_EF_mu40_MSonly_barrel_tight_2, &b_lep_Match_EF_mu40_MSonly_barrel_tight_2);
   fChain->SetBranchAddress("lep_Match_EF_mu18_tight_2", &lep_Match_EF_mu18_tight_2, &b_lep_Match_EF_mu18_tight_2);
   fChain->SetBranchAddress("lep_Match_EF_mu8_EFFS_2", &lep_Match_EF_mu8_EFFS_2, &b_lep_Match_EF_mu8_EFFS_2);
   fChain->SetBranchAddress("lep_Match_EF_mu13_2", &lep_Match_EF_mu13_2, &b_lep_Match_EF_mu13_2);
   fChain->SetBranchAddress("lep_Match_EF_e22vh_medium1_2", &lep_Match_EF_e22vh_medium1_2, &b_lep_Match_EF_e22vh_medium1_2);
   fChain->SetBranchAddress("lep_Match_EF_e45_medium1_2", &lep_Match_EF_e45_medium1_2, &b_lep_Match_EF_e45_medium1_2);
   fChain->SetBranchAddress("lep_Match_EF_e12Tvh_loose1_2", &lep_Match_EF_e12Tvh_loose1_2, &b_lep_Match_EF_e12Tvh_loose1_2);
   fChain->SetBranchAddress("lep_PtID_3", &lep_PtID_3, &b_lep_PtID_3);
   fChain->SetBranchAddress("lep_PtIDuncorr_3", &lep_PtIDuncorr_3, &b_lep_PtIDuncorr_3);
   fChain->SetBranchAddress("lep_PtME_3", &lep_PtME_3, &b_lep_PtME_3);
   fChain->SetBranchAddress("lep_PtMEuncorr_3", &lep_PtMEuncorr_3, &b_lep_PtMEuncorr_3);
   fChain->SetBranchAddress("lep_ID_3", &lep_ID_3, &b_lep_ID_3);
   fChain->SetBranchAddress("lep_Pt_3", &lep_Pt_3, &b_lep_Pt_3);
   fChain->SetBranchAddress("lep_E_3", &lep_E_3, &b_lep_E_3);
   fChain->SetBranchAddress("lep_Eta_3", &lep_Eta_3, &b_lep_Eta_3);
   fChain->SetBranchAddress("lep_Phi_3", &lep_Phi_3, &b_lep_Phi_3);
   fChain->SetBranchAddress("lep_Etcone20Uncorr_3", &lep_Etcone20Uncorr_3, &b_lep_Etcone20Uncorr_3);
   fChain->SetBranchAddress("lep_Etcone30Uncorr_3", &lep_Etcone30Uncorr_3, &b_lep_Etcone30Uncorr_3);
   fChain->SetBranchAddress("lep_Etcone40Uncorr_3", &lep_Etcone40Uncorr_3, &b_lep_Etcone40Uncorr_3);
   fChain->SetBranchAddress("lep_Etcone20_3", &lep_Etcone20_3, &b_lep_Etcone20_3);
   fChain->SetBranchAddress("lep_Etcone30_3", &lep_Etcone30_3, &b_lep_Etcone30_3);
   fChain->SetBranchAddress("lep_Etcone40_3", &lep_Etcone40_3, &b_lep_Etcone40_3);
   fChain->SetBranchAddress("lep_Ptcone20_3", &lep_Ptcone20_3, &b_lep_Ptcone20_3);
   fChain->SetBranchAddress("lep_Ptcone30_3", &lep_Ptcone30_3, &b_lep_Ptcone30_3);
   fChain->SetBranchAddress("lep_Ptcone40_3", &lep_Ptcone40_3, &b_lep_Ptcone40_3);
   fChain->SetBranchAddress("lep_Nucone20_3", &lep_Nucone20_3, &b_lep_Nucone20_3);
   fChain->SetBranchAddress("lep_Nucone30_3", &lep_Nucone30_3, &b_lep_Nucone30_3);
   fChain->SetBranchAddress("lep_Nucone40_3", &lep_Nucone40_3, &b_lep_Nucone40_3);
   fChain->SetBranchAddress("lep_z0PV_3", &lep_z0PV_3, &b_lep_z0PV_3);
   fChain->SetBranchAddress("lep_sigd0PV_3", &lep_sigd0PV_3, &b_lep_sigd0PV_3);
   fChain->SetBranchAddress("lep_D0_3", &lep_D0_3, &b_lep_D0_3);
   fChain->SetBranchAddress("lep_Z0SinTheta_3", &lep_Z0SinTheta_3, &b_lep_Z0SinTheta_3);
   fChain->SetBranchAddress("lep_truth_parent_particle_id3", &lep_truth_parent_particle_id3, &b_lep_truth_parent_particle_id3);
   fChain->SetBranchAddress("lep_truth_particle_id3", &lep_truth_particle_id3, &b_lep_truth_particle_id3);
   fChain->SetBranchAddress("lep_isTightPP_3", &lep_isTightPP_3, &b_lep_isTightPP_3);
   fChain->SetBranchAddress("lep_isMediumPP_3", &lep_isMediumPP_3, &b_lep_isMediumPP_3);
   fChain->SetBranchAddress("lep_isLoosePP_3", &lep_isLoosePP_3, &b_lep_isLoosePP_3);
   fChain->SetBranchAddress("lep_isMultiLepton_3", &lep_isMultiLepton_3, &b_lep_isMultiLepton_3);
   fChain->SetBranchAddress("lep_isVeryTightLH_3", &lep_isVeryTightLH_3, &b_lep_isVeryTightLH_3);
   fChain->SetBranchAddress("lep_isTightLH_3", &lep_isTightLH_3, &b_lep_isTightLH_3);
   fChain->SetBranchAddress("lep_isMediumLH_3", &lep_isMediumLH_3, &b_lep_isMediumLH_3);
   fChain->SetBranchAddress("lep_isLooseLH_3", &lep_isLooseLH_3, &b_lep_isLooseLH_3);
   fChain->SetBranchAddress("lep_isLooseBLPixLH_3", &lep_isLooseBLPixLH_3, &b_lep_isLooseBLPixLH_3);
   fChain->SetBranchAddress("lep_isVeryLooseLH_3", &lep_isVeryLooseLH_3, &b_lep_isVeryLooseLH_3);
   fChain->SetBranchAddress("lep_isCombined_3", &lep_isCombined_3, &b_lep_isCombined_3);
   fChain->SetBranchAddress("lep_isTight_3", &lep_isTight_3, &b_lep_isTight_3);
   fChain->SetBranchAddress("lep_isMedium_3", &lep_isMedium_3, &b_lep_isMedium_3);
   fChain->SetBranchAddress("lep_isLoose_3", &lep_isLoose_3, &b_lep_isLoose_3);
   fChain->SetBranchAddress("lep_isHSG3Clear_3", &lep_isHSG3Clear_3, &b_lep_isHSG3Clear_3);
   fChain->SetBranchAddress("lep_isHSG3IsoClear_3", &lep_isHSG3IsoClear_3, &b_lep_isHSG3IsoClear_3);
   fChain->SetBranchAddress("lep_isTrigMatch_3", &lep_isTrigMatch_3, &b_lep_isTrigMatch_3);
   fChain->SetBranchAddress("lep_isFakable_3", &lep_isFakable_3, &b_lep_isFakable_3);
   fChain->SetBranchAddress("lep_BLayer_hit_3", &lep_BLayer_hit_3, &b_lep_BLayer_hit_3);
   fChain->SetBranchAddress("lep_conv_3", &lep_conv_3, &b_lep_conv_3);
   fChain->SetBranchAddress("lep_Author_3", &lep_Author_3, &b_lep_Author_3);
   fChain->SetBranchAddress("lep_Index_3", &lep_Index_3, &b_lep_Index_3);
   fChain->SetBranchAddress("lep_TrigSFEventWeight_3", &lep_TrigSFEventWeight_3, &b_lep_TrigSFEventWeight_3);
   fChain->SetBranchAddress("lep_TrigSFError_3", &lep_TrigSFError_3, &b_lep_TrigSFError_3);
   fChain->SetBranchAddress("lep_SFRecoEventWeight_3", &lep_SFRecoEventWeight_3, &b_lep_SFRecoEventWeight_3);
   fChain->SetBranchAddress("lep_SFIdEventWeight_3", &lep_SFIdEventWeight_3, &b_lep_SFIdEventWeight_3);
   fChain->SetBranchAddress("lep_SFIsoEventWeight_3", &lep_SFIsoEventWeight_3, &b_lep_SFIsoEventWeight_3);
   fChain->SetBranchAddress("lep_SFErrorIso_3", &lep_SFErrorIso_3, &b_lep_SFErrorIso_3);
   fChain->SetBranchAddress("lep_SFErrorSys_3", &lep_SFErrorSys_3, &b_lep_SFErrorSys_3);
   fChain->SetBranchAddress("lep_SFRecoError_3", &lep_SFRecoError_3, &b_lep_SFRecoError_3);
   fChain->SetBranchAddress("lep_SFRecoErrorSys_3", &lep_SFRecoErrorSys_3, &b_lep_SFRecoErrorSys_3);
   fChain->SetBranchAddress("lep_SFIdError_3", &lep_SFIdError_3, &b_lep_SFIdError_3);
   fChain->SetBranchAddress("lep_SFIsoError_3", &lep_SFIsoError_3, &b_lep_SFIsoError_3);
   fChain->SetBranchAddress("lep_Match_EF_mu24i_tight_3", &lep_Match_EF_mu24i_tight_3, &b_lep_Match_EF_mu24i_tight_3);
   fChain->SetBranchAddress("lep_Match_EF_mu36_tight_3", &lep_Match_EF_mu36_tight_3, &b_lep_Match_EF_mu36_tight_3);
   fChain->SetBranchAddress("lep_Match_EF_e24vhi_medium1_3", &lep_Match_EF_e24vhi_medium1_3, &b_lep_Match_EF_e24vhi_medium1_3);
   fChain->SetBranchAddress("lep_Match_EF_e60_medium1_3", &lep_Match_EF_e60_medium1_3, &b_lep_Match_EF_e60_medium1_3);
   fChain->SetBranchAddress("lep_Match_EF_mu24_tight_3", &lep_Match_EF_mu24_tight_3, &b_lep_Match_EF_mu24_tight_3);
   fChain->SetBranchAddress("lep_Match_EF_mu40_MSonly_barrel_tight_3", &lep_Match_EF_mu40_MSonly_barrel_tight_3, &b_lep_Match_EF_mu40_MSonly_barrel_tight_3);
   fChain->SetBranchAddress("lep_Match_EF_mu18_tight_3", &lep_Match_EF_mu18_tight_3, &b_lep_Match_EF_mu18_tight_3);
   fChain->SetBranchAddress("lep_Match_EF_mu8_EFFS_3", &lep_Match_EF_mu8_EFFS_3, &b_lep_Match_EF_mu8_EFFS_3);
   fChain->SetBranchAddress("lep_Match_EF_mu13_3", &lep_Match_EF_mu13_3, &b_lep_Match_EF_mu13_3);
   fChain->SetBranchAddress("lep_Match_EF_e22vh_medium1_3", &lep_Match_EF_e22vh_medium1_3, &b_lep_Match_EF_e22vh_medium1_3);
   fChain->SetBranchAddress("lep_Match_EF_e45_medium1_3", &lep_Match_EF_e45_medium1_3, &b_lep_Match_EF_e45_medium1_3);
   fChain->SetBranchAddress("lep_Match_EF_e12Tvh_loose1_3", &lep_Match_EF_e12Tvh_loose1_3, &b_lep_Match_EF_e12Tvh_loose1_3);
   fChain->SetBranchAddress("total_charge", &total_charge, &b_total_charge);
   fChain->SetBranchAddress("DRlep0jet", &DRlep0jet, &b_DRlep0jet);
   fChain->SetBranchAddress("DRlep1jet", &DRlep1jet, &b_DRlep1jet);
   fChain->SetBranchAddress("lep_IndexFake", &lep_IndexFake, &b_lep_IndexFake);
   fChain->SetBranchAddress("vertexEventWeight", &vertexEventWeight, &b_vertexEventWeight);
   fChain->SetBranchAddress("vertexEventWeight_Pu1", &vertexEventWeight_Pu1, &b_vertexEventWeight_Pu1);
   fChain->SetBranchAddress("vertexEventWeight_Pu088", &vertexEventWeight_Pu088, &b_vertexEventWeight_Pu088);
   fChain->SetBranchAddress("pileupEventWeight", &pileupEventWeight, &b_pileupEventWeight);
   fChain->SetBranchAddress("pileupEventWeight_094", &pileupEventWeight_094, &b_pileupEventWeight_094);
   fChain->SetBranchAddress("pileupEventWeight_080", &pileupEventWeight_080, &b_pileupEventWeight_080);
   fChain->SetBranchAddress("pileupEventWeight_090", &pileupEventWeight_090, &b_pileupEventWeight_090);
   fChain->SetBranchAddress("pileupEventWeight_088", &pileupEventWeight_088, &b_pileupEventWeight_088);
   fChain->SetBranchAddress("pileupEventWeight_075", &pileupEventWeight_075, &b_pileupEventWeight_075);
   fChain->SetBranchAddress("pileupEventWeight_103", &pileupEventWeight_103, &b_pileupEventWeight_103);
   fChain->SetBranchAddress("mcEventWeight", &mcEventWeight, &b_mcEventWeight);
   fChain->SetBranchAddress("mcWeightOrg", &mcWeightOrg, &b_mcWeightOrg);
   fChain->SetBranchAddress("trigEventWeight", &trigEventWeight, &b_trigEventWeight);
   fChain->SetBranchAddress("nJets_OR_MV1_70", &nJets_OR_MV1_70, &b_nJets_OR_MV1_70);
   fChain->SetBranchAddress("nJets_OR_MV1_80", &nJets_OR_MV1_80, &b_nJets_OR_MV1_80);
   fChain->SetBranchAddress("nJets_Pt20_MV1_70", &nJets_Pt20_MV1_70, &b_nJets_Pt20_MV1_70);
   fChain->SetBranchAddress("nJets_Pt20_MV1_80", &nJets_Pt20_MV1_80, &b_nJets_Pt20_MV1_80);
   fChain->SetBranchAddress("nJets_Pt20", &nJets_Pt20, &b_nJets_Pt20);
   fChain->SetBranchAddress("nJets_OR", &nJets_OR, &b_nJets_OR);
   fChain->SetBranchAddress("m_jet_selectStatus", &m_jet_selectStatus, &b_m_jet_selectStatus);
   fChain->SetBranchAddress("nJetsProbing_MV1_80", &nJetsProbing_MV1_80, &b_nJetsProbing_MV1_80);
   fChain->SetBranchAddress("nJetsProbing_MV1_70", &nJetsProbing_MV1_70, &b_nJetsProbing_MV1_70);
   fChain->SetBranchAddress("Nvxp", &Nvxp, &b_Nvxp);
   fChain->SetBranchAddress("jetPt0", &jetPt0, &b_jetPt0);
   fChain->SetBranchAddress("jetPt1", &jetPt1, &b_jetPt1);
   fChain->SetBranchAddress("jetEta0", &jetEta0, &b_jetEta0);
   fChain->SetBranchAddress("jetEta1", &jetEta1, &b_jetEta1);
   fChain->SetBranchAddress("jetE0", &jetE0, &b_jetE0);
   fChain->SetBranchAddress("jetE1", &jetE1, &b_jetE1);
   fChain->SetBranchAddress("jetY0", &jetY0, &b_jetY0);
   fChain->SetBranchAddress("jetY1", &jetY1, &b_jetY1);
   fChain->SetBranchAddress("jetM0", &jetM0, &b_jetM0);
   fChain->SetBranchAddress("jetM1", &jetM1, &b_jetM1);
   fChain->SetBranchAddress("jetPhi0", &jetPhi0, &b_jetPhi0);
   fChain->SetBranchAddress("jetPhi1", &jetPhi1, &b_jetPhi1);
   fChain->SetBranchAddress("jetMV10", &jetMV10, &b_jetMV10);
   fChain->SetBranchAddress("jetMV11", &jetMV11, &b_jetMV11);
   fChain->SetBranchAddress("z0Vtx", &z0Vtx, &b_z0Vtx);
   fChain->SetBranchAddress("bpos", &bpos, &b_bpos);
   fChain->SetBranchAddress("blen", &blen, &b_blen);
   fChain->SetBranchAddress("bgap", &bgap, &b_bgap);
   fChain->SetBranchAddress("DYPtllWeight", &DYPtllWeight, &b_DYPtllWeight);
   fChain->SetBranchAddress("DYPtllWeight_CT10", &DYPtllWeight_CT10, &b_DYPtllWeight_CT10);
   fChain->SetBranchAddress("DYPtllWeight_MRST", &DYPtllWeight_MRST, &b_DYPtllWeight_MRST);
   fChain->SetBranchAddress("onelep_type", &onelep_type, &b_onelep_type);
   fChain->SetBranchAddress("dilep_type", &dilep_type, &b_dilep_type);
   fChain->SetBranchAddress("trilep_type", &trilep_type, &b_trilep_type);
   fChain->SetBranchAddress("quadlep_type", &quadlep_type, &b_quadlep_type);
   fChain->SetBranchAddress("isEEE", &isEEE, &b_isEEE);
   fChain->SetBranchAddress("isEEM", &isEEM, &b_isEEM);
   fChain->SetBranchAddress("isMME", &isMME, &b_isMME);
   fChain->SetBranchAddress("isMMM", &isMMM, &b_isMMM);
   fChain->SetBranchAddress("Mll01", &Mll01, &b_Mll01);
   fChain->SetBranchAddress("Mll02", &Mll02, &b_Mll02);
   fChain->SetBranchAddress("Mll12", &Mll12, &b_Mll12);
   fChain->SetBranchAddress("Ptll01", &Ptll01, &b_Ptll01);
   fChain->SetBranchAddress("Ptll02", &Ptll02, &b_Ptll02);
   fChain->SetBranchAddress("Ptll12", &Ptll12, &b_Ptll12);
   fChain->SetBranchAddress("DPhill01", &DPhill01, &b_DPhill01);
   fChain->SetBranchAddress("DPhill02", &DPhill02, &b_DPhill02);
   fChain->SetBranchAddress("DPhill12", &DPhill12, &b_DPhill12);
   fChain->SetBranchAddress("DRll01", &DRll01, &b_DRll01);
   fChain->SetBranchAddress("DRll02", &DRll02, &b_DRll02);
   fChain->SetBranchAddress("DRll12", &DRll12, &b_DRll12);
   fChain->SetBranchAddress("DR012", &DR012, &b_DR012);
   fChain->SetBranchAddress("DR102", &DR102, &b_DR102);
   fChain->SetBranchAddress("DR201", &DR201, &b_DR201);
   fChain->SetBranchAddress("DPhi012", &DPhi012, &b_DPhi012);
   fChain->SetBranchAddress("DPhi102", &DPhi102, &b_DPhi102);
   fChain->SetBranchAddress("DPhi201", &DPhi201, &b_DPhi201);
   fChain->SetBranchAddress("DEtall01", &DEtall01, &b_DEtall01);
   fChain->SetBranchAddress("DEtall02", &DEtall02, &b_DEtall02);
   fChain->SetBranchAddress("DEtall12", &DEtall12, &b_DEtall12);
   fChain->SetBranchAddress("Yll01", &Yll01, &b_Yll01);
   fChain->SetBranchAddress("Yll02", &Yll02, &b_Yll02);
   fChain->SetBranchAddress("Yll12", &Yll12, &b_Yll12);
   fChain->SetBranchAddress("isEEEE", &isEEEE, &b_isEEEE);
   fChain->SetBranchAddress("isEEEM", &isEEEM, &b_isEEEM);
   fChain->SetBranchAddress("isEEMM", &isEEMM, &b_isEEMM);
   fChain->SetBranchAddress("isEMMM", &isEMMM, &b_isEMMM);
   fChain->SetBranchAddress("isMMMM", &isMMMM, &b_isMMMM);
   fChain->SetBranchAddress("Mll03", &Mll03, &b_Mll03);
   fChain->SetBranchAddress("Mll13", &Mll13, &b_Mll13);
   fChain->SetBranchAddress("Mll23", &Mll23, &b_Mll23);
   fChain->SetBranchAddress("Mlll012", &Mlll012, &b_Mlll012);
   fChain->SetBranchAddress("Mlll013", &Mlll013, &b_Mlll013);
   fChain->SetBranchAddress("Mlll023", &Mlll023, &b_Mlll023);
   fChain->SetBranchAddress("Mlll123", &Mlll123, &b_Mlll123);
   fChain->SetBranchAddress("Mllll", &Mllll, &b_Mllll);
   fChain->SetBranchAddress("DPhill03", &DPhill03, &b_DPhill03);
   fChain->SetBranchAddress("DPhill13", &DPhill13, &b_DPhill13);
   fChain->SetBranchAddress("DPhill23", &DPhill23, &b_DPhill23);
   fChain->SetBranchAddress("DPhi013", &DPhi013, &b_DPhi013);
   fChain->SetBranchAddress("DPhi103", &DPhi103, &b_DPhi103);
   fChain->SetBranchAddress("DPhi301", &DPhi301, &b_DPhi301);
   fChain->SetBranchAddress("DPhi023", &DPhi023, &b_DPhi023);
   fChain->SetBranchAddress("DPhi203", &DPhi203, &b_DPhi203);
   fChain->SetBranchAddress("DPhi302", &DPhi302, &b_DPhi302);
   fChain->SetBranchAddress("DPhi123", &DPhi123, &b_DPhi123);
   fChain->SetBranchAddress("DPhi213", &DPhi213, &b_DPhi213);
   fChain->SetBranchAddress("DPhi312", &DPhi312, &b_DPhi312);
   fChain->SetBranchAddress("DRll03", &DRll03, &b_DRll03);
   fChain->SetBranchAddress("DRll13", &DRll13, &b_DRll13);
   fChain->SetBranchAddress("DRll23", &DRll23, &b_DRll23);
   fChain->SetBranchAddress("DR013", &DR013, &b_DR013);
   fChain->SetBranchAddress("DR103", &DR103, &b_DR103);
   fChain->SetBranchAddress("DR301", &DR301, &b_DR301);
   fChain->SetBranchAddress("DR023", &DR023, &b_DR023);
   fChain->SetBranchAddress("DR203", &DR203, &b_DR203);
   fChain->SetBranchAddress("DR302", &DR302, &b_DR302);
   fChain->SetBranchAddress("DR123", &DR123, &b_DR123);
   fChain->SetBranchAddress("DR213", &DR213, &b_DR213);
   fChain->SetBranchAddress("DR312", &DR312, &b_DR312);
   fChain->SetBranchAddress("Ptll03", &Ptll03, &b_Ptll03);
   fChain->SetBranchAddress("Ptll13", &Ptll13, &b_Ptll13);
   fChain->SetBranchAddress("Ptll23", &Ptll23, &b_Ptll23);
   fChain->SetBranchAddress("Yll03", &Yll03, &b_Yll03);
   fChain->SetBranchAddress("Yll13", &Yll13, &b_Yll13);
   fChain->SetBranchAddress("Yll23", &Yll23, &b_Yll23);
   fChain->SetBranchAddress("DEtall03", &DEtall03, &b_DEtall03);
   fChain->SetBranchAddress("DEtall13", &DEtall13, &b_DEtall13);
   fChain->SetBranchAddress("DEtall23", &DEtall23, &b_DEtall23);
   fChain->SetBranchAddress("passEventCleaning", &passEventCleaning, &b_passEventCleaning);
   fChain->SetBranchAddress("muon_pt", &muon_pt, &b_muon_pt);
   fChain->SetBranchAddress("muon_eta", &muon_eta, &b_muon_eta);
   fChain->SetBranchAddress("muon_phi", &muon_phi, &b_muon_phi);
   fChain->SetBranchAddress("muon_E", &muon_E, &b_muon_E);
   fChain->SetBranchAddress("muon_Etcone20", &muon_Etcone20, &b_muon_Etcone20);
   fChain->SetBranchAddress("muon_Etcone30", &muon_Etcone30, &b_muon_Etcone30);
   fChain->SetBranchAddress("muon_Etcone40", &muon_Etcone40, &b_muon_Etcone40);
   fChain->SetBranchAddress("muon_Etcone20Uncorr", &muon_Etcone20Uncorr, &b_muon_Etcone20Uncorr);
   fChain->SetBranchAddress("muon_Etcone30Uncorr", &muon_Etcone30Uncorr, &b_muon_Etcone30Uncorr);
   fChain->SetBranchAddress("muon_Etcone40Uncorr", &muon_Etcone40Uncorr, &b_muon_Etcone40Uncorr);
   fChain->SetBranchAddress("muon_ptcone20", &muon_ptcone20, &b_muon_ptcone20);
   fChain->SetBranchAddress("muon_ptcone30", &muon_ptcone30, &b_muon_ptcone30);
   fChain->SetBranchAddress("muon_ptcone40", &muon_ptcone40, &b_muon_ptcone40);
   fChain->SetBranchAddress("muon_z0PV", &muon_z0PV, &b_muon_z0PV);
   fChain->SetBranchAddress("muon_sigd0PV", &muon_sigd0PV, &b_muon_sigd0PV);
   fChain->SetBranchAddress("muon_d0", &muon_d0, &b_muon_d0);
   fChain->SetBranchAddress("muon_z0SinTheta", &muon_z0SinTheta, &b_muon_z0SinTheta);
   fChain->SetBranchAddress("muon_author", &muon_author, &b_muon_author);
   fChain->SetBranchAddress("muon_d3pdindex", &muon_d3pdindex, &b_muon_d3pdindex);
   fChain->SetBranchAddress("muon_truth_parent_particle_id", &muon_truth_parent_particle_id, &b_muon_truth_parent_particle_id);
   fChain->SetBranchAddress("muon_truth_particle_id", &muon_truth_particle_id, &b_muon_truth_particle_id);
   fChain->SetBranchAddress("muon_ID", &muon_ID, &b_muon_ID);
   fChain->SetBranchAddress("muon_allAuthor", &muon_allAuthor, &b_muon_allAuthor);
   fChain->SetBranchAddress("muon_PtID", &muon_PtID, &b_muon_PtID);
   fChain->SetBranchAddress("muon_PtIDuncorr", &muon_PtIDuncorr, &b_muon_PtIDuncorr);
   fChain->SetBranchAddress("muon_PtME", &muon_PtME, &b_muon_PtME);
   fChain->SetBranchAddress("muon_matchchi2", &muon_matchchi2, &b_muon_matchchi2);
   fChain->SetBranchAddress("muon_PtMEuncorr", &muon_PtMEuncorr, &b_muon_PtMEuncorr);
   fChain->SetBranchAddress("muon_isCombined", &muon_isCombined, &b_muon_isCombined);
   fChain->SetBranchAddress("muon_isTight", &muon_isTight, &b_muon_isTight);
   fChain->SetBranchAddress("muon_isMedium", &muon_isMedium, &b_muon_isMedium);
   fChain->SetBranchAddress("muon_isLoose", &muon_isLoose, &b_muon_isLoose);
   fChain->SetBranchAddress("muon_Match_EF_mu24_tight", &muon_Match_EF_mu24_tight, &b_muon_Match_EF_mu24_tight);
   fChain->SetBranchAddress("muon_Match_EF_mu40_MSonly_barrel_tight", &muon_Match_EF_mu40_MSonly_barrel_tight, &b_muon_Match_EF_mu40_MSonly_barrel_tight);
   fChain->SetBranchAddress("muon_Match_EF_mu18_tight", &muon_Match_EF_mu18_tight, &b_muon_Match_EF_mu18_tight);
   fChain->SetBranchAddress("muon_Match_EF_mu8_EFFS", &muon_Match_EF_mu8_EFFS, &b_muon_Match_EF_mu8_EFFS);
   fChain->SetBranchAddress("muon_Match_EF_mu13", &muon_Match_EF_mu13, &b_muon_Match_EF_mu13);
   fChain->SetBranchAddress("muon_Match_EF_mu24i_tight", &muon_Match_EF_mu24i_tight, &b_muon_Match_EF_mu24i_tight);
   fChain->SetBranchAddress("muon_Match_EF_mu36_tight", &muon_Match_EF_mu36_tight, &b_muon_Match_EF_mu36_tight);
   fChain->SetBranchAddress("electron_pt", &electron_pt, &b_electron_pt);
   fChain->SetBranchAddress("electron_eta", &electron_eta, &b_electron_eta);
   fChain->SetBranchAddress("electron_phi", &electron_phi, &b_electron_phi);
   fChain->SetBranchAddress("electron_E", &electron_E, &b_electron_E);
   fChain->SetBranchAddress("electron_Etcone20", &electron_Etcone20, &b_electron_Etcone20);
   fChain->SetBranchAddress("electron_Etcone30", &electron_Etcone30, &b_electron_Etcone30);
   fChain->SetBranchAddress("electron_Etcone40", &electron_Etcone40, &b_electron_Etcone40);
   fChain->SetBranchAddress("electron_Etcone20Uncorr", &electron_Etcone20Uncorr, &b_electron_Etcone20Uncorr);
   fChain->SetBranchAddress("electron_Etcone30Uncorr", &electron_Etcone30Uncorr, &b_electron_Etcone30Uncorr);
   fChain->SetBranchAddress("electron_Etcone40Uncorr", &electron_Etcone40Uncorr, &b_electron_Etcone40Uncorr);
   fChain->SetBranchAddress("electron_ptcone20", &electron_ptcone20, &b_electron_ptcone20);
   fChain->SetBranchAddress("electron_ptcone30", &electron_ptcone30, &b_electron_ptcone30);
   fChain->SetBranchAddress("electron_ptcone40", &electron_ptcone40, &b_electron_ptcone40);
   fChain->SetBranchAddress("electron_z0PV", &electron_z0PV, &b_electron_z0PV);
   fChain->SetBranchAddress("electron_sigd0PV", &electron_sigd0PV, &b_electron_sigd0PV);
   fChain->SetBranchAddress("electron_d0", &electron_d0, &b_electron_d0);
   fChain->SetBranchAddress("electron_z0SinTheta", &electron_z0SinTheta, &b_electron_z0SinTheta);
   fChain->SetBranchAddress("electron_author", &electron_author, &b_electron_author);
   fChain->SetBranchAddress("electron_d3pdindex", &electron_d3pdindex, &b_electron_d3pdindex);
   fChain->SetBranchAddress("electron_truth_parent_particle_id", &electron_truth_parent_particle_id, &b_electron_truth_parent_particle_id);
   fChain->SetBranchAddress("electron_truth_particle_id", &electron_truth_particle_id, &b_electron_truth_particle_id);
   fChain->SetBranchAddress("electron_ID", &electron_ID, &b_electron_ID);
   fChain->SetBranchAddress("electron_ClEta", &electron_ClEta, &b_electron_ClEta);
   fChain->SetBranchAddress("electron_isTightPP", &electron_isTightPP, &b_electron_isTightPP);
   fChain->SetBranchAddress("electron_isMediumPP", &electron_isMediumPP, &b_electron_isMediumPP);
   fChain->SetBranchAddress("electron_isLoosePP", &electron_isLoosePP, &b_electron_isLoosePP);
   fChain->SetBranchAddress("electron_isMultiLepton", &electron_isMultiLepton, &b_electron_isMultiLepton);
   fChain->SetBranchAddress("electron_isVeryTightLH", &electron_isVeryTightLH, &b_electron_isVeryTightLH);
   fChain->SetBranchAddress("electron_isTightLH", &electron_isTightLH, &b_electron_isTightLH);
   fChain->SetBranchAddress("electron_isMediumLH", &electron_isMediumLH, &b_electron_isMediumLH);
   fChain->SetBranchAddress("electron_isLooseLH", &electron_isLooseLH, &b_electron_isLooseLH);
   fChain->SetBranchAddress("electron_isLooseBLPixLH", &electron_isLooseBLPixLH, &b_electron_isLooseBLPixLH);
   fChain->SetBranchAddress("electron_isVeryLooseLH", &electron_isVeryLooseLH, &b_electron_isVeryLooseLH);
   fChain->SetBranchAddress("electron_conv", &electron_conv, &b_electron_conv);
   fChain->SetBranchAddress("electron_BLayer_hit", &electron_BLayer_hit, &b_electron_BLayer_hit);
   fChain->SetBranchAddress("electron_Match_EF_e24vhi_medium1", &electron_Match_EF_e24vhi_medium1, &b_electron_Match_EF_e24vhi_medium1);
   fChain->SetBranchAddress("electron_Match_EF_e60_medium1", &electron_Match_EF_e60_medium1, &b_electron_Match_EF_e60_medium1);
   fChain->SetBranchAddress("electron_Match_EF_e22vh_medium1", &electron_Match_EF_e22vh_medium1, &b_electron_Match_EF_e22vh_medium1);
   fChain->SetBranchAddress("electron_Match_EF_e45_medium1", &electron_Match_EF_e45_medium1, &b_electron_Match_EF_e45_medium1);
   fChain->SetBranchAddress("electron_Match_EF_e12Tvh_loose1", &electron_Match_EF_e12Tvh_loose1, &b_electron_Match_EF_e12Tvh_loose1);
   fChain->SetBranchAddress("m_track_n", &m_track_n, &b_m_track_n);
   fChain->SetBranchAddress("m_track_nTight", &m_track_nTight, &b_m_track_nTight);
   fChain->SetBranchAddress("m_track_pt", &m_track_pt, &b_m_track_pt);
   fChain->SetBranchAddress("m_track_eta", &m_track_eta, &b_m_track_eta);
   fChain->SetBranchAddress("m_track_phi", &m_track_phi, &b_m_track_phi);
   fChain->SetBranchAddress("m_track_z0", &m_track_z0, &b_m_track_z0);
   fChain->SetBranchAddress("m_track_d0", &m_track_d0, &b_m_track_d0);
   fChain->SetBranchAddress("m_track_qoverp", &m_track_qoverp, &b_m_track_qoverp);
   fChain->SetBranchAddress("m_track_nPixHits", &m_track_nPixHits, &b_m_track_nPixHits);
   fChain->SetBranchAddress("m_track_nSCTHits", &m_track_nSCTHits, &b_m_track_nSCTHits);
   fChain->SetBranchAddress("m_track_ptcone20", &m_track_ptcone20, &b_m_track_ptcone20);
   fChain->SetBranchAddress("m_track_ptcone30", &m_track_ptcone30, &b_m_track_ptcone30);
   fChain->SetBranchAddress("m_track_ptcone40", &m_track_ptcone40, &b_m_track_ptcone40);
   fChain->SetBranchAddress("m_track_isTight", &m_track_isTight, &b_m_track_isTight);
   fChain->SetBranchAddress("m_truth_n", &m_truth_n, &b_m_truth_n);
   fChain->SetBranchAddress("m_truth_pt", &m_truth_pt, &b_m_truth_pt);
   fChain->SetBranchAddress("m_truth_m", &m_truth_m, &b_m_truth_m);
   fChain->SetBranchAddress("m_truth_eta", &m_truth_eta, &b_m_truth_eta);
   fChain->SetBranchAddress("m_truth_phi", &m_truth_phi, &b_m_truth_phi);
   fChain->SetBranchAddress("m_truth_status", &m_truth_status, &b_m_truth_status);
   fChain->SetBranchAddress("m_truth_pdgId", &m_truth_pdgId, &b_m_truth_pdgId);
   fChain->SetBranchAddress("m_truth_isFamilyChain", &m_truth_isFamilyChain, &b_m_truth_isFamilyChain);
   fChain->SetBranchAddress("m_truth_isFlatChain", &m_truth_isFlatChain, &b_m_truth_isFlatChain);
   fChain->SetBranchAddress("m_truth_childIndices", &m_truth_childIndices, &b_m_truth_childIndices);
   fChain->SetBranchAddress("m_truth_parentIndices", &m_truth_parentIndices, &b_m_truth_parentIndices);
   fChain->SetBranchAddress("trueHadronicTau_n", &trueHadronicTau_n, &b_trueHadronicTau_n);
   fChain->SetBranchAddress("trueHadronicTau_index", &trueHadronicTau_index, &b_trueHadronicTau_index);
   fChain->SetBranchAddress("trueHadronicTau_visPt", &trueHadronicTau_visPt, &b_trueHadronicTau_visPt);
   fChain->SetBranchAddress("trueHadronicTau_visEta", &trueHadronicTau_visEta, &b_trueHadronicTau_visEta);
   fChain->SetBranchAddress("trueHadronicTau_visPhi", &trueHadronicTau_visPhi, &b_trueHadronicTau_visPhi);
   fChain->SetBranchAddress("RunNumber", &RunNumber, &b_RunNumber);
   fChain->SetBranchAddress("EventNumber", &EventNumber, &b_EventNumber);
   fChain->SetBranchAddress("lbn", &lbn, &b_lbn);
   fChain->SetBranchAddress("bcid", &bcid, &b_bcid);
   fChain->SetBranchAddress("actualIntPerXing", &actualIntPerXing, &b_actualIntPerXing);
   fChain->SetBranchAddress("averageIntPerXing", &averageIntPerXing, &b_averageIntPerXing);
   fChain->SetBranchAddress("mc_channel_number", &mc_channel_number, &b_mc_channel_number);
   fChain->SetBranchAddress("larError", &larError, &b_larError);
   fChain->SetBranchAddress("MET_RefFinal_phi", &MET_RefFinal_phi, &b_MET_RefFinal_phi);
   fChain->SetBranchAddress("MET_RefFinal_et", &MET_RefFinal_et, &b_MET_RefFinal_et);
   fChain->SetBranchAddress("MET_RefFinal_sumet", &MET_RefFinal_sumet, &b_MET_RefFinal_sumet);
   fChain->SetBranchAddress("MET_Cryo_phi", &MET_Cryo_phi, &b_MET_Cryo_phi);
   fChain->SetBranchAddress("MET_Cryo_et", &MET_Cryo_et, &b_MET_Cryo_et);
   fChain->SetBranchAddress("MET_Cryo_sumet", &MET_Cryo_sumet, &b_MET_Cryo_sumet);
   fChain->SetBranchAddress("MET_RefEle_phi", &MET_RefEle_phi, &b_MET_RefEle_phi);
   fChain->SetBranchAddress("MET_RefEle_et", &MET_RefEle_et, &b_MET_RefEle_et);
   fChain->SetBranchAddress("MET_RefEle_sumet", &MET_RefEle_sumet, &b_MET_RefEle_sumet);
   fChain->SetBranchAddress("MET_RefJet_phi", &MET_RefJet_phi, &b_MET_RefJet_phi);
   fChain->SetBranchAddress("MET_RefJet_et", &MET_RefJet_et, &b_MET_RefJet_et);
   fChain->SetBranchAddress("MET_RefJet_sumet", &MET_RefJet_sumet, &b_MET_RefJet_sumet);
   fChain->SetBranchAddress("MET_SoftJets_phi", &MET_SoftJets_phi, &b_MET_SoftJets_phi);
   fChain->SetBranchAddress("MET_SoftJets_et", &MET_SoftJets_et, &b_MET_SoftJets_et);
   fChain->SetBranchAddress("MET_SoftJets_sumet", &MET_SoftJets_sumet, &b_MET_SoftJets_sumet);
   fChain->SetBranchAddress("MET_RefMuon_phi", &MET_RefMuon_phi, &b_MET_RefMuon_phi);
   fChain->SetBranchAddress("MET_RefMuon_et", &MET_RefMuon_et, &b_MET_RefMuon_et);
   fChain->SetBranchAddress("MET_RefMuon_sumet", &MET_RefMuon_sumet, &b_MET_RefMuon_sumet);
   fChain->SetBranchAddress("MET_RefGamma_phi", &MET_RefGamma_phi, &b_MET_RefGamma_phi);
   fChain->SetBranchAddress("MET_RefGamma_et", &MET_RefGamma_et, &b_MET_RefGamma_et);
   fChain->SetBranchAddress("MET_RefGamma_sumet", &MET_RefGamma_sumet, &b_MET_RefGamma_sumet);
   fChain->SetBranchAddress("MET_RefTau_phi", &MET_RefTau_phi, &b_MET_RefTau_phi);
   fChain->SetBranchAddress("MET_RefTau_et", &MET_RefTau_et, &b_MET_RefTau_et);
   fChain->SetBranchAddress("MET_RefTau_sumet", &MET_RefTau_sumet, &b_MET_RefTau_sumet);
   fChain->SetBranchAddress("MET_Track_phi", &MET_Track_phi, &b_MET_Track_phi);
   fChain->SetBranchAddress("MET_Track_et", &MET_Track_et, &b_MET_Track_et);
   fChain->SetBranchAddress("MET_Track_sumet", &MET_Track_sumet, &b_MET_Track_sumet);
   fChain->SetBranchAddress("MET_MuonBoy_phi", &MET_MuonBoy_phi, &b_MET_MuonBoy_phi);
   fChain->SetBranchAddress("MET_MuonBoy_et", &MET_MuonBoy_et, &b_MET_MuonBoy_et);
   fChain->SetBranchAddress("MET_MuonBoy_sumet", &MET_MuonBoy_sumet, &b_MET_MuonBoy_sumet);
   fChain->SetBranchAddress("MET_RefJet_JVF_phi", &MET_RefJet_JVF_phi, &b_MET_RefJet_JVF_phi);
   fChain->SetBranchAddress("MET_RefJet_JVF_et", &MET_RefJet_JVF_et, &b_MET_RefJet_JVF_et);
   fChain->SetBranchAddress("MET_RefJet_JVF_sumet", &MET_RefJet_JVF_sumet, &b_MET_RefJet_JVF_sumet);
   fChain->SetBranchAddress("MET_RefJet_JVFCut_phi", &MET_RefJet_JVFCut_phi, &b_MET_RefJet_JVFCut_phi);
   fChain->SetBranchAddress("MET_RefJet_JVFCut_et", &MET_RefJet_JVFCut_et, &b_MET_RefJet_JVFCut_et);
   fChain->SetBranchAddress("MET_RefJet_JVFCut_sumet", &MET_RefJet_JVFCut_sumet, &b_MET_RefJet_JVFCut_sumet);
   fChain->SetBranchAddress("MET_CellOut_Eflow_STVF_phi", &MET_CellOut_Eflow_STVF_phi, &b_MET_CellOut_Eflow_STVF_phi);
   fChain->SetBranchAddress("MET_CellOut_Eflow_STVF_et", &MET_CellOut_Eflow_STVF_et, &b_MET_CellOut_Eflow_STVF_et);
   fChain->SetBranchAddress("MET_CellOut_Eflow_STVF_sumet", &MET_CellOut_Eflow_STVF_sumet, &b_MET_CellOut_Eflow_STVF_sumet);
   fChain->SetBranchAddress("MET_CellOut_Eflow_JetArea_phi", &MET_CellOut_Eflow_JetArea_phi, &b_MET_CellOut_Eflow_JetArea_phi);
   fChain->SetBranchAddress("MET_CellOut_Eflow_JetArea_et", &MET_CellOut_Eflow_JetArea_et, &b_MET_CellOut_Eflow_JetArea_et);
   fChain->SetBranchAddress("MET_CellOut_Eflow_JetArea_sumet", &MET_CellOut_Eflow_JetArea_sumet, &b_MET_CellOut_Eflow_JetArea_sumet);
   fChain->SetBranchAddress("MET_CellOut_Eflow_JetAreaJVF_phi", &MET_CellOut_Eflow_JetAreaJVF_phi, &b_MET_CellOut_Eflow_JetAreaJVF_phi);
   fChain->SetBranchAddress("MET_CellOut_Eflow_JetAreaJVF_et", &MET_CellOut_Eflow_JetAreaJVF_et, &b_MET_CellOut_Eflow_JetAreaJVF_et);
   fChain->SetBranchAddress("MET_CellOut_Eflow_JetAreaJVF_sumet", &MET_CellOut_Eflow_JetAreaJVF_sumet, &b_MET_CellOut_Eflow_JetAreaJVF_sumet);
   fChain->SetBranchAddress("MET_CellOut_Eflow_JetAreaRhoEta5JVF_phi", &MET_CellOut_Eflow_JetAreaRhoEta5JVF_phi, &b_MET_CellOut_Eflow_JetAreaRhoEta5JVF_phi);
   fChain->SetBranchAddress("MET_CellOut_Eflow_JetAreaRhoEta5JVF_et", &MET_CellOut_Eflow_JetAreaRhoEta5JVF_et, &b_MET_CellOut_Eflow_JetAreaRhoEta5JVF_et);
   fChain->SetBranchAddress("MET_CellOut_Eflow_JetAreaRhoEta5JVF_sumet", &MET_CellOut_Eflow_JetAreaRhoEta5JVF_sumet, &b_MET_CellOut_Eflow_JetAreaRhoEta5JVF_sumet);
   fChain->SetBranchAddress("MET_RefFinal_STVF_phi", &MET_RefFinal_STVF_phi, &b_MET_RefFinal_STVF_phi);
   fChain->SetBranchAddress("MET_RefFinal_STVF_et", &MET_RefFinal_STVF_et, &b_MET_RefFinal_STVF_et);
   fChain->SetBranchAddress("MET_RefFinal_STVF_sumet", &MET_RefFinal_STVF_sumet, &b_MET_RefFinal_STVF_sumet);
   fChain->SetBranchAddress("MET_CellOut_Eflow_phi", &MET_CellOut_Eflow_phi, &b_MET_CellOut_Eflow_phi);
   fChain->SetBranchAddress("MET_CellOut_Eflow_et", &MET_CellOut_Eflow_et, &b_MET_CellOut_Eflow_et);
   fChain->SetBranchAddress("MET_CellOut_Eflow_sumet", &MET_CellOut_Eflow_sumet, &b_MET_CellOut_Eflow_sumet);
   fChain->SetBranchAddress("MET_RefMuon_Track_phi", &MET_RefMuon_Track_phi, &b_MET_RefMuon_Track_phi);
   fChain->SetBranchAddress("MET_RefMuon_Track_et", &MET_RefMuon_Track_et, &b_MET_RefMuon_Track_et);
   fChain->SetBranchAddress("MET_RefMuon_Track_sumet", &MET_RefMuon_Track_sumet, &b_MET_RefMuon_Track_sumet);
   fChain->SetBranchAddress("MET_Topo_phi", &MET_Topo_phi, &b_MET_Topo_phi);
   fChain->SetBranchAddress("MET_Topo_et", &MET_Topo_et, &b_MET_Topo_et);
   fChain->SetBranchAddress("MET_Topo_sumet", &MET_Topo_sumet, &b_MET_Topo_sumet);
   fChain->SetBranchAddress("MET_Truth_NonInt_phi", &MET_Truth_NonInt_phi, &b_MET_Truth_NonInt_phi);
   fChain->SetBranchAddress("MET_Truth_NonInt_et", &MET_Truth_NonInt_et, &b_MET_Truth_NonInt_et);
   fChain->SetBranchAddress("MET_Truth_NonInt_sumet", &MET_Truth_NonInt_sumet, &b_MET_Truth_NonInt_sumet);
   fChain->SetBranchAddress("EF_2e12Tvh_loose1", &EF_2e12Tvh_loose1, &b_EF_2e12Tvh_loose1);
   fChain->SetBranchAddress("EF_e12Tvh_medium1_mu8", &EF_e12Tvh_medium1_mu8, &b_EF_e12Tvh_medium1_mu8);
   fChain->SetBranchAddress("EF_e24vhi_medium1", &EF_e24vhi_medium1, &b_EF_e24vhi_medium1);
   fChain->SetBranchAddress("EF_e60_medium1", &EF_e60_medium1, &b_EF_e60_medium1);
   fChain->SetBranchAddress("EF_mu18_tight_mu8_EFFS", &EF_mu18_tight_mu8_EFFS, &b_EF_mu18_tight_mu8_EFFS);
   fChain->SetBranchAddress("EF_mu24i_tight", &EF_mu24i_tight, &b_EF_mu24i_tight);
   fChain->SetBranchAddress("EF_mu36_tight", &EF_mu36_tight, &b_EF_mu36_tight);
   fChain->SetBranchAddress("EF_2mu13", &EF_2mu13, &b_EF_2mu13);
   fChain->SetBranchAddress("top_hfor_type", &top_hfor_type, &b_top_hfor_type);
   fChain->SetBranchAddress("m_jet_n", &m_jet_n, &b_m_jet_n);
   fChain->SetBranchAddress("m_jet_E", &m_jet_E, &b_m_jet_E);
   fChain->SetBranchAddress("m_jet_pt", &m_jet_pt, &b_m_jet_pt);
   fChain->SetBranchAddress("m_jet_eta", &m_jet_eta, &b_m_jet_eta);
   fChain->SetBranchAddress("m_jet_phi", &m_jet_phi, &b_m_jet_phi);
   fChain->SetBranchAddress("m_jet_sumPtTrk", &m_jet_sumPtTrk, &b_m_jet_sumPtTrk);
   fChain->SetBranchAddress("m_jet_jvtxf", &m_jet_jvtxf, &b_m_jet_jvtxf);
   fChain->SetBranchAddress("m_jet_flavor_weight_MV1", &m_jet_flavor_weight_MV1, &b_m_jet_flavor_weight_MV1);
   fChain->SetBranchAddress("m_jet_flavor_truth_label", &m_jet_flavor_truth_label, &b_m_jet_flavor_truth_label);
   fChain->SetBranchAddress("m_jet_nTrk_pv0_500MeV", &m_jet_nTrk_pv0_500MeV, &b_m_jet_nTrk_pv0_500MeV);
   fChain->SetBranchAddress("m_vxp_n", &m_vxp_n, &b_m_vxp_n);
   fChain->SetBranchAddress("m_vxp_nTracks", &m_vxp_nTracks, &b_m_vxp_nTracks);
   fChain->SetBranchAddress("m_tau_n", &m_tau_n, &b_m_tau_n);
   fChain->SetBranchAddress("m_tau_pt", &m_tau_pt, &b_m_tau_pt);
   fChain->SetBranchAddress("m_tau_eta", &m_tau_eta, &b_m_tau_eta);
   fChain->SetBranchAddress("m_tau_phi", &m_tau_phi, &b_m_tau_phi);
   fChain->SetBranchAddress("m_tau_charge", &m_tau_charge, &b_m_tau_charge);
   fChain->SetBranchAddress("m_tau_BDTJetScore", &m_tau_BDTJetScore, &b_m_tau_BDTJetScore);
   fChain->SetBranchAddress("m_tau_BDTEleScore", &m_tau_BDTEleScore, &b_m_tau_BDTEleScore);
   fChain->SetBranchAddress("m_tau_muonVeto", &m_tau_muonVeto, &b_m_tau_muonVeto);
   fChain->SetBranchAddress("m_tau_JetBDTSigLoose", &m_tau_JetBDTSigLoose, &b_m_tau_JetBDTSigLoose);
   fChain->SetBranchAddress("m_tau_JetBDTSigMedium", &m_tau_JetBDTSigMedium, &b_m_tau_JetBDTSigMedium);
   fChain->SetBranchAddress("m_tau_JetBDTSigTight", &m_tau_JetBDTSigTight, &b_m_tau_JetBDTSigTight);
   fChain->SetBranchAddress("m_tau_EleBDTLoose", &m_tau_EleBDTLoose, &b_m_tau_EleBDTLoose);
   fChain->SetBranchAddress("m_tau_EleBDTMedium", &m_tau_EleBDTMedium, &b_m_tau_EleBDTMedium);
   fChain->SetBranchAddress("m_tau_EleBDTTight", &m_tau_EleBDTTight, &b_m_tau_EleBDTTight);
   fChain->SetBranchAddress("m_tau_author", &m_tau_author, &b_m_tau_author);
   fChain->SetBranchAddress("m_tau_numTrack", &m_tau_numTrack, &b_m_tau_numTrack);
   fChain->SetBranchAddress("m_mcevt_pdf_id1", &m_mcevt_pdf_id1, &b_m_mcevt_pdf_id1);
   fChain->SetBranchAddress("m_mcevt_pdf_id2", &m_mcevt_pdf_id2, &b_m_mcevt_pdf_id2);
   fChain->SetBranchAddress("m_mcevt_pdf_x1", &m_mcevt_pdf_x1, &b_m_mcevt_pdf_x1);
   fChain->SetBranchAddress("m_mcevt_pdf_x2", &m_mcevt_pdf_x2, &b_m_mcevt_pdf_x2);
   fChain->SetBranchAddress("m_mcevt_pdf_scale", &m_mcevt_pdf_scale, &b_m_mcevt_pdf_scale);
   fChain->SetBranchAddress("m_jetTruth_n", &m_jetTruth_n, &b_m_jetTruth_n);
   fChain->SetBranchAddress("m_jetTruth_E", &m_jetTruth_E, &b_m_jetTruth_E);
   fChain->SetBranchAddress("m_jetTruth_pt", &m_jetTruth_pt, &b_m_jetTruth_pt);
   fChain->SetBranchAddress("m_jetTruth_eta", &m_jetTruth_eta, &b_m_jetTruth_eta);
   fChain->SetBranchAddress("m_jetTruth_phi", &m_jetTruth_phi, &b_m_jetTruth_phi);
   Notify();
}

Bool_t HWWtth::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void HWWtth::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t HWWtth::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef HWWtth_cxx
