include $(MAMBODIR)/Makefile.inc

MKDIR=mkdir
CP=cp
CCADMIN=CCadmin

DIRS = src Ntuples CutFlows

all: install 

core:
	@$(MAKE) $(MFLAGS) -C src 
	@ln -sf $(PWD)/src/libMAMbo.so   ./lib/
	@ln -sf $(PWD)/src/$(EXE)        ./bin/

ntuples:
	@$(MAKE) $(MFLAGS) -C Ntuples
	@ln -sf $(PWD)/Ntuples/*.so      ./lib/

cutflows:
	@$(MAKE) $(MFLAGS) -C CutFlows
	@ln -sf $(PWD)/CutFlows/*.so ./lib/

hfillers:
	@$(MAKE) $(MFLAGS) -C HistogramFillers
	@ln -sf $(PWD)/HistogramFillers/*.so	 ./lib/

moma:
	@if  [ -z "$(ROOTCOREDIR)" ]; then echo "ATLAS ROOTCORE not found" ; exit 0 ; \
	else echo "ATLAS ROOTCORE installed in $(ROOTCOREDIR)" ; fi
#	else echo "ATLAS ROOTCORE installed in $(ROOTCOREDIR)" ; $(MAKE) $(MFLAGS) -C MoMA ; fi

environment: ./bin/MAMbo-setenv.sh.template
	@sed "s!@PREFIX@!$(PWD)!g" $(PWD)/bin/MAMbo-setenv.sh.template  > $(PWD)/bin/MAMbo-setenv.sh
	@ln -sf $(PWD)/bin/MAMbo-setenv.sh $(PWD)/run/MAMbo-setenv.sh
	@ln -sf $(PWD)/bin/MAMbo-submit.sh $(PWD)/run/MAMbo-submit.sh


install: moma core hfillers ntuples cutflows environment
	@ln -sf $(PWD)/share/control/    ./run/


clean:
	@cd src      ; $(MAKE) $(MFLAGS) clean
	@cd Ntuples  ; $(MAKE) $(MFLAGS) clean
	@cd CutFlows ; $(MAKE) $(MFLAGS) clean
	@cd HistogramFillers ; $(MAKE) $(MFLAGS) clean
#	@cd MoMA     ; $(MAKE) $(MFLAGS) clean

force_look:
	@true

# run tests
build-tests: 
	@$(MAKE) $(MFLAGS) -C tests 
		
# run tests
test: 
	@$(MAKE) $(MFLAGS) -C tests 
	
#include Makefile.inc
