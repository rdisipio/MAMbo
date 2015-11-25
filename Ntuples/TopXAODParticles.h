//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed Nov 25 14:54:28 2015 by ROOT version 6.02/12
// from TTree particleLevel/tree
// found on file: ljets.output.root
//////////////////////////////////////////////////////////

#ifndef TopXAODParticles_h
#define TopXAODParticles_h


#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>


// Header file for the classes stored in the TTree if any.
#include "vector"


using namespace std;

class TopXAODParticles {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Float_t         weight_mc;
   ULong64_t       eventNumber;
   UInt_t          runNumber;
   UInt_t          mcChannelNumber;
   Float_t         mu;
   vector<float>   *el_pt;
   vector<float>   *el_eta;
   vector<float>   *el_phi;
   vector<float>   *el_e;
   vector<float>   *el_charge;
   vector<float>   *el_pt_bare;
   vector<float>   *el_eta_bare;
   vector<float>   *el_phi_bare;
   vector<float>   *el_e_bare;
   vector<float>   *mu_pt;
   vector<float>   *mu_eta;
   vector<float>   *mu_phi;
   vector<float>   *mu_e;
   vector<float>   *mu_charge;
   vector<float>   *mu_pt_bare;
   vector<float>   *mu_eta_bare;
   vector<float>   *mu_phi_bare;
   vector<float>   *mu_e_bare;
   vector<float>   *jet_pt;
   vector<float>   *jet_eta;
   vector<float>   *jet_phi;
   vector<float>   *jet_e;
   vector<int>     *jet_nGhosts_bHadron;
   vector<float>   *ljet_pt;
   vector<float>   *ljet_eta;
   vector<float>   *ljet_phi;
   vector<float>   *ljet_e;
   vector<int>     *ljet_nGhosts_bHadron;
   Float_t         met_met;
   Float_t         met_phi;
   Int_t           passed_boosted_mujets_1fj1b;
   Int_t           passed_resolved_ejets_2j0b;
   Int_t           passed_resolved_mujets_4j0b;
   Int_t           passed_boosted_mujets_1fj0b;
   Int_t           passed_resolved_ejets_4j0b;
   Int_t           passed_resolved_ejets_4j1b;
   Int_t           passed_resolved_mujets_4j1b;
   Int_t           passed_resolved_ejets_4j2b;
   Int_t           passed_boosted_ejets_1fj1b;
   Int_t           passed_resolved_mujets_4j2b;
   Int_t           passed_resolved_mujets_2j0b;
   Int_t           passed_boosted_ejets_1fj0b;
   vector<float>   *ljet_m;
   vector<float>   *ljet_sd12;
   vector<float>   *ljet_tau32;
   vector<float>   *ljet_tau21;
   vector<int>     *ljet_topTag50;
   vector<int>     *ljet_topTag80;

   // List of branches
   TBranch        *b_weight_mc;   //!
   TBranch        *b_eventNumber;   //!
   TBranch        *b_runNumber;   //!
   TBranch        *b_mcChannelNumber;   //!
   TBranch        *b_mu;   //!
   TBranch        *b_el_pt;   //!
   TBranch        *b_el_eta;   //!
   TBranch        *b_el_phi;   //!
   TBranch        *b_el_e;   //!
   TBranch        *b_el_charge;   //!
   TBranch        *b_el_pt_bare;   //!
   TBranch        *b_el_eta_bare;   //!
   TBranch        *b_el_phi_bare;   //!
   TBranch        *b_el_e_bare;   //!
   TBranch        *b_mu_pt;   //!
   TBranch        *b_mu_eta;   //!
   TBranch        *b_mu_phi;   //!
   TBranch        *b_mu_e;   //!
   TBranch        *b_mu_charge;   //!
   TBranch        *b_mu_pt_bare;   //!
   TBranch        *b_mu_eta_bare;   //!
   TBranch        *b_mu_phi_bare;   //!
   TBranch        *b_mu_e_bare;   //!
   TBranch        *b_jet_pt;   //!
   TBranch        *b_jet_eta;   //!
   TBranch        *b_jet_phi;   //!
   TBranch        *b_jet_e;   //!
   TBranch        *b_jet_nGhosts_bHadron;   //!
   TBranch        *b_ljet_pt;   //!
   TBranch        *b_ljet_eta;   //!
   TBranch        *b_ljet_phi;   //!
   TBranch        *b_ljet_e;   //!
   TBranch        *b_ljet_nGhosts_bHadron;   //!
   TBranch        *b_met_met;   //!
   TBranch        *b_met_phi;   //!
   TBranch        *b_passed_boosted_mujets_1fj1b;   //!
   TBranch        *b_passed_resolved_ejets_2j0b;   //!
   TBranch        *b_passed_resolved_mujets_4j0b;   //!
   TBranch        *b_passed_boosted_mujets_1fj0b;   //!
   TBranch        *b_passed_resolved_ejets_4j0b;   //!
   TBranch        *b_passed_resolved_ejets_4j1b;   //!
   TBranch        *b_passed_resolved_mujets_4j1b;   //!
   TBranch        *b_passed_resolved_ejets_4j2b;   //!
   TBranch        *b_passed_boosted_ejets_1fj1b;   //!
   TBranch        *b_passed_resolved_mujets_4j2b;   //!
   TBranch        *b_passed_resolved_mujets_2j0b;   //!
   TBranch        *b_passed_boosted_ejets_1fj0b;   //!
   TBranch        *b_ljet_m;   //!
   TBranch        *b_ljet_sd12;   //!
   TBranch        *b_ljet_tau32;   //!
   TBranch        *b_ljet_tau21;   //!
   TBranch        *b_ljet_topTag50;   //!
   TBranch        *b_ljet_topTag80;   //!

