/* File HistoTools.cpp
 *
 * Created       : Fri Sep 14 16:05:31 CDT 2007
 * Author        : kvita
 * Purpose       : many buggeous histo/graph tools;-)
 * Last modified : 
 * Comments      : 
 */


// this somehow never works:
//#ifdef __CINT__

#include <math.h>
#include <cassert>

#ifdef ROOT_VERSION 
# include "TH1D.h"
# include "TH2D.h"
# include "TH1F.h"
# include "TLegend.h"
# include "TRandom3.h"
# include "TF1.h"
# include "TFile.h"
# include "TString.h"
# include "TObjString.h"
# include "TRandom3.h"
# include "TGraphErrors.h"
# include "TPaveText.h"
# include "TObject.h"
# include "TKey.h"
# include "TObjArray.h"
# include "TCanvas.h"
# include "TDirectory.h"
# include "TArrayD.h"
# include "TCanvas.h"
#endif

#ifndef ROOT_VERSION 
// this somehow never works:
//#if !(defined(__CINT__) || defined(__MAKECINT__))
#  include "HistoTools.h"
#endif

#include <fstream>
#include <iostream>
#include <vector>
#include <string>

using std::cout;
using std::cerr;
using std::endl;

/*
  void HistoTools()

  {
  #ifdef __CINT__
  cout<<"__CINT__\n";
  #else
  cout<<"NO __CINT__\n";
  #endif

  #ifdef __MAKECINT__
  cout<<"__MAKECINT__\n";
  #else
  cout<<"NO __MAKECINT__\n";
  #endif 
  }

*/

namespace HistoTools {


  const double Epsilon = 1.e-6;

  // set this debug variable to 1, 2 to get more verbose output:
  int _hist_util_debug = 0;
  // int _hist_util_debug = 2;

  const int maxNbins = 1000;

  const Int_t canv_height = 800;
  const Int_t canv_width = 800;

  const int markerStyle = 22;

  const  float mSlicesize = 1.;
  const  int linecol   = 2;
  const  int linewidth = 2;
  const  int gcol      = 4;
  const  int slicecol  = 1;
  const  int errbarcol = 1;
  const TString SliceDrawOpt = "e1hist";

  /* original design:
     const  int nx = 3;
     const  int ny = 3;
     const  float mSlicesize = 0.65;
     const  int linecol   = 2;
     const  int linewidth = 2;
     const  int gcol      = 4;
     const  int slicecol  = 108;
     const  int errbarcol = 15;
     const TString SliceDrawOpt = "e1";
  */
  // const  int NminGaussEntries = 20;


// _______________________________________________________________________________

TString GetSubstring(TString name1, TString name2, TString sub1, TString sub2)
{
  
  // check for sub1 or sub2 in both name1 and name2 consistently and uniquely

  TString result = "";

  if (name1.Contains(sub1) && name1.Contains(sub2) ) {
    cerr << "ERROR: Unable to determine " << sub1.Data() << " / " << sub2.Data() << " from the string name1!" << endl;
    return "";
  }
  if (name2.Contains(sub1) && name2.Contains(sub2) ) {
    cerr << "ERROR: Unable to determine " << sub1.Data() << " / " << sub2.Data() << " from the string name2!" << endl;
    return "";
  }
  if (name1.Contains(sub1) && name2.Contains(sub2) ) {
    cerr << "ERROR: trying to run on neither " << sub1.Data() << " / " << sub2.Data() << "!" << endl;
    return "";
  }
  if (name1.Contains(sub1) && name2.Contains(sub2) ) {
    cerr << "ERROR: trying to run on neither " << sub1.Data() << " / " << sub2.Data() << "!" << endl;
    return "";
  }
  if (name1.Contains(sub2))
    result = sub2;
  else
    if (name1.Contains(sub1))
      result = sub1;
    else {
      cerr << "ERROR: Unable to determine " << sub1.Data() << " / " << sub2.Data() << " from the file name!" << endl;
      return "";
    }

  return result;

}

// _______________________________________________________________________________

  void PrintCanvasAs(TCanvas *can, std::string suffix, bool SaveIndividual, std::string name)
  {

    if (name == "")
      can -> Print(Form("%s%s", can -> GetName(), suffix.c_str() ));
    else
      can -> Print(Form("%s%s", name.c_str(), suffix.c_str() ));

    if (SaveIndividual) {

      int k = 0;
      TPad *pad = 0;
      while(pad = (TPad*)can -> GetPad(++k)) {
      
	if (name == "")
	  pad -> Print(Form("%s_%i%s", can -> GetName(), k, suffix.c_str() ));
	else
	  pad -> Print(Form("%s_%i%s", name.c_str(), k, suffix.c_str() ));
      }
    
    } // save individual
  
  }


  // ___________________________________

  bool IsUniformlyBinned(TH1* h1)
  {

    // we compare bin widths to the first bin width, within the precision

    if (h1) {
      double precision = 1.e-4;
      bool isuniform = true;
      for (int i = 2; i < h1 -> GetNbinsX()+1; ++i)
	isuniform = isuniform && ( TMath::Abs(h1 -> GetBinWidth(1) - h1 -> GetBinWidth(i) ) < precision);
      return isuniform;
    }
    return true;

  }

  // ___________________________________

  void InvertHisto(TH1F* h1)
  {
    // perform 1/h1:
    if (h1) {
      double content, error;
      for (int i = 0; i <= h1 -> GetNbinsX()+1; ++i) {
	content = h1 -> GetBinContent(i);
	error = h1 -> GetBinError(i);
	if (TMath::Abs(content) > Epsilon) {
	  error /= content;
	  content = 1./content;
	  h1 -> SetBinContent(i, content);
	  h1 -> SetBinError(i, error);
	}
      }
      h1 -> Scale(1.);
    }
    return;
  }

  // ___________________________________

  TH1F* DivideHistos(TH1F* h1, TF1 *f2, std::string tag)
  {
    // perform h1/f2:
    if (h1 && f2) {
      //      cout << "Making divided histo " << (tag + std::string(h1 -> GetName()) + std::string(f2 -> GetName())).c_str() << endl;
      TH1F *div = (TH1F*) h1 -> Clone((tag + std::string(h1 -> GetName()) + std::string(f2 -> GetName())).c_str()); 
      div -> Divide(f2);
      return div;
    }
    return 0;
  }

  // ___________________________________

  TH1F* DivideHistos(TF1 *f2, TH1F* h1, std::string tag)
  {
    // perform f2/h1:
    if (h1 && f2) {
      //      cout << "Making divided histo " << (tag + std::string(f2 -> GetName()) + std::string(h1 -> GetName())).c_str() << endl;
      TH1F *div = (TH1F*) h1 -> Clone((tag + std::string(f2 -> GetName()) + std::string(h1 -> GetName())).c_str()); 

      // make a unity histo (flat at 1.)
      div -> Divide(h1);
      // zero the error bars:
      for (int i = 0; i <= div -> GetNbinsX() + 1; ++i) {
	div -> SetBinContent(i, 1.);
	div -> SetBinError(i, 0.);
      }
      div -> Divide(h1);
      div -> Multiply(f2);
      return div;
    }
    return 0;
  }

  // ___________________________________

  TH1F* DivideHistos(TH1F* h1, TH1F *h2, std::string tag)
  {
    // perform h1/h2:
    if (h1 && h2) {
      //      cout << "Making divided histo " << (tag + std::string(h1 -> GetName()) + std::string(h2 -> GetName())).c_str() << endl;
      TH1F *div = (TH1F*) h1 -> Clone((tag + std::string(h1 -> GetName()) + std::string(h2 -> GetName())).c_str()); 
      div -> Divide(h2);
      return div;
    }
    return 0;
  }
  
  // ___________________________________
  /*
  TH2F* DiagonaliseHistos(TH2F* h2, TH1F *fun, std::string name)
  {

    // jk 1.7.2008
    // getting a fit reco(truth), truth on x-axis,
    // we want to diagonalise the 2D migration matrix
    // i.g. for each y bin in given truth xbin, we need to move
    // <y_old> = fit to <y_new> = diag (i.e. bin center of the diagonal bin)
    // this can be done by performing in each y bin a transformation
    // y_new = y/fit*diag

    if (h2 && fun) {

      TH2F *div = (TH2F*) h2 -> Clone(name.c_str()); 
      div -> Reset();

      for (int i = 0; i <= div -> GetNbinsX() + 1; ++i) {
	div -> SetBinContent(i, 1.);
	div -> SetBinError(i, 0.);
      }
      div -> Divide(h1);
      div -> Multiply(f2);
      return div;
    }
    return 0;
  }
  */
  // ___________________________________

  TH1F* DivideHistosErrors(TH1F* h1, TH1F *h2, std::string tag)
  {
    // perform errh1/errh2:
    if (h1 && h2) {
      //      cout << "Making divided histo error bars " << (tag + std::string(h1 -> GetName()) + std::string(h2 -> GetName())).c_str() << endl;
      TH1F *div = (TH1F*) h1 -> Clone((tag + std::string(h1 -> GetName()) + std::string(h2 -> GetName())).c_str()); 
      div -> Reset();
      for (int i = 1; i <= div -> GetNbinsX(); ++i) {
	
       float erry1 = h1 -> GetBinError(i);
       float erry2 = h2 -> GetBinError(i);
       float ratio = 0.;
       float ratioerr = 0.; // ratio*sqrt();
       if (erry2 > 0.) {
	 ratio = erry1/erry2;
       }
       div -> SetBinContent(i, ratio);
       div -> SetBinError(i, ratioerr);
      }
      div -> Scale(1.);
      return div;
    }
    return 0;
  }
  
  /*
  // ________________________________________________________________________
  
  int DivideByBinWidth(TH1F* &h)
  {
  if (h) {

  TH1F *h1 = (TH1F*) h -> Clone(Form("divided_%s", h -> GetName()));
  h1 -> Sumw2();

  cout << "--HistoTools::DivideByBinWidth for " << h1 -> GetName() << endl;
  for (int k = 0; k <= h1->GetNbinsX() + 1 ; ++k) {
  cout << "content: " << h1->GetBinContent(k)
  << " width: " << h1->GetBinWidth(k)
  << " new content: " << (h1->GetBinContent(k)) / (h1->GetBinWidth(k))
  << endl;
  //	if (h1->GetBinContent(k) > 0.) {
  h1 -> SetBinContent(k, (h1->GetBinContent(k)) / (h1->GetBinWidth(k)) );
  h1 -> SetBinError(k, (h1->GetBinError(k)) / (h1->GetBinWidth(k)) );
  //	}
  }
  h -> Scale(2.);
  h -> Scale(1./2.);
  h = h1;
  return 1;
  }
  return 0;
  }
  
  */

  /*

  // ________________________________________________________________________
  
  int DivideByBinWidth(TH1 *h1, int debug = 0)
  {
  if (h1) {
  float max = h1 -> GetMaximum();
  float newmax = -999;
  if (debug)
  cout << "--- HistoTools::DivideByBinWidth for " << h1 -> GetName() << endl;
  for (int k = 0; k <= h1->GetNbinsX() + 1 ; ++k) {
  float newcont = (h1->GetBinContent(k)) / (h1->GetBinWidth(k));
  if (newcont > newmax)
  newmax = newcont;
  if (debug)
  cout << "content: " << h1->GetBinContent(k)
  << " width: " << h1->GetBinWidth(k)
  << " new content: " << newcont
  << endl;
  //	if (h1->GetBinContent(k) > 0.) {
  h1 -> SetBinContent(k, newcont);
  h1 -> SetBinError(k, (h1->GetBinError(k)) / (h1->GetBinWidth(k)) );
  //	}
  }
  //      if (newmax > 0.) {
  // just a dummy scale to recompute fMaximum:
  h1 -> Scale(2.);
  h1 -> Scale(1./2.);
  //      }
  return 1;
  }
  return 0;
  }
  */

  // short version:

  // ________________________________________________________________________
  
