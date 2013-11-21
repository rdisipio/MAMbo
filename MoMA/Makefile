include Makefile_MoMA.inc

DIRS = src

all: checkenv install

checkenv:
ifndef MAMBODIR
@$(error MAMbo not set)
endif

ifndef ROOTCOREDIR
@$(error ATLAS RootCore not set)
endif

install:
	$(info MAMbo installed in $(MAMBODIR) )
	$(info ATLAS RootCore installed in $(ROOTCOREDIR) )
	@echo

	@$(MAKE) $(MFLAGS) -C src
	@ln -sf $(PWD)/lib/$(MOMALIB) $(MAMBODIR)/lib/

clean:
	@cd src ; $(MAKE) $(MFLAGS) clean
	@rm -f $(MAMBODIR)/lib/$(MOMA_SOLIB)
	@rm -f lib/$(MOMA_SOLIB)

force_look:
	@true
