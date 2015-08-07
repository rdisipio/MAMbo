
#include <fstream>
#include <string>
#include <iostream>

#include "StandardIncludes.h"
#include "HistoTools.C"


// usage:
// root -l MakeTheoryHistoMCFM_Mtt.C+



void MakeTheoryHistoMCFM_Mtt()
{

  const int N = 3;
  std::string dirname = "data/";
  // these are for thi bin edge 950, though later below we bin it in 960! jk 22.1.2013
  std::string names[N] = {"Mtt_MCFM_scale172.txt", "Mtt_MCFM_scale345.txt", "Mtt_MCFM_scale690.txt"};

  TH1F *hist[N] = {0, 0, 0};

  const int nbins = 5;
  double xbins[nbins+1] = { 250., 450., 550., 700., 950., 2700.};

  // CMS binning:
  //  const int nbins = 7;
  //  double xbins[nbins+1] = { 345, 400, 470, 550, 650, 800, 1100, 1600 };


  TFile *outfile = new TFile("Theory_MCFM_Mtt.root", "recreate");

  for (int i = 0; i < N; ++i) {


    std::string filename = dirname + names[i];
    TString basename = TString(names[i].c_str()).ReplaceAll(".txt", "");

    ifstream mystream(filename.c_str()); //, ios::in);
    cout << "Reading from file " << filename << endl;
    
    int il = 0;
    double val[nbins];
    hist[i] = new TH1F(basename, basename, nbins, (double*)xbins);
    while ( mystream >> val[il] ) {
      cout << val[il] << endl;
      hist[i] -> SetBinContent(il+1, val[il]);
      il++;
    } // file
    HistoTools::DivideByBinWidth(hist[i], 0);
      //    hist[i] -> Scale(1.);
    cout << "mean : " << hist[i] -> GetMean() << endl;
    cout << "int  : " << hist[i] -> Integral("width") << endl;


    //    hist[i] -> Write();
      
    
  } // files
  
  outfile -> Write();


}
