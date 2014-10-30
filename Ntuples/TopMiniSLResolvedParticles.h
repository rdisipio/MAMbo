//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed Oct 29 11:18:04 2014 by ROOT version 5.34/04
// from TTree particles/Particle objects and associated decision
// found on file: /gpfs_data/local/atlas/disipio/minituples/TTbarResolved8TeV/examples_mc/mc.root
//////////////////////////////////////////////////////////

#ifndef TopMiniSLResolvedParticles_h
#define TopMiniSLResolvedParticles_h
#define TopMiniSLResolvedParticles_cxx

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

// Fixed size dimensions of array or collections stored in the TTree if any.
using namespace std;

class TopMiniSLResolvedParticles {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   Int_t           runNumber;
   Int_t           channelNumber;
   Int_t           eventNumber;
   Int_t           part_el_n;
   Float_t         part_el_pt[2];   //[part_el_n]
   Float_t         part_el_eta[2];   //[part_el_n]
   Float_t         part_el_phi[2];   //[part_el_n]
   Float_t         part_el_E[2];   //[part_el_n]
   Bool_t          part_el_matchWboson[2];   //[part_el_n]
   Float_t         part_el_isolation[2];   //[part_el_n]
   Float_t         part_el_charge[2];   //[part_el_n]
   Int_t           part_mu_n;
   Float_t         part_mu_pt[2];   //[part_mu_n]
   Float_t         part_mu_eta[2];   //[part_mu_n]
   Float_t         part_mu_phi[2];   //[part_mu_n]
   Float_t         part_mu_E[2];   //[part_mu_n]
   Bool_t          part_mu_matchWboson[2];   //[part_mu_n]
   Float_t         part_mu_isolation[2];   //[part_mu_n]
   Float_t         part_mu_charge[2];   //[part_mu_n]
   Float_t         part_met_et;
   Float_t         part_met_phi;
   Float_t         part_mwt_el[2];   //[part_el_n]
   Float_t         part_mwt_mu[2];   //[part_mu_n]
   Int_t           part_jet_n;
   Float_t         part_jet_pt[11];   //[part_jet_n]
   Float_t         part_jet_eta[11];   //[part_jet_n]
   Float_t         part_jet_phi[11];   //[part_jet_n]
   Float_t         part_jet_E[11];   //[part_jet_n]
   Int_t           part_jet_ntags;
   Bool_t          part_jet_tagged[11];   //[part_jet_n]
   Bool_t          part_jet_from_top[11];   //[part_jet_n]
   Int_t           part_jet_flavour_pdgId[11];   //[part_jet_n]
   Float_t         part_jet_muE[11];   //[part_jet_n]
   Float_t         part_jet_nuE[11];   //[part_jet_n]
   Int_t           part_nu_n;
   Float_t         part_nu_pt[6];   //[part_nu_n]
   Float_t         part_nu_eta[6];   //[part_nu_n]
   Float_t         part_nu_phi[6];   //[part_nu_n]
   Bool_t          part_nu_matchWboson[6];   //[part_nu_n]
   Bool_t          pass_part_ejet;
   Bool_t          pass_part_mujet;

   // List of branches
   TBranch        *b_runNumber;   //!
   TBranch        *b_channelNumber;   //!
   TBranch        *b_eventNumber;   //!
   TBranch        *b_part_el_n;   //!
   TBranch        *b_part_el_pt;   //!
   TBranch        *b_part_el_eta;   //!
   TBranch        *b_part_el_phi;   //!
   TBranch        *b_part_el_E;   //!
   TBranch        *b_part_el_matchWboson;   //!
   TBranch        *b_part_el_isolation;   //!
   TBranch        *b_part_el_charge;   //!
   TBranch        *b_part_mu_n;   //!
   TBranch        *b_part_mu_pt;   //!
   TBranch        *b_part_mu_eta;   //!
   TBranch        *b_part_mu_phi;   //!
   TBranch        *b_part_mu_E;   //!
   TBranch        *b_part_mu_matchWboson;   //!
   TBranch        *b_part_mu_isolation;   //!
   TBranch        *b_part_mu_charge;   //!
   TBranch        *b_part_met_et;   //!
   TBranch        *b_part_met_phi;   //!
   TBranch        *b_part_mwt_el;   //!
   TBranch        *b_part_mwt_mu;   //!
   TBranch        *b_part_jet_n;   //!
   TBranch        *b_part_jet_pt;   //!
   TBranch        *b_part_jet_eta;   //!
   TBranch        *b_part_jet_phi;   //!
   TBranch        *b_part_jet_E;   //!
   TBranch        *b_part_jet_ntags;   //!
   TBranch        *b_part_jet_tagged;   //!
   TBranch        *b_part_jet_from_top;   //!
   TBranch        *b_part_jet_flavour_pdgId;   //!
   TBranch        *b_part_jet_muE;   //!
   TBranch        *b_part_jet_nuE;   //!
   TBranch        *b_part_nu_n;   //!
   TBranch        *b_part_nu_pt;   //!
   TBranch        *b_part_nu_eta;   //!
   TBranch        *b_part_nu_phi;   //!
   TBranch        *b_part_nu_matchWboson;   //!
   TBranch        *b_pass_part_ejet;   //!
   TBranch        *b_pass_part_mujet;   //!

