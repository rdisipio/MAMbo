// -*- C++ -*-

/**
 * Fake (and real) lepton efficiency provider.
 */
#ifndef __FAKESEFFPROVIDER_H__
#define  __FAKESEFFPROVIDER_H__
#include "Commons.h" 
class FakeEffProvider {
  
public:
  FakeEffProvider(int channel, int type=Type::fakeEff, int syst=Systematic::nominal); //channel: e=0, mu=1
  ~FakeEffProvider() {}
  enum Type {fakeEff, realEff, tightEff};
  enum Systematic {nominal, stat_D, stat_U, fakeEff_MCscale_D, fakeEff_MCscale_U, fakeEff_CR_S};
  enum Var {NJETS, NBTAG, LPT, LETA, JET1PT, MINDRLJET, DPHILMET, MET, 
            TWODIM_PT_ETA, TWODIM_PT_DPHI, TWODIM_PT_NBTAG, TWODIM_PT_MET, TWODIM_PT_JET1PT,
            TWODIM_DPHI_NJETS, TWODIM_DPHI_NBTAG, TWODIM_DPHI_MET, TWODIM_DPHI_ETA,
            TWODIM_ETA_NBTAG,
            TWODIM_JET1PT_DPHI, TWODIM_JET1PT_NJETS, TWODIM_JET1PT_NBTAG,
            TWODIM_NJETS_NBTAG,
            LPT_E1J, LPT_G1J, MET_E1J, MET_G1J,
            TWODIM_PT_NBTAG_E1J, TWODIM_PT_NBTAG_G1J,
            TWODIM_PT_ETA_E1J, TWODIM_PT_ETA_G1J,
            TWODIM_PT_DPHI_E1J, TWODIM_PT_DPHI_G1J,
            TWODIM_DPHI_ETA_E1J, TWODIM_DPHI_ETA_G1J,
            TWODIM_JET1PT_DPHI_E1J, TWODIM_JET1PT_DPHI_G1J,
           };
  double GetEfficiency(int var, float value, bool binned=false);
  double GetEfficiency2D(int var, float xvalue, float yvalue, bool binned=false);
  double GetAverageEfficiency() {return m_average;}
  
  static double ErrorWald(double nPas, double nTot, double ePas, double eTot, double z, bool upper, bool correlated);
  static double ErrorNormal(double nPas, double nTot, double ePas, double eTot, double z, bool upper, bool correlated);
  static double ErrorAC(double nPas, double nTot, double ePas, double eTot, double z, bool upper, bool correlated);

private:
  TFile* m_file;
  std::map<int, TEfficiency*> m_hist;
  std::map<int, TF1*> m_func;
  double m_average;
  int m_syst;
  double (*m_ErrorFunc)(double,double,double,double,double,bool,bool);
  
  double ErrorFuncWrapper(TEfficiency*,int,double,bool,bool);
  int GetRightBin(TEfficiency* h, double v);
  int GetRightBin2D(TEfficiency* h, double vx, double vy);
};

//____________________________________________________________________________________________________

