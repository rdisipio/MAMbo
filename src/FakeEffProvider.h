// -*- C++ -*-

/**
 * Fake (and real) lepton efficiency provider.
 */
#ifndef __FAKESEFFPROVIDER_H__
#define  __FAKESEFFPROVIDER_H__
#include "Commons.h" 
class FakeEffProvider {
  
public:
  FakeEffProvider(int channel, int type=Type::fakeEff); //channel: e=0, mu=1
  ~FakeEffProvider() {}
  enum Type {fakeEff, realEff, tightEff};
  enum Var {NJETS, NBTAG, LPT, LETA, JET1PT, MINDRLJET, DPHILMET, MET, 
            TWODIM_PT_ETA, TWODIM_PT_DPHI, TWODIM_PT_NBTAG, TWODIM_PT_MET,
            TWODIM_DPHI_NBTAG, TWODIM_DPHI_MET, TWODIM_DPHI_ETA,
            TWODIM_NJETS_NBTAG
           };
  double GetEfficiency(int var, float value, bool binned=false);
  double GetEfficiency2D(int var, float xvalue, float yvalue, bool binned=false);

private:
  TFile* m_file;
  std::map<int, TEfficiency*> m_hist;
  std::map<int, TF1*> m_func;
  
  int GetRightBin(TEfficiency* h, double v);
  int GetRightBin2D(TEfficiency* h, double vx, double vy);
};

//____________________________________________________________________________________________________

FakeEffProvider::FakeEffProvider(int channel, int type) {
 TString prefix;
  string basePath = string( getenv( "MAMBODIR" ) ) + "/share/data/FakeEfficiencies";
   cout << "Debug: FakeEffProvider - base path is " << basePath << endl;
  if (channel == 0) {
    if (type==Type::tightEff)
      m_file = TFile::Open( (basePath + "/tight_eff_e.root").c_str());
    else if (type==Type::realEff)
      m_file = TFile::Open( (basePath + "/real_eff_e.root").c_str());
    else
      m_file = TFile::Open( (basePath + "/fake_eff_e.root").c_str());
    prefix += "e_";
  } else if (channel == 1) {
    if (type==Type::tightEff)
      m_file = TFile::Open( (basePath + "/tight_eff_mu.root").c_str());
    else if (type==Type::realEff)
      m_file = TFile::Open( (basePath + "/real_eff_mu.root").c_str());
    else
      m_file = TFile::Open( (basePath + "/fake_eff_mu.root").c_str());
    prefix += "mu_";
  } else {
    Error("Utils::FakeEffProvider", "Wrong channel number!");
    throw std::runtime_error( "Wrong channel number!" );
  }
    cout << "Debug: FakeEffProvider - Opened file " << m_file->GetPath()  << endl;
  
  //1D histograms
  m_hist[Var::NJETS]     = dynamic_cast<TEfficiency*>(m_file->Get( (TString("histograms/")+prefix+"njets_Eff").Data() ));
  m_hist[Var::NBTAG]     = dynamic_cast<TEfficiency*>(m_file->Get( (TString("histograms/")+prefix+"nbtag_Eff").Data() ));
  m_hist[Var::LPT]       = dynamic_cast<TEfficiency*>(m_file->Get( (TString("histograms/")+prefix+"l_pt_Eff").Data() ));
  m_hist[Var::LETA]      = dynamic_cast<TEfficiency*>(m_file->Get( (TString("histograms/")+prefix+"l_eta_Eff").Data() ));
  m_hist[Var::MINDRLJET] = dynamic_cast<TEfficiency*>(m_file->Get( (TString("histograms/")+prefix+"min_dR_l_jet_Eff").Data() ));
  m_hist[Var::DPHILMET]  = dynamic_cast<TEfficiency*>(m_file->Get( (TString("histograms/")+prefix+"dphi_l_met_Eff").Data() ));
  m_hist[Var::MET]       = dynamic_cast<TEfficiency*>(m_file->Get( (TString("histograms/")+prefix+"met_Eff").Data() ));
  m_hist[Var::JET1PT]    = dynamic_cast<TEfficiency*>(m_file->Get( (TString("histograms/")+prefix+"jet1_pt_Eff").Data() ));
  
  //1D functions
  m_func[Var::LPT]       = dynamic_cast<TF1*>(m_file->Get( (TString("functions/")+prefix+"l_pt_Eff").Data() ));
  m_func[Var::LETA]      = dynamic_cast<TF1*>(m_file->Get( (TString("functions/")+prefix+"l_eta_Eff").Data() ));
  m_func[Var::JET1PT]    = dynamic_cast<TF1*>(m_file->Get( (TString("functions/")+prefix+"jet1_pt_Eff").Data() ));
  m_func[Var::MINDRLJET] = dynamic_cast<TF1*>(m_file->Get( (TString("functions/")+prefix+"min_dR_l_jet_Eff").Data() ));
  m_func[Var::DPHILMET]  = dynamic_cast<TF1*>(m_file->Get( (TString("functions/")+prefix+"dphi_l_met_Eff").Data() ));
  m_func[Var::MET]       = dynamic_cast<TF1*>(m_file->Get( (TString("functions/")+prefix+"met_Eff").Data() ));
  
  //2D histograms
  if (type==Type::fakeEff) {
    m_hist[Var::TWODIM_PT_ETA]  = dynamic_cast<TEfficiency*>(m_file->Get( (TString("histograms/")+prefix+"2D_pt_eta").Data() ));
    m_hist[Var::TWODIM_PT_DPHI]     = dynamic_cast<TEfficiency*>(m_file->Get( (TString("histograms/")+prefix+"2D_pt_dphi").Data() ));
    m_hist[Var::TWODIM_PT_NBTAG]    = dynamic_cast<TEfficiency*>(m_file->Get( (TString("histograms/")+prefix+"2D_pt_nbtag").Data() ));
    m_hist[Var::TWODIM_PT_MET]      = dynamic_cast<TEfficiency*>(m_file->Get( (TString("histograms/")+prefix+"2D_pt_met").Data() ));
    m_hist[Var::TWODIM_DPHI_NBTAG]  = dynamic_cast<TEfficiency*>(m_file->Get( (TString("histograms/")+prefix+"2D_dphi_nbtag").Data() ));
    m_hist[Var::TWODIM_DPHI_MET]    = dynamic_cast<TEfficiency*>(m_file->Get( (TString("histograms/")+prefix+"2D_dphi_met").Data() ));
    m_hist[Var::TWODIM_DPHI_ETA]    = dynamic_cast<TEfficiency*>(m_file->Get( (TString("histograms/")+prefix+"2D_dphi_eta").Data() ));
    m_hist[Var::TWODIM_NJETS_NBTAG] = dynamic_cast<TEfficiency*>(m_file->Get( (TString("histograms/")+prefix+"2D_njets_nbtag").Data() ));
  }
  
}

