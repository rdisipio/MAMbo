include ../Makefile.inc

# modify the following line EMS = ... according to your needs
EMS  += Dummy

# do not change what follows unless you know what you're doing

EMSSRCS = $(foreach EM, $(EMS), EM$(EM).cxx)
EMOBJS  = ${EMSSRCS:.cxx=.o}

all: $(foreach EM, $(EMS), libEventModifier$(EM).so)
debug:   all
release: all

EM%.o: EM%.cxx
	$(CC) $(DEBUG) $(CFLAGS) -I../src -c $<

libEventModifier%.so: EM%.o
	@echo Compiling Event Modifier $@
	$(LD) $(SOFLAGS) -Wl,-export-dynamic $< -ldl -o $@

clean:
	rm -rf *.o *.so  
