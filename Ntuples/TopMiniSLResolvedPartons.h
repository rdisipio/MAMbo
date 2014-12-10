//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Tue Nov  4 14:36:22 2014 by ROOT version 5.34/19
// from TTree partons/Partons and association with top decay
// found on file: /home/ATLAS-T3/mromano/testarea/unversioned/Resolved8TeV/AnalysisTop-1.8.0/grid/examples_mc/mc.root
//////////////////////////////////////////////////////////

#ifndef TopMiniSLResolvedPartons_h
#define TopMiniSLResolvedPartons_h
//#define TopMiniSLResolvedPartons_cxx

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

// Fixed size dimensions of array or collections stored in the TTree if any.

class TopMiniSLResolvedPartons {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   Int_t           runNumber;
   Int_t           eventNumber;
   Int_t           parton_topQuark_n;
   Float_t         parton_topQuark_m[2];   //[parton_topQuark_n]
   Float_t         parton_topQuark_pt[2];   //[parton_topQuark_n]
   Float_t         parton_topQuark_eta[2];   //[parton_topQuark_n]
   Float_t         parton_topQuark_phi[2];   //[parton_topQuark_n]
   Int_t           parton_topQuark_status[2];   //[parton_topQuark_n]
   Int_t           parton_topQuark_isHadronic[2];   //[parton_topQuark_n]
   Int_t           parton_topQuark_pdgId[2];   //[parton_topQuark_n]
   Int_t           parton_bQuark_n;
   Float_t         parton_bQuark_m[9];   //[parton_bQuark_n]
   Float_t         parton_bQuark_pt[9];   //[parton_bQuark_n]
   Float_t         parton_bQuark_eta[9];   //[parton_bQuark_n]
   Float_t         parton_bQuark_phi[9];   //[parton_bQuark_n]
   Bool_t          parton_bQuark_from_top[9];   //[parton_bQuark_n]
   Int_t           parton_bQuark_status[9];   //[parton_bQuark_n]
   Int_t           parton_bQuark_pdgId[9];   //[parton_bQuark_n]
   Int_t           parton_cQuark_n;
   Float_t         parton_cQuark_m[12];   //[parton_cQuark_n]
   Float_t         parton_cQuark_pt[12];   //[parton_cQuark_n]
   Float_t         parton_cQuark_eta[12];   //[parton_cQuark_n]
   Float_t         parton_cQuark_phi[12];   //[parton_cQuark_n]
   Bool_t          parton_cQuark_from_top[12];   //[parton_cQuark_n]
   Int_t           parton_cQuark_status[12];   //[parton_cQuark_n]
   Int_t           parton_cQuark_pdgId[12];   //[parton_cQuark_n]
   Int_t           parton_Wboson_n;
   Float_t         parton_Wboson_m[6];   //[parton_Wboson_n]
   Float_t         parton_Wboson_pt[6];   //[parton_Wboson_n]
   Float_t         parton_Wboson_eta[6];   //[parton_Wboson_n]
   Float_t         parton_Wboson_phi[6];   //[parton_Wboson_n]
   Bool_t          parton_Wboson_from_top[6];   //[parton_Wboson_n]
   Int_t           parton_Wboson_status[6];   //[parton_Wboson_n]
   Int_t           parton_Wboson_isHadronic[6];   //[parton_Wboson_n]
   Int_t           parton_Wboson_pdgId[6];   //[parton_Wboson_n]

   // List of branches
   TBranch        *b_runNumber;   //!
   TBranch        *b_eventNumber;   //!
   TBranch        *b_parton_topQuark_n;   //!
   TBranch        *b_parton_topQuark_m;   //!
   TBranch        *b_parton_topQuark_pt;   //!
   TBranch        *b_parton_topQuark_eta;   //!
   TBranch        *b_parton_topQuark_phi;   //!
   TBranch        *b_parton_topQuark_status;   //!
   TBranch        *b_parton_topQuark_isHadronic;   //!
   TBranch        *b_parton_topQuark_pdgId;   //!
   TBranch        *b_parton_bQuark_n;   //!
   TBranch        *b_parton_bQuark_m;   //!
   TBranch        *b_parton_bQuark_pt;   //!
   TBranch        *b_parton_bQuark_eta;   //!
   TBranch        *b_parton_bQuark_phi;   //!
   TBranch        *b_parton_bQuark_from_top;   //!
   TBranch        *b_parton_bQuark_status;   //!
   TBranch        *b_parton_bQuark_pdgId;   //!
   TBranch        *b_parton_cQuark_n;   //!
   TBranch        *b_parton_cQuark_m;   //!
   TBranch        *b_parton_cQuark_pt;   //!
   TBranch        *b_parton_cQuark_eta;   //!
   TBranch        *b_parton_cQuark_phi;   //!
   TBranch        *b_parton_cQuark_from_top;   //!
   TBranch        *b_parton_cQuark_status;   //!
   TBranch        *b_parton_cQuark_pdgId;   //!
   TBranch        *b_parton_Wboson_n;   //!
   TBranch        *b_parton_Wboson_m;   //!
   TBranch        *b_parton_Wboson_pt;   //!
   TBranch        *b_parton_Wboson_eta;   //!
   TBranch        *b_parton_Wboson_phi;   //!
   TBranch        *b_parton_Wboson_from_top;   //!
   TBranch        *b_parton_Wboson_status;   //!
   TBranch        *b_parton_Wboson_isHadronic;   //!
   TBranch        *b_parton_Wboson_pdgId;   //!

