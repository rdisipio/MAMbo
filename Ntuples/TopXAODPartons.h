//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed Nov 25 14:53:57 2015 by ROOT version 6.02/12
// from TTree truth/tree
// found on file: ljets.output.root
//////////////////////////////////////////////////////////

#ifndef TopXAODPartons_h
#define TopXAODPartons_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>


// Header file for the classes stored in the TTree if any.
#include "vector"

using namespace std;

class TopXAODPartons {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Float_t         weight_mc;
   ULong64_t       eventNumber;
   UInt_t          runNumber;
   UInt_t          mcChannelNumber;
   vector<float>   *mc_pt;
   vector<float>   *mc_eta;
   vector<float>   *mc_phi;
   vector<float>   *mc_e;
   vector<int>     *mc_pdgId;
   vector<float>   *PDFinfo_X1;
   vector<float>   *PDFinfo_X2;
   vector<int>     *PDFinfo_PDGID1;
   vector<int>     *PDFinfo_PDGID2;
   vector<float>   *PDFinfo_Q;
   vector<float>   *PDFinfo_XF1;
   vector<float>   *PDFinfo_XF2;
   Int_t           MC_Wdecay2_from_t_pdgId;
   Int_t           MC_Wdecay2_from_tbar_pdgId;
   Int_t           MC_Wdecay1_from_tbar_pdgId;
   Int_t           MC_Wdecay1_from_t_pdgId;
   Float_t         MC_Wdecay2_from_tbar_eta;
   Float_t         MC_W_from_t_pt;
   Float_t         MC_Wdecay1_from_tbar_pt;
   Float_t         MC_W_from_t_m;
   Float_t         MC_W_from_t_phi;
   Float_t         MC_tbar_beforeFSR_m;
   Float_t         MC_t_beforeFSR_eta;
   Float_t         MC_ttbar_beforeFSR_m;
   Float_t         MC_ttbar_beforeFSR_pt;
   Float_t         MC_Wdecay2_from_tbar_phi;
   Float_t         MC_ttbar_beforeFSR_eta;
   Float_t         MC_t_beforeFSR_m;
   Float_t         MC_Wdecay2_from_t_pt;
   Float_t         MC_Wdecay2_from_t_eta;
   Float_t         MC_ttbar_beforeFSR_phi;
   Float_t         MC_ttbar_afterFSR_phi;
   Float_t         MC_W_from_tbar_pt;
   Float_t         MC_tbar_beforeFSR_pt;
   Float_t         MC_b_from_t_m;
   Float_t         MC_Wdecay2_from_t_phi;
   Float_t         MC_W_from_tbar_m;
   Float_t         MC_ttbar_afterFSR_pt;
   Float_t         MC_Wdecay1_from_tbar_m;
   Float_t         MC_ttbar_afterFSR_m;
   Float_t         MC_ttbar_afterFSR_eta;
   Float_t         MC_W_from_tbar_eta;
   Float_t         MC_t_beforeFSR_pt;
   Float_t         MC_W_from_tbar_phi;
   Float_t         MC_b_from_t_pt;
   Float_t         MC_b_from_t_eta;
   Float_t         MC_W_from_t_eta;
   Float_t         MC_b_from_tbar_pt;
   Float_t         MC_tbar_beforeFSR_eta;
   Float_t         MC_Wdecay2_from_tbar_m;
   Float_t         MC_b_from_tbar_m;
   Float_t         MC_b_from_tbar_phi;
   Float_t         MC_tbar_beforeFSR_phi;
   Float_t         MC_Wdecay1_from_t_m;
   Float_t         MC_Wdecay1_from_t_pt;
   Float_t         MC_Wdecay1_from_t_eta;
   Float_t         MC_Wdecay1_from_t_phi;
   Float_t         MC_Wdecay1_from_tbar_eta;
   Float_t         MC_t_beforeFSR_phi;
   Float_t         MC_Wdecay1_from_tbar_phi;
   Float_t         MC_b_from_t_phi;
   Float_t         MC_Wdecay2_from_t_m;
   Float_t         MC_b_from_tbar_eta;
   Float_t         MC_Wdecay2_from_tbar_pt;

