# CRPG source makefile
# This file should be able to
# compile on most systems 
# 8/13/04 - KanadaKid

# variables and other info
CPP = g++
OFLAG = -o
OSUFFIX = .o
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
crpg: crpg.o
	$(CPP) $(OFLAG) crpg crpg.o

crpg.o : crpg.cpp

# clean the directory
clean: 
	rm -f crpg$(OSUFFIX)
	rm -f crpg
