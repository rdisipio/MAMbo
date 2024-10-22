// Kelsey Bilsback
// May 2012
//
// This code is used to read in the theory 
// root -l -b -q 'RebinTheory_yt_difftop.C+("data/difftop_lhc_8TeV_y_ct14.dat")'

#include <stdlib.h>
#include <iostream>
using std::cerr;
using std::cout;
using std::endl;

#include <fstream>
using std::ifstream;

#include <cstdlib>
#include <TROOT.h>
#include <TH1D.h>
#include <TGraph.h>
//#include <TVectorT.h>
#include <TCanvas.h>
#include <TFile.h>

using namespace std;

#include "Theory.C"


TH1D *RebinTheory_yt_difftop(TString inputName = "data/difftop_lhc_8TeV_y_ct14.dat", bool Draw = true, int debug = 1) 
{
  
  MyDataType data;
  ifstream readData;
  Float_t num;

  // opens file, throws error if file cannot be opened
  readData.open(inputName.Data());
  if (!readData) {
    cerr << "File could not be opened." << endl;
    exit(1);
  }

  // fills the data array with the data from the file
  // prints what is filled in the array
  int nRows = 0;
  cout << "Reading data..." << endl;
  while (!readData.eof()) {
    vector<double> item;
    readData >> num;
    item.push_back(num);
    readData >> num;
    item.push_back(num);
    readData >> num;
    if (debug) {
      for (int it = 0; it < item.size(); ++it) {
	cout << " " << item[it];
      }
      cout << endl;
    } // debug
    data.push_back(item);
    nRows++;
  }

  // closes the file
  readData.close();
  if (debug > 0)
    cout << "End of File, read " << nRows << " lines." << endl;

  // CMS binning 8 TeV
  const int numXbins = 11;
  double xbins[numXbins] = {-2.5,-1.3,-0.9,-0.6,-0.3,0,0.3,0.6,0.9,1.3,2.5};
 
  int numBins = numXbins - 1;

   if (debug > 0)
    cout << "Making out root file..." << endl;
  TString outName = inputName;
  outName.ReplaceAll("data/", "");
  outName.ReplaceAll(".dat", "");
  TFile *outFile = new TFile(outName + ".root", "recreate");
  TString basename = "theory";
  //  TString basename = outName;

  if (debug > 0)
    cout << "Making the TGraph..." << endl;
  // makes graph of original theory 
  TGraph *theory = new TGraph(nRows);
  theory -> SetName("gr_" + basename);
  double integral = 0.;
  for(int j = 0; j < nRows; j++){
    cout << "Setting point " << j << " " << data[j][0] << " " << data[j][1] << endl;
    theory->SetPoint(j,data[j][0],data[j][1]);
    if (j < nRows-1) {
      //  integral += (data[j+1][0]-data[j][0])*data[j][1];
      integral += getArea(data[j][0], data[j+1][0], data[j][1], data[j+1][1]);
    }
  }
  theory -> SetLineColor(kRed);
  theory -> SetMarkerColor(kRed);
  theory -> SetMarkerColor(kRed);
  cout << " integral: Graph=" << theory -> Integral()
       << " by-hand=" << integral
       << endl;
  
  if (debug > 0)
    cout << "Making the binned histo..." << endl; 
  // call the function MakeHisto from the Theory.C file and draw it
  TH1D *theoryNewBin = 0;
  bool ValuesAreAtCentreOfBin = false; // !!!
  theoryNewBin = MakeHisto("TheoryXs_abs", "TheoryXs_abs", numBins, xbins, data, debug, ValuesAreAtCentreOfBin);
  TH1D *theoryNewBin_rel = NormalizeHisto(theoryNewBin);
  cout << "Integral after rebin: " << theoryNewBin->Integral("width") << endl;
  


  TCanvas *c1 = 0;
  if (Draw and theoryNewBin) {
    c1 = new TCanvas();
    c1->cd();
    c1->SetLogy(kTRUE);
    theory->Draw("AL");
    theoryNewBin->Draw("same");
    c1->Print("theory.eps");
  }

  theory -> Write();
  outFile -> Write();

  return theoryNewBin;

}

