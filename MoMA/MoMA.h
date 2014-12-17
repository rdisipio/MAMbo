#ifndef __MOMA_H__
#define __MOMA_H__

#include "Commons.h"

#include "RootCoreHeaders.h"

using namespace std;

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
 private:
	MoMATool();

	bool           m_debug;

        FakesWeights * m_fakes_weighter_el;
        FakesWeights * m_fakes_weighter_mu;
};

#endif /** __MOMA_H__ */

// Local Variables:
// mode: c++
// End:
