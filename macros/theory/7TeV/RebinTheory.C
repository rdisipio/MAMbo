// Kelsey Bilsback
// May 2012
//
// This code is used to read in the theory from the pttopnnloapprox7lhc173m.dat and pttopnnloapprox7lhc173mT.dat files. It then rebins
// the theory in HistoMakerBinnings.cfg.
// using TheoryBins.C

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


TH1D *RebinTheory(TString inputName = "data/pttopnnloapprox7lhc173m.dat", bool Draw = false, int debug = 0) 
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
  readData >> num;
  while (!readData.eof()) {
    //cout << num << endl;
    vector<double> item;
    //    data[nRows][0] = num;
    item.push_back(num);
    readData >> num;
    //cout << num << endl;
    //    data[nRows][1] = num;
    item.push_back(num);
    readData >> num;
    data.push_back(item);
    nRows++;
  }

  // closes the file
  readData.close();
  if (debug > 0)
    cout << "End of File, read " << nRows << " lines." << endl;


  // creates array xbins with proper binning
  // see /configs/HistoMakerBinnings.cfg 
  //double xbins [numXbins] = {0., 41.27, 85.80, 132.37, 184.3, 245.28, 320.91, 421.99, 571.23}; //standard binning
  //double xbins [numXbins] = { 0., 50., 105., 160., 230., 310., 420., 600., 1000.}; //Opt1
  //double xbins[numXbins] = { 0., 55., 110., 170., 245., 340., 500., 820., 1000.}; //Opt2 
  //double xbins[numXbins] = { 0., 50., 105., 160., 230., 310., 420., 1000.}; //Opt3 
  //double xbins[numXbins] = { 0., 50., 100., 150., 200., 250., 400., 600., 1000.}; //Opt4
  //double xbins[numXbins] = { 0., 50., 100., 150., 200., 250., 325., 600., 1000.}; //Opt5


  // ATLAS
  static const int numXbins = 8;
  double xbins[numXbins] = { 0., 50., 100., 150., 200., 250., 350., 800.}; //Opt5

  // CMS binning:
  // const int numXbins = 8;
  //  double xbins[numXbins] = {0,60,100,150,200,260,320,400};
 

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
    theory->SetPoint(j,data[j][0],data[j][1]);
    if (j < nRows-1)
      integral += (data[j+1][0]-data[j][0])*data[j][1];
    // integral += getArea(data[j][0], data[j+1][0], data[j][1], data[j+1][1]);
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
  theoryNewBin=MakeHisto("h_" + basename, "Theory Histogram", numBins, xbins, data);
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

