#include $(MAMBODIR)/Makefile.inc
include Makefile_MoMA.inc

CFLAGS += -I$(MAMBODIR)/src

TOOLS = MoMA
SRCS = $(TOOLS:=.cxx)
OBJS = ${SRCS:.cxx=.o}

all: $(MOMA_SOLIB) install


$(MOMA_SOLIB): $(OBJS)
	@echo Linking shared library
	$(LD) $(DEBUG) $(SOFLAGS) $(ROOTCORELDFLAGS) $(OBJS) -o lib/$@

install: $(MOMA_SOLIB)
	$(info ATLAS RootCore installed in $(ROOTCOREDIR) )
	$(info MAMbo installed in $(MAMBODIR) )
	@echo
	@ln -sf $(PWD)/lib/$(MOMA_SOLIB) $(MAMBODIR)/lib/.
	$(info $(MOMA_SOLIB) installed in $(MAMBODIR)/lib )

clean:
	@rm -rf *.o *.so
#	@cd src ; $(MAKE) $(MFLAGS) clean
	@rm -f $(MAMBODIR)/lib/$(MOMA_SOLIB)
	@rm -f lib/$(MOMA_SOLIB)

force_look:
	@true
