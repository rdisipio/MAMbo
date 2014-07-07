//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Tue Jul  1 14:53:27 2014 by ROOT version 5.34/04
// from TTree mini/4-vectors + variables required for scaling factors
// found on file: user.mromano.117050.e1728_s1581_s1586_r3658_r3549_p1400.MC_no_syst/user.mromano.007979._00800.merge.el.root
//////////////////////////////////////////////////////////

#ifndef TopMini_h
#define TopMini_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

using namespace std;

// Header file for the classes stored in the TTree if any.
#include <vector>
#include <vector>

// Fixed size dimensions of array or collections stored in the TTree if any.

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
   Float_t         scaleFactor_PILEUP;
   Float_t         scaleFactor_ELE;
   Float_t         scaleFactor_MUON;
   Float_t         scaleFactor_BTAG;
   Float_t         scaleFactor_TRIGGER;
   Float_t         scaleFactor_WJETSNORM;
   Float_t         scaleFactor_WJETSSHAPE;
   Float_t         scaleFactor_JVFSF;
   Float_t         scaleFactor_ZVERTEX;
   Int_t           mc_n;
   vector<float>   *mc_m;
   vector<float>   *mc_pt;
   vector<float>   *mc_eta;
   vector<float>   *mc_phi;
   vector<int>     *mc_status;
   vector<int>     *mc_barcode;
   vector<int>     *mc_pdgId;
   vector<float>   *mc_charge;
   vector<vector<int> > *mc_parent_index;
   vector<vector<int> > *mc_child_index;
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
   Float_t         jet_pt[15];   //[alljet_n]
   Float_t         jet_eta[15];   //[alljet_n]
   Float_t         jet_phi[15];   //[alljet_n]
   Float_t         jet_E[15];   //[alljet_n]
   Float_t         jet_jvf[15];   //[alljet_n]
   Int_t           jet_trueflav[15];   //[alljet_n]
   Int_t           jet_truthMatched[15];   //[alljet_n]
   Float_t         jet_SV0[15];   //[alljet_n]
   Float_t         jet_COMBNN[15];   //[alljet_n]
   Float_t         jet_MV1[15];   //[alljet_n]
   Float_t         jet_MV1c[15];   //[alljet_n]
   Int_t           jet_isSemilep[15];   //[alljet_n]
   Bool_t          jet_BadMediumBCH[15];   //[alljet_n]
   Bool_t          jet_BadTightBCH[15];   //[alljet_n]
   Float_t         jet_emfrac[15];   //[alljet_n]
   Float_t         jet_BCH_CORR_CELL[15];   //[alljet_n]

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
   TBranch        *b_m_scaleFactor_PILEUP;   //!
   TBranch        *b_m_scaleFactor_ELE;   //!
   TBranch        *b_m_scaleFactor_MUON;   //!
   TBranch        *b_m_scaleFactor_BTAG;   //!
   TBranch        *b_m_scaleFactor_TRIGGER;   //!
   TBranch        *b_m_scaleFactor_WJETSNORM;   //!
   TBranch        *b_m_scaleFactor_WJETSSHAPE;   //!
   TBranch        *b_m_scaleFactor_JVFSF;   //!
   TBranch        *b_m_scaleFactor_ZVERTEX;   //!
   TBranch        *b_mc_n;   //!
   TBranch        *b_mc_m;   //!
   TBranch        *b_mc_pt;   //!
   TBranch        *b_mc_eta;   //!
   TBranch        *b_mc_phi;   //!
   TBranch        *b_mc_status;   //!
   TBranch        *b_mc_barcode;   //!
   TBranch        *b_mc_pdgId;   //!
   TBranch        *b_mc_charge;   //!
   TBranch        *b_mc_parent_index;   //!
   TBranch        *b_mc_child_index;   //!
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
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("user.mromano.117050.e1728_s1581_s1586_r3658_r3549_p1400.MC_no_syst/user.mromano.007979._00800.merge.el.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("user.mromano.117050.e1728_s1581_s1586_r3658_r3549_p1400.MC_no_syst/user.mromano.007979._00800.merge.el.root");
      }
      f->GetObject("mini",tree);

   }
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
   mc_m = 0;
   mc_pt = 0;
   mc_eta = 0;
   mc_phi = 0;
   mc_status = 0;
   mc_barcode = 0;
   mc_pdgId = 0;
   mc_charge = 0;
   mc_parent_index = 0;
   mc_child_index = 0;
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
   fChain->SetBranchAddress("scaleFactor_PILEUP", &scaleFactor_PILEUP, &b_m_scaleFactor_PILEUP);
   fChain->SetBranchAddress("scaleFactor_ELE", &scaleFactor_ELE, &b_m_scaleFactor_ELE);
   fChain->SetBranchAddress("scaleFactor_MUON", &scaleFactor_MUON, &b_m_scaleFactor_MUON);
   fChain->SetBranchAddress("scaleFactor_BTAG", &scaleFactor_BTAG, &b_m_scaleFactor_BTAG);
   fChain->SetBranchAddress("scaleFactor_TRIGGER", &scaleFactor_TRIGGER, &b_m_scaleFactor_TRIGGER);
   fChain->SetBranchAddress("scaleFactor_WJETSNORM", &scaleFactor_WJETSNORM, &b_m_scaleFactor_WJETSNORM);
   fChain->SetBranchAddress("scaleFactor_WJETSSHAPE", &scaleFactor_WJETSSHAPE, &b_m_scaleFactor_WJETSSHAPE);
   fChain->SetBranchAddress("scaleFactor_JVFSF", &scaleFactor_JVFSF, &b_m_scaleFactor_JVFSF);
   fChain->SetBranchAddress("scaleFactor_ZVERTEX", &scaleFactor_ZVERTEX, &b_m_scaleFactor_ZVERTEX);
   fChain->SetBranchAddress("mc_n", &mc_n, &b_mc_n);
   fChain->SetBranchAddress("mc_m", &mc_m, &b_mc_m);
   fChain->SetBranchAddress("mc_pt", &mc_pt, &b_mc_pt);
   fChain->SetBranchAddress("mc_eta", &mc_eta, &b_mc_eta);
   fChain->SetBranchAddress("mc_phi", &mc_phi, &b_mc_phi);
   fChain->SetBranchAddress("mc_status", &mc_status, &b_mc_status);
   fChain->SetBranchAddress("mc_barcode", &mc_barcode, &b_mc_barcode);
   fChain->SetBranchAddress("mc_pdgId", &mc_pdgId, &b_mc_pdgId);
   fChain->SetBranchAddress("mc_charge", &mc_charge, &b_mc_charge);
   fChain->SetBranchAddress("mc_parent_index", &mc_parent_index, &b_mc_parent_index);
   fChain->SetBranchAddress("mc_child_index", &mc_child_index, &b_mc_child_index);
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
   fChain->SetBranchAddress("jet_BadMediumBCH", jet_BadMediumBCH, &b_jet_BadMediumBCH);
   fChain->SetBranchAddress("jet_BadTightBCH", jet_BadTightBCH, &b_jet_BadTightBCH);
   fChain->SetBranchAddress("jet_emfrac", jet_emfrac, &b_jet_emfrac);
   fChain->SetBranchAddress("jet_BCH_CORR_CELL", jet_BCH_CORR_CELL, &b_jet_BCH_CORR_CELL);
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
