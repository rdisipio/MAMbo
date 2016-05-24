//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Mon Feb 15 10:39:47 2016 by ROOT version 6.04/12
//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Mon Nov 30 18:01:59 2015 by ROOT version 6.02/12
// from TTree sumWeights/
// found on file: /home/ATLAS-T3/mromano/TTbarUnfold/ljets.output.root
//////////////////////////////////////////////////////////

#ifndef sumWeights_h
#define sumWeights_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <vector>
#include <map>
#include <string>
#include <cstdio>
using namespace std;


class PDFsumWeights {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Int_t           dsid;
   vector<float>   *CT14nlo;
   vector<float>   *NNPDF30_nlo_as_0118;
   vector<float>   *MMHT2014nlo68cl;
   vector<float>   *PDF4LHC15_nlo_30;
   vector<float>   *PDF4LHC15_nlo_asvar;
   vector<float>   *m_pdfWeights;
   string m_pdfName;

   // List of branches
   TBranch        *b_dsid;   //!
   TBranch        *b_CT14nlo;   //!
   TBranch        *b_NNPDF30_nlo_as_0118;   //!
   TBranch        *b_MMHT2014nlo68cl;   //!
   TBranch        *b_PDF4LHC15_nlo_30;   //!
   TBranch        *b_PDF4LHC15_nlo_asvar;   //!

   PDFsumWeights( string pdfName, TTree *tree=0);
   virtual ~PDFsumWeights();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(string pdfname,TTree *tree);
   virtual void     Loop( int& id, float& nevents, int nVariation);
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef PDFsumWeights_cxx
PDFsumWeights::PDFsumWeights(string pdfName,TTree *tree) : fChain(0) 
{
	
	m_pdfName = pdfName;
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("/gpfs_data/storm/atlas/localgroupdisk/rucio/user/amenga/bd/cf/user.amenga.7696864._000132.ljets.output.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("/gpfs_data/storm/atlas/localgroupdisk/rucio/user/amenga/bd/cf/user.amenga.7696864._000132.ljets.output.root");
      }
      f->GetObject("PDFsumWeights",tree);

   }
   Init(pdfName, tree);
}

PDFsumWeights::~PDFsumWeights()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t PDFsumWeights::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t PDFsumWeights::LoadTree(Long64_t entry)
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

void PDFsumWeights::Init(string pdfName,TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   CT14nlo = 0;
   NNPDF30_nlo_as_0118 = 0;
   MMHT2014nlo68cl = 0;
   PDF4LHC15_nlo_30 = 0;
   PDF4LHC15_nlo_asvar = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("dsid", &dsid, &b_dsid);
   fChain->SetBranchAddress("CT14nlo", &CT14nlo, &b_CT14nlo);
   fChain->SetBranchAddress("NNPDF30_nlo_as_0118", &NNPDF30_nlo_as_0118, &b_NNPDF30_nlo_as_0118);
   fChain->SetBranchAddress("MMHT2014nlo68cl", &MMHT2014nlo68cl, &b_MMHT2014nlo68cl);
   fChain->SetBranchAddress("PDF4LHC15_nlo_30", &PDF4LHC15_nlo_30, &b_PDF4LHC15_nlo_30);
   fChain->SetBranchAddress("PDF4LHC15_nlo_asvar", &PDF4LHC15_nlo_asvar, &b_PDF4LHC15_nlo_asvar);
   if( pdfName == "CT14nlo" )
   {
	     m_pdfWeights = CT14nlo;
		 }
   else if( pdfName == "NNPDF30_nlo_as_0118" )
   {
	     m_pdfWeights = NNPDF30_nlo_as_0118;
		 }
   else if( pdfName == "PDF4LHC15_nlo_asvar" )
   {
	     m_pdfWeights = PDF4LHC15_nlo_asvar;
		 }
   else if( pdfName == "MMHT2014nlo68cl" )
   {
	     m_pdfWeights = MMHT2014nlo68cl;
   }
   else if( pdfName == "PDF4LHC15_nlo_30" )
   {
	     m_pdfWeights = PDF4LHC15_nlo_30;
  }
   
   
   
   Notify();
}

Bool_t PDFsumWeights::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void PDFsumWeights::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t PDFsumWeights::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef PDFsumWeights_cxx
