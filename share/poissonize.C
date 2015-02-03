// function to get asymmetric error bars for hists
TGraphAsymmErrors* poissonize(TH1 *h) {
  vector<int> points_to_remove;
  TGraphAsymmErrors* gr= new TGraphAsymmErrors(h);
  for (UInt_t i=0; i< gr->GetN(); i++) {
   double content = (gr->GetY())[i];
   gr->SetPointError(i,0,0,GC_down(content),GC_up(content));
   if(content==0){
    gr->RemovePoint(i);
    i--;
   }
  }
  return gr;
}

double GC_up(double data) {
//Used in WZ observation
 if (data == 0 ) return 0;
 return 0.5*TMath::ChisquareQuantile(1.-0.1586555,2.*(data+1))-data;
}

double GC_down(double data) {
//Used in WZ observation
 if (data == 0 ) return 0;
 return data-0.5*TMath::ChisquareQuantile(0.1586555,2.*data);
}

