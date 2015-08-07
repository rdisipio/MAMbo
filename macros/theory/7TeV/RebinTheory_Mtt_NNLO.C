// Kelsey Bilsback
// May 2012
// fixed by Jiri, Jan 2014
//
// This code is used to read in the theory from the pttopnnloapprox7lhc173m.dat and pttopnnloapprox7lhc173mT.dat files. It then rebins
// the theory in HistoMakerBinnings.cfg.
// in dat files, the columns are: Mtt, central, +scale, -scale, +pdf, -pdf, +pdf&alphas, -pdf&alphas.
// using TheoryBins.C



// main usage: 
// root -l -b -q 'RebinTheory_Mtt_NNLO.C+("data/Mtt_7000_Mtt_norm.dat", 0, false, 1, "recreate")'
// root -l -b -q 'RebinTheory_Mtt_NNLO.C+("data/Mtt_7000_Mtt_fin.dat", 0, false, 1, "recreate")'



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

// _____________________________________________________________
// _____________________________________________________________
// _____________________________________________________________

TH1D *RebinTheory_Mtt_NNLO(TString inputName = "data/Mtt_7000_Mtt_fin.dat", int ResultToUse = -1, bool Draw = true, int debug = 2, TString fopt = "recreate" ) 
{
  
  MyDataType data;
  ifstream readData;
  const int nresults = 7;
  double xx, y[nresults];
  assert(ResultToUse < nresults);

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
  readData >> xx;
  while (!readData.eof()) {
    vector<double> item;
    item.push_back(xx);
    for (int i = 0; i < nresults; ++i)
      readData >> y[i];
    if (ResultToUse <= 0)
      item.push_back(y[0]);
    else // pdf or scale variation:
      item.push_back(y[0] + y[ResultToUse]);
    if (debug > 1) {
      cout << " xx=" << xx;
      for (int i = 0; i < nresults; ++i)
	cout << " y" << i << "=" << y[i];
      cout << endl;
    }

    readData >> xx;
    data.push_back(item);
    nRows++;
  }

  // closes the file
  readData.close();
  if (debug > 0)
    cout << "End of File, read " << nRows << " lines." << endl;

  // ATLAS
   static const int numXbins = 6;
  double xbins[numXbins] = { 250., 450., 550., 700., 950., 2700. };
  // // next round: new Miho: 250. 450. 550. 700. 950. 2700. // 960 -> 950

  // CMS binning:
  //  const int numXbins = 8;
  //  double xbins[numXbins] = { 345, 400, 470, 550, 650, 800, 1100, 1600 };


  int numBins = numXbins - 1;

   if (debug > 0)
    cout << "Making out root file..." << endl;
  TString outName = inputName;
  outName.ReplaceAll("data/", "");
  outName.ReplaceAll(".dat", "");
  TFile *outFile = new TFile(outName + ".root",  fopt);
  TString basename = "theoryMtt_";
  if (ResultToUse > 0)
    basename += ResultToUse;
  //  TString basename = outName;

  if (debug > 0)
    cout << "Making the TGraph..." << endl;
  // makes graph of original theory 
  TGraph *theory = new TGraph(nRows);
  theory -> SetName("gr_" + basename);
  double integral = 0.;
  for(int j = 0; j < nRows; j++){
    theory->SetPoint(j,data[j][0],data[j][1]);
    if (j < nRows-1) {
      // this gives rel. xsect integral of 1...
      if (debug > 1) {
	cout << data[j+1][0] << "," << data[j][0] << "," << data[j][1] << endl;
      }
      //      integral += (data[j+1][0]-data[j][0])*data[j][1];
      // this gives 0.95...
      integral += getArea(data[j][0], data[j+1][0], data[j][1], data[j+1][1], true);
    }
  } // rows
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
  theoryNewBin=MakeHisto("h_" + basename, "Theory Histogram", numBins, xbins, data, debug, false, true);
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

// _____________________________________________________________
// _____________________________________________________________
// _____________________________________________________________


