//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Fri Dec  5 18:56:19 2014 by ROOT version 5.34/19
// from TTree mini/4-vectors + variables required for scaling factors
// found on file: /gpfs_data/local/atlas/mromano/Resolved8TeV/minintuples-october-resolved/user.vscarfon.periodL.Egamma.grp14_v01_p1562.DATA_RESOLVED_2014_11_03_el_loose.root/user.vscarfon.4357076._000001.el_loose.root
//////////////////////////////////////////////////////////

#ifndef TopMiniSLResolved_loose_h
#define TopMiniSLResolved_loose_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

// Fixed size dimensions of array or collections stored in the TTree if any.

using namespace std;

class TopMiniSLResolved_loose {
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
   Float_t         lep_pt;
   Float_t         lep_eta;
   Float_t         lep_phi;
   Float_t         lep_E;
   Float_t         lep_trackd0pvunbiased;
   Float_t         lep_tracksigd0pvunbiased;
   Float_t         lep_charge;
   UShort_t        lep_trigMatch;
   Float_t         el_cl_eta;
   Float_t         eptcone30;
   Float_t         eetcone20;
   Float_t         mptcone30;
   Float_t         metcone20;
   Float_t         eminiIso10_4;
   Float_t         mminiIso10_4;
   Float_t         met_sumet;
   Float_t         met_et;
   Float_t         met_phi;
   Float_t         mwt;
   UInt_t          jet_n;
   UInt_t          alljet_n;
   Float_t         jet_pt[1];   //[alljet_n]
   Float_t         jet_eta[1];   //[alljet_n]
   Float_t         jet_phi[1];   //[alljet_n]
   Float_t         jet_E[1];   //[alljet_n]
   Float_t         jet_jvf[1];   //[alljet_n]
   Int_t           jet_trueflav[1];   //[alljet_n]
   Int_t           jet_truthMatched[1];   //[alljet_n]
   Float_t         jet_SV0[1];   //[alljet_n]
   Float_t         jet_COMBNN[1];   //[alljet_n]
   Float_t         jet_MV1[1];   //[alljet_n]
   Float_t         jet_MV1c[1];   //[alljet_n]
   Int_t           jet_isSemilep[1];   //[alljet_n]
   Bool_t          jet_BadMediumBCH[1];   //[alljet_n]
   Bool_t          jet_BadTightBCH[1];   //[alljet_n]
   Float_t         jet_emfrac[1];   //[alljet_n]
   Float_t         jet_BCH_CORR_CELL[1];   //[alljet_n]
   Bool_t          tight;

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
   TBranch        *b_lep_pt;   //!
   TBranch        *b_lep_eta;   //!
   TBranch        *b_lep_phi;   //!
   TBranch        *b_lep_E;   //!
   TBranch        *b_lep_trackd0pvunbiased;   //!
   TBranch        *b_lep_tracksigd0pvunbiased;   //!
   TBranch        *b_lep_charge;   //!
   TBranch        *b_lep_trigMatch;   //!
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
   TBranch        *b_jet_BadMediumBCH;   //!
   TBranch        *b_jet_BadTightBCH;   //!
   TBranch        *b_jet_emfrac;   //!
   TBranch        *b_jet_BCH_CORR_CELL;   //!
   TBranch        *b_tight;   //!

   TopMiniSLResolved_loose(TTree *tree=0);
   virtual ~TopMiniSLResolved_loose();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef TopMiniSLResolved_loose_cxx
TopMiniSLResolved_loose::TopMiniSLResolved_loose(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("/gpfs_data/local/atlas/mromano/Resolved8TeV/minintuples-october-resolved/user.vscarfon.periodL.Egamma.grp14_v01_p1562.DATA_RESOLVED_2014_11_03_el_loose.root/user.vscarfon.4357076._000001.el_loose.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("/gpfs_data/local/atlas/mromano/Resolved8TeV/minintuples-october-resolved/user.vscarfon.periodL.Egamma.grp14_v01_p1562.DATA_RESOLVED_2014_11_03_el_loose.root/user.vscarfon.4357076._000001.el_loose.root");
      }
      f->GetObject("mini",tree);

   }
   Init(tree);
}

TopMiniSLResolved_loose::~TopMiniSLResolved_loose()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t TopMiniSLResolved_loose::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t TopMiniSLResolved_loose::LoadTree(Long64_t entry)
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

