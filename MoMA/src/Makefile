include ../Makefile_MoMA.inc

TOOLS = MoMA
SRCS = $(TOOLS:=.cxx)
OBJS = ${SRCS:.cxx=.o}

all: $(MOMA_SOLIB)

$(MOMA_SOLIB): $(OBJS)
	@echo Linking shared library
	@$(LD) $(DEBUG) $(SOFLAGS) $(OBJS) -o ../lib/$@

clean:
	@rm -rf *.o *.so
