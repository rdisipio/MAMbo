{


  TString fname = "/afs/cern.ch/user/q/qitek/public/MCsigHalves/BootsTrap/10toys/histograms_data_el.root";


  gSystem->AddIncludePath(" -I../../../");
  gSystem->AddIncludePath(" -I../../../BootstrapGenerator/");
  gROOT->ProcessLine( ".L ../../../BootstrapGenerator/StandAlone/libBootstrapGenerator.so" );
  TH1DBootstrap * h;
  TFile * f = TFile::Open( fname, "read" );
  f->GetObject( "m_boots", h );
  TH1D * hist = h->GetNominal();
  hist->Print( "all" );
  int nReplica = h->GetNReplica();
  for( int i = 0; i < nReplica; ++i )
  {
      hist = (TH1D*) h->GetReplica( i );
      hist->Print( "all" );
  }
}

