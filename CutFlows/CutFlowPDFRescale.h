#ifndef __CF_PDFRescale_H__
#define __CF_PDFRescale_H__

#include "ICutFlow.h"

#include "ScalerPDF.h"

class CutFlowPDFRescale : public CutFlow
{
 public:
  CutFlowPDFRescale();
  virtual ~CutFlowPDFRescale();

  virtual bool Initialize();
  virtual bool Apply( EventData * ed );
  virtual bool Finalize();

 protected:
   ScalerPDF * m_scalerpdf;
};

typedef CutFlowPluginFactory< CutFlowPDFRescale > CutFlowPluginFactory_PDFRescale;

extern "C" {
  CutFlowPluginFactory_PDFRescale * MakeCutFlowPlugin();
}

#endif /** __CF_PDFRescale_H__ */
