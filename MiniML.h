//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Mon Jan 21 11:57:33 2013 by ROOT version 5.32/04
// from TTree mini/4-vectors + variables required for scaling factors
// found on file: /home/ATLAS/disipio/development/BoostedTops/runD3PD/MiniML/ML_2D.root
//////////////////////////////////////////////////////////

#ifndef MiniML_h
#define MiniML_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

// Fixed size dimensions of array or collections stored in the TTree if any.

class MiniML {
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
   Float_t         mcWeight;
   Float_t         eventWeight_PRETAG;
   Float_t         eventWeight_BTAG;
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
   Float_t         scaleFactor_DILEP;
   Float_t         scaleFactor_BTAG;
   Float_t         scaleFactor_WJETSNORM;
   Float_t         scaleFactor_WJETSSHAPE;
   Float_t         scaleFactor_JVFSF;
   Float_t         scaleFactor_ZVERTEX;
   Float_t         scaleFactor_ALLPRETAG;
   Float_t         scaleFactor_ALLBTAG;
   Int_t           truE;
   Int_t           truM;
   Bool_t          trigE;
   Bool_t          trigM;
   Bool_t          passGRL;
   Bool_t          cosmicEvent;
   Bool_t          isOS;
   Bool_t          hasGoodVertex;
   Float_t         ht;
   Float_t         mass;
   Float_t         massInv_LL;
   Float_t         massInv_BQQ;
   Float_t         massTrans_BLMet;
   Float_t         massTrans_LMet;
   UInt_t          flag_DL;
   UInt_t          flag_TTZ;
   UInt_t          channel_DL;
   UInt_t          channel_TTZ;
   Float_t         scaledWeight;
   UInt_t          lep_n;
   Bool_t          lep_truthMatched[2];   //[lep_n]
   Bool_t          lep_trigMatched[2];   //[lep_n]
   Float_t         lep_pt[2];   //[lep_n]
   Float_t         lep_eta[2];   //[lep_n]
   Float_t         lep_phi[2];   //[lep_n]
   Float_t         lep_E[2];   //[lep_n]
   Float_t         lep_z0[2];   //[lep_n]
   Float_t         lep_charge[2];   //[lep_n]
   Bool_t          lep_isTight[2];   //[lep_n]
   UInt_t          lep_type[2];   //[lep_n]
   UInt_t          lep_flag[2];   //[lep_n]
   Float_t         el_cl_eta[2];   //[lep_n]
   Float_t         lep_ptcone30[2];   //[lep_n]
   Float_t         lep_etcone20[2];   //[lep_n]
   Float_t         lep_miniIso10_4[2];   //[lep_n]
   Float_t         massTrans_LMet_Vec[2];   //[lep_n]
   UInt_t          lepPair_n;
   Bool_t          isSameFlavor_LL_Vec[1];   //[lepPair_n]
   Bool_t          isOppSign_LL_Vec[1];   //[lepPair_n]
   Float_t         massInv_LL_Vec[1];   //[lepPair_n]
   Float_t         met_sumet;
   Float_t         met_et;
   Float_t         met_phi;
   UInt_t          jet_n;
   UInt_t          alljet_n;
   Float_t         jet_pt[11];   //[alljet_n]
   Float_t         jet_eta[11];   //[alljet_n]
   Float_t         jet_phi[11];   //[alljet_n]
   Float_t         jet_E[11];   //[alljet_n]
   Float_t         jet_m[11];   //[alljet_n]
   Float_t         jet_jvf[11];   //[alljet_n]
   Int_t           jet_trueflav[11];   //[alljet_n]
   Int_t           jet_truthMatched[11];   //[alljet_n]
   Float_t         jet_SV0[11];   //[alljet_n]
   Float_t         jet_MV1[11];   //[alljet_n]
   UInt_t          jet_flag[11];   //[alljet_n]

