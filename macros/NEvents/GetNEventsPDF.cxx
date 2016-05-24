#include "PDFsumWeights.h"
#include "../../src/HelperFunctions.h"

using namespace std;

int main( int nargs, char ** args)
{ 

   const string mcfilename        = args[1];
   const string PDFname = args[2];
   int variationNumber;
   sscanf( args[3], "%i", &variationNumber)  ; 
   cout << "INFO: sumWeights tree read from " << mcfilename << endl;
   TChain * m_sumWeights   = HelperFunctions::LoadChain( mcfilename.c_str(), "PDFsumWeights" );
   cout << "INFO: sumWeights tree has " << m_sumWeights->GetEntries() << " entries" << endl;
   PDFsumWeights * m_ntuple_PDFsumWeights = new PDFsumWeights( PDFname, m_sumWeights ); 
   int dsid;
   float nEvents;
   m_ntuple_PDFsumWeights->Loop( dsid, nEvents, variationNumber );
   cout << dsid << " " << std::fixed << std::setprecision(7) << nEvents << endl;
   
   
   
   
 }
