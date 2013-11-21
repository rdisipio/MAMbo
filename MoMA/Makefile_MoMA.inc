include $(MAMBODIR)/Makefile.inc

ROOTCOREINCS = $(ROOTCOREDIR)/RootCore/include
ROOTCORELIBS = $(ROOTCOREDIR)/RootCore/lib

ROOTCORETOOLS += egammaAnalysisUtils egammaEvent
ROOTCORETOOLS += MissingETUtility
ROOTCORETOOLS += MuonEfficiencyCorrections MuonMomentumCorrections 
ROOTCORETOOLS += ApplyJetCalibration ApplyJetResolutionSmearing JetEffiProvider JetResolution JetUncertainties
ROOTCORETOOLS += PileupReweighting 
ROOTCORETOOLS += GoodRunsLists
ROOTCORELDFLAGS = -L$(ROOTCOREDIR)/RootCore/lib $(foreach tool,$(ROOTCORETOOLS),-l$(tool))

.cxx.o:
	$(CC) $(CFLAGS) -c -I$(ROOTCOREINCS) $<

MOMA_TAG   = MoMA
MOMA_SOLIB = lib$(MOMA_TAG).so

LDFLAGS += -I$(ROOTCOREINCS)
SOFLAGS += $(ROOTCORELDFLAGS)
