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
TOOLS   = HelperFunctions PluginManager HistogramManager
SRCS    = $(NTUPLE).cxx NtupleWrapper.cxx EventMaker.cxx CutFlow.cxx $(TOOLS:=.cxx)
OBJS    = ${SRCS:.cxx=.o}

EXE     = runMAMbo

PLUGIN  = CutFlowBoostedSL
SOPLIB  = lib$(PLUGIN).so

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
	$(LD) $(DEBUG) $(SOFLAGS) -c $(PLUGIN).cxx
	$(LD) $(SOFLAGS) -Wl,-export-dynamic,$(SOPLIB) $(PLUGIN).o -ldl -o $(SOLIB)

clean:
	rm -rf *.o $(EXE) $(SOLIB)
