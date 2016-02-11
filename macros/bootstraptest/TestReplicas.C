{



  TString dir = "/afs/cern.ch/user/q/qitek/public/MCsigHalves/BootsTrap/1000toys";
  //  TString dir = "/afs/cern.ch/user/q/qitek/public/MCsigHalves/BootsTrap/5000toys";                                                                                                             // TString dir = "../../run/";
  
  TString fname = dir + "/histograms_data_el.root";


  cout << "Loading libs..." << endl;

  gSystem->AddIncludePath(" -I../../../");
  gSystem->AddIncludePath(" -I../../../BootstrapGenerator/");
  gROOT->ProcessLine( ".L ../../../BootstrapGenerator/StandAlone/libBootstrapGenerator.so" );



  TH1DBootstrap * h;
  TFile * f = TFile::Open( fname, "read" );
  //  f->GetObject( "m_boots", h );

  
  const int N = 5;
  TString names[N] = {"reco_4j2b_topH_pt_boots", "reco_4j2b_topH_absrap_boots", 
		     "reco_4j2b_tt_m_boots", "reco_4j2b_tt_pt_boots",  "reco_4j2b_tt_absrap_boots"};
  

  for (int j = 0; j < N; ++j) {
    cout << "*** Processing spectrum " << names[j].Data() << endl;
    f->GetObject( names[j], h );
    TH1D * hist = h->GetNominal();
    hist->Print( "all" );
    int nReplica = h->GetNReplica();
    for( int i = 0; i < nReplica; ++i ) {
      hist = (TH1D*) h->GetReplica( i );
      hist->Print( "all" );
    }
  }

}

