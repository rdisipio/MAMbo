{
//=========Macro generated from canvas: Cartoon_trapezoid/Cartoon_trapezoid
//=========  (Mon Aug  3 14:04:02 2015) by ROOT version5.34/14
   TCanvas *Cartoon_trapezoid = new TCanvas("Cartoon_trapezoid", "Cartoon_trapezoid",836,237,700,560);
   Cartoon_trapezoid->Range(0,0,1,1);
   Cartoon_trapezoid->SetFillColor(0);
   Cartoon_trapezoid->SetBorderMode(0);
   Cartoon_trapezoid->SetBorderSize(2);
   Cartoon_trapezoid->SetFrameBorderMode(0);
   TArrow *arrow = new TArrow(0.1537356,0.1666667,0.8146552,0.1666667,0.025,">");
   arrow->SetFillColor(1);
   arrow->SetFillStyle(1001);
   arrow->SetAngle(30);
   arrow->Draw();
   arrow = new TArrow(0.1522989,0.1666667,0.1522989,0.9008439,0.025,">");
   arrow->SetFillColor(1);
   arrow->SetFillStyle(1001);
   arrow->SetAngle(30);
   arrow->Draw();
   TMarker *marker = new TMarker(0.2327586,0.5548523,20);
   marker->SetMarkerStyle(20);
   marker->Draw();
   marker = new TMarker(0.3117816,0.5907173,20);
   marker->SetMarkerStyle(20);
   marker->Draw();
   marker = new TMarker(0.3793103,0.6603376,20);
   marker->SetMarkerStyle(20);
   marker->Draw();
   marker = new TMarker(0.4798851,0.6118143,20);
   marker->SetMarkerStyle(20);
   marker->Draw();
   marker = new TMarker(0.5545977,0.5189873,20);
   marker->SetMarkerStyle(20);
   marker->Draw();
   marker = new TMarker(0.6465517,0.4113924,20);
   marker->SetMarkerStyle(20);
   marker->Draw();
   TLine *line = new TLine(0.2341954,0.5535714,0.308908,0.5873016);
   line->Draw();
   line = new TLine(0.3103448,0.5892857,0.3807471,0.6626984);
   line->Draw();
   line = new TLine(0.3778736,0.656746,0.4798851,0.6130952);
   line->Draw();
   line = new TLine(0.4798851,0.6130952,0.5517241,0.5198413);
   line->Draw();
   line = new TLine(0.5560345,0.5218254,0.6436782,0.4146825);
   line->Draw();
   line = new TLine(0.2327586,0.5515873,0.2327586,0.1646825);
   line->Draw();
   line = new TLine(0.3132184,0.5892857,0.3132184,0.1626984);
   line->Draw();
   line = new TLine(0.6465517,0.406746,0.6465517,0.1646825);
   line->Draw();
   line = new TLine(0.5545977,0.5178571,0.5545977,0.1646825);
   line->Draw();
   line = new TLine(0.4813218,0.609127,0.4813218,0.1666667);
   line->Draw();
   line = new TLine(0.3793103,0.656746,0.3793103,0.1646825);
   line->Draw();
   Cartoon_trapezoid->Modified();
   Cartoon_trapezoid->cd();
   Cartoon_trapezoid->SetSelected(Cartoon_trapezoid);
   Cartoon_trapezoid->ToggleToolBar();
}
