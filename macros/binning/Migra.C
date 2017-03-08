
// code by Josef Pacalt, modified by Jiri Kvita

#include "includes.h"
#include "TColor.h"
#include "../../share/AtlasUtils.h"
#include "../../share/AtlasStyle.h" 

using namespace std;

const double EPSILON = 1.e-9;

//gROOT->SetBatch(1);

// ____________________________________________________________________________

void PercDraw(const TH2D *resmat)
{  
  TH2D *percmat=(TH2D*)resmat->Clone("percmat");
  TString name=resmat->GetTitle();
  Int_t nbins=resmat->GetXaxis()->GetNbins();

  for (Int_t i=0;i<nbins;i++)
  {
     for(Int_t j=0;j<nbins;j++)
    {
      Double_t slicesum=0;

      for (Int_t u=0;u<nbins;u++)
      {
	slicesum+=resmat->GetBinContent(u+1,i+1);
      }
      Double_t percentage;
         
      
      percentage = (resmat->GetBinContent(j+1,i+1)) / slicesum * 100;  
      if (percentage < 0.5)
	percentage = 0.;
      percmat->SetBinContent(j+1,i+1,percentage);
      if (slicesum < EPSILON)
	percmat->SetBinContent(j+1,i+1,0.);
	
    }
  }
  percmat->GetZaxis()->SetRangeUser(0., 100.);
  percmat->GetZaxis()->SetTitle("Migration [%]    ");
  percmat->GetZaxis()->SetLabelSize(0.045);
  percmat->GetYaxis()->SetLabelSize(0.045);
  percmat->GetXaxis()->SetLabelSize(0.045);
  percmat->GetZaxis()->SetTitleSize(0.045);
  percmat->GetZaxis()->SetTitleOffset(1.13);
  percmat->GetYaxis()->SetTitleOffset(1.21);
  percmat->Draw("colz");
  percmat->Draw("sametext");
  cout << "Setting labels..." << endl;
  percmat->GetXaxis()->SetLabelOffset(999); // moving labels out of sight!:)
  percmat->GetYaxis()->SetLabelOffset(999); // moving labels out of sight!:)

 return;
}//end of the function for percentage calculation and drawing over resmat

// ____________________________________________________________________________

void normalize_columns( TH2D * h )
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

// HERE
// ____________________________________________________________________________

TH2D * MakeIntHisto(TH2D *input)
{
  if (!input)
    return 0;

  cout << "Making bin-like migration matrix..." << endl;

  int nx = input -> GetXaxis() -> GetNbins();
  int ny = input -> GetYaxis() -> GetNbins();
  TH2D *migra =new TH2D(Form("%s_labels", input -> GetName()), input -> GetTitle(), nx, 0, nx, ny, 0, ny); //Tady se tvoří popisky, když jsou moc dlouhý tak je to natočí
  
  
  cout << "Setting contents..." << endl;
  cout << migra->GetName() << endl;
  for (int i = 1; i <= migra -> GetXaxis()->GetNbins(); i++) {
    cout << "Line" << i;
    for (int j = 1; j <= migra -> GetYaxis()->GetNbins(); j++) {
      migra -> SetBinContent(i, j, input -> GetBinContent(i, j));
      migra -> SetBinError(i, j, input -> GetBinError(i, j));
      cout << " " <<  migra -> GetBinContent(i,j);
    }
    cout << endl;
  }
  migra -> Scale(1.);
  migra->GetXaxis()->SetNdivisions(nx,0,0);
  migra->GetYaxis()->SetNdivisions(ny,0,0);
//   cout << "Setting labels..." << endl;

  
//   for (int i = 1; i <= migra -> GetXaxis()->GetNbins(); i++)
//   {
//     if (input->GetXaxis()->GetBinUpEdge(nx)-input->GetXaxis()->GetBinLowEdge(1)<30)
//     {
//     migra -> GetXaxis()->SetBinLabel(i,Form("%4.2f", input -> GetXaxis()->GetBinLowEdge(i)));
// 
//     }
//    else
//     {
//     migra -> GetXaxis()->SetBinLabel(i,Form("%4.0f", input -> GetXaxis()->GetBinLowEdge(i)));
//     }
//      
//   }
//   
//     for (int i = 1; i <= migra -> GetYaxis()->GetNbins(); i++)
//     { 
//      if (input->GetYaxis()->GetBinUpEdge(ny)-input->GetYaxis()->GetBinLowEdge(1)<30) 
//      {
//     migra -> GetYaxis()->SetBinLabel(i,Form("%4.2f", input -> GetYaxis()->GetBinLowEdge(i)));
//      }
//     
//     else
//      {
//     migra -> GetYaxis()->SetBinLabel(i,Form("%4.0f", input -> GetYaxis()->GetBinLowEdge(i)));
//      }
//     }
// 
//   migra->GetXaxis()->SetLabelSize(0.044);
//   migra->GetYaxis()->SetLabelSize(0.044);
//   
//

   return migra;
 }

