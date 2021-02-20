# g++ is the GCC compiler for C++
PROG := spacewar
PP := g++

include common.mk

# CFLAGS are the compiler flages for when we compile C code in this course
CXXFLAGS += `sdl2-config --cflags`
CXXFLAGS += -m64 -std=c++11 -Weffc++
CXXFLAGS += -O0 -g -Wall -Wextra -Wconversion -Wshadow -pedantic -Werror -Werror=maybe-uninitialized -Warray-bounds -Wempty-body -lefence

LDFLAGS := `sdl2-config --cflags --libs` -lSDL2_mixer -lSDL2_image -lSDL2_ttf -lSDL2 -lm

# Link program
$(PROG): $(OBJS)
	$(PP) -o $@ $(OBJS) $(LDFLAGS)
