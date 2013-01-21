CC=g++
LD=g++
CFLAGS  = -fPIC -g 
ROOTCFLAGS = $(shell root-config --cflags)
XMLCFLAGS  = $(shell xml2-config --cflags)
CFLAGS += $(ROOTCFLAGS) $(XMLCFLAGS)
DEBUG = -g
SOFLAGS = -fPIC -shared $(ROOTCFLAGS) $(XMLCFLAGS)

LIBS    = $(shell root-config --libs) $(shell xml2-config --libs)

PROJECT = MAMbo
SOLIB   = lib$(PROJECT).so

NTUPLE  = MiniSLBoost
NTUPLESRC = NtupleWrapper$(NTUPLE).cxx
NTUPLEOBJ = $(NTUPLESRC:.cxx=.o)
TOOLS   = HelperFunctions PluginManager HistogramManager ConfigManager
SRCS    = $(NTUPLE).cxx INtupleWrapper.cxx CutFlow.cxx $(TOOLS:=.cxx) $(NTUPLESRC)
OBJS    = ${SRCS:.cxx=.o}

EXE     = runMAMbo

CUTFLOW     = CutFlowBoostedSL
CUTFLOWLIB  = lib$(CUTFLOW).so

NTUPLELIB   = libNtupleWrapper$(NTUPLE).so

.SUFFIXES:
.SUFFIXES: .o .cxx .C

.cxx.o:
	$(CC) $(CFLAGS) -c $<


all: $(EXE) $(SOLIB) $(LIB) plugins


$(SOLIB): $(OBJS)
	$(LD) $(DEBUG) $(SOFLAGS) $(OBJS) -o $@


$(EXE): $(EXE).o $(SOLIB)
	$(LD) $(CFLAGS) $(LIBS) -L. -l$(PROJECT) $(EXE).o -o $@


plugins: 
	$(LD) $(DEBUG) $(SOFLAGS) -c $(CUTFLOW).cxx
	$(LD) $(SOFLAGS) -Wl,-export-dynamic,$(CUTFLOWLIB) $(CUTFLOW).o -ldl -o $(CUTFLOWLIB)

	$(LD) $(SOFLAGS) -Wl,-export-dynamic,$(NTUPLELIB) $(NTUPLEOBJ) -ldl -o $(NTUPLELIB)

clean:
	rm -rf *.o *.so $(EXE) 
