include ../Makefile.inc

# modify the following line NTUPLES = ... according to your needs
# to add more ntuples, lauch bin/MAMbo-NtupleWrapperWizard.py -t treeName -w outputWrapperName FILE.root
NTUPLES   = HWWtth
#NTUPLES  = MiniSLBoost MiniML NTUPTOP HWWtth

# do not change what follows unless you know what you're doing

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