int FakeEffProvider::GetRightBin(TEfficiency* eff, double v) {
  
  const TH1* h = eff->GetTotalHistogram();
  
  int firstBin = 1;
  int lastBin = h->GetNbinsX();
  
  for (int i=firstBin; i<=lastBin; ++i) {
    if (eff->GetEfficiency(i)<=0) firstBin=i+1;
    else break;
  }
  for (int i=lastBin; i>=firstBin; --i) {
    if (eff->GetEfficiency(i)<=0) lastBin=i-1;
    else break;
  }
  
  double min = h->GetBinLowEdge(firstBin);
  double max = h->GetBinLowEdge(lastBin+1);
  
  if (v < min) {
    Warning("Utils::FakeEffProvider", "GetRightBin: v < min !!! returning first non-zero bin");
    return firstBin;
  }
  else if (v >= max)
    return lastBin;
  else
    return h->FindFixBin(v);
}

double FakeEffProvider::GetEfficiency(int var, float value, bool binned) {
  if (binned) { //binned efficiency
    std::map<int, TEfficiency*>::iterator it = m_hist.find(var);
    if (it==m_hist.end() || (*it).second==0) {
      Error("Utils::FakeEffProvider", TString::Format("Efficiency histogram for variable %d not found",var).Data() );
       throw std::runtime_error( "error" );
	   }
    else {
      TEfficiency* eff = (*it).second;
      return eff->GetEfficiency( GetRightBin(eff, value) );
    }
  }
  else { //fitted efficiency
    std::map<int, TF1*>::iterator it = m_func.find(var);
    if (it==m_func.end() || (*it).second==0) {
      Error("Utils::FakeEffProvider", TString::Format("Efficiency function for variable %d not found",var).Data() );
      throw std::runtime_error( "error1" );
    } 
    else {
      TF1* f = (*it).second;
      return f->Eval(value);
    }
  }
}

int FakeEffProvider::GetRightBin2D(TEfficiency* eff, double vx, double vy) {
  
  const TH1* h = eff->GetTotalHistogram();
  // this doesn't necessarily mean the efficiency is well defined and calculated in this bin:
  // (see FakeEffProvider::GetRightBin for the better way to check this, not implemented here for 2D case)
  double x_min = h->GetXaxis()->GetBinLowEdge(h->FindFirstBinAbove(0,1));
  double x_max = h->GetXaxis()->GetBinLowEdge(h->FindLastBinAbove(0,1)+1);
  double y_min = h->GetYaxis()->GetBinLowEdge(h->FindFirstBinAbove(0,2));
  double y_max = h->GetYaxis()->GetBinLowEdge(h->FindLastBinAbove(0,2)+1);
  
  int binx=1;
  int biny=1;
  
  if (vx < x_min) {
    Warning("Utils::FakeEffProvider", "GetRightBin2D: vx < x_min !!! returning value from the first x-bin");
    vx=x_min;
  } 
  else if (vx >= x_max) {
    vx=h->GetXaxis()->GetBinLowEdge(h->GetNbinsX());
  }
  
 if (vy < y_min) {
    Warning("Utils::FakeEffProvider", "GetRightBin2D: vy < y_min !!! returning value from the first y-bin");
    vy=y_min;
  }
  else if (vy >= y_max) {
    vy=h->GetYaxis()->GetBinLowEdge(h->GetNbinsY());
  }

  return h->FindFixBin(vx,vy);
  
}

double FakeEffProvider::GetEfficiency2D(int var, float xvalue, float yvalue, bool binned) {
  if (binned) {
    std::map<int, TEfficiency*>::iterator it = m_hist.find(var);
    if (it==m_hist.end() || (*it).second==0) {
      Error("Utils::FakeEffProvider", TString::Format("Efficiency histogram for variable %d not found",var).Data() );
     throw std::runtime_error( "error2" );
    }
    else {
      TEfficiency* eff = (*it).second;
      double result = eff->GetEfficiency( GetRightBin2D(eff, xvalue, yvalue) );
      return result;
    }
    
  }
  else {
      Error("Utils::FakeEffProvider", "Fitted 2D efficiencies are not implemented yet!");
     throw std::runtime_error( "error3" );
  }
}


#endif