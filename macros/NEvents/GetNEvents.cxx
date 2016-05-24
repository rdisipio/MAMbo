#include "sumWeights.h"
#include "../../src/HelperFunctions.h"

using namespace std;

int main( int nargs, char ** args)
{ 

   const string mcfilename        = args[1]; 
   cout << "INFO: sumWeights tree read from " << mcfilename << endl;
   TChain * m_sumWeights   = HelperFunctions::LoadChain( mcfilename.c_str(), "sumWeights" );
   cout << "INFO: sumWeights tree has " << m_sumWeights->GetEntries() << " entries" << endl;
   sumWeights * m_ntuple_sumWeights = new sumWeights( m_sumWeights );
   int dsid;
   float nEvents;
   m_ntuple_sumWeights->Loop( dsid, nEvents );
   cout << dsid << " " << std::fixed << std::setprecision(7) << nEvents << endl;
   
   
   
   
 }
