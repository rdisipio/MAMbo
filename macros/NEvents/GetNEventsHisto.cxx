 #include "sumWeights.h"
 #include "../../src/HelperFunctions.h"



using namespace std;

int main( int nargs, char ** args)
{ 

   const string mcfilename        = args[1]; 
   //Open filebuf
   ifstream filelist( mcfilename.c_str());
   int dsid = -1;
   double nEvents = 0;
   while(1)
   {
        //read line
        string infile;
        filelist >> infile;
        
        if( filelist.eof() ) break;
        cout << "INFO: Opening " << infile << endl;
        //Open root file
        TFile * f_in = TFile::Open( infile.c_str() );        
        //get dsid
        if( dsid < 0 )
        {
                TTree * tree = (TTree *)f_in->Get( "sumWeights");
                sumWeights * m_ntuple_sumWeights = new sumWeights( tree );
                float temp;
                m_ntuple_sumWeights->Loop( dsid, temp );
            //    delete m_ntuple_sumWeights;
        }
        TH1D * h_cutflow = (TH1D*) f_in->Get( "passed_resolved_ejets_2j0b/cutflow_mc_pu_zvtx");
        nEvents += h_cutflow->GetBinContent(1);
        delete f_in;
   }

   cout << dsid << " " << std::fixed << std::setprecision(7) << nEvents << endl;
   
   
   
   
 }

 
 410000 19225397.0168204
