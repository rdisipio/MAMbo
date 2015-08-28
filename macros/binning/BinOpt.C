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
	      Slices[i]->Fit("g1","q");
	      TF1 *f1=Slices[i]->GetFunction("g1");
	      xl=(f1->GetParameter(1))-2*(f1->GetParameter(2));
	      xm=(f1->GetParameter(1))+2*(f1->GetParameter(2));
	      TF1 *g2=new TF1("g2","gaus",xl,xm);
	      Slices[i]->Fit("g2","q");
	      f1=Slices[i]->GetFunction("g2");
	      if (f1->GetParameter(2)==0)continue;
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
  TString ftitle[3],ptitle[3];
  
  if(Name=="rap_had")x_start=-2.4;
  if(Name.Contains("m_"))x_start=225;
  if(Name.Contains("R_lb"))x_start=0.1;
  if(Name.Contains("chi_ttbar")){x_start=1;x_end=4;}
  //if(Name.Contains("dPhi"))x_start=0.5;
  
  ftitle[0]="Binning_"+Name+"_pol.txt";
  ftitle[1]="Binning_"+Name+"_exp.txt";
  ftitle[2]="Binning_"+Name+"_lin.txt";
  ptitle[0]="Binning_"+Name+"_pol.png";
  ptitle[1]="Binning_"+Name+"_exp.png";
  ptitle[2]="Binning_"+Name+"_lin.png";
  
  double_t dif=0,ndf[3],chi[3],chindf[3],p0,p1,p2=0,p3=0,p4=0,p5=0,p6=0,p7=0,p8=0;
 
  TF1 *ResFnc[3],*fbin[3],*forz,*zbin,*foryboost,*ybin,*forpout,*poutbin,*fordphi,*dphibin,*forchi,*chibin;
  ResFnc[0]=new TF1("res","[0]+[1]*x+[2]*x*x",x_start,x_end); 
  ResFnc[1]=new TF1("res1","[0]+[1]*exp([2]+[3]*x)",x_start,x_end); 
  ResFnc[2]=new TF1("res2","[0]+[1]*x",x_start,x_end);
  forz = new TF1("forz","(x<1)*([0]+[1]*x+[2]*x*x)+(x>1)*([3]+[4]*x+[5]*x*x)",x_start,x_end);
  foryboost = new TF1("foryboost","(x<0.2)*([0]+[1]*x+[2]*x*x)+(x>0.2)*(x<1.4)*([3]+[4]*x+[5]*x*x)+(x>1.4)*([6]+[7]*x+[8]*x*x)",x_start,x_end);
  forpout = new TF1 ("forpout","(x<0)*([0]+[1]*x+[2]*x*x)+(x>0)*([4]+[5]*x+[6]*x*x)",x_start,x_end);
  fordphi = new TF1("fordphi","(x>0.37)*(x<3)*([0]+[1]*x+[2]*x*x)+(x<0.37)*([4]+[5]*x+[6]*x*x)+(x>3)*([7]+[8]*x+[9]*x*x)",x_start,x_end);
  forchi = new TF1("forchi","(x<1)*(0)+(x>1)*([0]+[1]*x)*(x<1.1)+(x>1.1)*([2]+[3]*exp([4]+[5]*x))",x_start,x_end);
  //for delta!=1
  //fbin[0]=new TF1("fbin","[0]*[1]+[0]*[2]*x+[0]*[3]*x*x-x+[4]",x_start,x_end);
  //fbin[1]=new TF1("fbin1","[0]*[1]+[0]*[2]*exp([3]+[4]*x)-x+[5]",x_start,x_end);
  //fbin[2]=new TF1("fbin2","[0]*[1]+[0]*[2]*x-x+[3]",x_start,x_end);
  //zbin = new TF1 ("zbin","((x<1)*([0]*[1]+[0]*[2]*x)+(x>1)*([0]*[3]+[0]*[4]*x+[0]*[5]*x*x))-x+[6]",x_start,x_end);
  dphibin=new TF1("dphibin","(x>0.4)*(x<2.9)*([0]+[1]*x+[2]*x*x)+(x<0.4)*([3]+[4]*x+[5]*x*x)+(x>2.9)*([6]+[7]*x+[8]*x*x)-x+[9]",x_start,x_end);
  fbin[0]=new TF1("fbin","[0]+[1]*x+[2]*x*x-x+[3]",x_start,x_end);
  fbin[1]=new TF1("fbin1","[0]+[1]*exp([2]+[3]*x)-x+[4]",x_start,x_end);
  fbin[2]=new TF1("fbin2","[0]+[1]*x-x+[2]",x_start,x_end);
  zbin = new TF1 ("zbin","((x<1)*([0]+[1]*x+[2]*x*x)+(x>1)*([3]+[4]*x+[5]*x*x))-x+[6]",x_start,x_end);
  ybin = new TF1 ("ybin","(x<0.2)*([0]+[1]*x+[2]*x*x)+(x>0.2)*(x<1.4)*([3]+[4]*x+[5]*x*x)+(x>1.4)*([6]+[7]*x+[8]*x*x)-x+[9]",x_start,x_end);
  poutbin = new TF1 ("poutbin","(x<0)*([0]+[1]*x+[2]*x*x)+(x>0)*([3]+[4]*x+[5]*x*x)-x+[6]",x_start,x_end);
  chibin = new TF1("chibin","([0]+[1]*x)*(x<1.1)+(x>1.1)*([2]+[3]*x+[4]*x*x)-x+[5]",x_start,x_end);
  
  
  ResFnc[0]->SetParameters(30.,0.01,0.001); //polfit
  ResFnc[1]->SetParameters(30.,0.01,0.001,0.001); //expfit
  ResFnc[2]->SetParameters(10.,2.);
  forz->SetParameters(1,1,1,1,1,1);
  foryboost->SetParameters(1,1,1,1,1,1,1,1,1);
  forpout->SetParameters(1,1,1,1,1,1);
  fordphi->SetParameters(1,1,1,1,1,1,1,1,1);
  forchi->SetParameters(1,1,1,1,1,-1);
  //ResFnc->SetParLimits(2,0.,1000);


  //Int_t col=RMS->GetLineColor();
  
  for (Int_t i = 0; i < 3 ;i++)
  {
    ofstream out;
    out.open(ftitle[i]);
    if (Name.Contains("z_tt"))RMS->Fit(forz,"q");
    if (Name.Contains("R_"))RMS->Fit(forz,"q");
    if (Name.Contains("yboost"))RMS->Fit(foryboost,"q"); 
    if (Name.Contains("Pout"))RMS->Fit(forpout,"q");
    if (Name.Contains("dPhi"))RMS->Fit(fordphi,"q");
    if (Name.Contains("chi"))RMS->Fit(forchi,"q");
    if (!(Name.Contains("z_tt") || Name.Contains("yboost") || Name.Contains("Pout")||Name.Contains("dPhi")||Name.Contains("R_")||Name.Contains("chi"))) RMS->Fit(ResFnc[i],"q");

    if (Name.Contains("z_tt")){ndf[i]=forz->GetNDF();chi[i]=forz->GetChisquare();}
    if (Name.Contains("R_")){ndf[i]=forz->GetNDF();chi[i]=forz->GetChisquare();}
    if (Name.Contains("yboost")){ndf[i]=foryboost->GetNDF();chi[i]=foryboost->GetChisquare();}
    if (Name.Contains("Pout")){ndf[i]=forpout->GetNDF();chi[i]=forpout->GetChisquare();}
    if (Name.Contains("dPhi")){ndf[i]=fordphi->GetNDF();chi[i]=fordphi->GetChisquare();}
    if (Name.Contains("chi")){ndf[i]=forchi->GetNDF();chi[i]=forchi->GetChisquare();}
    if (!(Name.Contains("z_tt") || Name.Contains("yboost")|| Name.Contains("Pout")||Name.Contains("dPhi")||Name.Contains("R_")||Name.Contains("chi")))
    {
      ndf[i]=ResFnc[i]->GetNDF();
      chi[i]=ResFnc[i]->GetChisquare();
    }
    
    if (!(ndf==0)) chindf[i]=chi[i]/ndf[i];
  
    //ResFnc[i]->SetLineColor(col);
    //foryboost->SetLineColor(col);
    //forz->SetLineColor(col);
    //forpout->SetLineColor(col);
    
    TCanvas *c1= new TCanvas("fit","fit");
    c1->Clear();
  //c1->cd(1);
    RMS->Draw();
    if(!(Name.Contains("z_tt") || Name.Contains("yboost")|| Name.Contains("Pout")||Name.Contains("dPhi")||Name.Contains("R_")||Name.Contains("chi")))ResFnc[i]->Draw("same");
    
    if(Name.Contains("Pout")){RMS->GetHistogram()->SetMaximum(150);RMS->GetHistogram()->SetMinimum(0.);}
    if(Name.Contains("chi")){RMS->GetHistogram()->SetMaximum(3);RMS->GetHistogram()->SetMinimum(0.);}
    if(Name.Contains("yboost")){RMS->GetHistogram()->SetMaximum(0.2);RMS->GetHistogram()->SetMinimum(0.);}
    if(Name.Contains("R_") || Name.Contains("z_tt")){RMS->GetHistogram()->SetMaximum(1);RMS->GetHistogram()->SetMinimum(0.);}
    if(Name.Contains("rap"))
    {
     RMS->GetHistogram()->SetMaximum(0.1);
     RMS->GetHistogram()->SetMinimum(0.);	
     if (Name.Contains("lep"))RMS->GetHistogram()->SetMaximum(0.5);
    }
    char buf[128];
    sprintf( buf, "#Chi^{2}/NDF: %3.2f", chindf[i]);
    TLatex l;
    l.SetTextSize(0.04); 
    l.SetNDC();
    l.SetTextColor(kBlack);
    l.DrawLatex(0.1,0.92,buf);
  

    c1->Print(ptitle[i]);
  
    c1->Close();
  
    out<<title<<" :chisquare/ndf "<<chindf[i]<< "  Calculating " << ftitle[i]<<endl;

  //if(Name.Contains("dPhi"))x_start=.8;
    p0=ResFnc[i]->GetParameter(0);
    p1=ResFnc[i]->GetParameter(1);
    if (i<2)p2=ResFnc[i]->GetParameter(2);
    if (i==1)p3=ResFnc[i]->GetParameter(3); //expfit only
   // if (Name.Contains("z_tt"))p4=forz->GetParameter(4);
    if (Name.Contains("yboost")){p0=foryboost->GetParameter(0);p1=foryboost->GetParameter(1);p2=foryboost->GetParameter(2);p3=foryboost->GetParameter(3);p4=foryboost->GetParameter(4);p5=foryboost->GetParameter(5);p6=foryboost->GetParameter(6);p7=foryboost->GetParameter(7);p8=foryboost->GetParameter(8);}
    if (Name.Contains("dphi")){p0=fordphi->GetParameter(0);p1=fordphi->GetParameter(1);p2=fordphi->GetParameter(2);p3=fordphi->GetParameter(3);p4=fordphi->GetParameter(4);p5=fordphi->GetParameter(5);p6=fordphi->GetParameter(6);p7=fordphi->GetParameter(7);p8=fordphi->GetParameter(8);}
    if (Name.Contains("Pout")){p0=forpout->GetParameter(0);p1=forpout->GetParameter(1);p2=forpout->GetParameter(2);p3=forpout->GetParameter(3);p4=forpout->GetParameter(4);p5=forpout->GetParameter(5);}
    if (Name.Contains("z_tt")||Name.Contains("R_")){p0=forz->GetParameter(0);p1=forz->GetParameter(1);p2=forz->GetParameter(2);p3=forz->GetParameter(3);p4=forz->GetParameter(4);p5=forz->GetParameter(5);}
    if (Name.Contains("chi")){p0=forchi->GetParameter(0);p1=forchi->GetParameter(1);p2=forchi->GetParameter(2);}
  
    
   // double_t delta=1;
    double_t binEdge=x_start;
    double_t stor=x_start;
  
    while (binEdge<x_end)
    {
      if(i==0)fbin[0]->SetParameters(p0,p1,p2,binEdge);
      if(i==1)fbin[1]->SetParameters(p0,p1,p2,p3,binEdge);
      if(i==2)fbin[2]->SetParameters(p0,p1,binEdge);
      if(Name.Contains("z_tt")||Name.Contains("R_"))zbin->SetParameters(p0,p1,p2,p3,p4,p5,binEdge);
      if(Name.Contains("yboost"))ybin->SetParameters(p0,p1,p2,p3,p4,p5,p6,p7,p8,binEdge);
      if(Name.Contains("dPhi"))dphibin->SetParameters(p0,p1,p2,p3,p4,p5,p6,p7,p8,binEdge);
      if(Name.Contains("chi"))chibin->SetParameters(p0,p1,p2,binEdge);
      if(Name.Contains("Pout"))poutbin->SetParameters(p0,p1,p2,p3,p4,p5,binEdge);
      
      double_t prec=0.01;
      double_t step=x_end;

      while(step>x_start)
      {
	double_t val;
	if (Name.Contains("z_tt")||Name.Contains("R_"))val=zbin->Eval(step);
	if (Name.Contains("yboost")) val=ybin->Eval(step);
	if (Name.Contains("Pout"))val=poutbin->Eval(step);
	if (Name.Contains("dPhi"))val=dphibin->Eval(step);
	if (Name.Contains("chi"))val=chibin->Eval(step);
	if (!(Name.Contains("z_tt") || Name.Contains("yboost")|| Name.Contains("Pout")||Name.Contains("R_")||Name.Contains("chi")||Name.Contains("dPhi"))) val=fbin[i]->Eval(step);
	if (val>prec)break;
	step-=prec;
      }
      stor+=dif;
      binEdge=2*(step-binEdge)+binEdge;
      dif=binEdge-stor;
      if (dif<0){cout<<"Negative bin width error";break;}
      out<<"bin edge: "<<binEdge<<"; bin width: "<<dif<<endl;
    }
  out<<endl;
  out<<endl;
  out.close();
  }

}//end of EvalBins
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void BinOpt (TString type="all",TString var="all")
{
  TFile *in=new TFile("histograms_PowHeg_co_witdil_ljets.root", "read");
  
  if (!(type=="tt"||type=="lep"||type=="had"||type=="all"))
  {
    cout<<"Wrong type of quark"<<endl;
    return;
  }
  if (!(var=="R_lb"||var=="R_Wb_had"||var=="pt"||var=="all"||var=="m"||var=="rap"||var=="Pout"||var=="zttbar"||var=="dPhi"||var=="Ht"||var=="yboost"||var=="chittbar")) 
  {
    cout<<"Wrong variable"<<endl;
    return;
  }
  if((var=="m"||var=="Pout"||var=="zttbar"||var=="dPhi")&&(type=="lep"||type=="had"))
  {
    cout<<"Wrong parameter combination"<<endl;
  }
  
  TH2D *resmat_WL_y,*resmat_WL_pt,*resmat_WH_pt,*resmat_WH_y,*resmat_R_Wt_had,*resmat_R_Wt_lep,*resmat_R_lb,*resmat_R_Wb_had,*resmat_R_Wb_lep,*resmat_tt_Salam,*resmat_tt_yboost,*resmat_tt_chittbar,*resmat_pt_lep,*resmat_pt_had,*resmat_pt_tt,*resmat_m_tt,*resmat_y_tt,*resmat_y_lep,*resmat_y_had,*resmat_abs_tt,*resmat_Ht_tt,*resmat_Ht_pseudo,*resmat_abs_lep,*resmat_abs_had,*resmat_Pout,*resmat_zttbar,*resmat_dPhi;
cout<<"starting"<<endl;
      
      if (var=="R_lb"||var=="all")
      {
	resmat_R_lb=(TH2D*)in->Get("reco/4j2b/difference/Matrix_reco_particle_R_lb_1");
	
	TGraphErrors *R_lbRms=SliceFit(resmat_R_lb,"R","R_lb");
	
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
	
	TGraphErrors *R_WHbRms=SliceFit(resmat_R_Wb_had,"R","R_WHb");
	
      TCanvas *R_WHb=new TCanvas("R_WHb","Ratio of hadronic W pt and b-jet pt");
      R_WHb->cd(1);
      R_WHbRms->Draw();
      R_WHbRms->SetTitle("");
      R_WHbRms->GetXaxis()->SetTitle("R_Wb_had");
      R_WHbRms->GetYaxis()->SetTitle("#sigma_{fit}");
      R_WHbRms->GetYaxis()->SetTitleOffset(1.4);
      R_WHbRms->SetLineColor(4);
      R_WHbRms->SetMarkerStyle(21);
      R_WHbRms->SetMarkerSize(1);
      R_WHbRms->SetMarkerColor(4);
      
      EvalBins(R_WHbRms,"R_Wb_had");
      }//end of R_WHb      
      
      if (var=="R_Wt"||var=="all")
      {
	resmat_R_Wt_had=(TH2D*)in->Get("reco/4j2b/difference/Matrix_reco_particle_R_Wt_had_1");
	
	TGraphErrors *R_WHtRms=SliceFit(resmat_R_Wt_had,"R","R_WHt");
	
      TCanvas *R_WHt=new TCanvas("R_WHt","Ratio of hadronic W pt and hadronic top quark pt");
      R_WHt->cd(1);
      R_WHtRms->Draw();
      R_WHtRms->SetTitle("");
      R_WHtRms->GetXaxis()->SetTitle("R_Wt_had");
      R_WHtRms->GetYaxis()->SetTitle("#sigma_{fit}");
      R_WHtRms->GetYaxis()->SetTitleOffset(1.4);
      R_WHtRms->SetLineColor(4);
      R_WHtRms->SetMarkerStyle(21);
      R_WHtRms->SetMarkerSize(1);
      R_WHtRms->SetMarkerColor(4);
      
      EvalBins(R_WHtRms,"R_Wt_had");
      }//end of R_WHt     
  
  
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
      
      EvalBins(YboostRms,"yboost");
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
      resmat_Ht_pseudo=(TH2D*)in->Get("reco/4j2b/difference/Matrix_reco_particle_HT_ttbar_1"); 
 
      TGraphErrors *HtpsRms=SliceFit(resmat_Ht_pseudo,"tt","HT_ttbar");
   
      TCanvas *Htps=new TCanvas("Htps","Sum of transversal momentum of all pseudotop elements");
      Htps->cd(1);
      HtpsRms->Draw();
      HtpsRms->SetTitle("");
      HtpsRms->GetXaxis()->SetTitle("H_{T}^{t#bar{t}} [GeV]");
      HtpsRms->GetYaxis()->SetTitle("#sigma_{fit}[GeV]");
      HtpsRms->GetYaxis()->SetTitleOffset(1.4);
      HtpsRms->SetLineColor(4);
      HtpsRms->SetMarkerStyle(21);
      HtpsRms->SetMarkerSize(1);
      HtpsRms->SetMarkerColor(4);
      
      EvalBins(HtpsRms,"Ht_ttbar");
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