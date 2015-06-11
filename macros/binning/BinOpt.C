#include "TTree.h"
#include "TROOT.h"
#include "TStyle.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TString.h"
#include "TLine.h"
#include "TPaveStats.h"
#include "TH1.h"
#include "TH1D.h"
#include "TH2.h"
#include "TH2D.h"
#include "THStack.h"
#include "TMath.h"
#include "TF1.h"
#include "TLatex.h"
#include "TList.h"
#include "TMath.h"
#include "TMathBase.h"
#include "TChain.h"
#include "TLegend.h"
#include "TGraphErrors.h"
#include "TPaveLabel.h"

#include <iostream>
#include <fstream>

using namespace std;

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------
//Slicing and fiting function
TGraphErrors *SliceFit(const TH2D *resmat,const TString type,const TString name)
{
       Int_t nbins,binstop=0;
       double_t upEdge,lowEdge,xl,xm,fitmean;
       
       TFile *profs=new TFile("profiles.root","recreate");
       
       //name=resmat->GetXaxis()->GetTitle();
       TString pop, popobr;
       TString title="SlicesDiag_";
       title+=type;
       title+="_";
       title+=name;
       pop=title;
       popobr+=title;
       popobr+=".png";
       title+=".txt";
  
       bool almok;
       
       double_t unzero;
       bool itsok=true;
       
       ofstream rmss;
       rmss.open(title);
       rmss<<"Variable: "<<name<<" , Type of top: "<<type<<endl;
       rmss<<endl;
       

       
       nbins=resmat->GetXaxis()->GetNbins();

       lowEdge=resmat->GetXaxis()->GetXmin();
       upEdge=resmat->GetXaxis()->GetXmax();
       
       TString strName[nbins];
       TH1D *Slices[nbins];
       double_t rms[nbins],rmserr[nbins],bincont;
       double_t vari[nbins],binwdth[nbins],Rms[nbins],chisquare[nbins],ndf[nbins],chindf[nbins],rmsrat[nbins],mean,difmean[nbins],dummy[nbins],dummy2[nbins];
       	TCanvas *slican=new TCanvas("slican",pop);
	
	slican->Clear();
	slican->Divide(7,7);
	
	
	
       
       for(Int_t i=0;i<nbins;i++)
      {	
	if (i<49)slican->cd(i+1);
	  //gPad->SetLogy();
	  unzero=0;
	  almok=false;
	  strName[i]="Prof";
	  strName[i]+=i;
	  strName[i]+="_";
	  strName[i]+=name;
	  strName[i]+="_";
	  strName[i]+=type;
	  
	  Slices[i]=new TH1D(strName[i],strName[i],nbins,lowEdge,upEdge);
	  
	  binwdth[i]=(lowEdge-upEdge)/nbins;
	  
	  for (Int_t j=0; j<nbins;j++)
	  {
		 bincont=0;
		 
		 bincont=resmat->GetBinContent(j+1,i+1);//slicing along X axis to get reco resolution for binning, slicing trough truth bins
		 if (!(bincont==0))unzero+=1;
		 Slices[i]->SetBinContent(j+1,bincont);
		 vari[i]=resmat->GetXaxis()->GetBinCenter(i+1);
	  }//end of j loop

	 rms[i]=0.;
	 rmserr[i]=0.;
	      
	 if (unzero>=4)almok=true;
	 
	  if (almok==true && itsok==true && Slices[i]->GetEntries()>(nbins-2))
	  {
	      if (name=="dPhi")Slices[i]->Rebin(4);
	      Rms[i]=Slices[i]->GetRMS();
	      mean=Slices[i]->GetMean();
	      xl=mean-2*Rms[i];
	      //if (xl<0)xl=0;
	      xm=mean+2*Rms[i];
	      TF1 *g1=new TF1("g1","gaus",xl,xm);
	      Slices[i]->Fit("g1");
	      TF1 *f1=Slices[i]->GetFunction("g1");
	      xl=(f1->GetParameter(1))-2*(f1->GetParameter(2));
	      xm=(f1->GetParameter(1))+2*(f1->GetParameter(2));
	      TF1 *g2=new TF1("g2","gaus",xl,xm);
	      Slices[i]->Fit("g2");
	      f1=Slices[i]->GetFunction("g2");
	      rms[i]=f1->GetParameter(2);
	      rmserr[i]=f1->GetParError(2);
	      if(rmserr[i]>20.)itsok=false;
	      if(name.Contains("Pout"))itsok=true;
	      if(name.Contains("pseudo"))itsok=true;
	      binstop=i;
	      fitmean=f1->GetParameter(1);
	      dummy[i]=i;
	      chisquare[i]=f1->GetChisquare();
	      ndf[i]=f1->GetNDF();
	      chindf[i]=chisquare[i]/ndf[i];
	      rmsrat[i]=rms[i]/Rms[i];
	      dummy2[i]=resmat->GetYaxis()->GetBinCenter(i+1);
	      difmean[i]=(mean-fitmean)/dummy2[i];
	      rmss<<"Slice number:"<<i<<"; chisquare/ndf: "<<chisquare[i]<<"/"<<ndf[i]<<"="<<chindf[i]<<"; #sigma_{fit}/RMS of slice: "<<rms[i]<<"/"<<Rms[i]<<"="<<rmsrat[i]<<endl;
	  }
	  
 	}//end of i loop
	slican->Print(popobr);
	slican->Close();
	
	TGraph *grmeans=new TGraph(binstop,dummy,difmean);
	TGraph *ndfs=new TGraph(binstop,dummy,chindf);
	TGraph *rmsgr=new TGraph(binstop,dummy,rmsrat); 
	TString naz1="MeanDiag_";
	TString naz="SliceDiag_";
	naz+=type;
	naz+="_";
	naz+=name;
	naz1+=type;
	naz1+="_";
	naz1+=name;
	TString canname="Slice diagnosis";
	canname+=naz;
	naz+=".png";
	naz1+=".png";
	
	TCanvas *means=new TCanvas("means",naz1);
	means->cd(1);
	
	grmeans->Draw();
	grmeans->SetTitle("(Mean - Fitmean)/truth_bin_value");
	grmeans->GetXaxis()->SetTitle("Fitted slice number");
	grmeans->GetYaxis()->SetTitle("Mean -Fitmean");
	grmeans->GetYaxis()->SetTitleOffset(1.4);
	grmeans->GetHistogram()->SetMaximum(0.1);
	grmeans->GetHistogram()->SetMinimum(-0.1);
	grmeans->SetLineColor(4);
	grmeans->SetMarkerStyle(21);
	grmeans->SetMarkerSize(1);
	grmeans->SetMarkerColor(4);
	means->Print(naz1);
	//means->Close();
	
 	TCanvas *diag=new TCanvas("diag",canname);
	diag->Divide(2,1);
	diag->cd(1);
	ndfs->Draw();
	ndfs->SetTitle("#Chi^{2}/NDF");
	ndfs->GetXaxis()->SetTitle("Fitted slice number");
	ndfs->GetYaxis()->SetTitle("#Chi^{2}/NDF");
	ndfs->GetYaxis()->SetTitleOffset(1.4);
	ndfs->SetLineColor(4);
	ndfs->SetMarkerStyle(21);
	ndfs->SetMarkerSize(1);
	ndfs->SetMarkerColor(4);	
	diag->cd(2);
	rmsgr->Draw();
	rmsgr->SetTitle("#sigma_{fit}/RMS ratio");
	rmsgr->GetXaxis()->SetTitle("Fitted slice number");
	rmsgr->GetYaxis()->SetTitle("#sigma_{fit}/RMS");
	rmsgr->GetYaxis()->SetTitleOffset(1.4);
	rmsgr->SetLineColor(4);
	rmsgr->SetMarkerStyle(21);
	rmsgr->SetMarkerSize(1);
	rmsgr->SetMarkerColor(4);
	diag->Print(naz);
	diag->Close();

 	rmss<<"End of fitting slices, number of posible slices: "<<nbins<<endl;
 	rmss.close();
	profs->Write();
 	TGraphErrors *RMS=new TGraphErrors(binstop,vari,rms,binwdth,rmserr);
	return RMS;
}//end of SliceFit
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//binning evaluation function
void EvalBins(TGraphErrors *RMS,TString Name)
{
  double_t x_start=RMS->GetXaxis()->GetXmin();
  double_t x_end=RMS->GetXaxis()->GetXmax();
  
  TString title=RMS->GetTitle();
  TString ftitle="Binning_"+Name+".txt";
  TString ptitle="Binning_"+Name+"_pol.png";
  //TString ptitle="Binning_"+Name+"_exp.png";
 
  Int_t col=RMS->GetLineColor();
   //([0]+[1]*x+[2]*x*x) původně
  TF1 *ResFnc=new TF1("res","[0]+[1]*x+[2]*x*x",x_start,x_end); 
 // TF1 *ResFnc=new TF1("res","[0]+[1]*exp([2]+[3]*x)",x_start,x_end);
  
  ResFnc->SetLineColor(col);
  ResFnc->SetParameters(30.,0.01,0.001); //polfit
  //ResFnc->SetParameters(30.,0.01,0.001,0.001); //expfit
 // ResFnc->SetParLimits(0,0,100);
 // ResFnc->SetParLimits(1,0.,1.);
  //ResFnc->SetParLimits(2,0.,1000);

  RMS->Fit(ResFnc);
 // RMS->Fit(ResFnc);
  double_t ndf=ResFnc->GetNDF();
  double_t chi=ResFnc->GetChisquare();
  double_t chindf;
  if (!(ndf==0)) chindf=chi/ndf;
  //else double_t chindf=0;
  double_t dif=0;
  
  TCanvas *c1= new TCanvas("fit","fit");
  c1->Clear();
  //c1->cd(1);
  RMS->Draw();
  ResFnc->Draw("same");
  if(Name.Contains("rap"))
  {
    RMS->GetHistogram()->SetMaximum(0.2);
    RMS->GetHistogram()->SetMinimum(0.);	
    if (Name.Contains("lep"))RMS->GetHistogram()->SetMaximum(0.5);
  }
  char buf[128];
  sprintf( buf, "#Chi^{2}/NDF: %3.2f", chindf );
  TLatex l;
  l.SetTextSize(0.04); 
  l.SetNDC();
  l.SetTextColor(kBlack);
  l.DrawLatex(0.1,0.92,buf);
  

  c1->Print(ptitle);
  
  c1->Close();
   
  ofstream out;
  out.open(ftitle);
  
  out<<title<<" :chisquare/ndf "<<chindf<<endl;
  if(Name=="rap_had")x_start=-2.4;
  if(Name.Contains("m_"))x_start=225;
//  if(Name.Contains("Salam"))x_start=-0.7;
  if(Name.Contains("R_lb"))x_start=0.1;
 // if(Name.Contains("HT_pseudo"))x_start=300.;
  //if(Name.Contains("dPhi"))x_start=.8;
  double_t p0=ResFnc->GetParameter(0);
  double_t p1=ResFnc->GetParameter(1);
  double_t p2=ResFnc->GetParameter(2);
 //double_t p3=ResFnc->GetParameter(3); //expfit only
 // double_t p4=ResFnc->GetParameter(4);
  double_t delta=1;
  double_t binEdge=x_start;
 // x_start=0.;
  double_t stor=x_start;
  
  while (binEdge<x_end)
  {
    
    TF1 *fbin=new TF1("fbin","[0]*[1]+[0]*[2]*x+[0]*[3]*x*x-x+[4]",x_start,x_end);     //polfit
    fbin->SetParameters(delta,p0,p1,p2,binEdge);
 //     TF1 *fbin=new TF1("fbin","[0]*[1]+[0]*[2]*exp([3]+[4]*x)-x+[5]",x_start,x_end);	 //expfit
  //    fbin->SetParameters(delta,p0,p1,p2,p3,binEdge);
    
    double_t prec=0.01;
    double_t step=x_end;
    while(step>x_start)
    {
      double_t val=fbin->Eval(step);
      if (val>prec)break;
      step-=prec;
    }
    stor+=dif;
    //dif=binEdge-dif;
    binEdge=2*(step-binEdge)+binEdge;
    dif=binEdge-stor;
    out<<"bin edge: "<<binEdge<<"; bin width: "<<dif<<endl;
 //     cout<<binEdge<<endl;
  }
  out<<endl;
  out<<endl;
  out.close();
}//end of EvalBins
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void BinOpt (TString type="all",TString var="all")
{
  TFile *in=new TFile("histograms_PowHeg_ll_incl.root", "read");
  
  if (!(type=="tt"||type=="lep"||type=="had"||type=="all"||type=="W"))
  {
    cout<<"Wrong type of quark"<<endl;
    return;
  }
  if (!(var=="R_lb"||var=="R_Wb_had"||var=="pt"||var=="all"||var=="m"||var=="absrap"||var=="rap"||var=="Pout"||var=="zttbar"||var=="dPhi"||var=="Ht"||var=="Salam"||var=="yboost"||var=="chittbar")) 
  {
    cout<<"Wrong variable"<<endl;
    return;
  }
  if((var=="m"||var=="Pout"||var=="zttbar"||var=="dPhi")&&(type=="lep"||type=="had"))
  {
    cout<<"Wrong parameter combination"<<endl;//add W wrong combos
  }
  
  TH2D *resmat_W_pt,*resmat_W_y,*resmat_R_lb,*resmat_R_Wb_had,*resmat_tt_Salam,*resmat_tt_yboost,*resmat_tt_chittbar,*resmat_pt_lep,*resmat_pt_had,*resmat_pt_tt,*resmat_m_tt,*resmat_y_tt,*resmat_y_lep,*resmat_y_had,*resmat_abs_tt,*resmat_Ht_tt,*resmat_Ht_pseudo,*resmat_abs_lep,*resmat_abs_had,*resmat_Pout,*resmat_zttbar,*resmat_dPhi;

  if (type=="W"||type=="all")
  {
      if (var=="pt"||var=="all")
      {
	resmat_W_pt=(TH2D*)in->Get("reco/4j2b/WH/Matrix_reco_particle_pt_1");
	
	TGraphErrors *W_ptRms=SliceFit(resmat_W_pt,"W","pt");
	
      TCanvas *W_pt=new TCanvas("W_pt","Transverse momentum of hadronic W");
      W_pt->cd(1);
      W_ptRms->Draw();
      W_ptRms->SetTitle("");
      W_ptRms->GetXaxis()->SetTitle("p_{T} [GeV]");
      W_ptRms->GetYaxis()->SetTitle("#sigma_{fit}");
      W_ptRms->GetYaxis()->SetTitleOffset(1.4);
      W_ptRms->SetLineColor(4);
      W_ptRms->SetMarkerStyle(21);
      W_ptRms->SetMarkerSize(1);
      W_ptRms->SetMarkerColor(4);
      
      EvalBins(W_ptRms,"W_pt");
      }//end of W pt
  
      if (var=="y"||var=="all")
      {
	resmat_W_y=(TH2D*)in->Get("reco/4j2b/WH/Matrix_reco_particle_rapidity_1");
  
	TGraphErrors *W_yRms=SliceFit(resmat_W_y,"W","absrap");
	
      TCanvas *W_y=new TCanvas("W_y","Rapidity of hadronic W");
      W_y->cd(1);
      W_yRms->Draw();
      W_yRms->SetTitle("");
      W_yRms->GetXaxis()->SetTitle("y");
      W_yRms->GetYaxis()->SetTitle("#sigma_{fit}");
      W_yRms->GetYaxis()->SetTitleOffset(1.4);
      W_yRms->SetLineColor(4);
      W_yRms->SetMarkerStyle(21);
      W_yRms->SetMarkerSize(1);
      W_yRms->SetMarkerColor(4);
      
      EvalBins(W_yRms,"W_y");
      }//end of W y
      
      if (var=="R_lb"||var=="all")
      {
	resmat_R_lb=(TH2D*)in->Get("reco/4j2b/difference/Matrix_reco_particle_R_lb_1");
	
	TGraphErrors *R_lbRms=SliceFit(resmat_R_lb,"W","R_lb");
	
      TCanvas *R_lb=new TCanvas("R_lb","Ratio of light jets and b-taged jets");
      R_lb->cd(1);
      R_lbRms->Draw();
      R_lbRms->SetTitle("");
      R_lbRms->GetXaxis()->SetTitle("R_lb");
      R_lbRms->GetYaxis()->SetTitle("#sigma_{fit}");
      R_lbRms->GetYaxis()->SetTitleOffset(1.4);
      R_lbRms->SetLineColor(4);
      R_lbRms->SetMarkerStyle(21);
      R_lbRms->SetMarkerSize(1);
      R_lbRms->SetMarkerColor(4);
      
      EvalBins(R_lbRms,"R_lb");
      }//end of R_lb
 
      if (var=="R_Wb"||var=="all")
      {
	resmat_R_Wb_had=(TH2D*)in->Get("reco/4j2b/difference/Matrix_reco_particle_R_Wb_had_1");
	
	TGraphErrors *R_WbRms=SliceFit(resmat_R_Wb_had,"W","R_Wb");
	
      TCanvas *R_Wb=new TCanvas("R_Wb","Ratio of hadronic W pt and b-jet pt");
      R_Wb->cd(1);
      R_WbRms->Draw();
      R_WbRms->SetTitle("");
      R_WbRms->GetXaxis()->SetTitle("R_Wb");
      R_WbRms->GetYaxis()->SetTitle("#sigma_{fit}");
      R_WbRms->GetYaxis()->SetTitleOffset(1.4);
      R_WbRms->SetLineColor(4);
      R_WbRms->SetMarkerStyle(21);
      R_WbRms->SetMarkerSize(1);
      R_WbRms->SetMarkerColor(4);
      
      EvalBins(R_WbRms,"R_Wb");
      }//end of R_Wb
  }//end of W

  if (type=="tt"||type=="all")
  {
     if (var=="all"||var=="yboost")
     {
      resmat_tt_yboost=(TH2D*)in->Get("reco/4j2b/difference/Matrix_reco_particle_Yboost_1"); 
 
      TGraphErrors *YboostRms=SliceFit(resmat_tt_yboost,"tt","yboost");
   
      TCanvas *Yboost=new TCanvas("yboost","Boost of ttbar system");
      Yboost->cd(1);
      YboostRms->Draw();
      YboostRms->SetTitle("");
      YboostRms->GetXaxis()->SetTitle("y_{boost}");
      YboostRms->GetYaxis()->SetTitle("#sigma_{fit}");
      YboostRms->GetYaxis()->SetTitleOffset(1.4);
      YboostRms->SetLineColor(4);
      YboostRms->SetMarkerStyle(21);
      YboostRms->SetMarkerSize(1);
      YboostRms->SetMarkerColor(4);
      
      EvalBins(YboostRms,"y_boost");
     }
    
     if (var=="all"||var=="chittbar")
     {
      resmat_tt_chittbar=(TH2D*)in->Get("reco/4j2b/difference/Matrix_reco_particle_Chi_ttbar_1"); 
 
      TGraphErrors *ChiRms=SliceFit(resmat_tt_chittbar,"tt","Chi");
   
      TCanvas *Chi=new TCanvas("Chi","Chi variable.");
      Chi->cd(1);
      ChiRms->Draw();
      ChiRms->SetTitle("");
      ChiRms->GetXaxis()->SetTitle("#Chi_{t#bar{t}}");
      ChiRms->GetYaxis()->SetTitle("#sigma_{fit}");
      ChiRms->GetYaxis()->SetTitleOffset(1.4);
      ChiRms->SetLineColor(4);
      ChiRms->SetMarkerStyle(21);
      ChiRms->SetMarkerSize(1);
      ChiRms->SetMarkerColor(4);
      
      EvalBins(ChiRms,"chi_ttbar");
     }
    
     if (var=="all"||var=="Ht")
     {
      resmat_Ht_pseudo=(TH2D*)in->Get("reco/4j2b/difference/Matrix_reco_particle_HT_pseudo_1"); 
 
      TGraphErrors *HtpsRms=SliceFit(resmat_Ht_pseudo,"tt","HT_pseudo");
   
      TCanvas *Htps=new TCanvas("Htps","Sum of transversal momentum of all pseudotop elements");
      Htps->cd(1);
      HtpsRms->Draw();
      HtpsRms->SetTitle("");
      HtpsRms->GetXaxis()->SetTitle("H_{T}^{pseudo} [GeV]");
      HtpsRms->GetYaxis()->SetTitle("#sigma_{fit}[GeV]");
      HtpsRms->GetYaxis()->SetTitleOffset(1.4);
      HtpsRms->SetLineColor(4);
      HtpsRms->SetMarkerStyle(21);
      HtpsRms->SetMarkerSize(1);
      HtpsRms->SetMarkerColor(4);
      
      EvalBins(HtpsRms,"Ht_pseudo");
     }
     
     if (var=="all"||var=="Pout")
     {
      resmat_Pout=(TH2D*)in->Get("reco/4j2b/difference/Matrix_reco_particle_Pout_1"); 
 
      TGraphErrors *PoutRms=SliceFit(resmat_Pout,"tt","Pout");
   
      TCanvas *ttPout=new TCanvas("ttPout","Out of plane momentum of ttbar system 50 eq. bins");
      ttPout->cd(1);
      PoutRms->Draw();
      PoutRms->SetTitle("");
      PoutRms->GetXaxis()->SetTitle("Pout [GeV]");
      PoutRms->GetYaxis()->SetTitle("#sigma_{fit}[GeV]");
      PoutRms->GetYaxis()->SetTitleOffset(1.4);
      PoutRms->SetLineColor(4);
      PoutRms->SetMarkerStyle(21);
      PoutRms->SetMarkerSize(1);
      PoutRms->SetMarkerColor(4);
      
      EvalBins(PoutRms,"Pout_tt");      
     }
     
     if (var=="all"||var=="zttbar")
     {
      resmat_zttbar=(TH2D*)in->Get("reco/4j2b/difference/Matrix_reco_particle_z_ttbar_1"); 
      
      TGraphErrors *zttbarRms=SliceFit(resmat_zttbar,"tt","z_ttbar");
      
      TCanvas *czttbar=new TCanvas("czttbar","Ratio of pt of had. and lep. top of ttbar system, 100 eq. bins");
      czttbar->cd(1);
      zttbarRms->Draw();
      zttbarRms->SetTitle("");
      zttbarRms->GetXaxis()->SetTitle("z_ttbar");
      zttbarRms->GetYaxis()->SetTitle("#sigma_{fit}");
      zttbarRms->GetYaxis()->SetTitleOffset(1.4);
      zttbarRms->SetLineColor(4);
      zttbarRms->SetMarkerStyle(21);
      zttbarRms->SetMarkerSize(1);
      zttbarRms->SetMarkerColor(4);
      
      EvalBins(zttbarRms,"z_tt");      
     }
     
     if (var=="all"||var=="dPhi")
     {
      resmat_dPhi=(TH2D*)in->Get("reco/4j2b/difference/Matrix_reco_particle_dPhi_ttbar_1"); 
      
      TGraphErrors *dPhiRms=SliceFit(resmat_dPhi,"tt","dPhi");
      
      TCanvas *cdPhi=new TCanvas("cdPhi","Difference between Phi angles of ttbar system, 100 eq. bins");
      cdPhi->cd(1);
      dPhiRms->Draw();
      dPhiRms->SetTitle("");
      dPhiRms->GetXaxis()->SetTitle("dPhi");
      dPhiRms->GetYaxis()->SetTitle("#sigma_{fit}");
      dPhiRms->GetYaxis()->SetTitleOffset(1.4);
      dPhiRms->SetLineColor(4);
      dPhiRms->SetMarkerStyle(21);
      dPhiRms->SetMarkerSize(1);
      dPhiRms->SetMarkerColor(4);
      
      EvalBins(dPhiRms,"dPhi_tt");      
     }
     
     if (var=="all"||var=="pt")
     {
       resmat_pt_tt=(TH2D*)in->Get("reco/4j2b/tt/Matrix_reco_particle_pt_1");
    
       TGraphErrors *PtRmsEl=SliceFit(resmat_pt_tt,"tt","pt");
 
	TCanvas *ttpt=new TCanvas("ttpt","TTbar transversal momentum 50 eq. binning");
	ttpt->cd(1);
	PtRmsEl->Draw();
	PtRmsEl->SetTitle("");
	PtRmsEl->GetXaxis()->SetTitle("pT [GeV]");
	PtRmsEl->GetYaxis()->SetTitle("#sigma_{fit} [GeV]");
	PtRmsEl->GetYaxis()->SetTitleOffset(1.4);
	PtRmsEl->SetLineColor(4);
	PtRmsEl->SetMarkerStyle(21);
	PtRmsEl->SetMarkerSize(1);
	PtRmsEl->SetMarkerColor(4);	  
	
	EvalBins(PtRmsEl,"pt_tt");
      }//end of TT pt
     
     if (var=="all"||var=="m")
     {
       resmat_m_tt=(TH2D*)in->Get("reco/4j2b/tt/Matrix_reco_particle_m_1");
       
 	TGraphErrors *MRmsEl=SliceFit(resmat_m_tt,"tt","m");
	  
	TCanvas *ttm=new TCanvas("ttm","TTbar mass  50 eq. binning");
	ttm->cd(1);
	MRmsEl->Draw();
	MRmsEl->SetTitle("");
	MRmsEl->GetXaxis()->SetTitle("m [GeV]");
	MRmsEl->GetYaxis()->SetTitle("#sigma_{fit} [GeV]");
	MRmsEl->GetYaxis()->SetTitleOffset(1.4);
	MRmsEl->SetLineColor(4);
	MRmsEl->SetMarkerStyle(21);
	MRmsEl->SetMarkerSize(1);
	MRmsEl->SetMarkerColor(4);	  

	EvalBins(MRmsEl,"m_tt");
     }//end of TT mT
     
     if (var=="absrap"||var=="all")
     {
       resmat_abs_tt=(TH2D*)in->Get("reco/4j2b/tt/Matrix_reco_particle_absrap_1");
       
 	TGraphErrors *absRmsEl=SliceFit(resmat_abs_tt,"tt","absrap");
	  
	TCanvas *ttabs=new TCanvas("ttabs","TTbar absolute value of rapidity 50 eq. binning");
	ttabs->cd(1);
	absRmsEl->Draw();
	absRmsEl->SetTitle("");
	absRmsEl->GetXaxis()->SetTitle("Absrapidity");
	absRmsEl->GetYaxis()->SetTitle("#sigma_{fit}");
	absRmsEl->GetYaxis()->SetTitleOffset(1.4);
	absRmsEl->SetLineColor(4);
	absRmsEl->SetMarkerStyle(21);
	absRmsEl->SetMarkerSize(1);
	absRmsEl->SetMarkerColor(4);	  
	
	EvalBins(absRmsEl,"absrap_tt");
     }//end of TT absrap

     if(var=="rap"||var=="all")
     {
       resmat_y_tt=(TH2D*)in->Get("reco/4j2b/tt/Matrix_reco_particle_rapidity_1");
       
 	TGraphErrors *YRmsEl=SliceFit(resmat_y_tt,"tt","rapidity");
	  
	TCanvas *tty=new TCanvas("tty","TTbar rapidity 50 eq. binning");
	tty->cd(1);
	YRmsEl->Draw();
	YRmsEl->SetTitle("");
	YRmsEl->GetXaxis()->SetTitle("Rapidity");
	YRmsEl->GetYaxis()->SetTitle("#sigma_{fit}");
	YRmsEl->GetYaxis()->SetTitleOffset(1.4);
	YRmsEl->SetLineColor(4);
	YRmsEl->SetMarkerStyle(21);
	YRmsEl->SetMarkerSize(1);
	YRmsEl->SetMarkerColor(4);	  
	  
	
	EvalBins(YRmsEl,"rap_tt");
     }//end of TT rapidity 
    
  }//end of TT
  
  if (type=="all"||type=="lep")
  {
    if (var=="all"||var=="pt")
    {
      resmat_pt_lep=(TH2D*)in->Get("reco/4j2b/topL/Matrix_reco_particle_pt_1");
        
	TGraphErrors *PtRmsEl=SliceFit(resmat_pt_lep,"lep","pt");
	  
	TCanvas *leppt=new TCanvas("leppt","Leptonic top transversal momentum 50 eq. binning");
	leppt->cd(1);
	PtRmsEl->Draw();
	PtRmsEl->SetTitle("");
	PtRmsEl->GetXaxis()->SetTitle("p_{T}^{lep} [GeV]");
	PtRmsEl->GetYaxis()->SetTitle("#sigma_{fit} [GeV]");
	PtRmsEl->GetYaxis()->SetTitleOffset(1.4);
	PtRmsEl->SetLineColor(4);
	PtRmsEl->SetMarkerStyle(21);
	PtRmsEl->SetMarkerSize(1);
	PtRmsEl->SetMarkerColor(4);	  
	  
	EvalBins(PtRmsEl,"pt_lep");
    }//end of lep pt
    if (var=="all"||var=="absrap")
    {
        resmat_abs_lep=(TH2D*)in->Get("reco/4j2b/topL/Matrix_reco_particle_absrap_1");

  	TGraphErrors *absRmsEl=SliceFit(resmat_abs_lep,"lep","absrap");
	  
	TCanvas *lepabs=new TCanvas("lepabs","Leptonic top absolute value of rapidity 50 eq. binning");
	lepabs->cd(1);
	absRmsEl->Draw();
	absRmsEl->SetTitle("");
	absRmsEl->GetXaxis()->SetTitle("Absrapidity");
	absRmsEl->GetYaxis()->SetTitle("#sigma_{fit}");
	absRmsEl->GetYaxis()->SetTitleOffset(1.4);
	absRmsEl->SetLineColor(4);
	absRmsEl->SetMarkerStyle(21);
	absRmsEl->SetMarkerSize(1);
	absRmsEl->SetMarkerColor(4);	  
	  
	EvalBins(absRmsEl,"absrap_lep");
    }//end of pseudorapidity
    
     if(var=="rap"||var=="all")
     {
       resmat_y_lep=(TH2D*)in->Get("reco/4j2b/topL/Matrix_reco_particle_rapidity_1");
       
 	TGraphErrors *YRmsEl=SliceFit(resmat_y_lep,"lep","rapidity");
	  
	TCanvas *lepy=new TCanvas("lepy","TTbar rapidity 50 eq. binning");
	lepy->cd(1);
	YRmsEl->Draw();
	YRmsEl->SetTitle("");
	YRmsEl->GetXaxis()->SetTitle("Rapidity");
	YRmsEl->GetYaxis()->SetTitle("#sigma_{fit}");
	YRmsEl->GetYaxis()->SetTitleOffset(1.4);
	YRmsEl->SetLineColor(4);
	YRmsEl->SetMarkerStyle(21);
	YRmsEl->SetMarkerSize(1);
	YRmsEl->SetMarkerColor(4);	  

	EvalBins(YRmsEl,"rap_lep");
     }//end of leptonic top rapidity 
  }//end of lep
  
  if (type=="all"||type=="had")
  {
      if (var=="all"||var=="pt")
      {
	resmat_pt_had=(TH2D*)in->Get("reco/4j2b/topH/Matrix_reco_particle_pt_1");
	
       	TGraphErrors *PtRmsEl=SliceFit(resmat_pt_had,"had","pt");
	  
	TCanvas *hadpt=new TCanvas("hadpt","Hadronic top transversal momentum  50 eq. binning");
	hadpt->cd(1);
	PtRmsEl->Draw();
	PtRmsEl->SetTitle("");
	PtRmsEl->GetXaxis()->SetTitle("pT [GeV]");
	PtRmsEl->GetYaxis()->SetTitle("#sigma_{fit} [GeV]");
	PtRmsEl->GetYaxis()->SetTitleOffset(1.4);
	PtRmsEl->SetLineColor(4);
	PtRmsEl->SetMarkerStyle(21);
	PtRmsEl->SetMarkerSize(1);
	PtRmsEl->SetMarkerColor(4);	  
	  
	EvalBins(PtRmsEl,"pt_had");
      }//end of had pt
      if (var=="all"||var=="absrap")
      {
	resmat_abs_had=(TH2D*)in->Get("reco/4j2b/topH/Matrix_reco_particle_absrap_1");
	
 	TGraphErrors *absRmsEl=SliceFit(resmat_abs_had,"had","absrap");
	  
	TCanvas *hadabs=new TCanvas("hadabs","Hadronic top absolute value of rapidity l 50 eq. binning");
	hadabs->cd(1);
	absRmsEl->Draw();
	absRmsEl->SetTitle("");
	absRmsEl->GetXaxis()->SetTitle("Absrapidity");
	absRmsEl->GetYaxis()->SetTitle("#sigma_{fit}");
	absRmsEl->GetYaxis()->SetTitleOffset(1.4);
	absRmsEl->SetLineColor(4);
	absRmsEl->SetMarkerStyle(21);
	absRmsEl->SetMarkerSize(1);
	absRmsEl->SetMarkerColor(4);	  

	EvalBins(absRmsEl,"absrap_had");
      }//end of had pseudorapidity
      
     if(var=="rap"||var=="all")
     {
        resmat_y_had=(TH2D*)in->Get("reco/4j2b/topH/Matrix_reco_particle_rapidity_1");
       
 	TGraphErrors *YRmsEl=SliceFit(resmat_y_had,"had","rapidity");
	  
	TCanvas *hady=new TCanvas("hady","Hadronic top rapidity 50 eq. binning");
	hady->cd(1);
	YRmsEl->Draw();
	YRmsEl->SetTitle("");
	YRmsEl->GetXaxis()->SetTitle("Rapidity");
	YRmsEl->GetYaxis()->SetTitle("#sigma_{fit}");
	YRmsEl->GetYaxis()->SetTitleOffset(1.4);
	YRmsEl->SetLineColor(4);
	YRmsEl->SetMarkerStyle(21);
	YRmsEl->SetMarkerSize(1);
	YRmsEl->SetMarkerColor(4);	  

	EvalBins(YRmsEl,"rap_had");
     }//end of had rapidity 
    
  }//end of had
}//end of script