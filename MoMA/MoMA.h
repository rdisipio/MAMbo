#ifndef __MOMA_H__
#define __MOMA_H__

#include "Commons.h"
#include "src/EventData.h"

#include "RootCoreHeaders.h"



using namespace std;

enum BTagType {
    UNKNOWN_TAGGER=0,
    PRETAG,
    MV1_60,
    MV1_70,
    MV1_80,
    MV1c_50,
    MV1c_57
  };

enum SYSTEMATIC_TYPE {
   NOMINAL = 0,
   BTAGSFUP, BTAGSFDOWN, CTAUTAGSFUP, CTAUTAGSFDOWN, MISTAGSFUP, MISTAGSFDOWN,
   QCD_MM_EL_FAKE_MC_UP, QCD_MM_EL_FAKE_MC_DOWN, QCD_MM_EL_FAKE_ALTERNATE, QCD_MM_EL_REAL_ALTERNATE, QCD_MM_EL_PAR_ALTERNATE, 
   QCD_MM_MU_FAKE_MC_UP, QCD_MM_MU_FAKE_MC_DOWN, QCD_MM_MU_FAKE_ALTERNATE, QCD_MM_MU_REAL_ALTERNATE, QCD_MM_MU_PAR_ALTERNATE
};

enum XS_SYSTEMATIC_TYPE {
   XS_NOMINAL = 0,
   XS_DOWN, XS_UP
};

class MoMATool
{
 public:
	virtual ~MoMATool();

	static MoMATool * GetHandle();

 public:
        inline void SetSystematicType( SYSTEMATIC_TYPE type ) { m_syst_type = type; };
        inline SYSTEMATIC_TYPE GetSystematicType() const      { return m_syst_type; };
        inline void SetXsSystematicType( XS_SYSTEMATIC_TYPE type ) { m_xs_syst_type = type; };
        inline XS_SYSTEMATIC_TYPE GetXsSystematicType() const      { return m_xs_syst_type; };

	inline void SetDebug( bool debug = true ) { m_debug = debug; };

        //double GetFakesWeight( int channel, const MMEvent& event, const MMLepton& lepton, bool tight );
       // double GetFakesWeight( int channel, bool tight, double lep_pt, double lep_eta, double el_cl_eta, double dR_lj_min, 
         //                          double pTdR_lj_min, double jet_pt0, int jet_n, int nJet_tagged, int trigger);
	//double GetBTagWeight( EventData * ed, const double mv1_cut = 0.7892, SYSTEMATIC_TYPE syst_type = NOMINAL ) const;
	
	double GetLumiWeight( int runNumber, float nEvents, float lumi = 1 );

 protected:
    //    void InitializeBTagWeights();
        void InitializeLumiWeights();

 private:
	MoMATool();

        SYSTEMATIC_TYPE m_syst_type;
        XS_SYSTEMATIC_TYPE m_xs_syst_type;        
	bool           m_debug;

      //  FakesWeights * m_fakes_weighter_el;
      //  FakesWeights * m_fakes_weighter_mu;
      

	SampleXsectionSvc * m_lumiSvc;

	//Analysis::CalibrationDataInterfaceROOT * m_btag_weighter;
        //unsigned int * m_CDIindex_SF;
	//unsigned int * m_CDIindex_Eff;
	
	double m_lumiWeight;
	int m_lumiRunNumber;

};

#endif /** __MOMA_H__ */

// Local Variables:
// mode: c++
// End:
