# G++ is for the GCC compiler for C++
PP := g++


# CFLAGS are the compiler flages for when we compile C code in this course 
FLAGS := -O0 -g -Wall -Wextra -Wconversion -Wshadow -pedantic -Werror -lm
CXXFLAGS := -m64 -std=c++11 -Weffc++ $(FLAGS)
SDLFLAGS := `sdl2-config --cflags --libs`

# Variables for Folders
main := .
CLASSES := $(main)/classes
PROG := $(main)/programs
OBJECTS := $(main)/objects
EXE := $(main)/executables


# Rotations
# Command: make main
Objs :=  $(OBJECTS)/main.o $(OBJECTS)/window.o $(OBJECTS)/spaceship.o

main: $(Objs)
	$(PP) $(CXXFLAGS) -o $(EXE)/main $(Objs) -lSDL2 -lSDL2_image
	$(EXE)/./main

$(OBJECTS)/main.o: $(PROG)/main.cpp $(CLASSES)/spaceship.h $(CLASSES)/window.h
	$(PP) $(CXXFLAGS) $(SDLFLAGS) -c $(PROG)/main.cpp -o $@

$(OBJECTS)/window.o: $(PROG)/window.cpp $(CLASSES)/window.h
	$(PP) $(CXXFLAGS) $(SDLFLAGS) -c $(PROG)/window.cpp -o $@
    
$(OBJECTS)/spaceship.o: $(PROG)/spaceship.cpp $(CLASSES)/spaceship.h $(CLASSES)/window.h
	$(PP) $(CXXFLAGS) $(SDLFLAGS) -c $(PROG)/spaceship.cpp -o $@
    
#Make all
all: main

# Make clean
clean:
	rm -rf $(OBJECTS)/* $(EXE)/* 