   TopXAODParticles(TTree *tree=0);
   virtual ~TopXAODParticles();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef TopXAODParticles_cxx
TopXAODParticles::TopXAODParticles(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("ljets.output.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("ljets.output.root");
      }
      f->GetObject("particleLevel",tree);

   }
   Init(tree);
}

TopXAODParticles::~TopXAODParticles()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t TopXAODParticles::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t TopXAODParticles::LoadTree(Long64_t entry)
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

void TopXAODParticles::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   el_pt = 0;
   el_eta = 0;
   el_phi = 0;
   el_e = 0;
   el_charge = 0;
   el_pt_bare = 0;
   el_eta_bare = 0;
   el_phi_bare = 0;
   el_e_bare = 0;
   mu_pt = 0;
   mu_eta = 0;
   mu_phi = 0;
   mu_e = 0;
   mu_charge = 0;
   mu_pt_bare = 0;
   mu_eta_bare = 0;
   mu_phi_bare = 0;
   mu_e_bare = 0;
   jet_pt = 0;
   jet_eta = 0;
   jet_phi = 0;
   jet_e = 0;
   jet_nGhosts_bHadron = 0;
   ljet_pt = 0;
   ljet_eta = 0;
   ljet_phi = 0;
   ljet_e = 0;
   ljet_nGhosts_bHadron = 0;
   ljet_m = 0;
   ljet_sd12 = 0;
   ljet_tau32 = 0;
   ljet_tau21 = 0;
   ljet_topTag50 = 0;
   ljet_topTag80 = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("weight_mc", &weight_mc, &b_weight_mc);
   fChain->SetBranchAddress("eventNumber", &eventNumber, &b_eventNumber);
   fChain->SetBranchAddress("runNumber", &runNumber, &b_runNumber);
   fChain->SetBranchAddress("mcChannelNumber", &mcChannelNumber, &b_mcChannelNumber);
   fChain->SetBranchAddress("mu", &mu, &b_mu);
   fChain->SetBranchAddress("el_pt", &el_pt, &b_el_pt);
   fChain->SetBranchAddress("el_eta", &el_eta, &b_el_eta);
   fChain->SetBranchAddress("el_phi", &el_phi, &b_el_phi);
   fChain->SetBranchAddress("el_e", &el_e, &b_el_e);
   fChain->SetBranchAddress("el_charge", &el_charge, &b_el_charge);
   fChain->SetBranchAddress("el_pt_bare", &el_pt_bare, &b_el_pt_bare);
   fChain->SetBranchAddress("el_eta_bare", &el_eta_bare, &b_el_eta_bare);
   fChain->SetBranchAddress("el_phi_bare", &el_phi_bare, &b_el_phi_bare);
   fChain->SetBranchAddress("el_e_bare", &el_e_bare, &b_el_e_bare);
   fChain->SetBranchAddress("mu_pt", &mu_pt, &b_mu_pt);
   fChain->SetBranchAddress("mu_eta", &mu_eta, &b_mu_eta);
   fChain->SetBranchAddress("mu_phi", &mu_phi, &b_mu_phi);
   fChain->SetBranchAddress("mu_e", &mu_e, &b_mu_e);
   fChain->SetBranchAddress("mu_charge", &mu_charge, &b_mu_charge);
   fChain->SetBranchAddress("mu_pt_bare", &mu_pt_bare, &b_mu_pt_bare);
   fChain->SetBranchAddress("mu_eta_bare", &mu_eta_bare, &b_mu_eta_bare);
   fChain->SetBranchAddress("mu_phi_bare", &mu_phi_bare, &b_mu_phi_bare);
   fChain->SetBranchAddress("mu_e_bare", &mu_e_bare, &b_mu_e_bare);
   fChain->SetBranchAddress("jet_pt", &jet_pt, &b_jet_pt);
   fChain->SetBranchAddress("jet_eta", &jet_eta, &b_jet_eta);
   fChain->SetBranchAddress("jet_phi", &jet_phi, &b_jet_phi);
   fChain->SetBranchAddress("jet_e", &jet_e, &b_jet_e);
   fChain->SetBranchAddress("jet_nGhosts_bHadron", &jet_nGhosts_bHadron, &b_jet_nGhosts_bHadron);
   fChain->SetBranchAddress("ljet_pt", &ljet_pt, &b_ljet_pt);
   fChain->SetBranchAddress("ljet_eta", &ljet_eta, &b_ljet_eta);
   fChain->SetBranchAddress("ljet_phi", &ljet_phi, &b_ljet_phi);
   fChain->SetBranchAddress("ljet_e", &ljet_e, &b_ljet_e);
   fChain->SetBranchAddress("ljet_nGhosts_bHadron", &ljet_nGhosts_bHadron, &b_ljet_nGhosts_bHadron);
   fChain->SetBranchAddress("met_met", &met_met, &b_met_met);
   fChain->SetBranchAddress("met_phi", &met_phi, &b_met_phi);
   fChain->SetBranchAddress("passed_boosted_mujets_1fj1b", &passed_boosted_mujets_1fj1b, &b_passed_boosted_mujets_1fj1b);
   fChain->SetBranchAddress("passed_resolved_ejets_2j0b", &passed_resolved_ejets_2j0b, &b_passed_resolved_ejets_2j0b);
   fChain->SetBranchAddress("passed_resolved_mujets_4j0b", &passed_resolved_mujets_4j0b, &b_passed_resolved_mujets_4j0b);
   fChain->SetBranchAddress("passed_boosted_mujets_1fj0b", &passed_boosted_mujets_1fj0b, &b_passed_boosted_mujets_1fj0b);
   fChain->SetBranchAddress("passed_resolved_ejets_4j0b", &passed_resolved_ejets_4j0b, &b_passed_resolved_ejets_4j0b);
   fChain->SetBranchAddress("passed_resolved_ejets_4j1b", &passed_resolved_ejets_4j1b, &b_passed_resolved_ejets_4j1b);
   fChain->SetBranchAddress("passed_resolved_mujets_4j1b", &passed_resolved_mujets_4j1b, &b_passed_resolved_mujets_4j1b);
   fChain->SetBranchAddress("passed_resolved_ejets_4j2b", &passed_resolved_ejets_4j2b, &b_passed_resolved_ejets_4j2b);
   fChain->SetBranchAddress("passed_boosted_ejets_1fj1b", &passed_boosted_ejets_1fj1b, &b_passed_boosted_ejets_1fj1b);
   fChain->SetBranchAddress("passed_resolved_mujets_4j2b", &passed_resolved_mujets_4j2b, &b_passed_resolved_mujets_4j2b);
   fChain->SetBranchAddress("passed_resolved_mujets_2j0b", &passed_resolved_mujets_2j0b, &b_passed_resolved_mujets_2j0b);
   fChain->SetBranchAddress("passed_boosted_ejets_1fj0b", &passed_boosted_ejets_1fj0b, &b_passed_boosted_ejets_1fj0b);
   fChain->SetBranchAddress("ljet_m", &ljet_m, &b_ljet_m);
   fChain->SetBranchAddress("ljet_sd12", &ljet_sd12, &b_ljet_sd12);
   fChain->SetBranchAddress("ljet_tau32", &ljet_tau32, &b_ljet_tau32);
   fChain->SetBranchAddress("ljet_tau21", &ljet_tau21, &b_ljet_tau21);
   fChain->SetBranchAddress("ljet_topTag50", &ljet_topTag50, &b_ljet_topTag50);
   fChain->SetBranchAddress("ljet_topTag80", &ljet_topTag80, &b_ljet_topTag80);
   Notify();
}

Bool_t TopXAODParticles::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void TopXAODParticles::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t TopXAODParticles::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef TopXAODParticles_cxx
