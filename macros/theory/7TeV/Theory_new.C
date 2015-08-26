// Kelsey Bilsback
// June 14, 2012
//
// This macro makes a pointer to a histogram that contains rebinned theory data


#include "TH1D.h"
#include <iostream>
#include <vector>

using namespace std;

typedef vector<vector<double> > MyDataType;

// _____________________________________________________________

double getArea(double x1, double x2, double y1, double y2, bool ValuesAreAtCentreOfBin = false)
{
  double area = 0;
  double rect = fabs(x2 - x1) * y1;
  if (ValuesAreAtCentreOfBin)
    return rect;
  //double tri = (y2 - y1) * fabs(x2 - x1); 
  double tri = 0.5 * (y2 - y1) * fabs(x2 - x1); 
  area = rect + tri;
  return area;
}


// _____________________________________________________________

// xbins - array of new binning
TH1D* MakeHisto(TString name, TString title, int nbins, double *xbins, MyDataType xsect, int debug = 2, bool CorrectFirstBin = false, bool ValuesAreAtCentreOfBin = false)
  {

    TH1D *hist = new TH1D(name, title, nbins, xbins);
    hist -> Sumw2();

    int theoryBins = xsect.size();
    int NtheoryBins = theoryBins-1;

    // walk the coarse binned histo bins:
    int ibin = 1;

    cout << "MakeHisto: theoryBins=" << theoryBins << endl;

    // for loop that runs though all the theory entries
    for (int j = 0; j < NtheoryBins-1; j++) {

      if (debug > 2)
      	cout << "Computing the area..." 
      	     << endl;
      double area=0;
      double x1 = xsect[j][0];
      double x2 = xsect[j + 1][0];
      double y1 = xsect[j][1];
      double y2 = xsect[j + 1][1];

      double binwidth = x2-x1;
      area = getArea(x1,x2,y1,y2, ValuesAreAtCentreOfBin);

      if (debug > 1)
	cout << "area=" << area 
	     << " x1=" << x1
	     << " x2=" << x2
	     << " y1=" << y1
	     << " y2=" << y2
	     << " binwidth=" << binwidth
	     << endl;

	double hlowEdge = hist ->GetBinLowEdge(ibin);
	double hhighEdge = hlowEdge + hist->GetBinWidth(ibin);
	double theorylowEdge = x1;
	double theoryhighEdge = x2;

	if ( (hlowEdge > theorylowEdge) and (theoryhighEdge < hhighEdge)) {
	  // part of the theory bin is under the histo low edge
	  // need to split, and throw away the underflow:
	  double areaUp = getArea(hlowEdge,x2,y1,y2, ValuesAreAtCentreOfBin);
	  hist -> AddBinContent(ibin, areaUp);
	} else if ( (hlowEdge <= theorylowEdge) and (theoryhighEdge < hhighEdge) ) {
	  // theory bin fuly contained in histogram bin, just add bin content
	  hist -> AddBinContent(ibin, area);
	} else if ( (hlowEdge < theorylowEdge) and (theoryhighEdge >= hhighEdge) ) {
	  // high theory bin edge is in the next histo bin 
	  // need to split, and shift ibin:
	  double xmiddle = hhighEdge;
	  double area1 = getArea(x1,xmiddle,y1,y2, ValuesAreAtCentreOfBin);
	  hist -> AddBinContent(ibin, area1);
	  ibin++;
	  // just don't fill the overflow bin:
	  if (ibin <= hist -> GetNbinsX() ) {
	    double area2 = getArea(xmiddle,x2,y1,y2, ValuesAreAtCentreOfBin);
	    hist -> AddBinContent(ibin, area2);
	  } else {
	    cout << "Breaking, in order not to fill overflows!" << endl;
	    break;
	  }
	}  else {
	  cerr << "THIS SHOULD NOT HAPPEN!" 
	       << " hlowEdge=" << hlowEdge
	       << " hhighEdge=" << hhighEdge
	       << " theorylowEdge=" << theorylowEdge
	       << " theoryhighEdge=" << theoryhighEdge
	       << endl;
	}


    } // theory bins

    // divide by bin width 
    for (int ibin = 1; ibin < nbins+1; ibin++) {
      double width = hist -> GetBinWidth(ibin);
      if (debug > 0)
	cout << "Dividing bin " << ibin << " by width " << width << endl;
      hist -> SetBinContent(ibin, (hist -> GetBinContent(ibin)) / width);
    }
    cout << "integral of histo: " << hist->Integral("width") << endl;

    return hist;
  }

// _____________________________________________________________
// _____________________________________________________________
// _____________________________________________________________