  int DivideByBinWidth(TH1 *h1, int debug)
  {
    if (h1) {
      if (debug)
	cout << "--- HistoTools::DivideByBinWidth for " << h1 -> GetName() << endl;
      for (int k = 0; k <= h1->GetNbinsX() + 1 ; ++k) {
	float newcont = (h1->GetBinContent(k)) / (h1->GetBinWidth(k));
	if (debug)
	  cout << "content: " << h1->GetBinContent(k)
	       << " width: " << h1->GetBinWidth(k)
	       << " new content: " << newcont
	       << endl;
	h1 -> SetBinContent(k, newcont);
	h1 -> SetBinError(k, (h1->GetBinError(k)) / (h1->GetBinWidth(k)) );
      }
      // just a dummy scale to recompute fMaximum:
      h1 -> Scale(1.);
      //      }
      return 1;
    }
    return 0;
  }

  // ________________________________________________________________________
  
  int MultiplyByBinWidth(TH1 *h1, int debug)
  {
    if (h1) {
      if (debug)
	cout << "--- HistoTools::MultiplyByBinWidth for " << h1 -> GetName() << endl;
      for (int k = 0; k <= h1->GetNbinsX() + 1 ; ++k) {
	float newcont = (h1->GetBinContent(k)) * (h1->GetBinWidth(k));
	if (debug)
	  cout << "content: " << h1->GetBinContent(k)
	       << " width: " << h1->GetBinWidth(k)
	       << " new content: " << newcont
	       << endl;
	h1 -> SetBinContent(k, newcont);
	h1 -> SetBinError(k, (h1->GetBinError(k)) * (h1->GetBinWidth(k)) );
      }
      // just a dummy scale to recompute fMaximum:
      h1 -> Scale(1.);
      //      }
      return 1;
    }
    return 0;
  }

  // ________________________________________________________________________
  
  int DivideByBinCenter(TH1 *h1, int debug)
  {
    if (h1) {
      if (debug)
	cout << "--- HistoTools::DivideByBinCenter for " << h1 -> GetName() << endl;
      for (int k = 0; k <= h1->GetNbinsX() + 1 ; ++k) {
	float newcont = (h1->GetBinContent(k)) / (h1->GetBinCenter(k));
	if (debug)
	  cout << "content: " << h1->GetBinContent(k)
	       << " center: " << h1->GetBinCenter(k)
	       << " new content: " << newcont
	       << endl;
	h1 -> SetBinContent(k, newcont);
	h1 -> SetBinError(k, (h1->GetBinError(k)) / (h1->GetBinCenter(k)) );
      }
      // just a dummy scale to recompute fMaximum:
      h1 -> Scale(1.);
      //      }
      return 1;
    }
    return 0;
  }

  // ________________________________________________________________________
  
  TGraphErrors* DivideGraphByBinCenter(TGraphErrors *g1, int debug)
  {
    if (g1) {
      if (debug)
	cout << "--- HistoTools::DivideGraphByBinCenter for graph " << g1 -> GetName() << endl;
      TGraphErrors *g2 = new TGraphErrors();
      g2 -> SetName(Form("rel_%s", g1 -> GetName()));
      double x, y, ex, ey;
      int grp = 0;
      for (int k = 0; k <= g1->GetN() ; ++k) {
	g1 -> GetPoint(k, x, y);
	if ( fabs(x) > 1.e-7) {
	  g2 -> SetPoint(grp, x, y/x);
	  ex = g1 -> GetErrorX(k);
	  ey = g1 ->  GetErrorY(k);
	  if (ey > 1.e-7)
	    g2 -> SetPointError(grp, sqrt( pow(ex/x, 2) + pow(ey/y, 2) ));
	  else
	    g2 -> SetPointError(grp, ex/x);
	  grp++;
	}
      }
      return g2;
    }
    return 0;
  }

  // ________________________________________________________________________
  
  int MultiplyByBinCenter(TH1 *h1, int debug)
  {
    if (h1) {
      if (debug)
	cout << "--- HistoTools::MultiplyByBinCenter for " << h1 -> GetName() << endl;
      for (int k = 0; k <= h1->GetNbinsX() + 1 ; ++k) {
	float newcont = (h1->GetBinContent(k)) * (h1->GetBinCenter(k));
	if (debug)
	  cout << "content: " << h1->GetBinContent(k)
	       << " center: " << h1->GetBinCenter(k)
	       << " new content: " << newcont
	       << endl;
	h1 -> SetBinContent(k, newcont);
	h1 -> SetBinError(k, (h1->GetBinError(k)) * (h1->GetBinCenter(k)) );
      }
      // just a dummy scale to recompute fMaximum:
      h1 -> Scale(1.);
      //      }
      return 1;
    }
    return 0;
  }

 // ________________________________________________________________________

  int PrintIntegrals(TH1* h1)
  {
    if (h1) {
      cout << "HistoTools::PrintIntegrals: Printing integrals of " << h1 -> GetName() << endl;
      const int nint = 4;
      double integral[nint];
      integral[0] = h1-> Integral(1, h1->GetNbinsX(), "");
      integral[1] = h1-> Integral(1, h1->GetNbinsX(), "width");
      integral[2] = h1-> Integral(0, h1->GetNbinsX()+1, "");
      integral[3] = h1-> Integral(0, h1->GetNbinsX()+1, "width");
      for (int i = 0; i < nint; ++i)
	cout << "Integral " << i << ": " << integral[i] << endl;
    }
    
  }

 // ________________________________________________________________________

  int PrintDivideIntegrals(TH1* h1, TH1* h2)
  {
    if (h1 && h2) {
      cout << "HistoTools::PrintDivideIntegrals: Printing integrals ratios of " 
	   << h1 -> GetName() << " " 
	   << h2 -> GetName() << " " 
	   <<  endl;
      const int nint = 4;
      const int nhist = 2;
      double integral[nhist][nint];
      TH1* hist[nhist] = {h1, h2};
      for (int j = 0; j < nhist; ++j) {
	integral[j][0] = hist[j]-> Integral(1, hist[j]->GetNbinsX(), "");
	integral[j][1] = hist[j]-> Integral(1, hist[j]->GetNbinsX(), "width");
	integral[j][2] = hist[j]-> Integral(0, hist[j]->GetNbinsX()+1, "");
	integral[j][3] = hist[j]-> Integral(0, hist[j]->GetNbinsX()+1, "width");
      }
      for (int i = 0; i < nint; ++i) {
	cout << "Integrals ratio " << i << ": ";
	if (integral[1][i] > 0.)
	  cout << integral[0][i]/integral[1][i] << endl;
	else 
	  cout << " NAN" << endl;
      }
    }
    
  }
  

 // ________________________________________________________________________

  int NormaliseToUnity(TH1* h1, bool UseWidth, bool UseOverflows)
  {
    if (h1) {

      TString opt = "";
      if (UseWidth)
	opt = "width";
      int n0 = 1;
      int n1 = h1 -> GetNbinsX();
      if (UseOverflows) {
	n0--;
	n1++;
      }
      
      double integral = h1-> Integral(n0, n1, opt.Data());
      if (integral > 0.)
	h1 -> Scale(1./integral);
      return 1;
    }
    return 0;
  }

  // ___________________________________________________________

  void SetHistoStyle(TH1F *h, int col, int width, int mark, float size, int rebin, 
		     bool _DivideByBinWidth)
  {
    if (h) {
      h -> SetLineColor(col);
      h -> SetLineWidth(width);
      h -> SetMarkerColor(col);
      h -> SetMarkerStyle(mark);
      h -> SetMarkerSize(size);
      if (rebin > 1)
	h -> Rebin(rebin);
      h -> SetStats(0);
    
      if (_DivideByBinWidth) 
	DivideByBinWidth(h, 0);
    }

  }

  // ___________________________________________________________

  void SetHistoStyle(TH1F *h, int lcol, int lwidth, int lstyle, int mark, int mcol, float msize)
  {
    if (h) {
      h -> SetLineColor(lcol);
      h -> SetLineWidth(lwidth);
      h -> SetLineStyle(lstyle);
      h -> SetMarkerColor(mcol);
      h -> SetMarkerStyle(mark);
      h -> SetMarkerSize(msize);
    }
  }
 // ___________________________________________________________
  void SetGraphStyle(TGraph *h, int lcol, int lwidth, int lstyle, int mark, int mcol, float msize)
  {
    if (h) {
      h -> SetLineColor(lcol);
      h -> SetLineWidth(lwidth);
      h -> SetLineStyle(lstyle);
      h -> SetMarkerColor(mcol);
      h -> SetMarkerStyle(mark);
      h -> SetMarkerSize(msize);
    }
  }
  // ___________________________________________________________

  void CopyGraphStyle(TGraphErrors *h1, TGraphErrors *h2)
  {
    if (h1 && h2) {
      h2 -> SetLineColor(h1 -> GetLineColor());
      h2 -> SetLineStyle(h1 -> GetLineStyle());
      h2 -> SetLineWidth(h1 -> GetLineWidth());
      h2 -> SetMarkerColor(h1 -> GetMarkerColor());
      h2 -> SetMarkerStyle(h1 -> GetMarkerStyle());
      h2 -> SetMarkerSize(h1 -> GetMarkerSize());
    }

  }


 

  // ___________________________________________________________

  void CopyHistoStyle(TH1 *h1, TH1 *h2)
  {
    if (h1 && h2) {
      h2 -> SetLineColor(h1 -> GetLineColor());
      h2 -> SetLineStyle(h1 -> GetLineStyle());
      h2 -> SetLineWidth(h1 -> GetLineWidth());
      h2 -> SetMarkerColor(h1 -> GetMarkerColor());
      h2 -> SetMarkerStyle(h1 -> GetMarkerStyle());
      h2 -> SetMarkerSize(h1 -> GetMarkerSize());
      if (h1 -> GetFillStyle() > 0) {
	h2 -> SetFillStyle(h1 -> GetFillStyle());
	h2 -> SetFillColor(h1 -> GetFillColor());
      }
    }

  }

  void CopyHistoStyle(TH1 *h1, TGraph *h2)
  {
    if (h1 && h2) {
      h2 -> SetLineColor(h1 -> GetLineColor());
      h2 -> SetLineStyle(h1 -> GetLineStyle());
      h2 -> SetLineWidth(h1 -> GetLineWidth());
      h2 -> SetMarkerColor(h1 -> GetMarkerColor());
      h2 -> SetMarkerStyle(h1 -> GetMarkerStyle());
      h2 -> SetMarkerSize(h1 -> GetMarkerSize());
    }

  }


  void CopyHistoStyle(TGraph *h1, TH1 *h2)
  {
    if (h1 && h2) {
      h2 -> SetLineColor(h1 -> GetLineColor());
      h2 -> SetLineStyle(h1 -> GetLineStyle());
      h2 -> SetLineWidth(h1 -> GetLineWidth());
      h2 -> SetMarkerColor(h1 -> GetMarkerColor());
      h2 -> SetMarkerStyle(h1 -> GetMarkerStyle());
      h2 -> SetMarkerSize(h1 -> GetMarkerSize());
    }

  }


  // ________________________________________________________________________

  int PrintBinContent(TH1* h1)
  {
    if (h1) {
      cout << "HistoTools::Printing the bin content of " << h1 -> GetName() << endl;
      for (int k = 0; k <= h1->GetNbinsX() + 1 ; ++k) {
	cout << k << ". bin: " 
	     << " x=" << h1 -> GetBinCenter(k)
	     << " y=" << h1 -> GetBinContent(k)
	     << " err=" << h1->GetBinError(k)
	     << endl;
      }
      return 1;
    }
    return 0;
  }

 // ________________________________________________________________________

  int PrintBinContentTeXSimple(TH1* h1, TString outfilename, bool vertical, int precision)
  {
   

    if (!h1)
      return 1;
    int nBins = h1 -> GetNbinsX();

    std::ofstream outfile(outfilename.Data());
    //     outfile << endl << "%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
    for (int i = 1; i <= nBins; ++i) {
      outfile.width(10);
      outfile.precision(precision);
      outfile << h1 -> GetBinContent(i);
      if (vertical)
	outfile << endl;
      else {
	if (i < nBins)
	  outfile << " & ";
	else 
	  outfile << " \\\\" << endl;
      }
    }
    outfile.close();
    return 0;
  }


 // ________________________________________________________________________

