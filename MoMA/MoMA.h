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
        double GetFakesWeight( int channel, const MMEvent& event, const MMLepton& lepton, bool tight );

 private:
	MoMATool();

        FakesWeights * m_fakes_weighter_el;
        FakesWeights * m_fakes_weighter_mu;
};

#endif /** __MOMA_H__ */

// Local Variables:
// mode: c++
// End:
