#include "ScalerWjets.h"
#include "Commons.h"
#include "EventData.h"

using namespace PhysicsHelperFunctions;



ScalerWjets * ScalerWjets::m_instance = NULL;
ScalerWjets::ScalerWjets( int channel, string syst )
{
        m_channel = channel;
        m_systematic = syst;
        cout << "DEBUG: initializing wjets weights interface for channel " << (channel == 0 ? "el" : "mu") << " and systematic " << syst << "\n";
        m_CA_systematic = "nominal";
        m_Kbb_systematic = "nominal";
        m_Kc_systematic = "nominal";
        m_Klight_systematic = "nominal";
        
        if( m_systematic != "nominal")
        {
                vector< string > tokens;
                int nTokens =   HelperFunctions::Tokenize( m_systematic, tokens, "_" );
                if( nTokens != 2 )
                {
                        char message[100];
                        sprintf( message, "ScalerWjets: Badly formed systematic string: %s\n", m_systematic.c_str());
                        throw runtime_error( message );
                }
                if( tokens[0] == "CA" )
                {
                        m_CA_systematic = tokens[1];
                }
                else if( tokens[0] == "Kbb" )
                {
                        m_Kbb_systematic = tokens[1];
                } 
                else if( tokens[0] == "Kc" )
                {
                        m_Kc_systematic = tokens[1];
                } 
                else if( tokens[0] == "Klight" )
                {
                        m_Klight_systematic = tokens[1];
                } 
                else
                {
                        char message[100];
                        sprintf( message, "ScalerWjets: Unknown heavy flavor definition: %s\n", tokens[0].c_str());
                        throw runtime_error( message );
                        
                }
        }

        string basePath = string( getenv( "MAMBODIR" ) ) + "/share/data/WjetsScaleFactors";
        m_weightsFilename = basePath + "/Wjets_CA_" +  ( channel == 0 ? "el.root" : "mu.root" ); 
        cout << "DEBUG: getting weight histogram from " << m_weightsFilename << endl;
        m_weightsFile = TFile::Open( m_weightsFilename.c_str() );
        m_CA_weights = (TH2D*) m_weightsFile->Get( ( "CA/" + m_CA_systematic ).c_str() );
        m_Kbb_weights = (TH2D*) m_weightsFile->Get( ( "Kbb/" + m_Kbb_systematic ).c_str() );
        m_Kc_weights = (TH2D*) m_weightsFile->Get( ( "Kc/" + m_Kc_systematic ).c_str() );
        m_Klight_weights = (TH2D*) m_weightsFile->Get( ( "Klight/" + m_Klight_systematic ).c_str() );
        cout << "Tool inizialized.\n CA Weights are:\n";
        cout << "\t";
        for( int i = 0; i < 5; ++i )
        {
                cout << i << "j\t";
        }
        cout << endl;
        for( int j = 0; j < 2; ++j )
        {
                cout << j << "bj\t";
                for( int i = 0; i < 5; ++i )
                {
                        cout << m_CA_weights->GetBinContent( i+1, j+1 ) << "\t";
                }
                cout << endl;
        }
        cout << "\n Kbb Weights are:\n";
        cout << "\t";
        for( int i = 0; i < 5; ++i )
        {
                cout << i << "j\t";
        }
        cout << endl;
        for( int j = 0; j < 2; ++j )
        {
                cout << j << "bj\t";
                for( int i = 0; i < 5; ++i )
                {
                        cout << m_Kbb_weights->GetBinContent( i+1, j+1 ) << "\t";
                }
                cout << endl;
        }
        cout << "\n Kc Weights are:\n";
        cout << "\t";
        for( int i = 0; i < 5; ++i )
        {
                cout << i << "j\t";
        }
        cout << endl;
        for( int j = 0; j < 2; ++j )
        {
                cout << j << "bj\t";
                for( int i = 0; i < 5; ++i )
                {
                        cout << m_Kc_weights->GetBinContent( i+1, j+1 ) << "\t";
                }
                cout << endl;
        }
        cout << "\n Klight Weights are:\n";
        cout << "\t";
        for( int i = 0; i < 5; ++i )
        {
                cout << i << "j\t";
        }
        cout << endl;
        for( int j = 0; j < 2; ++j )
        {
                cout << j << "bj\t";
                for( int i = 0; i < 5; ++i )
                {
                        cout << m_Klight_weights->GetBinContent( i+1, j+1 ) << "\t";
                }
                cout << endl;
        }
        
        
        cout << "ScalerWjets: adding runs to light run list\n";
        
        m_lightList.push_back(361300);
        m_lightList.push_back(361303);
        m_lightList.push_back(361306);
        m_lightList.push_back(361309);
        m_lightList.push_back(361312);
        m_lightList.push_back(361315);
        m_lightList.push_back(361318);
        m_lightList.push_back(361321);
        m_lightList.push_back(361324);
        m_lightList.push_back(361327);
        m_lightList.push_back(361330);
        m_lightList.push_back(361333);
        m_lightList.push_back(361336);
        m_lightList.push_back(361339);
        m_lightList.push_back(361342);
        m_lightList.push_back(361345);
        m_lightList.push_back(361348);
        m_lightList.push_back(361351);
        m_lightList.push_back(361354);
        m_lightList.push_back(361357);
        m_lightList.push_back(361360);
        m_lightList.push_back(361363);
        m_lightList.push_back(361366);
        m_lightList.push_back(361369);
        cout << "Added " << m_lightList.size() << " runs\n";
        
        
        cout << "ScalerWjets: adding runs to b run list\n";

        m_bList.push_back(361302);
        m_bList.push_back(361305);
        m_bList.push_back(361308);
        m_bList.push_back(361311);
        m_bList.push_back(361314);
        m_bList.push_back(361317);
        m_bList.push_back(361320);
        m_bList.push_back(361323);
        m_bList.push_back(361326);
        m_bList.push_back(361329);
        m_bList.push_back(361332);
        m_bList.push_back(361335);
        m_bList.push_back(361338);
        m_bList.push_back(361341);
        m_bList.push_back(361344);
        m_bList.push_back(361347);
        m_bList.push_back(361350);
        m_bList.push_back(361353);
        m_bList.push_back(361356);
        m_bList.push_back(361359);
        m_bList.push_back(361362);
        m_bList.push_back(361365);
        m_bList.push_back(361368);
        m_bList.push_back(361371);        
        cout << "Added " << m_bList.size() << " runs\n";
        
        
}