   // List of branches
   TBranch        *b_weight_mc;   //!
   TBranch        *b_eventNumber;   //!
   TBranch        *b_runNumber;   //!
   TBranch        *b_mcChannelNumber;   //!
   TBranch        *b_mc_pt;   //!
   TBranch        *b_mc_eta;   //!
   TBranch        *b_mc_phi;   //!
   TBranch        *b_mc_e;   //!
   TBranch        *b_mc_pdgId;   //!
   TBranch        *b_PDFinfo_X1;   //!
   TBranch        *b_PDFinfo_X2;   //!
   TBranch        *b_PDFinfo_PDGID1;   //!
   TBranch        *b_PDFinfo_PDGID2;   //!
   TBranch        *b_PDFinfo_Q;   //!
   TBranch        *b_PDFinfo_XF1;   //!
   TBranch        *b_PDFinfo_XF2;   //!
   TBranch        *b_MC_Wdecay2_from_t_pdgId;   //!
   TBranch        *b_MC_Wdecay2_from_tbar_pdgId;   //!
   TBranch        *b_MC_Wdecay1_from_tbar_pdgId;   //!
   TBranch        *b_MC_Wdecay1_from_t_pdgId;   //!
   TBranch        *b_MC_Wdecay2_from_tbar_eta;   //!
   TBranch        *b_MC_W_from_t_pt;   //!
   TBranch        *b_MC_Wdecay1_from_tbar_pt;   //!
   TBranch        *b_MC_W_from_t_m;   //!
   TBranch        *b_MC_W_from_t_phi;   //!
   TBranch        *b_MC_tbar_beforeFSR_m;   //!
   TBranch        *b_MC_t_beforeFSR_eta;   //!
   TBranch        *b_MC_ttbar_beforeFSR_m;   //!
   TBranch        *b_MC_ttbar_beforeFSR_pt;   //!
   TBranch        *b_MC_Wdecay2_from_tbar_phi;   //!
   TBranch        *b_MC_ttbar_beforeFSR_eta;   //!
   TBranch        *b_MC_t_beforeFSR_m;   //!
   TBranch        *b_MC_Wdecay2_from_t_pt;   //!
   TBranch        *b_MC_Wdecay2_from_t_eta;   //!
   TBranch        *b_MC_ttbar_beforeFSR_phi;   //!
   TBranch        *b_MC_ttbar_afterFSR_phi;   //!
   TBranch        *b_MC_W_from_tbar_pt;   //!
   TBranch        *b_MC_tbar_beforeFSR_pt;   //!
   TBranch        *b_MC_b_from_t_m;   //!
   TBranch        *b_MC_Wdecay2_from_t_phi;   //!
   TBranch        *b_MC_W_from_tbar_m;   //!
   TBranch        *b_MC_ttbar_afterFSR_pt;   //!
   TBranch        *b_MC_Wdecay1_from_tbar_m;   //!
   TBranch        *b_MC_ttbar_afterFSR_m;   //!
   TBranch        *b_MC_ttbar_afterFSR_eta;   //!
   TBranch        *b_MC_W_from_tbar_eta;   //!
   TBranch        *b_MC_t_beforeFSR_pt;   //!
   TBranch        *b_MC_W_from_tbar_phi;   //!
   TBranch        *b_MC_b_from_t_pt;   //!
   TBranch        *b_MC_b_from_t_eta;   //!
   TBranch        *b_MC_W_from_t_eta;   //!
   TBranch        *b_MC_b_from_tbar_pt;   //!
   TBranch        *b_MC_tbar_beforeFSR_eta;   //!
   TBranch        *b_MC_Wdecay2_from_tbar_m;   //!
   TBranch        *b_MC_b_from_tbar_m;   //!
   TBranch        *b_MC_b_from_tbar_phi;   //!
   TBranch        *b_MC_tbar_beforeFSR_phi;   //!
   TBranch        *b_MC_Wdecay1_from_t_m;   //!
   TBranch        *b_MC_Wdecay1_from_t_pt;   //!
   TBranch        *b_MC_Wdecay1_from_t_eta;   //!
   TBranch        *b_MC_Wdecay1_from_t_phi;   //!
   TBranch        *b_MC_Wdecay1_from_tbar_eta;   //!
   TBranch        *b_MC_t_beforeFSR_phi;   //!
   TBranch        *b_MC_Wdecay1_from_tbar_phi;   //!
   TBranch        *b_MC_b_from_t_phi;   //!
   TBranch        *b_MC_Wdecay2_from_t_m;   //!
   TBranch        *b_MC_b_from_tbar_eta;   //!
   TBranch        *b_MC_Wdecay2_from_tbar_pt;   //!

