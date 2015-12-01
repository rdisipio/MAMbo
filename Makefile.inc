PROJECT = MAMbo
EXE     = run$(PROJECT)

ifndef MAMBODIR
MAMBODIR = $(PWD)
endif

CC = g++
LD = g++
CFLAGS      += -fPIC -std=c++11 -I$(MAMBODIR)
DEBUGFLAGS   = -O0 -D_DEBUG_ -g
RELEASEFLAGS = -O2 -D_RELEASE_

# release or debug?
debug:   CC += $(DEBUGFLAGS)
debug:   LD += $(DEBUGFLAGS)
debug:   MSG = Add debug symbols
release: CC += $(RELEASEFLAGS)
release: LD += $(RELEASEFLAGS)
release: MSG = Level-3 optimization

ROOTCFLAGS    = $(shell root-config --cflags)
XMLCFLAGS     = $(shell xml2-config --cflags)
###JK ROOTCFLAGS    = $(shell root-config --cflags) -I$(MAMBODIR)/../BootstrapGenerator/

CFLAGS += $(ROOTCFLAGS) $(XMLCFLAGS)

SOFLAGS = -fPIC -shared $(ROOTCFLAGS) $(XMLCFLAGS)

ROOTLIBS    = $(shell root-config --libs) 
XMLLIBS     = $(shell xml2-config --libs)

# finally
LIBS = $(ROOTLIBS) $(XMLLIBS)
###JK LIBS = $(ROOTLIBS) $(XMLLIBS) -L$(MAMBODIR)/../BootstrapGenerator/StandAlone/ -lBootstrapGenerator

# compile directives

.SUFFIXES:
.SUFFIXES: .o .cxx .C

.cxx.o:
	$(CC) $(CFLAGS) -c $<
ARCH=x86_64-slc6-gcc47-opt
ifdef MAMBO_USE_ANALYSISTOP
CFLAGS += -D__MOMA__
ARCH=$(ROOTCORECONFIG)
include $(MAMBODIR)/MoMA/Makefile.rootcore.inc 


CFLAGS += -I$(MAMBODIR)/MoMA
LIBS   += -L$(MAMBODIR)/MoMA/lib -lMoMA
endif

###JK CFLAGS += -I$(MAMBODIR)/../BootstrapGenerator/
###JK LIBS   += -L$(MAMBODIR)/../BootstrapGenerator/StandAlone/ -lBootstrapGenerator


## Use xAOD format?
#ifeq ($(shell $(MAMBODIR)/share/use_xAOD.sh),"USE_XAOD")
ifdef MAMBO_USE_XAOD
CFLAGS += -D_USE_XAOD_

ARCH=x86_64-slc6-gcc48-opt

ROOTCOREINCS = -I$(ROOTCOREDIR)/include
ROOTCORELIBS = $(ROOTCOREDIR)/lib/$(ARCH)
XAODLIBS  = Base BTaggingEfficiency BTagging CaloEvent Core Egamma EventFormat EventInfo EventShape Jet 
XAODLIBS += MissingET Muon PFlow RootAccess Tau Tracking Trigger Truth

CFLAGS  += $(ROOTCOREINCS)
SOFLAGS += -L$(ROOTCORELIBS) 
SOFLAGS += $(foreach tool,$(XAODLIBS),-lxAOD$(tool))
SOFLAGS += $(foreach tool,$(XAODLIBS),-lxAOD$(tool)_Reflex)
SOFLAGS += -lxAODPrimitives -lxAODRootAccessInterfaces
endif

ifdef FASTJETLOCATION
CFLAGS += -D__USE_FASTJET__
FASTJETCFLAGS = $(shell fastjet-config --cxxflags)
FASTJETLIBS = $(shell fastjet-config --libs)
CFLAGS  += $(FASTJETCFLAGS)
SOFLAGS += $(FASTJETCFLAGS)
LIBS    += $(FASTJETLIBS)
endif

ifdef LHAPATH
CFLAGS += -D__USE_LHAPDF__
LHAPDFCFLAGS = $(shell lhapdf-config --cppflags)
LHAPDFLIBS   = $(shell lhapdf-config --ldflags)
CFLAGS += $(LHAPDFCFLAGS)
SOFLAGS += $(LHAPDFLIBS)
LIBS    += $(LHAPDFLIBS)
endif
