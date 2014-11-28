include $(MAMBODIR)/Makefile.inc

ROOTCOREINCS = $(ROOTCOREDIR)/include
ROOTCORELIBS = $(ROOTCOREDIR)/lib/$(ARCH)

ROOTCORETOOLS += egammaAnalysisUtils egammaEvent
ROOTCORETOOLS += MissingETUtility
ROOTCORETOOLS += MuonEfficiencyCorrections MuonMomentumCorrections 
ROOTCORETOOLS += ApplyJetCalibration ApplyJetResolutionSmearing JetEffiProvider JetResolution JetUncertainties
ROOTCORETOOLS += PileupReweighting 
ROOTCORETOOLS += GoodRunsLists
ROOTCORELDFLAGS = -L$(ROOTCORELIBS) $(foreach tool,$(ROOTCORETOOLS),-l$(tool))

.cxx.o:
	@echo Compiling $<
	$(CC) $(CFLAGS) -c -I$(ROOTCOREINCS) $(ROOTCORELDFLAGS) $<

MOMA_TAG   = MoMA
MOMA_SOLIB = lib$(MOMA_TAG).so

LDFLAGS += -I$(ROOTCOREINCS)
SOFLAGS += $(ROOTCORELDFLAGS)
