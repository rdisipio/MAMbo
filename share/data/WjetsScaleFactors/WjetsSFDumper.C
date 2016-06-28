#include "WjetsSFDumper.h"
using namespace std;
void WjetsSFDumper::BuildArrays()
{
        
        CA_sf_el_pretag_nominal = {1,1,0.911 , 0.783,  0.907}; 
        CA_sf_el_tag_nominal = {1,1,1.167 , 1.003 , 1.162 }; 
        CA_sf_mu_pretag_nominal = {1,1,1.023, 0.931,0.917 } ;
        CA_sf_mu_tag_nominal = {1,1,1.283, 1.168, 1.150}; 
        
        CA_unc_stat_el_pretag = {1,1,0.045, 0.055, 0.088 };
        CA_unc_stat_el_tag = {1,1,0.058,  0.072  , 0.115 };
        CA_unc_stat_mu_pretag = {1,1,0.038, 0.054, 0.063 };
        CA_unc_stat_mu_tag = {1,1,0.048,  0.068  , 0.079 };
        
        CA_unc_syst_el_pretag = {1,1,0.253,	0.145,	0.229 };
        CA_unc_syst_el_tag = {1,1,0.186,	0.127,	0.222};
        CA_unc_syst_mu_pretag = {1,1,0.166,	0.157,	0.18};
         CA_unc_syst_mu_tag = {1,1,0.111,	0.112,	0.162 };
        // ///////////////////////////
        // Kbb_sf_el_pretag_nominal = {1,1,1.05 , 1.07,  1.08}; 
        // Kbb_sf_el_tag_nominal = {1,1,1.05 , 1.07,  1.08}; //USING pretag for tagged
        // Kbb_sf_mu_pretag_nominal = {1,1,0.37, 0.38,0.41 } ;
        // Kbb_sf_mu_tag_nominal = {1,1,0.37, 0.38,0.41}; 
        
        // Kbb_unc_stat_el_pretag = {1,1,0.045, 0.055, 0.088 };
        // Kbb_unc_stat_el_tag = {1,1,0.058,  0.072  , 0.115 };
        // Kbb_unc_stat_mu_pretag = {1,1,0.038, 0.054, 0.063 };
        // Kbb_unc_stat_mu_tag = {1,1,0.048,  0.068  , 0.079 };
        
        // Kbb_unc_syst_el_pretag = {1,1,0.253,	0.145,	0.229 };
        // Kbb_unc_syst_el_tag = {1,1,0.186,	0.127,	0.222};
        // Kbb_unc_syst_mu_pretag = {1,1,0.166,	0.157,	0.18};
        // Kbb_unc_syst_mu_tag = {1,1,0.111,	0.112,	0.162 };
        // ///////////////////////////
        // Kc_sf_el_pretag_nominal = {1,1,0.57 , 0.58,  0.59}; 
        // Kc_sf_el_tag_nominal = {1,1,0.57 , 0.58,  0.59 }; 
        // Kc_sf_mu_pretag_nominal = {1,1,1.12, 1.16, 1.22 } ;
        // Kc_sf_mu_tag_nominal = {1,1,1.12, 1.16, 1.22}; 
        
        // Kc_unc_stat_el_pretag = {1,1,0.045, 0.055, 0.088 };
        // Kc_unc_stat_el_tag = {1,1,0.058,  0.072  , 0.115 };
        // Kc_unc_stat_mu_pretag = {1,1,0.038, 0.054, 0.063 };
        // Kc_unc_stat_mu_tag = {1,1,0.048,  0.068  , 0.079 };
        
        // Kc_unc_syst_el_pretag = {1,1,0.253,	0.145,	0.229 };
        // Kc_unc_syst_el_tag = {1,1,0.186,	0.127,	0.222};
        // Kc_unc_syst_mu_pretag = {1,1,0.166,	0.157,	0.18};
        // Kc_unc_syst_mu_tag = {1,1,0.111,	0.112,	0.162 };
        // ///////////////////////////
        // Klight_sf_el_pretag_nominal = {1,1,1.13 , 1.15,  1.16}; 
        // Klight_sf_el_tag_nominal = {1,1,1.13 , 1.15,  1.16 }; 
        // Klight_sf_mu_pretag_nominal = {1,1,1.06, 1.09,1.16 } ;
        // Klight_sf_mu_tag_nominal = {1,1,1.06, 1.09,1.16}; 
        
        // Klight_unc_stat_el_pretag = {1,1,0.045, 0.055, 0.088 };
        // Klight_unc_stat_el_tag = {1,1,0.058,  0.072  , 0.115 };
        // Klight_unc_stat_mu_pretag = {1,1,0.038, 0.054, 0.063 };
        // Klight_unc_stat_mu_tag = {1,1,0.048,  0.068  , 0.079 };
        
        // Klight_unc_syst_el_pretag = {1,1,0.253,	0.145,	0.229 };
        // Klight_unc_syst_el_tag = {1,1,0.186,	0.127,	0.222};
        // Klight_unc_syst_mu_pretag = {1,1,0.166,	0.157,	0.18};
        // Klight_unc_syst_mu_tag = {1,1,0.111,	0.112,	0.162 };
        // ///////////////////////////
        ///////////////////////////
        Kbb_sf_el_pretag_nominal = {1,1,1,1,1};// {1,1,1.05 , 1.07,  1.08}; 
        Kbb_sf_el_tag_nominal = {1,1,1,1,1};// {1,1,1.05 , 1.07,  1.08}; //USING pretag for tagged
        Kbb_sf_mu_pretag_nominal = {1,1,1,1,1};// {1,1,0.37, 0.38,0.41 } ;
        Kbb_sf_mu_tag_nominal = {1,1,1,1,1};// {1,1,0.37, 0.38,0.41}; 
        
        Kbb_unc_stat_el_pretag = {1,1,1,1,1};// {1,1,0.045, 0.055, 0.088 };
        Kbb_unc_stat_el_tag = {1,1,1,1,1};// {1,1,0.058,  0.072  , 0.115 };
        Kbb_unc_stat_mu_pretag = {1,1,1,1,1};// {1,1,0.038, 0.054, 0.063 };
        Kbb_unc_stat_mu_tag = {1,1,1,1,1};// {1,1,0.048,  0.068  , 0.079 };
        
        Kbb_unc_syst_el_pretag = {1,1,1,1,1};// {1,1,0.253,	0.145,	0.229 };
        Kbb_unc_syst_el_tag = {1,1,1,1,1};// {1,1,0.186,	0.127,	0.222};
        Kbb_unc_syst_mu_pretag = {1,1,1,1,1};// {1,1,0.166,	0.157,	0.18};
        Kbb_unc_syst_mu_tag = {1,1,1,1,1};// {1,1,0.111,	0.112,	0.162 };
        ///////////////////////////
        Kc_sf_el_pretag_nominal = {1,1,1,1,1};// {1,1,0.57 , 0.58,  0.59}; 
        Kc_sf_el_tag_nominal = {1,1,1,1,1};// {1,1,0.57 , 0.58,  0.59 }; 
        Kc_sf_mu_pretag_nominal = {1,1,1,1,1};// {1,1,1.12, 1.16, 1.22 } ;
        Kc_sf_mu_tag_nominal = {1,1,1,1,1};// {1,1,1.12, 1.16, 1.22}; 
        
        Kc_unc_stat_el_pretag = {1,1,1,1,1};// {1,1,0.045, 0.055, 0.088 };
        Kc_unc_stat_el_tag = {1,1,1,1,1};// {1,1,0.058,  0.072  , 0.115 };
        Kc_unc_stat_mu_pretag = {1,1,1,1,1};// {1,1,0.038, 0.054, 0.063 };
        Kc_unc_stat_mu_tag = {1,1,1,1,1};// {1,1,0.048,  0.068  , 0.079 };
        
        Kc_unc_syst_el_pretag = {1,1,1,1,1};// {1,1,0.253,	0.145,	0.229 };
        Kc_unc_syst_el_tag = {1,1,1,1,1};// {1,1,0.186,	0.127,	0.222};
        Kc_unc_syst_mu_pretag = {1,1,1,1,1};// {1,1,0.166,	0.157,	0.18};
        Kc_unc_syst_mu_tag = {1,1,1,1,1};// {1,1,0.111,	0.112,	0.162 };
        ///////////////////////////
        Klight_sf_el_pretag_nominal = {1,1,1,1,1};// {1,1,1.13 , 1.15,  1.16}; 
        Klight_sf_el_tag_nominal = {1,1,1,1,1};// {1,1,1.13 , 1.15,  1.16 }; 
        Klight_sf_mu_pretag_nominal = {1,1,1,1,1};// {1,1,1.06, 1.09,1.16 } ;
        Klight_sf_mu_tag_nominal = {1,1,1,1,1};// {1,1,1.06, 1.09,1.16}; 
        
        Klight_unc_stat_el_pretag = {1,1,1,1,1};// {1,1,0.045, 0.055, 0.088 };
        Klight_unc_stat_el_tag = {1,1,1,1,1};// {1,1,0.058,  0.072  , 0.115 };
        Klight_unc_stat_mu_pretag = {1,1,1,1,1};// {1,1,0.038, 0.054, 0.063 };
        Klight_unc_stat_mu_tag = {1,1,1,1,1};// {1,1,0.048,  0.068  , 0.079 };
        
        Klight_unc_syst_el_pretag = {1,1,1,1,1};// {1,1,0.253,	0.145,	0.229 };
        Klight_unc_syst_el_tag = {1,1,1,1,1};// {1,1,0.186,	0.127,	0.222};
        Klight_unc_syst_mu_pretag = {1,1,1,1,1};// {1,1,0.166,	0.157,	0.18};
        Klight_unc_syst_mu_tag = {1,1,1,1,1};// {1,1,0.111,	0.112,	0.162 };
        ///////////////////////////
}

