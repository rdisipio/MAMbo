//gROOT->Macro("./rootlogon.C")
//gROOT->LoadMacro("./AtlasUtils.C");

void normalize_columns( TH2F * h )
{
  const int nbins = h->GetNbinsX();
  for( int ix = 0 ; ix < nbins ; ++ix ) {
    double sum = 0.;
    for( int iy = 0 ; iy < nbins ; ++iy ) {
      sum += h->GetBinContent( ix+1, iy+1 );
    }

    for( int iy = 0 ; iy < nbins ; ++iy ) {
      const double y_old = h->GetBinContent( ix+1, iy+1 );
      const double y_new = y_old / sum;
      h->SetBinContent( ix+1, iy+1, y_new );
    }

  }
}

void normalize_rows( TH2F * h )
{
  const int nbins = h->GetNbinsX();
  for( int iy = 0 ; iy < nbins ; ++iy ) {

    double sum = 0.;
    for( int ix = 0 ; ix < nbins ; ++ix ) {
      sum += h->GetBinContent( ix+1, iy+1 );
    }

    for( int ix = 0 ; ix < nbins ; ++ix ) {
      const double y_old = h->GetBinContent( ix+1, iy+1 );
      const double y_new = y_old / sum;
      h->SetBinContent( ix+1, iy+1, y_new );
    }

  }
}


void basic_plot( const char * hname, const char * htitle = "" )
{
  static const UInt_t Number = 3;
   Double_t Red[Number]    = { 1.00, 0.43, 0.05};
   Double_t Green[Number]  = { 1.00, 0.78, 0.59};
   Double_t Blue[Number]   = { 1.00, 0.69, 0.53};

   Double_t Length[Number] = { 0.00, 0.25, 1.00 };
   Int_t nb=100;
   TColor::CreateGradientColorTable(Number,Length,Red,Green,Blue,nb);
    

//  gROOT->Macro("./rootlogon.C");
  gROOT->LoadMacro("./AtlasUtils.C");

  TH2F * h = (TH2F*)gDirectory->Get( hname );
  
  normalize_rows( h );

  char buf[128];
  sprintf( buf, "%s (reco level)", htitle );
  h->GetXaxis()->SetTitle( buf );
  sprintf( buf,	"%s (particle level)", htitle );
  h->GetYaxis()->SetTitle( buf );

  TCanvas * c = new TCanvas("c", "canv", 1000, 800 );
  gPad->SetLeftMargin( 0.15 );
  gPad->SetRightMargin( 0.15 );
  gPad->SetBottomMargin( 0.14 );
  gPad->SetTopMargin( 0.10 );

  h->SetMaximum( 1. );
  h->SetMinimum( 0. );

  h->SetContour(nb);
  h->Draw( "colz" );
 
  double x = 0.15; // eta distributions
//  double x = 0.45;
  double y = 0.93;
  ATLAS_LABEL( x, y, kBlack );
  myText( x+0.14, y, kBlack, "Internal Simulation   e+jets 4j2b" );
//  myText( x, y-0.05, kBlack, "Period A - Egamma stream" );
//  myText( x, y-0.05, kBlack, "e+jets 4j1b" );

  const double rho = h->GetCorrelationFactor();
  sprintf( buf, "correlation: %3.2f", rho );
  myText(  0.60, 0.80, kBlack, buf );

  char pname[128];
  sprintf( pname, "img/migration_%s.png", hname );
  c->SaveAs( pname );
}
