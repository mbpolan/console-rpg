# CRPG source makefile
# This file should be able to
# compile on most systems 
# 8/13/04 - KanadaKid

# variables and other info
###########################
# GCC/G++ Compilers (Linux)
###########################
CPP = g++
OFLAG = -o
CFLAG = -c
EXT = 
OSUFFIX = .o
CPPFLAGS = -D__LINUX__ -DDEBUG #for debugging
#CPPFLAGS = -D__LINUX__
LINKFLAGS = -lxml2
DEL = rm -f

#########################
# Dev-Cpp (G++) (Windows)
#########################
#CPP = g++.exe
#OFLAG = -o
#CFLAG = -c
#EXT = .exe
#OSUFFIX = .obj
#CPPFLAGS = -D__WINDOWS__ -DDEBUG #for debugging
#CPPFLAGS = -D__WINDOWS__
#LINKFLAGS = -lxml2
#DEL = rm
#
############################
# end compiler specific part
############################

.SUFFIXES : $(OSUFFIX) .cpp
.cpp$(OSUFFIX) :
	$(CPP) $(CPPFLAGS) $(OFLAG) $<

# compile this
all: \
	crpg

# object files
crpg: crpg$(OSUFFIX) battlesystem$(OSUFFIX) enemy$(OSUFFIX) items$(OSUFFIX) map$(OSUFFIX) npc$(OSUFFIX) player$(OSUFFIX) movement$(OSUFFIX) utilities$(OSUFFIX)
	$(CPP) crpg$(OSUFFIX) battlesystem$(OSUFFIX) enemy$(OSUFFIX) items$(OSUFFIX) map$(OSUFFIX) npc$(OSUFFIX) player$(OSUFFIX) movement$(OSUFFIX) utilities$(OSUFFIX) $(LINKFLAGS) $(OFLAG) crpg$(EXT)

crpg$(OSUFFIX): crpg.cpp definitions.h
	$(CPP) $(CPPFLAGS) $(CFLAG) crpg.cpp $(OFLAG) crpg$(OSUFFIX)

battlesystem$(OSUFFIX): battlesystem.cpp battlesystem.h
	$(CPP) $(CPPFLAGS) $(CFLAG) battlesystem.cpp $(OFLAG) battlesystem$(OSUFFIX)

enemy$(OSUFFIX): enemy.cpp enemy.h creature.h
	$(CPP) $(CPPFLAGS) $(CFLAG) enemy.cpp $(OFLAG) enemy$(OSUFFIX)

items$(OSUFFIX): items.cpp items.h
	$(CPP) $(CPPFLAGS) $(CFLAG) items.cpp $(OFLAG) items$(OSUFFIX)

map$(OSUFFIX): map.cpp map.h items.h
	$(CPP) $(CPPFLAGS) $(CFLAG) map.cpp $(OFLAG) map$(OSUFFIX)

npc$(OSUFFIX): npc.cpp npc.h creature.h
	$(CPP) $(CPPFLAGS) $(CFLAG) npc.cpp $(OFLAG) npc$(OSUFFIX)

player$(OSUFFIX): player.cpp player.h items.h creature.h
	$(CPP) $(CPPFLAGS) $(CFLAG) player.cpp $(OFLAG) player$(OSUFFIX)

movement$(OSUFFIX): movement.cpp movement.h map.h
	$(CPP) $(CPPFLAGS) $(CFLAG) movement.cpp $(OFLAG) movement$(OSUFFIX)

utilities$(OSUFFIX): utilities.cpp utilities.h player.h
	$(CPP) $(CPPFLAGS) $(CFLAG) utilities.cpp $(OFLAG) utilities$(OSUFFIX)

# clean the directory
clean: 
	$(DEL) *$(OSUFFIX)
	$(DEL) crpg$(EXT)
