//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Thu Jun  4 19:08:09 2015 by ROOT version 5.34/19
// from TTree nominal/tree
// found on file: ../run/spano.root
//////////////////////////////////////////////////////////

#ifndef TopXAOD_h
#define TopXAOD_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include <vector>
#include <vector>
#include <vector>
#include <vector>

using namespace std;
// Fixed size dimensions of array or collections stored in the TTree if any.

class TopXAOD {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   Float_t         mcWeight;
   Float_t         pileupWeight;
   UInt_t          eventNumber;
   UInt_t          runNumber;
   UInt_t          mcChannelNumber;
   Float_t         mu;
   vector<float>   *el_pt;
   vector<float>   *el_eta;
   vector<float>   *el_phi;
   vector<float>   *el_e;
   vector<float>   *el_charge;
   vector<float>   *el_miniiso;
   vector<float>   *mu_pt;
   vector<float>   *mu_eta;
   vector<float>   *mu_phi;
   vector<float>   *mu_e;
   vector<float>   *mu_charge;
   vector<float>   *mu_miniiso;
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
   Float_t         met_met;
   Float_t         met_phi;
   Short_t         klfitter_selected;
   vector<short>   *klfitter_minuitDidNotConverge;
   vector<short>   *klfitter_fitAbortedDueToNaN;
   vector<short>   *klfitter_atLeastOneFitParameterAtItsLimit;
   vector<short>   *klfitter_invalidTransferFunctionAtConvergence;
   vector<unsigned int> *klfitter_bestPermutation;
   vector<float>   *klfitter_logLikelihood;
   vector<float>   *klfitter_eventProbability;
   vector<vector<double> > *klfitter_parameters;
   vector<vector<double> > *klfitter_parameterErrors;
   vector<float>   *klfitter_model_bhad_pt;
   vector<float>   *klfitter_model_bhad_eta;
   vector<float>   *klfitter_model_bhad_phi;
   vector<float>   *klfitter_model_bhad_E;
   vector<unsigned int> *klfitter_model_bhad_jetIndex;
   vector<float>   *klfitter_model_blep_pt;
   vector<float>   *klfitter_model_blep_eta;
   vector<float>   *klfitter_model_blep_phi;
   vector<float>   *klfitter_model_blep_E;
   vector<unsigned int> *klfitter_model_blep_jetIndex;
   vector<float>   *klfitter_model_lq1_pt;
   vector<float>   *klfitter_model_lq1_eta;
   vector<float>   *klfitter_model_lq1_phi;
   vector<float>   *klfitter_model_lq1_E;
   vector<unsigned int> *klfitter_model_lq1_jetIndex;
   vector<float>   *klfitter_model_lq2_pt;
   vector<float>   *klfitter_model_lq2_eta;
   vector<float>   *klfitter_model_lq2_phi;
   vector<float>   *klfitter_model_lq2_E;
   vector<unsigned int> *klfitter_model_lq2_jetIndex;
   vector<float>   *klfitter_model_lep_pt;
   vector<float>   *klfitter_model_lep_eta;
   vector<float>   *klfitter_model_lep_phi;
   vector<float>   *klfitter_model_lep_E;
   Int_t           ee;
   Int_t           mumu;
   Int_t           emu;
   Int_t           ejets;
   Int_t           mujets;