ScalerWjets::~ScalerWjets( )
{
        m_weightsFile->Close();
        delete m_weightsFile;
        //delete m_tightEff;
}

ScalerWjets * ScalerWjets::GetHandle( int channel, string syst )
{
        if( m_instance == NULL ) m_instance = new ScalerWjets( channel, syst );
        else
        {
                if( channel != m_instance->GetChannel()  || syst != m_instance->GetSystematic() ) 
                {
                        char msg[100];
                        sprintf( msg,"ScalerWjets requested  with channel == %i and syst == %s \
but an instance already exists with channel == %i and syst == %si\n", channel, syst.c_str(),  m_instance->GetChannel(),  m_instance->GetSystematic().c_str() );
                        throw std::runtime_error( msg );
                }
        }
        return m_instance;
}
/*
double ScalerWjets::GetWjetsWeight( int njets, int nbjets){

        int x = njets <= 4 ? njets+1 : 5;
        int y = nbjets <= 1 ? nbjets+1 : 2;
        return m_weights->GetBinContent( x, y );

}
*/
double ScalerWjets::GetWjetsWeight( EventData * ed){

        int njets = ed->jets.n;
        int nbjets = ed->bjets.n;
        double is_WplusC = ed->property[ "is_WplusC"];
        double is_WplusCC = ed->property[ "is_WplusCC"];
        bool isB     = std::find(m_bList.begin(), m_bList.end(),  ed->info.mcChannelNumber) != m_bList.end();
        bool isLight = std::find(m_lightList.begin(), m_lightList.end(),  ed->info.mcChannelNumber) != m_lightList.end();
        //check coherence of the flags
        if( ( is_WplusC && is_WplusCC ) || (isLight && (is_WplusC || is_WplusCC || isB )  ) )
        {
                char msg[100];
                sprintf( msg, "ScalerWjets::GetWjetsWeight - ERROR: wrong HF flags for event %i, run number %i.\n is_WplusC = %i, is_WplusCC = %i, is_WplusB = %i, isLight = %i. Only one of these flags can be true.\n",
                ed->info.eventNumber, ed->info.mcChannelNumber, is_WplusC, is_WplusCC, isB, isLight );
                throw runtime_error( msg );
        }
        int x = njets <= 4 ? njets+1 : 5;
        int y = nbjets <= 1 ? nbjets+1 : 2;
        double CA_weight = m_CA_weights->GetBinContent( x, y );
        double HF_weight = 1;
        if( is_WplusC ) HF_weight = m_Kc_weights->GetBinContent( x, y );
        else if( is_WplusCC || isB ) HF_weight = m_Kbb_weights->GetBinContent( x, y );
        else if( isLight ) HF_weight = m_Klight_weights->GetBinContent( x, y );
        return CA_weight * HF_weight;
}

