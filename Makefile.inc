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
EXE     = run$(PROJECT)

.SUFFIXES:
.SUFFIXES: .o .cxx .C

.cxx.o:
	$(CC) $(CFLAGS) -c $<
