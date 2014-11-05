CC=g++
LD=g++
CFLAGS  = -fPIC -std=c++11 

#DEBUG = -O3
DEBUG = -g
CFLAGS += $(DEBUG)

ROOTCFLAGS = $(shell root-config --cflags)#-pthread -Wno-deprecated-declarations -m64 -I/afs/cern.ch/sw/lcg/app/releases/ROOT/5.34.17/x86_64-slc6-gcc48-dbg/root/include #$(shell root-config --cflags)
XMLCFLAGS  = $(shell xml2-config --cflags)
FASTJETCFLAGS = $(shell fastjet-config --cxxflags) #-I/afs/cern.ch/sw/lcg/external/fastjet/3.0.3/x86_64-slc6-gcc48-opt/include #$(shell fastjet-config --cxxflags)

CFLAGS += $(ROOTCFLAGS) $(XMLCFLAGS) $(FASTJETCFLAGS)

SOFLAGS = -fPIC -shared $(ROOTCFLAGS) $(XMLCFLAGS) $(FASTJETCFLAGS)

ROOTLIBS = $(shell root-config --libs) #-L/afs/cern.ch/sw/lcg/contrib/gcc/4.8.1/x86_64-slc6-gcc48-opt/lib64 -L/afs/cern.ch/sw/lcg/app/releases/ROOT/5.34.17/x86_64-slc6-gcc48-dbg/root/lib -lCore -lCint -lRIO -lNet -lHist -lGraf -lGraf3d -lGpad -lTree -lRint -lPostscript -lMatrix -lPhysics -lMathCore -lThread -pthread -lm -ldl -rdynamic #$(shell root-config --libs)
XMLLIBS  = $(shell xml2-config --libs)
FASTJETLIBS = $(shell fastjet-config --libs) #-Wl,-rpath,/afs/cern.ch/sw/lcg/external/fastjet/3.0.3/x86_64-slc6-gcc48-opt/lib -lm -L/afs/cern.ch/sw/lcg/external/fastjet/3.0.3/x86_64-slc6-gcc48-opt/lib -lfastjettools -lfastjet #$(shell fastjet-config --libs)

LIBS    = $(ROOTLIBS) $(XMLLIBS) $(FASTJETLIBS)

PROJECT = MAMbo
EXE     = run$(PROJECT)

.SUFFIXES:
.SUFFIXES: .o .cxx .C

.cxx.o:
	$(CC) $(CFLAGS) -c $<
