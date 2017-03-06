#ifndef __ROOTCORE_HEADERS_H__
#define __ROOTCORE_HEADERS_H__

/*
////////////////////////
// Electrons and Photons
#include <egammaAnalysisUtils/egammaTriggerMatching.h>
#include <egammaAnalysisUtils/EnergyRescaler.h>


////////////////////////
// Muons

#include <MuonMomentumCorrections/SmearingClass.h>


////////////////////////
// Jets

#include <JetUncertainties/MultijetJESUncertaintyProvider.h>

*/
////////////////////////
// QCD

/*#include "FakesMacros/MatrixUtils.h"
#include "FakesMacros/MMEfficiency.h"
#include "FakesMacros/MMEffSet.h"
#include "FakesMacros/FakesWeights.h"
*/
//////////////////////////
// Lumi
#include "TopDataPreparation/SampleXsectionSvc.h"
//#include "TopFakes/FakesWeights.h"


/*
///////////////////////
// BTagging
#include "CalibrationDataInterface/CalibrationDataInterfaceROOT.h"*/
//#include "CalibrationDataInterface/

//Bootstrap
#ifdef BOOTSTRAP_MAMBO
        #ifndef BOOTSTRAP_MAMBO_ADDED
        #define BOOTSTRAP_MAMBO_ADDED
        #pragma message("INFO: adding bootstrap support")

        #include "BootstrapGenerator/BootstrapGenerator.h"
        #include "BootstrapGenerator/TH1DBootstrap.h"
        #endif
#endif


#endif /** __ROOTCORE_HEADERS_H__ */