  int PrintBinContentTeXSimple2D(TH2* h2, TString outfilename, int precision)
  {
   

    if (!h2)
      return 1;
    int nBinsX = h2 -> GetNbinsX();
    int nBinsY = h2 -> GetNbinsY();

    std::ofstream outfile(outfilename.Data());
    //     outfile << endl << "%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;

    for (int j = nBinsY; j > 0; --j) {
      for (int i = 1; i <= nBinsX; ++i) {
	outfile.width(10);
	outfile.precision(precision);
	outfile << h2 -> GetBinContent(i, j);
	if (i < nBinsX)
	  outfile << " & ";
	else 
	  outfile << " \\\\" << endl;
      } // j
      //      outfile << " " << endl;
    } // i
  
    outfile.close();
    return 0;
  }

  // ________________________________________________________________________

  int PrintBinContentTeX(int nHistos, TH1** h1, TString *Tags, bool *PrintErrorInsteadOfBinContent, TString outfilename, TString caption, TString label, 
			 int PrintError, bool PrintSum, bool UseWidth, bool UseOverflows, bool SkipEmptyBins, 
			 int precision, int error_precision, double SubtractVal,
			 TH1F *ScaleHisto, TH1F *CentralHisto,
			 bool Symmetrise)

  // jk 20.4.2009
  // Scale histo is used to scale the relative histo content to the absolute one (e.g. when printing errors)
  // Central histo is used to print the relative error

  {


    
    // count bins and check for consistency
    int nBins = -1;
    for (int i = 0; i < nHistos; ++i) {
      if (!h1[i]) {
	cerr << "ERROR: HistoTools::PrintBinContentTeX: histo #" << i << " is a null pointer!" << endl;
	continue;
      }
      int nbins = h1[i] -> GetNbinsX();
      if (nBins < 0)
	nBins = nbins;
      else {
	if (nBins != nbins) {
	  cerr << "ERROR: HistoTools::PrintBinContentTeX: Inconsistent binning!" << nBins << " != " << nbins << endl;
	  nBins = TMath::Min(nBins, nbins);
	}
      }
    } // histos

    int nhistos = 0;
    bool* IsTotallyZero = new bool[nBins];
    double *BinnedSum = new double[nBins];
    double *BinnedStat = new double[nBins];
    for (int ibin = 1; ibin <= nBins; ++ibin) {
      IsTotallyZero[ibin-1] = true;
      BinnedSum[ibin-1] = 0.;
      BinnedStat[ibin-1] = 0.;
    }
    for (int ibin = 1; ibin <= nBins; ++ibin) {
      for (int i = 0; i < nHistos; ++i) {
	IsTotallyZero[ibin-1] = IsTotallyZero[ibin-1] && (h1[i] -> GetBinContent(ibin) < 1.e-9);
      }
    }
    for (int ibin = 1; ibin <= nBins; ++ibin) {
      cout << "IsTotallyZero[" << ibin-1 << "]: " << IsTotallyZero[ibin-1] << endl;
    }

    // prepare the output
    //    std::ofstream outfile(outfilename.Data(), ios::out);
    std::ofstream outfile(outfilename.Data());
    outfile << endl << "%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
    outfile << "\\begin{table}[h]" << endl;
    outfile << "\\begin{tabular}{|l|";
    for (int k = 0; k < nBins; ++k) {
      if (SkipEmptyBins && IsTotallyZero[k])
	continue;
      outfile << "r";
    }
    if (PrintSum)
      outfile << "r";
    outfile << "|} \\hline " << endl;
    //    outfile << "" << endl;

    double GrandSum = 0.; // for syst.
    double Stat = 0.;
    //    double StatPlusSyst = 0.;

    // main loop over histos
    for (int i = 0; i < nHistos; ++i) {
      if (!h1[i]) {
	continue;
      }
      bool PrintOut = true;
      if (Symmetrise && Tags[i].Contains("-")) {
	cout << "Skipping negative syst as asked to symmetrise..." << endl;
	PrintOut = false;
      }
 
      bool AddToTotal = Tags[i].Contains("+") || Tags[i].Contains("Weight") || Tags[i].Contains("Reweight");

      // print bin edges
      if (nhistos == 0) {
	//	outfile.width(20);
	outfile << "Bins [GeV]";
	outfile << " & ";
	for (int ibin = 1; ibin <= nBins; ++ibin) {

	  if (SkipEmptyBins && IsTotallyZero[ibin-1])
	    continue;
	  outfile.width(10);
	  outfile << h1[i] -> GetXaxis() -> GetBinLowEdge(ibin) << "--" 
		  << h1[i] -> GetXaxis() -> GetBinUpEdge(ibin) << " ";
	  if (ibin == nBins && !PrintSum)
	    outfile << " \\\\ \\hline" << endl;
	  else
	    outfile << " & ";
	}
	if (PrintSum) {
	  outfile << " $\\sigma_{\\rm tot}$\\\\ \\hline " << endl;
	} 
      }

      TString opt = "";
      if (UseWidth)
	opt = "width";
      
      // loop through bins and print contents
      double Sum = 0.;
      double SubtractSum = 0.;
      double SumWeights = 0.;
      double SumWidths = 0.;

      // for syst errors
      //      if (PrintOut)
      //	outfile << "\\hline" << endl;
      outfile.width(20);
      TString tagname = Tags[i];
      if (Symmetrise) {
	tagname.ReplaceAll("+", "");
	tagname.ReplaceAll("-", "");
      }
      if (PrintOut)
	outfile << tagname.Data() << " & ";

      int n0 = 1;
      int n1 = h1[i] -> GetNbinsX();

      for (int ibin = 1; ibin <= nBins; ++ibin) {

	if (SkipEmptyBins && IsTotallyZero[ibin-1]) {
	  //	  if (ibin == nBins && !PrintSum)
	  //	    outfile << " \\\\ " << endl;
	  continue;
	}

	double weight = 1.;
	double BinWidth = h1[i] -> GetBinWidth(ibin);
	double BinContent = h1[i] -> GetBinContent(ibin);

	if (CentralHisto)
	  weight = CentralHisto -> GetBinContent(ibin);
	SumWeights += weight;
	SumWidths += BinWidth;

	outfile.width(10);
	outfile.precision(precision);
	if (PrintErrorInsteadOfBinContent[i]) {
	  double valerr = h1[i] -> GetBinError(ibin);
	  if (ScaleHisto)
	    valerr *= ScaleHisto -> GetBinContent(ibin);
	  // ok, we're asking to print relative error:
	  if (CentralHisto) {
	    if (CentralHisto -> GetBinContent(ibin) > 0.)
	      valerr /= CentralHisto -> GetBinContent(ibin);
	    valerr *= 100.;
	  }
	  if (PrintOut)
	    outfile << valerr << " ";
	  if (CentralHisto) {
	    if (PrintOut)
	      outfile << "\\% ";
	  }
	  if (Tags[i].Contains("Stat")) {
	    BinnedStat[ibin-1] += valerr*valerr;
	    SubtractSum += valerr*valerr;
	  }
	  else
	    SubtractSum += valerr;
	  //	  if (UseWidth)
	  //	    Sum += valerr * BinWidth;
	  //	  else
	  if (CentralHisto)
	    Sum += valerr * weight;
	  else
	    Sum += valerr;
	} // print errors instead of bin content
	else {
	  double val = BinContent - SubtractVal;
	  if (ScaleHisto)
	    val *= ScaleHisto -> GetBinContent(ibin);
	  // ok, we're asking to print relative error:
	  if (CentralHisto) {
	    if (CentralHisto -> GetBinContent(ibin) > 0.)
	      val /= CentralHisto -> GetBinContent(ibin);
	    val *= 100;
	  }
	  if (PrintOut)
	    outfile << val << " ";
	  if (CentralHisto) {
	    if (PrintOut)
	      outfile << "\\% ";
	    SubtractSum += SubtractVal*100; // * h1[i] -> GetBinWidth(ibin);
	  } else
	    SubtractSum += SubtractVal; 
	  //	  if (UseWidth)
	  //	    Sum += val * BinWidth;
	  //	  else 
	  if (AddToTotal)
	    BinnedSum[ibin-1] += pow(val, 2);
	  if (CentralHisto) {
	    Sum += val * weight;
	  } else {
	    Sum += val;
	  }
	  

	}
	if (ibin == nBins && !PrintSum) {
	  if (PrintOut) {
	    outfile << " \\\\ ";
	    if (Tags[i].Contains("Stat"))
	      outfile << "\\hline";
	    outfile  << endl;
	  }
	} else
	  if (PrintOut)
	    outfile << " & ";
	


      } // bins


      if (PrintSum) {
	if (UseOverflows) {
	  n0 = 0;
	  n1++;
	}
	if (PrintErrorInsteadOfBinContent[i] && Tags[i].Contains("Stat")) {
	  if (Tags[i].Contains("Stat") && SubtractSum > 0.) {
	    SubtractSum = sqrt(SubtractSum);
	    Stat = SubtractSum;
	  }
	  if (PrintOut)
	    outfile << SubtractSum;
	  if (AddToTotal) {
	    GrandSum += pow(SubtractSum, 2);
	  }
	} else {
	  /*
	    double val = h1[i] -> Integral(n0, n1, opt.Data());
	    if (CentralHisto)
	    val *= 100;
	    val -= SubtractSum;	  
	    //	  outfile << val;
	    */
	  double val = Sum;
	  //	  if (UseWidth && SumWidths > 0.)
	  //	    val /= SumWidths;
	  //	  else 
	  if (UseWidth)
	    val = h1[i] -> Integral(n0, n1, opt.Data());

	  if (CentralHisto && SumWeights > 0.)
	    val /= SumWeights;
	  if (PrintOut)
	    outfile << val;
	  if (AddToTotal) {
	    GrandSum += pow(val, 2);
	  }
	}
	if (PrintOut) {
	  if (CentralHisto)
	    outfile << " \\%";
	  outfile << " \\\\ ";
	  if (Tags[i].Contains("Stat"))
	    outfile << "\\hline";
	  outfile << endl;
	}
      } 

      if ( (i == PrintError && h1[PrintError]) ) {
	outfile.width(20);
	outfile << "Error";
	outfile << " & ";
	for (int ibin = 1; ibin <= nBins; ++ibin) {
	  if (SkipEmptyBins && IsTotallyZero[ibin-1])
	    continue;
	  outfile.width(10);
	  outfile.precision(error_precision);
	  outfile << h1[i] -> GetBinError(ibin) << " ";
	  if (ibin == nBins && !PrintSum)
	    outfile << " \\\\ " << endl;
	  else
	    outfile << " & ";
	} // bins
	if (PrintSum) {
	  int n0 = 1;
	  int n1 = h1[i] -> GetNbinsX();
	  if (UseOverflows) {
	    n0 = 0;
	    n1++;
	  }
	  double errsum = 0;
	  for (int ib = 1; ib <= h1[i] -> GetNbinsX(); ++ib) {
	    // this would be wrong, as it would assume all errors uncorrelated
	    //  errsum +=  pow(h1[i] -> GetBinError(ib) *  h1[i] -> GetBinWidth(ib), 2);
	    // this is conservative
	    // better, stat errors should be added and quadrature and syst just added (fully correlated)
	    // best, flat (coherent) and shape-only errors should be treated separately:
	    if (Tags[i].Contains("Stat"))
	      errsum +=  pow(h1[i] -> GetBinError(ib) *  h1[i] -> GetBinWidth(ib), 2);
	    else
	      errsum +=  h1[i] -> GetBinError(ib) *  h1[i] -> GetBinWidth(ib);
	  }
	  if (Tags[i].Contains("Stat"))
	    errsum = sqrt(errsum);
	  outfile << errsum;
	  outfile << " \\\\ " << endl;
	}
      } // i == printerror
      
      nhistos++;
    } //histos
    
    // print the grand sum of all total errors:
    if (CentralHisto || ScaleHisto) {
      if (GrandSum > 0.)
	GrandSum = sqrt(GrandSum);
      //      outfile << " " << endl;
      outfile << " \\hline" << endl;
      //      outfile.width(10);
      outfile << " Conservative Total Syst        & ";
      for (int ibin = 1; ibin <= nBins; ++ibin) {
	outfile.width(10);
	double binsyst = BinnedSum[ibin-1];
	if (binsyst > 0.)
	  binsyst = sqrt(binsyst);
	outfile << binsyst;
	if (CentralHisto)
	  outfile << " \\% & ";
	else
	  outfile << "  & ";
      }
      outfile << GrandSum;
      if (CentralHisto)
	outfile << " \\% \\\\" << endl;
      else
	outfile << "  \\\\" << endl;

      //      outfile.width(10);
      outfile << " Conservative Syst$\\oplus$Stat & ";
      for (int ibin = 1; ibin <= nBins; ++ibin) {
	outfile.width(10);
	double statsyst = BinnedSum[ibin-1] + BinnedStat[ibin-1];
	if (statsyst > 0.)
	  statsyst = sqrt(statsyst);
	outfile << statsyst;
	if (CentralHisto)
	  outfile << " \\% & ";
	else
	  outfile << "  & ";
      }
      outfile << sqrt(Stat*Stat + GrandSum*GrandSum);
      if (CentralHisto)
	outfile << " \\% \\\\" << endl;
      else
	outfile << "  \\\\" << endl;

    }
    cout << "deleting IsTotallyZero..." << endl;
    delete [] IsTotallyZero;
    cout << "deleting BinnedSum..." << endl;
    delete [] BinnedSum;

    outfile << "  \\hline" << endl;
    outfile << "\\end{tabular}" << endl;
    outfile << "\\caption{" << caption.Data() << "}" << endl;
    outfile << "\\label{" << label.Data() << "}" << endl;
    outfile << "\\end{table}" << endl  
	    << "%%%%%%%%%%%%%%%%%%%%%%%%%%%" 
	    << endl << endl;

    outfile.close();
    
    return 0;
  }