FakeEffProvider::FakeEffProvider(int channel, int type, int syst) 
: m_syst(syst), m_file(nullptr) {
    TString prefix;
  string basePath = string( getenv( "MAMBODIR" ) ) + "/share/data/FakeEfficiencies";
  cout << "Debug: FakeEffProvider - base path is " << basePath << " and channel is " << channel << endl;
  //set default uncertainty calculation method
  m_ErrorFunc = ErrorAC;
 
  string filename = "";
  if (channel == 0) { //electron channel
    prefix += "e_";
    if (type==Type::tightEff) {
      filename = basePath + "/tight_eff_e.root";
    }
    else if (type==Type::realEff) {
      filename = basePath + "/real_eff_e.root";
    }
    else if (type==Type::fakeEff) {
      if (m_syst==Systematic::fakeEff_MCscale_D)
        filename = basePath + "/systematics/fakes_fakeEff_MCscale_D/fake_eff_e.root";
      else if (m_syst==Systematic::fakeEff_MCscale_U)
        filename = basePath + "/systematics/fakes_fakeEff_MCscale_U/fake_eff_e.root";
      else if (m_syst==Systematic::fakeEff_CR_S)
        filename = basePath + "/systematics/fakes_fakeEff_CR_S/fake_eff_e.root";
      else
        filename = basePath + "/fake_eff_e.root";
    }
    else {
      Error("FakeEffProvider", "Wrong efficiency type! Please use internal enum type");
      throw  (EXIT_FAILURE);
    }
  } else if (channel == 1) { //muon channel
    prefix += "mu_";
    if (type==Type::tightEff) {
      filename = basePath + "/tight_eff_mu.root";
    }
    else if (type==Type::realEff) {
      filename = basePath + "/real_eff_mu.root";
    }
    else if (type==Type::fakeEff) {
      if (m_syst==Systematic::fakeEff_MCscale_D)
        filename = basePath + "/systematics/fakes_fakeEff_MCscale_D/fake_eff_mu.root";
      else if (m_syst==Systematic::fakeEff_MCscale_U)
        filename = basePath + "/systematics/fakes_fakeEff_MCscale_U/fake_eff_mu.root";
      else if (m_syst==Systematic::fakeEff_CR_S)
        filename = basePath + "/systematics/fakes_fakeEff_CR_S/fake_eff_mu.root";
      else
        filename = basePath + "/fake_eff_mu.root";
    }
    else {
      Error("FakeEffProvider", "Wrong efficiency type! Please use internal enum type");
      throw  (EXIT_FAILURE);
    }
  } else {
    Error("FakeEffProvider", "Wrong channel number!");
    throw  (EXIT_FAILURE);
  }

  cout << "Opening " << filename << endl;
  m_file = TFile::Open(filename.c_str());
  if (!m_file) {
    Error("FakeEffProvider", "Failed to open efficiency file %s", filename.c_str());
    throw(EXIT_FAILURE);
  }
  
  //1D histograms
  m_hist[Var::NJETS]     = dynamic_cast<TEfficiency*>(m_file->Get( (TString("histograms/")+prefix+"njets_Eff").Data() ));
  m_hist[Var::NBTAG]     = dynamic_cast<TEfficiency*>(m_file->Get( (TString("histograms/")+prefix+"nbtag_Eff").Data() ));
  m_hist[Var::LPT]       = dynamic_cast<TEfficiency*>(m_file->Get( (TString("histograms/")+prefix+"l_pt_Eff").Data() ));
  m_hist[Var::LPT_E1J]       = dynamic_cast<TEfficiency*>(m_file->Get( (TString("histograms/")+prefix+"l_pt_e1j_Eff").Data() ));
  m_hist[Var::LPT_G1J]       = dynamic_cast<TEfficiency*>(m_file->Get( (TString("histograms/")+prefix+"l_pt_g1j_Eff").Data() ));
  m_hist[Var::LETA]      = dynamic_cast<TEfficiency*>(m_file->Get( (TString("histograms/")+prefix+"l_eta_Eff").Data() ));
  m_hist[Var::MINDRLJET] = dynamic_cast<TEfficiency*>(m_file->Get( (TString("histograms/")+prefix+"min_dR_l_jet_Eff").Data() ));
  m_hist[Var::DPHILMET]  = dynamic_cast<TEfficiency*>(m_file->Get( (TString("histograms/")+prefix+"dphi_l_met_Eff").Data() ));
  m_hist[Var::MET]       = dynamic_cast<TEfficiency*>(m_file->Get( (TString("histograms/")+prefix+"met_Eff").Data() ));
  m_hist[Var::MET_E1J]       = dynamic_cast<TEfficiency*>(m_file->Get( (TString("histograms/")+prefix+"met_e1j_Eff").Data() ));
  m_hist[Var::MET_G1J]       = dynamic_cast<TEfficiency*>(m_file->Get( (TString("histograms/")+prefix+"met_g1j_Eff").Data() ));
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
    m_hist[Var::TWODIM_PT_ETA]       = dynamic_cast<TEfficiency*>(m_file->Get( (TString("histograms/")+prefix+"2D_pt_eta").Data() ));
    m_hist[Var::TWODIM_PT_ETA_E1J]       = dynamic_cast<TEfficiency*>(m_file->Get( (TString("histograms/")+prefix+"2D_pt_eta_e1j").Data() ));
    m_hist[Var::TWODIM_PT_ETA_G1J]       = dynamic_cast<TEfficiency*>(m_file->Get( (TString("histograms/")+prefix+"2D_pt_eta_g1j").Data() ));
    m_hist[Var::TWODIM_PT_DPHI]      = dynamic_cast<TEfficiency*>(m_file->Get( (TString("histograms/")+prefix+"2D_pt_dphi").Data() ));
    m_hist[Var::TWODIM_PT_DPHI_E1J]      = dynamic_cast<TEfficiency*>(m_file->Get( (TString("histograms/")+prefix+"2D_pt_dphi_e1j").Data() ));
    m_hist[Var::TWODIM_PT_DPHI_G1J]      = dynamic_cast<TEfficiency*>(m_file->Get( (TString("histograms/")+prefix+"2D_pt_dphi_g1j").Data() ));
    m_hist[Var::TWODIM_PT_NBTAG]     = dynamic_cast<TEfficiency*>(m_file->Get( (TString("histograms/")+prefix+"2D_pt_nbtag").Data() ));
    m_hist[Var::TWODIM_PT_NBTAG_E1J]     = dynamic_cast<TEfficiency*>(m_file->Get( (TString("histograms/")+prefix+"2D_pt_nbtag_e1j").Data() ));
    m_hist[Var::TWODIM_PT_NBTAG_G1J]     = dynamic_cast<TEfficiency*>(m_file->Get( (TString("histograms/")+prefix+"2D_pt_nbtag_g1j").Data() ));
    m_hist[Var::TWODIM_PT_MET]       = dynamic_cast<TEfficiency*>(m_file->Get( (TString("histograms/")+prefix+"2D_pt_met").Data() ));
    m_hist[Var::TWODIM_PT_JET1PT]    = dynamic_cast<TEfficiency*>(m_file->Get( (TString("histograms/")+prefix+"2D_pt_jet1pt").Data() ));
    m_hist[Var::TWODIM_DPHI_NJETS]   = dynamic_cast<TEfficiency*>(m_file->Get( (TString("histograms/")+prefix+"2D_dphi_njets").Data() ));
    m_hist[Var::TWODIM_DPHI_NBTAG]   = dynamic_cast<TEfficiency*>(m_file->Get( (TString("histograms/")+prefix+"2D_dphi_nbtag").Data() ));
    m_hist[Var::TWODIM_DPHI_MET]     = dynamic_cast<TEfficiency*>(m_file->Get( (TString("histograms/")+prefix+"2D_dphi_met").Data() ));
    m_hist[Var::TWODIM_DPHI_ETA]     = dynamic_cast<TEfficiency*>(m_file->Get( (TString("histograms/")+prefix+"2D_dphi_eta").Data() ));
    m_hist[Var::TWODIM_DPHI_ETA_E1J]     = dynamic_cast<TEfficiency*>(m_file->Get( (TString("histograms/")+prefix+"2D_dphi_eta_e1j").Data() ));
    m_hist[Var::TWODIM_DPHI_ETA_G1J]     = dynamic_cast<TEfficiency*>(m_file->Get( (TString("histograms/")+prefix+"2D_dphi_eta_g1j").Data() ));
    m_hist[Var::TWODIM_ETA_NBTAG]    = dynamic_cast<TEfficiency*>(m_file->Get( (TString("histograms/")+prefix+"2D_eta_nbtag").Data() ));
    m_hist[Var::TWODIM_JET1PT_DPHI]  = dynamic_cast<TEfficiency*>(m_file->Get( (TString("histograms/")+prefix+"2D_jet1pt_dphi").Data() ));
    m_hist[Var::TWODIM_JET1PT_DPHI_E1J]  = dynamic_cast<TEfficiency*>(m_file->Get( (TString("histograms/")+prefix+"2D_jet1pt_dphi_e1j").Data() ));
    m_hist[Var::TWODIM_JET1PT_DPHI_G1J]  = dynamic_cast<TEfficiency*>(m_file->Get( (TString("histograms/")+prefix+"2D_jet1pt_dphi_g1j").Data() ));
    m_hist[Var::TWODIM_JET1PT_NJETS] = dynamic_cast<TEfficiency*>(m_file->Get( (TString("histograms/")+prefix+"2D_jet1pt_njets").Data() ));
    m_hist[Var::TWODIM_JET1PT_NBTAG] = dynamic_cast<TEfficiency*>(m_file->Get( (TString("histograms/")+prefix+"2D_jet1pt_nbtag").Data() ));
    m_hist[Var::TWODIM_NJETS_NBTAG]  = dynamic_cast<TEfficiency*>(m_file->Get( (TString("histograms/")+prefix+"2D_njets_nbtag").Data() ));
  } else if (type==Type::realEff) {
    m_hist[Var::TWODIM_PT_ETA]       = dynamic_cast<TEfficiency*>(m_file->Get( (TString("histograms/")+prefix+"2D_pt_eta_Eff").Data() ));
    m_hist[Var::TWODIM_PT_DPHI]      = dynamic_cast<TEfficiency*>(m_file->Get( (TString("histograms/")+prefix+"2D_pt_dphi_Eff").Data() ));
    m_hist[Var::TWODIM_NJETS_NBTAG]  = dynamic_cast<TEfficiency*>(m_file->Get( (TString("histograms/")+prefix+"2D_njets_nbtag_Eff").Data() ));
  }
  
  m_average=-1;
  if (m_hist[Var::NJETS]) {
    m_average = m_hist[Var::NJETS]->GetPassedHistogram()->Integral(0,100) / m_hist[Var::NJETS]->GetTotalHistogram()->Integral(0,100);
  } else if (m_hist[Var::LPT]) {
    m_average = m_hist[Var::LPT]->GetPassedHistogram()->Integral(0,100) / m_hist[Var::LPT]->GetTotalHistogram()->Integral(0,100);
  } else {
    Warning("FakeEffProvider", "Couldn't get the average efficiency!");
  }
}

