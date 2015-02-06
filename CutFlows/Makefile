include ../Makefile.inc

# modify the following line CUTFLOWS = ... according to your needs
# to add more ntuples, lauch bin/
CUTFLOWS  = Dummy TTbarResolved TTbarResolvedParticleLevel
#CUTFLOWS      = TTHTo2LeptonsSS
#CUTFLOWS     = BoostedSL FakeRateZjet FakeRateZel FakeRateZfjet

# do not change what follows unless you know what you're doing

CUTFLOWSSRCS = $(foreach CF, $(CUTFLOWS), CutFlow$(CF).cxx)
CUTFLOWLIBS  = $(foreach CF, $(CUTFLOWS), lib$(CF).so)

all: $(foreach CF, $(CUTFLOWS), libCutFlow$(CF).so)
debug:   all
release: all

CutFlow%.o: CutFlow%.cxx
	$(CC) $(DEBUG) $(CFLAGS) -I../src -c $<

libCutFlow%.so: CutFlow%.o
	@echo Compiling cutflow library $@
	$(LD) $(SOFLAGS) -Wl,-export-dynamic $< -ldl -o $@

clean:
	rm -rf *.o *.so  
