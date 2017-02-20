#include <iostream>
#include <string>
#include <vector>
#include "TH1D.h"
#include "TFile.h"

using namespace std;
// void resolved_StressTestRescaler(string target_filename, string stress_filename, string reference_filename, string syst){

int main( int nargs, char ** args )
{

   string target_filename = args[1];
   string stress_filename = args[2];
   string reference_filename = args[3];
   string syst = args[4];
  TFile *f_target = new TFile(target_filename.c_str(), "update");
  TFile *f_reference = new TFile(reference_filename.c_str());
  TFile *f_stress = new TFile(stress_filename.c_str());
  TH1D * h_reference,  * h_stress, * h_target;
 // TFile *f_out = new TFile(newfilename.c_str());
  
  string RegionNameArray[]={"4j2b" };//,"cutflow"};
  std::vector<std::string> RegionName;
  RegionName.assign(RegionNameArray,RegionNameArray+1);
  double sf = 1;
  
  //   string ParticleNameArray[]={"topH","lep","smallJ","met","bjet","largejet"};
  //   std::vector<std::string> ParticleName;
  //   ParticleName.assign(ParticleNameArray,ParticleNameArray+6);
  //   
  //   
  
  h_reference = (TH1D*) f_reference->Get( "LPLUSJETS_cutflow_particle_weighted");
  h_target = (TH1D*) f_target->Get( "LPLUSJETS_cutflow_particle_weighted");
  h_stress = (TH1D*) f_stress->Get( "LPLUSJETS_cutflow_particle_weighted");
  TH1D * h_cut = h_target;
  double oldIntegral = h_target->Integral();
  sf = h_reference->GetBinContent(1) / h_stress->GetBinContent(1);
  h_target->Scale( sf );
  vector<string> phaseSpaces;
  if( syst == "nominal") phaseSpaces.push_back( "reco");
  phaseSpaces.push_back( "particle");
  phaseSpaces.push_back( "parton");
  for( const auto& phaseSpace: phaseSpaces)
  {          
         for(unsigned int j = 0; j<RegionName.size(); j++){
            f_target->cd((phaseSpace + "/"+RegionName[j]).c_str());
            
            //Iteration on directories in Reco
            TListIter ParticleName(gDirectory->GetListOfKeys());
            while( TObject* tmp_dir = ParticleName.Next()){
              string currentParticleName=tmp_dir->GetName();
              
              cout<<currentParticleName<<endl;
              string pathTarget = phaseSpace + "/" +RegionName[j]+"/"+currentParticleName; 
              string pathReference = "parton/" +RegionName[j]+"/"+currentParticleName;
              cout << "Doing " << pathTarget << endl;
              f_target->cd(pathTarget.c_str());
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
                h_target = NULL;
                h_target = (TH1D*) f_target->Get((pathTarget+"/"+name).c_str());
                if ( h_target == NULL ) continue;
              cout << "Doing " << pathTarget+"/"+name << ", " << h_target << endl;
                //
       //         h_reference = (TH1D*) f_reference->Get((pathReference+"/"+name).c_str());
       //         h_stress = (TH1D*) f_stress->Get((pathReference+"/"+name).c_str());
       //         sf = h_reference->Integral(-1, -1) / h_stress->Integral(-1, -1);
        //	cout <<  "Rescaling " << h_target->GetName() << " by " << sf << endl;
                h_target->Scale( sf );
                h_target->Write( (pathTarget+"/"+name).c_str());
                
                
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
