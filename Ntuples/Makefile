include ../Makefile.inc

# modify the following line NTUPLES = ... according to your needs
# to add more ntuples, lauch bin/MAMbo-NtupleWrapperWizard.py -t treeName -w outputWrapperName FILE.root
#NTUPLES   = HWWtth
NTUPLES   = TopMiniSLResolved TopMiniSLResolvedParticles TopMiniSLBoosted LHEF

# specify special dependency here. The pattern is DEPS_[NTUPLE] = list of objects
DEPS_TopMiniSLResolved := TopMiniSLResolvedParticles.o TopMiniSLResolvedPartons.o

# do not change what follows unless you know what you're doing

NTUPLESRC = $(foreach NTUPLE, $(NTUPLES), NtupleWrapper$(NTUPLE).cxx)
NTUPLEOBJ = $(NTUPLESRC:.cxx=.o)
NTUPLELIB = $(foreach NTUPLE, $(NTUPLES), libNtupleWrapper$(NTUPLE).so )

all: $(foreach NTUPLE, $(NTUPLES), libNtupleWrapper$(NTUPLE).so)
debug:   all
release: all

NtupleWrapper%.o: NtupleWrapper%.cxx
	@echo Compiling wrapper $<
	$(CC) $(DEBUG) $(CFLAGS) -I${MAMBODIR}/src -I${MAMBODIR}/EventDumpers -c $<
	@echo


clean:
	@rm -rf *.o *.so 


.SECONDEXPANSION:

libNtupleWrapper%.so: NtupleWrapper%.o %.o $$(DEPS_$$*)
	@echo
	@echo Creating ntuple wrapper library $@ from $<
	$(LD) $(SOFLAGS) -Wl,-export-dynamic $< $(DEPS_$(subst .so,,$(subst libNtupleWrapper,,$@))) $(subst NtupleWrapper,,$<) -ldl -o $@
	@echo

# for the record:
# $(DEPS_$(subst .so,,$(subst libNtupleWrapper,,$@)))



