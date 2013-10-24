include Makefile.inc

DIRS = src Ntuples CutFlows

all: install

core:
	@$(MAKE) $(MFLAGS) -C src 

ntuples:
	@$(MAKE) $(MFLAGS) -C Ntuples

cutflows:
	@$(MAKE) $(MFLAGS) -C CutFlows

install: core ntuples cutflows environment
	@ln -sf $(PWD)/src/libMAMbo.so $(PWD)/lib/
	@ln -sf $(PWD)/Ntuples/*.so $(PWD)/lib/
	@ln -sf $(PWD)/CutFlows/*.so $(PWD)/lib/
	@ln -sf $(PWD)/share/control/ $(PWD)/run/

	@ln -sf $(PWD)/src/$(EXE) $(PWD)/bin/

environment: $(PWD)/bin/MAMbo-setenv.sh.template
	@sed "s!@PREFIX@!$(PWD)!g" $(PWD)/bin/MAMbo-setenv.sh.template  > $(PWD)/bin/MAMbo-setenv.sh
	@ln -sf $(PWD)/bin/MAMbo-setenv.sh $(PWD)/run/MAMbo-setenv.sh

clean:
	@cd src      ; $(MAKE) $(MFLAGS) clean
	@cd Ntuples  ; $(MAKE) $(MFLAGS) clean
	@cd CutFlows ; $(MAKE) $(MFLAGS) clean

force_look:
	@true
