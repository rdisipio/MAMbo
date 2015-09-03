
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "../../share/AtlasStyle.C"

using std::endl;
using std::cerr;
using std::cout;


/*
#include "RooDataSet.h"
#include "RooFormulaVar.h"
#include "RooPlot.h"
#include "RooArgSet.h"
#include "RooGlobalFunc.h"
*/

#include "TLine.h"
#include "TString.h"
#include "TFile.h"
#include "TTree.h"
#include "TChain.h"
#include "TMath.h"
#include "TCanvas.h"
#include "TLatex.h"
#include "TSystem.h"
#include "TStyle.h"
#include "TLegend.h"

#include "TH1D.h"
#include "TH2D.h"
#include "TH1F.h"
#include "TH2F.h"

#include "TF1.h"
#include "TGraph.h"
#include "TGraphErrors.h"



// _______________________________________________________________________

TH1D* MakeRatio(TH1D* h1,TH1D* h2)
{
  TH1D* ratio = (TH1D*) h1 -> Clone( TString(h1 -> GetName()) + "_div_" + TString(h2 -> GetName()) );
  ratio -> Divide(h2);
  return ratio;
}


// _______________________________________________________________________

void PrintRMS(TH1D *histo)
{
  cout << "histo " << histo->GetName() << " mean=" << histo->GetMean() << " RMS=" << histo->GetRMS() << endl;
}

// _______________________________________________________________________
// _______________________________________________________________________
// _______________________________________________________________________



void Cmp() 
{


  SetAtlasStyle ();

  TFile *_file_old = TFile::Open("v1/ptaNNNLO8lhc173.3m.root");
  TFile *_file_good = TFile::Open("v2_goodTri/ptaNNNLO8lhc173.3m.root");
  TFile *_file_bad = TFile::Open("v2_badTri/ptaNNNLO8lhc173.3m.root");
  TFile *_file_binCentre = TFile::Open("v2_stepLike/ptaNNNLO8lhc173.3m.root");
  TFile *_file_RDS = TFile::Open("topH_pt_ll.aNNNLO.root");

  TH1D *h_old = (TH1D*) _file_old -> Get("h_theory");
  TH1D *h_good = (TH1D*) _file_good -> Get("h_theory");
  TH1D *h_bad = (TH1D*) _file_bad -> Get("h_theory");
  TH1D *h_binCentre = (TH1D*) _file_binCentre -> Get("h_theory");
  TH1D *h_RDS = (TH1D*) _file_RDS -> Get("TheoryXs_abs");

  TGraph* gr = (TGraph*) _file_good -> Get("gr_theory");

  PrintRMS(h_old);
  PrintRMS(h_good);
  PrintRMS(h_bad);
  PrintRMS(h_binCentre);
  PrintRMS(h_RDS);

  TCanvas *can = new TCanvas();

  double bsize = 0.;
  TPad *pad1 = new TPad("pad1","histos",0.,0.50+bsize,1.,1.);
  pad1 -> SetBottomMargin(0.); // important!
  TPad *pad2 = new TPad("pad2","ratio",0.,0.,1.,0.50-bsize);
  pad2 -> SetTopMargin(0.); // important!
  //pad2 -> SetGridx(true);
  // pad2 -> SetGridy(true);

  pad1 -> Draw();
  pad2 -> Draw();  

  pad1 -> cd();

  h_good->SetLineColor(kRed); 
  h_good->SetLineWidth(3); 
  h_good->SetLineStyle(1); 
  h_good->Draw("hist");
  
  h_bad->SetLineColor(kBlue); 
  h_bad->SetLineWidth(2);
  h_bad->SetLineStyle(1); 
  h_bad->Draw("hist same");

  h_binCentre->SetLineColor(kMagenta); 
  h_binCentre->SetLineWidth(3);
  h_binCentre->SetLineStyle(3); 
  h_binCentre->Draw("hist same");

  h_RDS->SetLineColor(kAzure); 
  h_RDS->SetLineWidth(3);
  h_RDS->SetLineStyle(4); 
  h_RDS->Draw("hist same");
  
  h_old -> SetLineStyle(2); 
  h_old -> SetLineColor(kBlack); 
  h_old -> Draw("hist same");

  gr -> SetMarkerSize(0.8);
  gr -> SetMarkerStyle(21);
  gr -> SetMarkerColor(kBlack);
  gr -> Draw("P");

  TLegend *leg1 = new TLegend(0.5, 0.5, 0.87, 0.87);
  leg1 -> SetBorderSize(0);
  leg1 -> SetHeader("8 TeV");
  leg1 -> AddEntry(h_good, "new", "PL");
  leg1 -> AddEntry(h_bad, "bugged tri", "PL");
  leg1 -> AddEntry(h_old, "old", "PL");
  leg1 -> AddEntry(h_binCentre, "binCentre", "PL");
  leg1 -> AddEntry(h_RDS, "Riccardo", "PL");
  leg1 -> Draw();

  pad2 -> cd();
  
  TH1D* h_bad_r = MakeRatio(h_bad, h_good);
  TH1D* h_binCentre_r = MakeRatio(h_binCentre, h_good);
  TH1D* h_old_r = MakeRatio(h_old, h_good);
  TH1D* h_RDS_r = MakeRatio(h_RDS, h_good);

  // draw ratios:

  h_bad_r -> SetMaximum(1.2);
  h_bad_r -> SetMinimum(0.8);

  h_bad_r -> Draw("hist");
  h_binCentre_r -> Draw("hist same");
  h_RDS_r -> Draw("hist same");
  h_old_r -> Draw("hist same");
 
  TLegend *leg2 = new TLegend(0.5, 0.5, 0.87, 0.87);
  leg2 -> SetBorderSize(0);
  leg2 -> SetHeader("8 TeV");
  leg2 -> AddEntry(h_RDS_r, "Riccardo / new", "PL");
  leg2 -> AddEntry(h_bad_r, "bugged tri / new", "PL");
  leg2 -> AddEntry(h_old_r, "old / new", "PL");
  leg2 -> AddEntry(h_binCentre_r, "binCentre / new", "PL");
  leg2 -> Draw();


}