  // ___________________________________
  void SetErrorBarsRelative(TH1F *from, TH1F* to)
  {
    // method to apply error bars from one histogram to another
    // by scaling them by the ratio of the bin contents
    if (from && to) {
      // check binning
      if (from -> GetNbinsX() != to -> GetNbinsX() ) {
	cerr << "ERROR: HistoTools::SetErrorBarsRelative: histograms have different number of bins!" << endl;
	return;
      }
      
      double cfrom, cto, errfrom, errto;
      for (int i = 1; i <= from -> GetNbinsX(); ++i) {
	cfrom = from -> GetBinContent(i);
	cto = to -> GetBinContent(i);
	errfrom = from -> GetBinError(i);
	// keep the old error in case we cannot recompute the new one
	errto = to -> GetBinError(i);
	if (cto > 0. && cfrom > 0.) {
	    errto = errfrom * cto / cfrom;
	}
	to -> SetBinError(i, errto);

      } // bins
      to -> Scale(1.);
    } // both exist
  }
  // ___________________________________
  void AddErrorBarsRelative(TH1F *from, double CentralConstant, TH1F* to, TH1F *scale)
  {
    // method to apply error bars from histogram 'from' 
    // (where the error is expected to be coded in the bin content, not bin error!!)
    // to another histogram 'to'
    // by scaling them by the ratio of the bin contents of the scale histo
    // if scale histo is provided, the error is taken from the 'from' histo
    // but it is understood it is an error relative to 'scale',
    // therefore the error is scaled by to/scale bin contents.

    if (from && to) {
      // check binning
      if (from -> GetNbinsX() != to -> GetNbinsX() ) {
	cerr << "ERROR: HistoTools::SetErrorBarsRelative: 'from' and 'to' histograms have different number of bins!" << endl;
	return;
      }
      
      if (scale) {
	if (from -> GetNbinsX() != scale -> GetNbinsX() ) {
	  cerr << "ERROR: HistoTools::SetErrorBarsRelative: 'from' and 'scale' histograms have different number of bins!" << endl;
	  return;
	}
      }

      double cfrom, cto, errfrom, errto;
      for (int i = 1; i <= from -> GetNbinsX(); ++i) {
	cfrom = from -> GetBinContent(i);
	cto = to -> GetBinContent(i);
	// expected relative error:
	errfrom = TMath::Abs(from -> GetBinContent(i) - CentralConstant);

	// keep the old error in case we cannot recompute the new one
	errto = to -> GetBinError(i);
	double cscale = -999;
	if (scale)
	  cscale = scale -> GetBinContent(i);
	  
	cout << " cfrom=" << cfrom
	     << " errfrom=" << errfrom
	     << " cto=" << cto
	     << " errto=" << errto
	     << " cscale=" << cscale
	     << endl;

	if (scale) {
	  if (cscale > 0.)
	    errto = sqrt( errto*errto + pow(errfrom/cscale*cto, 2.) );
	} else {
	  errfrom =  from -> GetBinError(i);
	  if (cto > 0.) {
	    if (cfrom > 0.) 
	      errto = sqrt( errto*errto + pow(errfrom*cto/cfrom, 2.) );
	    else 
	      errto = sqrt( errto*errto + pow(errfrom*cto, 2.) );
	  }
	}
	
	to -> SetBinError(i, errto);

      } // bins
      // safety feature
      to -> Scale(1.);

    } // both exist
  }

  // ___________________________________
  void ScaleErrorBars(TH1F* to, double errorSF)
  {
    if (to) {
      double cfrom, cto, errfrom, errto;
      for (int i = 1; i <= to -> GetNbinsX(); ++i) {
	cto = to -> GetBinContent(i);
	errto = to -> GetBinError(i);
	if (errorSF > 0.)
	  errto *= errorSF;
	to -> SetBinError(i, errto);
      } // bins
    } // exist
  }

  // ___________________________________

  TH1F *MakeFitResidualsHisto(TH1F* h1, TF1 *fit, std::string tag, bool _relative,
			      float xmin, float xmax)
  {
    // perform h1/h2:
    if (h1 && fit) {
      cout << "Making residuals histo " << (tag + std::string(h1 -> GetName()) + std::string(fit -> GetName())).c_str() << endl;
      
      TH1F *res = (TH1F*) h1 -> Clone((tag + std::string(h1 -> GetName()) + std::string(fit -> GetName())).c_str()); 
      res -> Reset();
      res -> SetTitle(Form("%s Residuals", h1 -> GetTitle()));
      
      for (int k = 1; k < h1->GetNbinsX() + 1 ; ++k) {
	
	if (xmin < xmax)
	  if (h1->GetBinCenter(k) < xmin || h1->GetBinCenter(k) > xmax )
	    continue;

	double fity = fit -> Eval(h1->GetBinCenter(k));
	if (_relative) {
	  res -> SetBinContent(k, (h1->GetBinContent(k) - fity) / fity );
	  res -> SetBinError(k, (h1->GetBinError(k)) / fity );

	} else
	  res -> SetBinContent(k, h1->GetBinContent(k) - fity);
	res -> SetBinError(k, (h1->GetBinError(k))  );
	  
      }
      
      return res;
    }
    return 0;
  }
  

  // ___________________________________

  TH1F *MakeFitResidualsProjection(TH1F* h1, TF1 *fit, std::string tag , bool _relative,
				   float &x1, float &x2, int Nbins, bool weightBySigma,
				   float xmin, float xmax)
  {
    // perform h1/h2:
    if (h1 && fit) {
      cout << "Making residuals histo " << (tag + std::string(h1 -> GetName()) + std::string(fit -> GetName())).c_str() << endl;
      

      float *residuum = new float[ h1->GetNbinsX() + 1];
      if (x1 > x2) {
	// let's find the range ourselves
	x1 = 9999;
	x2 = -9999;
      }
      for (int k = 1; k < h1->GetNbinsX() + 1 ; ++k) {

	if (xmin < xmax)
	  if (h1->GetBinCenter(k) < xmin || h1->GetBinCenter(k) > xmax )
	    continue;
      
	double fity = fit -> Eval(h1->GetBinCenter(k));
	double biny = h1->GetBinContent(k);

	if (_relative) {
	  residuum[k] = (biny - fity) / fity;
	} else
	  residuum[k] = biny - fity;
      
	if (x1 > residuum[k])
	  x1 = residuum[k];
	if (x2 < residuum[k])
	  x2 = residuum[k];

      } // bins
    
      if (x1 < 0)
	x1 *= 1.1;
      else
	x1 *= 0.9;

      if (x2 > 0)
	x2 *= 1.1;
      else
	x2 *= 0.9;

      TH1F *res =  new TH1F((tag + std::string(h1 -> GetName()) + std::string(fit -> GetName())).c_str(),
			    Form("%s Residuals", h1 -> GetTitle()),
			    Nbins, x1, x2);
      res -> Sumw2();
      CopyHistoStyle(h1, res);

      for (int k = 1; k < h1->GetNbinsX() + 1 ; ++k) {

	if (xmin < xmax)
	  if (h1->GetBinCenter(k) < xmin || h1->GetBinCenter(k) > xmax )
	    continue;
      
	double biney = h1->GetBinError(k);
	double weight = 1.;

	if (weightBySigma && biney > 0.)
	  weight = 1. / biney;
	if (_relative) {
	  res -> Fill(residuum[k], weight);
	} else
	  res -> Fill(residuum[k], weight);
      } // bins
    
      delete [] residuum;
    
      return res;
    }
    return 0;
  }

  // ___________________________________________________________

  TH2F *MergeEnsembleHistos(int Nesb, TH1F **hist, int nbinsy, std::string name, float maxmaxy, int ibin0)
  {

    // first find y axis range:
    float miny = 99999;
    float maxy = -99999;

    for (int iesb = 0; iesb < Nesb; ++iesb) {
      TH1F *h = hist[iesb];
      if (h) {
	for (int ibin = ibin0; ibin <= h -> GetNbinsX(); ++ibin) {
	  float content = h -> GetBinContent(ibin);
	  if (content > maxy)
	    maxy = content;
	  if (content < miny)
	    miny = content;
	}
      } // histo exists
    } // loop over ensemble histos
    
    float off = 0.1*(maxy - miny);

    if (maxy > maxmaxy)
      maxy = maxmaxy;
    else {
      miny -= off;
      maxy += off;
    }
  

    int nbinsx = -1;
    double *binsx = 0;

    int k = 0;
    while (nbinsx < 0) {
      if (hist[k]) {
	nbinsx = hist[k] -> GetNbinsX();
	const TArrayD *array =  hist[k] -> GetXaxis() -> GetXbins();
	binsx = array -> fArray;
      }
      ++k;
    }

    /*
      cout << "nbinsx: " << nbinsx << endl;
      for (int i = 0; i < nbinsx; ++i)
        cout << binsx[i] << " ";
      cout << endl;
    */

    // fill the merged 2D histo:
    TH2F *h2 = new TH2F(name.c_str(), name.c_str(), 
			nbinsx, binsx,
			nbinsy, miny, maxy);
    h2 -> Sumw2();
    for (int iesb = 0; iesb < Nesb; ++iesb) {
      TH1F *h = hist[iesb];
      if (h) {
	for (int ibin = 1; ibin <= h -> GetNbinsX(); ++ibin) {
	  float content = h -> GetBinContent(ibin);
	  h2 -> Fill(h -> GetBinCenter(ibin), content);
	} // bins
      } // if h
    } // loop over ensembles

    return h2;

  }

  // ___________________________________________________________

  bool CheckFileOpen(TFile *f) 
  {
    if (f) {
      if (f -> IsOpen())
	return true;
      else 
	cout << "File " << f -> GetName() << " not open!" << endl;
    } else {
      cout << "CheckFileOpen: Got null pointer!" << endl;
    }
    return false;
  }

  // ________________________________________________________________________
  // ________________________________________________________________________
 
  Double_t GetNeff(TH1D* h1)
  {
  
    if (!h1)
      return 0.;
  
    if ( h1 -> GetSumw2() < 0 )
      return h1 -> GetEntries();
    else 
      if ( h1 -> GetSumw2() -> GetSum() < 0 )
	return h1 -> GetEntries();
      else {
	if (h1 -> GetSumw2()->GetSum() > 0.)
	  return ( h1 -> GetSum() * h1 -> GetSum() / h1 -> GetSumw2()->GetSum() );
      }
  
    return h1 -> GetEntries();
  
  }
  
  // _______________________________________________________________________________