//____________________________________________________________________________
void normalize_rows( TH2D * h )
{
  //cout<<h<<endl;
  const int nbins = h->GetNbinsX();
 
  for( int iy = 0 ; iy < nbins ; ++iy ) {

    double sum = 0.;
    for( int ix = 0 ; ix < nbins ; ++ix ) {
      sum += h->GetBinContent( ix+1, iy+1 );
    }

    for( int ix = 0 ; ix < nbins ; ++ix ) {
      const double y_old = h->GetBinContent( ix+1, iy+1 );
      
      double y_new = y_old / sum;
      if (sum==0) y_new=0;
      
      h->SetBinContent( ix+1, iy+1, y_new );
    }

  }
}

// ____________________________________________________________________________
// used for reco-particle, the main migrations:

void basic_plot( const char * hname, const char * htitle = "", TString channel = "co", TString topotag = "Resolved")
{
   

 // gROOT->Macro("./rootlogon.C");
  gROOT->LoadMacro( "../../share/AtlasUtils.C" );
  gROOT->LoadMacro( "../../share/rootlogon.C" );
  gROOT->LoadMacro( "../../share/AtlasStyle.C" );
  SetAtlasStyle();


   gStyle->SetPaintTextFormat("4.0f");
   gStyle->SetOptStat(0);
   gStyle->SetMarkerSize(1.7);
   gStyle->SetOptTitle(0);

   const int Number = 3;
   Double_t Red[Number]    = { 1.00, 0.43, 0.05};
   Double_t Green[Number]  = { 1.00, 0.78, 0.59};
   Double_t Blue[Number]   = { 1.00, 0.69, 0.53};

   Double_t Length[Number] = { 0.00, 0.25, 1.00 };
   Int_t nb=100;
   TColor::CreateGradientColorTable(Number,Length,Red,Green,Blue,nb);
    
  TH2D * h = (TH2D*)gDirectory->Get( hname );
  
  int nbins = h->GetXaxis()->GetNbins();
  
  normalize_rows( h );

  // computation of the bin edges! JKJK
  double xvals[256];
  for(int i = 0; i < nbins;i++){
    xvals[i] = h -> GetXaxis()->GetBinLowEdge(i+1);
  }
  xvals[nbins] = h->GetXaxis()->GetBinUpEdge(nbins);  
  
  TH2D *migra=MakeIntHisto(h);
  
  char buf[128];
  sprintf( buf, "%s (detector level)    ", htitle );
  migra->GetXaxis()->SetTitle( buf );
  migra->GetXaxis()->SetTitleOffset( 1.1 );
  sprintf( buf,	"%s (particle level)    ", htitle );
  migra->GetYaxis()->SetTitle( buf );
  migra->GetYaxis()->SetTitleOffset( 1.1 );

  TCanvas * c = new TCanvas("c", "canv", 800, 800 );
  gPad->SetLeftMargin( 0.13 );
  gPad->SetRightMargin( 0.15 );
  gPad->SetBottomMargin( 0.15 );
  gPad->SetTopMargin( 0.13 );

  migra->SetMaximum( 1. );
  migra->SetMinimum( 0. );
  
  
  migra->SetContour(nb);
 // migra->Draw( "colz" );
  
  PercDraw(migra);
  
    TText labelX,labelY;
    labelX.SetTextSize(0.045);// JKJK commented 0.028
    labelX.SetTextAlign(23);
    labelY.SetTextSize(0.045);// JKJK commented 0.028
    labelY.SetTextAlign(32);

    // HERE
  Double_t ylabel = migra->GetYaxis()->GetBinLowEdge(1) - 0.2*(migra->GetYaxis()->GetBinWidth(1));// custom y
  Double_t xlabel = migra->GetXaxis()->GetBinLowEdge(1) - 0.2*(migra->GetXaxis()->GetBinWidth(1));// custom x

   for (Int_t k=0;k<=nbins;k++)
   {
      Double_t xlow = xvals[k];
      Double_t ynew = migra->GetYaxis()->GetBinLowEdge(k+1);
      Double_t xnew = migra->GetXaxis()->GetBinLowEdge(k+1);
      if (xvals[nbins]-xvals[0]<30)
      {	
	// JKJK hack: only odd:
	// // ??if (k % 2 == 1) {
	if (topotag == "Resolved" && (k % 2 == 1) ) {
	  labelX.DrawText(xnew,ylabel,Form("%4.1f",xlow));
	  labelY.DrawText(xlabel,ynew,Form("%4.1f",xlow));
	}
      }
      else
      {
	// JKJK hack: only odd:
	if (topotag == "Resolved" && (k % 2 == 1) ) {
	  labelX.DrawText(xnew,ylabel,Form("%4.0f",xlow));
	  labelY.DrawText(xlabel+0.12,ynew,Form("%4.0f",xlow));
	}
      }
   }
 //gPad->RedrawAxis();
  
  // double x = 0.15; // eta distributions
  //  double x = 0.45;
  // double y = 0.93;
  double xx = 0.17;
  double yy = 0.75;
  if (topotag == "Resolved")
    yy =  0.80;
  double xxoffset = 0.31-0.16;
  double yyoffset = 0.05;
  ATLAS_LABEL( xx, yy, kBlack );
  ////
  //  myText( 0.31, 0.80, kBlack, " Simulation Internal" );
  //myText( xx+xxoffset, 0.80, kBlack, " Simulation Preliminary" );
  myText( xx+xxoffset, yy, kBlack, " Simulation" );
  ///!!!
  myText( xx, yy-1*yyoffset, kBlack, "Internal" );
  //  myText( xx, 0.80-yyoffset, kBlack, "Preliminary" );
  //  myText( 0.31, 0.74, kBlack, " Internal" );
  myText( xx, yy-2*yyoffset, kBlack, topotag );

  //const double rho = h->GetCorrelationFactor();
  //sprintf( buf, "correlation: %3.2f", rho );
  //myText(  0.7, 0.95, kBlack, buf );

  char pname[128];
  sprintf( pname, "migration_%s_%s.png", hname, channel.Data() );
  c->SaveAs( pname );
  sprintf( pname, "migration_%s_%s.pdf", hname, channel.Data() );
  c->SaveAs( pname );
}