void WjetsSFDumper::OpenFiles()
{
        f_el = TFile::Open( "Wjets_CA_el.root", "recreate" );
        f_el->mkdir( "CA");
        f_el->mkdir( "Kbb");
        f_el->mkdir( "Kc");
        f_el->mkdir( "Klight");
        f_mu = TFile::Open( "Wjets_CA_mu.root", "recreate" );
        f_mu->mkdir( "CA");
        f_mu->mkdir( "Kbb");
        f_mu->mkdir( "Kc");
        f_mu->mkdir( "Klight");
}


void WjetsSFDumper::BuildHistograms()
{
        m_nbinsX = 5;
        m_nbinsY = 2;
        f_el->cd( "CA");
        h_CA_el_nominal =  new TH2D( "nominal", "nominal", m_nbinsX, -0.5, m_nbinsX -0.5, m_nbinsY, -0.5, m_nbinsY -0.5  );
        m_histos.push_back( h_CA_el_nominal );
        h_CA_el_stat =  new TH2D( "stat", "stat", m_nbinsX, -0.5, m_nbinsX -0.5, m_nbinsY, -0.5, m_nbinsY -0.5  );
        m_histos.push_back( h_CA_el_stat );
        h_CA_el_syst =  new TH2D( "syst", "syst", m_nbinsX, -0.5, m_nbinsX -0.5, m_nbinsY, -0.5, m_nbinsY -0.5  );
        m_histos.push_back( h_CA_el_syst );
        f_el->cd( "Kbb");
        h_Kbb_el_nominal =  new TH2D( "nominal", "nominal", m_nbinsX, -0.5, m_nbinsX -0.5, m_nbinsY, -0.5, m_nbinsY -0.5  );
        m_histos.push_back( h_Kbb_el_nominal );
        h_Kbb_el_stat =  new TH2D( "stat", "stat", m_nbinsX, -0.5, m_nbinsX -0.5, m_nbinsY, -0.5, m_nbinsY -0.5  );
        m_histos.push_back( h_Kbb_el_stat );
        h_Kbb_el_syst =  new TH2D( "syst", "syst", m_nbinsX, -0.5, m_nbinsX -0.5, m_nbinsY, -0.5, m_nbinsY -0.5  );
        m_histos.push_back( h_Kbb_el_syst );
        f_el->cd( "Kc");
        h_Kc_el_nominal =  new TH2D( "nominal", "nominal", m_nbinsX, -0.5, m_nbinsX -0.5, m_nbinsY, -0.5, m_nbinsY -0.5  );
        m_histos.push_back( h_Kc_el_nominal );
        h_Kc_el_stat =  new TH2D( "stat", "stat", m_nbinsX, -0.5, m_nbinsX -0.5, m_nbinsY, -0.5, m_nbinsY -0.5  );
        m_histos.push_back( h_Kc_el_stat );
        h_Kc_el_syst =  new TH2D( "syst", "syst", m_nbinsX, -0.5, m_nbinsX -0.5, m_nbinsY, -0.5, m_nbinsY -0.5  );
        m_histos.push_back( h_Kc_el_syst );
        f_el->cd( "Klight");
        h_Klight_el_nominal =  new TH2D( "nominal", "nominal", m_nbinsX, -0.5, m_nbinsX -0.5, m_nbinsY, -0.5, m_nbinsY -0.5  );
        m_histos.push_back( h_Klight_el_nominal );
        h_Klight_el_stat =  new TH2D( "stat", "stat", m_nbinsX, -0.5, m_nbinsX -0.5, m_nbinsY, -0.5, m_nbinsY -0.5  );
        m_histos.push_back( h_Klight_el_stat );
        h_Klight_el_syst =  new TH2D( "syst", "syst", m_nbinsX, -0.5, m_nbinsX -0.5, m_nbinsY, -0.5, m_nbinsY -0.5  );
        m_histos.push_back( h_Klight_el_syst );
        
        f_mu->cd( "CA");
        h_CA_mu_nominal =  new TH2D( "nominal", "nominal", m_nbinsX, -0.5, m_nbinsX -0.5, m_nbinsY, -0.5, m_nbinsY -0.5  );
        m_histos.push_back( h_CA_mu_nominal );
        h_CA_mu_stat =  new TH2D( "stat", "stat", m_nbinsX, -0.5, m_nbinsX -0.5, m_nbinsY, -0.5, m_nbinsY -0.5  );
        m_histos.push_back( h_CA_mu_stat );
        h_CA_mu_syst =  new TH2D( "syst", "syst", m_nbinsX, -0.5, m_nbinsX -0.5, m_nbinsY, -0.5, m_nbinsY -0.5  );
        m_histos.push_back( h_CA_mu_syst );
        f_mu->cd( "Kbb");
        h_Kbb_mu_nominal =  new TH2D( "nominal", "nominal", m_nbinsX, -0.5, m_nbinsX -0.5, m_nbinsY, -0.5, m_nbinsY -0.5  );
        m_histos.push_back( h_Kbb_mu_nominal );
        h_Kbb_mu_stat =  new TH2D( "stat", "stat", m_nbinsX, -0.5, m_nbinsX -0.5, m_nbinsY, -0.5, m_nbinsY -0.5  );
        m_histos.push_back( h_Kbb_mu_stat );
        h_Kbb_mu_syst =  new TH2D( "syst", "syst", m_nbinsX, -0.5, m_nbinsX -0.5, m_nbinsY, -0.5, m_nbinsY -0.5  );
        m_histos.push_back( h_Kbb_mu_syst );
        f_mu->cd( "Kc");
        h_Kc_mu_nominal =  new TH2D( "nominal", "nominal", m_nbinsX, -0.5, m_nbinsX -0.5, m_nbinsY, -0.5, m_nbinsY -0.5  );
        m_histos.push_back( h_Kc_mu_nominal );
        h_Kc_mu_stat =  new TH2D( "stat", "stat", m_nbinsX, -0.5, m_nbinsX -0.5, m_nbinsY, -0.5, m_nbinsY -0.5  );
        m_histos.push_back( h_Kc_mu_stat );
        h_Kc_mu_syst =  new TH2D( "syst", "syst", m_nbinsX, -0.5, m_nbinsX -0.5, m_nbinsY, -0.5, m_nbinsY -0.5  );
        m_histos.push_back( h_Kc_mu_syst );
        f_mu->cd( "Klight");
        h_Klight_mu_nominal =  new TH2D( "nominal", "nominal", m_nbinsX, -0.5, m_nbinsX -0.5, m_nbinsY, -0.5, m_nbinsY -0.5  );
        m_histos.push_back( h_Klight_mu_nominal );
        h_Klight_mu_stat =  new TH2D( "stat", "stat", m_nbinsX, -0.5, m_nbinsX -0.5, m_nbinsY, -0.5, m_nbinsY -0.5  );
        m_histos.push_back( h_Klight_mu_stat );
        h_Klight_mu_syst =  new TH2D( "syst", "syst", m_nbinsX, -0.5, m_nbinsX -0.5, m_nbinsY, -0.5, m_nbinsY -0.5  );
        m_histos.push_back( h_Klight_mu_syst );
        
        
        char title[100];
        for( auto& h: m_histos)
        {
                for( int i = 0; i < m_nbinsX; ++i )
                {
                        if( i < 4 ) sprintf( title, "== %i jets", i );
                        else sprintf( title, ">= %i jets", i );
                        h->GetXaxis()->SetBinLabel( i+1, title);
                }
                
                for( int i = 0; i < m_nbinsY; ++i )
                {
                        if( i < 1 ) sprintf( title, "== %i b-jets", i );
                        else sprintf( title, ">= %i b-jets", i );
                        h->GetYaxis()->SetBinLabel( i+1, title);
                } 
        }

}