  Double_t GetMCError(TH1D* h1, Float_t *N_eff)
  {

    if (!h1)
      return 0.;
  
    if ( h1 -> GetSumw2() == 0 )
      return 0;
    else 
      if ( h1 -> GetSumw2() -> GetSum() == 0 )
	return 0;
      else {
	(*N_eff) = h1 -> GetSum() * h1 -> GetSum() / h1 -> GetSumw2() -> GetSum();
	if ((*N_eff) > 0.)
	  return h1 -> GetRMS() / sqrt((*N_eff));
	else 
	  return 0.;
      }
  
  }
 // _______________________________________________________________________________

  Float_t GetNeff(TH1F* h1)
  {
  
    if (!h1)
      return 0.;
  
    if ( h1 -> GetSumw2() == 0 )
      return h1 -> GetEntries();
    else 
      if ( h1 -> GetSumw2() -> GetSum() == 0 )
	return h1 -> GetEntries();
      else {
	return ( h1 -> GetSum() * h1 -> GetSum() / h1 -> GetSumw2()->GetSum() );
      }
  
    return h1 -> GetEntries();
  
  }
  
  // _______________________________________________________________________________

  Float_t GetMCError(TH1F* h1, Float_t *N_eff)
  {

    if (!h1)
      return 0.;
  
    if ( h1 -> GetSumw2() == 0 )
      return 0;
    else 
      if ( h1 -> GetSumw2() -> GetSum() == 0 )
	return 0;
      else {
	(*N_eff) = h1 -> GetSum() * h1 -> GetSum() / h1 -> GetSumw2() -> GetSum();
	if ((*N_eff) > 0.)
	  return h1 -> GetRMS() / sqrt((*N_eff));
	else 
	  return 0.;
      }
  
  }

  // ________________________________________________________________________

  Double_t HistMeanError (TH1* h, Int_t axis)

  // This code by Amnon Harel, slightly modified.
  // Replacement to the buggy ROOT routine. AH 8/31/2006

  {

    if (h) {
      if (axis < 1 || axis > 3) 
	return 0;
      Double_t stats[11];
      for (int i = 4; i < 11; ++i) 
	stats[i] = 0;
      h -> GetStats (stats);
      if (stats[1] == 0) 
	return 0;
      Double_t rms = h -> GetRMS (axis);
    
      // in the ROOT version used in D0 to date (8/31/06), GetEffectiveEntries doesn't exist yet.
      Double_t effN = stats[1] ? stats[0]*stats[0] / stats[1] : 0.;
      return rms / sqrt (effN);
    } else
      return 0.;

  }

  // ________________________________________________________________________

  Double_t HistRMSError (TH1* h, Int_t axis)

  // This code by Amnon Harel, slightly modified.
  // Replacement to the buggy ROOT routine. AH 8/31/2006
  // altered by jiri kvita from HistMeanError()

  {

    if (h) {
      if (axis < 1 || axis > 3) 
	return 0;
      Double_t stats[11];
      for (int i = 4; i < 11; ++i) 
	stats[i] = 0;
      h -> GetStats (stats);
      if (stats[1] == 0) 
	return 0;
      Double_t rmserr = h -> GetRMSError (axis);
    
      // in the ROOT version used in D0 to date (8/31/06), GetEffectiveEntries doesn't exist yet.
      Double_t effN = stats[1] ? stats[0]*stats[0] / stats[1] : 0.;
      return rmserr / sqrt (effN);
    } else
      return 0.;

  }



  // _______________________________________________________________________________
  // alternative coded by dag gillberg:

  Float_t GetYError(TH1D* dist, Float_t *N_eff)
  {

    if ( dist -> GetSumw2() == 0 )
      return 0.;
    else
      if ( dist -> GetSumw2() -> GetSum() == 0 )
	return 0.;
      else {
	(*N_eff) = dist->GetSum() * dist->GetSum() / dist->GetSumw2()->GetSum();
	return dist->GetRMS() / sqrt((*N_eff));
      }

  }

  // _______________________________________________________________________________

  void PrintTF1Pars(TF1 *f) 
  {
    cout << "Parameter of " << f -> GetName() << ": ";
    for (int ng = 0; ng <  f -> GetNpar(); ++ng)
      cout << f -> GetParameter(ng) << " ";
    cout << endl;
  }


  // ___________________________________________________________
  // 20.6.2008 jk

  TH1F* MakeHistoFromGraph(TGraphErrors *graph, TH1F* BinningHisto, TString name) 
  {
    TH1F *histo = 0;
    if (graph) {
     double x, y, ex, ey;
      if (BinningHisto) {
	histo = (TH1F*)BinningHisto -> Clone(name.Data());
	histo -> Reset();
      } else {
	//const TArrayD *array = graph -> GetXaxis()->GetXbins();
	//double *binsx = array -> fArray;
	//cout << "OK, making the histo from TGraph by hand, bins: " << array->GetSize() << endl;
	int n = graph -> GetN();
	double *binsx = new double[n+1];
	for (int ip = 0; ip < n; ++ip) {
	  graph -> GetPoint(ip, x, y);
	  ex = graph -> GetErrorX(ip);
	  ey = graph -> GetErrorY(ip);	  
	  binsx[ip] = x - ex;
	}
	binsx[n] = x + ex;
	histo = new TH1F(name.Data(), name.Data(), n, binsx);
      }
 
      //      for (int i = 0; i < graph -> GetN(); ++i) {
      int ip = 0;
      for (int i = 1; (i <= histo -> GetNbinsX()) && (ip < graph -> GetN()); ++i) {
	graph -> GetPoint(ip, x, y);
	ex = graph -> GetErrorX(ip);
	ey = graph -> GetErrorY(ip);
	if (x >= histo -> GetBinLowEdge(i) && x < histo -> GetBinLowEdge(i) + histo -> GetBinWidth(i) ) {
	  histo -> SetBinContent(i, y);
	  histo -> SetBinError(i, ey);
	  ip++;
	} else {
	  
	}
      } // graph
      histo -> Scale(1.);
    }
    return histo;
    
  }

  // ____________________________________________

  TH1F* MakeHalfMaxDiffHisto(std::vector<TH1F*> histos, std::string name)
  {

    // jk 27.6.2008
    // we assume the same binning over histos!

    TH1F* histo = 0;
    int nbins = 0;
    for (unsigned int i = 0; i < histos.size(); ++i) {
      if (histos[i]) {
	if (!histo) {
	  // make a new histo using the
	  histo = (TH1F*) histos[i] -> Clone(name.c_str());
	  histo -> Reset();
	  nbins = histos[i] -> GetNbinsX();
	}
	if (nbins != histos[i] -> GetNbinsX()) {
	  cerr << "ERROR in HistoTools::MakeMaxDiffHisto: Histograms have to have the same binning!" << endl;
	  return 0;
	}
      } // got histo
    } // loop
    
    std::vector<float> maxdiff;
    std::vector<float> differr;
    for (int k = 1; k <= nbins; ++k) {
      maxdiff.push_back(-1.9);
      differr.push_back(0.);
    }
    
    // ok, now we need to find the maximum difference in each bin:
    float diff;
    for (unsigned int i = 0; i < histos.size(); ++i) {
      for (unsigned int j = i; j < histos.size(); ++j) {
	for (unsigned int k = 1; k <= nbins; ++k) {
	  diff = fabs( histos[i] -> GetBinContent(k) - histos[j] -> GetBinContent(k) );
	  if (diff > maxdiff[k-1]) {
	    maxdiff[k-1] = diff;
	    differr[k-1] = sqrt( pow(histos[i] -> GetBinError(k), 2) + pow(histos[j] -> GetBinError(k), 2) );
	  }
	} // bins
      } // j
    } // i

    if (histo) {
      for (int k = 1; k <= nbins; ++k) {
	histo -> SetBinContent(k, maxdiff[k-1] / 2.);
	histo -> SetBinError(k, differr[k-1] / 2.);
      } 
      histo -> Scale(1.);
    }


    return histo;

  }

  // ____________________________________________
  void ZeroErrorBars(TH1F *h)
  {
    if (h) {
      for (int i = 1; i <= h -> GetNbinsX(); ++i) {
	h -> SetBinError(i, 0.);
      }
    }
  }

  // ____________________________________________
  void SquareHisto(TH1F *h)
  {
    if (h) {
      for (int i = 1; i <= h -> GetNbinsX(); ++i) {
	float y = h -> GetBinContent(i);
	float ye = h -> GetBinError(i);
	h -> SetBinContent(i, y*y);
	h -> SetBinError(i, ye*ye);
      }
      h -> Scale(1.);
    }
  }
  // ____________________________________________

  void SquareRootHisto(TH1F *h)
  {
    if (h) {
      for (int i = 1; i <= h -> GetNbinsX(); ++i) {
	float y = h -> GetBinContent(i);
	float ye = h -> GetBinError(i);
	if (y > 0.)
	  h -> SetBinContent(i, sqrt(y));
	if (ye > 0.)
	  h -> SetBinError(i, sqrt(ye));
      }
      h -> Scale(1.);
    }
  }
  // ____________________________________________

  void AddInSquares(TH1F *AddTo, TH1F *what, float OverAllSign)
  {
    if (AddTo && what) {

      AddTo -> Scale(1./OverAllSign);
      SquareHisto(AddTo);
      SquareHisto(what);
      AddTo -> Add(what);
      SquareRootHisto(AddTo);
      SquareRootHisto(what);
      AddTo -> Scale(OverAllSign);

    }
  }

  // ____________________________________________

  std::vector<std::string> TokenizeString(std::string input, std::string delim)
  {
    
    TString SuperString(input.c_str());
    TObjArray *tokens = SuperString.Tokenize(delim.c_str());

    std::vector<std::string> output;
    cout << "--- TokenizeString: Read "
	 << tokens -> GetEntries() << " === "
	 << " tokens from " << input.c_str() 
	 << endl;
    for (int i = 0; i < tokens -> GetEntries(); ++i) {
      TObjString *tokenString = (TObjString*)(tokens -> At(i));
      TString token = tokenString -> GetString();
      cout << "  read token: " <<  token.Data() << endl;
      output.push_back(std::string(token.Data()));
    }

    return output;
  
  }


  // ___________________________________________________________

  TH1F* MakeSymErrorBand(TH1F *center, TH1F *Err, TString name, bool reset, double center_value)
  {

    if (reset == false) {
      if (!center)
	cout << "ERROR. asked to use center histo while no such provided!" << endl;
      return 0;
    }

    TH1F *CloneFrom = center;
    //    bool reset = false;
    if (CloneFrom == 0) {
      CloneFrom = Err;
      reset = true;
    }
    
    TH1F *histo = 0;
    if (CloneFrom) {
      histo = (TH1F*) CloneFrom -> Clone(name);
      if (reset) {
	histo -> Reset();
      }
      if (Err) {
	for (int i = 1; i < histo -> GetNbinsX() + 1; ++i) {
	  if (reset)
	    histo -> SetBinContent(i, center_value);
	  histo -> SetBinError(i, TMath::Abs(Err -> GetBinContent(i)));
	  //	  cout <<  histo -> GetBinContent(i) << " " << histo -> GetBinError(i) << endl;
	} // bins
      } // Err
      histo -> Scale(1.);
    }
    
    return histo;
  }


  // ___________________________________________________________

  TH1F* MakeSymErrorBandHisto(TH1F *center, TH1F *Err, float Sign, TString name, bool reset, double center_value)
  {

    if (reset == false) {
      if (!center)
	cout << "ERROR. asked to use center histo while no such provided!" << endl;
      return 0;
    }

    TH1F *CloneFrom = center;
    if (CloneFrom == 0) {
      CloneFrom = Err;
      reset = true;
    }
    
    TH1F *histo = 0;
    if (CloneFrom) {
      histo = (TH1F*) CloneFrom -> Clone(name);
      if (reset) {
	histo -> Reset();
      }
      if (Err) {
	for (int i = 1; i < histo -> GetNbinsX() + 1; ++i) {
	  if (reset) {
	    histo -> SetBinContent(i, center_value + Sign*(Err -> GetBinContent(i)) );
	    histo -> SetBinError(i, 0.);
	  } else {
	    histo -> SetBinContent(i, center -> GetBinContent(i) + Sign*(Err -> GetBinContent(i)) );
	    histo -> SetBinError(i, center -> GetBinError(i));
	  }

	  //	  cout <<  histo -> GetBinContent(i) << " " << histo -> GetBinError(i) << endl;
	} // bins
      } // Err
      histo -> Scale(1.);
    }
    
    return histo;
  }