// ____________________________________________________________________________
// parton level?

void basic_plot_par( const char * hname, const char * htitle = "", TString channel = "co", TString topotag = "Resolved" ) // topotag not used!
{
   
   gStyle->SetPaintTextFormat("4.0f");
   gStyle->SetOptStat(0);
   gStyle->SetMarkerSize(1.5);
   gStyle->SetOptTitle(0);
   static const UInt_t Number = 3;
   Double_t Red[Number]    = { 1.00, 0.78, 0.59};
   Double_t Green[Number]  = { 1.00, 0.69, 0.53};
   Double_t Blue[Number]   = { 1.00, 0.43, 0.05};

   Double_t Length[Number] = { 0.00, 0.25, 1.00 };
   Int_t nb=100;
   TColor::CreateGradientColorTable(Number,Length,Red,Green,Blue,nb);
    

  //gROOT->Macro("./rootlogon.C");
  gROOT->LoadMacro("./AtlasUtils2.C");

  TH2D * h = (TH2D*)gDirectory->Get( hname );
  
  int nbins = h->GetXaxis()->GetNbins();
  
  normalize_rows( h );
  
  double xvals[256];
  for(int i =0;i<nbins;i++){xvals[i]=h->GetXaxis()->GetBinLowEdge(i+1);}
  xvals[nbins]=h->GetXaxis()->GetBinUpEdge(nbins);
  
  TH2D *migra=MakeIntHisto(h);
  char buf[128];
  
  sprintf( buf, "%s (particle level)", htitle );
  migra->GetXaxis()->SetTitle( buf );
  migra->GetXaxis()->SetTitleOffset( 1.1 );
  sprintf( buf,	"%s (parton level)", htitle );
  migra->GetYaxis()->SetTitle( buf );
  migra->GetYaxis()->SetTitleOffset( 1.1 );

  TCanvas * c = new TCanvas("c", "canv", 800, 600 );
  gPad->SetLeftMargin( 0.12 );
  gPad->SetRightMargin( 0.15 );
  gPad->SetBottomMargin( 0.15 );
  gPad->SetTopMargin( 0.10 );

  migra->SetMaximum( 1. );
  migra->SetMinimum( 0. );
  
  
  migra->SetContour(nb);
 // migra->Draw( "colz" );
  PercDraw(migra);
  
      TText labelX,labelY;
    labelX.SetTextSize(0.04);
    labelX.SetTextAlign(23);
    labelY.SetTextSize(0.04);
    labelY.SetTextAlign(32);
  
  Double_t ylabel = migra->GetYaxis()->GetBinLowEdge(1);//ještě pošibovat a je to
  Double_t xlabel = migra->GetXaxis()->GetBinLowEdge(1);//ještě pošibovat
  
   for (Int_t k=0;k<=nbins;k++)
   {
      Double_t xlow = xvals[k];
      Double_t ynew = migra->GetYaxis()->GetBinLowEdge(k+1);
      Double_t xnew = migra->GetXaxis()->GetBinLowEdge(k+1);
      if (xvals[nbins]-xvals[0]<30)
      {	
      labelX.DrawText(xnew,ylabel,Form("%4.2f",xlow));
      labelY.DrawText(xlabel,ynew,Form("%4.2f",xlow));
      }
      else
      {
      labelX.DrawText(xnew,ylabel,Form("%4.0f",xlow));
      labelY.DrawText(xlabel,ynew,Form("%4.0f",xlow));	
      }
   }
   
 //gPad->RedrawAxis();
  
 // double x = 0.15; // eta distributions
//  double x = 0.45;
 // double y = 0.93;
  ATLAS_LABEL( 0.05, 0.95, kBlack );
  // OBSOLETE  myText( 0.19, 0.95, kBlack, " Simulation Internal   l+jets" );
  //myText( 0.19, 0.95, kBlack, " Simulation" );
//  myText( x, y-0.05, kBlack, "Period A - Egamma stream" );
//  myText( x, y-0.05, kBlack, "e+jets 4j1b" );

  //const double rho = h->GetCorrelationFactor();
  //sprintf( buf, "correlation: %3.2f", rho );
  //myText(  0.7, 0.95, kBlack, buf );

  char pname[128];
  sprintf( pname, "migration_%s_%s.png", hname, channel.Data() );
  c->SaveAs( pname );
  sprintf( pname, "migration_%s_%s.pdf", hname, channel.Data() );
  c->SaveAs( pname );
}

// ____________________________________________________________________________
// reco-parton

void basic_plot_rp( const char * hname, const char * htitle = "", TString channel = "co", TString topotag = "Resolved" ) // topotag not used!
{
   
   gStyle->SetPaintTextFormat("4.0f");
   gStyle->SetOptStat(0);
   gStyle->SetMarkerSize(1.5);
   gStyle->SetOptTitle(0);
   static const UInt_t Number = 3;
   Double_t Red[Number]    = { 1.00, 0.78, 0.59};
   Double_t Green[Number]  = { 1.00, 0.43, 0.05};
   Double_t Blue[Number]   = { 1.00, 0.69, 0.53};

   Double_t Length[Number] = { 0.00, 0.25, 1.00 };
   Int_t nb=100;
   TColor::CreateGradientColorTable(Number,Length,Red,Green,Blue,nb);
    

 // gROOT->Macro("./rootlogon.C");
  gROOT->LoadMacro("./AtlasUtils.C");

  TH2D * h = (TH2D*)gDirectory->Get( hname );
  
  int nbins = h->GetXaxis()->GetNbins();
  
  normalize_rows( h );
  
  double xvals[256];
  for(int i =0;i<nbins;i++){xvals[i]=h->GetXaxis()->GetBinLowEdge(i+1);}
  xvals[nbins]=h->GetXaxis()->GetBinUpEdge(nbins);
  
  TH2D *migra=MakeIntHisto(h);
  char buf[128];
  
  sprintf( buf, "%s (detector level)", htitle );
  migra->GetXaxis()->SetTitle( buf );
  migra->GetXaxis()->SetTitleOffset( 1.1 );
  sprintf( buf,	"%s (parton level)", htitle );
  migra->GetYaxis()->SetTitle( buf );
  migra->GetYaxis()->SetTitleOffset( 1.1 );

  TCanvas * c = new TCanvas("c", "canv", 800, 800 );
  gPad->SetLeftMargin( 0.13 );
  gPad->SetRightMargin( 0.15 );
  gPad->SetBottomMargin( 0.15 );
  gPad->SetTopMargin( 0.13 );

  migra->SetMaximum( 1. );
  migra->SetMinimum( 0. );
  
  
  migra->SetContour(nb);
 // migra->Draw( "colz" );
  PercDraw(migra);
  
      TText labelX,labelY;
    labelX.SetTextSize(0.03);
    labelX.SetTextAlign(23);
    labelY.SetTextSize(0.03);
    labelY.SetTextAlign(32);
  
  Double_t ylabel = migra->GetYaxis()->GetBinLowEdge(1) - 0.2*(migra->GetYaxis()->GetBinWidth(1));//ještě pošibovat a je to
  Double_t xlabel = migra->GetXaxis()->GetBinLowEdge(1) - 0.2*(migra->GetXaxis()->GetBinWidth(1));//ještě pošibovat
  
   for (Int_t k=0;k<=nbins;k++)
   {
      Double_t xlow = xvals[k];
      Double_t ynew = migra->GetYaxis()->GetBinLowEdge(k+1);
      Double_t xnew = migra->GetXaxis()->GetBinLowEdge(k+1);
      if (xvals[nbins]-xvals[0]<30)
      {	
      labelX.DrawText(xnew,ylabel,Form("%4.2f",xlow));
      labelY.DrawText(xlabel,ynew,Form("%4.2f",xlow));
      }
      else
      {
      labelX.DrawText(xnew,ylabel,Form("%4.0f",xlow));
      labelY.DrawText(xlabel,ynew,Form("%4.0f",xlow));	
      }
   }
   
 //gPad->RedrawAxis();
  
 // double x = 0.15; // eta distributions
//  double x = 0.45;
 // double y = 0.93;
   double xx = 0.92 - 0.05;
   ATLAS_LABEL( 0.05, xx, kBlack );
  // obsolete?
  ///
  //  myText( 0.21, xx, kBlack, " Simulation Internal" );
  ///!!!
  //  myText( 0.21, xx, kBlack, " Simulation Preliminary" );
  myText( 0.21, xx, kBlack, " Simulation Internal" );
  //myText( 0.21, xx, kBlack, " Simulation" );
//  myText( x, y-0.05, kBlack, "e+jets 4j1b" );

  //const double rho = h->GetCorrelationFactor();
  //sprintf( buf, "correlation: %3.2f", rho );
  //myText(  0.7, 0.95, kBlack, buf );

  char pname[128];
  sprintf( pname, "migration_%s_%s.png", hname, channel.Data() );
  c->SaveAs( pname );
  sprintf( pname, "migration_%s_%s.pdf", hname, channel.Data() );
  c->SaveAs( pname );
}

void Migra(TString input, TString channel, TString topo = "4j2b")
{

  TFile *in=new TFile(input,"read");

  if (topo == "4j2b") {
    TString topotag = "Resolved";
   //reco to particle matrices
  basic_plot("reco/" + topo + "/topL/Matrix_reco_particle_pt","p_{T}^{t,lep} [GeV]", channel, topotag);
//  basic_plot("reco/" + topo + "/WL/Matrix_reco_particle_pt","p_{T}^{W,lep} [GeV]", channel, topotag);
//  basic_plot("reco/" + topo + "/WH/Matrix_reco_particle_pt","p_{T}^{W,had} [GeV]", channel, topotag);
//  basic_plot("reco/" + topo + "/WH/Matrix_reco_particle_absrap","|y|_{W,had}", channel, topotag);
//  basic_plot("reco/" + topo + "/WL/Matrix_reco_particle_absrap","|y|_{W,lep}", channel, topotag);
  basic_plot("reco/" + topo + "/topL/Matrix_reco_particle_m","m_{t,lep}", channel, topotag);
  basic_plot("reco/" + topo + "/topH/Matrix_reco_particle_m","m_{t,had}", channel, topotag); 
  basic_plot("reco/" + topo + "/topL/Matrix_reco_particle_absrap","|y|_{t,lep}", channel, topotag);
  basic_plot("reco/" + topo + "/topH/Matrix_reco_particle_pt","p_{T}^{t,had} [GeV]", channel, topotag);
  basic_plot("reco/" + topo + "/topH/Matrix_reco_particle_absrap","|y|_{t,had}", channel, topotag);
  basic_plot("reco/" + topo + "/tt/Matrix_reco_particle_pt","p_{T}^{t#bar{t}} [GeV]", channel, topotag);
  basic_plot("reco/" + topo + "/tt/Matrix_reco_particle_m","m_{t#bar{t}}", channel, topotag);
  basic_plot("reco/" + topo + "/tt/Matrix_reco_particle_absrap","|y|_{t#bar{t}}", channel, topotag);
  basic_plot("reco/" + topo + "/difference/Matrix_reco_particle_Pout","p_{out}^{t#bar{t}} [GeV]", channel, topotag);
  //basic_plot("reco/" + topo + "/difference/Matrix_reco_particle_absPout","|p_{out}^{t#bar{t}}| [GeV]", channel, topotag);  
  basic_plot("reco/" + topo + "/difference/Matrix_reco_particle_z_ttbar","z_{t#bar{t}}", channel, topotag);
  basic_plot("reco/" + topo + "/difference/Matrix_reco_particle_dPhi_ttbar","#Delta#phi_{t#bar{t}}", channel, topotag);
  basic_plot("reco/" + topo + "/difference/Matrix_reco_particle_HT_ttbar","H_{T}^{t#bar{t}} [GeV]", channel, topotag);
  basic_plot("reco/" + topo + "/difference/Matrix_reco_particle_HT_pseudo","H_{T}^{pseudo} [GeV]", channel, topotag);
  basic_plot("reco/" + topo + "/difference/Matrix_reco_particle_Chi_ttbar","#chi_{t#bar{t}}", channel, topotag);
  basic_plot("reco/" + topo + "/difference/Matrix_reco_particle_Yboost","y_{boost}", channel, topotag);
  basic_plot("reco/" + topo + "/difference/Matrix_reco_particle_R_Wb_had","p_{T}^{W,had}/p_{T}^{b,had}", channel, topotag);
  basic_plot("reco/" + topo + "/difference/Matrix_reco_particle_R_Wb_lep","p_{T}^{W,lep}/p_{T}^{b,lep}", channel, topotag);
  basic_plot("reco/" + topo + "/difference/Matrix_reco_particle_R_Wt_had","p_{T}^{W,had}/p_{T}^{t,had}", channel, topotag);
  basic_plot("reco/" + topo + "/difference/Matrix_reco_particle_R_Wt_lep","p_{T}^{W,lep}/p_{T}^{t,lep}", channel, topotag);
  basic_plot("reco/" + topo + "/difference/Matrix_reco_particle_R_lb","(p_{T}^{Wj1}+p_{T}^{Wj2})/(p_{T}^{bj1}+p_{T}^{bj2})", channel, topotag);


  /*
  
//   basic_plot("reco/" + topo + "/topL/Matrix_reco_particle_px","p_{x}^{lep} [GeV]", channel, topotag);
//   basic_plot("reco/" + topo + "/topL/Matrix_reco_particle_py","p_{y}^{lep} [GeV]", channel, topotag);
//   basic_plot("reco/" + topo + "/topL/Matrix_reco_particle_pz","p_{z}^{lep} [GeV]", channel, topotag);
//   basic_plot("reco/" + topo + "/topH/Matrix_reco_particle_px","p_{x}^{had} [GeV]", channel, topotag);
//   basic_plot("reco/" + topo + "/topH/Matrix_reco_particle_py","p_{y}^{had} [GeV]", channel, topotag);
//   basic_plot("reco/" + topo + "/topH/Matrix_reco_particle_pz","p_{z}^{had} [GeV]", channel, topotag);
// 
//   //parton to particle matrices
  basic_plot_par("particle/" + topo + "/topL/Matrix_particle_parton_pt","p_{T}^{t,lep} [GeV]", channel, topotag);
//  basic_plot_par("particle/" + topo + "/WL/Matrix_particle_parton_pt","p_{T}^{W,lep} [GeV]", channel, topotag);
//  basic_plot_par("particle/" + topo + "/WH/Matrix_particle_parton_pt","p_{T}^{W,had} [GeV]", channel, topotag);
//  basic_plot_par("particle/" + topo + "/WL/Matrix_particle_parton_absrap","|y|_{W,lep}", channel, topotag);
//  basic_plot_par("particle/" + topo + "/WH/Matrix_particle_parton_absrap","|y|_{W,had}", channel, topotag); 
  basic_plot_par("particle/" + topo + "/topL/Matrix_particle_parton_absrap","|y|_{t,lep}", channel, topotag);
  basic_plot_par("particle/" + topo + "/topH/Matrix_particle_parton_pt","p_{T}^{t,had} [GeV]", channel, topotag);
  basic_plot_par("particle/" + topo + "/topH/Matrix_particle_parton_absrap","|y|_{t,had}", channel, topotag);
  basic_plot_par("particle/" + topo + "/tt/Matrix_particle_parton_pt","p_{T}^{t#bar{t}} [GeV]", channel, topotag);
  basic_plot_par("particle/" + topo + "/tt/Matrix_particle_parton_m","m_{t#bar{t}}", channel, topotag);
  basic_plot_par("particle/" + topo + "/tt/Matrix_particle_parton_absrap","|y|_{t#bar{t}}", channel, topotag);
  basic_plot_par("particle/" + topo + "/difference/Matrix_particle_parton_Pout","p_{out}^{t#bar{t}} [GeV]", channel, topotag);
  //basic_plot_par("particle/" + topo + "/difference/Matrix_particle_parton_absPout","|p_{out}^{t#bar{t}}| [GeV]", channel, topotag);
  basic_plot_par("particle/" + topo + "/difference/Matrix_particle_parton_z_ttbar","z_{t#bar{t}}", channel, topotag);
  basic_plot_par("particle/" + topo + "/difference/Matrix_particle_parton_dPhi_ttbar","#Delta#phi_{t#bar{t}}", channel, topotag);
  basic_plot_par("particle/" + topo + "/difference/Matrix_particle_parton_HT_ttbar","H_{T}^{t#bar{t}} [GeV]", channel, topotag);
  basic_plot_par("particle/" + topo + "/difference/Matrix_particle_parton_Chi_ttbar","#chi_{t#bar{t}}", channel, topotag);
  basic_plot_par("particle/" + topo + "/difference/Matrix_particle_parton_Yboost","y_{boost}", channel, topotag);
  basic_plot_par("particle/" + topo + "/difference/Matrix_particle_parton_R_Wb_had","p_{T}^{W,had}/p_{T}^{b,had}", channel, topotag);
  basic_plot_par("particle/" + topo + "/difference/Matrix_particle_parton_R_Wb_lep","p_{T}^{W,lep}/p_{T}^{b,lep}", channel, topotag);
  basic_plot_par("particle/" + topo + "/difference/Matrix_particle_parton_R_Wt_had","p_{T}^{W,had}/p_{T}^{t,had}", channel, topotag);
  basic_plot_par("particle/" + topo + "/difference/Matrix_particle_parton_R_Wt_lep","p_{T}^{W,lep}/p_{T}^{t,lep}", channel, topotag);
  basic_plot_par("particle/" + topo + "/difference/Matrix_particle_parton_R_lb","(p_{T}^{Wj1}+p_{T}^{Wj2})/(p_{T}^{bj1}+p_{T}^{bj2})", channel, topotag);
//   basic_plot_par("particle/" + topo + "/topL/Matrix_particle_parton_px","p_{x}^{lep} [GeV]", channel, topotag);
//   basic_plot_par("particle/" + topo + "/topL/Matrix_particle_parton_py","p_{y}^{lep} [GeV]", channel, topotag);
//   basic_plot_par("particle/" + topo + "/topL/Matrix_particle_parton_pz","p_{z}^{lep} [GeV]", channel, topotag);
//   basic_plot_par("particle/" + topo + "/topH/Matrix_particle_parton_px","p_{x}^{had} [GeV]", channel, topotag);
//   basic_plot_par("particle/" + topo + "/topH/Matrix_particle_parton_py","p_{y}^{had} [GeV]", channel, topotag);
//   basic_plot_par("particle/" + topo + "/topH/Matrix_particle_parton_pz","p_{z}^{had} [GeV]", channel, topotag);
  
  //reco to parton matrices
  basic_plot_rp("reco/" + topo + "/topL/Matrix_reco_parton_pt_5","p_{T}^{t,lep} [GeV]", channel, topotag);
//  basic_plot_rp("reco/" + topo + "/WL/Matrix_reco_parton_pt_5","p_{T}^{W,lep} [GeV]", channel, topotag);
//  basic_plot_rp("reco/" + topo + "/WH/Matrix_reco_parton_pt_5","p_{T}^{H,lep} [GeV]", channel, topotag);
//  basic_plot_rp("reco/" + topo + "/WL/Matrix_reco_parton_absrap_5","|y|_{W,lep}", channel, topotag);
//  basic_plot_rp("reco/" + topo + "/WH/Matrix_reco_parton_absrap_5","|y|_{W,had}", channel, topotag);
  basic_plot_rp("reco/" + topo + "/topL/Matrix_reco_parton_absrap_5","|y|_{t,lep}", channel, topotag);
  basic_plot_rp("reco/" + topo + "/topH/Matrix_reco_parton_pt_5","p_{T}^{t,had} [GeV]", channel, topotag);
  basic_plot_rp("reco/" + topo + "/topH/Matrix_reco_parton_absrap_5","|y|_{t,had}", channel, topotag);
  basic_plot_rp("reco/" + topo + "/tt/Matrix_reco_parton_pt_5","p_{T}^{t#bar{t}} [GeV]", channel, topotag);
  basic_plot_rp("reco/" + topo + "/tt/Matrix_reco_parton_m_5","m_{t#bar{t}}", channel, topotag);
  basic_plot_rp("reco/" + topo + "/tt/Matrix_reco_parton_absrap_5","|y|_{t#bar{t}}", channel, topotag);
  basic_plot_rp("reco/" + topo + "/difference/Matrix_reco_parton_Pout_5","p_{out}^{t#bar{t}} [GeV]", channel, topotag);
  //basic_plot_rp("reco/" + topo + "/difference/Matrix_reco_parton_absPout_5","|p_{out}^{t#bar{t}}| [GeV]", channel, topotag); 
  basic_plot_rp("reco/" + topo + "/difference/Matrix_reco_parton_z_ttbar_5","z_{t#bar{t}}", channel, topotag);
  basic_plot_rp("reco/" + topo + "/difference/Matrix_reco_parton_dPhi_ttbar_5","#Delta#phi_{t#bar{t}}", channel, topotag);
  basic_plot_rp("reco/" + topo + "/difference/Matrix_reco_parton_HT_ttbar_5","H_{T}^{t#bar{t}} [GeV]", channel, topotag);
  basic_plot_rp("reco/" + topo + "/difference/Matrix_reco_parton_Chi_ttbar_5","#chi_{t#bar{t}}", channel, topotag);
  basic_plot_rp("reco/" + topo + "/difference/Matrix_reco_parton_Yboost_5","y_{boost}", channel, topotag);
  */
  
  } else {
    // boosted:
    // 1fj1b:
    TString topotag = "Boosted";
    // spaces after GeV important so that label does not overlap with axis numbers: hack by JK
    basic_plot("reco/" + topo + "/topH/Matrix_reco_particle_pt","p_{T}^{t,had} [GeV]  ", channel, topotag);
    basic_plot("reco/" + topo + "/topH/Matrix_reco_particle_absrap","|y|_{t,had}", channel, topotag);

  }

}
