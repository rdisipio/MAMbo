{
	double sf_el_pretag_nominal[] = {1,1,1.097 , 0.836,  0.937}; 
	double sf_el_tag_nominal[] = {1,1,1.408 , 1.067 , 1.202 }; 
	double sf_mu_pretag_nominal[] = {1,1,1.002, 0.881,0.892 } ;
	double sf_mu_tag_nominal[] = {1,1,1.250, 1.097, 1.115}; 
	
	double unc_stat_el_pretag[] = {1,1,0.134, 0.245, 0.085 };
	double unc_stat_el_tag[] = {1,1,0.173,  0.314  , 0.111 };
	double unc_stat_mu_pretag[] = {1,1,0.041, 0.049, 0.065 };
	double unc_stat_mu_tag[] = {1,1,0.053,  0.062  , 0.082 };
	
	double unc_syst_el_pretag[] = {1,1,0.253,	0.145,	0.229 };
	double unc_syst_el_tag[] = {1,1,0.186,	0.127,	0.222};
	double unc_syst_mu_pretag[] = {1,1,0.166,	0.157,	0.18};
	double unc_syst_mu_tag[] = {1,1,0.111,	0.112,	0.162 };
	
	
	
	TFile * el = TFile::Open( "Wjets_CA_el.root", "recreate" );
	TH2D * nominal_el = new TH2D( "nominal", "nominal", 5, -0.5, 4.5, 2, -0.5, 1.5 );
	nominal_el->SetDirectory( el );
	TH2D * syst_el = new TH2D( "syst", "syst", 5, -0.5, 4.5, 2, -0.5, 1.5 );
	syst_el->SetDirectory( el );
	TH2D * stat_el = new TH2D( "stat", "stat", 5, -0.5, 4.5, 2, -0.5, 1.5 );
	
	TFile * mu = TFile::Open( "Wjets_CA_mu.root", "recreate" );
	TH2D * nominal_mu = new TH2D( "nominal", "nominal", 5, -0.5, 4.5, 2, -0.5, 1.5 );
	nominal_mu->SetDirectory( mu );
	TH2D * syst_mu = new TH2D( "syst", "syst", 5, -0.5, 4.5, 2, -0.5, 1.5 );
	syst_mu->SetDirectory( mu );
	TH2D * stat_mu = new TH2D( "stat", "stat", 5, -0.5, 4.5, 2, -0.5, 1.5 );
	syst_mu->SetDirectory( mu );

	for( int i = 1; i<=5; ++i )
	{
		nominal_el->SetBinContent( i, 1, sf_el_pretag_nominal[i-1] );
		nominal_el->SetBinContent( i, 2, sf_el_tag_nominal[i-1] );
		stat_el->SetBinContent( i, 1, sf_el_pretag_nominal[i-1] +  unc_stat_el_pretag[i-1] );
		stat_el->SetBinContent( i, 2, sf_el_tag_nominal[i-1]  + unc_stat_el_tag[i-1]);
		syst_el->SetBinContent( i, 1, sf_el_pretag_nominal[i-1] +  unc_syst_el_pretag[i-1] );
		syst_el->SetBinContent( i, 2, sf_el_tag_nominal[i-1]  + unc_syst_el_tag[i-1]);
		nominal_mu->SetBinContent( i, 1, sf_mu_pretag_nominal[i-1] );
		nominal_mu->SetBinContent( i, 2, sf_mu_tag_nominal[i-1] );
		stat_mu->SetBinContent( i, 1, sf_mu_pretag_nominal[i-1] +  unc_stat_mu_pretag[i-1] );
		stat_mu->SetBinContent( i, 2, sf_mu_tag_nominal[i-1]  + unc_stat_mu_tag[i-1]);
		syst_mu->SetBinContent( i, 1, sf_mu_pretag_nominal[i-1] +  unc_syst_mu_pretag[i-1] );
		syst_mu->SetBinContent( i, 2, sf_mu_tag_nominal[i-1]  + unc_syst_mu_tag[i-1]);
	}
	el->Write();
	el->Close();
	mu->Write();
	mu->Close();
	
	
}
