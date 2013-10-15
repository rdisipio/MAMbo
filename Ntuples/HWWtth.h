//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Tue Oct 15 12:42:26 2013 by ROOT version 5.34/04
// from TTree HWWTree/ttH to leptons Ntuple
// found on file: /home/ATLAS/disipio/LOCAL_DISK/ntuples/ttH/minintuples/116108.root
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

using namespace std;

// Fixed size dimensions of array or collections stored in the TTree if any.

class HWWtth {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   Float_t         higgsPt;
   Int_t           isBlinded;
   Bool_t          hasBtaggedJets;
   Float_t         Mll;
   Float_t         MT;
   Float_t         MTrans;
   Float_t         gammaStar_weight;
   Float_t         m_gammaStar;
   Float_t         Ptll;
   Float_t         DPhill;
   Float_t         DRll;
   Float_t         DEtall;
   Float_t         Yll;
   Float_t         Pttot;
   Float_t         Mjj;
   Float_t         Ptjj;
   Float_t         DPhijj;
   Float_t         DRjj;
   Float_t         DEtajj;
   Float_t         DYjj;
   Float_t         Mtt;
   Float_t         x1;
   Float_t         x2;
   Int_t           RandomRunNumber;
   Double_t        WgStarEventWeight;
   Double_t        WgStarEventWeightError;
   Bool_t          overlapWZ;
   Bool_t          didEJoverlap;
   Bool_t          didMJoverlap;
   Bool_t          didEEoverlap;
   Bool_t          didEMoverlap;
   Float_t         lepPtSum;
   Float_t         DPhiSubLeadLepMET;
   Float_t         DPhiLeadLepMET;
   Float_t         MinDPhi;
   Float_t         MinDPhi_noJVF;
   Float_t         MET;
   Float_t         MET_x;
   Float_t         MET_y;
   Float_t         MET_phi;
   Float_t         METRel;
   Float_t         METRel_x;
   Float_t         METRel_y;
   Float_t         METRel_noJets;
   Float_t         MET_default;
   Float_t         MET_default_x;
   Float_t         MET_default_y;
   Float_t         DPhiSubLeadLepMET_STVF;
   Float_t         DPhiLeadLepMET_STVF;
   Float_t         MinDPhi_STVF;
   Float_t         MinDPhi_noJVF_STVF;
   Float_t         MT_STVF;
   Float_t         MTrans_STVF;
   Float_t         Mtt_STVF;
   Float_t         x1_STVF;
   Float_t         x2_STVF;
   Float_t         Pttot_STVF;
   Float_t         MET_STVF;
   Float_t         MET_x_STVF;
   Float_t         MET_y_STVF;
   Float_t         MET_phi_STVF;
   Float_t         METRel_STVF;
   Float_t         METRel_x_STVF;
   Float_t         METRel_y_STVF;
   Float_t         METRel_noJets_STVF;
   Float_t         MET_default_STVF;
   Float_t         MET_default_x_STVF;
   Float_t         MET_default_y_STVF;
   Float_t         MET_TrackHWW;
   Float_t         MET_x_TrackHWW;
   Float_t         MET_y_TrackHWW;
   Float_t         MET_phi_TrackHWW;
   Float_t         MinDPhi_TrackHWW;
   Float_t         MinDPhi_noJVF_TrackHWW;
   Float_t         METRel_TrackHWW;
   Float_t         METRel_x_TrackHWW;
   Float_t         METRel_y_TrackHWW;
   Float_t         DPhi_CaloTrackHWW;
   Float_t         MT_TrackHWW;
   Float_t         PtTrack_TrackHWW;
   Float_t         MTrans_TrackHWW;
   Float_t         Mtt_TrackHWW;
   Float_t         x1_TrackHWW;
   Float_t         x2_TrackHWW;
   Float_t         DPhiSubLeadLepMET_TrackHWW;
   Float_t         DPhiLeadLepMET_TrackHWW;
   Float_t         Pttot_TrackHWW;
   Float_t         HighTrackPt_TrackHWW;
   Int_t           MET_TrackHWW_Nmu;
   Int_t           MET_TrackHWW_NmuMatched;
   Int_t           MET_TrackHWW_Nel;
   Int_t           MET_TrackHWW_NelMatched;
   Int_t           MET_TrackHWW_Ntracks;
   Float_t         lepPtID0;
   Float_t         lepPtME0;
   Float_t         lepID0;
   Float_t         lepPt0;
   Float_t         lepPx0;
   Float_t         lepPy0;
   Float_t         lepPz0;
   Float_t         lepE0;
   Float_t         lepEta0;
   Float_t         lepPhi0;
   Float_t         lepEtcone20_0;
   Float_t         lepEtcone30_0;
   Float_t         lepEtcone40_0;
   Float_t         lepPtcone20_0;
   Float_t         lepPtcone30_0;
   Float_t         lepPtcone40_0;
   Float_t         lepNucone20_0;
   Float_t         lepNucone30_0;
   Float_t         lepNucone40_0;
   Float_t         lepz0PV0;
   Float_t         lepsigd0PV0;
   Float_t         lepD0_0;
   Float_t         lepZ0SinTheta_0;
   Float_t         lepMagD0_0;
   Int_t           lep_isTightPP0;
   Int_t           lep_isMediumPP0;
   Int_t           lep_isLoosePP0;
   Int_t           lep_isMultiLepton0;
   Int_t           lep_isVeryTightLH0;
   Int_t           lep_isTightLH0;
   Int_t           lep_isMediumLH0;
   Int_t           lep_isLooseLH0;
   Int_t           lep_isLooseBLPixLH0;
   Int_t           lep_isVeryLooseLH0;
   Int_t           lep_isCombined0;
   Int_t           lep_isTight0;
   Int_t           lep_isMedium0;
   Int_t           lep_isLoose0;
   Int_t           lep_isHSG3Clear0;
   Int_t           lep_isHSG3IsoClear0;
   Int_t           lep_isTrigMatch0;
   Bool_t          lep_isFakable0;
   Float_t         BLayer_hit0;
   Float_t         conv0;
   Int_t           lepAuthor0;
   Double_t        lepTrigSF0EventWeight;
   Double_t        lepTrigSF0Error;
   Double_t        lepSF0RecoEventWeight;
   Double_t        lepSF0IdEventWeight;
   Double_t        lepSF0IsoEventWeight;
   Double_t        lepSF0ErrorIso;
   Double_t        lepSF0ErrorSys;
   Double_t        lepSF0RecoError;
   Double_t        lepSF0RecoErrorSys;
   Double_t        lepSF0IdError;
   Double_t        lepSF0IsoError;
   Bool_t          lepMatch_EF_mu24i_tight_0;
   Bool_t          lepMatch_EF_mu36_tight_0;
   Bool_t          lepMatch_EF_e24vhi_medium1_0;
   Bool_t          lepMatch_EF_e60_medium1_0;
   Bool_t          lepMatch_EF_mu24_tight_0;
   Bool_t          lepMatch_EF_mu40_MSonly_barrel_tight_0;
   Bool_t          lepMatch_EF_mu18_tight_0;
   Bool_t          lepMatch_EF_mu8_EFFS_0;
   Bool_t          lepMatch_EF_mu13_0;
   Bool_t          lepMatch_EF_e22vh_medium1_0;
   Bool_t          lepMatch_EF_e45_medium1_0;
   Bool_t          lepMatch_EF_e12Tvh_loose1_0;
   Float_t         lepPtID1;
   Float_t         lepPtME1;
   Float_t         lepID1;
   Float_t         lepPt1;
   Float_t         lepPx1;
   Float_t         lepPy1;
   Float_t         lepPz1;
   Float_t         lepE1;
   Float_t         lepEta1;
   Float_t         lepPhi1;
   Float_t         lepEtcone20_1;
   Float_t         lepEtcone30_1;
   Float_t         lepEtcone40_1;
   Float_t         lepPtcone20_1;
   Float_t         lepPtcone30_1;
   Float_t         lepPtcone40_1;
   Float_t         lepNucone20_1;
   Float_t         lepNucone30_1;
   Float_t         lepNucone40_1;
   Float_t         lepz0PV1;
   Float_t         lepsigd0PV1;
   Float_t         lepD0_1;
   Float_t         lepZ0SinTheta_1;
   Float_t         lepMagD0_1;
   Int_t           lep_isTightPP1;
   Int_t           lep_isMediumPP1;
   Int_t           lep_isLoosePP1;
   Int_t           lep_isMultiLepton1;
   Int_t           lep_isVeryTightLH1;
   Int_t           lep_isTightLH1;
   Int_t           lep_isMediumLH1;
   Int_t           lep_isLooseLH1;
   Int_t           lep_isLooseBLPixLH1;
   Int_t           lep_isVeryLooseLH1;
   Int_t           lep_isCombined1;
   Int_t           lep_isTight1;
   Int_t           lep_isMedium1;
   Int_t           lep_isLoose1;
   Int_t           lep_isHSG3Clear1;
   Int_t           lep_isHSG3IsoClear1;
   Int_t           lep_isTrigMatch1;
   Bool_t          lep_isFakable1;
   Float_t         BLayer_hit1;
   Float_t         conv1;
   Int_t           lepAuthor1;
   Double_t        lepTrigSF1EventWeight;
   Double_t        lepTrigSF1Error;
   Double_t        lepSF1RecoEventWeight;
   Double_t        lepSF1IdEventWeight;
   Double_t        lepSF1IsoEventWeight;
   Double_t        lepSF1ErrorIso;
   Double_t        lepSF1ErrorSys;
   Double_t        lepSF1RecoError;
   Double_t        lepSF1RecoErrorSys;
   Double_t        lepSF1IdError;
   Double_t        lepSF1IsoError;
   Bool_t          lepMatch_EF_mu24i_tight_1;
   Bool_t          lepMatch_EF_mu36_tight_1;
   Bool_t          lepMatch_EF_e24vhi_medium1_1;
   Bool_t          lepMatch_EF_e60_medium1_1;
   Bool_t          lepMatch_EF_mu24_tight_1;
   Bool_t          lepMatch_EF_mu40_MSonly_barrel_tight_1;
   Bool_t          lepMatch_EF_mu18_tight_1;
   Bool_t          lepMatch_EF_mu8_EFFS_1;
   Bool_t          lepMatch_EF_mu13_1;
   Bool_t          lepMatch_EF_e22vh_medium1_1;
   Bool_t          lepMatch_EF_e45_medium1_1;
   Bool_t          lepMatch_EF_e12Tvh_loose1_1;
   Float_t         lepPtID2;
   Float_t         lepPtME2;
   Float_t         lepID2;
   Float_t         lepPt2;
   Float_t         lepPx2;
   Float_t         lepPy2;
   Float_t         lepPz2;
   Float_t         lepE2;
   Float_t         lepEta2;
   Float_t         lepPhi2;
   Float_t         lepEtcone20_2;
   Float_t         lepEtcone30_2;
   Float_t         lepEtcone40_2;
   Float_t         lepPtcone20_2;
   Float_t         lepPtcone30_2;
   Float_t         lepPtcone40_2;
   Float_t         lepNucone20_2;
   Float_t         lepNucone30_2;
   Float_t         lepNucone40_2;
   Float_t         lepz0PV2;
   Float_t         lepsigd0PV2;
   Float_t         lepD0_2;
   Float_t         lepZ0SinTheta_2;
   Float_t         lepMagD0_2;
   Int_t           lep_isTightPP2;
   Int_t           lep_isMediumPP2;
   Int_t           lep_isLoosePP2;
   Int_t           lep_isMultiLepton2;
   Int_t           lep_isVeryTightLH2;
   Int_t           lep_isTightLH2;
   Int_t           lep_isMediumLH2;
   Int_t           lep_isLooseLH2;
   Int_t           lep_isLooseBLPixLH2;
   Int_t           lep_isVeryLooseLH2;
   Int_t           lep_isCombined2;
   Int_t           lep_isTight2;
   Int_t           lep_isMedium2;
   Int_t           lep_isLoose2;
   Int_t           lep_isHSG3Clear2;
   Int_t           lep_isHSG3IsoClear2;
   Int_t           lep_isTrigMatch2;
   Bool_t          lep_isFakable2;
   Float_t         BLayer_hit2;
   Float_t         conv2;
   Int_t           lepAuthor2;
   Double_t        lepTrigSF2EventWeight;
   Double_t        lepTrigSF2Error;
   Double_t        lepSF2RecoEventWeight;
   Double_t        lepSF2IdEventWeight;
   Double_t        lepSF2IsoEventWeight;
   Double_t        lepSF2ErrorIso;
   Double_t        lepSF2ErrorSys;
   Double_t        lepSF2RecoError;
   Double_t        lepSF2RecoErrorSys;
   Double_t        lepSF2IdError;
   Double_t        lepSF2IsoError;
   Bool_t          lepMatch_EF_mu24i_tight_2;
   Bool_t          lepMatch_EF_mu36_tight_2;
   Bool_t          lepMatch_EF_e24vhi_medium1_2;
   Bool_t          lepMatch_EF_e60_medium1_2;
   Bool_t          lepMatch_EF_mu24_tight_2;
   Bool_t          lepMatch_EF_mu40_MSonly_barrel_tight_2;
   Bool_t          lepMatch_EF_mu18_tight_2;
   Bool_t          lepMatch_EF_mu8_EFFS_2;
   Bool_t          lepMatch_EF_mu13_2;
   Bool_t          lepMatch_EF_e22vh_medium1_2;
   Bool_t          lepMatch_EF_e45_medium1_2;
   Bool_t          lepMatch_EF_e12Tvh_loose1_2;
   Float_t         lepPtID3;
   Float_t         lepPtME3;
   Float_t         lepID3;
   Float_t         lepPt3;
   Float_t         lepPx3;
   Float_t         lepPy3;
   Float_t         lepPz3;
   Float_t         lepE3;
   Float_t         lepEta3;
   Float_t         lepPhi3;
   Float_t         lepEtcone20_3;
   Float_t         lepEtcone30_3;
   Float_t         lepEtcone40_3;
   Float_t         lepPtcone20_3;
   Float_t         lepPtcone30_3;
   Float_t         lepPtcone40_3;
   Float_t         lepNucone20_3;
   Float_t         lepNucone30_3;
   Float_t         lepNucone40_3;
   Float_t         lepz0PV3;
   Float_t         lepsigd0PV3;
   Float_t         lepD0_3;
   Float_t         lepZ0SinTheta_3;
   Float_t         lepMagD0_3;
   Int_t           lep_isTightPP3;
   Int_t           lep_isMediumPP3;
   Int_t           lep_isLoosePP3;
   Int_t           lep_isMultiLepton3;
   Int_t           lep_isVeryTightLH3;
   Int_t           lep_isTightLH3;
   Int_t           lep_isMediumLH3;
   Int_t           lep_isLooseLH3;
   Int_t           lep_isLooseBLPixLH3;
   Int_t           lep_isVeryLooseLH3;
   Int_t           lep_isCombined3;
   Int_t           lep_isTight3;
   Int_t           lep_isMedium3;
   Int_t           lep_isLoose3;
   Int_t           lep_isHSG3Clear3;
   Int_t           lep_isHSG3IsoClear3;
   Int_t           lep_isTrigMatch3;
   Bool_t          lep_isFakable3;
   Float_t         BLayer_hit3;
   Float_t         conv3;
   Int_t           lepAuthor3;
   Double_t        lepTrigSF3EventWeight;
   Double_t        lepTrigSF3Error;
   Double_t        lepSF3RecoEventWeight;
   Double_t        lepSF3IdEventWeight;
   Double_t        lepSF3IsoEventWeight;
   Double_t        lepSF3ErrorIso;
   Double_t        lepSF3ErrorSys;
   Double_t        lepSF3RecoError;
   Double_t        lepSF3RecoErrorSys;
   Double_t        lepSF3IdError;
   Double_t        lepSF3IsoError;
   Bool_t          lepMatch_EF_mu24i_tight_3;
   Bool_t          lepMatch_EF_mu36_tight_3;
   Bool_t          lepMatch_EF_e24vhi_medium1_3;
   Bool_t          lepMatch_EF_e60_medium1_3;
   Bool_t          lepMatch_EF_mu24_tight_3;
   Bool_t          lepMatch_EF_mu40_MSonly_barrel_tight_3;
   Bool_t          lepMatch_EF_mu18_tight_3;
   Bool_t          lepMatch_EF_mu8_EFFS_3;
   Bool_t          lepMatch_EF_mu13_3;
   Bool_t          lepMatch_EF_e22vh_medium1_3;
   Bool_t          lepMatch_EF_e45_medium1_3;
   Bool_t          lepMatch_EF_e12Tvh_loose1_3;
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
   Double_t        higgsPtEventWeight;
   Double_t        higgsMEventWeight;
   Double_t        higgsPtError;
   Double_t        mcEventWeight;
   Double_t        mcWeightOrg;
   Double_t        trigEventWeight;
   Double_t        lepTrigSFEventWeight;
   Double_t        lepTrigSFEventWeightUp;
   Double_t        lepTrigSFEventWeightDown;
   Double_t        lepSF0EventWeight;
   Double_t        lepSF1EventWeight;
   Double_t        lepSF0Error;
   Double_t        lepSF1Error;
   Double_t        MV1_70_EventWeight;
   Double_t        MV1_80_EventWeight;
   Double_t        MV120_80_EventWeight;
   Double_t        MV120_70_EventWeight;
   Double_t        MV1_70_BJetWeight;
   Double_t        MV1_80_BJetWeight;
   Double_t        MV120_80_BJetWeight;
   Double_t        MV120_70_BJetWeight;
   Double_t        MV1_70_CTJetWeight;
   Double_t        MV1_80_CTJetWeight;
   Double_t        MV120_80_CTJetWeight;
   Double_t        MV120_70_CTJetWeight;
   Double_t        MV1_70_MisTagWeight;
   Double_t        MV1_80_MisTagWeight;
   Double_t        MV120_80_MisTagWeight;
   Double_t        MV120_70_MisTagWeight;
   Double_t        MV1_70_BJetWeightUp;
   Double_t        MV1_80_BJetWeightUp;
   Double_t        MV120_80_BJetWeightUp;
   Double_t        MV120_70_BJetWeightUp;
   Double_t        MV1_70_CTJetWeightUp;
   Double_t        MV1_80_CTJetWeightUp;
   Double_t        MV120_80_CTJetWeightUp;
   Double_t        MV120_70_CTJetWeightUp;
   Double_t        MV1_70_MisTagWeightUp;
   Double_t        MV1_80_MisTagWeightUp;
   Double_t        MV120_80_MisTagWeightUp;
   Double_t        MV120_70_MisTagWeightUp;
   Double_t        MV1_70_BJetWeightDown;
   Double_t        MV1_80_BJetWeightDown;
   Double_t        MV120_80_BJetWeightDown;
   Double_t        MV120_70_BJetWeightDown;
   Double_t        MV1_70_CTJetWeightDown;
   Double_t        MV1_80_CTJetWeightDown;
   Double_t        MV120_80_CTJetWeightDown;
   Double_t        MV120_70_CTJetWeightDown;
   Double_t        MV1_70_MisTagWeightDown;
   Double_t        MV1_80_MisTagWeightDown;
   Double_t        MV120_80_MisTagWeightDown;
   Double_t        MV120_70_MisTagWeightDown;
   Double_t        MV1_80_BJetWeightEV_1_Up;
   Double_t        MV1_80_BJetWeightEV_2_Up;
   Double_t        MV1_80_BJetWeightEV_3_Up;
   Double_t        MV1_80_BJetWeightEV_4_Up;
   Double_t        MV1_80_BJetWeightEV_5_Up;
   Double_t        MV1_80_BJetWeightEV_6_Up;
   Double_t        MV1_80_BJetWeightEV_7_Up;
   Double_t        MV1_80_BJetWeightEV_8_Up;
   Double_t        MV1_80_BJetWeightEV_9_Up;
   Double_t        MV1_80_BJetWeightEV_1_Down;
   Double_t        MV1_80_BJetWeightEV_2_Down;
   Double_t        MV1_80_BJetWeightEV_3_Down;
   Double_t        MV1_80_BJetWeightEV_4_Down;
   Double_t        MV1_80_BJetWeightEV_5_Down;
   Double_t        MV1_80_BJetWeightEV_6_Down;
   Double_t        MV1_80_BJetWeightEV_7_Down;
   Double_t        MV1_80_BJetWeightEV_8_Down;
   Double_t        MV1_80_BJetWeightEV_9_Down;
   Int_t           nJets_Pt25_MV1_70;
   Int_t           nJets_Pt25_MV1_80;
   Int_t           nJets_Pt20_MV1_70;
   Int_t           nJets_Pt20_MV1_80;
   Int_t           nJets_Pt20;
   Float_t         nJetsProbing_MV1_80;
   Float_t         nJetsProbing_MV1_70;
   Int_t           Nvxp;
   Float_t         centralJetVeto_leadPt;
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
   Int_t           dilep_type;
   Bool_t          isEEE;
   Bool_t          isEEM;
   Bool_t          isMME;
   Bool_t          isMMM;
   Float_t         Mll01;
   Float_t         Mll02;
   Float_t         Mll12;
   Float_t         Mlll;
   Float_t         MT01;
   Float_t         MT02;
   Float_t         MT12;
   Float_t         MTrans01;
   Float_t         MTrans02;
   Float_t         MTrans12;
   Float_t         Ptll01;
   Float_t         Ptll02;
   Float_t         Ptll12;
   Float_t         DPhill01;
   Float_t         DPhill02;
   Float_t         DPhill12;
   Float_t         DRll01;
   Float_t         DRll02;
   Float_t         DRll12;
   Float_t         DR;
   Float_t         DR012;
   Float_t         DR102;
   Float_t         DR201;
   Float_t         DPhi;
   Float_t         DPhi012;
   Float_t         DPhi102;
   Float_t         DPhi201;
   Float_t         DEtall01;
   Float_t         DEtall02;
   Float_t         DEtall12;
   Float_t         Yll01;
   Float_t         Yll02;
   Float_t         Yll12;
   Float_t         Mtt01;
   Float_t         Mtt02;
   Float_t         Mtt12;
   Float_t         x1_01;
   Float_t         x1_02;
   Float_t         x1_12;
   Float_t         x2_01;
   Float_t         x2_02;
   Float_t         x2_12;
   Float_t         DPhiThirdLepMET;
   Float_t         DPhiThirdLepMET_STVF;
   Float_t         MT_STVF01;
   Float_t         MT_STVF02;
   Float_t         MT_STVF12;
   Float_t         MTrans_STVF01;
   Float_t         MTrans_STVF02;
   Float_t         MTrans_STVF12;
   Float_t         Mtt_STVF01;
   Float_t         Mtt_STVF02;
   Float_t         Mtt_STVF12;
   Float_t         x1_STVF_01;
   Float_t         x1_STVF_02;
   Float_t         x1_STVF_12;
   Float_t         x2_STVF_01;
   Float_t         x2_STVF_02;
   Float_t         x2_STVF_12;
   Float_t         MT_TrackHWW01;
   Float_t         MT_TrackHWW02;
   Float_t         MT_TrackHWW12;
   Float_t         MTrans_TrackHWW01;
   Float_t         MTrans_TrackHWW02;
   Float_t         MTrans_TrackHWW12;
   Float_t         Mtt_TrackHWW01;
   Float_t         Mtt_TrackHWW02;
   Float_t         Mtt_TrackHWW12;
   Float_t         x1_TrackHWW_01;
   Float_t         x1_TrackHWW_02;
   Float_t         x1_TrackHWW_12;
   Float_t         x2_TrackHWW_01;
   Float_t         x2_TrackHWW_02;
   Float_t         x2_TrackHWW_12;
   Float_t         DPhiThirdLepMET_TrackHWW;
   Float_t         DRlep2jet;
   Double_t        lepSF2EventWeight;
   Double_t        lepSF2Error;
   Bool_t          isEEEE;
   Bool_t          isEEEM;
   Bool_t          isEEMM;
   Bool_t          isEMMM;
   Bool_t          isMMMM;
   Float_t         Mll03;
   Float_t         Mll13;
   Float_t         Mll23;
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
   Float_t         MT03;
   Float_t         MT13;
   Float_t         MT23;
   Float_t         MTrans03;
   Float_t         MTrans13;
   Float_t         MTrans23;
   Float_t         x1_03;
   Float_t         x1_13;
   Float_t         x1_23;
   Float_t         x2_03;
   Float_t         x2_13;
   Float_t         x2_23;
   Float_t         Mtt03;
   Float_t         Mtt13;
   Float_t         Mtt23;
   Float_t         MT_STVF03;
   Float_t         MT_STVF13;
   Float_t         MT_STVF23;
   Float_t         MTrans_STVF03;
   Float_t         MTrans_STVF13;
   Float_t         MTrans_STVF23;
   Float_t         Mtt_STVF03;
   Float_t         Mtt_STVF13;
   Float_t         Mtt_STVF23;
   Float_t         x1_STVF_03;
   Float_t         x1_STVF_13;
   Float_t         x1_STVF_23;
   Float_t         x2_STVF_03;
   Float_t         x2_STVF_13;
   Float_t         x2_STVF_23;
   Float_t         MT_TrackHWW03;
   Float_t         MT_TrackHWW13;
   Float_t         MT_TrackHWW23;
   Float_t         MTrans_TrackHWW03;
   Float_t         MTrans_TrackHWW13;
   Float_t         MTrans_TrackHWW23;
   Float_t         Mtt_TrackHWW03;
   Float_t         Mtt_TrackHWW13;
   Float_t         Mtt_TrackHWW23;
   Float_t         x1_TrackHWW_03;
   Float_t         x1_TrackHWW_13;
   Float_t         x1_TrackHWW_23;
   Float_t         x2_TrackHWW_03;
   Float_t         x2_TrackHWW_13;
   Float_t         x2_TrackHWW_23;
   Float_t         DRlep3jet;
   Double_t        lepSF3EventWeight;
   Double_t        lepSF3Error;
   vector<float>   *lepton_Pt;
   vector<float>   *lepton_Eta;
   vector<float>   *lepton_Phi;
   vector<float>   *lepton_ID;
   vector<float>   *lepton_Etcone20;
   vector<float>   *lepton_Etcone30;
   vector<float>   *lepton_Etcone40;
 //  vector<float>   *lepton_ID;
   vector<float>   *lepton_Ptcone30;
   vector<float>   *lepton_Ptcone40;
   vector<float>   *lepton_z0PV;
   vector<float>   *lepton_sigd0PV;
   vector<float>   *lepton_D0;
   vector<float>   *lepton_Z0SinTheta;
   vector<int>     *lepton_isTightPP;
   vector<int>     *lepton_isMediumPP;
   vector<int>     *lepton_isLoosePP;
   vector<int>     *lepton_isMultiLepton;
   vector<int>     *lepton_isVeryTightLH;
   vector<int>     *lepton_isTightLH;
   vector<int>     *lepton_isMediumLH;
   vector<int>     *lepton_isLooseLH;
   vector<int>     *lepton_isLooseBLPixLH;
   vector<int>     *lepton_isVeryLooseLH;
   vector<int>     *lepton_isCombined;
   vector<int>     *lepton_isTight;
   vector<int>     *lepton_isMedium;
   vector<int>     *lepton_isLoose;
   vector<float>   *lepton_BLayer_hit;
   vector<float>   *lepton_conv;
   vector<int>     *lepton_Author;
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
   Int_t           top_hfor_type;
   Int_t           m_jet_n;
   vector<float>   *m_jet_E;
   vector<float>   *m_jet_pt;
   vector<float>   *m_jet_eta;
   vector<float>   *m_jet_phi;
   vector<float>   *m_jet_LArQuality;
   vector<float>   *m_jet_sumPtTrk;
   vector<float>   *m_jet_emfrac;
   vector<float>   *m_jet_jvtxf;
   vector<float>   *m_jet_flavor_weight_MV1;
   vector<int>     *m_jet_flavor_truth_label;
   Int_t           m_vxp_n;
   vector<int>     *m_vxp_nTracks;
   vector<int>     *m_mcevt_pdf_id1;
   vector<int>     *m_mcevt_pdf_id2;
   vector<double>  *m_mcevt_pdf_x1;
   vector<double>  *m_mcevt_pdf_x2;
   vector<double>  *m_mcevt_pdf_scale;
   Int_t           m_truth_n;
   vector<float>   *m_truth_pt;
   vector<float>   *m_truth_m;
   vector<float>   *m_truth_eta;
   vector<float>   *m_truth_phi;
   vector<int>     *m_truth_status;
   vector<int>     *m_truth_pdgId;
   Int_t           m_jetTruth_n;
   vector<float>   *m_jetTruth_E;
   vector<float>   *m_jetTruth_pt;
   vector<float>   *m_jetTruth_eta;
   vector<float>   *m_jetTruth_phi;

