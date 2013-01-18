//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed Jan 16 15:00:46 2013 by ROOT version 5.32/04
// from TTree mini/4-vectors + variables required for scaling factors
// found on file: el.root
//////////////////////////////////////////////////////////

#ifndef MiniSLBoost_h
#define MiniSLBoost_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

// Fixed size dimensions of array or collections stored in the TTree if any.
using namespace std;

class MiniSLBoost {
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
   Float_t         eventWeight;
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
   Float_t         met_sumet;
   Float_t         met_et;
   Float_t         met_phi;
   Float_t         mwt;
   UInt_t          jet_n;
   UInt_t          alljet_n;
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
   Bool_t          EF_e20_medium;
   Bool_t          EF_e22_medium;
   Bool_t          EF_e22_medium1;
   Bool_t          EF_e22vh_medium1;
   Bool_t          EF_e45_medium1;
   Bool_t          EF_mu18;
   Bool_t          EF_mu18_medium;
   Bool_t          EF_j240_a10tc_EFFS;
   Int_t           OrigNumOfEventsInFile;
   UInt_t          fjet_n;
   Float_t         fjet_pt[1];   //[fjet_n]
   Float_t         fjet_eta[1];   //[fjet_n]
   Float_t         fjet_phi[1];   //[fjet_n]
   Float_t         fjet_E[1];   //[fjet_n]
   Float_t         fjet_m[1];   //[fjet_n]
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

   // List of branches
   TBranch        *b_runNumber;   //!
   TBranch        *b_eventNumber;   //!
   TBranch        *b_channelNumber;   //!
   TBranch        *b_rndRunNumber;   //!
   TBranch        *b_dataPeriod;   //!
   TBranch        *b_mu;   //!
   TBranch        *b_eventWeight;   //!
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
   TBranch        *b_EF_e20_medium;   //!
   TBranch        *b_EF_e22_medium;   //!
   TBranch        *b_EF_e22_medium1;   //!
   TBranch        *b_EF_e22vh_medium1;   //!
   TBranch        *b_EF_e45_medium1;   //!
   TBranch        *b_EF_mu18;   //!
   TBranch        *b_EF_mu18_medium;   //!
   TBranch        *b_EF_j240_a10tc_EFFS;   //!
   TBranch        *b_OrigNumOfEventsInFile;   //!
   TBranch        *b_fjet_n;   //!
   TBranch        *b_fjet_pt;   //!
   TBranch        *b_fjet_eta;   //!
   TBranch        *b_fjet_phi;   //!
   TBranch        *b_fjet_E;   //!
   TBranch        *b_fjet_m;   //!
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

   MiniSLBoost(TTree *tree=0);
   virtual ~MiniSLBoost();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef MiniSLBoost_cxx
MiniSLBoost::MiniSLBoost(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("el.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("el.root");
      }
      f->GetObject("mini",tree);

   }
   Init(tree);
}

MiniSLBoost::~MiniSLBoost()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t MiniSLBoost::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t MiniSLBoost::LoadTree(Long64_t entry)
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

void MiniSLBoost::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

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
   fChain->SetBranchAddress("eventWeight", &eventWeight, &b_eventWeight);
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
   fChain->SetBranchAddress("EF_e20_medium", &EF_e20_medium, &b_EF_e20_medium);
   fChain->SetBranchAddress("EF_e22_medium", &EF_e22_medium, &b_EF_e22_medium);
   fChain->SetBranchAddress("EF_e22_medium1", &EF_e22_medium1, &b_EF_e22_medium1);
   fChain->SetBranchAddress("EF_e22vh_medium1", &EF_e22vh_medium1, &b_EF_e22vh_medium1);
   fChain->SetBranchAddress("EF_e45_medium1", &EF_e45_medium1, &b_EF_e45_medium1);
   fChain->SetBranchAddress("EF_mu18", &EF_mu18, &b_EF_mu18);
   fChain->SetBranchAddress("EF_mu18_medium", &EF_mu18_medium, &b_EF_mu18_medium);
   fChain->SetBranchAddress("EF_j240_a10tc_EFFS", &EF_j240_a10tc_EFFS, &b_EF_j240_a10tc_EFFS);
   fChain->SetBranchAddress("OrigNumOfEventsInFile", &OrigNumOfEventsInFile, &b_OrigNumOfEventsInFile);
   fChain->SetBranchAddress("fjet_n", &fjet_n, &b_fjet_n);
   fChain->SetBranchAddress("fjet_pt", fjet_pt, &b_fjet_pt);
   fChain->SetBranchAddress("fjet_eta", fjet_eta, &b_fjet_eta);
   fChain->SetBranchAddress("fjet_phi", fjet_phi, &b_fjet_phi);
   fChain->SetBranchAddress("fjet_E", fjet_E, &b_fjet_E);
   fChain->SetBranchAddress("fjet_m", fjet_m, &b_fjet_m);
   fChain->SetBranchAddress("fjet_d12", fjet_d12, &b_fjet_d12);
   fChain->SetBranchAddress("fjet_DeltaPhi_Lap_FatJet", fjet_DeltaPhi_Lap_FatJet, &b_fjet_DeltaPhi_Lap_FatJet);
   fChain->SetBranchAddress("fjet_DeltaR_LapJet_Fatjet", fjet_DeltaR_LapJet_Fatjet, &b_fjet_DeltaR_LapJet_Fatjet);
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
   Notify();
}

Bool_t MiniSLBoost::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void MiniSLBoost::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t MiniSLBoost::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef MiniSLBoost_cxx
