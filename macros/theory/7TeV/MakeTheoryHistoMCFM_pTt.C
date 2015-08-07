
#include <fstream>
#include <string>
#include <iostream>

#include "StandardIncludes.h"
#include "HistoTools.C"


// usage:
// root -l MakeTheoryHistoMCFM_pTt.C+



void MakeTheoryHistoMCFM_pTt()
{

  const int N = 3;
  std::string dirname = "data/";
  std::string names[N] = {"pttop_MCFM_scale172.txt", "pttop_MCFM_scale345.txt", "pttop_MCFM_scale690.txt"};
  //std::string names[N] = {"pttop_MCFM_scale172_Opt1.txt", "pttop_MCFM_scale345_Opt1.txt", "pttop_MCFM_scale690_Opt1.txt"};
  //std::string names[N] = {"pttop_MCFM_scale172_Opt2.txt", "pttop_MCFM_scale345_Opt2.txt", "pttop_MCFM_scale690_Opt2.txt"};
  //std::string names[N] = {"pttop_MCFM_scale172_Opt3.txt", "pttop_MCFM_scale345_Opt3.txt", "pttop_MCFM_scale690_Opt3.txt"};
  //std::string names[N] = {"pttop_MCFM_scale172_Opt4.txt", "pttop_MCFM_scale345_Opt4.txt", "pttop_MCFM_scale690_Opt4.txt"};
  //std::string names[N] = {"pttop_MCFM_scale172_Opt5.txt", "pttop_MCFM_scale345_Opt5.txt", "pttop_MCFM_scale690_Opt5.txt"};


  TH1F *hist[N] = {0, 0, 0};

  //double xbins[nbins+1] = { 0., 41.27, 85.80, 132.37, 184.3, 245.28, 320.91, 421.99, 571.23}; //Resolution Binning
  //double xbins[nbins+1] = { 0., 50., 105., 160., 230., 310., 420., 600., 1000.}; //Opt1
  //double xbins[nbins+1] = { 0., 55., 110., 170., 245., 340., 500., 820., 1000.}; //Opt2 
  //double xbins[nbins+1] = { 0., 50., 105., 160., 230., 310., 420., 1000.}; //Opt3 
  //double xbins[nbins+1] = { 0., 50., 100., 150., 200., 250., 400., 600., 1000.}; //Opt4
  //double xbins[nbins+1] = { 0., 50., 100., 150., 200., 250., 350., 600., 1000.}; //Opt5
 

  const int nbins = 7;
  double xbins[nbins+1] = { 0., 50., 100., 150., 200., 250., 350., 800.}; //final binning

  // CMS binning:
  // const int nbins = 7;
  //  double xbins[nbins+1] = {0,60,100,150,200,260,320,400};
 
  //TFile *outfile = new TFile("Theory_MCFM_pTt.root", "recreate");
  //TFile *outfile = new TFile("Theory_MCFM_pTt_Opt1.root", "recreate");
  //TFile *outfile = new TFile("Theory_MCFM_pTt_Opt2.root", "recreate");
  //TFile *outfile = new TFile("Theory_MCFM_pTt_Opt3.root", "recreate");
  //TFile *outfile = new TFile("Theory_MCFM_pTt_Opt4.root", "recreate");
  TFile *outfile = new TFile("Theory_MCFM_pTt.root", "recreate");

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
