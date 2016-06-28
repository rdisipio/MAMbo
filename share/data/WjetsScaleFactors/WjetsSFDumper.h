#ifndef WJETS_
#define WJETS_
#include <vector>
#include "TFile.h"
#include "TH2D.h"
#include <string>
class WjetsSFDumper
{
private:
        std::vector< double > CA_sf_el_pretag_nominal;// {1,1,0.911 , 0.783, 0.907}; 
        std::vector< double > CA_sf_el_tag_nominal;// {1,1,1.167 , 1.003 , 1.162 }; 
        std::vector< double > CA_sf_mu_pretag_nominal;// {1,1,1.023, 0.931,0.917 } ;
        std::vector< double > CA_sf_mu_tag_nominal;// {1,1,1.283, 1.168, 1.150}; 

        std::vector< double > CA_unc_stat_el_pretag;// {1,1,0.045, 0.055, 0.088 };
        std::vector< double > CA_unc_stat_el_tag;// {1,1,0.058, 0.072 , 0.115 };
        std::vector< double > CA_unc_stat_mu_pretag;// {1,1,0.038, 0.054, 0.063 };
        std::vector< double > CA_unc_stat_mu_tag;// {1,1,0.048, 0.068 , 0.079 };

        std::vector< double > CA_unc_syst_el_pretag;// {1,1,0.253,	0.145,	0.229 };
        std::vector< double > CA_unc_syst_el_tag;// {1,1,0.186,	0.127,	0.222};
        std::vector< double > CA_unc_syst_mu_pretag;// {1,1,0.166,	0.157,	0.18};
        std::vector< double > CA_unc_syst_mu_tag;// {1,1,0.111,	0.112,	0.162 };
        ///////////////////////////
        std::vector< double > Kbb_sf_el_pretag_nominal;// {1,1,1.05 , 0.57, 1.13}; 
        std::vector< double > Kbb_sf_el_tag_nominal;// {1,1,1.05 , 0.57, 1.13}; //USING pretag for tagged
        std::vector< double > Kbb_sf_mu_pretag_nominal;// {1,1,1.023, 0.931,0.917 } ;
        std::vector< double > Kbb_sf_mu_tag_nominal;// {1,1,1.283, 1.168, 1.150}; 

        std::vector< double > Kbb_unc_stat_el_pretag;// {1,1,0.045, 0.055, 0.088 };
        std::vector< double > Kbb_unc_stat_el_tag;// {1,1,0.058, 0.072 , 0.115 };
        std::vector< double > Kbb_unc_stat_mu_pretag;// {1,1,0.038, 0.054, 0.063 };
        std::vector< double > Kbb_unc_stat_mu_tag;// {1,1,0.048, 0.068 , 0.079 };

        std::vector< double > Kbb_unc_syst_el_pretag;// {1,1,0.253,	0.145,	0.229 };
        std::vector< double > Kbb_unc_syst_el_tag;// {1,1,0.186,	0.127,	0.222};
        std::vector< double > Kbb_unc_syst_mu_pretag;// {1,1,0.166,	0.157,	0.18};
        std::vector< double > Kbb_unc_syst_mu_tag;// {1,1,0.111,	0.112,	0.162 };
        ///////////////////////////
        std::vector< double > Kc_sf_el_pretag_nominal;// {1,1,0.911 , 0.783, 0.907}; 
        std::vector< double > Kc_sf_el_tag_nominal;// {1,1,1.167 , 1.003 , 1.162 }; 
        std::vector< double > Kc_sf_mu_pretag_nominal;// {1,1,1.023, 0.931,0.917 } ;
        std::vector< double > Kc_sf_mu_tag_nominal;// {1,1,1.283, 1.168, 1.150}; 

        std::vector< double > Kc_unc_stat_el_pretag;// {1,1,0.045, 0.055, 0.088 };
        std::vector< double > Kc_unc_stat_el_tag;// {1,1,0.058, 0.072 , 0.115 };
        std::vector< double > Kc_unc_stat_mu_pretag;// {1,1,0.038, 0.054, 0.063 };
        std::vector< double > Kc_unc_stat_mu_tag;// {1,1,0.048, 0.068 , 0.079 };

        std::vector< double > Kc_unc_syst_el_pretag;// {1,1,0.253,	0.145,	0.229 };
        std::vector< double > Kc_unc_syst_el_tag;// {1,1,0.186,	0.127,	0.222};
        std::vector< double > Kc_unc_syst_mu_pretag;// {1,1,0.166,	0.157,	0.18};
        std::vector< double > Kc_unc_syst_mu_tag;// {1,1,0.111,	0.112,	0.162 };
        ///////////////////////////
        std::vector< double > Klight_sf_el_pretag_nominal;// {1,1,0.911 , 0.783, 0.907}; 
        std::vector< double > Klight_sf_el_tag_nominal;// {1,1,1.167 , 1.003 , 1.162 }; 
        std::vector< double > Klight_sf_mu_pretag_nominal;// {1,1,1.023, 0.931,0.917 } ;
        std::vector< double > Klight_sf_mu_tag_nominal;// {1,1,1.283, 1.168, 1.150}; 

        std::vector< double > Klight_unc_stat_el_pretag;// {1,1,0.045, 0.055, 0.088 };
        std::vector< double > Klight_unc_stat_el_tag;// {1,1,0.058, 0.072 , 0.115 };
        std::vector< double > Klight_unc_stat_mu_pretag;// {1,1,0.038, 0.054, 0.063 };
        std::vector< double > Klight_unc_stat_mu_tag;// {1,1,0.048, 0.068 , 0.079 };

        std::vector< double > Klight_unc_syst_el_pretag;// {1,1,0.253,	0.145,	0.229 };
        std::vector< double > Klight_unc_syst_el_tag;// {1,1,0.186,	0.127,	0.222};
        std::vector< double > Klight_unc_syst_mu_pretag;// {1,1,0.166,	0.157,	0.18};
        std::vector< double > Klight_unc_syst_mu_tag;// {1,1,0.111,	0.112,	0.162 };
        ///////////////////////////
        
        TFile * f_el, *f_mu;
        std::string m_elFilename, m_muFilename;
        TH2D * h_CA_el_nominal,  * h_CA_el_stat, * h_CA_el_syst; 
        TH2D * h_Kbb_el_nominal,  * h_Kbb_el_stat, * h_Kbb_el_syst; 
        TH2D * h_Kc_el_nominal,  * h_Kc_el_stat, * h_Kc_el_syst; 
        TH2D * h_Klight_el_nominal,  * h_Klight_el_stat, * h_Klight_el_syst; 
        TH2D * h_CA_mu_nominal,  * h_CA_mu_stat, * h_CA_mu_syst; 
        TH2D * h_Kbb_mu_nominal,  * h_Kbb_mu_stat, * h_Kbb_mu_syst; 
        TH2D * h_Kc_mu_nominal,  * h_Kc_mu_stat, * h_Kc_mu_syst; 
        TH2D * h_Klight_mu_nominal,  * h_Klight_mu_stat, * h_Klight_mu_syst; 
        std::vector< TH2D* > m_histos;
        int m_nbinsX, m_nbinsY;
        
        public:
              WjetsSFDumper(){};
              ~WjetsSFDumper();
              void BuildArrays();
              void OpenFiles();
              void BuildHistograms();
              void DumpSF();
              void Initialize(){BuildArrays(); OpenFiles(); BuildHistograms(); } ;

};




#endif