   // List of branches
   TBranch        *b_higgsPt;   //!
   TBranch        *b_isBlinded;   //!
   TBranch        *b_hasBtaggedJets;   //!
   TBranch        *b_Mll;   //!
   TBranch        *b_MT;   //!
   TBranch        *b_MTrans;   //!
   TBranch        *b_gammaStar_weight;   //!
   TBranch        *b_m_gammaStar;   //!
   TBranch        *b_Ptll;   //!
   TBranch        *b_DPhill;   //!
   TBranch        *b_DRll;   //!
   TBranch        *b_DEtall;   //!
   TBranch        *b_Yll;   //!
   TBranch        *b_Pttot;   //!
   TBranch        *b_Mjj;   //!
   TBranch        *b_Ptjj;   //!
   TBranch        *b_DPhijj;   //!
   TBranch        *b_DRjj;   //!
   TBranch        *b_DEtajj;   //!
   TBranch        *b_DYjj;   //!
   TBranch        *b_Mtt;   //!
   TBranch        *b_x1;   //!
   TBranch        *b_x2;   //!
   TBranch        *b_RandomRunNumber;   //!
   TBranch        *b_WgStarEventWeight;   //!
   TBranch        *b_WgStarEventWeightError;   //!
   TBranch        *b_overlapWZ;   //!
   TBranch        *b_didEJoverlap;   //!
   TBranch        *b_didMJoverlap;   //!
   TBranch        *b_didEEoverlap;   //!
   TBranch        *b_didEMoverlap;   //!
   TBranch        *b_lepPtSum;   //!
   TBranch        *b_DPhiSubLeadLepMET;   //!
   TBranch        *b_DPhiLeadLepMET;   //!
   TBranch        *b_MinDPhi;   //!
   TBranch        *b_MinDPhi_noJVF;   //!
   TBranch        *b_MET;   //!
   TBranch        *b_MET_x;   //!
   TBranch        *b_MET_y;   //!
   TBranch        *b_MET_phi;   //!
   TBranch        *b_METRel;   //!
   TBranch        *b_METRel_x;   //!
   TBranch        *b_METRel_y;   //!
   TBranch        *b_METRel_noJets;   //!
   TBranch        *b_MET_default;   //!
   TBranch        *b_MET_default_x;   //!
   TBranch        *b_MET_default_y;   //!
   TBranch        *b_DPhiSubLeadLepMET_STVF;   //!
   TBranch        *b_DPhiLeadLepMET_STVF;   //!
   TBranch        *b_MinDPhi_STVF;   //!
   TBranch        *b_MinDPhi_noJVF_STVF;   //!
   TBranch        *b_MT_STVF;   //!
   TBranch        *b_MTrans_STVF;   //!
   TBranch        *b_Mtt_STVF;   //!
   TBranch        *b_x1_STVF;   //!
   TBranch        *b_x2_STVF;   //!
   TBranch        *b_Pttot_STVF;   //!
   TBranch        *b_MET_STVF;   //!
   TBranch        *b_MET_x_STVF;   //!
   TBranch        *b_MET_y_STVF;   //!
   TBranch        *b_MET_phi_STVF;   //!
   TBranch        *b_METRel_STVF;   //!
   TBranch        *b_METRel_x_STVF;   //!
   TBranch        *b_METRel_y_STVF;   //!
   TBranch        *b_METRel_noJets_STVF;   //!
   TBranch        *b_MET_default_STVF;   //!
   TBranch        *b_MET_default_x_STVF;   //!
   TBranch        *b_MET_default_y_STVF;   //!
   TBranch        *b_MET_TrackHWW;   //!
   TBranch        *b_MET_x_TrackHWW;   //!
   TBranch        *b_MET_y_TrackHWW;   //!
   TBranch        *b_MET_phi_TrackHWW;   //!
   TBranch        *b_MinDPhi_TrackHWW;   //!
   TBranch        *b_MinDPhi_noJVF_TrackHWW;   //!
   TBranch        *b_METRel_Track_HWW;   //!
   TBranch        *b_METRel_x_TrackHWW;   //!
   TBranch        *b_METRel_y_TrackHWW;   //!
   TBranch        *b_DPhi_CaloTrackHWW;   //!
   TBranch        *b_MT_TrackHWW;   //!
   TBranch        *b_PtTrack_TrackHWW;   //!
   TBranch        *b_MTrans_TrackHWW;   //!
   TBranch        *b_Mtt_TrackHWW;   //!
   TBranch        *b_x1_TrackHWW;   //!
   TBranch        *b_x2_TrackHWW;   //!
   TBranch        *b_DPhiSubLeadLepMET_TrackHWW;   //!
   TBranch        *b_DPhiLeadLepMET_TrackHWW;   //!
   TBranch        *b_Pttot_TrackHWW;   //!
   TBranch        *b_HighTrackPt_TrackHWW;   //!
   TBranch        *b_MET_TrackHWW_Nmu;   //!
   TBranch        *b_MET_TrackHWW_NmuMatched;   //!
   TBranch        *b_MET_TrackHWW_Nel;   //!
   TBranch        *b_MET_TrackHWW_NelMatched;   //!
   TBranch        *b_MET_TrackHWW_Ntracks;   //!
   TBranch        *b_lepPtID0;   //!
   TBranch        *b_lepPtME0;   //!
   TBranch        *b_lepID0;   //!
   TBranch        *b_lepPt0;   //!
   TBranch        *b_lepPx0;   //!
   TBranch        *b_lepPy0;   //!
   TBranch        *b_lepPz0;   //!
   TBranch        *b_lepE0;   //!
   TBranch        *b_lepEta0;   //!
   TBranch        *b_lepPhi0;   //!
   TBranch        *b_lepEtcone20_0;   //!
   TBranch        *b_lepEtcone30_0;   //!
   TBranch        *b_lepEtcone40_0;   //!
   TBranch        *b_lepPtcone20_0;   //!
   TBranch        *b_lepPtcone30_0;   //!
   TBranch        *b_lepPtcone40_0;   //!
   TBranch        *b_lepNucone20_0;   //!
   TBranch        *b_lepNucone30_0;   //!
   TBranch        *b_lepNucone40_0;   //!
   TBranch        *b_lepz0PV0;   //!
   TBranch        *b_lepsigd0PV0;   //!
   TBranch        *b_lepD0_0;   //!
   TBranch        *b_lepZ0SinTheta_0;   //!
   TBranch        *b_lepMagD0_0;   //!
   TBranch        *b_lep_isTightPP0;   //!
   TBranch        *b_lep_isMediumPP0;   //!
   TBranch        *b_lep_isLoosePP0;   //!
   TBranch        *b_lep_isMultiLepton0;   //!
   TBranch        *b_lep_isVeryTightLH0;   //!
   TBranch        *b_lep_isTightLH0;   //!
   TBranch        *b_lep_isMediumLH0;   //!
   TBranch        *b_lep_isLooseLH0;   //!
   TBranch        *b_lep_isLooseBLPixLH0;   //!
   TBranch        *b_lep_isVeryLooseLH0;   //!
   TBranch        *b_lep_isCombined0;   //!
   TBranch        *b_lep_isTight0;   //!
   TBranch        *b_lep_isMedium0;   //!
   TBranch        *b_lep_isLoose0;   //!
   TBranch        *b_lep_isHSG3Clear0;   //!
   TBranch        *b_lep_isHSG3IsoClear0;   //!
   TBranch        *b_lep_isTrigMatch0;   //!
   TBranch        *b_lep_isFakable0;   //!
   TBranch        *b_BLayer_hit0;   //!
   TBranch        *b_conv0;   //!
   TBranch        *b_lepAuthor0;   //!
   TBranch        *b_lepTrigSF0EventWeight;   //!
   TBranch        *b_lepTrigSF0Error;   //!
   TBranch        *b_lepSF0RecoEventWeight;   //!
   TBranch        *b_lepSF0IdEventWeight;   //!
   TBranch        *b_lepSF0IsoEventWeight;   //!
   TBranch        *b_lepSF0ErrorIso;   //!
   TBranch        *b_lepSF0ErrorSys;   //!
   TBranch        *b_lepSF0RecoError;   //!
   TBranch        *b_lepSF0RecoErrorSys;   //!
   TBranch        *b_lepSF0IdError;   //!
   TBranch        *b_lepSF0IsoError;   //!
   TBranch        *b_lepMatch_EF_mu24i_tight_0;   //!
   TBranch        *b_lepMatch_EF_mu36_tight_0;   //!
   TBranch        *b_lepMatch_EF_e24vhi_medium1_0;   //!
   TBranch        *b_lepMatch_EF_e60_medium1_0;   //!
   TBranch        *b_lepMatch_EF_mu24_tight_0;   //!
   TBranch        *b_lepMatch_EF_mu40_MSonly_barrel_tight_0;   //!
   TBranch        *b_lepMatch_EF_mu18_tight_0;   //!
   TBranch        *b_lepMatch_EF_mu8_EFFS_0;   //!
   TBranch        *b_lepMatch_EF_mu13_0;   //!
   TBranch        *b_lepMatch_EF_e22vh_medium1_0;   //!
   TBranch        *b_lepMatch_EF_e45_medium1_0;   //!
   TBranch        *b_lepMatch_EF_e12Tvh_loose1_0;   //!
   TBranch        *b_lepPtID1;   //!
   TBranch        *b_lepPtME1;   //!
   TBranch        *b_lepID1;   //!
   TBranch        *b_lepPt1;   //!
   TBranch        *b_lepPx1;   //!
   TBranch        *b_lepPy1;   //!
   TBranch        *b_lepPz1;   //!
   TBranch        *b_lepE1;   //!
   TBranch        *b_lepEta1;   //!
   TBranch        *b_lepPhi1;   //!
   TBranch        *b_lepEtcone20_1;   //!
   TBranch        *b_lepEtcone30_1;   //!
   TBranch        *b_lepEtcone40_1;   //!
   TBranch        *b_lepPtcone20_1;   //!
   TBranch        *b_lepPtcone30_1;   //!
   TBranch        *b_lepPtcone40_1;   //!
   TBranch        *b_lepNucone20_1;   //!
   TBranch        *b_lepNucone30_1;   //!
   TBranch        *b_lepNucone40_1;   //!
   TBranch        *b_lepz0PV1;   //!
   TBranch        *b_lepsigd0PV1;   //!
   TBranch        *b_lepD0_1;   //!
   TBranch        *b_lepZ0SinTheta_1;   //!
   TBranch        *b_lepMagD0_1;   //!
   TBranch        *b_lep_isTightPP1;   //!
   TBranch        *b_lep_isMediumPP1;   //!
   TBranch        *b_lep_isLoosePP1;   //!
   TBranch        *b_lep_isMultiLepton1;   //!
   TBranch        *b_lep_isVeryTightLH1;   //!
   TBranch        *b_lep_isTightLH1;   //!
   TBranch        *b_lep_isMediumLH1;   //!
   TBranch        *b_lep_isLooseLH1;   //!
   TBranch        *b_lep_isLooseBLPixLH1;   //!
   TBranch        *b_lep_isVeryLooseLH1;   //!
   TBranch        *b_lep_isCombined1;   //!
   TBranch        *b_lep_isTight1;   //!
   TBranch        *b_lep_isMedium1;   //!
   TBranch        *b_lep_isLoose1;   //!
   TBranch        *b_lep_isHSG3Clear1;   //!
   TBranch        *b_lep_isHSG3IsoClear1;   //!
   TBranch        *b_lep_isTrigMatch1;   //!
   TBranch        *b_lep_isFakable1;   //!
   TBranch        *b_BLayer_hit1;   //!
   TBranch        *b_conv1;   //!
   TBranch        *b_lepAuthor1;   //!
   TBranch        *b_lepTrigSF1EventWeight;   //!
   TBranch        *b_lepTrigSF1Error;   //!
   TBranch        *b_lepSF1RecoEventWeight;   //!
   TBranch        *b_lepSF1IdEventWeight;   //!
   TBranch        *b_lepSF1IsoEventWeight;   //!
   TBranch        *b_lepSF1ErrorIso;   //!
   TBranch        *b_lepSF1ErrorSys;   //!
   TBranch        *b_lepSF1RecoError;   //!
   TBranch        *b_lepSF1RecoErrorSys;   //!
   TBranch        *b_lepSF1IdError;   //!
   TBranch        *b_lepSF1IsoError;   //!
   TBranch        *b_lepMatch_EF_mu24i_tight_1;   //!
   TBranch        *b_lepMatch_EF_mu36_tight_1;   //!
   TBranch        *b_lepMatch_EF_e24vhi_medium1_1;   //!
   TBranch        *b_lepMatch_EF_e60_medium1_1;   //!
   TBranch        *b_lepMatch_EF_mu24_tight_1;   //!
   TBranch        *b_lepMatch_EF_mu40_MSonly_barrel_tight_1;   //!
   TBranch        *b_lepMatch_EF_mu18_tight_1;   //!
   TBranch        *b_lepMatch_EF_mu8_EFFS_1;   //!
   TBranch        *b_lepMatch_EF_mu13_1;   //!
   TBranch        *b_lepMatch_EF_e22vh_medium1_1;   //!
   TBranch        *b_lepMatch_EF_e45_medium1_1;   //!
   TBranch        *b_lepMatch_EF_e12Tvh_loose1_1;   //!
   TBranch        *b_lepPtID2;   //!
   TBranch        *b_lepPtME2;   //!
   TBranch        *b_lepID2;   //!
   TBranch        *b_lepPt2;   //!
   TBranch        *b_lepPx2;   //!
   TBranch        *b_lepPy2;   //!
   TBranch        *b_lepPz2;   //!
   TBranch        *b_lepE2;   //!
   TBranch        *b_lepEta2;   //!
   TBranch        *b_lepPhi2;   //!
   TBranch        *b_lepEtcone20_2;   //!
   TBranch        *b_lepEtcone30_2;   //!
   TBranch        *b_lepEtcone40_2;   //!
   TBranch        *b_lepPtcone20_2;   //!
   TBranch        *b_lepPtcone30_2;   //!
   TBranch        *b_lepPtcone40_2;   //!
   TBranch        *b_lepNucone20_2;   //!
   TBranch        *b_lepNucone30_2;   //!
   TBranch        *b_lepNucone40_2;   //!
   TBranch        *b_lepz0PV2;   //!
   TBranch        *b_lepsigd0PV2;   //!
   TBranch        *b_lepD0_2;   //!
   TBranch        *b_lepZ0SinTheta_2;   //!
   TBranch        *b_lepMagD0_2;   //!
   TBranch        *b_lep_isTightPP2;   //!
   TBranch        *b_lep_isMediumPP2;   //!
   TBranch        *b_lep_isLoosePP2;   //!
   TBranch        *b_lep_isMultiLepton2;   //!
   TBranch        *b_lep_isVeryTightLH2;   //!
   TBranch        *b_lep_isTightLH2;   //!
   TBranch        *b_lep_isMediumLH2;   //!
   TBranch        *b_lep_isLooseLH2;   //!
   TBranch        *b_lep_isLooseBLPixLH2;   //!
   TBranch        *b_lep_isVeryLooseLH2;   //!
   TBranch        *b_lep_isCombined2;   //!
   TBranch        *b_lep_isTight2;   //!
   TBranch        *b_lep_isMedium2;   //!
   TBranch        *b_lep_isLoose2;   //!
   TBranch        *b_lep_isHSG3Clear2;   //!
   TBranch        *b_lep_isHSG3IsoClear2;   //!
   TBranch        *b_lep_isTrigMatch2;   //!
   TBranch        *b_lep_isFakable2;   //!
   TBranch        *b_BLayer_hit2;   //!
   TBranch        *b_conv2;   //!
   TBranch        *b_lepAuthor2;   //!
   TBranch        *b_lepTrigSF2EventWeight;   //!
   TBranch        *b_lepTrigSF2Error;   //!
   TBranch        *b_lepSF2RecoEventWeight;   //!
   TBranch        *b_lepSF2IdEventWeight;   //!
   TBranch        *b_lepSF2IsoEventWeight;   //!
   TBranch        *b_lepSF2ErrorIso;   //!
   TBranch        *b_lepSF2ErrorSys;   //!
   TBranch        *b_lepSF2RecoError;   //!
   TBranch        *b_lepSF2RecoErrorSys;   //!
   TBranch        *b_lepSF2IdError;   //!
   TBranch        *b_lepSF2IsoError;   //!
   TBranch        *b_lepMatch_EF_mu24i_tight_2;   //!
   TBranch        *b_lepMatch_EF_mu36_tight_2;   //!
   TBranch        *b_lepMatch_EF_e24vhi_medium1_2;   //!
   TBranch        *b_lepMatch_EF_e60_medium1_2;   //!
   TBranch        *b_lepMatch_EF_mu24_tight_2;   //!
   TBranch        *b_lepMatch_EF_mu40_MSonly_barrel_tight_2;   //!
   TBranch        *b_lepMatch_EF_mu18_tight_2;   //!
   TBranch        *b_lepMatch_EF_mu8_EFFS_2;   //!
   TBranch        *b_lepMatch_EF_mu13_2;   //!
   TBranch        *b_lepMatch_EF_e22vh_medium1_2;   //!
   TBranch        *b_lepMatch_EF_e45_medium1_2;   //!
   TBranch        *b_lepMatch_EF_e12Tvh_loose1_2;   //!
   TBranch        *b_lepPtID3;   //!
   TBranch        *b_lepPtME3;   //!
   TBranch        *b_lepID3;   //!
   TBranch        *b_lepPt3;   //!
   TBranch        *b_lepPx3;   //!
   TBranch        *b_lepPy3;   //!
   TBranch        *b_lepPz3;   //!
   TBranch        *b_lepE3;   //!
   TBranch        *b_lepEta3;   //!
   TBranch        *b_lepPhi3;   //!
   TBranch        *b_lepEtcone20_3;   //!
   TBranch        *b_lepEtcone30_3;   //!
   TBranch        *b_lepEtcone40_3;   //!
   TBranch        *b_lepPtcone20_3;   //!
   TBranch        *b_lepPtcone30_3;   //!
   TBranch        *b_lepPtcone40_3;   //!
   TBranch        *b_lepNucone20_3;   //!
   TBranch        *b_lepNucone30_3;   //!
   TBranch        *b_lepNucone40_3;   //!
   TBranch        *b_lepz0PV3;   //!
   TBranch        *b_lepsigd0PV3;   //!
   TBranch        *b_lepD0_3;   //!
   TBranch        *b_lepZ0SinTheta_3;   //!
   TBranch        *b_lepMagD0_3;   //!
   TBranch        *b_lep_isTightPP3;   //!
   TBranch        *b_lep_isMediumPP3;   //!
   TBranch        *b_lep_isLoosePP3;   //!
   TBranch        *b_lep_isMultiLepton3;   //!
   TBranch        *b_lep_isVeryTightLH3;   //!
   TBranch        *b_lep_isTightLH3;   //!
   TBranch        *b_lep_isMediumLH3;   //!
   TBranch        *b_lep_isLooseLH3;   //!
   TBranch        *b_lep_isLooseBLPixLH3;   //!
   TBranch        *b_lep_isVeryLooseLH3;   //!
   TBranch        *b_lep_isCombined3;   //!
   TBranch        *b_lep_isTight3;   //!
   TBranch        *b_lep_isMedium3;   //!
   TBranch        *b_lep_isLoose3;   //!
   TBranch        *b_lep_isHSG3Clear3;   //!
   TBranch        *b_lep_isHSG3IsoClear3;   //!
   TBranch        *b_lep_isTrigMatch3;   //!
   TBranch        *b_lep_isFakable3;   //!
   TBranch        *b_BLayer_hit3;   //!
   TBranch        *b_conv3;   //!
   TBranch        *b_lepAuthor3;   //!
   TBranch        *b_lepTrigSF3EventWeight;   //!
   TBranch        *b_lepTrigSF3Error;   //!
   TBranch        *b_lepSF3RecoEventWeight;   //!
   TBranch        *b_lepSF3IdEventWeight;   //!
   TBranch        *b_lepSF3IsoEventWeight;   //!
   TBranch        *b_lepSF3ErrorIso;   //!
   TBranch        *b_lepSF3ErrorSys;   //!
   TBranch        *b_lepSF3RecoError;   //!
   TBranch        *b_lepSF3RecoErrorSys;   //!
   TBranch        *b_lepSF3IdError;   //!
   TBranch        *b_lepSF3IsoError;   //!
   TBranch        *b_lepMatch_EF_mu24i_tight_3;   //!
   TBranch        *b_lepMatch_EF_mu36_tight_3;   //!
   TBranch        *b_lepMatch_EF_e24vhi_medium1_3;   //!
   TBranch        *b_lepMatch_EF_e60_medium1_3;   //!
   TBranch        *b_lepMatch_EF_mu24_tight_3;   //!
   TBranch        *b_lepMatch_EF_mu40_MSonly_barrel_tight_3;   //!
   TBranch        *b_lepMatch_EF_mu18_tight_3;   //!
   TBranch        *b_lepMatch_EF_mu8_EFFS_3;   //!
   TBranch        *b_lepMatch_EF_mu13_3;   //!
   TBranch        *b_lepMatch_EF_e22vh_medium1_3;   //!
   TBranch        *b_lepMatch_EF_e45_medium1_3;   //!
   TBranch        *b_lepMatch_EF_e12Tvh_loose1_3;   //!
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
   TBranch        *b_higgsPtEventWeight;   //!
   TBranch        *b_higgsMEventWeight;   //!
   TBranch        *b_higgsPtError;   //!
   TBranch        *b_mcEventWeight;   //!
   TBranch        *b_mcWeightOrg;   //!
   TBranch        *b_trigEventWeight;   //!
   TBranch        *b_lepTrigSFEventWeight;   //!
   TBranch        *b_lepTrigSFEventWeightUp;   //!
   TBranch        *b_lepTrigSFEventWeightDown;   //!
   TBranch        *b_lepSF0EventWeight;   //!
   TBranch        *b_lepSF1EventWeight;   //!
   TBranch        *b_lepSF0Error;   //!
   TBranch        *b_lepSF1Error;   //!
   TBranch        *b_MV1_70_EventWeight;   //!
   TBranch        *b_MV1_80_EventWeight;   //!
   TBranch        *b_MV120_80_EventWeight;   //!
   TBranch        *b_MV120_70_EventWeight;   //!
   TBranch        *b_MV1_70_BJetWeight;   //!
   TBranch        *b_MV1_80_BJetWeight;   //!
   TBranch        *b_MV120_80_BJetWeight;   //!
   TBranch        *b_MV120_70_BJetWeight;   //!
   TBranch        *b_MV1_70_CTJetWeight;   //!
   TBranch        *b_MV1_80_CTJetWeight;   //!
   TBranch        *b_MV120_80_CTJetWeight;   //!
   TBranch        *b_MV120_70_CTJetWeight;   //!
   TBranch        *b_MV1_70_MisTagWeight;   //!
   TBranch        *b_MV1_80_MisTagWeight;   //!
   TBranch        *b_MV120_80_MisTagWeight;   //!
   TBranch        *b_MV120_70_MisTagWeight;   //!
   TBranch        *b_MV1_70_BJetWeightUp;   //!
   TBranch        *b_MV1_80_BJetWeightUp;   //!
   TBranch        *b_MV120_80_BJetWeightUp;   //!
   TBranch        *b_MV120_70_BJetWeightUp;   //!
   TBranch        *b_MV1_70_CTJetWeightUp;   //!
   TBranch        *b_MV1_80_CTJetWeightUp;   //!
   TBranch        *b_MV120_80_CTJetWeightUp;   //!
   TBranch        *b_MV120_70_CTJetWeightUp;   //!
   TBranch        *b_MV1_70_MisTagWeightUp;   //!
   TBranch        *b_MV1_80_MisTagWeightUp;   //!
   TBranch        *b_MV120_80_MisTagWeightUp;   //!
   TBranch        *b_MV120_70_MisTagWeightUp;   //!
   TBranch        *b_MV1_70_BJetWeightDown;   //!
   TBranch        *b_MV1_80_BJetWeightDown;   //!
   TBranch        *b_MV120_80_BJetWeightDown;   //!
   TBranch        *b_MV120_70_BJetWeightDown;   //!
   TBranch        *b_MV1_70_CTJetWeightDown;   //!
   TBranch        *b_MV1_80_CTJetWeightDown;   //!
   TBranch        *b_MV120_80_CTJetWeightDown;   //!
   TBranch        *b_MV120_70_CTJetWeightDown;   //!
   TBranch        *b_MV1_70_MisTagWeightDown;   //!
   TBranch        *b_MV1_80_MisTagWeightDown;   //!
   TBranch        *b_MV120_80_MisTagWeightDown;   //!
   TBranch        *b_MV120_70_MisTagWeightDown;   //!
   TBranch        *b_MV1_80_BJetWeightEV_1_Up;   //!
   TBranch        *b_MV1_80_BJetWeightEV_2_Up;   //!
   TBranch        *b_MV1_80_BJetWeightEV_3_Up;   //!
   TBranch        *b_MV1_80_BJetWeightEV_4_Up;   //!
   TBranch        *b_MV1_80_BJetWeightEV_5_Up;   //!
   TBranch        *b_MV1_80_BJetWeightEV_6_Up;   //!
   TBranch        *b_MV1_80_BJetWeightEV_7_Up;   //!
   TBranch        *b_MV1_80_BJetWeightEV_8_Up;   //!
   TBranch        *b_MV1_80_BJetWeightEV_9_Up;   //!
   TBranch        *b_MV1_80_BJetWeightEV_1_Down;   //!
   TBranch        *b_MV1_80_BJetWeightEV_2_Down;   //!
   TBranch        *b_MV1_80_BJetWeightEV_3_Down;   //!
   TBranch        *b_MV1_80_BJetWeightEV_4_Down;   //!
   TBranch        *b_MV1_80_BJetWeightEV_5_Down;   //!
   TBranch        *b_MV1_80_BJetWeightEV_6_Down;   //!
   TBranch        *b_MV1_80_BJetWeightEV_7_Down;   //!
   TBranch        *b_MV1_80_BJetWeightEV_8_Down;   //!
   TBranch        *b_MV1_80_BJetWeightEV_9_Down;   //!
   TBranch        *b_nJets_Pt25_MV1_70;   //!
   TBranch        *b_nJets_Pt25_MV1_80;   //!
   TBranch        *b_nJets_Pt20_MV1_70;   //!
   TBranch        *b_nJets_Pt20_MV1_80;   //!
   TBranch        *b_nJets_Pt20;   //!
   TBranch        *b_nJetsProbing_MV1_80;   //!
   TBranch        *b_nJetsProbing_MV1_70;   //!
   TBranch        *b_Nvxp;   //!
   TBranch        *b_centralJetVeto_leadPt;   //!
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
   TBranch        *b_dilep_type;   //!
   TBranch        *b_isEEE;   //!
   TBranch        *b_isEEM;   //!
   TBranch        *b_isMME;   //!
   TBranch        *b_isMMM;   //!
   TBranch        *b_Mll01;   //!
   TBranch        *b_Mll02;   //!
   TBranch        *b_Mll12;   //!
   TBranch        *b_Mlll;   //!
   TBranch        *b_MT01;   //!
   TBranch        *b_MT02;   //!
   TBranch        *b_MT12;   //!
   TBranch        *b_MTrans01;   //!
   TBranch        *b_MTrans02;   //!
   TBranch        *b_MTrans12;   //!
   TBranch        *b_Ptll01;   //!
   TBranch        *b_Ptll02;   //!
   TBranch        *b_Ptll12;   //!
   TBranch        *b_DPhill01;   //!
   TBranch        *b_DPhill02;   //!
   TBranch        *b_DPhill12;   //!
   TBranch        *b_DRll01;   //!
   TBranch        *b_DRll02;   //!
   TBranch        *b_DRll12;   //!
   TBranch        *b_DR;   //!
   TBranch        *b_DR012;   //!
   TBranch        *b_DR102;   //!
   TBranch        *b_DR201;   //!
   TBranch        *b_DPhi;   //!
   TBranch        *b_DPhi012;   //!
   TBranch        *b_DPhi102;   //!
   TBranch        *b_DPhi201;   //!
   TBranch        *b_DEtall01;   //!
   TBranch        *b_DEtall02;   //!
   TBranch        *b_DEtall12;   //!
   TBranch        *b_Yll01;   //!
   TBranch        *b_Yll02;   //!
   TBranch        *b_Yll12;   //!
   TBranch        *b_Mtt01;   //!
   TBranch        *b_Mtt02;   //!
   TBranch        *b_Mtt12;   //!
   TBranch        *b_x1_01;   //!
   TBranch        *b_x1_02;   //!
   TBranch        *b_x1_12;   //!
   TBranch        *b_x2_01;   //!
   TBranch        *b_x2_02;   //!
   TBranch        *b_x2_12;   //!
   TBranch        *b_DPhiThirdLepMET;   //!
   TBranch        *b_DPhiThirdLepMET_STVF;   //!
   TBranch        *b_MT_STVF01;   //!
   TBranch        *b_MT_STVF02;   //!
   TBranch        *b_MT_STVF12;   //!
   TBranch        *b_MTrans_STVF01;   //!
   TBranch        *b_MTrans_STVF02;   //!
   TBranch        *b_MTrans_STVF12;   //!
   TBranch        *b_Mtt_STVF01;   //!
   TBranch        *b_Mtt_STVF02;   //!
   TBranch        *b_Mtt_STVF12;   //!
   TBranch        *b_x1_STVF_01;   //!
   TBranch        *b_x1_STVF_02;   //!
   TBranch        *b_x1_STVF_12;   //!
   TBranch        *b_x2_STVF_01;   //!
   TBranch        *b_x2_STVF_02;   //!
   TBranch        *b_x2_STVF_12;   //!
   TBranch        *b_MT_TrackHWW01;   //!
   TBranch        *b_MT_TrackHWW02;   //!
   TBranch        *b_MT_TrackHWW12;   //!
   TBranch        *b_MTrans_TrackHWW01;   //!
   TBranch        *b_MTrans_TrackHWW02;   //!
   TBranch        *b_MTrans_TrackHWW12;   //!
   TBranch        *b_Mtt_TrackHWW01;   //!
   TBranch        *b_Mtt_TrackHWW02;   //!
   TBranch        *b_Mtt_TrackHWW12;   //!
   TBranch        *b_x1_TrackHWW_01;   //!
   TBranch        *b_x1_TrackHWW_02;   //!
   TBranch        *b_x1_TrackHWW_12;   //!
   TBranch        *b_x2_TrackHWW_01;   //!
   TBranch        *b_x2_TrackHWW_02;   //!
   TBranch        *b_x2_TrackHWW_12;   //!
   TBranch        *b_DPhiThirdLepMET_TrackHWW;   //!
   TBranch        *b_DRlep2jet;   //!
   TBranch        *b_lepSF2EventWeight;   //!
   TBranch        *b_lepSF2Error;   //!
   TBranch        *b_isEEEE;   //!
   TBranch        *b_isEEEM;   //!
   TBranch        *b_isEEMM;   //!
   TBranch        *b_isEMMM;   //!
   TBranch        *b_isMMMM;   //!
   TBranch        *b_Mll03;   //!
   TBranch        *b_Mll13;   //!
   TBranch        *b_Mll23;   //!
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
   TBranch        *b_MT03;   //!
   TBranch        *b_MT13;   //!
   TBranch        *b_MT23;   //!
   TBranch        *b_MTrans03;   //!
   TBranch        *b_MTrans13;   //!
   TBranch        *b_MTrans23;   //!
   TBranch        *b_x1_03;   //!
   TBranch        *b_x1_13;   //!
   TBranch        *b_x1_23;   //!
   TBranch        *b_x2_03;   //!
   TBranch        *b_x2_13;   //!
   TBranch        *b_x2_23;   //!
   TBranch        *b_Mtt03;   //!
   TBranch        *b_Mtt13;   //!
   TBranch        *b_Mtt23;   //!
   TBranch        *b_MT_STVF03;   //!
   TBranch        *b_MT_STVF13;   //!
   TBranch        *b_MT_STVF23;   //!
   TBranch        *b_MTrans_STVF03;   //!
   TBranch        *b_MTrans_STVF13;   //!
   TBranch        *b_MTrans_STVF23;   //!
   TBranch        *b_Mtt_STVF03;   //!
   TBranch        *b_Mtt_STVF13;   //!
   TBranch        *b_Mtt_STVF23;   //!
   TBranch        *b_x1_STVF_03;   //!
   TBranch        *b_x1_STVF_13;   //!
   TBranch        *b_x1_STVF_23;   //!
   TBranch        *b_x2_STVF_03;   //!
   TBranch        *b_x2_STVF_13;   //!
   TBranch        *b_x2_STVF_23;   //!
   TBranch        *b_MT_TrackHWW03;   //!
   TBranch        *b_MT_TrackHWW13;   //!
   TBranch        *b_MT_TrackHWW23;   //!
   TBranch        *b_MTrans_TrackHWW03;   //!
   TBranch        *b_MTrans_TrackHWW13;   //!
   TBranch        *b_MTrans_TrackHWW23;   //!
   TBranch        *b_Mtt_TrackHWW03;   //!
   TBranch        *b_Mtt_TrackHWW13;   //!
   TBranch        *b_Mtt_TrackHWW23;   //!
   TBranch        *b_x1_TrackHWW_03;   //!
   TBranch        *b_x1_TrackHWW_13;   //!
   TBranch        *b_x1_TrackHWW_23;   //!
   TBranch        *b_x2_TrackHWW_03;   //!
   TBranch        *b_x2_TrackHWW_13;   //!
   TBranch        *b_x2_TrackHWW_23;   //!
   TBranch        *b_DRlep3jet;   //!
   TBranch        *b_lepSF3EventWeight;   //!
   TBranch        *b_lepSF3Error;   //!
   TBranch        *b_lepton_Pt;   //!
   TBranch        *b_lepton_Eta;   //!
   TBranch        *b_lepton_Phi;   //!
 //  TBranch        *b_lepton_ID;   //!
   TBranch        *b_lepton_Etcone20;   //!
   TBranch        *b_lepton_Etcone30;   //!
   TBranch        *b_lepton_Etcone40;   //!
   TBranch        *b_lepton_ID;   //!
   TBranch        *b_lepton_Ptcone30;   //!
   TBranch        *b_lepton_Ptcone40;   //!
   TBranch        *b_lepton_z0PV;   //!
   TBranch        *b_lepton_sigd0PV;   //!
   TBranch        *b_lepton_D0;   //!
   TBranch        *b_lepton_Z0SinTheta;   //!
   TBranch        *b_lepton_isTightPP;   //!
   TBranch        *b_lepton_isMediumPP;   //!
   TBranch        *b_lepton_isLoosePP;   //!
   TBranch        *b_lepton_isMultiLepton;   //!
   TBranch        *b_lepton_isVeryTightLH;   //!
   TBranch        *b_lepton_isTightLH;   //!
   TBranch        *b_lepton_isMediumLH;   //!
   TBranch        *b_lepton_isLooseLH;   //!
   TBranch        *b_lepton_isLooseBLPixLH;   //!
   TBranch        *b_lepton_isVeryLooseLH;   //!
   TBranch        *b_lepton_isCombined;   //!
   TBranch        *b_lepton_isTight;   //!
   TBranch        *b_lepton_isMedium;   //!
   TBranch        *b_lepton_isLoose;   //!
   TBranch        *b_lepton_BLayer_hit;   //!
   TBranch        *b_lepton_conv;   //!
   TBranch        *b_lepton_Author;   //!
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
   TBranch        *b_top_hfor_type;   //!
   TBranch        *b_m_jet_n;   //!
   TBranch        *b_m_jet_E;   //!
   TBranch        *b_m_jet_pt;   //!
   TBranch        *b_m_jet_eta;   //!
   TBranch        *b_m_jet_phi;   //!
   TBranch        *b_m_jet_LArQuality;   //!
   TBranch        *b_m_jet_sumPtTrk;   //!
   TBranch        *b_m_jet_emfrac;   //!
   TBranch        *b_m_jet_jvtxf;   //!
   TBranch        *b_m_jet_flavor_weight_MV1;   //!
   TBranch        *b_m_jet_flavor_truth_label;   //!
   TBranch        *b_m_vxp_n;   //!
   TBranch        *b_m_vxp_nTracks;   //!
   TBranch        *b_m_mcevt_pdf_id1;   //!
   TBranch        *b_m_mcevt_pdf_id2;   //!
   TBranch        *b_m_mcevt_pdf_x1;   //!
   TBranch        *b_m_mcevt_pdf_x2;   //!
   TBranch        *b_m_mcevt_pdf_scale;   //!
   TBranch        *b_m_truth_n;   //!
   TBranch        *b_m_truth_pt;   //!
   TBranch        *b_m_truth_m;   //!
   TBranch        *b_m_truth_eta;   //!
   TBranch        *b_m_truth_phi;   //!
   TBranch        *b_m_truth_status;   //!
   TBranch        *b_m_truth_pdgId;   //!
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
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("/home/ATLAS/disipio/LOCAL_DISK/ntuples/ttH/minintuples/116108.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("/home/ATLAS/disipio/LOCAL_DISK/ntuples/ttH/minintuples/116108.root");
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
   lepton_Pt = 0;
   lepton_Eta = 0;
   lepton_Phi = 0;
   //lepton_ID = 0;
   lepton_Etcone20 = 0;
   lepton_Etcone30 = 0;
   lepton_Etcone40 = 0;
   lepton_ID = 0;
   lepton_Ptcone30 = 0;
   lepton_Ptcone40 = 0;
   lepton_z0PV = 0;
   lepton_sigd0PV = 0;
   lepton_D0 = 0;
   lepton_Z0SinTheta = 0;
   lepton_isTightPP = 0;
   lepton_isMediumPP = 0;
   lepton_isLoosePP = 0;
   lepton_isMultiLepton = 0;
   lepton_isVeryTightLH = 0;
   lepton_isTightLH = 0;
   lepton_isMediumLH = 0;
   lepton_isLooseLH = 0;
   lepton_isLooseBLPixLH = 0;
   lepton_isVeryLooseLH = 0;
   lepton_isCombined = 0;
   lepton_isTight = 0;
   lepton_isMedium = 0;
   lepton_isLoose = 0;
   lepton_BLayer_hit = 0;
   lepton_conv = 0;
   lepton_Author = 0;
   m_jet_E = 0;
   m_jet_pt = 0;
   m_jet_eta = 0;
   m_jet_phi = 0;
   m_jet_LArQuality = 0;
   m_jet_sumPtTrk = 0;
   m_jet_emfrac = 0;
   m_jet_jvtxf = 0;
   m_jet_flavor_weight_MV1 = 0;
   m_jet_flavor_truth_label = 0;
   m_vxp_nTracks = 0;
   m_mcevt_pdf_id1 = 0;
   m_mcevt_pdf_id2 = 0;
   m_mcevt_pdf_x1 = 0;
   m_mcevt_pdf_x2 = 0;
   m_mcevt_pdf_scale = 0;
   m_truth_pt = 0;
   m_truth_m = 0;
   m_truth_eta = 0;
   m_truth_phi = 0;
   m_truth_status = 0;
   m_truth_pdgId = 0;
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
   fChain->SetBranchAddress("Mll", &Mll, &b_Mll);
   fChain->SetBranchAddress("MT", &MT, &b_MT);
   fChain->SetBranchAddress("MTrans", &MTrans, &b_MTrans);
   fChain->SetBranchAddress("gammaStar_weight", &gammaStar_weight, &b_gammaStar_weight);
   fChain->SetBranchAddress("m_gammaStar", &m_gammaStar, &b_m_gammaStar);
   fChain->SetBranchAddress("Ptll", &Ptll, &b_Ptll);
   fChain->SetBranchAddress("DPhill", &DPhill, &b_DPhill);
   fChain->SetBranchAddress("DRll", &DRll, &b_DRll);
   fChain->SetBranchAddress("DEtall", &DEtall, &b_DEtall);
   fChain->SetBranchAddress("Yll", &Yll, &b_Yll);
   fChain->SetBranchAddress("Pttot", &Pttot, &b_Pttot);
   fChain->SetBranchAddress("Mjj", &Mjj, &b_Mjj);
   fChain->SetBranchAddress("Ptjj", &Ptjj, &b_Ptjj);
   fChain->SetBranchAddress("DPhijj", &DPhijj, &b_DPhijj);
   fChain->SetBranchAddress("DRjj", &DRjj, &b_DRjj);
   fChain->SetBranchAddress("DEtajj", &DEtajj, &b_DEtajj);
   fChain->SetBranchAddress("DYjj", &DYjj, &b_DYjj);
   fChain->SetBranchAddress("Mtt", &Mtt, &b_Mtt);
   fChain->SetBranchAddress("x1", &x1, &b_x1);
   fChain->SetBranchAddress("x2", &x2, &b_x2);
   fChain->SetBranchAddress("RandomRunNumber", &RandomRunNumber, &b_RandomRunNumber);
   fChain->SetBranchAddress("WgStarEventWeight", &WgStarEventWeight, &b_WgStarEventWeight);
   fChain->SetBranchAddress("WgStarEventWeightError", &WgStarEventWeightError, &b_WgStarEventWeightError);
   fChain->SetBranchAddress("overlapWZ", &overlapWZ, &b_overlapWZ);
   fChain->SetBranchAddress("didEJoverlap", &didEJoverlap, &b_didEJoverlap);
   fChain->SetBranchAddress("didMJoverlap", &didMJoverlap, &b_didMJoverlap);
   fChain->SetBranchAddress("didEEoverlap", &didEEoverlap, &b_didEEoverlap);
   fChain->SetBranchAddress("didEMoverlap", &didEMoverlap, &b_didEMoverlap);
   fChain->SetBranchAddress("lepPtSum", &lepPtSum, &b_lepPtSum);
   fChain->SetBranchAddress("DPhiSubLeadLepMET", &DPhiSubLeadLepMET, &b_DPhiSubLeadLepMET);
   fChain->SetBranchAddress("DPhiLeadLepMET", &DPhiLeadLepMET, &b_DPhiLeadLepMET);
   fChain->SetBranchAddress("MinDPhi", &MinDPhi, &b_MinDPhi);
   fChain->SetBranchAddress("MinDPhi_noJVF", &MinDPhi_noJVF, &b_MinDPhi_noJVF);
   fChain->SetBranchAddress("MET", &MET, &b_MET);
   fChain->SetBranchAddress("MET_x", &MET_x, &b_MET_x);
   fChain->SetBranchAddress("MET_y", &MET_y, &b_MET_y);
   fChain->SetBranchAddress("MET_phi", &MET_phi, &b_MET_phi);
   fChain->SetBranchAddress("METRel", &METRel, &b_METRel);
   fChain->SetBranchAddress("METRel_x", &METRel_x, &b_METRel_x);
   fChain->SetBranchAddress("METRel_y", &METRel_y, &b_METRel_y);
   fChain->SetBranchAddress("METRel_noJets", &METRel_noJets, &b_METRel_noJets);
   fChain->SetBranchAddress("MET_default", &MET_default, &b_MET_default);
   fChain->SetBranchAddress("MET_default_x", &MET_default_x, &b_MET_default_x);
   fChain->SetBranchAddress("MET_default_y", &MET_default_y, &b_MET_default_y);
   fChain->SetBranchAddress("DPhiSubLeadLepMET_STVF", &DPhiSubLeadLepMET_STVF, &b_DPhiSubLeadLepMET_STVF);
   fChain->SetBranchAddress("DPhiLeadLepMET_STVF", &DPhiLeadLepMET_STVF, &b_DPhiLeadLepMET_STVF);
   fChain->SetBranchAddress("MinDPhi_STVF", &MinDPhi_STVF, &b_MinDPhi_STVF);
   fChain->SetBranchAddress("MinDPhi_noJVF_STVF", &MinDPhi_noJVF_STVF, &b_MinDPhi_noJVF_STVF);
   fChain->SetBranchAddress("MT_STVF", &MT_STVF, &b_MT_STVF);
   fChain->SetBranchAddress("MTrans_STVF", &MTrans_STVF, &b_MTrans_STVF);
   fChain->SetBranchAddress("Mtt_STVF", &Mtt_STVF, &b_Mtt_STVF);
   fChain->SetBranchAddress("x1_STVF", &x1_STVF, &b_x1_STVF);
   fChain->SetBranchAddress("x2_STVF", &x2_STVF, &b_x2_STVF);
   fChain->SetBranchAddress("Pttot_STVF", &Pttot_STVF, &b_Pttot_STVF);
   fChain->SetBranchAddress("MET_STVF", &MET_STVF, &b_MET_STVF);
   fChain->SetBranchAddress("MET_x_STVF", &MET_x_STVF, &b_MET_x_STVF);
   fChain->SetBranchAddress("MET_y_STVF", &MET_y_STVF, &b_MET_y_STVF);
   fChain->SetBranchAddress("MET_phi_STVF", &MET_phi_STVF, &b_MET_phi_STVF);
   fChain->SetBranchAddress("METRel_STVF", &METRel_STVF, &b_METRel_STVF);
   fChain->SetBranchAddress("METRel_x_STVF", &METRel_x_STVF, &b_METRel_x_STVF);
   fChain->SetBranchAddress("METRel_y_STVF", &METRel_y_STVF, &b_METRel_y_STVF);
   fChain->SetBranchAddress("METRel_noJets_STVF", &METRel_noJets_STVF, &b_METRel_noJets_STVF);
   fChain->SetBranchAddress("MET_default_STVF", &MET_default_STVF, &b_MET_default_STVF);
   fChain->SetBranchAddress("MET_default_x_STVF", &MET_default_x_STVF, &b_MET_default_x_STVF);
   fChain->SetBranchAddress("MET_default_y_STVF", &MET_default_y_STVF, &b_MET_default_y_STVF);
   fChain->SetBranchAddress("MET_TrackHWW", &MET_TrackHWW, &b_MET_TrackHWW);
   fChain->SetBranchAddress("MET_x_TrackHWW", &MET_x_TrackHWW, &b_MET_x_TrackHWW);
   fChain->SetBranchAddress("MET_y_TrackHWW", &MET_y_TrackHWW, &b_MET_y_TrackHWW);
   fChain->SetBranchAddress("MET_phi_TrackHWW", &MET_phi_TrackHWW, &b_MET_phi_TrackHWW);
   fChain->SetBranchAddress("MinDPhi_TrackHWW", &MinDPhi_TrackHWW, &b_MinDPhi_TrackHWW);
   fChain->SetBranchAddress("MinDPhi_noJVF_TrackHWW", &MinDPhi_noJVF_TrackHWW, &b_MinDPhi_noJVF_TrackHWW);
   fChain->SetBranchAddress("METRel_TrackHWW", &METRel_TrackHWW, &b_METRel_Track_HWW);
   fChain->SetBranchAddress("METRel_x_TrackHWW", &METRel_x_TrackHWW, &b_METRel_x_TrackHWW);
   fChain->SetBranchAddress("METRel_y_TrackHWW", &METRel_y_TrackHWW, &b_METRel_y_TrackHWW);
   fChain->SetBranchAddress("DPhi_CaloTrackHWW", &DPhi_CaloTrackHWW, &b_DPhi_CaloTrackHWW);
   fChain->SetBranchAddress("MT_TrackHWW", &MT_TrackHWW, &b_MT_TrackHWW);
   fChain->SetBranchAddress("PtTrack_TrackHWW", &PtTrack_TrackHWW, &b_PtTrack_TrackHWW);
   fChain->SetBranchAddress("MTrans_TrackHWW", &MTrans_TrackHWW, &b_MTrans_TrackHWW);
   fChain->SetBranchAddress("Mtt_TrackHWW", &Mtt_TrackHWW, &b_Mtt_TrackHWW);
   fChain->SetBranchAddress("x1_TrackHWW", &x1_TrackHWW, &b_x1_TrackHWW);
   fChain->SetBranchAddress("x2_TrackHWW", &x2_TrackHWW, &b_x2_TrackHWW);
   fChain->SetBranchAddress("DPhiSubLeadLepMET_TrackHWW", &DPhiSubLeadLepMET_TrackHWW, &b_DPhiSubLeadLepMET_TrackHWW);
   fChain->SetBranchAddress("DPhiLeadLepMET_TrackHWW", &DPhiLeadLepMET_TrackHWW, &b_DPhiLeadLepMET_TrackHWW);
   fChain->SetBranchAddress("Pttot_TrackHWW", &Pttot_TrackHWW, &b_Pttot_TrackHWW);
   fChain->SetBranchAddress("HighTrackPt_TrackHWW", &HighTrackPt_TrackHWW, &b_HighTrackPt_TrackHWW);
   fChain->SetBranchAddress("MET_TrackHWW_Nmu", &MET_TrackHWW_Nmu, &b_MET_TrackHWW_Nmu);
   fChain->SetBranchAddress("MET_TrackHWW_NmuMatched", &MET_TrackHWW_NmuMatched, &b_MET_TrackHWW_NmuMatched);
   fChain->SetBranchAddress("MET_TrackHWW_Nel", &MET_TrackHWW_Nel, &b_MET_TrackHWW_Nel);
   fChain->SetBranchAddress("MET_TrackHWW_NelMatched", &MET_TrackHWW_NelMatched, &b_MET_TrackHWW_NelMatched);
   fChain->SetBranchAddress("MET_TrackHWW_Ntracks", &MET_TrackHWW_Ntracks, &b_MET_TrackHWW_Ntracks);
   fChain->SetBranchAddress("lepPtID0", &lepPtID0, &b_lepPtID0);
   fChain->SetBranchAddress("lepPtME0", &lepPtME0, &b_lepPtME0);
   fChain->SetBranchAddress("lepID0", &lepID0, &b_lepID0);
   fChain->SetBranchAddress("lepPt0", &lepPt0, &b_lepPt0);
   fChain->SetBranchAddress("lepPx0", &lepPx0, &b_lepPx0);
   fChain->SetBranchAddress("lepPy0", &lepPy0, &b_lepPy0);
   fChain->SetBranchAddress("lepPz0", &lepPz0, &b_lepPz0);
   fChain->SetBranchAddress("lepE0", &lepE0, &b_lepE0);
   fChain->SetBranchAddress("lepEta0", &lepEta0, &b_lepEta0);
   fChain->SetBranchAddress("lepPhi0", &lepPhi0, &b_lepPhi0);
   fChain->SetBranchAddress("lepEtcone20_0", &lepEtcone20_0, &b_lepEtcone20_0);
   fChain->SetBranchAddress("lepEtcone30_0", &lepEtcone30_0, &b_lepEtcone30_0);
   fChain->SetBranchAddress("lepEtcone40_0", &lepEtcone40_0, &b_lepEtcone40_0);
   fChain->SetBranchAddress("lepPtcone20_0", &lepPtcone20_0, &b_lepPtcone20_0);
   fChain->SetBranchAddress("lepPtcone30_0", &lepPtcone30_0, &b_lepPtcone30_0);
   fChain->SetBranchAddress("lepPtcone40_0", &lepPtcone40_0, &b_lepPtcone40_0);
   fChain->SetBranchAddress("lepNucone20_0", &lepNucone20_0, &b_lepNucone20_0);
   fChain->SetBranchAddress("lepNucone30_0", &lepNucone30_0, &b_lepNucone30_0);
   fChain->SetBranchAddress("lepNucone40_0", &lepNucone40_0, &b_lepNucone40_0);
   fChain->SetBranchAddress("lepz0PV0", &lepz0PV0, &b_lepz0PV0);
   fChain->SetBranchAddress("lepsigd0PV0", &lepsigd0PV0, &b_lepsigd0PV0);
   fChain->SetBranchAddress("lepD0_0", &lepD0_0, &b_lepD0_0);
   fChain->SetBranchAddress("lepZ0SinTheta_0", &lepZ0SinTheta_0, &b_lepZ0SinTheta_0);
   fChain->SetBranchAddress("lepMagD0_0", &lepMagD0_0, &b_lepMagD0_0);
   fChain->SetBranchAddress("lep_isTightPP0", &lep_isTightPP0, &b_lep_isTightPP0);
   fChain->SetBranchAddress("lep_isMediumPP0", &lep_isMediumPP0, &b_lep_isMediumPP0);
   fChain->SetBranchAddress("lep_isLoosePP0", &lep_isLoosePP0, &b_lep_isLoosePP0);
   fChain->SetBranchAddress("lep_isMultiLepton0", &lep_isMultiLepton0, &b_lep_isMultiLepton0);
   fChain->SetBranchAddress("lep_isVeryTightLH0", &lep_isVeryTightLH0, &b_lep_isVeryTightLH0);
   fChain->SetBranchAddress("lep_isTightLH0", &lep_isTightLH0, &b_lep_isTightLH0);
   fChain->SetBranchAddress("lep_isMediumLH0", &lep_isMediumLH0, &b_lep_isMediumLH0);
   fChain->SetBranchAddress("lep_isLooseLH0", &lep_isLooseLH0, &b_lep_isLooseLH0);
   fChain->SetBranchAddress("lep_isLooseBLPixLH0", &lep_isLooseBLPixLH0, &b_lep_isLooseBLPixLH0);
   fChain->SetBranchAddress("lep_isVeryLooseLH0", &lep_isVeryLooseLH0, &b_lep_isVeryLooseLH0);
   fChain->SetBranchAddress("lep_isCombined0", &lep_isCombined0, &b_lep_isCombined0);
   fChain->SetBranchAddress("lep_isTight0", &lep_isTight0, &b_lep_isTight0);
   fChain->SetBranchAddress("lep_isMedium0", &lep_isMedium0, &b_lep_isMedium0);
   fChain->SetBranchAddress("lep_isLoose0", &lep_isLoose0, &b_lep_isLoose0);
   fChain->SetBranchAddress("lep_isHSG3Clear0", &lep_isHSG3Clear0, &b_lep_isHSG3Clear0);
   fChain->SetBranchAddress("lep_isHSG3IsoClear0", &lep_isHSG3IsoClear0, &b_lep_isHSG3IsoClear0);
   fChain->SetBranchAddress("lep_isTrigMatch0", &lep_isTrigMatch0, &b_lep_isTrigMatch0);
   fChain->SetBranchAddress("lep_isFakable0", &lep_isFakable0, &b_lep_isFakable0);
   fChain->SetBranchAddress("BLayer_hit0", &BLayer_hit0, &b_BLayer_hit0);
   fChain->SetBranchAddress("conv0", &conv0, &b_conv0);
   fChain->SetBranchAddress("lepAuthor0", &lepAuthor0, &b_lepAuthor0);
   fChain->SetBranchAddress("lepTrigSF0EventWeight", &lepTrigSF0EventWeight, &b_lepTrigSF0EventWeight);
   fChain->SetBranchAddress("lepTrigSF0Error", &lepTrigSF0Error, &b_lepTrigSF0Error);
   fChain->SetBranchAddress("lepSF0RecoEventWeight", &lepSF0RecoEventWeight, &b_lepSF0RecoEventWeight);
   fChain->SetBranchAddress("lepSF0IdEventWeight", &lepSF0IdEventWeight, &b_lepSF0IdEventWeight);
   fChain->SetBranchAddress("lepSF0IsoEventWeight", &lepSF0IsoEventWeight, &b_lepSF0IsoEventWeight);
   fChain->SetBranchAddress("lepSF0ErrorIso", &lepSF0ErrorIso, &b_lepSF0ErrorIso);
   fChain->SetBranchAddress("lepSF0ErrorSys", &lepSF0ErrorSys, &b_lepSF0ErrorSys);
   fChain->SetBranchAddress("lepSF0RecoError", &lepSF0RecoError, &b_lepSF0RecoError);
   fChain->SetBranchAddress("lepSF0RecoErrorSys", &lepSF0RecoErrorSys, &b_lepSF0RecoErrorSys);
   fChain->SetBranchAddress("lepSF0IdError", &lepSF0IdError, &b_lepSF0IdError);
   fChain->SetBranchAddress("lepSF0IsoError", &lepSF0IsoError, &b_lepSF0IsoError);
   fChain->SetBranchAddress("lepMatch_EF_mu24i_tight_0", &lepMatch_EF_mu24i_tight_0, &b_lepMatch_EF_mu24i_tight_0);
   fChain->SetBranchAddress("lepMatch_EF_mu36_tight_0", &lepMatch_EF_mu36_tight_0, &b_lepMatch_EF_mu36_tight_0);
   fChain->SetBranchAddress("lepMatch_EF_e24vhi_medium1_0", &lepMatch_EF_e24vhi_medium1_0, &b_lepMatch_EF_e24vhi_medium1_0);
   fChain->SetBranchAddress("lepMatch_EF_e60_medium1_0", &lepMatch_EF_e60_medium1_0, &b_lepMatch_EF_e60_medium1_0);
   fChain->SetBranchAddress("lepMatch_EF_mu24_tight_0", &lepMatch_EF_mu24_tight_0, &b_lepMatch_EF_mu24_tight_0);
   fChain->SetBranchAddress("lepMatch_EF_mu40_MSonly_barrel_tight_0", &lepMatch_EF_mu40_MSonly_barrel_tight_0, &b_lepMatch_EF_mu40_MSonly_barrel_tight_0);
   fChain->SetBranchAddress("lepMatch_EF_mu18_tight_0", &lepMatch_EF_mu18_tight_0, &b_lepMatch_EF_mu18_tight_0);
   fChain->SetBranchAddress("lepMatch_EF_mu8_EFFS_0", &lepMatch_EF_mu8_EFFS_0, &b_lepMatch_EF_mu8_EFFS_0);
   fChain->SetBranchAddress("lepMatch_EF_mu13_0", &lepMatch_EF_mu13_0, &b_lepMatch_EF_mu13_0);
   fChain->SetBranchAddress("lepMatch_EF_e22vh_medium1_0", &lepMatch_EF_e22vh_medium1_0, &b_lepMatch_EF_e22vh_medium1_0);
   fChain->SetBranchAddress("lepMatch_EF_e45_medium1_0", &lepMatch_EF_e45_medium1_0, &b_lepMatch_EF_e45_medium1_0);
   fChain->SetBranchAddress("lepMatch_EF_e12Tvh_loose1_0", &lepMatch_EF_e12Tvh_loose1_0, &b_lepMatch_EF_e12Tvh_loose1_0);
   fChain->SetBranchAddress("lepPtID1", &lepPtID1, &b_lepPtID1);
   fChain->SetBranchAddress("lepPtME1", &lepPtME1, &b_lepPtME1);
   fChain->SetBranchAddress("lepID1", &lepID1, &b_lepID1);
   fChain->SetBranchAddress("lepPt1", &lepPt1, &b_lepPt1);
   fChain->SetBranchAddress("lepPx1", &lepPx1, &b_lepPx1);
   fChain->SetBranchAddress("lepPy1", &lepPy1, &b_lepPy1);
   fChain->SetBranchAddress("lepPz1", &lepPz1, &b_lepPz1);
   fChain->SetBranchAddress("lepE1", &lepE1, &b_lepE1);
   fChain->SetBranchAddress("lepEta1", &lepEta1, &b_lepEta1);
   fChain->SetBranchAddress("lepPhi1", &lepPhi1, &b_lepPhi1);
   fChain->SetBranchAddress("lepEtcone20_1", &lepEtcone20_1, &b_lepEtcone20_1);
   fChain->SetBranchAddress("lepEtcone30_1", &lepEtcone30_1, &b_lepEtcone30_1);
   fChain->SetBranchAddress("lepEtcone40_1", &lepEtcone40_1, &b_lepEtcone40_1);
   fChain->SetBranchAddress("lepPtcone20_1", &lepPtcone20_1, &b_lepPtcone20_1);
   fChain->SetBranchAddress("lepPtcone30_1", &lepPtcone30_1, &b_lepPtcone30_1);
   fChain->SetBranchAddress("lepPtcone40_1", &lepPtcone40_1, &b_lepPtcone40_1);
   fChain->SetBranchAddress("lepNucone20_1", &lepNucone20_1, &b_lepNucone20_1);
   fChain->SetBranchAddress("lepNucone30_1", &lepNucone30_1, &b_lepNucone30_1);
   fChain->SetBranchAddress("lepNucone40_1", &lepNucone40_1, &b_lepNucone40_1);
   fChain->SetBranchAddress("lepz0PV1", &lepz0PV1, &b_lepz0PV1);
   fChain->SetBranchAddress("lepsigd0PV1", &lepsigd0PV1, &b_lepsigd0PV1);
   fChain->SetBranchAddress("lepD0_1", &lepD0_1, &b_lepD0_1);
   fChain->SetBranchAddress("lepZ0SinTheta_1", &lepZ0SinTheta_1, &b_lepZ0SinTheta_1);
   fChain->SetBranchAddress("lepMagD0_1", &lepMagD0_1, &b_lepMagD0_1);
   fChain->SetBranchAddress("lep_isTightPP1", &lep_isTightPP1, &b_lep_isTightPP1);
   fChain->SetBranchAddress("lep_isMediumPP1", &lep_isMediumPP1, &b_lep_isMediumPP1);
   fChain->SetBranchAddress("lep_isLoosePP1", &lep_isLoosePP1, &b_lep_isLoosePP1);
   fChain->SetBranchAddress("lep_isMultiLepton1", &lep_isMultiLepton1, &b_lep_isMultiLepton1);
   fChain->SetBranchAddress("lep_isVeryTightLH1", &lep_isVeryTightLH1, &b_lep_isVeryTightLH1);
   fChain->SetBranchAddress("lep_isTightLH1", &lep_isTightLH1, &b_lep_isTightLH1);
   fChain->SetBranchAddress("lep_isMediumLH1", &lep_isMediumLH1, &b_lep_isMediumLH1);
   fChain->SetBranchAddress("lep_isLooseLH1", &lep_isLooseLH1, &b_lep_isLooseLH1);
   fChain->SetBranchAddress("lep_isLooseBLPixLH1", &lep_isLooseBLPixLH1, &b_lep_isLooseBLPixLH1);
   fChain->SetBranchAddress("lep_isVeryLooseLH1", &lep_isVeryLooseLH1, &b_lep_isVeryLooseLH1);
   fChain->SetBranchAddress("lep_isCombined1", &lep_isCombined1, &b_lep_isCombined1);
   fChain->SetBranchAddress("lep_isTight1", &lep_isTight1, &b_lep_isTight1);
   fChain->SetBranchAddress("lep_isMedium1", &lep_isMedium1, &b_lep_isMedium1);
   fChain->SetBranchAddress("lep_isLoose1", &lep_isLoose1, &b_lep_isLoose1);
   fChain->SetBranchAddress("lep_isHSG3Clear1", &lep_isHSG3Clear1, &b_lep_isHSG3Clear1);
   fChain->SetBranchAddress("lep_isHSG3IsoClear1", &lep_isHSG3IsoClear1, &b_lep_isHSG3IsoClear1);
   fChain->SetBranchAddress("lep_isTrigMatch1", &lep_isTrigMatch1, &b_lep_isTrigMatch1);
   fChain->SetBranchAddress("lep_isFakable1", &lep_isFakable1, &b_lep_isFakable1);
   fChain->SetBranchAddress("BLayer_hit1", &BLayer_hit1, &b_BLayer_hit1);
   fChain->SetBranchAddress("conv1", &conv1, &b_conv1);
   fChain->SetBranchAddress("lepAuthor1", &lepAuthor1, &b_lepAuthor1);
   fChain->SetBranchAddress("lepTrigSF1EventWeight", &lepTrigSF1EventWeight, &b_lepTrigSF1EventWeight);
   fChain->SetBranchAddress("lepTrigSF1Error", &lepTrigSF1Error, &b_lepTrigSF1Error);
   fChain->SetBranchAddress("lepSF1RecoEventWeight", &lepSF1RecoEventWeight, &b_lepSF1RecoEventWeight);
   fChain->SetBranchAddress("lepSF1IdEventWeight", &lepSF1IdEventWeight, &b_lepSF1IdEventWeight);
   fChain->SetBranchAddress("lepSF1IsoEventWeight", &lepSF1IsoEventWeight, &b_lepSF1IsoEventWeight);
   fChain->SetBranchAddress("lepSF1ErrorIso", &lepSF1ErrorIso, &b_lepSF1ErrorIso);
   fChain->SetBranchAddress("lepSF1ErrorSys", &lepSF1ErrorSys, &b_lepSF1ErrorSys);
   fChain->SetBranchAddress("lepSF1RecoError", &lepSF1RecoError, &b_lepSF1RecoError);
   fChain->SetBranchAddress("lepSF1RecoErrorSys", &lepSF1RecoErrorSys, &b_lepSF1RecoErrorSys);
   fChain->SetBranchAddress("lepSF1IdError", &lepSF1IdError, &b_lepSF1IdError);
   fChain->SetBranchAddress("lepSF1IsoError", &lepSF1IsoError, &b_lepSF1IsoError);
   fChain->SetBranchAddress("lepMatch_EF_mu24i_tight_1", &lepMatch_EF_mu24i_tight_1, &b_lepMatch_EF_mu24i_tight_1);
   fChain->SetBranchAddress("lepMatch_EF_mu36_tight_1", &lepMatch_EF_mu36_tight_1, &b_lepMatch_EF_mu36_tight_1);
   fChain->SetBranchAddress("lepMatch_EF_e24vhi_medium1_1", &lepMatch_EF_e24vhi_medium1_1, &b_lepMatch_EF_e24vhi_medium1_1);
   fChain->SetBranchAddress("lepMatch_EF_e60_medium1_1", &lepMatch_EF_e60_medium1_1, &b_lepMatch_EF_e60_medium1_1);
   fChain->SetBranchAddress("lepMatch_EF_mu24_tight_1", &lepMatch_EF_mu24_tight_1, &b_lepMatch_EF_mu24_tight_1);
   fChain->SetBranchAddress("lepMatch_EF_mu40_MSonly_barrel_tight_1", &lepMatch_EF_mu40_MSonly_barrel_tight_1, &b_lepMatch_EF_mu40_MSonly_barrel_tight_1);
   fChain->SetBranchAddress("lepMatch_EF_mu18_tight_1", &lepMatch_EF_mu18_tight_1, &b_lepMatch_EF_mu18_tight_1);
   fChain->SetBranchAddress("lepMatch_EF_mu8_EFFS_1", &lepMatch_EF_mu8_EFFS_1, &b_lepMatch_EF_mu8_EFFS_1);
   fChain->SetBranchAddress("lepMatch_EF_mu13_1", &lepMatch_EF_mu13_1, &b_lepMatch_EF_mu13_1);
   fChain->SetBranchAddress("lepMatch_EF_e22vh_medium1_1", &lepMatch_EF_e22vh_medium1_1, &b_lepMatch_EF_e22vh_medium1_1);
   fChain->SetBranchAddress("lepMatch_EF_e45_medium1_1", &lepMatch_EF_e45_medium1_1, &b_lepMatch_EF_e45_medium1_1);
   fChain->SetBranchAddress("lepMatch_EF_e12Tvh_loose1_1", &lepMatch_EF_e12Tvh_loose1_1, &b_lepMatch_EF_e12Tvh_loose1_1);
   fChain->SetBranchAddress("lepPtID2", &lepPtID2, &b_lepPtID2);
   fChain->SetBranchAddress("lepPtME2", &lepPtME2, &b_lepPtME2);
   fChain->SetBranchAddress("lepID2", &lepID2, &b_lepID2);
   fChain->SetBranchAddress("lepPt2", &lepPt2, &b_lepPt2);
   fChain->SetBranchAddress("lepPx2", &lepPx2, &b_lepPx2);
   fChain->SetBranchAddress("lepPy2", &lepPy2, &b_lepPy2);
   fChain->SetBranchAddress("lepPz2", &lepPz2, &b_lepPz2);
   fChain->SetBranchAddress("lepE2", &lepE2, &b_lepE2);
   fChain->SetBranchAddress("lepEta2", &lepEta2, &b_lepEta2);
   fChain->SetBranchAddress("lepPhi2", &lepPhi2, &b_lepPhi2);
   fChain->SetBranchAddress("lepEtcone20_2", &lepEtcone20_2, &b_lepEtcone20_2);
   fChain->SetBranchAddress("lepEtcone30_2", &lepEtcone30_2, &b_lepEtcone30_2);
   fChain->SetBranchAddress("lepEtcone40_2", &lepEtcone40_2, &b_lepEtcone40_2);
   fChain->SetBranchAddress("lepPtcone20_2", &lepPtcone20_2, &b_lepPtcone20_2);
   fChain->SetBranchAddress("lepPtcone30_2", &lepPtcone30_2, &b_lepPtcone30_2);
   fChain->SetBranchAddress("lepPtcone40_2", &lepPtcone40_2, &b_lepPtcone40_2);
   fChain->SetBranchAddress("lepNucone20_2", &lepNucone20_2, &b_lepNucone20_2);
   fChain->SetBranchAddress("lepNucone30_2", &lepNucone30_2, &b_lepNucone30_2);
   fChain->SetBranchAddress("lepNucone40_2", &lepNucone40_2, &b_lepNucone40_2);
   fChain->SetBranchAddress("lepz0PV2", &lepz0PV2, &b_lepz0PV2);
   fChain->SetBranchAddress("lepsigd0PV2", &lepsigd0PV2, &b_lepsigd0PV2);
   fChain->SetBranchAddress("lepD0_2", &lepD0_2, &b_lepD0_2);
   fChain->SetBranchAddress("lepZ0SinTheta_2", &lepZ0SinTheta_2, &b_lepZ0SinTheta_2);
   fChain->SetBranchAddress("lepMagD0_2", &lepMagD0_2, &b_lepMagD0_2);
   fChain->SetBranchAddress("lep_isTightPP2", &lep_isTightPP2, &b_lep_isTightPP2);
   fChain->SetBranchAddress("lep_isMediumPP2", &lep_isMediumPP2, &b_lep_isMediumPP2);
   fChain->SetBranchAddress("lep_isLoosePP2", &lep_isLoosePP2, &b_lep_isLoosePP2);
   fChain->SetBranchAddress("lep_isMultiLepton2", &lep_isMultiLepton2, &b_lep_isMultiLepton2);
   fChain->SetBranchAddress("lep_isVeryTightLH2", &lep_isVeryTightLH2, &b_lep_isVeryTightLH2);
   fChain->SetBranchAddress("lep_isTightLH2", &lep_isTightLH2, &b_lep_isTightLH2);
   fChain->SetBranchAddress("lep_isMediumLH2", &lep_isMediumLH2, &b_lep_isMediumLH2);
   fChain->SetBranchAddress("lep_isLooseLH2", &lep_isLooseLH2, &b_lep_isLooseLH2);
   fChain->SetBranchAddress("lep_isLooseBLPixLH2", &lep_isLooseBLPixLH2, &b_lep_isLooseBLPixLH2);
   fChain->SetBranchAddress("lep_isVeryLooseLH2", &lep_isVeryLooseLH2, &b_lep_isVeryLooseLH2);
   fChain->SetBranchAddress("lep_isCombined2", &lep_isCombined2, &b_lep_isCombined2);
   fChain->SetBranchAddress("lep_isTight2", &lep_isTight2, &b_lep_isTight2);
   fChain->SetBranchAddress("lep_isMedium2", &lep_isMedium2, &b_lep_isMedium2);
   fChain->SetBranchAddress("lep_isLoose2", &lep_isLoose2, &b_lep_isLoose2);
   fChain->SetBranchAddress("lep_isHSG3Clear2", &lep_isHSG3Clear2, &b_lep_isHSG3Clear2);
   fChain->SetBranchAddress("lep_isHSG3IsoClear2", &lep_isHSG3IsoClear2, &b_lep_isHSG3IsoClear2);
   fChain->SetBranchAddress("lep_isTrigMatch2", &lep_isTrigMatch2, &b_lep_isTrigMatch2);
   fChain->SetBranchAddress("lep_isFakable2", &lep_isFakable2, &b_lep_isFakable2);
   fChain->SetBranchAddress("BLayer_hit2", &BLayer_hit2, &b_BLayer_hit2);
   fChain->SetBranchAddress("conv2", &conv2, &b_conv2);
   fChain->SetBranchAddress("lepAuthor2", &lepAuthor2, &b_lepAuthor2);
   fChain->SetBranchAddress("lepTrigSF2EventWeight", &lepTrigSF2EventWeight, &b_lepTrigSF2EventWeight);
   fChain->SetBranchAddress("lepTrigSF2Error", &lepTrigSF2Error, &b_lepTrigSF2Error);
   fChain->SetBranchAddress("lepSF2RecoEventWeight", &lepSF2RecoEventWeight, &b_lepSF2RecoEventWeight);
   fChain->SetBranchAddress("lepSF2IdEventWeight", &lepSF2IdEventWeight, &b_lepSF2IdEventWeight);
   fChain->SetBranchAddress("lepSF2IsoEventWeight", &lepSF2IsoEventWeight, &b_lepSF2IsoEventWeight);
   fChain->SetBranchAddress("lepSF2ErrorIso", &lepSF2ErrorIso, &b_lepSF2ErrorIso);
   fChain->SetBranchAddress("lepSF2ErrorSys", &lepSF2ErrorSys, &b_lepSF2ErrorSys);
   fChain->SetBranchAddress("lepSF2RecoError", &lepSF2RecoError, &b_lepSF2RecoError);
   fChain->SetBranchAddress("lepSF2RecoErrorSys", &lepSF2RecoErrorSys, &b_lepSF2RecoErrorSys);
   fChain->SetBranchAddress("lepSF2IdError", &lepSF2IdError, &b_lepSF2IdError);
   fChain->SetBranchAddress("lepSF2IsoError", &lepSF2IsoError, &b_lepSF2IsoError);
   fChain->SetBranchAddress("lepMatch_EF_mu24i_tight_2", &lepMatch_EF_mu24i_tight_2, &b_lepMatch_EF_mu24i_tight_2);
   fChain->SetBranchAddress("lepMatch_EF_mu36_tight_2", &lepMatch_EF_mu36_tight_2, &b_lepMatch_EF_mu36_tight_2);
   fChain->SetBranchAddress("lepMatch_EF_e24vhi_medium1_2", &lepMatch_EF_e24vhi_medium1_2, &b_lepMatch_EF_e24vhi_medium1_2);
   fChain->SetBranchAddress("lepMatch_EF_e60_medium1_2", &lepMatch_EF_e60_medium1_2, &b_lepMatch_EF_e60_medium1_2);
   fChain->SetBranchAddress("lepMatch_EF_mu24_tight_2", &lepMatch_EF_mu24_tight_2, &b_lepMatch_EF_mu24_tight_2);
   fChain->SetBranchAddress("lepMatch_EF_mu40_MSonly_barrel_tight_2", &lepMatch_EF_mu40_MSonly_barrel_tight_2, &b_lepMatch_EF_mu40_MSonly_barrel_tight_2);
   fChain->SetBranchAddress("lepMatch_EF_mu18_tight_2", &lepMatch_EF_mu18_tight_2, &b_lepMatch_EF_mu18_tight_2);
   fChain->SetBranchAddress("lepMatch_EF_mu8_EFFS_2", &lepMatch_EF_mu8_EFFS_2, &b_lepMatch_EF_mu8_EFFS_2);
   fChain->SetBranchAddress("lepMatch_EF_mu13_2", &lepMatch_EF_mu13_2, &b_lepMatch_EF_mu13_2);
   fChain->SetBranchAddress("lepMatch_EF_e22vh_medium1_2", &lepMatch_EF_e22vh_medium1_2, &b_lepMatch_EF_e22vh_medium1_2);
   fChain->SetBranchAddress("lepMatch_EF_e45_medium1_2", &lepMatch_EF_e45_medium1_2, &b_lepMatch_EF_e45_medium1_2);
   fChain->SetBranchAddress("lepMatch_EF_e12Tvh_loose1_2", &lepMatch_EF_e12Tvh_loose1_2, &b_lepMatch_EF_e12Tvh_loose1_2);
   fChain->SetBranchAddress("lepPtID3", &lepPtID3, &b_lepPtID3);
   fChain->SetBranchAddress("lepPtME3", &lepPtME3, &b_lepPtME3);
   fChain->SetBranchAddress("lepID3", &lepID3, &b_lepID3);
   fChain->SetBranchAddress("lepPt3", &lepPt3, &b_lepPt3);
   fChain->SetBranchAddress("lepPx3", &lepPx3, &b_lepPx3);
   fChain->SetBranchAddress("lepPy3", &lepPy3, &b_lepPy3);
   fChain->SetBranchAddress("lepPz3", &lepPz3, &b_lepPz3);
   fChain->SetBranchAddress("lepE3", &lepE3, &b_lepE3);
   fChain->SetBranchAddress("lepEta3", &lepEta3, &b_lepEta3);
   fChain->SetBranchAddress("lepPhi3", &lepPhi3, &b_lepPhi3);
   fChain->SetBranchAddress("lepEtcone20_3", &lepEtcone20_3, &b_lepEtcone20_3);
   fChain->SetBranchAddress("lepEtcone30_3", &lepEtcone30_3, &b_lepEtcone30_3);
   fChain->SetBranchAddress("lepEtcone40_3", &lepEtcone40_3, &b_lepEtcone40_3);
   fChain->SetBranchAddress("lepPtcone20_3", &lepPtcone20_3, &b_lepPtcone20_3);
   fChain->SetBranchAddress("lepPtcone30_3", &lepPtcone30_3, &b_lepPtcone30_3);
   fChain->SetBranchAddress("lepPtcone40_3", &lepPtcone40_3, &b_lepPtcone40_3);
   fChain->SetBranchAddress("lepNucone20_3", &lepNucone20_3, &b_lepNucone20_3);
   fChain->SetBranchAddress("lepNucone30_3", &lepNucone30_3, &b_lepNucone30_3);
   fChain->SetBranchAddress("lepNucone40_3", &lepNucone40_3, &b_lepNucone40_3);
   fChain->SetBranchAddress("lepz0PV3", &lepz0PV3, &b_lepz0PV3);
   fChain->SetBranchAddress("lepsigd0PV3", &lepsigd0PV3, &b_lepsigd0PV3);
   fChain->SetBranchAddress("lepD0_3", &lepD0_3, &b_lepD0_3);
   fChain->SetBranchAddress("lepZ0SinTheta_3", &lepZ0SinTheta_3, &b_lepZ0SinTheta_3);
   fChain->SetBranchAddress("lepMagD0_3", &lepMagD0_3, &b_lepMagD0_3);
   fChain->SetBranchAddress("lep_isTightPP3", &lep_isTightPP3, &b_lep_isTightPP3);
   fChain->SetBranchAddress("lep_isMediumPP3", &lep_isMediumPP3, &b_lep_isMediumPP3);
   fChain->SetBranchAddress("lep_isLoosePP3", &lep_isLoosePP3, &b_lep_isLoosePP3);
   fChain->SetBranchAddress("lep_isMultiLepton3", &lep_isMultiLepton3, &b_lep_isMultiLepton3);
   fChain->SetBranchAddress("lep_isVeryTightLH3", &lep_isVeryTightLH3, &b_lep_isVeryTightLH3);
   fChain->SetBranchAddress("lep_isTightLH3", &lep_isTightLH3, &b_lep_isTightLH3);
   fChain->SetBranchAddress("lep_isMediumLH3", &lep_isMediumLH3, &b_lep_isMediumLH3);
   fChain->SetBranchAddress("lep_isLooseLH3", &lep_isLooseLH3, &b_lep_isLooseLH3);
   fChain->SetBranchAddress("lep_isLooseBLPixLH3", &lep_isLooseBLPixLH3, &b_lep_isLooseBLPixLH3);
   fChain->SetBranchAddress("lep_isVeryLooseLH3", &lep_isVeryLooseLH3, &b_lep_isVeryLooseLH3);
   fChain->SetBranchAddress("lep_isCombined3", &lep_isCombined3, &b_lep_isCombined3);
   fChain->SetBranchAddress("lep_isTight3", &lep_isTight3, &b_lep_isTight3);
   fChain->SetBranchAddress("lep_isMedium3", &lep_isMedium3, &b_lep_isMedium3);
   fChain->SetBranchAddress("lep_isLoose3", &lep_isLoose3, &b_lep_isLoose3);
   fChain->SetBranchAddress("lep_isHSG3Clear3", &lep_isHSG3Clear3, &b_lep_isHSG3Clear3);
   fChain->SetBranchAddress("lep_isHSG3IsoClear3", &lep_isHSG3IsoClear3, &b_lep_isHSG3IsoClear3);
   fChain->SetBranchAddress("lep_isTrigMatch3", &lep_isTrigMatch3, &b_lep_isTrigMatch3);
   fChain->SetBranchAddress("lep_isFakable3", &lep_isFakable3, &b_lep_isFakable3);
   fChain->SetBranchAddress("BLayer_hit3", &BLayer_hit3, &b_BLayer_hit3);
   fChain->SetBranchAddress("conv3", &conv3, &b_conv3);
   fChain->SetBranchAddress("lepAuthor3", &lepAuthor3, &b_lepAuthor3);
   fChain->SetBranchAddress("lepTrigSF3EventWeight", &lepTrigSF3EventWeight, &b_lepTrigSF3EventWeight);
   fChain->SetBranchAddress("lepTrigSF3Error", &lepTrigSF3Error, &b_lepTrigSF3Error);
   fChain->SetBranchAddress("lepSF3RecoEventWeight", &lepSF3RecoEventWeight, &b_lepSF3RecoEventWeight);
   fChain->SetBranchAddress("lepSF3IdEventWeight", &lepSF3IdEventWeight, &b_lepSF3IdEventWeight);
   fChain->SetBranchAddress("lepSF3IsoEventWeight", &lepSF3IsoEventWeight, &b_lepSF3IsoEventWeight);
   fChain->SetBranchAddress("lepSF3ErrorIso", &lepSF3ErrorIso, &b_lepSF3ErrorIso);
   fChain->SetBranchAddress("lepSF3ErrorSys", &lepSF3ErrorSys, &b_lepSF3ErrorSys);
   fChain->SetBranchAddress("lepSF3RecoError", &lepSF3RecoError, &b_lepSF3RecoError);
   fChain->SetBranchAddress("lepSF3RecoErrorSys", &lepSF3RecoErrorSys, &b_lepSF3RecoErrorSys);
   fChain->SetBranchAddress("lepSF3IdError", &lepSF3IdError, &b_lepSF3IdError);
   fChain->SetBranchAddress("lepSF3IsoError", &lepSF3IsoError, &b_lepSF3IsoError);
   fChain->SetBranchAddress("lepMatch_EF_mu24i_tight_3", &lepMatch_EF_mu24i_tight_3, &b_lepMatch_EF_mu24i_tight_3);
   fChain->SetBranchAddress("lepMatch_EF_mu36_tight_3", &lepMatch_EF_mu36_tight_3, &b_lepMatch_EF_mu36_tight_3);
   fChain->SetBranchAddress("lepMatch_EF_e24vhi_medium1_3", &lepMatch_EF_e24vhi_medium1_3, &b_lepMatch_EF_e24vhi_medium1_3);
   fChain->SetBranchAddress("lepMatch_EF_e60_medium1_3", &lepMatch_EF_e60_medium1_3, &b_lepMatch_EF_e60_medium1_3);
   fChain->SetBranchAddress("lepMatch_EF_mu24_tight_3", &lepMatch_EF_mu24_tight_3, &b_lepMatch_EF_mu24_tight_3);
   fChain->SetBranchAddress("lepMatch_EF_mu40_MSonly_barrel_tight_3", &lepMatch_EF_mu40_MSonly_barrel_tight_3, &b_lepMatch_EF_mu40_MSonly_barrel_tight_3);
   fChain->SetBranchAddress("lepMatch_EF_mu18_tight_3", &lepMatch_EF_mu18_tight_3, &b_lepMatch_EF_mu18_tight_3);
   fChain->SetBranchAddress("lepMatch_EF_mu8_EFFS_3", &lepMatch_EF_mu8_EFFS_3, &b_lepMatch_EF_mu8_EFFS_3);
   fChain->SetBranchAddress("lepMatch_EF_mu13_3", &lepMatch_EF_mu13_3, &b_lepMatch_EF_mu13_3);
   fChain->SetBranchAddress("lepMatch_EF_e22vh_medium1_3", &lepMatch_EF_e22vh_medium1_3, &b_lepMatch_EF_e22vh_medium1_3);
   fChain->SetBranchAddress("lepMatch_EF_e45_medium1_3", &lepMatch_EF_e45_medium1_3, &b_lepMatch_EF_e45_medium1_3);
   fChain->SetBranchAddress("lepMatch_EF_e12Tvh_loose1_3", &lepMatch_EF_e12Tvh_loose1_3, &b_lepMatch_EF_e12Tvh_loose1_3);
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
   fChain->SetBranchAddress("higgsPtEventWeight", &higgsPtEventWeight, &b_higgsPtEventWeight);
   fChain->SetBranchAddress("higgsMEventWeight", &higgsMEventWeight, &b_higgsMEventWeight);
   fChain->SetBranchAddress("higgsPtError", &higgsPtError, &b_higgsPtError);
   fChain->SetBranchAddress("mcEventWeight", &mcEventWeight, &b_mcEventWeight);
   fChain->SetBranchAddress("mcWeightOrg", &mcWeightOrg, &b_mcWeightOrg);
   fChain->SetBranchAddress("trigEventWeight", &trigEventWeight, &b_trigEventWeight);
   fChain->SetBranchAddress("lepTrigSFEventWeight", &lepTrigSFEventWeight, &b_lepTrigSFEventWeight);
   fChain->SetBranchAddress("lepTrigSFEventWeightUp", &lepTrigSFEventWeightUp, &b_lepTrigSFEventWeightUp);
   fChain->SetBranchAddress("lepTrigSFEventWeightDown", &lepTrigSFEventWeightDown, &b_lepTrigSFEventWeightDown);
   fChain->SetBranchAddress("lepSF0EventWeight", &lepSF0EventWeight, &b_lepSF0EventWeight);
   fChain->SetBranchAddress("lepSF1EventWeight", &lepSF1EventWeight, &b_lepSF1EventWeight);
   fChain->SetBranchAddress("lepSF0Error", &lepSF0Error, &b_lepSF0Error);
   fChain->SetBranchAddress("lepSF1Error", &lepSF1Error, &b_lepSF1Error);
   fChain->SetBranchAddress("MV1_70_EventWeight", &MV1_70_EventWeight, &b_MV1_70_EventWeight);
   fChain->SetBranchAddress("MV1_80_EventWeight", &MV1_80_EventWeight, &b_MV1_80_EventWeight);
   fChain->SetBranchAddress("MV120_80_EventWeight", &MV120_80_EventWeight, &b_MV120_80_EventWeight);
   fChain->SetBranchAddress("MV120_70_EventWeight", &MV120_70_EventWeight, &b_MV120_70_EventWeight);
   fChain->SetBranchAddress("MV1_70_BJetWeight", &MV1_70_BJetWeight, &b_MV1_70_BJetWeight);
   fChain->SetBranchAddress("MV1_80_BJetWeight", &MV1_80_BJetWeight, &b_MV1_80_BJetWeight);
   fChain->SetBranchAddress("MV120_80_BJetWeight", &MV120_80_BJetWeight, &b_MV120_80_BJetWeight);
   fChain->SetBranchAddress("MV120_70_BJetWeight", &MV120_70_BJetWeight, &b_MV120_70_BJetWeight);
   fChain->SetBranchAddress("MV1_70_CTJetWeight", &MV1_70_CTJetWeight, &b_MV1_70_CTJetWeight);
   fChain->SetBranchAddress("MV1_80_CTJetWeight", &MV1_80_CTJetWeight, &b_MV1_80_CTJetWeight);
   fChain->SetBranchAddress("MV120_80_CTJetWeight", &MV120_80_CTJetWeight, &b_MV120_80_CTJetWeight);
   fChain->SetBranchAddress("MV120_70_CTJetWeight", &MV120_70_CTJetWeight, &b_MV120_70_CTJetWeight);
   fChain->SetBranchAddress("MV1_70_MisTagWeight", &MV1_70_MisTagWeight, &b_MV1_70_MisTagWeight);
   fChain->SetBranchAddress("MV1_80_MisTagWeight", &MV1_80_MisTagWeight, &b_MV1_80_MisTagWeight);
   fChain->SetBranchAddress("MV120_80_MisTagWeight", &MV120_80_MisTagWeight, &b_MV120_80_MisTagWeight);
   fChain->SetBranchAddress("MV120_70_MisTagWeight", &MV120_70_MisTagWeight, &b_MV120_70_MisTagWeight);
   fChain->SetBranchAddress("MV1_70_BJetWeightUp", &MV1_70_BJetWeightUp, &b_MV1_70_BJetWeightUp);
   fChain->SetBranchAddress("MV1_80_BJetWeightUp", &MV1_80_BJetWeightUp, &b_MV1_80_BJetWeightUp);
   fChain->SetBranchAddress("MV120_80_BJetWeightUp", &MV120_80_BJetWeightUp, &b_MV120_80_BJetWeightUp);
   fChain->SetBranchAddress("MV120_70_BJetWeightUp", &MV120_70_BJetWeightUp, &b_MV120_70_BJetWeightUp);
   fChain->SetBranchAddress("MV1_70_CTJetWeightUp", &MV1_70_CTJetWeightUp, &b_MV1_70_CTJetWeightUp);
   fChain->SetBranchAddress("MV1_80_CTJetWeightUp", &MV1_80_CTJetWeightUp, &b_MV1_80_CTJetWeightUp);
   fChain->SetBranchAddress("MV120_80_CTJetWeightUp", &MV120_80_CTJetWeightUp, &b_MV120_80_CTJetWeightUp);
   fChain->SetBranchAddress("MV120_70_CTJetWeightUp", &MV120_70_CTJetWeightUp, &b_MV120_70_CTJetWeightUp);
   fChain->SetBranchAddress("MV1_70_MisTagWeightUp", &MV1_70_MisTagWeightUp, &b_MV1_70_MisTagWeightUp);
   fChain->SetBranchAddress("MV1_80_MisTagWeightUp", &MV1_80_MisTagWeightUp, &b_MV1_80_MisTagWeightUp);
   fChain->SetBranchAddress("MV120_80_MisTagWeightUp", &MV120_80_MisTagWeightUp, &b_MV120_80_MisTagWeightUp);
   fChain->SetBranchAddress("MV120_70_MisTagWeightUp", &MV120_70_MisTagWeightUp, &b_MV120_70_MisTagWeightUp);
   fChain->SetBranchAddress("MV1_70_BJetWeightDown", &MV1_70_BJetWeightDown, &b_MV1_70_BJetWeightDown);
   fChain->SetBranchAddress("MV1_80_BJetWeightDown", &MV1_80_BJetWeightDown, &b_MV1_80_BJetWeightDown);
   fChain->SetBranchAddress("MV120_80_BJetWeightDown", &MV120_80_BJetWeightDown, &b_MV120_80_BJetWeightDown);
   fChain->SetBranchAddress("MV120_70_BJetWeightDown", &MV120_70_BJetWeightDown, &b_MV120_70_BJetWeightDown);
   fChain->SetBranchAddress("MV1_70_CTJetWeightDown", &MV1_70_CTJetWeightDown, &b_MV1_70_CTJetWeightDown);
   fChain->SetBranchAddress("MV1_80_CTJetWeightDown", &MV1_80_CTJetWeightDown, &b_MV1_80_CTJetWeightDown);
   fChain->SetBranchAddress("MV120_80_CTJetWeightDown", &MV120_80_CTJetWeightDown, &b_MV120_80_CTJetWeightDown);
   fChain->SetBranchAddress("MV120_70_CTJetWeightDown", &MV120_70_CTJetWeightDown, &b_MV120_70_CTJetWeightDown);
   fChain->SetBranchAddress("MV1_70_MisTagWeightDown", &MV1_70_MisTagWeightDown, &b_MV1_70_MisTagWeightDown);
   fChain->SetBranchAddress("MV1_80_MisTagWeightDown", &MV1_80_MisTagWeightDown, &b_MV1_80_MisTagWeightDown);
   fChain->SetBranchAddress("MV120_80_MisTagWeightDown", &MV120_80_MisTagWeightDown, &b_MV120_80_MisTagWeightDown);
   fChain->SetBranchAddress("MV120_70_MisTagWeightDown", &MV120_70_MisTagWeightDown, &b_MV120_70_MisTagWeightDown);
   fChain->SetBranchAddress("MV1_80_BJetWeightEV_1_Up", &MV1_80_BJetWeightEV_1_Up, &b_MV1_80_BJetWeightEV_1_Up);
   fChain->SetBranchAddress("MV1_80_BJetWeightEV_2_Up", &MV1_80_BJetWeightEV_2_Up, &b_MV1_80_BJetWeightEV_2_Up);
   fChain->SetBranchAddress("MV1_80_BJetWeightEV_3_Up", &MV1_80_BJetWeightEV_3_Up, &b_MV1_80_BJetWeightEV_3_Up);
   fChain->SetBranchAddress("MV1_80_BJetWeightEV_4_Up", &MV1_80_BJetWeightEV_4_Up, &b_MV1_80_BJetWeightEV_4_Up);
   fChain->SetBranchAddress("MV1_80_BJetWeightEV_5_Up", &MV1_80_BJetWeightEV_5_Up, &b_MV1_80_BJetWeightEV_5_Up);
   fChain->SetBranchAddress("MV1_80_BJetWeightEV_6_Up", &MV1_80_BJetWeightEV_6_Up, &b_MV1_80_BJetWeightEV_6_Up);
   fChain->SetBranchAddress("MV1_80_BJetWeightEV_7_Up", &MV1_80_BJetWeightEV_7_Up, &b_MV1_80_BJetWeightEV_7_Up);
   fChain->SetBranchAddress("MV1_80_BJetWeightEV_8_Up", &MV1_80_BJetWeightEV_8_Up, &b_MV1_80_BJetWeightEV_8_Up);
   fChain->SetBranchAddress("MV1_80_BJetWeightEV_9_Up", &MV1_80_BJetWeightEV_9_Up, &b_MV1_80_BJetWeightEV_9_Up);
   fChain->SetBranchAddress("MV1_80_BJetWeightEV_1_Down", &MV1_80_BJetWeightEV_1_Down, &b_MV1_80_BJetWeightEV_1_Down);
   fChain->SetBranchAddress("MV1_80_BJetWeightEV_2_Down", &MV1_80_BJetWeightEV_2_Down, &b_MV1_80_BJetWeightEV_2_Down);
   fChain->SetBranchAddress("MV1_80_BJetWeightEV_3_Down", &MV1_80_BJetWeightEV_3_Down, &b_MV1_80_BJetWeightEV_3_Down);
   fChain->SetBranchAddress("MV1_80_BJetWeightEV_4_Down", &MV1_80_BJetWeightEV_4_Down, &b_MV1_80_BJetWeightEV_4_Down);
   fChain->SetBranchAddress("MV1_80_BJetWeightEV_5_Down", &MV1_80_BJetWeightEV_5_Down, &b_MV1_80_BJetWeightEV_5_Down);
   fChain->SetBranchAddress("MV1_80_BJetWeightEV_6_Down", &MV1_80_BJetWeightEV_6_Down, &b_MV1_80_BJetWeightEV_6_Down);
   fChain->SetBranchAddress("MV1_80_BJetWeightEV_7_Down", &MV1_80_BJetWeightEV_7_Down, &b_MV1_80_BJetWeightEV_7_Down);
   fChain->SetBranchAddress("MV1_80_BJetWeightEV_8_Down", &MV1_80_BJetWeightEV_8_Down, &b_MV1_80_BJetWeightEV_8_Down);
   fChain->SetBranchAddress("MV1_80_BJetWeightEV_9_Down", &MV1_80_BJetWeightEV_9_Down, &b_MV1_80_BJetWeightEV_9_Down);
   fChain->SetBranchAddress("nJets_Pt25_MV1_70", &nJets_Pt25_MV1_70, &b_nJets_Pt25_MV1_70);
   fChain->SetBranchAddress("nJets_Pt25_MV1_80", &nJets_Pt25_MV1_80, &b_nJets_Pt25_MV1_80);
   fChain->SetBranchAddress("nJets_Pt20_MV1_70", &nJets_Pt20_MV1_70, &b_nJets_Pt20_MV1_70);
   fChain->SetBranchAddress("nJets_Pt20_MV1_80", &nJets_Pt20_MV1_80, &b_nJets_Pt20_MV1_80);
   fChain->SetBranchAddress("nJets_Pt20", &nJets_Pt20, &b_nJets_Pt20);
   fChain->SetBranchAddress("nJetsProbing_MV1_80", &nJetsProbing_MV1_80, &b_nJetsProbing_MV1_80);
   fChain->SetBranchAddress("nJetsProbing_MV1_70", &nJetsProbing_MV1_70, &b_nJetsProbing_MV1_70);
   fChain->SetBranchAddress("Nvxp", &Nvxp, &b_Nvxp);
   fChain->SetBranchAddress("centralJetVeto_leadPt", &centralJetVeto_leadPt, &b_centralJetVeto_leadPt);
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
   fChain->SetBranchAddress("dilep_type", &dilep_type, &b_dilep_type);
   fChain->SetBranchAddress("isEEE", &isEEE, &b_isEEE);
   fChain->SetBranchAddress("isEEM", &isEEM, &b_isEEM);
   fChain->SetBranchAddress("isMME", &isMME, &b_isMME);
   fChain->SetBranchAddress("isMMM", &isMMM, &b_isMMM);
   fChain->SetBranchAddress("Mll01", &Mll01, &b_Mll01);
   fChain->SetBranchAddress("Mll02", &Mll02, &b_Mll02);
   fChain->SetBranchAddress("Mll12", &Mll12, &b_Mll12);
   fChain->SetBranchAddress("Mlll", &Mlll, &b_Mlll);
   fChain->SetBranchAddress("MT01", &MT01, &b_MT01);
   fChain->SetBranchAddress("MT02", &MT02, &b_MT02);
   fChain->SetBranchAddress("MT12", &MT12, &b_MT12);
   fChain->SetBranchAddress("MTrans01", &MTrans01, &b_MTrans01);
   fChain->SetBranchAddress("MTrans02", &MTrans02, &b_MTrans02);
   fChain->SetBranchAddress("MTrans12", &MTrans12, &b_MTrans12);
   fChain->SetBranchAddress("Ptll01", &Ptll01, &b_Ptll01);
   fChain->SetBranchAddress("Ptll02", &Ptll02, &b_Ptll02);
   fChain->SetBranchAddress("Ptll12", &Ptll12, &b_Ptll12);
   fChain->SetBranchAddress("DPhill01", &DPhill01, &b_DPhill01);
   fChain->SetBranchAddress("DPhill02", &DPhill02, &b_DPhill02);
   fChain->SetBranchAddress("DPhill12", &DPhill12, &b_DPhill12);
   fChain->SetBranchAddress("DRll01", &DRll01, &b_DRll01);
   fChain->SetBranchAddress("DRll02", &DRll02, &b_DRll02);
   fChain->SetBranchAddress("DRll12", &DRll12, &b_DRll12);
   fChain->SetBranchAddress("DR", &DR, &b_DR);
   fChain->SetBranchAddress("DR012", &DR012, &b_DR012);
   fChain->SetBranchAddress("DR102", &DR102, &b_DR102);
   fChain->SetBranchAddress("DR201", &DR201, &b_DR201);
   fChain->SetBranchAddress("DPhi", &DPhi, &b_DPhi);
   fChain->SetBranchAddress("DPhi012", &DPhi012, &b_DPhi012);
   fChain->SetBranchAddress("DPhi102", &DPhi102, &b_DPhi102);
   fChain->SetBranchAddress("DPhi201", &DPhi201, &b_DPhi201);
   fChain->SetBranchAddress("DEtall01", &DEtall01, &b_DEtall01);
   fChain->SetBranchAddress("DEtall02", &DEtall02, &b_DEtall02);
   fChain->SetBranchAddress("DEtall12", &DEtall12, &b_DEtall12);
   fChain->SetBranchAddress("Yll01", &Yll01, &b_Yll01);
   fChain->SetBranchAddress("Yll02", &Yll02, &b_Yll02);
   fChain->SetBranchAddress("Yll12", &Yll12, &b_Yll12);
   fChain->SetBranchAddress("Mtt01", &Mtt01, &b_Mtt01);
   fChain->SetBranchAddress("Mtt02", &Mtt02, &b_Mtt02);
   fChain->SetBranchAddress("Mtt12", &Mtt12, &b_Mtt12);
   fChain->SetBranchAddress("x1_01", &x1_01, &b_x1_01);
   fChain->SetBranchAddress("x1_02", &x1_02, &b_x1_02);
   fChain->SetBranchAddress("x1_12", &x1_12, &b_x1_12);
   fChain->SetBranchAddress("x2_01", &x2_01, &b_x2_01);
   fChain->SetBranchAddress("x2_02", &x2_02, &b_x2_02);
   fChain->SetBranchAddress("x2_12", &x2_12, &b_x2_12);
   fChain->SetBranchAddress("DPhiThirdLepMET", &DPhiThirdLepMET, &b_DPhiThirdLepMET);
   fChain->SetBranchAddress("DPhiThirdLepMET_STVF", &DPhiThirdLepMET_STVF, &b_DPhiThirdLepMET_STVF);
   fChain->SetBranchAddress("MT_STVF01", &MT_STVF01, &b_MT_STVF01);
   fChain->SetBranchAddress("MT_STVF02", &MT_STVF02, &b_MT_STVF02);
   fChain->SetBranchAddress("MT_STVF12", &MT_STVF12, &b_MT_STVF12);
   fChain->SetBranchAddress("MTrans_STVF01", &MTrans_STVF01, &b_MTrans_STVF01);
   fChain->SetBranchAddress("MTrans_STVF02", &MTrans_STVF02, &b_MTrans_STVF02);
   fChain->SetBranchAddress("MTrans_STVF12", &MTrans_STVF12, &b_MTrans_STVF12);
   fChain->SetBranchAddress("Mtt_STVF01", &Mtt_STVF01, &b_Mtt_STVF01);
   fChain->SetBranchAddress("Mtt_STVF02", &Mtt_STVF02, &b_Mtt_STVF02);
   fChain->SetBranchAddress("Mtt_STVF12", &Mtt_STVF12, &b_Mtt_STVF12);
   fChain->SetBranchAddress("x1_STVF_01", &x1_STVF_01, &b_x1_STVF_01);
   fChain->SetBranchAddress("x1_STVF_02", &x1_STVF_02, &b_x1_STVF_02);
   fChain->SetBranchAddress("x1_STVF_12", &x1_STVF_12, &b_x1_STVF_12);
   fChain->SetBranchAddress("x2_STVF_01", &x2_STVF_01, &b_x2_STVF_01);
   fChain->SetBranchAddress("x2_STVF_02", &x2_STVF_02, &b_x2_STVF_02);
   fChain->SetBranchAddress("x2_STVF_12", &x2_STVF_12, &b_x2_STVF_12);
   fChain->SetBranchAddress("MT_TrackHWW01", &MT_TrackHWW01, &b_MT_TrackHWW01);
   fChain->SetBranchAddress("MT_TrackHWW02", &MT_TrackHWW02, &b_MT_TrackHWW02);
   fChain->SetBranchAddress("MT_TrackHWW12", &MT_TrackHWW12, &b_MT_TrackHWW12);
   fChain->SetBranchAddress("MTrans_TrackHWW01", &MTrans_TrackHWW01, &b_MTrans_TrackHWW01);
   fChain->SetBranchAddress("MTrans_TrackHWW02", &MTrans_TrackHWW02, &b_MTrans_TrackHWW02);
   fChain->SetBranchAddress("MTrans_TrackHWW12", &MTrans_TrackHWW12, &b_MTrans_TrackHWW12);
   fChain->SetBranchAddress("Mtt_TrackHWW01", &Mtt_TrackHWW01, &b_Mtt_TrackHWW01);
   fChain->SetBranchAddress("Mtt_TrackHWW02", &Mtt_TrackHWW02, &b_Mtt_TrackHWW02);
   fChain->SetBranchAddress("Mtt_TrackHWW12", &Mtt_TrackHWW12, &b_Mtt_TrackHWW12);
   fChain->SetBranchAddress("x1_TrackHWW_01", &x1_TrackHWW_01, &b_x1_TrackHWW_01);
   fChain->SetBranchAddress("x1_TrackHWW_02", &x1_TrackHWW_02, &b_x1_TrackHWW_02);
   fChain->SetBranchAddress("x1_TrackHWW_12", &x1_TrackHWW_12, &b_x1_TrackHWW_12);
   fChain->SetBranchAddress("x2_TrackHWW_01", &x2_TrackHWW_01, &b_x2_TrackHWW_01);
   fChain->SetBranchAddress("x2_TrackHWW_02", &x2_TrackHWW_02, &b_x2_TrackHWW_02);
   fChain->SetBranchAddress("x2_TrackHWW_12", &x2_TrackHWW_12, &b_x2_TrackHWW_12);
   fChain->SetBranchAddress("DPhiThirdLepMET_TrackHWW", &DPhiThirdLepMET_TrackHWW, &b_DPhiThirdLepMET_TrackHWW);
   fChain->SetBranchAddress("DRlep2jet", &DRlep2jet, &b_DRlep2jet);
   fChain->SetBranchAddress("lepSF2EventWeight", &lepSF2EventWeight, &b_lepSF2EventWeight);
   fChain->SetBranchAddress("lepSF2Error", &lepSF2Error, &b_lepSF2Error);
   fChain->SetBranchAddress("isEEEE", &isEEEE, &b_isEEEE);
   fChain->SetBranchAddress("isEEEM", &isEEEM, &b_isEEEM);
   fChain->SetBranchAddress("isEEMM", &isEEMM, &b_isEEMM);
   fChain->SetBranchAddress("isEMMM", &isEMMM, &b_isEMMM);
   fChain->SetBranchAddress("isMMMM", &isMMMM, &b_isMMMM);
   fChain->SetBranchAddress("Mll03", &Mll03, &b_Mll03);
   fChain->SetBranchAddress("Mll13", &Mll13, &b_Mll13);
   fChain->SetBranchAddress("Mll23", &Mll23, &b_Mll23);
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
   fChain->SetBranchAddress("MT03", &MT03, &b_MT03);
   fChain->SetBranchAddress("MT13", &MT13, &b_MT13);
   fChain->SetBranchAddress("MT23", &MT23, &b_MT23);
   fChain->SetBranchAddress("MTrans03", &MTrans03, &b_MTrans03);
   fChain->SetBranchAddress("MTrans13", &MTrans13, &b_MTrans13);
   fChain->SetBranchAddress("MTrans23", &MTrans23, &b_MTrans23);
   fChain->SetBranchAddress("x1_03", &x1_03, &b_x1_03);
   fChain->SetBranchAddress("x1_13", &x1_13, &b_x1_13);
   fChain->SetBranchAddress("x1_23", &x1_23, &b_x1_23);
   fChain->SetBranchAddress("x2_03", &x2_03, &b_x2_03);
   fChain->SetBranchAddress("x2_13", &x2_13, &b_x2_13);
   fChain->SetBranchAddress("x2_23", &x2_23, &b_x2_23);
   fChain->SetBranchAddress("Mtt03", &Mtt03, &b_Mtt03);
   fChain->SetBranchAddress("Mtt13", &Mtt13, &b_Mtt13);
   fChain->SetBranchAddress("Mtt23", &Mtt23, &b_Mtt23);
   fChain->SetBranchAddress("MT_STVF03", &MT_STVF03, &b_MT_STVF03);
   fChain->SetBranchAddress("MT_STVF13", &MT_STVF13, &b_MT_STVF13);
   fChain->SetBranchAddress("MT_STVF23", &MT_STVF23, &b_MT_STVF23);
   fChain->SetBranchAddress("MTrans_STVF03", &MTrans_STVF03, &b_MTrans_STVF03);
   fChain->SetBranchAddress("MTrans_STVF13", &MTrans_STVF13, &b_MTrans_STVF13);
   fChain->SetBranchAddress("MTrans_STVF23", &MTrans_STVF23, &b_MTrans_STVF23);
   fChain->SetBranchAddress("Mtt_STVF03", &Mtt_STVF03, &b_Mtt_STVF03);
   fChain->SetBranchAddress("Mtt_STVF13", &Mtt_STVF13, &b_Mtt_STVF13);
   fChain->SetBranchAddress("Mtt_STVF23", &Mtt_STVF23, &b_Mtt_STVF23);
   fChain->SetBranchAddress("x1_STVF_03", &x1_STVF_03, &b_x1_STVF_03);
   fChain->SetBranchAddress("x1_STVF_13", &x1_STVF_13, &b_x1_STVF_13);
   fChain->SetBranchAddress("x1_STVF_23", &x1_STVF_23, &b_x1_STVF_23);
   fChain->SetBranchAddress("x2_STVF_03", &x2_STVF_03, &b_x2_STVF_03);
   fChain->SetBranchAddress("x2_STVF_13", &x2_STVF_13, &b_x2_STVF_13);
   fChain->SetBranchAddress("x2_STVF_23", &x2_STVF_23, &b_x2_STVF_23);
   fChain->SetBranchAddress("MT_TrackHWW03", &MT_TrackHWW03, &b_MT_TrackHWW03);
   fChain->SetBranchAddress("MT_TrackHWW13", &MT_TrackHWW13, &b_MT_TrackHWW13);
   fChain->SetBranchAddress("MT_TrackHWW23", &MT_TrackHWW23, &b_MT_TrackHWW23);
   fChain->SetBranchAddress("MTrans_TrackHWW03", &MTrans_TrackHWW03, &b_MTrans_TrackHWW03);
   fChain->SetBranchAddress("MTrans_TrackHWW13", &MTrans_TrackHWW13, &b_MTrans_TrackHWW13);
   fChain->SetBranchAddress("MTrans_TrackHWW23", &MTrans_TrackHWW23, &b_MTrans_TrackHWW23);
   fChain->SetBranchAddress("Mtt_TrackHWW03", &Mtt_TrackHWW03, &b_Mtt_TrackHWW03);
   fChain->SetBranchAddress("Mtt_TrackHWW13", &Mtt_TrackHWW13, &b_Mtt_TrackHWW13);
   fChain->SetBranchAddress("Mtt_TrackHWW23", &Mtt_TrackHWW23, &b_Mtt_TrackHWW23);
   fChain->SetBranchAddress("x1_TrackHWW_03", &x1_TrackHWW_03, &b_x1_TrackHWW_03);
   fChain->SetBranchAddress("x1_TrackHWW_13", &x1_TrackHWW_13, &b_x1_TrackHWW_13);
   fChain->SetBranchAddress("x1_TrackHWW_23", &x1_TrackHWW_23, &b_x1_TrackHWW_23);
   fChain->SetBranchAddress("x2_TrackHWW_03", &x2_TrackHWW_03, &b_x2_TrackHWW_03);
   fChain->SetBranchAddress("x2_TrackHWW_13", &x2_TrackHWW_13, &b_x2_TrackHWW_13);
   fChain->SetBranchAddress("x2_TrackHWW_23", &x2_TrackHWW_23, &b_x2_TrackHWW_23);
   fChain->SetBranchAddress("DRlep3jet", &DRlep3jet, &b_DRlep3jet);
   fChain->SetBranchAddress("lepSF3EventWeight", &lepSF3EventWeight, &b_lepSF3EventWeight);
   fChain->SetBranchAddress("lepSF3Error", &lepSF3Error, &b_lepSF3Error);
   fChain->SetBranchAddress("lepton_Pt", &lepton_Pt, &b_lepton_Pt);
   fChain->SetBranchAddress("lepton_Eta", &lepton_Eta, &b_lepton_Eta);
   fChain->SetBranchAddress("lepton_Phi", &lepton_Phi, &b_lepton_Phi);
   fChain->SetBranchAddress("lepton_ID", &lepton_ID, &b_lepton_ID);
   fChain->SetBranchAddress("lepton_Etcone20", &lepton_Etcone20, &b_lepton_Etcone20);
   fChain->SetBranchAddress("lepton_Etcone30", &lepton_Etcone30, &b_lepton_Etcone30);
   fChain->SetBranchAddress("lepton_Etcone40", &lepton_Etcone40, &b_lepton_Etcone40);
//    fChain->SetBranchAddress("lepton_ID", &lepton_ID, &b_lepton_ID);
   fChain->SetBranchAddress("lepton_Ptcone30", &lepton_Ptcone30, &b_lepton_Ptcone30);
   fChain->SetBranchAddress("lepton_Ptcone40", &lepton_Ptcone40, &b_lepton_Ptcone40);
   fChain->SetBranchAddress("lepton_z0PV", &lepton_z0PV, &b_lepton_z0PV);
   fChain->SetBranchAddress("lepton_sigd0PV", &lepton_sigd0PV, &b_lepton_sigd0PV);
   fChain->SetBranchAddress("lepton_D0", &lepton_D0, &b_lepton_D0);
   fChain->SetBranchAddress("lepton_Z0SinTheta", &lepton_Z0SinTheta, &b_lepton_Z0SinTheta);
   fChain->SetBranchAddress("lepton_isTightPP", &lepton_isTightPP, &b_lepton_isTightPP);
   fChain->SetBranchAddress("lepton_isMediumPP", &lepton_isMediumPP, &b_lepton_isMediumPP);
   fChain->SetBranchAddress("lepton_isLoosePP", &lepton_isLoosePP, &b_lepton_isLoosePP);
   fChain->SetBranchAddress("lepton_isMultiLepton", &lepton_isMultiLepton, &b_lepton_isMultiLepton);
   fChain->SetBranchAddress("lepton_isVeryTightLH", &lepton_isVeryTightLH, &b_lepton_isVeryTightLH);
   fChain->SetBranchAddress("lepton_isTightLH", &lepton_isTightLH, &b_lepton_isTightLH);
   fChain->SetBranchAddress("lepton_isMediumLH", &lepton_isMediumLH, &b_lepton_isMediumLH);
   fChain->SetBranchAddress("lepton_isLooseLH", &lepton_isLooseLH, &b_lepton_isLooseLH);
   fChain->SetBranchAddress("lepton_isLooseBLPixLH", &lepton_isLooseBLPixLH, &b_lepton_isLooseBLPixLH);
   fChain->SetBranchAddress("lepton_isVeryLooseLH", &lepton_isVeryLooseLH, &b_lepton_isVeryLooseLH);
   fChain->SetBranchAddress("lepton_isCombined", &lepton_isCombined, &b_lepton_isCombined);
   fChain->SetBranchAddress("lepton_isTight", &lepton_isTight, &b_lepton_isTight);
   fChain->SetBranchAddress("lepton_isMedium", &lepton_isMedium, &b_lepton_isMedium);
   fChain->SetBranchAddress("lepton_isLoose", &lepton_isLoose, &b_lepton_isLoose);
   fChain->SetBranchAddress("lepton_BLayer_hit", &lepton_BLayer_hit, &b_lepton_BLayer_hit);
   fChain->SetBranchAddress("lepton_conv", &lepton_conv, &b_lepton_conv);
   fChain->SetBranchAddress("lepton_Author", &lepton_Author, &b_lepton_Author);
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
   fChain->SetBranchAddress("top_hfor_type", &top_hfor_type, &b_top_hfor_type);
   fChain->SetBranchAddress("m_jet_n", &m_jet_n, &b_m_jet_n);
   fChain->SetBranchAddress("m_jet_E", &m_jet_E, &b_m_jet_E);
   fChain->SetBranchAddress("m_jet_pt", &m_jet_pt, &b_m_jet_pt);
   fChain->SetBranchAddress("m_jet_eta", &m_jet_eta, &b_m_jet_eta);
   fChain->SetBranchAddress("m_jet_phi", &m_jet_phi, &b_m_jet_phi);
   fChain->SetBranchAddress("m_jet_LArQuality", &m_jet_LArQuality, &b_m_jet_LArQuality);
   fChain->SetBranchAddress("m_jet_sumPtTrk", &m_jet_sumPtTrk, &b_m_jet_sumPtTrk);
   fChain->SetBranchAddress("m_jet_emfrac", &m_jet_emfrac, &b_m_jet_emfrac);
   fChain->SetBranchAddress("m_jet_jvtxf", &m_jet_jvtxf, &b_m_jet_jvtxf);
   fChain->SetBranchAddress("m_jet_flavor_weight_MV1", &m_jet_flavor_weight_MV1, &b_m_jet_flavor_weight_MV1);
   fChain->SetBranchAddress("m_jet_flavor_truth_label", &m_jet_flavor_truth_label, &b_m_jet_flavor_truth_label);
   fChain->SetBranchAddress("m_vxp_n", &m_vxp_n, &b_m_vxp_n);
   fChain->SetBranchAddress("m_vxp_nTracks", &m_vxp_nTracks, &b_m_vxp_nTracks);
   fChain->SetBranchAddress("m_mcevt_pdf_id1", &m_mcevt_pdf_id1, &b_m_mcevt_pdf_id1);
   fChain->SetBranchAddress("m_mcevt_pdf_id2", &m_mcevt_pdf_id2, &b_m_mcevt_pdf_id2);
   fChain->SetBranchAddress("m_mcevt_pdf_x1", &m_mcevt_pdf_x1, &b_m_mcevt_pdf_x1);
   fChain->SetBranchAddress("m_mcevt_pdf_x2", &m_mcevt_pdf_x2, &b_m_mcevt_pdf_x2);
   fChain->SetBranchAddress("m_mcevt_pdf_scale", &m_mcevt_pdf_scale, &b_m_mcevt_pdf_scale);
   fChain->SetBranchAddress("m_truth_n", &m_truth_n, &b_m_truth_n);
   fChain->SetBranchAddress("m_truth_pt", &m_truth_pt, &b_m_truth_pt);
   fChain->SetBranchAddress("m_truth_m", &m_truth_m, &b_m_truth_m);
   fChain->SetBranchAddress("m_truth_eta", &m_truth_eta, &b_m_truth_eta);
   fChain->SetBranchAddress("m_truth_phi", &m_truth_phi, &b_m_truth_phi);
   fChain->SetBranchAddress("m_truth_status", &m_truth_status, &b_m_truth_status);
   fChain->SetBranchAddress("m_truth_pdgId", &m_truth_pdgId, &b_m_truth_pdgId);
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
