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


class MoMATool
{
 public:
	virtual ~MoMATool();

	static MoMATool * GetHandle();

 public:
	inline void SetDebug( bool debug = true ) { m_debug = debug; };

        double GetFakesWeight( int channel, const MMEvent& event, const MMLepton& lepton, bool tight );
        double GetFakesWeight( int channel, bool tight, double lep_pt, double lep_eta, double el_cl_eta, double dR_lj_min, 
                                   double pTdR_lj_min, double jet_pt0, int jet_n, int nJet_tagged, int trigger);

	double GetBTagWeight( EventData * ed, const double mv1_cut = 0.7892 ) const;

 private:
	MoMATool();

	bool           m_debug;

        FakesWeights * m_fakes_weighter_el;
        FakesWeights * m_fakes_weighter_mu;

	Analysis::CalibrationDataInterfaceROOT * m_btag_weighter;
        unsigned int * m_CDIindex_SF;
	unsigned int * m_CDIindex_Eff;
};

#endif /** __MOMA_H__ */

// Local Variables:
// mode: c++
// End:
