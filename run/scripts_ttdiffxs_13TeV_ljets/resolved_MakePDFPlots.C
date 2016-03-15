#include <TH1D.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TFile.h>
#include <TLegend.h>
#include "AtlasStyle.h"
#include <iostream>
#include <cmath>
using namespace std;


int main( int nargs, char **args )
{
  SetAtlasStyle();	
  string particle = args[1];
  string variable = args[2];
  string level = args[3];
  // gROOT->LoadMacro("AtlasUtils.C");
	string pdfPaths[31];
	cout << sizeof( pdfPaths ) / sizeof( string ) << endl;
	TFile * pdfFiles[31];
	TH1D * h_pdf[31];
	TH1D * h_totalUp;
	TH1D * h_totalDown;
	double * shifts_up;
	double * shifts_down;
	int nbins;
	string histoPath = (level == "nominal" ) ? "reco/4j2b/" + particle + "/" + variable :  "particle/4j2b/" + particle + "/" + variable;
	for( int i = 0; i <= 30; ++i )
	{
		char temp[1000];
		sprintf( temp, "output/PDF4LHC15_nlo_30_%i_%s/tt_diffxs_13TeV.mc.AFII.DiTop.410003.co.PDF4LHC15_nlo_30_%i_%s.nofullhad.histograms.root", i, level.c_str(), i, level.c_str() );
		cout << "Opening " << temp << endl;
		pdfPaths[ i ] = string( temp );
		pdfFiles[ i ] = TFile::Open( temp );
		pdfFiles[i]->cd();
		h_pdf[i] = (TH1D*) gDirectory->Get( histoPath.c_str() )->Clone();
		if( i == 0 ) 
		{
			h_pdf[i]->SetLineWidth(2);
			h_totalDown = (TH1D*) h_pdf[0]->Clone();
			h_totalUp = (TH1D*) h_pdf[0]->Clone();
			nbins = h_pdf[0]->GetNbinsX();
			shifts_down = new double[nbins];
			shifts_up = new double[nbins];
			for( int b = 0; b < nbins; ++b )
			{
				shifts_down[b] = 0;
				shifts_up[b] = 0;
			}		

		}
		else 
		{
			h_pdf[i]->SetLineWidth(1);
				
			double difference;
			for( int b = 0; b < nbins; ++b )
			{
				difference = h_pdf[i]->GetBinContent(b+1) - h_pdf[0]->GetBinContent(b+1);
				shifts_up[b] += difference*difference;
				shifts_down[b] += difference*difference;
				
			}
			h_pdf[i]->Divide( h_pdf[0] );
		}
		h_pdf[i]->SetLineColor( kBlue + i );

	}
	string ct10path = "output/" + level + "/tt_diffxs_13TeV.mc.AFII.DiTop.410003.co." + level + ".nofullhad.histograms.root";
	TFile * ct10File = TFile::Open( ct10path.c_str() );	
	TH1D * h_ct10 = (TH1D*) ct10File->Get( histoPath.c_str() )->Clone();
	h_ct10->SetLineWidth( 2 );
	h_ct10->SetLineColor( kRed );
	h_ct10->Divide( h_pdf[0] );
	
	//total unc
	for( int b = 0; b < nbins; ++b )
	{
		h_totalUp->SetBinContent( b+1, h_pdf[0]->GetBinContent(b +1 ) + sqrt( shifts_up[b] ) );
		h_totalDown->SetBinContent( b+1, h_pdf[0]->GetBinContent(b + 1) - sqrt( shifts_down[b] ) );
	}
	h_totalUp->Divide( h_pdf[0] );
	h_totalDown->Divide( h_pdf[0] );
	h_pdf[0]->Divide( h_pdf[0] );
	h_totalDown->SetLineWidth( 2 );
	h_totalUp->SetLineWidth( 2 );
	h_totalDown->SetLineColor( kBlack );
	h_totalUp->SetLineColor( kBlack );
	TH1D * h_ct10_up = (TH1D*) h_ct10->Clone();
	TH1D * h_ct10_down = (TH1D*) 	h_pdf[0]->Clone();
	
	h_ct10_down->Add( h_ct10_up, -1 );
	h_ct10_down->Add( h_pdf[0] );
	h_ct10_down->SetLineWidth( 2 );
	h_ct10_down->SetLineColor( kRed );	
	
	
	
	
	TCanvas * c = new TCanvas();
		TLegend* legend = new TLegend(0.5,0.75,0.7,0.90);
     legend->SetBorderSize(0);  // no border
     legend->SetBorderSize(0);  // simple border, but no drop shadow
     legend->SetFillColor(0);   // Legend background should be white
     legend->SetTextSize(0.04); // Increase entry font Width!
	//h_alpgen_num
	legend->Clear();
	legend->AddEntry( h_ct10, "MC@NLO+HPP (CT10)", "l" );
	legend->AddEntry( h_pdf[0], "MC@NLO+HPP (PDF4LHC15_nlo_30 central)", "l" );
	legend->AddEntry( h_totalUp, "Total PDF4LHC15_nlo_30 uncertainty", "l" );
	if ( level == "nominal" ) level = "reco";
	else level = "particle";
	h_ct10->GetXaxis()->SetTitle( ( particle + " " + variable + "(" + level + " level)" ).c_str() ); 
	h_ct10->GetYaxis()->SetTitle( "Ratio over PDF4LHC15_nlo_30 central" ); 
	// h_ct10->SetMaximum(  1 +  2 * ( h_ct10->GetMaximum() - 1 ) ); 
	// h_ct10->SetMinimum(  1 -2 * ( 1 -  h_ct10->GetMinimum() ) ); 
	h_ct10->SetMaximum(  1.1 ); 
	h_ct10->SetMinimum(  0.9 ); 
	h_ct10->Draw( "hist" );
	h_ct10_down->Draw( "same hist" );
	for( int i = 1; i <= 30; ++i )
	{
		h_pdf[i]->Draw( "hist same" );
	}
	h_totalDown->Draw( "hist same" );
	h_totalUp->Draw( "hist same" );
	h_pdf[0]->Draw( "hist same" );
	legend->Draw();
	c->Print( ( particle + "_" + variable + "_" + level + ".pdf" ).c_str() );
}
