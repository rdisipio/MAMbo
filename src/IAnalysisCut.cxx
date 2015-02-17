#include "IAnalysisCut.h"

IAnalysisCut::IAnalysisCut( const string& name ) : m_cutName( name )
{

}


IAnalysisCut::~IAnalysisCut()
{
}


//////////////////////////////////////////


void IAnalysisCut::Configure( const AnalysisCutParams_t& params )
{
   m_params = params;
}
