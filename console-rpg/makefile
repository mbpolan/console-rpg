# CRPG source makefile
# This file should be able to
# compile on most systems 
# 8/03/04 - KanadaKid

CPP = g++
OFLAG = -o
.SUFFIXES : .o .cpp
.cpp.o :
	$(CPP) $(CPPGLAGS) -c $<

all: \
	crpg \
	player \
	movement \
	
test: all
	crpg
	player
	movement

crpg: crpg.o
	$(CPP) $(OFLAG)crpg crpg.o

crpg.o : crpg.cpp

player: player.o
	$(CPP) $(OFLAG)player player.o

player.o : player.cpp

movement: movement.o
	$(CPP) $(OFLAG)movement movement.o

movement.o : movement.cpp

clean: 
	rm -rf *.o