   // List of branches
   TBranch        *b_mcWeight;   //!
   TBranch        *b_pileupWeight;   //!
   TBranch        *b_eventNumber;   //!
   TBranch        *b_runNumber;   //!
   TBranch        *b_mcChannelNumber;   //!
   TBranch        *b_mu;   //!
   TBranch        *b_el_pt;   //!
   TBranch        *b_el_eta;   //!
   TBranch        *b_el_phi;   //!
   TBranch        *b_el_e;   //!
   TBranch        *b_el_charge;   //!
   TBranch        *b_el_miniiso;   //!
   TBranch        *b_mu_pt;   //!
   TBranch        *b_mu_eta;   //!
   TBranch        *b_mu_phi;   //!
   TBranch        *b_mu_e;   //!
   TBranch        *b_mu_charge;   //!
   TBranch        *b_mu_miniiso;   //!
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
   TBranch        *b_met_met;   //!
   TBranch        *b_met_phi;   //!
   TBranch        *b_klfitter_selected;   //!
   TBranch        *b_klfitter_minuitDidNotConverge;   //!
   TBranch        *b_klfitter_fitAbortedDueToNaN;   //!
   TBranch        *b_klfitter_atLeastOneFitParameterAtItsLimit;   //!
   TBranch        *b_klfitter_invalidTransferFunctionAtConvergence;   //!
   TBranch        *b_klfitter_bestPermutation;   //!
   TBranch        *b_klfitter_logLikelihood;   //!
   TBranch        *b_klfitter_eventProbability;   //!
   TBranch        *b_klfitter_parameters;   //!
   TBranch        *b_klfitter_parameterErrors;   //!
   TBranch        *b_klfitter_model_bhad_pt;   //!
   TBranch        *b_klfitter_model_bhad_eta;   //!
   TBranch        *b_klfitter_model_bhad_phi;   //!
   TBranch        *b_klfitter_model_bhad_E;   //!
   TBranch        *b_klfitter_model_bhad_jetIndex;   //!
   TBranch        *b_klfitter_model_blep_pt;   //!
   TBranch        *b_klfitter_model_blep_eta;   //!
   TBranch        *b_klfitter_model_blep_phi;   //!
   TBranch        *b_klfitter_model_blep_E;   //!
   TBranch        *b_klfitter_model_blep_jetIndex;   //!
   TBranch        *b_klfitter_model_lq1_pt;   //!
   TBranch        *b_klfitter_model_lq1_eta;   //!
   TBranch        *b_klfitter_model_lq1_phi;   //!
   TBranch        *b_klfitter_model_lq1_E;   //!
   TBranch        *b_klfitter_model_lq1_jetIndex;   //!
   TBranch        *b_klfitter_model_lq2_pt;   //!
   TBranch        *b_klfitter_model_lq2_eta;   //!
   TBranch        *b_klfitter_model_lq2_phi;   //!
   TBranch        *b_klfitter_model_lq2_E;   //!
   TBranch        *b_klfitter_model_lq2_jetIndex;   //!
   TBranch        *b_klfitter_model_lep_pt;   //!
   TBranch        *b_klfitter_model_lep_eta;   //!
   TBranch        *b_klfitter_model_lep_phi;   //!
   TBranch        *b_klfitter_model_lep_E;   //!
   TBranch        *b_ee;   //!
   TBranch        *b_mumu;   //!
   TBranch        *b_emu;   //!
   TBranch        *b_ejets;   //!
   TBranch        *b_mujets;   //!

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
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("../run/spano.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("../run/spano.root");
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
   el_pt = 0;
   el_eta = 0;
   el_phi = 0;
   el_e = 0;
   el_charge = 0;
   el_miniiso = 0;
   mu_pt = 0;
   mu_eta = 0;
   mu_phi = 0;
   mu_e = 0;
   mu_charge = 0;
   mu_miniiso = 0;
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
   klfitter_minuitDidNotConverge = 0;
   klfitter_fitAbortedDueToNaN = 0;
   klfitter_atLeastOneFitParameterAtItsLimit = 0;
   klfitter_invalidTransferFunctionAtConvergence = 0;
   klfitter_bestPermutation = 0;
   klfitter_logLikelihood = 0;
   klfitter_eventProbability = 0;
   klfitter_parameters = 0;
   klfitter_parameterErrors = 0;
   klfitter_model_bhad_pt = 0;
   klfitter_model_bhad_eta = 0;
   klfitter_model_bhad_phi = 0;
   klfitter_model_bhad_E = 0;
   klfitter_model_bhad_jetIndex = 0;
   klfitter_model_blep_pt = 0;
   klfitter_model_blep_eta = 0;
   klfitter_model_blep_phi = 0;
   klfitter_model_blep_E = 0;
   klfitter_model_blep_jetIndex = 0;
   klfitter_model_lq1_pt = 0;
   klfitter_model_lq1_eta = 0;
   klfitter_model_lq1_phi = 0;
   klfitter_model_lq1_E = 0;
   klfitter_model_lq1_jetIndex = 0;
   klfitter_model_lq2_pt = 0;
   klfitter_model_lq2_eta = 0;
   klfitter_model_lq2_phi = 0;
   klfitter_model_lq2_E = 0;
   klfitter_model_lq2_jetIndex = 0;
   klfitter_model_lep_pt = 0;
   klfitter_model_lep_eta = 0;
   klfitter_model_lep_phi = 0;
   klfitter_model_lep_E = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("mcWeight", &mcWeight, &b_mcWeight);
   fChain->SetBranchAddress("pileupWeight", &pileupWeight, &b_pileupWeight);
   fChain->SetBranchAddress("eventNumber", &eventNumber, &b_eventNumber);
   fChain->SetBranchAddress("runNumber", &runNumber, &b_runNumber);
   fChain->SetBranchAddress("mcChannelNumber", &mcChannelNumber, &b_mcChannelNumber);
   fChain->SetBranchAddress("mu", &mu, &b_mu);
   fChain->SetBranchAddress("el_pt", &el_pt, &b_el_pt);
   fChain->SetBranchAddress("el_eta", &el_eta, &b_el_eta);
   fChain->SetBranchAddress("el_phi", &el_phi, &b_el_phi);
   fChain->SetBranchAddress("el_e", &el_e, &b_el_e);
   fChain->SetBranchAddress("el_charge", &el_charge, &b_el_charge);
   fChain->SetBranchAddress("el_miniiso", &el_miniiso, &b_el_miniiso);
   fChain->SetBranchAddress("mu_pt", &mu_pt, &b_mu_pt);
   fChain->SetBranchAddress("mu_eta", &mu_eta, &b_mu_eta);
   fChain->SetBranchAddress("mu_phi", &mu_phi, &b_mu_phi);
   fChain->SetBranchAddress("mu_e", &mu_e, &b_mu_e);
   fChain->SetBranchAddress("mu_charge", &mu_charge, &b_mu_charge);
   fChain->SetBranchAddress("mu_miniiso", &mu_miniiso, &b_mu_miniiso);
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
   fChain->SetBranchAddress("met_met", &met_met, &b_met_met);
   fChain->SetBranchAddress("met_phi", &met_phi, &b_met_phi);
   fChain->SetBranchAddress("klfitter_selected", &klfitter_selected, &b_klfitter_selected);
   fChain->SetBranchAddress("klfitter_minuitDidNotConverge", &klfitter_minuitDidNotConverge, &b_klfitter_minuitDidNotConverge);
   fChain->SetBranchAddress("klfitter_fitAbortedDueToNaN", &klfitter_fitAbortedDueToNaN, &b_klfitter_fitAbortedDueToNaN);
   fChain->SetBranchAddress("klfitter_atLeastOneFitParameterAtItsLimit", &klfitter_atLeastOneFitParameterAtItsLimit, &b_klfitter_atLeastOneFitParameterAtItsLimit);
   fChain->SetBranchAddress("klfitter_invalidTransferFunctionAtConvergence", &klfitter_invalidTransferFunctionAtConvergence, &b_klfitter_invalidTransferFunctionAtConvergence);
   fChain->SetBranchAddress("klfitter_bestPermutation", &klfitter_bestPermutation, &b_klfitter_bestPermutation);
   fChain->SetBranchAddress("klfitter_logLikelihood", &klfitter_logLikelihood, &b_klfitter_logLikelihood);
   fChain->SetBranchAddress("klfitter_eventProbability", &klfitter_eventProbability, &b_klfitter_eventProbability);
   fChain->SetBranchAddress("klfitter_parameters", &klfitter_parameters, &b_klfitter_parameters);
   fChain->SetBranchAddress("klfitter_parameterErrors", &klfitter_parameterErrors, &b_klfitter_parameterErrors);
   fChain->SetBranchAddress("klfitter_model_bhad_pt", &klfitter_model_bhad_pt, &b_klfitter_model_bhad_pt);
   fChain->SetBranchAddress("klfitter_model_bhad_eta", &klfitter_model_bhad_eta, &b_klfitter_model_bhad_eta);
   fChain->SetBranchAddress("klfitter_model_bhad_phi", &klfitter_model_bhad_phi, &b_klfitter_model_bhad_phi);
   fChain->SetBranchAddress("klfitter_model_bhad_E", &klfitter_model_bhad_E, &b_klfitter_model_bhad_E);
   fChain->SetBranchAddress("klfitter_model_bhad_jetIndex", &klfitter_model_bhad_jetIndex, &b_klfitter_model_bhad_jetIndex);
   fChain->SetBranchAddress("klfitter_model_blep_pt", &klfitter_model_blep_pt, &b_klfitter_model_blep_pt);
   fChain->SetBranchAddress("klfitter_model_blep_eta", &klfitter_model_blep_eta, &b_klfitter_model_blep_eta);
   fChain->SetBranchAddress("klfitter_model_blep_phi", &klfitter_model_blep_phi, &b_klfitter_model_blep_phi);
   fChain->SetBranchAddress("klfitter_model_blep_E", &klfitter_model_blep_E, &b_klfitter_model_blep_E);
   fChain->SetBranchAddress("klfitter_model_blep_jetIndex", &klfitter_model_blep_jetIndex, &b_klfitter_model_blep_jetIndex);
   fChain->SetBranchAddress("klfitter_model_lq1_pt", &klfitter_model_lq1_pt, &b_klfitter_model_lq1_pt);
   fChain->SetBranchAddress("klfitter_model_lq1_eta", &klfitter_model_lq1_eta, &b_klfitter_model_lq1_eta);
   fChain->SetBranchAddress("klfitter_model_lq1_phi", &klfitter_model_lq1_phi, &b_klfitter_model_lq1_phi);
   fChain->SetBranchAddress("klfitter_model_lq1_E", &klfitter_model_lq1_E, &b_klfitter_model_lq1_E);
   fChain->SetBranchAddress("klfitter_model_lq1_jetIndex", &klfitter_model_lq1_jetIndex, &b_klfitter_model_lq1_jetIndex);
   fChain->SetBranchAddress("klfitter_model_lq2_pt", &klfitter_model_lq2_pt, &b_klfitter_model_lq2_pt);
   fChain->SetBranchAddress("klfitter_model_lq2_eta", &klfitter_model_lq2_eta, &b_klfitter_model_lq2_eta);
   fChain->SetBranchAddress("klfitter_model_lq2_phi", &klfitter_model_lq2_phi, &b_klfitter_model_lq2_phi);
   fChain->SetBranchAddress("klfitter_model_lq2_E", &klfitter_model_lq2_E, &b_klfitter_model_lq2_E);
   fChain->SetBranchAddress("klfitter_model_lq2_jetIndex", &klfitter_model_lq2_jetIndex, &b_klfitter_model_lq2_jetIndex);
   fChain->SetBranchAddress("klfitter_model_lep_pt", &klfitter_model_lep_pt, &b_klfitter_model_lep_pt);
   fChain->SetBranchAddress("klfitter_model_lep_eta", &klfitter_model_lep_eta, &b_klfitter_model_lep_eta);
   fChain->SetBranchAddress("klfitter_model_lep_phi", &klfitter_model_lep_phi, &b_klfitter_model_lep_phi);
   fChain->SetBranchAddress("klfitter_model_lep_E", &klfitter_model_lep_E, &b_klfitter_model_lep_E);
   fChain->SetBranchAddress("ee", &ee, &b_ee);
   fChain->SetBranchAddress("mumu", &mumu, &b_mumu);
   fChain->SetBranchAddress("emu", &emu, &b_emu);
   fChain->SetBranchAddress("ejets", &ejets, &b_ejets);
   fChain->SetBranchAddress("mujets", &mujets, &b_mujets);
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
