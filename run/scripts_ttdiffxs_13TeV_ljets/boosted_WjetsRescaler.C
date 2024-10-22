void boosted_WjetsRescaler(string target_filename, string reference_filename){
  
  TFile *f_target = new TFile(target_filename.c_str(), "update");
  TFile *f_reference = new TFile(reference_filename.c_str());
  TH1D * h_reference, * h_target;
 // TFile *f_out = new TFile(newfilename.c_str());
  
  string RegionNameArray[]={"1fj1b","QCDcontrol","QCDcontrol2"};
  std::vector<std::string> RegionName;
  RegionName.assign(RegionNameArray,RegionNameArray+3);
  double sf = 1;
  
   cout<<"target "<<target_filename<<endl;
   cout<<"reference "<<reference_filename<<endl;
   /*  string ParticleNameArray[]={"topH","lep","smallJ","met","bjet","largejet"};
    std::vector<std::string> ParticleName;
    ParticleName.assign(ParticleNameArray,ParticleNameArray+6);
    
   */ 
  
  h_reference = (TH1D*) f_reference->Get( "LPLUSJETS_cutflow_reco_weighted");
  h_target = (TH1D*) f_target->Get( "LPLUSJETS_cutflow_reco_weighted");
 
 
  
  TH1D * h_cut = h_target;
  double oldIntegral = h_target->Integral();
  
  // h_reference->Copy( *h_target );
  for( int i = 1; i <= h_reference->GetNbinsX(); ++i )
  {
	  h_target->SetBinContent( i, h_reference->GetBinContent(i) );
  }
  
  f_target->cd();
  gDirectory->Delete("LPLUSJETS_cutflow_reco_weighted;1");
  h_target->Write("LPLUSJETS_cutflow_reco_weighted");
  
 for(unsigned int j = 0; j<RegionName.size(); j++){
    f_target->cd(("reco/"+RegionName[j]).c_str());
    
    //Iteration on directories in Reco
    TListIter ParticleName(gDirectory->GetListOfKeys());
    while( TObject* tmp_dir = ParticleName.Next()){
      string currentParticleName=tmp_dir->GetName();
      
     
      string path = "reco/"+RegionName[j]+"/"+currentParticleName;
      cout<<path<<endl;
      
      f_target->cd(path.c_str());
      TListIter Elements(gDirectory->GetListOfKeys());
      
      //Iteration on histogram in each subdirectory 
      string first=""; 
      int counter=0;
      bool loop = true;
      
      for (int l=0;;l++){

	
	TObject* tmp = Elements.Next();
	
	if (!tmp) break;
	string name = tmp->GetName();
	
	if(name.find("Matrix") != string::npos) continue;
	
	
	if( first == name) break;
	
	
	// TH1F* thisHisto = (TH1F*) f->Get((path+"/"+name).c_str())->Clone();
	h_target = (TH1D*) f_target->Get((path+"/"+name).c_str());
	h_reference = (TH1D*) f_reference->Get((path+"/"+name).c_str());
	
	if (h_target->Integral(-1, -1) == 0)
	{
	  continue;
	}
	
	if(loop) {
	  
	  first=name;
	  loop=false;
	  
	}
	
	sf = h_reference->Integral(-1, -1) / h_target->Integral(-1, -1);
	cout <<  "Rescaling " << h_target->GetName() << " by " << sf << endl;
	h_target->Scale( sf );
	
	gDirectory->Delete((name+";1").c_str());
	h_target->Write((name).c_str());
	
	
      }  
      
    }
  }
  //f_target->Write();
  
  double newIntegral = h_cut->Integral();
  cout << oldIntegral << " " << newIntegral << endl;
  f_target->Close();
  f_reference->Close();
}
