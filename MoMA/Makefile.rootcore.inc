ROOTCOREINCS = -I$(ROOTCOREDIR)/include
ROOTCORELIBS = $(ROOTCOREDIR)/lib/$(ARCH)

#ROOTCORETOOLS += egammaAnalysisUtils egammaEvent
ROOTCORETOOLS += FakesMacros 
#ROOTCORETOOLS += FakesTriggerUtils
#ROOTCORETOOLS += MissingETUtility METAnalysisCommon METSystematics METTrackUtil
#ROOTCORETOOLS += MuonEfficiencyCorrections MuonMomentumCorrections 
#ROOTCORETOOLS += ApplyJetCalibration ApplyJetResolutionSmearing JetEffiProvider JetResolution JetUncertainties
#ROOTCORETOOLS += PileupReweighting 
#ROOTCORETOOLS += GoodRunsLists

ROOTCORELDFLAGS = -L$(ROOTCORELIBS) $(foreach tool,$(ROOTCORETOOLS),-l$(tool))


CFLAGS += $(ROOTCOREINCS)
LIBS   += $(ROOTCORELDFLAGS)
