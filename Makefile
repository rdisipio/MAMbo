MKDIR=mkdir
CP=cp
CCADMIN=CCadmin

DIRS = src Ntuples CutFlows

all: install 

core:
	@$(MAKE) $(MFLAGS) -C src 

ntuples:
	@$(MAKE) $(MFLAGS) -C Ntuples

cutflows:
	@$(MAKE) $(MFLAGS) -C CutFlows

hfillers:
	@$(MAKE) $(MFLAGS) -C HistogramFillers


install: core hfillers ntuples cutflows environment 
	@ln -sf $(PWD)/src/libMAMbo.so   ./lib/
	@ln -sf $(PWD)/Ntuples/*.so      ./lib/
	@ln -sf $(PWD)/CutFlows/*.so     ./lib/
	@ln -sf $(PWD)/share/control/    ./run/
	@ln -sf $(PWD)/src/$(EXE)        ./bin/
	@ln -sf $(PWD)/HistogramFillers/*.so	 ./lib/

environment: ./bin/MAMbo-setenv.sh.template
	@sed "s!@PREFIX@!$(PWD)!g" $(PWD)/bin/MAMbo-setenv.sh.template  > $(PWD)/bin/MAMbo-setenv.sh
	@ln -sf $(PWD)/bin/MAMbo-setenv.sh $(PWD)/run/MAMbo-setenv.sh
	@ln -sf $(PWD)/bin/MAMbo-submit.sh $(PWD)/run/MAMbo-submit.sh

clean:
	@cd src      ; $(MAKE) $(MFLAGS) clean
	@cd Ntuples  ; $(MAKE) $(MFLAGS) clean
	@cd CutFlows ; $(MAKE) $(MFLAGS) clean
	@cd HistogramFillers ; $(MAKE) $(MFLAGS) clean

force_look:
	@true

# run tests
build-tests: 
	@$(MAKE) $(MFLAGS) -C tests 
		
# run tests
test: 
	@$(MAKE) $(MFLAGS) -C tests 
	
include Makefile.inc
