include ../Makefile.inc

CUTFLOWS     = BoostedSL FakeRateZjet
CUTFLOWSSRCS = $(foreach CF, $(CUTFLOWS), CutFlow$(CF).cxx)
CUTFLOWLIBS  = $(foreach CF, $(CUTFLOWS), lib$(CF).so)

all: $(foreach CF, $(CUTFLOWS), libCutFlow$(CF).so)

CutFlow%.o: CutFlow%.cxx
	$(LD) $(DEBUG) $(SOFLAGS) -I../src -c $<

libCutFlow%.so: CutFlow%.o
	@ echo Compiling library $@
	$(LD) $(SOFLAGS) -Wl,-export-dynamic,$@ $< -ldl -o $@

clean:
	rm -rf *.o *.so  
