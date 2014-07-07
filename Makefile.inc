CC=g++
LD=g++
CFLAGS  = -fPIC -g 

#DEBUG = -O3
DEBUG = -g
CFLAGS += $(DEBUG)

ROOTCFLAGS = $(shell root-config --cflags)
XMLCFLAGS  = $(shell xml2-config --cflags)
FASTJETCFLAGS = $(shell fastjet-config --cxxflags)

CFLAGS += $(ROOTCFLAGS) $(XMLCFLAGS) $(FASTJETCFLAGS)

SOFLAGS = -fPIC -shared $(ROOTCFLAGS) $(XMLCFLAGS) $(FASTJETCFLAGS)

ROOTLIBS = $(shell root-config --libs)
XMLLIBS  = $(shell xml2-config --libs)
FASTJETLIBS = $(shell fastjet-config --libs)

LIBS    = $(ROOTLIBS) $(XMLLIBS) $(FASTJETLIBS)

PROJECT = MAMbo
EXE     = run$(PROJECT)

.SUFFIXES:
.SUFFIXES: .o .cxx .C

.cxx.o:
	$(CC) $(CFLAGS) -c $<
