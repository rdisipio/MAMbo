#include "MoMA.h"

MoMATool::MoMATool() :
  m_qcd_mm(NULL)
{
  const char * dataDir = "";
  m_qcd_mm = new QCDMMScale( NOMINAL, dataDir );
}

MoMATool::~MoMATool()
{
  delete m_qcd_mm;
}


///////////////////////////////////////////


MoMATool * MoMATool::GetHandle()
{
   static MoMATool instance;

   return &instance;
}