   // List of branches
   TBranch        *b_runNumber;   //!
   TBranch        *b_eventNumber;   //!
   TBranch        *b_channelNumber;   //!
   TBranch        *b_rndRunNumber;   //!
   TBranch        *b_dataPeriod;   //!
   TBranch        *b_mu;   //!
   TBranch        *b_mcWeight;   //!
   TBranch        *b_eventWeight_PRETAG;   //!
   TBranch        *b_eventWeight_BTAG;   //!
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
   TBranch        *b_m_scaleFactor_DILEP;   //!
   TBranch        *b_m_scaleFactor_BTAG;   //!
   TBranch        *b_m_scaleFactor_WJETSNORM;   //!
   TBranch        *b_m_scaleFactor_WJETSSHAPE;   //!
   TBranch        *b_m_scaleFactor_JVFSF;   //!
   TBranch        *b_m_scaleFactor_ZVERTEX;   //!
   TBranch        *b_m_scaleFactor_ALLPRETAG;   //!
   TBranch        *b_m_scaleFactor_ALLBTAG;   //!
   TBranch        *b_truE;   //!
   TBranch        *b_truM;   //!
   TBranch        *b_trigE;   //!
   TBranch        *b_trigM;   //!
   TBranch        *b_passGRL;   //!
   TBranch        *b_cosmicEvent;   //!
   TBranch        *b_isOS;   //!
   TBranch        *b_hasGoodVertex;   //!
   TBranch        *b_ht;   //!
   TBranch        *b_mass;   //!
   TBranch        *b_massInv_LL;   //!
   TBranch        *b_massInv_BQQ;   //!
   TBranch        *b_massTrans_BLMet;   //!
   TBranch        *b_massTrans_LMet;   //!
   TBranch        *b_flag_DL;   //!
   TBranch        *b_flag_TTZ;   //!
   TBranch        *b_channel_DL;   //!
   TBranch        *b_channel_TTZ;   //!
   TBranch        *b_scaledWeight;   //!
   TBranch        *b_lep_n;   //!
   TBranch        *b_lep_truthMatched;   //!
   TBranch        *b_lep_trigMatched;   //!
   TBranch        *b_lep_pt;   //!
   TBranch        *b_lep_eta;   //!
   TBranch        *b_lep_phi;   //!
   TBranch        *b_lep_E;   //!
   TBranch        *b_lep_z0;   //!
   TBranch        *b_lep_charge;   //!
   TBranch        *b_lep_isTight;   //!
   TBranch        *b_lep_type;   //!
   TBranch        *b_lep_flag;   //!
   TBranch        *b_el_cl_eta;   //!
   TBranch        *b_lep_ptcone30;   //!
   TBranch        *b_lep_etcone20;   //!
   TBranch        *b_lep_miniIso10_4;   //!
   TBranch        *b_massTrans_LMet_Vec;   //!
   TBranch        *b_lepPair_n;   //!
   TBranch        *b_isSameFlavor_LL_Vec;   //!
   TBranch        *b_isOppSign_LL_Vec;   //!
   TBranch        *b_massInv_LL_Vec;   //!
   TBranch        *b_met_sumet;   //!
   TBranch        *b_met_et;   //!
   TBranch        *b_met_phi;   //!
   TBranch        *b_jet_n;   //!
   TBranch        *b_alljet_n;   //!
   TBranch        *b_jet_pt;   //!
   TBranch        *b_jet_eta;   //!
   TBranch        *b_jet_phi;   //!
   TBranch        *b_jet_E;   //!
   TBranch        *b_jet_m;   //!
   TBranch        *b_jet_jvf;   //!
   TBranch        *b_jet_trueflav;   //!
   TBranch        *b_jet_truthMatched;   //!
   TBranch        *b_jet_SV0;   //!
   TBranch        *b_jet_MV1;   //!
   TBranch        *b_jet_flag;   //!