  // ___________________________________________________________

  void Transpose(TH2 *histo)
  {
    for (int i = 0; i <= histo -> GetNbinsX() + 1; ++i) {
      for (int j = 0; j <= i; ++j) {
	
	float swap = histo -> GetBinContent(i, j);
	float swaperr = histo -> GetBinError(i, j);
	histo -> SetBinContent(i, j, histo -> GetBinContent(j, i));
	histo -> SetBinError(i, j, histo -> GetBinError(j, i));
	
	histo -> SetBinContent(j, i, swap);
	histo -> SetBinError(j, i, swaperr);
	
      }
    }
    
  }

  // ___________________________________________________________

  TH1F *MakeDiagonalHisto(TH2F *h2, TString name) 
  {
    TH1F *h = 0;
    if (h2) {
      const TArrayD *array = h2 -> GetXaxis() -> GetXbins();
      double *binsx = array -> fArray;
      h = new TH1F(name, TString("Purity ") + h2 -> GetTitle(), h2->GetNbinsX(), binsx);
      //      for (int j = 0; j < h2->GetNbinsX(); ++j)
      //	cout << binsx[j] << endl;
      h -> Sumw2();
      for (int i = 1; i <  h->GetNbinsX()+1; ++i) {
	//	cout << "Setting diag to " << h2 -> GetBinContent(i, i) << endl;
	h -> SetBinContent(i, h2 -> GetBinContent(i, i));
	h -> SetBinError(i, h2 -> GetBinError(i, i));
      } // bins
      h -> GetXaxis() -> SetTitle(h2 -> GetXaxis() -> GetTitle());
      h -> GetYaxis() -> SetTitle("Migration Purity");
      h -> Scale(1.);
    }
    return h;
  }

  // ___________________________________________________________
  TLegend *MakeLegend( float x1, float y1, float x2, float y2)
  {
    TLegend *leg = new TLegend(x1, y1, x2, y2);
    leg -> SetFillColor(0);
    return leg;
  }

  // ___________________________________________________________

  TPaveText *MakePaveText(TString item, float x1, float y1, float x2, float y2, float size) 
  {
    TPaveText *text = new TPaveText(x1, y1, x2, y2, "NDC");
    text -> SetBorderSize(0);
    text -> SetTextAlign(12);
    text -> SetTextSize(size);
    text -> SetTextColor(1);
    text -> AddText(item);
    text -> Draw();
    return text;
  }
  // ___________________________________________________________

  // assume poisson-like distributed content in each bin
  // and smear each bin content accordingly

  TH1F *MakePoissonSmearedHisto(TH1F *h, TRandom3 *rand, std::string tag)
  {
    if (h) {
      TH1F* hsmear = (TH1F*) h -> Clone(Form("%s%s", h -> GetName(), tag.c_str()));
      hsmear -> Reset();

      if (!rand)
	rand = new TRandom3(0);
      float sum = 0.;
      for (int k = 1; k < h->GetNbinsX() + 1 ; ++k) {
	float y = h -> GetBinContent(k);
	if (y > 0.) {
	  //	float err = h -> GetBinError(k);
	  float ynew = -1.;
	  while (ynew <= 0. ) {
	    ynew = rand -> Poisson(y);
	  }
	  hsmear -> SetBinContent(k, ynew);
	  hsmear -> SetBinError(k, sqrt(ynew));
	  sum += ynew;
	} // non-zero bin content
      } // bins
      hsmear -> SetEntries(sum);
      hsmear -> Scale(1.);
      return hsmear;
    }

    return 0;

  }


  // ___________________________________________________________

  TH1F* MakeConstHisto(TH1F *h, float CentralConst, float Const, std::string name, bool MultiplyByHisto)
  {
    TH1F* hnew = 0;
    if (h) {
      hnew = (TH1F*) h -> Clone(name.c_str());
      hnew -> Reset();
      //      cout << "Making const histo with he content: " << endl;
      for (int k = 1; k < hnew -> GetNbinsX() + 1 ; ++k) {
	if (MultiplyByHisto && h -> GetBinContent(k) > 0.)
	  hnew -> SetBinContent(k, CentralConst + Const*(h -> GetBinContent(k)));
	else
	  hnew -> SetBinContent(k, CentralConst + Const);
	//	cout << k << " " << hnew -> GetBinContent(k) << endl;

      }
      hnew -> Scale(1.);
    }
    return hnew;
  }

 // ___________________________________________________________


  // ___________________________________________________________
// _______________________________________________________________________________

bool FitGauss(TH1D* histo, int rebin, float width, float* mean, float* sigma, float* error, const char* fitoption,
	      float _MinimumEntries, bool getfit, TF1 **fit)
  
// performs a gauss fit on the interval (mean - width*sigma, mean + width*sigma)
  
{
  if (getfit)
    (*fit) = 0;
  if (histo) {

    if (rebin > 0)
      histo -> Rebin(rebin);
    float hmean  = histo -> GetMean();
    float hsigma = histo -> GetRMS();

    //check whether nentries!=0
    
    float evts_integral = histo -> Integral(histo -> GetXaxis() -> GetFirst(),
    					    histo -> GetXaxis() -> GetLast());


    if  (! (evts_integral > 0.)) {
      *error = 0;
      *sigma = 0;
      *mean = 0;
      return 1;
    }

    //    if  (histo ->GetEntries() < _MinimumEntries) {
    if  (GetNeff(histo) < _MinimumEntries) {
      *sigma = hsigma;
      *mean  = hmean;
      *error = (*sigma) / sqrt(evts_integral);
      cout << "FitGaus(): WARNING: Too few entries to perform Gauss fit (minumum: " << _MinimumEntries << "). Using mean and sigma. Nevts="
	   << evts_integral << ", Neff=" << GetNeff(histo) << endl;
      return 1;
    }

    //check wheter all entries are not in one bin:
    for (int i = histo -> GetXaxis() -> GetFirst(); i <= histo -> GetXaxis() -> GetLast(); ++i)
      if (evts_integral == histo -> GetBinContent(i)) {
	*sigma = (histo -> GetBinWidth(i));
	*mean  = hmean;
	*error = (*sigma) / sqrt(histo -> GetBinContent(i));
	cout << "FitGaus(): All entries in one bin i=" << i << "!" << endl;
	return 0;
      }

    if (width < 0.) {
      cout << "FitGaus(): Warning: Requested interval size in units of sigma < 0, multiplying it by -1." << endl;
      width *= -1;
    }

    std::string fname = "gaussfit_";
    fname += histo -> GetName();

    TF1 g(fname.c_str(), "[0]*exp(-(x-[1])^2/(2*[2]^2))",
	  hmean - width * hsigma,
	  hmean + width*hsigma);
    g.SetParameters(histo -> GetMaximum(), hmean, hsigma);
    g.SetParNames("A","#mu","#sigma");
    g.SetParLimits(2, 0., 100.*(histo -> GetXaxis() -> GetXmax() - histo -> GetXaxis() -> GetXmin()));
    //  g.SetLineWidth(1);
    histo -> Fit(&g, fitoption);
    *sigma = g.GetParameter(2);
    *mean  = g.GetParameter(1);

    float neff = GetNeff(histo);

    //number of entries within fit range:
    //    float neff = histo -> Integral(histo -> FindBin(hmean - width * hsigma),
    //				   histo -> FindBin(hmean + width * hsigma));

    if (neff > 0.)
      *error = (*sigma)/(sqrt(neff));
    else *error = 0.;
    //    char out[1000];
    // sprintf(out,"A=%6.3f, mean=%6.3f, sigma=%6.3f, Neff=%6.3f, error=%8.5f",g.GetParameter(0),*mean,*sigma,neff,*error);
    // cout << out << endl;
    //"A="<<g.GetParameter(0)<<", mean="<<(*mean)<<", sigma="<<(*sigma)<<", Neff="<<neff<<", error="<<(*error)<<endl;

    if (getfit)
      (*fit) = new TF1(g);

    return 1;
  }

  cout << "HistUtils.cpp::FitGaus(): ERROR: Cannot fit requested histogram, got a null pointer!" << endl;
  return 0;
}