   TopXAODPartons(TTree *tree=0);
   virtual ~TopXAODPartons();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef TopXAODPartons_cxx
TopXAODPartons::TopXAODPartons(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("ljets.output.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("ljets.output.root");
      }
      f->GetObject("truth",tree);

   }
   Init(tree);
}

TopXAODPartons::~TopXAODPartons()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t TopXAODPartons::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t TopXAODPartons::LoadTree(Long64_t entry)
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

void TopXAODPartons::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   mc_pt = 0;
   mc_eta = 0;
   mc_phi = 0;
   mc_e = 0;
   mc_pdgId = 0;
   PDFinfo_X1 = 0;
   PDFinfo_X2 = 0;
   PDFinfo_PDGID1 = 0;
   PDFinfo_PDGID2 = 0;
   PDFinfo_Q = 0;
   PDFinfo_XF1 = 0;
   PDFinfo_XF2 = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("weight_mc", &weight_mc, &b_weight_mc);
   fChain->SetBranchAddress("eventNumber", &eventNumber, &b_eventNumber);
   fChain->SetBranchAddress("runNumber", &runNumber, &b_runNumber);
   fChain->SetBranchAddress("mcChannelNumber", &mcChannelNumber, &b_mcChannelNumber);
   fChain->SetBranchAddress("mc_pt", &mc_pt, &b_mc_pt);
   fChain->SetBranchAddress("mc_eta", &mc_eta, &b_mc_eta);
   fChain->SetBranchAddress("mc_phi", &mc_phi, &b_mc_phi);
   fChain->SetBranchAddress("mc_e", &mc_e, &b_mc_e);
   fChain->SetBranchAddress("mc_pdgId", &mc_pdgId, &b_mc_pdgId);
   fChain->SetBranchAddress("PDFinfo_X1", &PDFinfo_X1, &b_PDFinfo_X1);
   fChain->SetBranchAddress("PDFinfo_X2", &PDFinfo_X2, &b_PDFinfo_X2);
   fChain->SetBranchAddress("PDFinfo_PDGID1", &PDFinfo_PDGID1, &b_PDFinfo_PDGID1);
   fChain->SetBranchAddress("PDFinfo_PDGID2", &PDFinfo_PDGID2, &b_PDFinfo_PDGID2);
   fChain->SetBranchAddress("PDFinfo_Q", &PDFinfo_Q, &b_PDFinfo_Q);
   fChain->SetBranchAddress("PDFinfo_XF1", &PDFinfo_XF1, &b_PDFinfo_XF1);
   fChain->SetBranchAddress("PDFinfo_XF2", &PDFinfo_XF2, &b_PDFinfo_XF2);
   fChain->SetBranchAddress("MC_Wdecay2_from_t_pdgId", &MC_Wdecay2_from_t_pdgId, &b_MC_Wdecay2_from_t_pdgId);
   fChain->SetBranchAddress("MC_Wdecay2_from_tbar_pdgId", &MC_Wdecay2_from_tbar_pdgId, &b_MC_Wdecay2_from_tbar_pdgId);
   fChain->SetBranchAddress("MC_Wdecay1_from_tbar_pdgId", &MC_Wdecay1_from_tbar_pdgId, &b_MC_Wdecay1_from_tbar_pdgId);
   fChain->SetBranchAddress("MC_Wdecay1_from_t_pdgId", &MC_Wdecay1_from_t_pdgId, &b_MC_Wdecay1_from_t_pdgId);
   fChain->SetBranchAddress("MC_Wdecay2_from_tbar_eta", &MC_Wdecay2_from_tbar_eta, &b_MC_Wdecay2_from_tbar_eta);
   fChain->SetBranchAddress("MC_W_from_t_pt", &MC_W_from_t_pt, &b_MC_W_from_t_pt);
   fChain->SetBranchAddress("MC_Wdecay1_from_tbar_pt", &MC_Wdecay1_from_tbar_pt, &b_MC_Wdecay1_from_tbar_pt);
   fChain->SetBranchAddress("MC_W_from_t_m", &MC_W_from_t_m, &b_MC_W_from_t_m);
   fChain->SetBranchAddress("MC_W_from_t_phi", &MC_W_from_t_phi, &b_MC_W_from_t_phi);
   fChain->SetBranchAddress("MC_tbar_beforeFSR_m", &MC_tbar_beforeFSR_m, &b_MC_tbar_beforeFSR_m);
   fChain->SetBranchAddress("MC_t_beforeFSR_eta", &MC_t_beforeFSR_eta, &b_MC_t_beforeFSR_eta);
   fChain->SetBranchAddress("MC_ttbar_beforeFSR_m", &MC_ttbar_beforeFSR_m, &b_MC_ttbar_beforeFSR_m);
   fChain->SetBranchAddress("MC_ttbar_beforeFSR_pt", &MC_ttbar_beforeFSR_pt, &b_MC_ttbar_beforeFSR_pt);
   fChain->SetBranchAddress("MC_Wdecay2_from_tbar_phi", &MC_Wdecay2_from_tbar_phi, &b_MC_Wdecay2_from_tbar_phi);
   fChain->SetBranchAddress("MC_ttbar_beforeFSR_eta", &MC_ttbar_beforeFSR_eta, &b_MC_ttbar_beforeFSR_eta);
   fChain->SetBranchAddress("MC_t_beforeFSR_m", &MC_t_beforeFSR_m, &b_MC_t_beforeFSR_m);
   fChain->SetBranchAddress("MC_Wdecay2_from_t_pt", &MC_Wdecay2_from_t_pt, &b_MC_Wdecay2_from_t_pt);
   fChain->SetBranchAddress("MC_Wdecay2_from_t_eta", &MC_Wdecay2_from_t_eta, &b_MC_Wdecay2_from_t_eta);
   fChain->SetBranchAddress("MC_ttbar_beforeFSR_phi", &MC_ttbar_beforeFSR_phi, &b_MC_ttbar_beforeFSR_phi);
   fChain->SetBranchAddress("MC_ttbar_afterFSR_phi", &MC_ttbar_afterFSR_phi, &b_MC_ttbar_afterFSR_phi);
   fChain->SetBranchAddress("MC_W_from_tbar_pt", &MC_W_from_tbar_pt, &b_MC_W_from_tbar_pt);
   fChain->SetBranchAddress("MC_tbar_beforeFSR_pt", &MC_tbar_beforeFSR_pt, &b_MC_tbar_beforeFSR_pt);
   fChain->SetBranchAddress("MC_b_from_t_m", &MC_b_from_t_m, &b_MC_b_from_t_m);
   fChain->SetBranchAddress("MC_Wdecay2_from_t_phi", &MC_Wdecay2_from_t_phi, &b_MC_Wdecay2_from_t_phi);
   fChain->SetBranchAddress("MC_W_from_tbar_m", &MC_W_from_tbar_m, &b_MC_W_from_tbar_m);
   fChain->SetBranchAddress("MC_ttbar_afterFSR_pt", &MC_ttbar_afterFSR_pt, &b_MC_ttbar_afterFSR_pt);
   fChain->SetBranchAddress("MC_Wdecay1_from_tbar_m", &MC_Wdecay1_from_tbar_m, &b_MC_Wdecay1_from_tbar_m);
   fChain->SetBranchAddress("MC_ttbar_afterFSR_m", &MC_ttbar_afterFSR_m, &b_MC_ttbar_afterFSR_m);
   fChain->SetBranchAddress("MC_ttbar_afterFSR_eta", &MC_ttbar_afterFSR_eta, &b_MC_ttbar_afterFSR_eta);
   fChain->SetBranchAddress("MC_W_from_tbar_eta", &MC_W_from_tbar_eta, &b_MC_W_from_tbar_eta);
   fChain->SetBranchAddress("MC_t_beforeFSR_pt", &MC_t_beforeFSR_pt, &b_MC_t_beforeFSR_pt);
   fChain->SetBranchAddress("MC_W_from_tbar_phi", &MC_W_from_tbar_phi, &b_MC_W_from_tbar_phi);
   fChain->SetBranchAddress("MC_b_from_t_pt", &MC_b_from_t_pt, &b_MC_b_from_t_pt);
   fChain->SetBranchAddress("MC_b_from_t_eta", &MC_b_from_t_eta, &b_MC_b_from_t_eta);
   fChain->SetBranchAddress("MC_W_from_t_eta", &MC_W_from_t_eta, &b_MC_W_from_t_eta);
   fChain->SetBranchAddress("MC_b_from_tbar_pt", &MC_b_from_tbar_pt, &b_MC_b_from_tbar_pt);
   fChain->SetBranchAddress("MC_tbar_beforeFSR_eta", &MC_tbar_beforeFSR_eta, &b_MC_tbar_beforeFSR_eta);
   fChain->SetBranchAddress("MC_Wdecay2_from_tbar_m", &MC_Wdecay2_from_tbar_m, &b_MC_Wdecay2_from_tbar_m);
   fChain->SetBranchAddress("MC_b_from_tbar_m", &MC_b_from_tbar_m, &b_MC_b_from_tbar_m);
   fChain->SetBranchAddress("MC_b_from_tbar_phi", &MC_b_from_tbar_phi, &b_MC_b_from_tbar_phi);
   fChain->SetBranchAddress("MC_tbar_beforeFSR_phi", &MC_tbar_beforeFSR_phi, &b_MC_tbar_beforeFSR_phi);
   fChain->SetBranchAddress("MC_Wdecay1_from_t_m", &MC_Wdecay1_from_t_m, &b_MC_Wdecay1_from_t_m);
   fChain->SetBranchAddress("MC_Wdecay1_from_t_pt", &MC_Wdecay1_from_t_pt, &b_MC_Wdecay1_from_t_pt);
   fChain->SetBranchAddress("MC_Wdecay1_from_t_eta", &MC_Wdecay1_from_t_eta, &b_MC_Wdecay1_from_t_eta);
   fChain->SetBranchAddress("MC_Wdecay1_from_t_phi", &MC_Wdecay1_from_t_phi, &b_MC_Wdecay1_from_t_phi);
   fChain->SetBranchAddress("MC_Wdecay1_from_tbar_eta", &MC_Wdecay1_from_tbar_eta, &b_MC_Wdecay1_from_tbar_eta);
   fChain->SetBranchAddress("MC_t_beforeFSR_phi", &MC_t_beforeFSR_phi, &b_MC_t_beforeFSR_phi);
   fChain->SetBranchAddress("MC_Wdecay1_from_tbar_phi", &MC_Wdecay1_from_tbar_phi, &b_MC_Wdecay1_from_tbar_phi);
   fChain->SetBranchAddress("MC_b_from_t_phi", &MC_b_from_t_phi, &b_MC_b_from_t_phi);
   fChain->SetBranchAddress("MC_Wdecay2_from_t_m", &MC_Wdecay2_from_t_m, &b_MC_Wdecay2_from_t_m);
   fChain->SetBranchAddress("MC_b_from_tbar_eta", &MC_b_from_tbar_eta, &b_MC_b_from_tbar_eta);
   fChain->SetBranchAddress("MC_Wdecay2_from_tbar_pt", &MC_Wdecay2_from_tbar_pt, &b_MC_Wdecay2_from_tbar_pt);
   Notify();
}

Bool_t TopXAODPartons::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void TopXAODPartons::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t TopXAODPartons::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef TopXAODPartons_cxx
