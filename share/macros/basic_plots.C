//gROOT->Macro("./rootlogon.C")
//gROOT->LoadMacro("./AtlasUtils.C");

void basic_plot( const char * hname, const char * htitle = "", bool isLogScale = false )
{
//  gROOT->Macro("./rootlogon.C");
  gROOT->LoadMacro("./AtlasUtils.C");

  const double iLumi = 21000;
  const double xs_tt = 250.; //fix this
  const double br_tt_nofullhad = 0.543; 
 // TFile * f = TFile::Open( "TTbarResolved.histograms.root" );

//  char hpath[128];
//  sprintf( hpath, "cutflow/%s", hname );
//  TH1F * h = (TH1F*)f->Get( hpath );
  TH1F * h = (TH1F*)gDirectory->Get( hname );

  const double sf = xs_tt * iLumi * br_tt_nofullhad / h->Integral(); 
  h->Scale( sf );

  const int nbins = h->GetNbinsX();
  for( int i = 0 ; i < nbins ; ++i ) {
    const double y_old = h->GetBinContent( i+1 );
    const double y_new = y_old / h->GetBinWidth( i+1 );
    h->SetBinContent( i+1, y_new );

    const double e_old = h->GetBinError( i+1 );
    const double e_new = e_old / h->GetBinWidth( i+1 );
    h->SetBinError( i+1, e_new );
  }

  h->GetXaxis()->SetTitle( htitle );
  h->GetYaxis()->SetTitle( "Events" );

  TCanvas * c = new TCanvas("c", "canv", 1000, 800 );

  h->SetMaximum( 1.3 * h->GetMaximum() );

  h->Draw();
 
  double x = 0.15; // eta distributions
//  double x = 0.45;
  double y = 0.85;
  ATLAS_LABEL( x, y, kBlack );
  myText( x+0.13, y, kBlack, "Internal    #int Ldt = 21 fb^{-1}   #sqrt{s}=8 TeV" );
//  myText( x, y-0.05, kBlack, "Period A - Egamma stream" );
  myText( x, y-0.05, kBlack, "e+jets 4j1b" );

  if( isLogScale )  gPad->SetLogy();

  char pname[128];
  sprintf( pname, "img/%s.png", hname );
  c->SaveAs( pname );
}