 // ________________________________________________________________________

int PlotProfile(TH2 *h2, 
		TGraphErrors **profile_graph, TGraphErrors **resolution_graph, 
		TPad **profile_can, TPad **resolution_can,
		bool doGauss, bool plotSlices, 
		TString title, TString SlicesTag,
		bool zoom , Float_t x1, Float_t x2, 
		bool draw, 
		float _MinimumEntriesForGaussFit, float widthToFitGaussAround,
		float graph_x1, float graph_x2,
		float graph_y1, float graph_y2,
		int col,
		int width,
		int mark,
		float size) 

{


  if (!h2) {
    cout << "HistUtils.cpp::PlotProfile: ERROR: pointer to 2D histogram is 0!" << endl;
    return 0;
  } else
    if (_hist_util_debug > 0)
      cout << "HistUtils.cpp::PlotProfile: Got TH2 " << h2 -> GetName() << endl;

  int NBins = h2 -> GetNbinsX();
  int point = 0;
  TString hname = h2 -> GetName();  

  TH1D *slice[maxNbins];
  for (int i = 0; i < maxNbins; ++i)
    slice[i] = 0;

  (*profile_graph) = new TGraphErrors();
  (*profile_graph) -> SetName(TString("ProfileGraph_") + hname);
  
  (*resolution_graph) = new TGraphErrors();
  (*resolution_graph) -> SetName(TString("ResolutionGraph_") + hname);

  /*
    TString canTag = "profile_graph";
    canTag += SlicesTag;
    if (draw) {
    (*profile_can) = new TCanvas(hname + "_Can_" + canTag,
    hname + "_Can_" + canTag,
    0, 0, 800, 500);
    canTag.ReplaceAll(TString("profile_graph"), "resolution_graph");
    (*resolution_can) = new TCanvas(hname + "_Can_" + canTag,
    hname + "_Can_" + canTag,
    0, 0, 800, 500);
    }
  */

  TCanvas *Can_Slices = 0;
 
  int nx = 3;
  int ny = 2;
  if (NBins > 6) {
    nx = 3;
    ny = 3;
  }
  if (NBins > 9) {
    nx = 4;
    ny = 3;
  }
  if (NBins > 12) {
    nx = 5;
    ny = 4;
  }

  if (plotSlices) {
    Can_Slices = new TCanvas("Slices_" + hname + SlicesTag,
			     "Slices_" + hname + SlicesTag,
			     canv_width * nx / 3, canv_width * ny / 3);    
    Can_Slices -> Divide(nx, ny);
  }

  TF1 *GaussFit[maxNbins];
    
  for ( int bin = 1; bin < NBins + 1; ++bin ) {
    TString SliceName = "Slice_";
    SliceName += bin;
    SliceName += "_";
    SliceName += hname;
    
    Double_t xx = h2 -> GetBinCenter(bin);
    Double_t xe = h2 -> GetBinWidth(bin) / 2.;

    if (_hist_util_debug > 1)
      cout << "Getting slice " << bin;

    slice[bin]  = h2   -> ProjectionY(SliceName, bin, bin, "e");
    if (slice[bin]) {
      //cout << "Got slice, mean=" <<  slice[bin] -> GetMean() << endl;
    } else {
      //cout << "ERROR making the slice of the 2D histo!" << endl;
    }

    Double_t yy, ye;
    bool GotPoint = false;
    Float_t N_eff = -1.;

    int rebin = 1;
    float fitmean;
    float fitsigma;
    float fiterror;
    //    const char* fitoption = "";
    bool getfit = true;

    GaussFit[bin] = 0;
    if (slice[bin] -> GetEntries() > 0.) {
      if (doGauss) {
	//	cout << "Gaussian fitting not supported yet!" << endl;
	  
	  /* another try:
	     
	  TString fitname = "gaussfit_";
	  fitname += hname = h2 -> GetName();
	  fitname += "_bin";
	  fitname += bin;
	  Float_t hsigma = slice[bin] -> GetRMS();
	  Float_t hmean = slice[bin] -> GetMean();
	  //	Float_t hmin = slice[bin] -> GetXaxis() -> GetXmin();
	  //	Float_t hmax = slice[bin] -> GetXaxis() -> GetXmax();
	  Float_t nsigmas  = 2.;
	  Float_t hmin = hmean - nsigmas*hsigma;
	  Float_t hmax = hmean - nsigmas*hsigma;
	  
	  GaussFit[bin] = new TF1(fitname, "[0]*exp( -(x - [1])^2 / (2*[2]^2))", hmin, hmax);
	  
	  //				hmean - width * hsigma, 
	  //				hmean + width*hsigma);
	  
	  GaussFit[bin] -> SetParameters(slice[bin] -> GetEntries(), hmean, hsigma);
	  slice[bin] -> Fit(GaussFit[bin]);
	  yy =  GaussFit[bin] -> GetParameter(1);
	  Float_t Neff = GetNeff(slice[bin]);
	  if (Neff > 0.)
	    ye = GaussFit[bin] -> GetParameter(2) / Neff;
	  else
	    ye = GaussFit[bin] -> GetParameter(2);

	  */
	

  
	if (FitGauss(slice[bin], rebin, widthToFitGaussAround, &fitmean, &fitsigma, &fiterror, "Q0",
		     _MinimumEntriesForGaussFit, getfit, &GaussFit[bin]) ) {
	  
	  yy = fitmean;
	  ye = fiterror;

	  GotPoint = true;
	} else {
	  yy = slice[bin] -> GetMean();
	  ye = GetYError(slice[bin], &N_eff);
	  GotPoint = true;
	}
	
      } else {
	yy = slice[bin] -> GetMean();
	ye = GetYError(slice[bin], &N_eff);
	GotPoint = true;
      }
    }
    
    if (GotPoint) {
      (*profile_graph) -> SetPoint(      point, xx, yy  );
      (*profile_graph) -> SetPointError( point, xe, ye  );

      if (doGauss && GaussFit[bin]) {
	(*resolution_graph) -> SetPoint(      point, xx, fitsigma  );
	(*resolution_graph) -> SetPointError( point, xe, (GaussFit[bin] -> GetParError(1))  );
      } else {

	(*resolution_graph) -> SetPoint(      point, xx, slice[bin] -> GetRMS()  );
	//	(*resolution_graph) -> SetPoint(      point, xx, HistMeanError(slice[bin], 1)  );
	(*resolution_graph) -> SetPointError( point, xe, HistRMSError(slice[bin], 1)  );
      }
      ++point;
      if (_hist_util_debug > 1)
	cout << "...Got point: "
	     << " xx=" << xx
	     << " yy=" << yy
	     << " xe=" << xe
	     << " ye=" << ye
	     << endl;

    }

    TLine* Meanline[maxNbins];
    //    int _RangeOut = 3; // a fraction of the bin range to be removed from view for slices; try 4, 5, 6

    if (plotSlices) {
      //      int bin1, bin2;
      Meanline[bin] = 0;
      if (slice[bin]) {

	// fix for SystemMass slices!
	if ( bin == 1 && TMath::Abs(slice[bin] -> GetRMS()) < 1.e-5)
	  continue;
	slice[bin] -> SetLineColor(errbarcol);
	slice[bin] -> SetLineWidth(1);
	slice[bin] -> SetMarkerColor(slicecol);
	slice[bin] -> SetMarkerStyle(markerStyle);
	slice[bin] -> SetMarkerSize(mSlicesize);
	if (bin <= nx*ny) {
	  Can_Slices -> cd(bin);

	  // 27.7.2008
	  //	  if (slice[bin] -> GetMaximum() > 0.)
	  //	    Can_Slices -> SetLogy();

	  //	  if (_RangeOut > 0) {
	  //	    bin1 = slice[bin]->GetNbinsX() / _RangeOut;
	  //	    bin2 = slice[bin]->GetNbinsX() -  slice[bin]->GetNbinsX() / _RangeOut;
	  //	  } else {
	  //	    bin1 = 1;
	  //	    bin2 = slice[bin]->GetNbinsX();
	  //	  }
	  //	  slice[bin] -> GetXaxis() -> SetRange(bin1, bin2);


	  // cout << " x1=" << x1  << " x2=" << x2  << endl;

	  if (x2 > x1)
	    slice[bin] -> GetXaxis() -> SetRangeUser(x1, x2);

	  // we're losing the pointer here!
	  //	  slice[bin] -> DrawCopy(SliceDrawOpt);
	  //	  cout << "Drawing slice " << slice[bin] -> GetName() 
	  //	       << " Entries: " <<  slice[bin] -> GetEntries() 
	  //	       << endl;
	  //	  PrintBinContent(slice[bin]);
	  slice[bin] -> SetMaximum(1.4*slice[bin] -> GetMaximum());
	  slice[bin] -> SetStats(0.);
	  slice[bin] -> Draw(SliceDrawOpt);

	  Meanline[bin] = new TLine(slice[bin]->GetMean(), slice[bin]->GetMinimum(), 
				    slice[bin]->GetMean(), 0.6*slice[bin]->GetMaximum());
	  Meanline[bin] -> SetLineWidth(linewidth);
	  Meanline[bin] -> SetLineColor(linecol);
	  Meanline[bin] -> Draw();
	  if (GotPoint && doGauss && GaussFit[bin]) {
	    GaussFit[bin] -> SetLineWidth(linewidth);
	    GaussFit[bin] -> SetLineColor(gcol);
	    GaussFit[bin] -> Draw("same");
	  }
	  TPaveText *pave = MakePaveText(Form("Mean: %3.2f, RMS: %3.2f; (%3.0f, %3.0f)",
					      slice[bin] -> GetMean(),
					      slice[bin] -> GetRMS(),
					      h2 -> GetXaxis() -> GetBinLowEdge(bin),
					      h2 -> GetXaxis() -> GetBinLowEdge(bin+1)), 
					 0.30, 0.80, 0.88, 0.88, 0.035);
	}
      }
    } // slices
    
  } // bins

  if (plotSlices) {
    Can_Slices -> Print(TString(Can_Slices->GetName()) + ".eps");
    for (int i = 0; i < nx*ny; ++i) {
      Can_Slices -> cd(i+1);
      if (slice[i+1]) {
	gPad -> SetLogy();
	slice[i+1] -> SetMaximum(3.5*slice[i+1] -> GetMaximum());
      }
    }
    Can_Slices -> Update();
    Can_Slices -> Print(TString(Can_Slices->GetName()) + "_log.eps");
  }

  (*profile_graph) -> SetLineColor(col);
  (*profile_graph) -> SetLineWidth(width);
  (*profile_graph) -> SetMarkerColor(col);
  (*profile_graph) -> SetMarkerStyle(mark);
  (*profile_graph) -> SetMarkerSize(size);
  (*profile_graph) -> SetTitle(title + ";" + h2 -> GetXaxis() -> GetTitle() + ";" + h2 -> GetYaxis() -> GetTitle());

  (*resolution_graph) -> SetLineColor(col);
  (*resolution_graph) -> SetLineWidth(width);
  (*resolution_graph) -> SetMarkerColor(col);
  (*resolution_graph) -> SetMarkerStyle(mark);
  (*resolution_graph) -> SetMarkerSize(size);
  (*resolution_graph) -> SetTitle(title + " Resolution;" + h2 -> GetXaxis() -> GetTitle() + ";#sigma " + h2 -> GetYaxis() -> GetTitle());


 if (draw) {
    (*profile_can) -> cd();
    //    (*profile_can) -> SetGridx();
    //    (*profile_can) -> SetGridy();
    if (graph_y1 < graph_y2)
      (*profile_graph) -> GetYaxis() -> SetRangeUser(graph_y1, graph_y2);
    (*profile_graph) -> Draw("AP");

    (*resolution_can) -> cd();
    //    (*resolution_can) -> SetGridx();
    //    (*resolution_can) -> SetGridy();
    (*resolution_graph) -> GetYaxis() -> SetRangeUser(graph_x1, graph_x2);
    (*resolution_graph) -> Draw("AP");

 }

  return 1;

}

// ________________________________________________________________________

int GetH2AndPlotProfile(TString hname, TString filename, TString dirname, 
			TGraphErrors **profile_graph, 
			TGraphErrors **resolution_graph,
			TPad **profile_can, TPad **resolution_can, 
			bool doGauss, bool plotSlices, TString title, TString SlicesTag,
			bool zoom , Float_t x1, Float_t x2,
			bool draw, bool getH2, TH2D **h2copy, TFile **file,
			float _MinimumEntriesForGaussFit, float widthToFitGaussAround,
			float graph_x1, float graph_x2, float graph_y1, float graph_y2) 
{

  //  TFile file(filename.Data(), "READ");
  //  TFile *file = new TFile(filename.Data(), "READ");
  if (!*file)
    (*file) = new TFile(filename.Data(), "READ");
  else {
    cout << "OK, assuming file is already open..." << endl;
    assert( (*file) -> IsOpen() );
  }
  //  if (!file.IsOpen()) {
  if (! (*file) -> IsOpen()) {
    cout << "HistUtils.cpp::GetH2AndPlotProfile: ERROR! File " << filename.Data() << " does not exist!" << endl;
    return 0;
  } else 
    if (_hist_util_debug > 0)
      cout << "HistUtils.cpp::GetH2AndPlotProfile: Opened file " << filename.Data() << endl;
  
  TH2D *h2 = 0;
  //  h2 = (TH2D*) file.Get( (dirname + hname).Data());
  h2 = (TH2D*) (*file) -> Get( (dirname + hname).Data());
  
  if (h2 && getH2) {
    cout << "Cloning the 2D histo..." << endl;
    //    gDirectory -> cd();
    (*h2copy) = (TH2D*) ( h2 -> Clone(TString(h2 -> GetName()) + "_copy") );
    cout << (*h2copy) -> GetName() << endl;
  }
  int col     =  2;
  int width   =  1;
  int mark    = 22;
  float size  =  0.7;
  return (PlotProfile(h2, profile_graph, resolution_graph, profile_can, resolution_can, 
		      doGauss, plotSlices, title, SlicesTag, zoom, x1, x2, draw, 
		      _MinimumEntriesForGaussFit, widthToFitGaussAround,
		      graph_x1, graph_x2, graph_y1, graph_y2, col, width, mark, size));
  
  
}

// ________________________________________________________________________


// ____________________________________________

TH1* GetHisto1DFromFile(TFile *file, std::string dirname, std::string hname)
{
  

  if (!file) {
    cout << "ERROR: GetHisto1DFromFile::Pointer to file is zero!" << endl;
    return 0;
  }
  // assert(file);
  
  TH1 *h = 0;
  cout << "Getting " << (dirname + hname).c_str() << endl;
  h = (TH1*) file -> Get((dirname + hname).c_str());

  /*
    if (h -> InheritsFrom("TH2F")) {
    TH2F *histo = (TH2F*) h;
    //    histo -> Draw("colz");
    } else {
    TH1F *histo = (TH1F*) h;
    //    histo -> Draw("e1hist");
    }
  */
  
  if (!h) 
    cout << "ERROR: GetHisto1DFromFile::Failed getting histogram " << (dirname+hname).c_str() 
	 << " from file " << file -> GetName()
	 << endl;

  return h;

}// ____________________________________________

TH2F* GetHisto2DFromFile(TFile *file, std::string dirname, std::string hname)
{
  

  if (!file) {
    cout << "ERROR: GetHisto2DFromFile::Pointer to file is zero!" << endl;
    return 0;
  }
  // assert(file);
  
  TH2F *h = 0;
  h = (TH2F*) file -> Get((dirname + hname).c_str());

  /*
    if (h -> InheritsFrom("TH2F")) {
    TH2F *histo = (TH2F*) h;
    //    histo -> Draw("colz");
    } else {
    TH1F *histo = (TH1F*) h;
    //    histo -> Draw("e1hist");
    }
  */
  
  if (!h) 
    cout << "ERROR: GetHisto2DFromFile::Failed getting histogram " << (dirname+hname).c_str() << endl;

  return h;

}


// ____________________________________________

TObject* GetFromFile(TFile *file, std::string dirname, std::string hname)
{
  if (!file) {
    cout << "ERROR: GetFromFile::Pointer to file is zero!" << endl;
    return 0;
  }
  // assert(file);
  
  TObject *h = 0;
  h = (TObject*) file -> Get((dirname + hname).c_str());

  
  if (!h) 
    cout << "ERROR: GetFromFile::Failed getting object " << (dirname+hname).c_str() << endl;

  return h;
}

// ____________________________________________

TObject* GetFromFile(TFile *file, std::string hname)
{
  if (!file) {
    cout << "ERROR: GetFromFile::Pointer to file is zero!" << endl;
    return 0;
  }
  // assert(file);
  
  TObject *h = 0;
  h = (TObject*) file -> Get(hname.c_str());

  
  if (!h) 
    cout << "ERROR: GetFromFile::Failed getting object " << hname.c_str() << endl;
  else
    cout << "Got " << hname.c_str() << " from file " << file -> GetName() << endl;

  return h;
}

// ____________________________________________

TObject* GetFromFile(std::string filename, TFile *file, std::string hname)
{

  TObject *h = 0;
  if (file) {
    cout << "OK, we assume file was already open, as got non-zero pointer!" << hname.c_str() << endl;
  }

  // second condition is not tried if already first one is fulfilled
  if (!file || !(file ->IsOpen()) ) {
    file = new TFile(filename.c_str(), "READ");
  } else {
    cout << "OK, we think we should have the file..." << endl;
  }
  
  if (CheckFileOpen(file)) {
    h = (TObject*) file -> Get(hname.c_str());
  }

   if (!h) 
     cout << "ERROR: GetFromFile::Failed getting object " << hname.c_str() 
	  << " from file " << filename.c_str() 
	  << endl;

  return h;
}

// ___________________________________________________________


