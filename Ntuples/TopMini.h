//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Fri Jul 11 14:21:25 2014 by ROOT version 5.34/04
// from TTree physics/4-vectors + variables required for scaling factors
// found on file: /home/ATLAS-T3/mromano/testarea/unversioned/Resolved8TeV/AnalysisTop-1.5.0/run/el.root
//////////////////////////////////////////////////////////

#ifndef TopMini_h
#define TopMini_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include <vector>
#include <vector>

// Fixed size dimensions of array or collections stored in the TTree if any.
using namespace std;

class TopMini {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   Int_t           runNumber;
   Int_t           eventNumber;
   Int_t           channelNumber;
   Int_t           rndRunNumber;
   Int_t           dataPeriod;
   Float_t         mu;
   Float_t         mcevt_weight;
   Int_t           pvxp_n;
   Int_t           hfor;
   Float_t         vxp_z;
   Float_t         mc_vxp_z;
   Double_t        mcevt_pdf1;
   Double_t        mcevt_pdf2;
   Int_t           mcevt_pdf_id1;
   Int_t           mcevt_pdf_id2;
   Double_t        mcevt_pdf_scale;
   Double_t        mcevt_pdf_x1;
   Double_t        mcevt_pdf_x2;
   Float_t         lep_pt;
   Float_t         lep_eta;
   Float_t         lep_phi;
   Float_t         lep_E;
   Float_t         lep_charge;
   Float_t         el_cl_eta;
   Float_t         eptcone30;
   Float_t         eetcone20;
   Float_t         mptcone30;
   Float_t         metcone20;
   Float_t         m_eminiIso10_4;
   Float_t         m_mminiIso10_4;
   Float_t         met_sumet;
   Float_t         met_et;
   Float_t         met_phi;
   Float_t         mwt;
   Int_t           jet_n;
   Int_t           alljet_n;
   Float_t         jet_pt[12];   //[alljet_n]
   Float_t         jet_eta[12];   //[alljet_n]
   Float_t         jet_phi[12];   //[alljet_n]
   Float_t         jet_E[12];   //[alljet_n]
   Float_t         jet_jvf[12];   //[alljet_n]
   Int_t           jet_trueflav[12];   //[alljet_n]
   Int_t           jet_truthMatched[12];   //[alljet_n]
   Float_t         jet_SV0[12];   //[alljet_n]
   Float_t         jet_COMBNN[12];   //[alljet_n]
   Float_t         jet_MV1[12];   //[alljet_n]
   Float_t         jet_MV1c[12];   //[alljet_n]
   Int_t           jet_isSemilep[12];   //[alljet_n]
   Int_t           lastCutPassed;
   Int_t           mc_n;
   vector<float>   *mc_E;
   vector<float>   *mc_pt;
   vector<float>   *mc_eta;
   vector<float>   *mc_phi;
   vector<float>   *mc_m;
   vector<int>     *mc_status;
   vector<int>     *mc_barcode;
   vector<int>     *mc_pdgId;
   vector<float>   *mc_charge;
   vector<vector<int> > *mc_parent_index;
   vector<vector<int> > *mc_child_index;
   Int_t           mc_jet_AntiKt10Truth_n;
   vector<float>   *mc_jet_AntiKt10Truth_E;
   vector<float>   *mc_jet_AntiKt10Truth_pt;
   vector<float>   *mc_jet_AntiKt10Truth_eta;
   vector<float>   *mc_jet_AntiKt10Truth_phi;
   vector<float>   *mc_jet_AntiKt10Truth_m;
   vector<int>     *mc_jet_AntiKt10Truth_constitN;
   vector<vector<int> > *mc_jet_AntiKt10Truth_constitIndex;
   Int_t           mc_jet_AntiKt10TruthTrimmed_n;
   vector<float>   *mc_jet_AntiKt10TruthTrimmed_E;
   vector<float>   *mc_jet_AntiKt10TruthTrimmed_pt;
   vector<float>   *mc_jet_AntiKt10TruthTrimmed_eta;
   vector<float>   *mc_jet_AntiKt10TruthTrimmed_phi;
   vector<float>   *mc_jet_AntiKt10TruthTrimmed_m;
   vector<int>     *mc_jet_AntiKt10TruthTrimmed_constitN;
   vector<vector<int> > *mc_jet_AntiKt10TruthTrimmed_constitIndex;
   vector<float>   *mc_jet_AntiKt10TruthTrimmed_SPLIT12;
   vector<int>     *mc_jet_AntiKt10TruthTrimmed_nBhad;
   Int_t           mc_jet_AntiKt4Truth_n;
   vector<float>   *mc_jet_AntiKt4Truth_E;
   vector<float>   *mc_jet_AntiKt4Truth_pt;
   vector<float>   *mc_jet_AntiKt4Truth_m;
   vector<float>   *mc_jet_AntiKt4Truth_eta;
   vector<float>   *mc_jet_AntiKt4Truth_phi;
   vector<int>     *mc_jet_AntiKt4Truth_flavor_truth_trueflav;
   Bool_t          EF_e20_medium;
   Bool_t          EF_e22_medium;
   Bool_t          EF_e22_medium1;
   Bool_t          EF_e22vh_medium1;
   Bool_t          EF_e45_medium1;
   Bool_t          EF_mu18;
   Bool_t          EF_mu18_medium;
   Bool_t          EF_j240_a10tc_EFFS;
   Int_t           OrigNumOfEventsInFile;
   Float_t         PUweight;
   Float_t         PUweightDe;
   Float_t         ZVxpWeight;
   Float_t         XSection;
   Float_t         KFactor;
   Float_t         JVFSFweight;
   Float_t         BTagSFweight;
   Float_t         totalScale;
   Float_t         elecScale;
   Float_t         muonScale;
   Float_t         trigScale;
   Float_t         WJetsShapeScale;
   Float_t         WJetsScale;
   Int_t           bTagCat;
   Int_t           Mtt;
   Int_t           chi2Min;
   Int_t           BoostedEvent;
   UInt_t          ntt_fjet_n;
   vector<float>   *ntt_fjet_pt;
   vector<float>   *ntt_fjet_eta;
   vector<float>   *ntt_fjet_phi;
   vector<float>   *ntt_fjet_E;
   vector<float>   *ntt_fjet_m;
   vector<float>   *ntt_fjet_m_orig;
   vector<float>   *ntt_fjet_d12;
   vector<float>   *ntt_fjet_DeltaPhi_Lap_FatJet;
   vector<float>   *ntt_fjet_DeltaR_LapJet_Fatjet;
   UInt_t          fjet_n;
   Float_t         fjet_pt[1];   //[fjet_n]
   Float_t         fjet_eta[1];   //[fjet_n]
   Float_t         fjet_phi[1];   //[fjet_n]
   Float_t         fjet_E[1];   //[fjet_n]
   Float_t         fjet_m[1];   //[fjet_n]
   Float_t         fjet_m_orig[1];   //[fjet_n]
   Float_t         fjet_d12[1];   //[fjet_n]
   Float_t         fjet_DeltaPhi_Lap_FatJet[1];   //[fjet_n]
   Float_t         fjet_DeltaR_LapJet_Fatjet[1];   //[fjet_n]
   Float_t         hadtop_pt;
   Float_t         hadtop_eta;
   Float_t         hadtop_phi;
   Float_t         hadtop_e;
   Float_t         hadtop_m;
   Float_t         leptop_pt;
   Float_t         leptop_eta;
   Float_t         leptop_phi;
   Float_t         leptop_e;
   Float_t         leptop_m;
   Float_t         ditop_pt;
   Float_t         ditop_eta;
   Float_t         ditop_phi;
   Float_t         ditop_e;
   Float_t         ditop_m;
   Float_t         nu_pt;
   Float_t         nu_eta;
   Float_t         nu_phi;
   Float_t         nu_e;
   Float_t         nu_m;
   Float_t         w_pt;
   Float_t         w_eta;
   Float_t         w_phi;
   Float_t         w_e;
   Float_t         w_m;
   Float_t         w_charge;
   Int_t           cl_n;
   vector<float>   *cl_pt;
   vector<int>     *cl_related_fatjet;
   vector<int>     *cl_related_jet;
   vector<float>   *cl_eta;
   vector<float>   *cl_phi;
   vector<float>   *cl_E_m;
   vector<float>   *cl_E_had;

