void EvaluateNormalization(string nominalinputStressed, string NoCutinputStressed, string NoCutinputNominal){
  
  string stress_type[] = {"tt_m","tt_mBump","tt_rapidity","t_pt"};  
  vector<string> Stress;
  Stress.assign(stress_type,stress_type+4);
  
  TFile *f_nocut = new TFile(NoCutinputNominal.c_str());
  
  for(int j=0; j<Stress.size(); j++){
    
    TFile *f_nocut_stressed = new TFile((Stress[j]+"_"+NoCutinputStressed).c_str());
    TFile *f_nominal_stressed = new TFile((Stress[j]+"_"+nominalinputStressed).c_str());
    TFile *f_nominal_rescaled= new TFile(("Rescaled_"+Stress[j]+"_"+nominalinputStressed).c_str(),"recreate");
    f_nominal_rescaled->mkdir("reco");
    f_nominal_rescaled->mkdir("reco/1fj1b");
    f_nominal_rescaled->mkdir("reco/1fj1b/topH");
    
    string histo_array[] = {"pt","absrap"};  
    vector<string> variable;
    variable.assign(histo_array,histo_array+2);
    
    
    string hpath = "particle/1fj1b/topH/pt";
    
    TH1F* stressedHisto = (TH1F*) f_nocut_stressed->Get(hpath.c_str());
    TH1F* nominalHisto = (TH1F*) f_nocut->Get(hpath.c_str());
    
    double  integral_stressed = stressedHisto->Integral(0,stressedHisto->GetNbinsX()+1);
    double integral_nominal = nominalHisto->Integral(0,nominalHisto->GetNbinsX()+1); 
    
    double normalization = integral_nominal/integral_stressed;
    
    f_nominal_rescaled->cd();
    for (unsigned int i = 0; i< variable.size(); i++){
      f_nominal_rescaled->cd("reco/1fj1b/topH/");
      TH1F* h1 = (TH1F*)f_nominal_stressed->Get(("reco/1fj1b/topH/"+variable[i]).c_str())->Clone();
      h1->Scale(normalization);
      
      h1->Write(variable[i].c_str());
    }
    
    
    f_nocut_stressed->Close();
    f_nominal_stressed->Close();
    f_nominal_rescaled->Close();
  }
  
  
}
