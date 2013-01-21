include Makefile.inc

DIRS = src Ntuples CutFlows

all: install

core:
	@$(MAKE) $(MFLAGS) -C src 

ntuples:
	@$(MAKE) $(MFLAGS) -C Ntuples

cutflows:
	@$(MAKE) $(MFLAGS) -C CutFlows

install: core ntuples cutflows
	@ln -sf $(PWD)/src/libMAMbo.so $(PWD)/lib/
	@ln -sf $(PWD)/Ntuples/*.so $(PWD)/lib/
	@ln -sf $(PWD)/CutFlows/*.so $(PWD)/lib/
	@ln -sf $(PWD)/share/control/ $(PWD)/run/

	@ln -sf $(PWD)/src/$(EXE) $(PWD)/bin/

clean:
	@cd src      ; $(MAKE) $(MFLAGS) clean
	@cd Ntuples  ; $(MAKE) $(MFLAGS) clean
	@cd CutFlows ; $(MAKE) $(MFLAGS) clean

force_look:
	@true