  TH1F *TruncateBinsFromHisto(TH1F *hist, TString name, int binout1, int binout2)
  {


    cout << "In HistoTools::TruncateBinsFromHisto" << endl;
    if (!hist)
      return 0;

    int nbins = hist -> GetNbinsX();
    if (binout1 <= 1 || binout2 >= nbins) {

      // works only for left or right part of bins
      // middle bins not expected to be removed, does not make sence
      const TArrayD *array =  hist -> GetXaxis() -> GetXbins();
      double *binsx = array -> fArray;
      double *binsxnew = new double[nbins];
      double *binsErr = new double[nbins];
      double *binsCon = new double[nbins];

      int nbinsnew = 0;
      binsxnew[nbinsnew++] = binsx[0];
      int lasti = 0;      
      for (int i = 1; i <= nbins; ++i) {
	if (i < binout1 || i > binout2) {
	  binsxnew[nbinsnew] = binsx[i];
	  binsErr[nbinsnew] = hist -> GetBinError(i);
	  binsCon[nbinsnew] = hist -> GetBinContent(i);
	  nbinsnew++;
	  lasti = i;
	} 
      }
      //      binsxnew[nbinsnew] = binsx[lasti];
      nbinsnew--;
      for (int i = 1; i <= nbinsnew; ++i) {
	cout <<  binsxnew[i-1] << " " <<  binsxnew[i] << " "
	     <<  binsCon[i] << " "
	     <<  binsErr[i] << endl;
      }
      //      cout << binsxnew[nbinsnew] << endl;
      
      TH1F *histnew = new TH1F(name, hist -> GetTitle(), nbinsnew, binsxnew);  
      histnew -> Sumw2();
      for (int i = 1; i <= nbinsnew; ++i) {
	histnew -> SetBinContent(i, binsCon[i]);
	histnew -> SetBinError(i, binsErr[i]);
      }
      histnew -> Scale(1.);
      delete [] binsxnew;
      delete [] binsErr;
      delete [] binsCon;

      return histnew;

    } else {
      cerr << "ERROR: HistoTools::TruncateBinsFromHisto: cannot remove bins from the centre of the axis!" << endl;
    }
    
    return 0;
  }


  // ___________________________________________________________

  TGraphErrors* MakeGraphFromHisto(TH1 *histo, TString name, bool ignoreYerrors)
  {

    if (!histo)
      return 0;

    int nbinsx = histo -> GetNbinsX();
    //    const TArrayD *array =  histo -> GetXaxis() -> GetXbins();
    //    double *binsx = array -> fArray;
    TGraphErrors *graph = new TGraphErrors();
    graph -> SetName(name);
    graph -> SetTitle(histo -> GetTitle());
    graph -> GetXaxis() -> SetTitle(histo -> GetXaxis() -> GetTitle());
    graph -> GetYaxis() -> SetTitle(histo -> GetYaxis() -> GetTitle());
    CopyHistoStyle(histo, graph);

    for (int i = 0; i < nbinsx; ++i) {   
      graph -> SetPoint(i, histo -> GetBinCenter(i+1), histo -> GetBinContent(i+1));
      double xe = 0.;
      double ye = histo -> GetBinError(i+1);
      if (!ignoreYerrors)
	xe = 0.5*(histo -> GetBinWidth(i+1));
      graph -> SetPointError(i, xe, ye  );
    }

    return graph;

  }

  // ___________________________________________________________
  
  int MakeShapeAndAbsoluteErrorHistos(TH1F *central, TH1F *shifted, TH1F *&shape, TH1F *&absolute)
  {

    shape = 0;
    absolute = 0;
    if (central and shifted) {

      shape = (TH1F*) shifted -> Clone(TString(shifted -> GetName()) + "_shape");
      double alpha =  central -> Integral("width") / shape -> Integral("width");
      shape -> Scale(alpha);
      absolute = (TH1F*) shifted -> Clone(TString(shifted -> GetName()) + "_absolute");
      absolute -> Add(shape, -1.);

      return 0;
    } 
    return 1;
    
  }
// _______________________________________________________

void ReadHistosToVector(std::vector<TH1F*> &hist, std::vector<TGraphErrors*> &graph)
{
  // adopted from Jochen's DMC:
  TObject *obj;
  TKey *key;
  TIter nextkey(gDirectory->GetListOfKeys());
  while ((key = (TKey*)nextkey()) ){
    obj = key->ReadObj();
    if (obj->InheritsFrom("TH1")){
      TString hname = obj->GetName();
      cout << "Read " << hname.Data() << endl;
      TH1F *_hist = (TH1F*)obj;
      //      _hist -> SetBit(TH1::kIsAverage);
      hist.push_back(_hist);
    } else if (obj->InheritsFrom("TGraphErrors")){
      TString hname = obj->GetName();
      graph.push_back((TGraphErrors*)obj);
    }
  } // while ((key = (TKey*)nextkey()) )

  return;
}

// _______________________________________________________

int AddHistosAver(TH1F *from, TH1F* to, double AverFactor)
{
 
  if (to && from) {
    // add histos as average: average bin conetent as well as errors!
    int nbins1 =  to -> GetNbinsX();
    int nbins2 =  from -> GetNbinsX();
    if (nbins1 != nbins2) {
      cout << "AddHistosAver:ERROR: adding histos witrh different binnings!" << endl;
      return 1;
    }
    
    for (int i = 0; i <= nbins1 + 1; ++i) {
      double ynew = from -> GetBinContent(i) + to -> GetBinContent(i);
      double errnew = from -> GetBinError(i) + to -> GetBinError(i);
      if (AverFactor > 0.) {
	ynew /= AverFactor;
	errnew /= AverFactor;
      }
      to -> SetBinContent(i, ynew);
      to -> SetBinError(i, errnew);
    }
    to -> Scale(1.);
  } else
    return 1;
  return 0;
}

// _______________________________________________________

TGraphErrors* AddGraphsAver(TGraphErrors *from, TGraphErrors *to, double AverFactor, TString MergeTag)
{
  
  if (from && to ) {
    int np1 =  from -> GetN();
    int np2 =  from -> GetN();
    if (np1 != np2) {
      cerr << "AddGraphsAver:ERROR: graphs have different number of points! " << np1 << " " << np2 << endl;
      return 0;
    }
    int np = np1;

    TGraphErrors *_graph = new TGraphErrors();
    _graph -> SetName(TString(from -> GetName()) + MergeTag);
    double x, x1, x2, y, y1, y2, ex, ex1, ex2, ey, ey1, ey2;
    int ipnew = 0;
    for (int ip = 0; ip < np ; ++ip) {
      from -> GetPoint(ip, x1, y1);
      ex1 = from -> GetErrorX(ip);
      ey1 = from -> GetErrorY(ip);
      to -> GetPoint(ip, x2, y2);
      ex2 = to -> GetErrorX(ip);
      ey2 = to -> GetErrorY(ip);
      
      if ( TMath::Abs(x1 - x2) < HistoTools::Epsilon) {
	y = (y1 + y2) / AverFactor;
	ey = (ey1 + ey2) / AverFactor;
	x = (x1 + x2) / 2;
	ex = (ex1 + ex2) / AverFactor;
	_graph -> SetPoint(ipnew, x, y);
	_graph -> SetPointError(ipnew, ex, ey);
	ipnew++;
      } else {
	cerr << "ERROR: points x's too far away! " << x1 << " " << x2 << endl;
      }
    } // graph
    return _graph;
  } // both exist

  return 0;

}
// _______________________________________________________

int PrintGraphContent(TGraphErrors *graph)
{
  if (!graph) {
    cerr << "PrintGraphContent:ERROR: got a null pointer, cannot print graph content!" << endl;
    return 1;
  }
  cout << "Printing the content of a TGraph " << graph -> GetName() << endl;
  double x, y, ex, ey;
  for (int ip = 0; ip < graph -> GetN() ; ++ip) {
    graph -> GetPoint(ip, x, y);
    ex = graph -> GetErrorX(ip);
    ey = graph -> GetErrorY(ip);
    cout << " i=" << ip
	 << " x=" << x
	 << " y=" << y
	 << " ex=" << ex
	 << " ey=" << ey
	 << endl;

  }
  return 0;
}

// _______________________________________________________

int AbsHisto(TH1F *hist)
{

  if (hist) {
  int nbins =  hist -> GetNbinsX();

    for (int i = 0; i <= nbins + 1; ++i) {
      double ynew = TMath::Abs(hist -> GetBinContent(i));
      //      double errnew = hist -> GetBinError(i);
      hist -> SetBinContent(i, ynew);
      //      hist -> SetBinError(i, errnew);
    }
    hist -> Scale(1.);
  }
  return 0;
}


  // ____________________________________________
  
  double GetMedian(TH1 *hist)
  {

    if (!hist)
      return 0.;

    double x = 0.5;  // position where to compute the quantiles in [0,1]
    double y;  // array to contain the quantiles
    hist->GetQuantiles(1,&y,&x);
    return y;

  }

// ___________________________________________________________

// ____________________________________________

TH2F * MakeIntHisto(TH2F *input) 
{
  if (!input)
    return 0;

  cout << "Making bin-like migration matrix..." << endl;

  int nx = input -> GetXaxis() -> GetNbins();
  int ny = input -> GetYaxis() -> GetNbins();
  TH2F *migra = new TH2F(Form("%s_labels", input -> GetName()), input -> GetTitle(), nx, 0, nx, ny, 0, ny);
  cout << "Setting labels..." << endl;
  for (int i = 1; i <= migra -> GetXaxis()->GetNbins(); i++) 
    migra -> GetXaxis()->SetBinLabel(i,Form("%4.0f - %4.0f", input -> GetXaxis()->GetBinLowEdge(i), input -> GetXaxis()->GetBinUpEdge(i)));
  for (int i = 1; i <= migra -> GetYaxis()->GetNbins(); i++) 
    migra -> GetYaxis()->SetBinLabel(i,Form("%4.0f - %4.0f", input -> GetYaxis()->GetBinLowEdge(i), input -> GetYaxis()->GetBinUpEdge(i)));
  
  migra->GetXaxis()->SetLabelSize(0.04);
  migra->GetYaxis()->SetLabelSize(0.04);

  cout << "Setting contents..." << endl;
  for (int i = 1; i <= migra -> GetXaxis()->GetNbins(); i++) {
    for (int j = 1; j <= migra -> GetYaxis()->GetNbins(); j++) {
      migra -> SetBinContent(i, j, input -> GetBinContent(i, j));
      migra -> SetBinError(i, j, input -> GetBinError(i, j));
    }
  }
  migra -> Scale(1.);
  return migra;

}

// ___________________________________________________________

} // namespace
