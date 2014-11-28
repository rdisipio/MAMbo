#ifndef __MOMA_H__
#define __MOMA_H__

#include "RootCoreHeaders.h"

class MoMATool
{
 public:
	virtual ~MoMATool();

	static MoMATool * GetHandle();

 private:
	MoMATool();

	QCDMMScale * m_qcd_mm;
};

#endif

// Local Variables:
// mode: c++
// End:
