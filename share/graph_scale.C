/*
  just scales the TGraph by some value.
  would be nice if root had this as a method fot TGraph like TH1.
 */
void
ScaleGraph(TGraphAsymmErrors* graph,double scale)
{
  //if(DEBUG)printf("SCALE=%.2e\n (1/SCALE=%.2e)\n",scale,1./scale);
  double* xValues = graph->GetX();
  double* yValues = graph->GetY();
  double* errXLow = graph->GetEXlow();
  double* errXHigh = graph->GetEXhigh();
  
  double* errYLow  = graph->GetEYlow();
  double* errYHigh = graph->GetEYhigh();

  for(int i=0; i<graph->GetN(); i++){
    double y=yValues[i], eYLow=errYLow[i], eYHigh=errYHigh[i];
    double yScaled=yValues[i]*scale;
    double eYLowScaled = errYLow[i]*scale;
    double eYHighScaled =errYHigh[i]*scale;

    graph->SetPoint(i,xValues[i],yScaled);
    graph->SetPointError(i,errXLow[i],errXHigh[i],
			 eYLowScaled,eYHighScaled);

   /* 
   if(DEBUG)
      printf("\tbin=%d : %.2f<%.2f<%.2f: y=%.2e, yScaled=%.2e\n\t\t yErrLow=%.2e, yErrLowScaled=%.2e\n",
	     i,xValues[i]-errXLow[i],xValues[i],xValues[i]+errXHigh[i],
	     y,yScaled,eYLow,eYLowScaled);
   */	     
  }
}
