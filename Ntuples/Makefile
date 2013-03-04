include ../Makefile.inc

NTUPLES  = MiniSLBoost MiniML NTUPTOP
NTUPLESRC = $(foreach NTUPLE, $(NTUPLES), NtupleWrapper$(NTUPLE).cxx)
NTUPLEOBJ = $(NTUPLESRC:.cxx=.o)
NTUPLELIB   = $(foreach NTUPLE, $(NTUPLES), libNtupleWrapper$(NTUPLE).so )

all: $(foreach NTUPLE, $(NTUPLES), libNtupleWrapper$(NTUPLE).so)

NtupleWrapper%.o: NtupleWrapper%.cxx
	$(LD) $(DEBUG) $(SOFLAGS) -I../src  -c $<

# $(patsubst NtupleWrapper,PIPPO,$<)
libNtupleWrapper%.so: NtupleWrapper%.o %.o
	$(LD) $(SOFLAGS) -Wl,-export-dynamic,$@ $< $(subst NtupleWrapper,,$<)  -ldl -o $@

clean:
	rm -rf *.o *.so 