   // List of branches
   TBranch        *b_runNumber;   //!
   TBranch        *b_eventNumber;   //!
   TBranch        *b_channelNumber;   //!
   TBranch        *b_rndRunNumber;   //!
   TBranch        *b_dataPeriod;   //!
   TBranch        *b_mu;   //!
   TBranch        *b_mcevt_weight;   //!
   TBranch        *b_pvxp_n;   //!
   TBranch        *b_hfor;   //!
   TBranch        *b_vxp_z;   //!
   TBranch        *b_mc_vxp_z;   //!
   TBranch        *b_mcevt_pdf1;   //!
   TBranch        *b_mcevt_pdf2;   //!
   TBranch        *b_mcevt_pdf_id1;   //!
   TBranch        *b_mcevt_pdf_id2;   //!
   TBranch        *b_mcevt_pdf_scale;   //!
   TBranch        *b_mcevt_pdf_x1;   //!
   TBranch        *b_mcevt_pdf_x2;   //!
   TBranch        *b_lep_pt;   //!
   TBranch        *b_lep_eta;   //!
   TBranch        *b_lep_phi;   //!
   TBranch        *b_lep_E;   //!
   TBranch        *b_lep_charge;   //!
   TBranch        *b_el_cl_eta;   //!
   TBranch        *b_eptcone30;   //!
   TBranch        *b_eetcone20;   //!
   TBranch        *b_mptcone30;   //!
   TBranch        *b_metcone20;   //!
   TBranch        *b_eminiIso10_4;   //!
   TBranch        *b_mminiIso10_4;   //!
   TBranch        *b_met_sumet;   //!
   TBranch        *b_met_et;   //!
   TBranch        *b_met_phi;   //!
   TBranch        *b_mwt;   //!
   TBranch        *b_jet_n;   //!
   TBranch        *b_alljet_n;   //!
   TBranch        *b_jet_pt;   //!
   TBranch        *b_jet_eta;   //!
   TBranch        *b_jet_phi;   //!
   TBranch        *b_jet_E;   //!
   TBranch        *b_jet_jvf;   //!
   TBranch        *b_jet_trueflav;   //!
   TBranch        *b_jet_truthMatched;   //!
   TBranch        *b_jet_SV0;   //!
   TBranch        *b_jet_COMBNN;   //!
   TBranch        *b_jet_MV1;   //!
   TBranch        *b_jet_MV1c;   //!
   TBranch        *b_jet_isSemilep;   //!
   TBranch        *b_lastCutPassed;   //!
   TBranch        *b_mc_n;   //!
   TBranch        *b_mc_E;   //!
   TBranch        *b_mc_pt;   //!
   TBranch        *b_mc_eta;   //!
   TBranch        *b_mc_phi;   //!
   TBranch        *b_mc_m;   //!
   TBranch        *b_mc_status;   //!
   TBranch        *b_mc_barcode;   //!
   TBranch        *b_mc_pdgId;   //!
   TBranch        *b_mc_charge;   //!
   TBranch        *b_mc_parent_index;   //!
   TBranch        *b_mc_child_index;   //!
   TBranch        *b_mc_jet_AntiKt10Truth_n;   //!
   TBranch        *b_mc_jet_AntiKt10Truth_E;   //!
   TBranch        *b_mc_jet_AntiKt10Truth_pt;   //!
   TBranch        *b_mc_jet_AntiKt10Truth_eta;   //!
   TBranch        *b_mc_jet_AntiKt10Truth_phi;   //!
   TBranch        *b_mc_jet_AntiKt10Truth_m;   //!
   TBranch        *b_mc_jet_AntiKt10Truth_constitN;   //!
   TBranch        *b_mc_jet_AntiKt10Truth_constitIndex;   //!
   TBranch        *b_mc_jet_AntiKt10TruthTrimmedPtFrac5SmallR30_n;   //!
   TBranch        *b_mc_jet_AntiKt10TruthTrimmed_E;   //!
   TBranch        *b_mc_jet_AntiKt10TruthTrimmed_pt;   //!
   TBranch        *b_mc_jet_AntiKt10TruthTrimmed_eta;   //!
   TBranch        *b_mc_jet_AntiKt10TruthTrimmed_phi;   //!
   TBranch        *b_mc_jet_AntiKt10TruthTrimmed_m;   //!
   TBranch        *b_mc_jet_AntiKt10TruthTrimmed_constitN;   //!
   TBranch        *b_mc_jet_AntiKt10TruthTrimmed_constitIndex;   //!
   TBranch        *b_mc_jet_AntiKt10TruthTrimmed_SPLIT12;   //!
   TBranch        *b_mc_jet_AntiKt10TruthTrimmed_nBhad;   //!
   TBranch        *b_mc_jet_AntiKt4Truth_n;   //!
   TBranch        *b_mc_jet_AntiKt4Truth_E;   //!
   TBranch        *b_mc_jet_AntiKt4Truth_pt;   //!
   TBranch        *b_mc_jet_AntiKt4Truth_m;   //!
   TBranch        *b_mc_jet_AntiKt4Truth_eta;   //!
   TBranch        *b_mc_jet_AntiKt4Truth_phi;   //!
   TBranch        *b_mc_jet_AntiKt4Truth_flavor_truth_trueflav;   //!
   TBranch        *b_EF_e20_medium;   //!
   TBranch        *b_EF_e22_medium;   //!
   TBranch        *b_EF_e22_medium1;   //!
   TBranch        *b_EF_e22vh_medium1;   //!
   TBranch        *b_EF_e45_medium1;   //!
   TBranch        *b_EF_mu18;   //!
   TBranch        *b_EF_mu18_medium;   //!
   TBranch        *b_EF_j240_a10tc_EFFS;   //!
   TBranch        *b_OrigNumOfEventsInFile;   //!
   TBranch        *b_PUweight;   //!
   TBranch        *b_PUweightDe;   //!
   TBranch        *b_ZVxpWeight;   //!
   TBranch        *b_XSection;   //!
   TBranch        *b_KFactor;   //!
   TBranch        *b_JVFSFweight;   //!
   TBranch        *b_BTagSFweight;   //!
   TBranch        *b_totalScale;   //!
   TBranch        *b_elecScale;   //!
   TBranch        *b_muonScale;   //!
   TBranch        *b_trigScale;   //!
   TBranch        *b_WJetsShapeScale;   //!
   TBranch        *b_WJetsScale;   //!
   TBranch        *b_bTagCat;   //!
   TBranch        *b_Mtt;   //!
   TBranch        *b_chi2Min;   //!
   TBranch        *b_BoostedEvent;   //!
   TBranch        *b_ntt_fjet_n;   //!
   TBranch        *b_ntt_fjet_pt;   //!
   TBranch        *b_ntt_fjet_eta;   //!
   TBranch        *b_ntt_fjet_phi;   //!
   TBranch        *b_ntt_fjet_E;   //!
   TBranch        *b_ntt_fjet_m;   //!
   TBranch        *b_ntt_fjet_m_orig;   //!
   TBranch        *b_ntt_fjet_d12;   //!
   TBranch        *b_ntt_fjet_DeltaPhi_Lap_FatJet;   //!
   TBranch        *b_ntt_fjet_DeltaR_LapJet_Fatjet;   //!
   TBranch        *b_fjet_n;   //!
   TBranch        *b_fjet_pt;   //!
   TBranch        *b_fjet_eta;   //!
   TBranch        *b_fjet_phi;   //!
   TBranch        *b_fjet_E;   //!
   TBranch        *b_fjet_m;   //!
   TBranch        *b_fjet_m_orig;   //!
   TBranch        *b_fjet_d12;   //!
   TBranch        *b_fjet_DeltaPhi_Lap_FatJet;   //!
   TBranch        *b_fjet_DeltaR_LapJet_Fatjet;   //!
   TBranch        *b_hadtop_pt;   //!
   TBranch        *b_hadtop_eta;   //!
   TBranch        *b_hadtop_phi;   //!
   TBranch        *b_hadtop_e;   //!
   TBranch        *b_hadtop_m;   //!
   TBranch        *b_leptop_pt;   //!
   TBranch        *b_leptop_eta;   //!
   TBranch        *b_leptop_phi;   //!
   TBranch        *b_leptop_e;   //!
   TBranch        *b_leptop_m;   //!
   TBranch        *b_ditop_pt;   //!
   TBranch        *b_ditop_eta;   //!
   TBranch        *b_ditop_phi;   //!
   TBranch        *b_ditop_e;   //!
   TBranch        *b_ditop_m;   //!
   TBranch        *b_m_nu_pt;   //!
   TBranch        *b_m_nu_eta;   //!
   TBranch        *b_m_nu_phi;   //!
   TBranch        *b_m_nu_e;   //!
   TBranch        *b_m_nu_m;   //!
   TBranch        *b_m_w_pt;   //!
   TBranch        *b_m_w_eta;   //!
   TBranch        *b_m_w_phi;   //!
   TBranch        *b_m_w_e;   //!
   TBranch        *b_m_w_m;   //!
   TBranch        *b_m_w_charge;   //!
   TBranch        *b_cl_n;   //!
   TBranch        *b_cl_pt;   //!
   TBranch        *b_cl_related_fatjet;   //!
   TBranch        *b_cl_related_jet;   //!
   TBranch        *b_cl_eta;   //!
   TBranch        *b_cl_phi;   //!
   TBranch        *b_cl_E_m;   //!
   TBranch        *b_cl_E_had;   //!