   TopMiniSLResolvedParticles(TTree *tree=0);
   virtual ~TopMiniSLResolvedParticles();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
  // virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef TopMiniSLResolvedParticles_cxx
TopMiniSLResolvedParticles::TopMiniSLResolvedParticles(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("/gpfs_data/local/atlas/disipio/minituples/TTbarResolved8TeV/examples_mc/mc.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("/gpfs_data/local/atlas/disipio/minituples/TTbarResolved8TeV/examples_mc/mc.root");
      }
      f->GetObject("particles",tree);

   }
   Init(tree);
}

TopMiniSLResolvedParticles::~TopMiniSLResolvedParticles()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t TopMiniSLResolvedParticles::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t TopMiniSLResolvedParticles::LoadTree(Long64_t entry)
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

void TopMiniSLResolvedParticles::Init(TTree *tree)
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
   fChain->SetBranchAddress("channelNumber", &channelNumber, &b_channelNumber);
   fChain->SetBranchAddress("eventNumber", &eventNumber, &b_eventNumber);
   fChain->SetBranchAddress("part_el_n", &part_el_n, &b_part_el_n);
   fChain->SetBranchAddress("part_el_pt", part_el_pt, &b_part_el_pt);
   fChain->SetBranchAddress("part_el_eta", part_el_eta, &b_part_el_eta);
   fChain->SetBranchAddress("part_el_phi", part_el_phi, &b_part_el_phi);
   fChain->SetBranchAddress("part_el_E", part_el_E, &b_part_el_E);
   fChain->SetBranchAddress("part_el_matchWboson", part_el_matchWboson, &b_part_el_matchWboson);
   fChain->SetBranchAddress("part_el_isolation", part_el_isolation, &b_part_el_isolation);
   fChain->SetBranchAddress("part_el_charge", part_el_charge, &b_part_el_charge);
   fChain->SetBranchAddress("part_mu_n", &part_mu_n, &b_part_mu_n);
   fChain->SetBranchAddress("part_mu_pt", part_mu_pt, &b_part_mu_pt);
   fChain->SetBranchAddress("part_mu_eta", part_mu_eta, &b_part_mu_eta);
   fChain->SetBranchAddress("part_mu_phi", part_mu_phi, &b_part_mu_phi);
   fChain->SetBranchAddress("part_mu_E", part_mu_E, &b_part_mu_E);
   fChain->SetBranchAddress("part_mu_matchWboson", part_mu_matchWboson, &b_part_mu_matchWboson);
   fChain->SetBranchAddress("part_mu_isolation", part_mu_isolation, &b_part_mu_isolation);
   fChain->SetBranchAddress("part_mu_charge", part_mu_charge, &b_part_mu_charge);
   fChain->SetBranchAddress("part_met_et", &part_met_et, &b_part_met_et);
   fChain->SetBranchAddress("part_met_phi", &part_met_phi, &b_part_met_phi);
   fChain->SetBranchAddress("part_mwt_el", part_mwt_el, &b_part_mwt_el);
   fChain->SetBranchAddress("part_mwt_mu", part_mwt_mu, &b_part_mwt_mu);
   fChain->SetBranchAddress("part_jet_n", &part_jet_n, &b_part_jet_n);
   fChain->SetBranchAddress("part_jet_pt", part_jet_pt, &b_part_jet_pt);
   fChain->SetBranchAddress("part_jet_eta", part_jet_eta, &b_part_jet_eta);
   fChain->SetBranchAddress("part_jet_phi", part_jet_phi, &b_part_jet_phi);
   fChain->SetBranchAddress("part_jet_E", part_jet_E, &b_part_jet_E);
   fChain->SetBranchAddress("part_jet_ntags", &part_jet_ntags, &b_part_jet_ntags);
   fChain->SetBranchAddress("part_jet_tagged", part_jet_tagged, &b_part_jet_tagged);
   fChain->SetBranchAddress("part_jet_from_top", part_jet_from_top, &b_part_jet_from_top);
   fChain->SetBranchAddress("part_jet_flavour_pdgId", part_jet_flavour_pdgId, &b_part_jet_flavour_pdgId);
   fChain->SetBranchAddress("part_jet_muE", part_jet_muE, &b_part_jet_muE);
   fChain->SetBranchAddress("part_jet_nuE", part_jet_nuE, &b_part_jet_nuE);
   fChain->SetBranchAddress("part_nu_n", &part_nu_n, &b_part_nu_n);
   fChain->SetBranchAddress("part_nu_pt", part_nu_pt, &b_part_nu_pt);
   fChain->SetBranchAddress("part_nu_eta", part_nu_eta, &b_part_nu_eta);
   fChain->SetBranchAddress("part_nu_phi", part_nu_phi, &b_part_nu_phi);
   fChain->SetBranchAddress("part_nu_matchWboson", part_nu_matchWboson, &b_part_nu_matchWboson);
   fChain->SetBranchAddress("pass_part_ejet", &pass_part_ejet, &b_pass_part_ejet);
   fChain->SetBranchAddress("pass_part_mujet", &pass_part_mujet, &b_pass_part_mujet);
   Notify();
}

Bool_t TopMiniSLResolvedParticles::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void TopMiniSLResolvedParticles::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t TopMiniSLResolvedParticles::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef TopMiniSLResolvedParticles_cxx
