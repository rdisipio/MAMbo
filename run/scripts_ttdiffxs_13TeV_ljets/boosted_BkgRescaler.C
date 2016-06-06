void boosted_BkgRescaler(string filename, string bkg){
  
  TFile *f = new TFile(filename.c_str(), "update");
 // TFile *f_out = new TFile(newfilename.c_str());
  
  string RegionNameArray[]={"1fj1b","QCDcontrol","QCDcontrol2"};
  std::vector<std::string> RegionName;
  RegionName.assign(RegionNameArray,RegionNameArray+2);
  double sf_zjets = 1.34;
  double sf_diboson = 1.34;
  double sf_ttV = 1.14;
  double sf_stop_wt = 1.053;
  double sf_stop_schan = 1.048;
  double sf_stop_tchan = 1.05;
  double sf = 1;
  if( bkg == "Zjets" )
  {
         sf = sf_zjets; 
  }
  else if( bkg == "Stop_Wt")
  {
         sf = sf_stop_wt;
  }
  else if( bkg == "Stop_schan")
  {
         sf = sf_stop_schan;
  }
  else if( bkg == "Stop_tchan")
  {
         sf = sf_stop_tchan;
  }
  else if( bkg == "Diboson")
  {
         sf = sf_diboson;
  }
  else if( bkg == "ttV")
  {
         sf = sf_ttV;
  }
 
  
  //   string ParticleNameArray[]={"topH","lep","smallJ","met","bjet","largejet"};
  //   std::vector<std::string> ParticleName;
  //   ParticleName.assign(ParticleNameArray,ParticleNameArray+6);
  //   
  //   
  
  //reweight cutflow
  
  // TH1D * h_cutflow = (TH1D*) f->Get( "LPLUSJETS_cutflow_reco_weighted")->Clone();
  TH1F * h_cutflow = (TH1F*) f->Get( "LPLUSJETS_cutflow_reco_weighted");
  float before =  h_cutflow->Integral();
  h_cutflow->Scale( sf );
  f->cd();
  // f->Delete("LPLUSJETS_cutflow_reco_weighted;1");
  // h_cutflow->Write("LPLUSJETS_cutflow_reco_weighted");
  
  for(unsigned int j = 0; j<RegionName.size(); j++){
    f->cd(("reco/"+RegionName[j]).c_str());
    
    //Iteration on directories in Reco
    TListIter ParticleName(gDirectory->GetListOfKeys());
    while( TObject* tmp_dir = ParticleName.Next()){
      string currentParticleName=tmp_dir->GetName();
      
      cout<<currentParticleName<<endl;
      string path = "reco/"+RegionName[j]+"/"+currentParticleName;
      f->cd(path.c_str());
      TListIter Elements(gDirectory->GetListOfKeys());
      
      //Iteration on histogram in each subdirectory 
      string first=""; 
      int counter=0;
      for (int l=0;;l++){
           
	
	
	bool loop = false;
	TObject* tmp = Elements.Next();
	
	if (!tmp) break;
	string name = tmp->GetName();
	
	if( first == name) break;
	// TH1F* thisHisto = (TH1F*) f->Get((path+"/"+name).c_str())->Clone();
	TH1F* thisHisto = (TH1F*) f->Get((path+"/"+name).c_str());
	cout <<  "Rescaling " << thisHisto->GetName() << " by " << sf << endl;
	thisHisto->Scale( sf );
	
	if(loop == true) {
	  
	  gDirectory->Delete((name+";1").c_str());
	  thisHisto->Write((name).c_str());
	  if(counter==0) first = name;
	  counter++;
	}
	
	
      }  
      
    }
  }
  
  cout << "Integral before rescaling" << before << endl;
  cout << "Integral before closing: " << ((TH1D*) f->Get( "LPLUSJETS_cutflow_reco_weighted"))->Integral() << endl;
 f->Write(); 
 f->Close();
}