void TopMiniSLResolved_loose::Init(TTree *tree)
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
   fChain->SetBranchAddress("lep_pt", &lep_pt, &b_lep_pt);
   fChain->SetBranchAddress("lep_eta", &lep_eta, &b_lep_eta);
   fChain->SetBranchAddress("lep_phi", &lep_phi, &b_lep_phi);
   fChain->SetBranchAddress("lep_E", &lep_E, &b_lep_E);
   fChain->SetBranchAddress("lep_trackd0pvunbiased", &lep_trackd0pvunbiased, &b_lep_trackd0pvunbiased);
   fChain->SetBranchAddress("lep_tracksigd0pvunbiased", &lep_tracksigd0pvunbiased, &b_lep_tracksigd0pvunbiased);
   fChain->SetBranchAddress("lep_charge", &lep_charge, &b_lep_charge);
   fChain->SetBranchAddress("lep_trigMatch", &lep_trigMatch, &b_lep_trigMatch);
   fChain->SetBranchAddress("el_cl_eta", &el_cl_eta, &b_el_cl_eta);
   fChain->SetBranchAddress("eptcone30", &eptcone30, &b_eptcone30);
   fChain->SetBranchAddress("eetcone20", &eetcone20, &b_eetcone20);
   fChain->SetBranchAddress("mptcone30", &mptcone30, &b_mptcone30);
   fChain->SetBranchAddress("metcone20", &metcone20, &b_metcone20);
   fChain->SetBranchAddress("eminiIso10_4", &eminiIso10_4, &b_eminiIso10_4);
   fChain->SetBranchAddress("mminiIso10_4", &mminiIso10_4, &b_mminiIso10_4);
   fChain->SetBranchAddress("met_sumet", &met_sumet, &b_met_sumet);
   fChain->SetBranchAddress("met_et", &met_et, &b_met_et);
   fChain->SetBranchAddress("met_phi", &met_phi, &b_met_phi);
   fChain->SetBranchAddress("mwt", &mwt, &b_mwt);
   fChain->SetBranchAddress("jet_n", &jet_n, &b_jet_n);
   fChain->SetBranchAddress("alljet_n", &alljet_n, &b_alljet_n);
   fChain->SetBranchAddress("jet_pt", &jet_pt, &b_jet_pt);
   fChain->SetBranchAddress("jet_eta", &jet_eta, &b_jet_eta);
   fChain->SetBranchAddress("jet_phi", &jet_phi, &b_jet_phi);
   fChain->SetBranchAddress("jet_E", &jet_E, &b_jet_E);
   fChain->SetBranchAddress("jet_jvf", &jet_jvf, &b_jet_jvf);
   fChain->SetBranchAddress("jet_trueflav", &jet_trueflav, &b_jet_trueflav);
   fChain->SetBranchAddress("jet_truthMatched", &jet_truthMatched, &b_jet_truthMatched);
   fChain->SetBranchAddress("jet_SV0", &jet_SV0, &b_jet_SV0);
   fChain->SetBranchAddress("jet_COMBNN", &jet_COMBNN, &b_jet_COMBNN);
   fChain->SetBranchAddress("jet_MV1", &jet_MV1, &b_jet_MV1);
   fChain->SetBranchAddress("jet_MV1c", &jet_MV1c, &b_jet_MV1c);
   fChain->SetBranchAddress("jet_isSemilep", &jet_isSemilep, &b_jet_isSemilep);
   fChain->SetBranchAddress("jet_BadMediumBCH", &jet_BadMediumBCH, &b_jet_BadMediumBCH);
   fChain->SetBranchAddress("jet_BadTightBCH", &jet_BadTightBCH, &b_jet_BadTightBCH);
   fChain->SetBranchAddress("jet_emfrac", &jet_emfrac, &b_jet_emfrac);
   fChain->SetBranchAddress("jet_BCH_CORR_CELL", &jet_BCH_CORR_CELL, &b_jet_BCH_CORR_CELL);
   fChain->SetBranchAddress("tight", &tight, &b_tight);
   Notify();
}

Bool_t TopMiniSLResolved_loose::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void TopMiniSLResolved_loose::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t TopMiniSLResolved_loose::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef TopMiniSLResolved_loose_cxx
