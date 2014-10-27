include ../Makefile.inc

TOOLS   = PhysicsHelperFunctions HelperFunctions PluginManager HistogramManager ConfigManager HEPTopTagger #HEPTopTaggerHelperFunctions
SRCS    = INtupleWrapper.cxx ICutFlow.cxx $(TOOLS:=.cxx)
OBJS    = ${SRCS:.cxx=.o}

SOLIB   = lib$(PROJECT).so

all: $(EXE) $(SOLIB)

$(SOLIB): $(OBJS)
	$(LD) $(DEBUG) $(SOFLAGS) $(OBJS) -o $@


$(EXE): $(EXE).o $(SOLIB)
	$(LD) $(CFLAGS) $(LIBS) -L. -l$(PROJECT) $(EXE).o -o $@

clean:
	rm -rf *.o *.so $(EXE) 
