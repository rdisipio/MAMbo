include ../Makefile.inc

# modify the following line HFILLERS = ... according to your needs
# to add more ntuples, lauch bin/MAMbo-HistogramFillersWizard.py [params]
HFILLERS   = FinalStateObjects


# do not change what follows unless you know what you're doing

HFSRC = $(foreach HF, $(HFILLERS), HF$(HF).cxx)
HFOBJ = $(HFSRC:.cxx=.o)

HF%.o: HF%.cxx
	@echo Compiling histogram filler $<
	$(LD) $(DEBUG) $(SOFLAGS) -I${MAMBODIR}/src -c $<	


all: libHistogramFillers

libHistogramFillers: $(HFOBJ)
	@echo
	@echo Creating histogram fillers library $@
	@echo
	@ar rv $@.a $?
	@ranlib $@.a
	$(LD) $(SOFLAGS) -Wl,-export-dynamic $< -ldl -o $@.so

clean:
	rm -rf *.o *.a *.so 
