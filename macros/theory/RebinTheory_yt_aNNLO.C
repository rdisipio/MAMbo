// Kelsey Bilsback
// May 2012
//
// This code is used to read in the theory 
// root -l -b -q 'RebinTheory_yt_aNNLO.C+("data/yaNNNLO8lhc173.3m.dat")'

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


TH1D *RebinTheory_yt_aNNLO(TString inputName = "data/yaNNNLO8lhc173.3m.dat", bool Draw = true, int debug = 0) 
{
  
  MyDataType data;
  ifstream readData;
  Float_t num;

  // opens file, throws error if file cannot be opened
  //  readData.open("data/pttopnnloapprox7lhc173m.dat");
  //  readData.open("data/pttopnnloapprox7lhc173mT.dat");
  readData.open(inputName.Data());
  if (!readData) {
    cerr << "File could not be opened." << endl;
    exit(1);
  }

  // fills the data array with the data from the file
  // prints what is filled in the array
  int nRows = 0;

  while (!readData.eof()) {
    cout << "nRows=" << nRows << endl;
    vector<double> item;
    readData >> num;
    cout << "  num0=" << num << endl;
    item.push_back(num);
    readData >> num;
    cout << "  num1=" << num << endl;
    item.push_back(num);
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
  for(int j = 0; j < nRows-1; j++){
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
  theoryNewBin = MakeHisto("h_" + basename, "Theory Histogram", numBins, xbins, data, debug, ValuesAreAtCentreOfBin);
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

