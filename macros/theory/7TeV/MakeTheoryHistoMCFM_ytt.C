#include <fstream>
#include <string>
#include <iostream>

#include "TH1F.h"
#include "TFile.h"

// usage:
// root -l MakeTheoryHistoMCFM_ytt.C+

using std::cout;
using std::endl;

void DivideByBinWidth(TH1F* histo);

void MakeTheoryHistoMCFM_ytt()
{

  const int N = 3;
  std::string dirname = "data/";
  std::string names[N] = {"ytt_MCFM_scale172.txt", "ytt_MCFM_scale345.txt", "ytt_MCFM_scale690.txt"};

  TH1F *hist[N] = {0, 0, 0};

  const int nbins = 6;
  double xbins[nbins+1] = { -2.5, -1., -0.5, 0., 0.5, 1., 2.5};
 
  TFile *outfile = new TFile("Theory_MCFM_ytt.root", "recreate");

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
    DivideByBinWidth(hist[i]);
    
    cout << "mean : " << hist[i] -> GetMean() << endl;
    cout << "int  : " << hist[i] -> Integral("width") << endl;


    //    hist[i] -> Write();
      
    
  } // files
  
  outfile -> Write();

   exit(0);
}


void DivideByBinWidth(TH1F* histo){
   
   for(unsigned int bin=1;bin<histo->GetNbinsX();++bin){
      double binWidth = histo->GetBinWidth(bin);
      double binContent = histo->GetBinContent(bin);
      histo->SetBinContent(bin,binContent/binWidth);
   }
   
}


