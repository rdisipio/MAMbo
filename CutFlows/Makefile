include ../Makefile.inc

# modify the following line CUTFLOWS = ... according to your needs
# to add more ntuples, lauch bin/
CUTFLOWS  = TTbarResolved
#CUTFLOWS      = TTHTo2LeptonsSS
#CUTFLOWS     = BoostedSL FakeRateZjet FakeRateZel FakeRateZfjet

# do not change what follows unless you know what you're doing

CUTFLOWSSRCS = $(foreach CF, $(CUTFLOWS), CutFlow$(CF).cxx)
CUTFLOWLIBS  = $(foreach CF, $(CUTFLOWS), lib$(CF).so)

all: $(foreach CF, $(CUTFLOWS), libCutFlow$(CF).so)

CutFlow%.o: CutFlow%.cxx
	$(LD) $(DEBUG) $(SOFLAGS) -I../src -c $<

libCutFlow%.so: CutFlow%.o
	@ echo Compiling library $@
	$(LD) $(SOFLAGS) -Wl,-export-dynamic $< -ldl -o $@

clean:
	rm -rf *.o *.so  
