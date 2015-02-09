include ../Makefile.inc

TOOLS   = PhysicsHelperFunctions HelperFunctions PluginManager HistogramManager ConfigManager 
TOOLS  += XMLBin XMLVariable XMLLevel ControlPlotValues JetValues Particle 

ifdef FASTJETLOCATION
TOOLS += HEPTopTagger
#HEPTopTaggerHelperFunctions
endif

SRCS    = IHistogramFiller.cxx INtupleWrapper.cxx ICutFlow.cxx $(TOOLS:=.cxx)
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