   TopMini(TTree *tree=0);
   virtual ~TopMini();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef TopMini_cxx
TopMini::TopMini(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
/*
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("/home/ATLAS-T3/mromano/testarea/unversioned/Resolved8TeV/AnalysisTop-1.5.0/run/el.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("/home/ATLAS-T3/mromano/testarea/unversioned/Resolved8TeV/AnalysisTop-1.5.0/run/el.root");
      }
      f->GetObject("physics",tree);

   }
*/
   Init(tree);
}

TopMini::~TopMini()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t TopMini::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t TopMini::LoadTree(Long64_t entry)
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

void TopMini::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   mc_E = 0;
   mc_pt = 0;
   mc_eta = 0;
   mc_phi = 0;
   mc_m = 0;
   mc_status = 0;
   mc_barcode = 0;
   mc_pdgId = 0;
   mc_charge = 0;
   mc_parent_index = 0;
   mc_child_index = 0;
   mc_jet_AntiKt10Truth_E = 0;
   mc_jet_AntiKt10Truth_pt = 0;
   mc_jet_AntiKt10Truth_eta = 0;
   mc_jet_AntiKt10Truth_phi = 0;
   mc_jet_AntiKt10Truth_m = 0;
   mc_jet_AntiKt10Truth_constitN = 0;
   mc_jet_AntiKt10Truth_constitIndex = 0;
   mc_jet_AntiKt10TruthTrimmed_E = 0;
   mc_jet_AntiKt10TruthTrimmed_pt = 0;
   mc_jet_AntiKt10TruthTrimmed_eta = 0;
   mc_jet_AntiKt10TruthTrimmed_phi = 0;
   mc_jet_AntiKt10TruthTrimmed_m = 0;
   mc_jet_AntiKt10TruthTrimmed_constitN = 0;
   mc_jet_AntiKt10TruthTrimmed_constitIndex = 0;
   mc_jet_AntiKt10TruthTrimmed_SPLIT12 = 0;
   mc_jet_AntiKt10TruthTrimmed_nBhad = 0;
   mc_jet_AntiKt4Truth_E = 0;
   mc_jet_AntiKt4Truth_pt = 0;
   mc_jet_AntiKt4Truth_m = 0;
   mc_jet_AntiKt4Truth_eta = 0;
   mc_jet_AntiKt4Truth_phi = 0;
   mc_jet_AntiKt4Truth_flavor_truth_trueflav = 0;
   ntt_fjet_pt = 0;
   ntt_fjet_eta = 0;
   ntt_fjet_phi = 0;
   ntt_fjet_E = 0;
   ntt_fjet_m = 0;
   ntt_fjet_m_orig = 0;
   ntt_fjet_d12 = 0;
   ntt_fjet_DeltaPhi_Lap_FatJet = 0;
   ntt_fjet_DeltaR_LapJet_Fatjet = 0;
   cl_pt = 0;
   cl_related_fatjet = 0;
   cl_related_jet = 0;
   cl_eta = 0;
   cl_phi = 0;
   cl_E_m = 0;
   cl_E_had = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("runNumber", &runNumber, &b_runNumber);
   fChain->SetBranchAddress("eventNumber", &eventNumber, &b_eventNumber);
   fChain->SetBranchAddress("channelNumber", &channelNumber, &b_channelNumber);
   fChain->SetBranchAddress("rndRunNumber", &rndRunNumber, &b_rndRunNumber);
   fChain->SetBranchAddress("dataPeriod", &dataPeriod, &b_dataPeriod);
   fChain->SetBranchAddress("mu", &mu, &b_mu);
   fChain->SetBranchAddress("mcevt_weight", &mcevt_weight, &b_mcevt_weight);
   fChain->SetBranchAddress("pvxp_n", &pvxp_n, &b_pvxp_n);
   fChain->SetBranchAddress("hfor", &hfor, &b_hfor);
   fChain->SetBranchAddress("vxp_z", &vxp_z, &b_vxp_z);
   fChain->SetBranchAddress("mc_vxp_z", &mc_vxp_z, &b_mc_vxp_z);
   fChain->SetBranchAddress("mcevt_pdf1", &mcevt_pdf1, &b_mcevt_pdf1);
   fChain->SetBranchAddress("mcevt_pdf2", &mcevt_pdf2, &b_mcevt_pdf2);
   fChain->SetBranchAddress("mcevt_pdf_id1", &mcevt_pdf_id1, &b_mcevt_pdf_id1);
   fChain->SetBranchAddress("mcevt_pdf_id2", &mcevt_pdf_id2, &b_mcevt_pdf_id2);
   fChain->SetBranchAddress("mcevt_pdf_scale", &mcevt_pdf_scale, &b_mcevt_pdf_scale);
   fChain->SetBranchAddress("mcevt_pdf_x1", &mcevt_pdf_x1, &b_mcevt_pdf_x1);
   fChain->SetBranchAddress("mcevt_pdf_x2", &mcevt_pdf_x2, &b_mcevt_pdf_x2);
   fChain->SetBranchAddress("lep_pt", &lep_pt, &b_lep_pt);
   fChain->SetBranchAddress("lep_eta", &lep_eta, &b_lep_eta);
   fChain->SetBranchAddress("lep_phi", &lep_phi, &b_lep_phi);
   fChain->SetBranchAddress("lep_E", &lep_E, &b_lep_E);
   fChain->SetBranchAddress("lep_charge", &lep_charge, &b_lep_charge);
   fChain->SetBranchAddress("el_cl_eta", &el_cl_eta, &b_el_cl_eta);
   fChain->SetBranchAddress("eptcone30", &eptcone30, &b_eptcone30);
   fChain->SetBranchAddress("eetcone20", &eetcone20, &b_eetcone20);
   fChain->SetBranchAddress("mptcone30", &mptcone30, &b_mptcone30);
   fChain->SetBranchAddress("metcone20", &metcone20, &b_metcone20);
   fChain->SetBranchAddress("m_eminiIso10_4", &m_eminiIso10_4, &b_eminiIso10_4);
   fChain->SetBranchAddress("m_mminiIso10_4", &m_mminiIso10_4, &b_mminiIso10_4);
   fChain->SetBranchAddress("met_sumet", &met_sumet, &b_met_sumet);
   fChain->SetBranchAddress("met_et", &met_et, &b_met_et);
   fChain->SetBranchAddress("met_phi", &met_phi, &b_met_phi);
   fChain->SetBranchAddress("mwt", &mwt, &b_mwt);
   fChain->SetBranchAddress("jet_n", &jet_n, &b_jet_n);
   fChain->SetBranchAddress("alljet_n", &alljet_n, &b_alljet_n);
   fChain->SetBranchAddress("jet_pt", jet_pt, &b_jet_pt);
   fChain->SetBranchAddress("jet_eta", jet_eta, &b_jet_eta);
   fChain->SetBranchAddress("jet_phi", jet_phi, &b_jet_phi);
   fChain->SetBranchAddress("jet_E", jet_E, &b_jet_E);
   fChain->SetBranchAddress("jet_jvf", jet_jvf, &b_jet_jvf);
   fChain->SetBranchAddress("jet_trueflav", jet_trueflav, &b_jet_trueflav);
   fChain->SetBranchAddress("jet_truthMatched", jet_truthMatched, &b_jet_truthMatched);
   fChain->SetBranchAddress("jet_SV0", jet_SV0, &b_jet_SV0);
   fChain->SetBranchAddress("jet_COMBNN", jet_COMBNN, &b_jet_COMBNN);
   fChain->SetBranchAddress("jet_MV1", jet_MV1, &b_jet_MV1);
   fChain->SetBranchAddress("jet_MV1c", jet_MV1c, &b_jet_MV1c);
   fChain->SetBranchAddress("jet_isSemilep", jet_isSemilep, &b_jet_isSemilep);
   fChain->SetBranchAddress("lastCutPassed", &lastCutPassed, &b_lastCutPassed);
   fChain->SetBranchAddress("mc_n", &mc_n, &b_mc_n);
   fChain->SetBranchAddress("mc_E", &mc_E, &b_mc_E);
   fChain->SetBranchAddress("mc_pt", &mc_pt, &b_mc_pt);
   fChain->SetBranchAddress("mc_eta", &mc_eta, &b_mc_eta);
   fChain->SetBranchAddress("mc_phi", &mc_phi, &b_mc_phi);
   fChain->SetBranchAddress("mc_m", &mc_m, &b_mc_m);
   fChain->SetBranchAddress("mc_status", &mc_status, &b_mc_status);
   fChain->SetBranchAddress("mc_barcode", &mc_barcode, &b_mc_barcode);
   fChain->SetBranchAddress("mc_pdgId", &mc_pdgId, &b_mc_pdgId);
   fChain->SetBranchAddress("mc_charge", &mc_charge, &b_mc_charge);
   fChain->SetBranchAddress("mc_parent_index", &mc_parent_index, &b_mc_parent_index);
   fChain->SetBranchAddress("mc_child_index", &mc_child_index, &b_mc_child_index);
   fChain->SetBranchAddress("mc_jet_AntiKt10Truth_n", &mc_jet_AntiKt10Truth_n, &b_mc_jet_AntiKt10Truth_n);
   fChain->SetBranchAddress("mc_jet_AntiKt10Truth_E", &mc_jet_AntiKt10Truth_E, &b_mc_jet_AntiKt10Truth_E);
   fChain->SetBranchAddress("mc_jet_AntiKt10Truth_pt", &mc_jet_AntiKt10Truth_pt, &b_mc_jet_AntiKt10Truth_pt);
   fChain->SetBranchAddress("mc_jet_AntiKt10Truth_eta", &mc_jet_AntiKt10Truth_eta, &b_mc_jet_AntiKt10Truth_eta);
   fChain->SetBranchAddress("mc_jet_AntiKt10Truth_phi", &mc_jet_AntiKt10Truth_phi, &b_mc_jet_AntiKt10Truth_phi);
   fChain->SetBranchAddress("mc_jet_AntiKt10Truth_m", &mc_jet_AntiKt10Truth_m, &b_mc_jet_AntiKt10Truth_m);
   fChain->SetBranchAddress("mc_jet_AntiKt10Truth_constitN", &mc_jet_AntiKt10Truth_constitN, &b_mc_jet_AntiKt10Truth_constitN);
   fChain->SetBranchAddress("mc_jet_AntiKt10Truth_constitIndex", &mc_jet_AntiKt10Truth_constitIndex, &b_mc_jet_AntiKt10Truth_constitIndex);
   fChain->SetBranchAddress("mc_jet_AntiKt10TruthTrimmed_n", &mc_jet_AntiKt10TruthTrimmed_n, &b_mc_jet_AntiKt10TruthTrimmedPtFrac5SmallR30_n);
   fChain->SetBranchAddress("mc_jet_AntiKt10TruthTrimmed_E", &mc_jet_AntiKt10TruthTrimmed_E, &b_mc_jet_AntiKt10TruthTrimmed_E);
   fChain->SetBranchAddress("mc_jet_AntiKt10TruthTrimmed_pt", &mc_jet_AntiKt10TruthTrimmed_pt, &b_mc_jet_AntiKt10TruthTrimmed_pt);
   fChain->SetBranchAddress("mc_jet_AntiKt10TruthTrimmed_eta", &mc_jet_AntiKt10TruthTrimmed_eta, &b_mc_jet_AntiKt10TruthTrimmed_eta);
   fChain->SetBranchAddress("mc_jet_AntiKt10TruthTrimmed_phi", &mc_jet_AntiKt10TruthTrimmed_phi, &b_mc_jet_AntiKt10TruthTrimmed_phi);
   fChain->SetBranchAddress("mc_jet_AntiKt10TruthTrimmed_m", &mc_jet_AntiKt10TruthTrimmed_m, &b_mc_jet_AntiKt10TruthTrimmed_m);
   fChain->SetBranchAddress("mc_jet_AntiKt10TruthTrimmed_constitN", &mc_jet_AntiKt10TruthTrimmed_constitN, &b_mc_jet_AntiKt10TruthTrimmed_constitN);
   fChain->SetBranchAddress("mc_jet_AntiKt10TruthTrimmed_constitIndex", &mc_jet_AntiKt10TruthTrimmed_constitIndex, &b_mc_jet_AntiKt10TruthTrimmed_constitIndex);
   fChain->SetBranchAddress("mc_jet_AntiKt10TruthTrimmed_SPLIT12", &mc_jet_AntiKt10TruthTrimmed_SPLIT12, &b_mc_jet_AntiKt10TruthTrimmed_SPLIT12);
   fChain->SetBranchAddress("mc_jet_AntiKt10TruthTrimmed_nBhad", &mc_jet_AntiKt10TruthTrimmed_nBhad, &b_mc_jet_AntiKt10TruthTrimmed_nBhad);
   fChain->SetBranchAddress("mc_jet_AntiKt4Truth_n", &mc_jet_AntiKt4Truth_n, &b_mc_jet_AntiKt4Truth_n);
   fChain->SetBranchAddress("mc_jet_AntiKt4Truth_E", &mc_jet_AntiKt4Truth_E, &b_mc_jet_AntiKt4Truth_E);
   fChain->SetBranchAddress("mc_jet_AntiKt4Truth_pt", &mc_jet_AntiKt4Truth_pt, &b_mc_jet_AntiKt4Truth_pt);
   fChain->SetBranchAddress("mc_jet_AntiKt4Truth_m", &mc_jet_AntiKt4Truth_m, &b_mc_jet_AntiKt4Truth_m);
   fChain->SetBranchAddress("mc_jet_AntiKt4Truth_eta", &mc_jet_AntiKt4Truth_eta, &b_mc_jet_AntiKt4Truth_eta);
   fChain->SetBranchAddress("mc_jet_AntiKt4Truth_phi", &mc_jet_AntiKt4Truth_phi, &b_mc_jet_AntiKt4Truth_phi);
   fChain->SetBranchAddress("mc_jet_AntiKt4Truth_flavor_truth_trueflav", &mc_jet_AntiKt4Truth_flavor_truth_trueflav, &b_mc_jet_AntiKt4Truth_flavor_truth_trueflav);
   fChain->SetBranchAddress("EF_e20_medium", &EF_e20_medium, &b_EF_e20_medium);
   fChain->SetBranchAddress("EF_e22_medium", &EF_e22_medium, &b_EF_e22_medium);
   fChain->SetBranchAddress("EF_e22_medium1", &EF_e22_medium1, &b_EF_e22_medium1);
   fChain->SetBranchAddress("EF_e22vh_medium1", &EF_e22vh_medium1, &b_EF_e22vh_medium1);
   fChain->SetBranchAddress("EF_e45_medium1", &EF_e45_medium1, &b_EF_e45_medium1);
   fChain->SetBranchAddress("EF_mu18", &EF_mu18, &b_EF_mu18);
   fChain->SetBranchAddress("EF_mu18_medium", &EF_mu18_medium, &b_EF_mu18_medium);
   fChain->SetBranchAddress("EF_j240_a10tc_EFFS", &EF_j240_a10tc_EFFS, &b_EF_j240_a10tc_EFFS);
   fChain->SetBranchAddress("OrigNumOfEventsInFile", &OrigNumOfEventsInFile, &b_OrigNumOfEventsInFile);
   fChain->SetBranchAddress("PUweight", &PUweight, &b_PUweight);
   fChain->SetBranchAddress("PUweightDe", &PUweightDe, &b_PUweightDe);
   fChain->SetBranchAddress("ZVxpWeight", &ZVxpWeight, &b_ZVxpWeight);
   fChain->SetBranchAddress("XSection", &XSection, &b_XSection);
   fChain->SetBranchAddress("KFactor", &KFactor, &b_KFactor);
   fChain->SetBranchAddress("JVFSFweight", &JVFSFweight, &b_JVFSFweight);
   fChain->SetBranchAddress("BTagSFweight", &BTagSFweight, &b_BTagSFweight);
   fChain->SetBranchAddress("totalScale", &totalScale, &b_totalScale);
   fChain->SetBranchAddress("elecScale", &elecScale, &b_elecScale);
   fChain->SetBranchAddress("muonScale", &muonScale, &b_muonScale);
   fChain->SetBranchAddress("trigScale", &trigScale, &b_trigScale);
   fChain->SetBranchAddress("WJetsShapeScale", &WJetsShapeScale, &b_WJetsShapeScale);
   fChain->SetBranchAddress("WJetsScale", &WJetsScale, &b_WJetsScale);
   fChain->SetBranchAddress("bTagCat", &bTagCat, &b_bTagCat);
   fChain->SetBranchAddress("Mtt", &Mtt, &b_Mtt);
   fChain->SetBranchAddress("chi2Min", &chi2Min, &b_chi2Min);
   fChain->SetBranchAddress("BoostedEvent", &BoostedEvent, &b_BoostedEvent);
   fChain->SetBranchAddress("ntt_fjet_n", &ntt_fjet_n, &b_ntt_fjet_n);
   fChain->SetBranchAddress("ntt_fjet_pt", &ntt_fjet_pt, &b_ntt_fjet_pt);
   fChain->SetBranchAddress("ntt_fjet_eta", &ntt_fjet_eta, &b_ntt_fjet_eta);
   fChain->SetBranchAddress("ntt_fjet_phi", &ntt_fjet_phi, &b_ntt_fjet_phi);
   fChain->SetBranchAddress("ntt_fjet_E", &ntt_fjet_E, &b_ntt_fjet_E);
   fChain->SetBranchAddress("ntt_fjet_m", &ntt_fjet_m, &b_ntt_fjet_m);
   fChain->SetBranchAddress("ntt_fjet_m_orig", &ntt_fjet_m_orig, &b_ntt_fjet_m_orig);
   fChain->SetBranchAddress("ntt_fjet_d12", &ntt_fjet_d12, &b_ntt_fjet_d12);
   fChain->SetBranchAddress("ntt_fjet_DeltaPhi_Lap_FatJet", &ntt_fjet_DeltaPhi_Lap_FatJet, &b_ntt_fjet_DeltaPhi_Lap_FatJet);
   fChain->SetBranchAddress("ntt_fjet_DeltaR_LapJet_Fatjet", &ntt_fjet_DeltaR_LapJet_Fatjet, &b_ntt_fjet_DeltaR_LapJet_Fatjet);
   fChain->SetBranchAddress("fjet_n", &fjet_n, &b_fjet_n);
   fChain->SetBranchAddress("fjet_pt", &fjet_pt, &b_fjet_pt);
   fChain->SetBranchAddress("fjet_eta", &fjet_eta, &b_fjet_eta);
   fChain->SetBranchAddress("fjet_phi", &fjet_phi, &b_fjet_phi);
   fChain->SetBranchAddress("fjet_E", &fjet_E, &b_fjet_E);
   fChain->SetBranchAddress("fjet_m", &fjet_m, &b_fjet_m);
   fChain->SetBranchAddress("fjet_m_orig", &fjet_m_orig, &b_fjet_m_orig);
   fChain->SetBranchAddress("fjet_d12", &fjet_d12, &b_fjet_d12);
   fChain->SetBranchAddress("fjet_DeltaPhi_Lap_FatJet", &fjet_DeltaPhi_Lap_FatJet, &b_fjet_DeltaPhi_Lap_FatJet);
   fChain->SetBranchAddress("fjet_DeltaR_LapJet_Fatjet", &fjet_DeltaR_LapJet_Fatjet, &b_fjet_DeltaR_LapJet_Fatjet);
   fChain->SetBranchAddress("hadtop_pt", &hadtop_pt, &b_hadtop_pt);
   fChain->SetBranchAddress("hadtop_eta", &hadtop_eta, &b_hadtop_eta);
   fChain->SetBranchAddress("hadtop_phi", &hadtop_phi, &b_hadtop_phi);
   fChain->SetBranchAddress("hadtop_e", &hadtop_e, &b_hadtop_e);
   fChain->SetBranchAddress("hadtop_m", &hadtop_m, &b_hadtop_m);
   fChain->SetBranchAddress("leptop_pt", &leptop_pt, &b_leptop_pt);
   fChain->SetBranchAddress("leptop_eta", &leptop_eta, &b_leptop_eta);
   fChain->SetBranchAddress("leptop_phi", &leptop_phi, &b_leptop_phi);
   fChain->SetBranchAddress("leptop_e", &leptop_e, &b_leptop_e);
   fChain->SetBranchAddress("leptop_m", &leptop_m, &b_leptop_m);
   fChain->SetBranchAddress("ditop_pt", &ditop_pt, &b_ditop_pt);
   fChain->SetBranchAddress("ditop_eta", &ditop_eta, &b_ditop_eta);
   fChain->SetBranchAddress("ditop_phi", &ditop_phi, &b_ditop_phi);
   fChain->SetBranchAddress("ditop_e", &ditop_e, &b_ditop_e);
   fChain->SetBranchAddress("ditop_m", &ditop_m, &b_ditop_m);
   fChain->SetBranchAddress("nu_pt", &nu_pt, &b_m_nu_pt);
   fChain->SetBranchAddress("nu_eta", &nu_eta, &b_m_nu_eta);
   fChain->SetBranchAddress("nu_phi", &nu_phi, &b_m_nu_phi);
   fChain->SetBranchAddress("nu_e", &nu_e, &b_m_nu_e);
   fChain->SetBranchAddress("nu_m", &nu_m, &b_m_nu_m);
   fChain->SetBranchAddress("w_pt", &w_pt, &b_m_w_pt);
   fChain->SetBranchAddress("w_eta", &w_eta, &b_m_w_eta);
   fChain->SetBranchAddress("w_phi", &w_phi, &b_m_w_phi);
   fChain->SetBranchAddress("w_e", &w_e, &b_m_w_e);
   fChain->SetBranchAddress("w_m", &w_m, &b_m_w_m);
   fChain->SetBranchAddress("w_charge", &w_charge, &b_m_w_charge);
   fChain->SetBranchAddress("cl_n", &cl_n, &b_cl_n);
   fChain->SetBranchAddress("cl_pt", &cl_pt, &b_cl_pt);
   fChain->SetBranchAddress("cl_related_fatjet", &cl_related_fatjet, &b_cl_related_fatjet);
   fChain->SetBranchAddress("cl_related_jet", &cl_related_jet, &b_cl_related_jet);
   fChain->SetBranchAddress("cl_eta", &cl_eta, &b_cl_eta);
   fChain->SetBranchAddress("cl_phi", &cl_phi, &b_cl_phi);
   fChain->SetBranchAddress("cl_E_m", &cl_E_m, &b_cl_E_m);
   fChain->SetBranchAddress("cl_E_had", &cl_E_had, &b_cl_E_had);
   Notify();
}

Bool_t TopMini::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void TopMini::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t TopMini::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef TopMini_cxx
