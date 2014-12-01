PROJECT = MAMbo
EXE     = run$(PROJECT)

CC=g++
LD=g++
CFLAGS  = -fPIC -std=c++11 -I$(MAMBODIR)

# fix this
ARCH=x86_64-slc6-gcc47-opt

#DEBUG = -O3
DEBUG = -g
CFLAGS += $(DEBUG)

ROOTCFLAGS    = $(shell root-config --cflags)
XMLCFLAGS     = $(shell xml2-config --cflags)
FASTJETCFLAGS = $(shell fastjet-config --cxxflags)

CFLAGS += $(ROOTCFLAGS) $(XMLCFLAGS) $(FASTJETCFLAGS)

SOFLAGS = -fPIC -shared $(ROOTCFLAGS) $(XMLCFLAGS) $(FASTJETCFLAGS)

ROOTLIBS    = $(shell root-config --libs) 
XMLLIBS     = $(shell xml2-config --libs)
FASTJETLIBS = $(shell fastjet-config --libs) 

# finally
LIBS = $(ROOTLIBS) $(XMLLIBS) $(FASTJETLIBS)

ifdef ROOTCOREDIR
CFLAGS += -D__MOMA__
include $(MAMBODIR)/Makefile.rootcore.inc
endif

# compile directives

.SUFFIXES:
.SUFFIXES: .o .cxx .C

.cxx.o:
	$(CC) $(CFLAGS) -c $<
