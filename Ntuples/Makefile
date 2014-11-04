include ../Makefile.inc

# modify the following line NTUPLES = ... according to your needs
# to add more ntuples, lauch bin/MAMbo-NtupleWrapperWizard.py -t treeName -w outputWrapperName FILE.root
#NTUPLES   = HWWtth
NTUPLES   = TopMiniSLResolved TopMiniSLBoosted

# do not change what follows unless you know what you're doing

NTUPLESRC = $(foreach NTUPLE, $(NTUPLES), NtupleWrapper$(NTUPLE).cxx)
NTUPLEOBJ = $(NTUPLESRC:.cxx=.o)
NTUPLELIB = $(foreach NTUPLE, $(NTUPLES), libNtupleWrapper$(NTUPLE).so )

all: $(foreach NTUPLE, $(NTUPLES), libNtupleWrapper$(NTUPLE).so)

NtupleWrapper%.o: NtupleWrapper%.cxx
	$(LD) $(DEBUG) $(SOFLAGS) -I${MAMBODIR}/src -I${MAMBODIR}/EventDumpers -c $<

libNtupleWrapper%.so: NtupleWrapper%.o %.o
	@echo
	@echo Creating ntuple wrapper library $@
	$(LD) $(SOFLAGS) -Wl,-export-dynamic $< $(subst NtupleWrapper,,$<) -ldl -o $@

clean:
	rm -rf *.o *.so 
