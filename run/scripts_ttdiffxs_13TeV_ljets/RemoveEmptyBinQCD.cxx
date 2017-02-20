void RemoveEmptyBinQCD(string filename){
  
  TFile *f = new TFile(filename.c_str() );
  
  string RegionNameArray[]={"4j2b","cutflow"};
  std::vector<std::string> RegionName;
  RegionName.assign(RegionNameArray,RegionNameArray+2);
  
  
  
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
	
	
	bool loop = false;
	TObject* tmp = Elements.Next();
	
	if (!tmp) break;
	string name = tmp->GetName();
	
	if( first == name) break;
	
	if (name.find("Matrix") != string::npos || name.find("weight") != string::npos) continue;
	
	TH1F* thisHisto = (TH1F*) f->Get((path+"/"+name).c_str())->Clone();
	for(int bin = 1; bin <= thisHisto->GetXaxis()->GetNbins(); bin++)
	{
	  
	  if(thisHisto->GetBinContent(bin) < 0){ 
	    cout << path+"/"+name << ", bin " << bin << " is negative (" << thisHisto->GetBinContent(bin) << ")\n";
	    
	  }
	}
	
	  counter++;
	}
	
	
      
    }
  }
//  f->Close();
}
