include ../Makefile.inc

# modify the following line HFILLERS = ... according to your needs
# to add more ntuples, lauch bin/MAMbo-HistogramFillersWizard.py [name]
HFILLERS   = FinalStateObjects


# do not change what follows unless you know what you're doing

HFSRC = $(foreach HF, $(HFILLERS), HistogramFiller$(HF).cxx)
HFOBJ = $(HFSRC:.cxx=.o)

HistogramFiller%.o: HistogramFiller%.cxx
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
