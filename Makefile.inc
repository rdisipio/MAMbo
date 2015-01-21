PROJECT = MAMbo
EXE     = run$(PROJECT)

ifndef MAMBODIR
MAMBODIR = $(PWD)
endif

CC = g++
LD = g++
CFLAGS       = -fPIC -std=c++11 -I$(MAMBODIR)
DEBUGFLAGS   = -O0 -D_DEBUG_ -g
RELEASEFLAGS = -O2 -D_RELEASE_

# fix this
ARCH=x86_64-slc6-gcc47-opt

# release or debug?
debug:   CC += $(DEBUGFLAGS)
debug:   LD += $(DEBUGFLAGS)
debug:   MSG = Add debug symbols
release: CC += $(RELEASEFLAGS)
release: LD += $(RELEASEFLAGS)
release: MSG = Level-3 optimization

ROOTCFLAGS    = $(shell root-config --cflags)
XMLCFLAGS     = $(shell xml2-config --cflags)

CFLAGS += $(ROOTCFLAGS) $(XMLCFLAGS)

SOFLAGS = -fPIC -shared $(ROOTCFLAGS) $(XMLCFLAGS)

ROOTLIBS    = $(shell root-config --libs) 
XMLLIBS     = $(shell xml2-config --libs)

# finally
LIBS = $(ROOTLIBS) $(XMLLIBS)

# compile directives

.SUFFIXES:
.SUFFIXES: .o .cxx .C

.cxx.o:
	$(CC) $(CFLAGS) -c $<

ifdef ROOTCOREDIR
CFLAGS += -D__MOMA__
include $(MAMBODIR)/MoMA/Makefile.rootcore.inc
CFLAGS += -I$(MAMBODIR)/MoMA
LIBS   += -L$(MAMBODIR)/MoMA/lib -lMoMA
endif


ifdef FASTJETLOCATION
CFLAGS += -D__USE_FASTJET__
FASTJETCFLAGS = $(shell fastjet-config --cxxflags)
FASTJETLIBS = $(shell fastjet-config --libs)
CFLAGS  += $(FASTJETCFLAGS)
SOFLAGS += $(FASTJETCFLAGS)
LIBS    += $(FASTJETLIBS)
endif
