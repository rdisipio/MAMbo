include Makefile_MoMA.inc

TOOLS = MoMA
SRCS = $(TOOLS:=.cxx)
OBJS = ${SRCS:.cxx=.o}

all: $(MOMA_SOLIB) install


$(MOMA_SOLIB): $(OBJS)
	@echo Linking shared library
	@$(LD) $(DEBUG) $(SOFLAGS) $(OBJS) -o ../lib/$@

install:
#	$(info MAMbo installed in $(MAMBODIR) )
#	$(info ATLAS RootCore installed in $(ROOTCOREDIR) )
	@echo

	@ln -sf $(PWD)/lib/$(MOMALIB) $(MAMBODIR)/lib/

clean:
	@cd src ; $(MAKE) $(MFLAGS) clean
	@rm -f $(MAMBODIR)/lib/$(MOMA_SOLIB)
	@rm -f lib/$(MOMA_SOLIB)

force_look:
	@true
