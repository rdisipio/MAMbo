#include <TH1D.h>
#include <TH2D.h>
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
  // gROOT->LoadMacro("AtlasUtils.C");
	string reco_pdfPaths[31];
	string particle_pdfPaths[31];
	TFile * reco_pdfFiles[31];
	TFile * particle_pdfFiles[31];
	TH1D * h_pdf_reco[31];
	TH1D * h_pdf_particle[31];
	TH1D * h_pdf_eff[31];
	TH1D * h_pdf_acc[31];
	TH2D * h_pdf_response[31];
	TH1D * h_eff_totalUp;
	TH1D * h_acc_totalUp;
	TH1D * h_eff_totalDown;
	TH1D * h_acc_totalDown;
	double * eff_shifts_up;
	double * eff_shifts_down;
	double * acc_shifts_up;
	double * acc_shifts_down;
	int nbins;
	string reco_histoPath =  "reco/4j2b/" + particle + "/" + variable ;
	string particle_histoPath =  "particle/4j2b/" + particle + "/" + variable;
	string response_histoPath ="reco/4j2b/" + particle + "/Matrix_reco_particle_" + variable;
	char histoname[20];
	for( int i = 0; i <= 30; ++i )
	{
		char temp[1000];
		sprintf( temp, "output/PDF4LHC15_nlo_30_%i_%s/tt_diffxs_13TeV.mc.AFII.DiTop.410003.co.PDF4LHC15_nlo_30_%i_%s.nofullhad.histograms.root", i, "nominal", i, "nominal" );
		cout << "Opening " << temp << endl;
		reco_pdfPaths[ i ] = string( temp );
		reco_pdfFiles[ i ] = TFile::Open( temp );
		reco_pdfFiles[i]->cd();
		h_pdf_reco[i] = (TH1D*) gDirectory->Get( reco_histoPath.c_str() )->Clone();
		nbins = h_pdf_reco[0]->GetNbinsX();
		h_pdf_response[i] = (TH2D*) gDirectory->Get( response_histoPath.c_str() )->Clone();
		sprintf( histoname, "acc_%i", i ); 
		h_pdf_acc[i] = h_pdf_response[i]->ProjectionX( histoname, 1, nbins );
		sprintf( histoname, "eff_%i", i ); 
		h_pdf_eff[i] = h_pdf_response[i]->ProjectionY( histoname, 1, nbins );
		
		
	sprintf( temp, "output/PDF4LHC15_nlo_30_%i_%s/tt_diffxs_13TeV.mc.AFII.DiTop.410003.co.PDF4LHC15_nlo_30_%i_%s.nofullhad.histograms.root", i, "nocut", i, "nocut");
		cout << "Opening " << temp << endl;
		particle_pdfPaths[ i ] = string( temp );
		particle_pdfFiles[ i ] = TFile::Open( temp );
		particle_pdfFiles[i]->cd();		
		h_pdf_particle[i] = (TH1D*) gDirectory->Get( particle_histoPath.c_str() )->Clone();
		
		h_pdf_acc[i]->Divide( h_pdf_reco[i] );
		h_pdf_eff[i]->Divide( h_pdf_particle[i] );
		if( i == 0 ) 
		{
			h_pdf_acc[i]->SetLineWidth(2);
			h_acc_totalDown = (TH1D*) h_pdf_acc[0]->Clone();
			h_acc_totalUp = (TH1D*) h_pdf_acc[0]->Clone();
			acc_shifts_down = new double[nbins];
			acc_shifts_up = new double[nbins];
			h_pdf_eff[i]->SetLineWidth(2);
			h_eff_totalDown = (TH1D*) h_pdf_eff[0]->Clone();
			h_eff_totalUp = (TH1D*) h_pdf_eff[0]->Clone();
			eff_shifts_down = new double[nbins];
			eff_shifts_up = new double[nbins];
			for( int b = 0; b < nbins; ++b )
			{
				acc_shifts_down[b] = 0;
				acc_shifts_up[b] = 0;
				eff_shifts_down[b] = 0;
				eff_shifts_up[b] = 0;
			}		

		}
		else 
		{
			h_pdf_acc[i]->SetLineWidth(1);
			h_pdf_eff[i]->SetLineWidth(1);
				
			double difference;
			for( int b = 0; b < nbins; ++b )
			{
				difference = h_pdf_eff[i]->GetBinContent(b+1) - h_pdf_eff[0]->GetBinContent(b+1);
				eff_shifts_up[b] += difference*difference;
				eff_shifts_down[b] += difference*difference;
				difference = h_pdf_acc[i]->GetBinContent(b+1) - h_pdf_acc[0]->GetBinContent(b+1);
				acc_shifts_up[b] += difference*difference;
				acc_shifts_down[b] += difference*difference;
				
			}
			h_pdf_acc[i]->Divide( h_pdf_acc[0] );
			h_pdf_eff[i]->Divide( h_pdf_eff[0] );
		}
		h_pdf_acc[i]->SetLineColor( kBlue + i );
		h_pdf_eff[i]->SetLineColor( kBlue + i );

	}
	string reco_ct10path = "output/nominal/tt_diffxs_13TeV.mc.AFII.DiTop.410003.co.nominal.nofullhad.histograms.root";
	string particle_ct10path = "output/nocut/tt_diffxs_13TeV.mc.AFII.DiTop.410003.co.nocut.nofullhad.histograms.root";
	TFile * reco_ct10File = TFile::Open( reco_ct10path.c_str() );	
	TH1D * h_ct10_reco = (TH1D*) reco_ct10File->Get( reco_histoPath.c_str() )->Clone();
	TH2D * h_ct10_response = (TH2D*) reco_ct10File->Get( response_histoPath.c_str() )->Clone();
	
	
	
		TFile * particle_ct10File = TFile::Open( particle_ct10path.c_str() );	
	TH1D * h_ct10_particle = (TH1D*) particle_ct10File->Get( particle_histoPath.c_str() )->Clone();
	

	TH1D * h_ct10_acc = h_ct10_response->ProjectionX( "acc_ct10", 1, nbins );
	TH1D * h_ct10_eff = h_ct10_response->ProjectionY( "eff_ct10", 1, nbins );
	h_ct10_acc->SetLineWidth( 2 );
	h_ct10_acc->SetLineColor( kRed );
	h_ct10_acc->Divide( h_ct10_reco );
	h_ct10_eff->SetLineWidth( 2 );
	h_ct10_eff->SetLineColor( kRed );
	h_ct10_eff->Divide(  h_ct10_particle );
	
	//total unc
	for( int b = 0; b < nbins; ++b )
	{
		h_acc_totalUp->SetBinContent( b+1, h_pdf_acc[0]->GetBinContent(b +1 ) + sqrt( acc_shifts_up[b] ) );
		h_acc_totalDown->SetBinContent( b+1, h_pdf_acc[0]->GetBinContent(b + 1) - sqrt( acc_shifts_down[b] ) );
		h_eff_totalUp->SetBinContent( b+1, h_pdf_eff[0]->GetBinContent(b +1 ) + sqrt( eff_shifts_up[b] ) );
		h_eff_totalDown->SetBinContent( b+1, h_pdf_eff[0]->GetBinContent(b + 1) - sqrt( eff_shifts_down[b] ) );
	}
	h_eff_totalUp->Divide( h_pdf_eff[0] );
	h_eff_totalDown->Divide( h_pdf_eff[0] );
	h_eff_totalDown->SetLineWidth( 2 );
	h_eff_totalUp->SetLineWidth( 2 );
	h_eff_totalDown->SetLineColor( kBlack );
	h_eff_totalUp->SetLineColor( kBlack );
	
	
	TH1D * h_ct10_eff_up = (TH1D*) h_ct10_eff->Clone();
	TH1D * h_ct10_eff_down = (TH1D*) 	h_pdf_eff[0]->Clone();
	
	h_ct10_eff_down->Add( h_ct10_eff, -1 );
	h_ct10_eff_down->Add( h_pdf_eff[0] );
	h_ct10_eff_down->SetLineWidth( 2 );
	h_ct10_eff_down->SetLineColor( kRed );	
	
	
	h_acc_totalUp->Divide( h_pdf_acc[0] );
	h_acc_totalDown->Divide( h_pdf_acc[0] );
	h_acc_totalDown->SetLineWidth( 2 );
	h_acc_totalUp->SetLineWidth( 2 );
	h_acc_totalDown->SetLineColor( kBlack );
	h_acc_totalUp->SetLineColor( kBlack );
	TH1D * h_ct10_acc_up = (TH1D*) h_ct10_acc->Clone();
	TH1D * h_ct10_acc_down = (TH1D*) 	h_pdf_acc[0]->Clone();
	
	h_ct10_acc_down->Add( h_ct10_acc, -1 );
	h_ct10_acc_down->Add( h_pdf_acc[0] );
	h_ct10_acc_down->SetLineWidth( 2 );
	h_ct10_acc_down->SetLineColor( kRed );	
	
	
	h_ct10_acc_up->Divide( h_pdf_acc[0] );
	h_ct10_acc_down->Divide( h_pdf_acc[0] );
	h_ct10_acc->Divide( h_pdf_acc[0] );
	h_ct10_eff_up->Divide( h_pdf_eff[0] );
	h_ct10_eff->Divide( h_pdf_eff[0] );
	h_ct10_eff_down->Divide( h_pdf_eff[0] );
	h_pdf_eff[0]->Divide( h_pdf_eff[0] );
	
	h_pdf_acc[0]->Divide( h_pdf_acc[0] );
	
	TCanvas * c = new TCanvas();
		TLegend* legend = new TLegend(0.5,0.75,0.7,0.90);
     legend->SetBorderSize(0);  // no border
     legend->SetBorderSize(0);  // simple border, but no drop shadow
     legend->SetFillColor(0);   // Legend background should be white
     legend->SetTextSize(0.04); // Increase entry font Width!
	//h_alpgen_num
	legend->Clear();
	legend->AddEntry( h_ct10_eff, "MC@NLO+HPP (CT10)", "l" );
	legend->AddEntry( h_pdf_eff[0], "MC@NLO+HPP (PDF4LHC15_nlo_30 central)", "l" );
	legend->AddEntry( h_eff_totalUp, "Total PDF4LHC15_nlo_30 uncertainty", "l" );
	h_ct10_eff->GetXaxis()->SetTitle( ( particle + " " + variable + "(particle level)" ).c_str() ); 
	h_ct10_eff->GetYaxis()->SetTitle( "Efficiency Ratio over PDF4LHC15_nlo_30" ); 
	// h_ct10->SetMaximum(  1 +  2 * ( h_ct10->GetMaximum() - 1 ) ); 
	// h_ct10->SetMinimum(  1 -2 * ( 1 -  h_ct10->GetMinimum() ) ); 
	h_ct10_eff->SetMaximum(  1.02 ); 
	h_ct10_eff->SetMinimum(  0.98 ); 
	h_ct10_eff->Draw( "hist" );
	h_ct10_eff_down->Draw( "same hist" );
	for( int i = 1; i <= 30; ++i )
	{
		h_pdf_eff[i]->Draw( "hist same" );
	}
	h_eff_totalDown->Draw( "hist same" );
	h_eff_totalUp->Draw( "hist same" );
	h_pdf_eff[0]->Draw( "hist same" );
	legend->Draw();
	c->Print( ( "eff_" + particle + "_" + variable + ".png" ).c_str() );
	
	//h_alpgen_num
	legend->Clear();
	legend->AddEntry( h_ct10_acc, "MC@NLO+HPP (CT10)", "l" );
	legend->AddEntry( h_pdf_acc[0], "MC@NLO+HPP (PDF4LHC15_nlo_30 central)", "l" );
	legend->AddEntry( h_acc_totalUp, "Total PDF4LHC15_nlo_30 uncertainty", "l" );

	h_ct10_acc->GetXaxis()->SetTitle( ( particle + " " + variable + "(reco level)" ).c_str() ); 
	h_ct10_acc->GetYaxis()->SetTitle( "Acceptance Ratio over PDF4LHC15_nlo_30" ); 
	// h_ct10->SetMaximum(  1 +  2 * ( h_ct10->GetMaximum() - 1 ) ); 
	// h_ct10->SetMinimum(  1 -2 * ( 1 -  h_ct10->GetMinimum() ) ); 
	h_ct10_acc->SetMaximum(  1.02 ); 
	h_ct10_acc->SetMinimum(  0.98 ); 
	h_ct10_acc->Draw( "hist" );
	h_ct10_acc_down->Draw( "same hist" );
	for( int i = 1; i <= 30; ++i )
	{
		h_pdf_acc[i]->Draw( "hist same" );
	}
	h_acc_totalDown->Draw( "hist same" );
	h_acc_totalUp->Draw( "hist same" );
	h_pdf_acc[0]->Draw( "hist same" );
	legend->Draw();
	c->Print( ( "acc_" + particle + "_" + variable + ".png" ).c_str() );	
	
	
}