//____________________________________________________________________________________________________

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
    Warning("FakeEffProvider", "GetRightBin: v < min !!! returning first non-zero bin");
    return firstBin;
  }
  else if (v >= max)
    return lastBin;
  else
    return h->FindFixBin(v);
}

//____________________________________________________________________________________________________

double FakeEffProvider::GetEfficiency(int var, float value, bool binned) {
  if (binned) { //binned efficiency
    std::map<int, TEfficiency*>::iterator it = m_hist.find(var);
    if (it==m_hist.end() || (*it).second==0) {
      Error("FakeEffProvider", "Efficiency histogram for variable %d not found", var);
      throw(EXIT_FAILURE);
    }
    else {
      TEfficiency* eff = (*it).second;
      int bin = GetRightBin(eff, value);
      if (m_syst==Systematic::stat_U)
        return eff->GetEfficiency(bin) + ErrorFuncWrapper(eff,bin,1.0,true,true);
      else if (m_syst==Systematic::stat_D)
        return eff->GetEfficiency(bin) - ErrorFuncWrapper(eff,bin,1.0,false,true);
      else //nominal
        return eff->GetEfficiency(bin);
    }
  }
  else { //fitted efficiency
    if (m_syst != Systematic::nominal) {
      Error("FakeEffProvider", "Configuration error: systematic variations of fitted efficiencies are not implemented!");
      throw(EXIT_FAILURE);
    }
    std::map<int, TF1*>::iterator it = m_func.find(var);
    if (it==m_func.end() || (*it).second==0) {
      Error("FakeEffProvider", "Efficiency function for variable %d not found", var);
      throw(EXIT_FAILURE);
    } 
    else {
      TF1* f = (*it).second;
      return f->Eval(value);
    }
  }
}

//____________________________________________________________________________________________________

int FakeEffProvider::GetRightBin2D(TEfficiency* eff, double vx, double vy) {
  
  const TH1* h = eff->GetPassedHistogram();
  //this doesn't necessarily mean the efficiency is well defined and calculated in this bin
  //a workaround for this problem is implemented downstream in the GetEfficiency2D method
  double x_min = h->GetXaxis()->GetBinLowEdge(h->FindFirstBinAbove(0,1));
  double x_max = h->GetXaxis()->GetBinLowEdge(h->FindLastBinAbove(0,1)+1);
  double y_min = h->GetYaxis()->GetBinLowEdge(h->FindFirstBinAbove(0,2));
  double y_max = h->GetYaxis()->GetBinLowEdge(h->FindLastBinAbove(0,2)+1);
  
  int binx=1;
  int biny=1;
  
  if (vx < x_min) {
    Warning("FakeEffProvider", "GetRightBin2D: vx < x_min !!! returning value from the first x-bin");
    vx=x_min;
  } 
  else if (vx >= x_max) {
    vx=h->GetXaxis()->GetBinLowEdge(h->GetNbinsX());
  }
  if (vy < y_min) {
    Warning("FakeEffProvider", "GetRightBin2D: vy < y_min !!! returning value from the first y-bin");
    vy=y_min;
  }
  else if (vy >= y_max) {
    vy=h->GetYaxis()->GetBinLowEdge(h->GetNbinsY());
  }

  return h->FindFixBin(vx,vy);
  
}

