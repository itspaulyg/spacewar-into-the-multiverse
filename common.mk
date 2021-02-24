OUT = bin

SEARCHPATH += src
vpath %.cpp $(SEARCHPATH)
vpath %.h $(SEARCHPATH)

DEPS += defs.h structs.h

_OBJS += draw.o
_OBJS += input.o
_OBJS += main.o
<<<<<<< HEAD
=======
_OBJS += util.o
>>>>>>> 6cbea1f703dc8a7b227922723a0ea436844c5ce4
_OBJS += space.o window.o

OBJS = $(patsubst %,$(OUT)/%,$(_OBJS))

# top-level rule to create the program.
all: $(PROG)

# compiling other source files.
$(OUT)/%.o: %.cpp %.h $(DEPS)
	@mkdir -p $(OUT)
	$(PP) $(CFLAGS) $(CXXFLAGS) -c -o $@ $<

# cleaning everything that can be automatically recreated with "make".
clean:
	$(RM) -rf $(OUT) $(PROG)
