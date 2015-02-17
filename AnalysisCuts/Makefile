include ../Makefile.inc

# modify the following line CUTS = ... according to your needs
CUTS  += Dummy PtThreshold

# do not change what follows unless you know what you're doing

CUTSSRCS = $(foreach CUT, $(CUTS), Cut$(CUT).cxx)
CUTOBJS  = ${CUTSSRCS:.cxx=.o}
CUTLIBS  = $(foreach AC, $(CUTS), libAnalysisCut$(AC).so)

#all: libAnalysisCuts.so
all: $(foreach AC, $(CUTS), libAnalysisCut$(AC).so)
debug:   all
release: all

Cut%.o: Cut%.cxx
	$(CC) $(DEBUG) $(CFLAGS) -I../src -c $<

libAnalysisCut%.so: Cut%.o
	@echo Compiling analysis cut library $@
	$(LD) $(SOFLAGS) -Wl,-export-dynamic $< -ldl -o $@

clean:
	rm -rf *.o *.so  