//____________________________________________________________________________________________________

double FakeEffProvider::GetEfficiency2D(int var, float xvalue, float yvalue, bool binned) {
  if (binned) {
    std::map<int, TEfficiency*>::iterator it = m_hist.find(var);
    if (it==m_hist.end() || (*it).second==0) {
      Error("FakeEffProvider", "Efficiency histogram for variable %d not found", var);
      throw(EXIT_FAILURE);
    }
    else {
      TEfficiency* eff = (*it).second;
      int bin = GetRightBin2D(eff, xvalue, yvalue);
      double result = eff->GetEfficiency(bin);
      double error = 0;
      if (result==0) { //if bin is missing, take the average of neighbouring bins
        int binx,biny,binz;
        eff->GetTotalHistogram()->GetBinXYZ(bin,binx,biny,binz);
        int binleft  = eff->GetTotalHistogram()->GetBin(binx-1,biny);
        int binright = eff->GetTotalHistogram()->GetBin(binx+1,biny);
        int bindown  = eff->GetTotalHistogram()->GetBin(binx,biny-1);
        int binup    = eff->GetTotalHistogram()->GetBin(binx,biny+1);
        int nAvg = 0;
        for (int thebin : {binleft, binright, bindown, binup}) {
          double theeff = eff->GetEfficiency(thebin);
          if (theeff==0) continue;
          
          double theerror = 0;
          if (m_syst==Systematic::stat_U)
            theerror = ErrorFuncWrapper(eff,thebin,1.0,true,true);
          else if (m_syst==Systematic::stat_D)
            theerror = -ErrorFuncWrapper(eff,thebin,1.0,false,true);
            
          result += theeff;
          error += theerror;
          
          ++nAvg;
        }
        if (nAvg==0) {//hopeless case - should be avoided by rebinning the efficiency
          Error("Utils::FakeEffProvider","Empty 2D efficiency %s bin %d, %d with only empty bins surrounding it. Unable to obtain efficiency, please rebin! (x,y)=(%f,%f)",eff->GetName(),binx,binz,xvalue,yvalue);
          throw(EXIT_FAILURE);
        }
        result /= (1.*nAvg);
        error /= (1.*nAvg);
      } else {
        if (m_syst==Systematic::stat_U)
          error = ErrorFuncWrapper(eff,bin,1.0,true,true);
        else if (m_syst==Systematic::stat_D)
          error = -ErrorFuncWrapper(eff,bin,1.0,false,true);
      }
      return result + error;
    }
    
  }
  else {
      Error("FakeEffProvider", "Fitted 2D efficiencies are not implemented yet!");
      throw(EXIT_FAILURE);
  }
}

//____________________________________________________________________________________________________