void WjetsSFDumper::DumpSF()
{
        

        for( int i = 1; i <= m_nbinsX; ++i )
        {
                h_CA_el_nominal->SetBinContent( i, 1, CA_sf_el_pretag_nominal[i-1] );
                h_CA_el_nominal->SetBinContent( i, 2, CA_sf_el_tag_nominal[i-1] );
                h_CA_el_stat->SetBinContent( i, 1, CA_sf_el_pretag_nominal[i-1] +  CA_unc_stat_el_pretag[i-1] );
                h_CA_el_stat->SetBinContent( i, 2, CA_sf_el_tag_nominal[i-1] +  CA_unc_stat_el_tag[i-1] );
                h_CA_el_syst->SetBinContent( i, 1, CA_sf_el_pretag_nominal[i-1] +  CA_unc_syst_el_pretag[i-1] );
                h_CA_el_syst->SetBinContent( i, 2, CA_sf_el_tag_nominal[i-1] +  CA_unc_syst_el_tag[i-1] );
                ///////
                h_Kbb_el_nominal->SetBinContent( i, 1, Kbb_sf_el_pretag_nominal[i-1] );
                h_Kbb_el_nominal->SetBinContent( i, 2, Kbb_sf_el_tag_nominal[i-1] );
                h_Kbb_el_stat->SetBinContent( i, 1, Kbb_sf_el_pretag_nominal[i-1] +  Kbb_unc_stat_el_pretag[i-1] );
                h_Kbb_el_stat->SetBinContent( i, 2, Kbb_sf_el_tag_nominal[i-1] +  Kbb_unc_stat_el_tag[i-1] );
                h_Kbb_el_syst->SetBinContent( i, 1, Kbb_sf_el_pretag_nominal[i-1] +  Kbb_unc_syst_el_pretag[i-1] );
                h_Kbb_el_syst->SetBinContent( i, 2, Kbb_sf_el_tag_nominal[i-1] +  Kbb_unc_syst_el_tag[i-1] );
                ///////
                h_Kc_el_nominal->SetBinContent( i, 1, Kc_sf_el_pretag_nominal[i-1] );
                h_Kc_el_nominal->SetBinContent( i, 2, Kc_sf_el_tag_nominal[i-1] );
                h_Kc_el_stat->SetBinContent( i, 1, Kc_sf_el_pretag_nominal[i-1] +  Kc_unc_stat_el_pretag[i-1] );
                h_Kc_el_stat->SetBinContent( i, 2, Kc_sf_el_tag_nominal[i-1] +  Kc_unc_stat_el_tag[i-1] );
                h_Kc_el_syst->SetBinContent( i, 1, Kc_sf_el_pretag_nominal[i-1] +  Kc_unc_syst_el_pretag[i-1] );
                h_Kc_el_syst->SetBinContent( i, 2, Kc_sf_el_tag_nominal[i-1] +  Kc_unc_syst_el_tag[i-1] );
                ///////
                h_Klight_el_nominal->SetBinContent( i, 1, Klight_sf_el_pretag_nominal[i-1] );
                h_Klight_el_nominal->SetBinContent( i, 2, Klight_sf_el_tag_nominal[i-1] );
                h_Klight_el_stat->SetBinContent( i, 1, Klight_sf_el_pretag_nominal[i-1] +  Klight_unc_stat_el_pretag[i-1] );
                h_Klight_el_stat->SetBinContent( i, 2, Klight_sf_el_tag_nominal[i-1] +  Klight_unc_stat_el_tag[i-1] );
                h_Klight_el_syst->SetBinContent( i, 1, Klight_sf_el_pretag_nominal[i-1] +  Klight_unc_syst_el_pretag[i-1] );
                h_Klight_el_syst->SetBinContent( i, 2, Klight_sf_el_tag_nominal[i-1] +  Klight_unc_syst_el_tag[i-1] );
                ///////
              
                ///////
                h_CA_mu_nominal->SetBinContent( i, 1, CA_sf_mu_pretag_nominal[i-1] );
                h_CA_mu_nominal->SetBinContent( i, 2, CA_sf_mu_tag_nominal[i-1] );
                h_CA_mu_stat->SetBinContent( i, 1, CA_sf_mu_pretag_nominal[i-1] +  CA_unc_stat_mu_pretag[i-1] );
                h_CA_mu_stat->SetBinContent( i, 2, CA_sf_mu_tag_nominal[i-1] +  CA_unc_stat_mu_tag[i-1] );
                h_CA_mu_syst->SetBinContent( i, 1, CA_sf_mu_pretag_nominal[i-1] +  CA_unc_syst_mu_pretag[i-1] );
                h_CA_mu_syst->SetBinContent( i, 2, CA_sf_mu_tag_nominal[i-1] +  CA_unc_syst_mu_tag[i-1] );
                ///////
                h_Kbb_mu_nominal->SetBinContent( i, 1, Kbb_sf_mu_pretag_nominal[i-1] );
                h_Kbb_mu_nominal->SetBinContent( i, 2, Kbb_sf_mu_tag_nominal[i-1] );
                h_Kbb_mu_stat->SetBinContent( i, 1, Kbb_sf_mu_pretag_nominal[i-1] +  Kbb_unc_stat_mu_pretag[i-1] );
                h_Kbb_mu_stat->SetBinContent( i, 2, Kbb_sf_mu_tag_nominal[i-1] +  Kbb_unc_stat_mu_tag[i-1] );
                h_Kbb_mu_syst->SetBinContent( i, 1, Kbb_sf_mu_pretag_nominal[i-1] +  Kbb_unc_syst_mu_pretag[i-1] );
                h_Kbb_mu_syst->SetBinContent( i, 2, Kbb_sf_mu_tag_nominal[i-1] +  Kbb_unc_syst_mu_tag[i-1] );
                ///////
                h_Kc_mu_nominal->SetBinContent( i, 1, Kc_sf_mu_pretag_nominal[i-1] );
                h_Kc_mu_nominal->SetBinContent( i, 2, Kc_sf_mu_tag_nominal[i-1] );
                h_Kc_mu_stat->SetBinContent( i, 1, Kc_sf_mu_pretag_nominal[i-1] +  Kc_unc_stat_mu_pretag[i-1] );
                h_Kc_mu_stat->SetBinContent( i, 2, Kc_sf_mu_tag_nominal[i-1] +  Kc_unc_stat_mu_tag[i-1] );
                h_Kc_mu_syst->SetBinContent( i, 1, Kc_sf_mu_pretag_nominal[i-1] +  Kc_unc_syst_mu_pretag[i-1] );
                h_Kc_mu_syst->SetBinContent( i, 2, Kc_sf_mu_tag_nominal[i-1] +  Kc_unc_syst_mu_tag[i-1] );
                ///////
                h_Klight_mu_nominal->SetBinContent( i, 1, Klight_sf_mu_pretag_nominal[i-1] );
                h_Klight_mu_nominal->SetBinContent( i, 2, Klight_sf_mu_tag_nominal[i-1] );
                h_Klight_mu_stat->SetBinContent( i, 1, Klight_sf_mu_pretag_nominal[i-1] +  Klight_unc_stat_mu_pretag[i-1] );
                h_Klight_mu_stat->SetBinContent( i, 2, Klight_sf_mu_tag_nominal[i-1] +  Klight_unc_stat_mu_tag[i-1] );
                h_Klight_mu_syst->SetBinContent( i, 1, Klight_sf_mu_pretag_nominal[i-1] +  Klight_unc_syst_mu_pretag[i-1] );
                h_Klight_mu_syst->SetBinContent( i, 2, Klight_sf_mu_tag_nominal[i-1] +  Klight_unc_syst_mu_tag[i-1] );
                ///////
              
                ///////
        }
        f_el->Write();
        f_mu->Write();
        
        
}


WjetsSFDumper::~WjetsSFDumper()
{
        
        for( auto& h: m_histos)
        {
                delete h;
        }       
        f_el->Close();
        delete f_el;
        f_mu->Close();
        delete f_mu; 
        
                
}
