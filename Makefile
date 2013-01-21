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

NTUPLES  = MiniSLBoost MiniML
NTUPLESRC = $(foreach NTUPLE, $(NTUPLES), NtupleWrapper$(NTUPLE).cxx)
NTUPLEOBJ = $(NTUPLESRC:.cxx=.o)
NTUPLELIB   = $(foreach NTUPLE, $(NTUPLES), libNtupleWrapper$(NTUPLE).so )

CUTFLOWS     = BoostedSL FakeRateZjet
CUTFLOWSSRCS = $(foreach CF, $(CUTFLOWS), CutFlow$(CF).cxx)
CUTFLOWLIBS  = $(foreach CF, $(CUTFLOWS), lib$(CF).so)

TOOLS   = HelperFunctions PluginManager HistogramManager ConfigManager
SRCS    = INtupleWrapper.cxx ICutFlow.cxx $(TOOLS:=.cxx) 
OBJS    = ${SRCS:.cxx=.o}

EXE     = runMAMbo


.SUFFIXES:
.SUFFIXES: .o .cxx .C

.cxx.o:
	$(CC) $(CFLAGS) -c $<


all: $(EXE) $(SOLIB) $(LIB) plugins


$(SOLIB): $(OBJS)
	$(LD) $(DEBUG) $(SOFLAGS) $(OBJS) -o $@


$(EXE): $(EXE).o $(SOLIB)
	$(LD) $(CFLAGS) $(LIBS) -L. -l$(PROJECT) $(EXE).o -o $@

CutFlow%.o: CutFlow%.cxx
	$(LD) $(DEBUG) $(SOFLAGS) -c $<

libCutFlow%.so: CutFlow%.o
	@ echo Compiling library $@
	$(LD) $(SOFLAGS) -Wl,-export-dynamic,$@ $< -ldl -o $@


NtupleWrapper%.o: NtupleWrapper%.cxx
	$(LD) $(DEBUG) $(SOFLAGS) -c $<

# $(patsubst NtupleWrapper,PIPPO,$<)
libNtupleWrapper%.so: NtupleWrapper%.o %.o
	$(LD) $(SOFLAGS) -Wl,-export-dynamic,$@ $< $(subst NtupleWrapper,,$<)  -ldl -o $@


libcutflows: $(foreach CF, $(CUTFLOWS), libCutFlow$(CF).so)

# $(foreach NTUPLE, $(NTUPLES), $(NTUPLE).o)
libntuplewrappers: $(foreach NTUPLE, $(NTUPLES), libNtupleWrapper$(NTUPLE).so)

plugins: libcutflows libntuplewrappers

clean:
	rm -rf *.o *.so $(EXE) 