double FakeEffProvider::ErrorFuncWrapper(TEfficiency* eff, int bin, double z=1.0, bool upper=false, bool correlated=false) {
  return m_ErrorFunc(
    eff->GetPassedHistogram()->GetBinContent(bin),
    eff->GetTotalHistogram()->GetBinContent(bin),
    eff->GetPassedHistogram()->GetBinError(bin),
    eff->GetTotalHistogram()->GetBinError(bin),
    z, upper, correlated
  );
}

//____________________________________________________________________________________________________
  
/**
 * Normal approximation for simple binomial case
 */
double FakeEffProvider::ErrorWald(double nPas, double nTot, double ePas=-1, double eTot=-1, double z=1.0, bool upper=false, bool correlated=false) {
  double eff = nPas/nTot;
  double var = eff*(1-eff)/nTot;
  double err = z*sqrt(var);
  if (!upper && nPas/nTot - err < 0) return nPas/nTot;
  else if (upper && nPas/nTot + err > 1) return 1.-nPas/nTot;
  else return err;
}

//____________________________________________________________________________________________________
  
/**
 * Normal approximation for non-binomial case
 */
double FakeEffProvider::ErrorNormal(double nPas, double nTot, double ePas, double eTot, double z=1.0, bool upper=false, bool correlated=false) {
  double ePas2 = (ePas<0) ? nPas : pow(ePas,2);
  double eTot2 = (eTot<0) ? nTot : pow(eTot,2);
  
  double invTot = 1.0/nTot;
  
  double var = (correlated) ? 
    pow(invTot,2)*ePas2 + pow(nPas,2)*pow(invTot,4)*eTot2  - 2*nPas*pow(invTot,3)*ePas2
  : pow(invTot,2)*ePas2 + pow(nPas,2)*pow(invTot,4)*eTot2  - 2*nPas*pow(invTot,3)*nPas;

  if (var<0) {
    //Warning("FakeEffProvider::ErrorNormal","Ill-defined relative uncertainties of numerator and denominator yielding negative variance. Returning Wald interval instead.");
    return ErrorWald(nPas,nTot,ePas,eTot,z,upper);
  }
  
  double err = z*sqrt(var);
  if (!upper && nPas/nTot - err < 0) return nPas/nTot;
  else if (upper && nPas/nTot + err > 1) return 1.-nPas/nTot;
  else return err;
}

//____________________________________________________________________________________________________

/**
 * Agresti-Coull method applied to non-binomial case
 */
double FakeEffProvider::ErrorAC(double nPas, double nTot,  double ePas, double eTot, double z=1.0, bool upper=false, bool correlated=false) {
  double nTotAC = nTot+z*z;
  double nPasAC = nPas+0.5*z*z;
  double effAC = nPasAC/nTotAC;
  double ePasScale = nPasAC/nPas;
  double eTotScale = nTotAC/nTot;
  if(ePas>0) ePas=(ePas/sqrt(nPas))*sqrt(nPasAC);
  else ePas=sqrt(nPasAC);
  if(eTot>0) eTot=(eTot/sqrt(nTot))*sqrt(nTotAC);
  else eTot=sqrt(nTotAC);
  
  double invTotAC = 1.0/nTotAC;
  double varAC = (correlated) ? 
    pow(invTotAC,2)*pow(ePas,2) + pow(nPasAC,2)*pow(invTotAC,4)*pow(eTot,2) - 2*nPasAC*pow(invTotAC,3)*pow(ePas,2)
  : pow(invTotAC,2)*pow(ePas,2) + pow(nPasAC,2)*pow(invTotAC,4)*pow(eTot,2) - 2*nPasAC*pow(invTotAC,3)*nPasAC;
  
  if (varAC<0) {
    //Warning("FakeEffProvider::ErrorAC","Ill-defined relative uncertainties of numerator and denominator yielding negative variance. Returning Wald interval instead.");
    return ErrorWald(nPas,nTot,ePas,eTot,z,upper);
  }
  
  if (upper) {
    double lim = effAC + z*sqrt(varAC);
    if (lim>1) lim=1;
    return lim - nPas/nTot;
  }
  else {
    double lim = effAC - z*sqrt(varAC);
    if (lim<0) lim=0;
    return nPas/nTot - lim;
  }
}
#endif