   TopMiniSLResolvedPartons(TTree *tree=0);
   virtual ~TopMiniSLResolvedPartons();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef TopMiniSLResolvedPartons_cxx
TopMiniSLResolvedPartons::TopMiniSLResolvedPartons(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("/home/ATLAS-T3/mromano/testarea/unversioned/Resolved8TeV/AnalysisTop-1.8.0/grid/examples_mc/mc.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("/home/ATLAS-T3/mromano/testarea/unversioned/Resolved8TeV/AnalysisTop-1.8.0/grid/examples_mc/mc.root");
      }
      f->GetObject("partons",tree);

   }
   Init(tree);
}

TopMiniSLResolvedPartons::~TopMiniSLResolvedPartons()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t TopMiniSLResolvedPartons::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t TopMiniSLResolvedPartons::LoadTree(Long64_t entry)
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

void TopMiniSLResolvedPartons::Init(TTree *tree)
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
   fChain->SetBranchAddress("parton_topQuark_n", &parton_topQuark_n, &b_parton_topQuark_n);
   fChain->SetBranchAddress("parton_topQuark_m", parton_topQuark_m, &b_parton_topQuark_m);
   fChain->SetBranchAddress("parton_topQuark_pt", parton_topQuark_pt, &b_parton_topQuark_pt);
   fChain->SetBranchAddress("parton_topQuark_eta", parton_topQuark_eta, &b_parton_topQuark_eta);
   fChain->SetBranchAddress("parton_topQuark_phi", parton_topQuark_phi, &b_parton_topQuark_phi);
   fChain->SetBranchAddress("parton_topQuark_status", parton_topQuark_status, &b_parton_topQuark_status);
   fChain->SetBranchAddress("parton_topQuark_isHadronic", parton_topQuark_isHadronic, &b_parton_topQuark_isHadronic);
   fChain->SetBranchAddress("parton_topQuark_pdgId", parton_topQuark_pdgId, &b_parton_topQuark_pdgId);
   fChain->SetBranchAddress("parton_bQuark_n", &parton_bQuark_n, &b_parton_bQuark_n);
   fChain->SetBranchAddress("parton_bQuark_m", parton_bQuark_m, &b_parton_bQuark_m);
   fChain->SetBranchAddress("parton_bQuark_pt", parton_bQuark_pt, &b_parton_bQuark_pt);
   fChain->SetBranchAddress("parton_bQuark_eta", parton_bQuark_eta, &b_parton_bQuark_eta);
   fChain->SetBranchAddress("parton_bQuark_phi", parton_bQuark_phi, &b_parton_bQuark_phi);
   fChain->SetBranchAddress("parton_bQuark_from_top", parton_bQuark_from_top, &b_parton_bQuark_from_top);
   fChain->SetBranchAddress("parton_bQuark_status", parton_bQuark_status, &b_parton_bQuark_status);
   fChain->SetBranchAddress("parton_bQuark_pdgId", parton_bQuark_pdgId, &b_parton_bQuark_pdgId);
   fChain->SetBranchAddress("parton_cQuark_n", &parton_cQuark_n, &b_parton_cQuark_n);
   fChain->SetBranchAddress("parton_cQuark_m", parton_cQuark_m, &b_parton_cQuark_m);
   fChain->SetBranchAddress("parton_cQuark_pt", parton_cQuark_pt, &b_parton_cQuark_pt);
   fChain->SetBranchAddress("parton_cQuark_eta", parton_cQuark_eta, &b_parton_cQuark_eta);
   fChain->SetBranchAddress("parton_cQuark_phi", parton_cQuark_phi, &b_parton_cQuark_phi);
   fChain->SetBranchAddress("parton_cQuark_from_top", parton_cQuark_from_top, &b_parton_cQuark_from_top);
   fChain->SetBranchAddress("parton_cQuark_status", parton_cQuark_status, &b_parton_cQuark_status);
   fChain->SetBranchAddress("parton_cQuark_pdgId", parton_cQuark_pdgId, &b_parton_cQuark_pdgId);
   fChain->SetBranchAddress("parton_Wboson_n", &parton_Wboson_n, &b_parton_Wboson_n);
   fChain->SetBranchAddress("parton_Wboson_m", parton_Wboson_m, &b_parton_Wboson_m);
   fChain->SetBranchAddress("parton_Wboson_pt", parton_Wboson_pt, &b_parton_Wboson_pt);
   fChain->SetBranchAddress("parton_Wboson_eta", parton_Wboson_eta, &b_parton_Wboson_eta);
   fChain->SetBranchAddress("parton_Wboson_phi", parton_Wboson_phi, &b_parton_Wboson_phi);
   fChain->SetBranchAddress("parton_Wboson_from_top", parton_Wboson_from_top, &b_parton_Wboson_from_top);
   fChain->SetBranchAddress("parton_Wboson_status", parton_Wboson_status, &b_parton_Wboson_status);
   fChain->SetBranchAddress("parton_Wboson_isHadronic", parton_Wboson_isHadronic, &b_parton_Wboson_isHadronic);
   fChain->SetBranchAddress("parton_Wboson_pdgId", parton_Wboson_pdgId, &b_parton_Wboson_pdgId);
   Notify();
}

Bool_t TopMiniSLResolvedPartons::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void TopMiniSLResolvedPartons::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t TopMiniSLResolvedPartons::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef TopMiniSLResolvedPartons_cxx
