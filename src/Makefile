include ../Makefile.inc

TOOLS  += PhysicsHelperFunctions HelperFunctions PluginManager HistogramManager ConfigManager ScalerTree
TOOLS  += XMLBin XMLVariable XMLLevel ControlPlotValues JetValues Particle ScalerFakes ScalerWjets

ifdef LHAPATH
TOOLS += ScalerPDF
endif

ifdef FASTJETLOCATION
TOOLS += HEPTopTagger
#HEPTopTaggerHelperFunctions
endif

SRCS    = IHistogramFiller.cxx INtupleWrapper.cxx ICutFlow.cxx IAnalysisCut.cxx IEventModifier.cxx
SRCS   += $(TOOLS:=.cxx)
OBJS    = ${SRCS:.cxx=.o}

SOLIB   = lib$(PROJECT).so

all: $(EXE) $(SOLIB)
debug:   all
release: all

$(SOLIB): $(OBJS)
	@echo
	@echo Building $@
	$(LD) $(DEBUG) $(SOFLAGS) $(LIBS) $(OBJS) -o $@
	@echo

$(EXE): $(EXE).o $(SOLIB)
	$(LD) $(CFLAGS) $(LIBS) -L. -l$(PROJECT) $(EXE).o -o $@

clean:
	rm -rf *.o *.so $(EXE) 
