void resolved_BkgRescaler(string filename, string bkg){
  
  TFile *f = new TFile(filename.c_str(), "update");
 // TFile *f_out = new TFile(newfilename.c_str());
  
  string RegionNameArray[]={"4j2b","cutflow"};
  std::vector<std::string> RegionName;
  RegionName.assign(RegionNameArray,RegionNameArray+2);
  double sf_zjets = 1.2;
  double sf_diboson = 1.2;
  double sf_stop = 1.3;
  double sf = 1;
  if( bkg == "Zjets" )
  {
         sf = sf_zjets; 
  }
  else if( bkg == "Stop")
  {
         sf = sf_stop;
  }
  else if( bkg == "Diboson")
  {
         sf = sf_diboson;
  }
 
  
  //   string ParticleNameArray[]={"topH","lep","smallJ","met","bjet","largejet"};
  //   std::vector<std::string> ParticleName;
  //   ParticleName.assign(ParticleNameArray,ParticleNameArray+6);
  //   
  //   
  
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
           
	
	
	bool loop = true;
	TObject* tmp = Elements.Next();
	
	if (!tmp) break;
	string name = tmp->GetName();
	
	if( first == name) break;
	TH1F* thisHisto = (TH1F*) f->Get((path+"/"+name).c_str())->Clone();
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
  f->Close();
}
