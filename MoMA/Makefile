include ../Makefile.inc

DIRS = src

MOMATAG = MoMA
MOMALIB = lib$(MOMATAG).so

all: checkmambo checkrootcore install

checkmambo:
	ifeq( $MAMBODIR, )
	$(error MAMbo not set)
	endif

checkrootcore:
	ifeq( $ROOTCOREDIR, )
	$(error ATLAS RootCore not set)
	endif

install:
	@$(MAKE) $(MFLAGS) -C src
	@ln -sf $(PWD)/lib/$(MOMALIB) $(MAMBODIR)/lib/

clean:
	@cd src ; $(MAKE) $(MFLAGS) clean
	@rm -f $(MAMBODIR)/lib/$(MOMALIB)
	@rm -f lib/$(MOMALIB)

force_look:
	@true
