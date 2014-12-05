include $(MAMBODIR)/Makefile.inc

ifdef ROOTCOREDIR
CFLAGS += -D__MOMA__
include Makefile.rootcore.inc
endif

MOMA_TAG   = MoMA
MOMA_SOLIB = lib$(MOMA_TAG).so

CFLAGS += -I$(ROOTCOREINCS) -I$(MAMBODIR)/MoMA
LIBS   += $(ROOTCORELDFLAGS)