   MiniML(TTree *tree=0);
   virtual ~MiniML();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef MiniML_cxx
MiniML::MiniML(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("/home/ATLAS/disipio/development/BoostedTops/runD3PD/MiniML/ML_2D.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("/home/ATLAS/disipio/development/BoostedTops/runD3PD/MiniML/ML_2D.root");
      }
      f->GetObject("mini",tree);

   }
   Init(tree);
}

MiniML::~MiniML()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t MiniML::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t MiniML::LoadTree(Long64_t entry)
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

void MiniML::Init(TTree *tree)
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
   fChain->SetBranchAddress("mcWeight", &mcWeight, &b_mcWeight);
   fChain->SetBranchAddress("eventWeight_PRETAG", &eventWeight_PRETAG, &b_eventWeight_PRETAG);
   fChain->SetBranchAddress("eventWeight_BTAG", &eventWeight_BTAG, &b_eventWeight_BTAG);
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
   fChain->SetBranchAddress("scaleFactor_DILEP", &scaleFactor_DILEP, &b_m_scaleFactor_DILEP);
   fChain->SetBranchAddress("scaleFactor_BTAG", &scaleFactor_BTAG, &b_m_scaleFactor_BTAG);
   fChain->SetBranchAddress("scaleFactor_WJETSNORM", &scaleFactor_WJETSNORM, &b_m_scaleFactor_WJETSNORM);
   fChain->SetBranchAddress("scaleFactor_WJETSSHAPE", &scaleFactor_WJETSSHAPE, &b_m_scaleFactor_WJETSSHAPE);
   fChain->SetBranchAddress("scaleFactor_JVFSF", &scaleFactor_JVFSF, &b_m_scaleFactor_JVFSF);
   fChain->SetBranchAddress("scaleFactor_ZVERTEX", &scaleFactor_ZVERTEX, &b_m_scaleFactor_ZVERTEX);
   fChain->SetBranchAddress("scaleFactor_ALLPRETAG", &scaleFactor_ALLPRETAG, &b_m_scaleFactor_ALLPRETAG);
   fChain->SetBranchAddress("scaleFactor_ALLBTAG", &scaleFactor_ALLBTAG, &b_m_scaleFactor_ALLBTAG);
   fChain->SetBranchAddress("truE", &truE, &b_truE);
   fChain->SetBranchAddress("truM", &truM, &b_truM);
   fChain->SetBranchAddress("trigE", &trigE, &b_trigE);
   fChain->SetBranchAddress("trigM", &trigM, &b_trigM);
   fChain->SetBranchAddress("passGRL", &passGRL, &b_passGRL);
   fChain->SetBranchAddress("cosmicEvent", &cosmicEvent, &b_cosmicEvent);
   fChain->SetBranchAddress("isOS", &isOS, &b_isOS);
   fChain->SetBranchAddress("hasGoodVertex", &hasGoodVertex, &b_hasGoodVertex);
   fChain->SetBranchAddress("ht", &ht, &b_ht);
   fChain->SetBranchAddress("mass", &mass, &b_mass);
   fChain->SetBranchAddress("massInv_LL", &massInv_LL, &b_massInv_LL);
   fChain->SetBranchAddress("massInv_BQQ", &massInv_BQQ, &b_massInv_BQQ);
   fChain->SetBranchAddress("massTrans_BLMet", &massTrans_BLMet, &b_massTrans_BLMet);
   fChain->SetBranchAddress("massTrans_LMet", &massTrans_LMet, &b_massTrans_LMet);
   fChain->SetBranchAddress("flag_DL", &flag_DL, &b_flag_DL);
   fChain->SetBranchAddress("flag_TTZ", &flag_TTZ, &b_flag_TTZ);
   fChain->SetBranchAddress("channel_DL", &channel_DL, &b_channel_DL);
   fChain->SetBranchAddress("channel_TTZ", &channel_TTZ, &b_channel_TTZ);
   fChain->SetBranchAddress("scaledWeight", &scaledWeight, &b_scaledWeight);
   fChain->SetBranchAddress("lep_n", &lep_n, &b_lep_n);
   fChain->SetBranchAddress("lep_truthMatched", lep_truthMatched, &b_lep_truthMatched);
   fChain->SetBranchAddress("lep_trigMatched", lep_trigMatched, &b_lep_trigMatched);
   fChain->SetBranchAddress("lep_pt", lep_pt, &b_lep_pt);
   fChain->SetBranchAddress("lep_eta", lep_eta, &b_lep_eta);
   fChain->SetBranchAddress("lep_phi", lep_phi, &b_lep_phi);
   fChain->SetBranchAddress("lep_E", lep_E, &b_lep_E);
   fChain->SetBranchAddress("lep_z0", lep_z0, &b_lep_z0);
   fChain->SetBranchAddress("lep_charge", lep_charge, &b_lep_charge);
   fChain->SetBranchAddress("lep_isTight", lep_isTight, &b_lep_isTight);
   fChain->SetBranchAddress("lep_type", lep_type, &b_lep_type);
   fChain->SetBranchAddress("lep_flag", lep_flag, &b_lep_flag);
   fChain->SetBranchAddress("el_cl_eta", el_cl_eta, &b_el_cl_eta);
   fChain->SetBranchAddress("lep_ptcone30", lep_ptcone30, &b_lep_ptcone30);
   fChain->SetBranchAddress("lep_etcone20", lep_etcone20, &b_lep_etcone20);
   fChain->SetBranchAddress("lep_miniIso10_4", lep_miniIso10_4, &b_lep_miniIso10_4);
   fChain->SetBranchAddress("massTrans_LMet_Vec", massTrans_LMet_Vec, &b_massTrans_LMet_Vec);
   fChain->SetBranchAddress("lepPair_n", &lepPair_n, &b_lepPair_n);
   fChain->SetBranchAddress("isSameFlavor_LL_Vec", isSameFlavor_LL_Vec, &b_isSameFlavor_LL_Vec);
   fChain->SetBranchAddress("isOppSign_LL_Vec", isOppSign_LL_Vec, &b_isOppSign_LL_Vec);
   fChain->SetBranchAddress("massInv_LL_Vec", massInv_LL_Vec, &b_massInv_LL_Vec);
   fChain->SetBranchAddress("met_sumet", &met_sumet, &b_met_sumet);
   fChain->SetBranchAddress("met_et", &met_et, &b_met_et);
   fChain->SetBranchAddress("met_phi", &met_phi, &b_met_phi);
   fChain->SetBranchAddress("jet_n", &jet_n, &b_jet_n);
   fChain->SetBranchAddress("alljet_n", &alljet_n, &b_alljet_n);
   fChain->SetBranchAddress("jet_pt", jet_pt, &b_jet_pt);
   fChain->SetBranchAddress("jet_eta", jet_eta, &b_jet_eta);
   fChain->SetBranchAddress("jet_phi", jet_phi, &b_jet_phi);
   fChain->SetBranchAddress("jet_E", jet_E, &b_jet_E);
   fChain->SetBranchAddress("jet_m", jet_m, &b_jet_m);
   fChain->SetBranchAddress("jet_jvf", jet_jvf, &b_jet_jvf);
   fChain->SetBranchAddress("jet_trueflav", jet_trueflav, &b_jet_trueflav);
   fChain->SetBranchAddress("jet_truthMatched", jet_truthMatched, &b_jet_truthMatched);
   fChain->SetBranchAddress("jet_SV0", jet_SV0, &b_jet_SV0);
   fChain->SetBranchAddress("jet_MV1", jet_MV1, &b_jet_MV1);
   fChain->SetBranchAddress("jet_flag", jet_flag, &b_jet_flag);
   Notify();
}

Bool_t MiniML::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void MiniML::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t MiniML::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef MiniML_cxx
