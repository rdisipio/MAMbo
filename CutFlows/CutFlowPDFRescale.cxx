#include "CutFlowPDFRescale.h"

CutFlowPDFRescale::CutFlowPDFRescale() 
{
   m_scalerpdf = new ScalerPDF;
}

CutFlowPDFRescale::~CutFlowPDFRescale()
{
}


/////////////////////////////////////////


bool CutFlowPDFRescale::Initialize()
{
   bool success = true;

   AddChannel("LPLUSJETS");

   AddCounterName("LPLUSJETS", "reco_unweight", 1 );
   SetCutName("LPLUSJETS", "reco_unweight", 0, "All Events");

   m_scalerpdf->initWrite( *m_hm->GetOutputFile() );

   return success;
}


/////////////////////////////////////////


bool CutFlowPDFRescale::Apply( EventData * ed )
{
  bool success = true;

  CutFlow::Start();

  /*
  struct PDFParams { 
     int      id1;
     int      id2;
     double  pdf1;
     double  pdf2;
     double    x1;
     double    x2;
     double scale;
  };
  */
  ScalerPDF::PDFParams pdf;
  //pdf.id1 = ed->params['pdf_id1'];
  // etc
  m_scalerpdf->SetParams( pdf );
  m_scalerpdf->calculate();
  m_scalerpdf->tree()->Fill();

  return success;
}


/////////////////////////////////////////


bool CutFlowPDFRescale::Finalize()
{
   bool success = true;

   m_scalerpdf->tree()->Write();

   return success;
}

/////////////////////////////////////////
// Plugin

extern "C" {
  CutFlowPluginFactory_PDFRescale * MakeCutFlowPlugin() {
    return new CutFlowPluginFactory_PDFRescale( "PDFRescale" );
  };
}

