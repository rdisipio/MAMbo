void WjetsRescaler(string filename, string channel){
  
  TFile *f = new TFile(filename.c_str(), "update");
 // TFile *f_out = new TFile(newfilename.c_str());
  
  string RegionNameArray[]={"4j2b","cutflow"};
  std::vector<std::string> RegionName;
  RegionName.assign(RegionNameArray,RegionNameArray+2);
  double sf_el_pretag = 0.937; // ± 0.085;
  double sf_el_tag = 1.202;// ± 0.111
  double sf_mu_pretag = 0.892;// ± 0.062
  double sf_mu_tag = 1.115;// ± 0.078
  double sf = 1;
  double sf_tag = 1;
  double sf_pretag = 1;
  if( channel == "el" )
  {
          sf_tag = sf_el_tag;
          sf_pretag = sf_el_pretag;
  }
  else if( channel == "mu" )
  {
          sf_tag = sf_mu_tag;
          sf_pretag = sf_mu_pretag;
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
              sf = sf_tag;
	
	
	bool loop = true;
	TObject* tmp = Elements.Next();
	
	if (!tmp) break;
	string name = tmp->GetName();
	
	if( first == name) break;
	
	if (name.find("Matrix") != string::npos || name.find("weight") != string::npos) continue;
	if( path.find( "4j0b" ) != string::npos ) sf = sf_pretag;
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
