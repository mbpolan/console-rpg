# CRPG source makefile
# This file should be able to
# compile on most systems 
# 8/13/04 - KanadaKid

# variables and other info
CPP = g++
OFLAG = -c
OSUFFIX = .o
DEL = rm -f
.SUFFIXES : .o .cpp
.cpp.o :
	$(CPP) $(CPPGLAGS) -c $<

# compile this
all: \
	crpg
	
# test the program
test: all
	crpg

# object files
crpg: crpg.o items.o map.o player.o movement.o
	$(CPP) crpg.o items.o map.o player.o movement.o -o crpg

crpg.o: crpg.cpp definitions.h
	$(CPP) $(OFLAG) crpg.cpp -o crpg.o

items.o: items.cpp items.h
	$(CPP) $(OFLAG) items.cpp -o items.o

map.o: map.cpp map.h items.h
	$(CPP) $(OFLAG) map.cpp -o map.o

player.o: player.cpp player.h items.h creature.h
	$(CPP) $(OFLAG) player.cpp -o player.o

movement.o: movement.cpp movement.h map.h
	$(CPP) $(OFLAG) movement.cpp -o movement.o

# clean the directory
clean: 
	$(DEL) *$(OSUFFIX)
	$(DEL) crpg
