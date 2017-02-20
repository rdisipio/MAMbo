#include <iostream>
#include <string>
#include <vector>
#include "TFile.h"
#include "TH1D.h"
#include "TROOT.h"

using namespace std;

void resolved_WjetsRescaler(string target_filename, string reference_filename){
  
  TFile *f_target = new TFile(target_filename.c_str(), "update");
  TFile *f_reference = new TFile(reference_filename.c_str());
  TH1D * h_reference, * h_target;
 // TFile *f_out = new TFile(newfilename.c_str());
  
  string RegionNameArray[]={"4j2b","cutflow"};
  std::vector<std::string> RegionName;
  RegionName.assign(RegionNameArray,RegionNameArray+2);
  double sf = 1;
  
  //   string ParticleNameArray[]={"topH","lep","smallJ","met","bjet","largejet"};
  //   std::vector<std::string> ParticleName;
  //   ParticleName.assign(ParticleNameArray,ParticleNameArray+6);
  //   
  //   
  
  h_reference = (TH1D*) f_reference->Get( "LPLUSJETS_cutflow_reco_weighted");
  h_target = (TH1D*) f_target->Get( "LPLUSJETS_cutflow_reco_weighted");
  TH1D * h_cut = h_target;
  double oldIntegral = h_target->Integral();
  
  // h_reference->Copy( *h_target );
  for( int i = 1; i <= h_reference->GetNbinsX(); ++i )
  {
	  h_target->SetBinContent( i, h_reference->GetBinContent(i) );
  }
  
  
  /*
 for(unsigned int j = 0; j<RegionName.size(); j++){
    f_target->cd(("reco/"+RegionName[j]).c_str());
    
    //Iteration on directories in Reco
    TListIter ParticleName(gDirectory->GetListOfKeys());
    while( TObject* tmp_dir = ParticleName.Next()){
      string currentParticleName=tmp_dir->GetName();
      
      cout<<currentParticleName<<endl;
      string path = "reco/"+RegionName[j]+"/"+currentParticleName;
      cout << path << endl;
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
	
	
	if( first == name) break;
	if(loop) {
	  
	  first=name;
	  loop=false;
	  
	}
	// TH1F* thisHisto = (TH1F*) f->Get((path+"/"+name).c_str())->Clone();
	h_target = (TH1D*) f_target->Get((path+"/"+name).c_str());
	h_reference = (TH1D*) f_reference->Get((path+"/"+name).c_str());
        cout << path+"/"+name << " " << h_target << " " << h_reference << endl;
	sf = h_reference->Integral(-1, -1) / h_target->Integral(-1, -1);
//	cout <<  "Rescaling " << h_target->GetName() << " by " << sf << endl;
	h_target->Scale( sf );
	h_target->Write( (path+"/"+name).c_str());
	
	
      }  
      
    }
  }*/
 

 /*
  for(unsigned int j = 0; j<RegionName.size(); j++){
    f_target->cd(("reco/"+RegionName[j]).c_str());
    cout << "RegionName = reco/" << RegionName[j] << endl;
    //Iteration on directories in Reco
    TListIter ParticleName(gDirectory->GetListOfKeys());
    while( TObject* tmp_dir = ParticleName.Next()){
      string currentParticleName=tmp_dir->GetName();
      
      cout<< "CurrentParticleName " << currentParticleName<<endl;
      string path = "reco/"+RegionName[j]+"/"+currentParticleName;
      f_target->cd(path.c_str());
      TListIter Elements(gDirectory->GetListOfKeys());
      
      TList * keys = gDirectory->GetListOfKeys();
      
      //Print histogram in this directory
      cout << "List of keys" << endl;
      for( int l = 0; l < keys->GetEntries(); ++l )              {
              cout << keys->At(l)->GetName() << endl;
      }
      
      
      //Iteration on histogram in each subdirectory 
      string first=""; 
      int counter=0;
      for (int l=0;;l++){
           
	
	
	bool loop = false;
	TObject* tmp = Elements.Next();
	
	if (!tmp) break;
	string name = tmp->GetName();
	if( first == name) break;
	if( l == 0 ) first = name;
	// TH1F* thisHisto = (TH1F*) f->Get((path+"/"+name).c_str())->Clone();
	cout <<  "Rescaling " << h_target->GetName() << " by " << sf << endl;
	h_target = (TH1D*) f_target->Get((path+"/"+name).c_str());
	h_reference = (TH1D*) f_reference->Get((path+"/"+name).c_str());
        cout << path+"/"+name << " " << h_target << " " << h_reference << endl;
	sf = h_reference->Integral(-1, -1) / h_target->Integral(-1, -1);        
        
        
	h_target->Scale( sf );

	
	
      }  
      
    }
  }
  

*/








  f_reference->cd();
  // f->Delete("LPLUSJETS_cutflow_reco_weighted;1");
  // h_cutflow->Write("LPLUSJETS_cutflow_reco_weighted");
  
  for(unsigned int j = 0; j<RegionName.size(); j++){
    f_reference->cd(("reco/"+RegionName[j]).c_str());
    
    //Iteration on directories in Reco
    TListIter ParticleName(gDirectory->GetListOfKeys());
    while( TObject* tmp_dir = ParticleName.Next()){
      string currentParticleName=tmp_dir->GetName();
      
      cout<<currentParticleName<<endl;
      string path = "reco/"+RegionName[j]+"/"+currentParticleName;
      f_reference->cd(path.c_str());
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
	TH1F* h_reference = (TH1F*) f_reference->Get((path+"/"+name).c_str());
	TH1F* h_target = (TH1F*) f_target->Get((path+"/"+name).c_str());
        sf = h_reference->Integral( -1, -1 ) / h_target->Integral( -1, -1);
	cout <<  "Rescaling " << h_target->GetName() << " by " << sf << endl;
	h_target->Scale( sf );
	
	if(loop == true) {
	  
	  gDirectory->Delete((name+";1").c_str());
	  h_target->Write((name).c_str());
	  if(counter==0) first = name;
	  counter++;
	}
	
	
      }  
      
    }
  }
  














 f_target->Write();
  
  double newIntegral = h_cut->Integral();
  cout << oldIntegral << " " << newIntegral << endl;
  f_target->Close();
  f_reference->Close();
}




int main( int nargs, char ** args)
{
        string target_filename = args[1];
        string reference_filename = args[2];
        resolved_WjetsRescaler( target_filename, reference_filename );
}