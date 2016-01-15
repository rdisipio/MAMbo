ROOTCOREINCS = -I$(ROOTCOREBIN)/include
ROOTCORELIBS = $(ROOTCOREBIN)/lib/$(ARCH)

#ROOTCORETOOLS += FakesMacros 
#ROOTCORETOOLS += CalibrationDataInterface 
ROOTCORETOOLS += TopDataPreparation
#ROOTCORETOOLS += TopFakes
#ROOTCORETOOLS += egammaAnalysisUtils egammaEvent
#ROOTCORETOOLS += FakesTriggerUtils
#ROOTCORETOOLS += MissingETUtility METAnalysisCommon METSystematics METTrackUtil
#ROOTCORETOOLS += MuonEfficiencyCorrections MuonMomentumCorrections 
#ROOTCORETOOLS += ApplyJetCalibration ApplyJetResolutionSmearing JetEffiProvider JetResolution JetUncertainties
#ROOTCORETOOLS += PileupReweighting 
#ROOTCORETOOLS += GoodRunsLists
#ROOTCORETOOLS += TopEvent 
#ROOTCORETOOLS += TopConfiguration
#ROOTCORETOOLS += AsgTools



ROOTCORELDFLAGS = -L$(ROOTCORELIBS) $(foreach tool,$(ROOTCORETOOLS),-l$(tool))


CFLAGS += $(ROOTCOREINCS)
LIBS   += $(ROOTCORELDFLAGS)
