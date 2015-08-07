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

double getArea(double x1, double x2, double y1, double y2, bool ValuesAreAtCentreOfBin = false);

// _____________________________________________________________

// xbins - array of new binning
TH1D* MakeHisto(TString name, TString title, int nbins, double *xbins, MyDataType xsect, int debug = 2, bool CorrectFirstBin = false, bool ValuesAreAtCentreOfBin = false)
  {

    TH1D *hist = new TH1D(name, title, nbins, xbins);
    hist -> Sumw2();

    int theoryBins = xsect.size();
    int NtheoryBins = theoryBins-1;

    cout << "MakeHisto: theoryBins=" << theoryBins << endl;

    // if (ValuesAreAtCentreOfBin) {
    //   cout << "OK, assuming we work with bin centres, increasing bin number for computational purposes..." << endl;
    //   NtheoryBins++;
    // }

    // for loop that runs though all the theory entries
    for (int j = 0; j < NtheoryBins; j++) {
      // for loop that runs through all of the bins
      if (debug > 2)
      	cout << "Computing the area..." 
      	     << endl;
      double area=0;
      double x1 = xsect[j][0];
      double y1 = xsect[j][1];
      double x2 = x1;
      double y2 = y1;
      //      if (not ValuesAreAtCentreOfBin or j == 0) {
      x2 = xsect[j + 1][0];
      y2 = xsect[j + 1][1];
      //} else {
      //x1 = xsect[j - 1][0];
      // }
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

      // integrates each bin using trapezoidal approximation and puts value in each bin
      // loop over the requested bins:
      for (int i = 1; i <= nbins; i++) {

	double lowEdge = hist ->GetBinLowEdge(i);
	double highEdge = lowEdge + hist->GetBinWidth(i);

	double theorylowEdge = x1 - binwidth/2.;
	double theoryhighEdge = x1 + binwidth/2.;

	if (debug > 2)
	  cout << "Theory bin edges: [" << theorylowEdge << "," << theoryhighEdge << "]" << endl;

	if ((theorylowEdge>=lowEdge)&& (theoryhighEdge<=highEdge)){ // if theory completely contained in bin 
	  hist -> AddBinContent(i, area);
	  if (debug > 1)
	    cout << "Adding Bin j=" << j
		 << " edged [" << theorylowEdge << ","  << theoryhighEdge << "]"
		 << " centered at " << x1
		 << " Content: " << area
		 << " computed from xsect of " << y1
		 << " to bin" << i 
		 << " to Analysis bin edged [" << lowEdge
		 << "," << highEdge << "]"
		 << endl; 
	  break;
	}
	else if((theorylowEdge<highEdge)&&(theoryhighEdge>highEdge)){
	  double x3 = highEdge;
	  double y3 = ((x3-x1)/(x2-x1))*(y2-y1)+y1;
	  // if we want to use the trapezoidal approximation for bin splitting:
	  double a1 = getArea(x1,x3,y1,y3, ValuesAreAtCentreOfBin);
	  double a2 = getArea(x3,x2,y3,y2, ValuesAreAtCentreOfBin);
	  if (ValuesAreAtCentreOfBin) {
	    a1 = area * (highEdge-theorylowEdge) / (theoryhighEdge - theorylowEdge);
	    a2 = area * (theoryhighEdge - highEdge) / (theoryhighEdge - theorylowEdge);
	  }
	  hist -> AddBinContent(i,a1);
	  hist -> AddBinContent(i+1,a2);
	  cout << "Splitting Bin j=" << j
	       << " edges: " << theorylowEdge << "," << theoryhighEdge
	       << " Content: a=" << area << " to "
	       << a1  << " to bin" << i  << " and " 
	       << a2  << " to bin" << i+1
	       << " fractions f1,f2=" << a1/area << "," << a2/area
	       << endl; 
	  break;
	}
      } // i, over requested bins  
      if ( j < NtheoryBins and xsect[j + 1][0] >= xbins[nbins]) {
	hist -> AddBinContent(nbins, area);
	if (debug > 1)
	  cout << "LAST Adding Bin Content: " << area 
	       << " computed from xsect of " << xsect[j][1] << " to bin" << nbins
	    //	       << " edged [" << lowEdge
	    //	       << "," << highEdge << "]"
	    //	       << endl; 
	       << endl;
      } // if
    } // j, over theory bins

    // divide by bin width 
    double width;
    int ibin = 1;
    int start = 1;
    
    
    // WRONG correction for the first bin, where theory starts later in pT, so we need to divide by smaller bin width:
    //  COMMENTED ON PURPOSE!!
    /* 
    if (  CorrectFirstBin ) {
      width =  xbins[1] - xsect[0][0];
      if (debug > 1)
	cout << "First bin width: " << width << endl;
      hist -> SetBinContent(ibin, (hist -> GetBinContent(ibin)) / width);
      // go over bins except for first and last, which are treated above and below
      start = 2;
    }
    */

    // go over bins except for the last, which is treated later
    cout << "startbin=" << start
	 << "nbins=" << nbins
	 << endl;
    for (ibin = start; ibin < nbins+1; ibin++) {
      width = hist -> GetBinWidth(ibin);
      if (debug > 0)
	cout << "Dividing bin " << ibin << " by width " << width << endl;
      hist -> SetBinContent(ibin, (hist -> GetBinContent(ibin)) / width);
    }

    if (ibin < nbins) {
      // correction for the last bin, where theory goes beyond our pT range
      // and so we need to divide by the bin width with righr edge being the rightmost theory bin
      width = xsect[theoryBins-1][0] - xbins[nbins-1];
      if (debug > 0)
	cout << "Last bin width: " << width << endl;
      hist -> SetBinContent(nbins, (hist -> GetBinContent(nbins)) / width);
    }

    cout << "integral of histo: " << hist->Integral("width") << endl;

    return hist;
  }

// _____________________________________________________________

double getArea(double x1, double x2, double y1, double y2, bool ValuesAreAtCentreOfBin){
  double area = 0;
  double rect = fabs(x2 - x1) * y1;
  if (ValuesAreAtCentreOfBin)
    return rect;
  double tri = 0.5*(y2 - y1) * fabs(x2 - x1); 
  area = rect + tri;

  /*
  // overcomplicated:
  //  double tri = 0.5*(fabs(y2 - y1) * fabs(x2 - x1)); 
  //  never used double midpoint = 0.5*(x2-x1)+x1;
  if(y1<y2)
  area = rect + tri;
  else if(y2<y1)
  area = rect - tri;
  */  

  return area;
}


// _____________________________________________________________
// _____________________________________________________________
// _____________________________________________________________
