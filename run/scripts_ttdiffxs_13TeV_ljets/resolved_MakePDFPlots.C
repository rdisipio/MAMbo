#include <TH1D.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TFile.h>
#include <TLegend.h>
#include "AtlasStyle.h"
#include <iostream>

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
		if( i != 0 ) 
		{
			h_pdf[i]->SetLineWidth(1);
			
		h_pdf[i]->Divide( h_pdf[0] );
		}
		else 
		{
			h_pdf[i]->SetLineWidth(2);
		}
		h_pdf[i]->SetLineColor( kBlue + i );
	}
	string ct10path = "output/" + level + "/tt_diffxs_13TeV.mc.AFII.DiTop.410003.co." + level + ".nofullhad.histograms.root";
	TFile * ct10File = TFile::Open( ct10path.c_str() );	
	TH1D * h_ct10 = (TH1D*) ct10File->Get( histoPath.c_str() )->Clone();
	h_ct10->SetLineWidth( 2 );
	h_ct10->SetLineColor( kRed );
	h_ct10->Divide( h_pdf[0] );
	h_pdf[0]->Divide( h_pdf[0] );
	
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
	if ( level == "nominal" ) level = "reco";
	else level = "particle";
	h_ct10->GetXaxis()->SetTitle( ( particle + " " + variable + "(" + level + " level)" ).c_str() ); 
	h_ct10->GetYaxis()->SetTitle( "Ratio over PDF4LHC15_nlo_30 central" ); 
	h_ct10->Draw( "hist" );
	for( int i = 1; i <= 30; ++i )
	{
		h_pdf[i]->Draw( "hist same" );
	}
	h_pdf[0]->Draw( "hist same" );
	legend->Draw();
	c->Print( ( particle + "_" + variable + "_" + level + ".png" ).c_str() );
}