bin_PROGRAMS = crpg2

AM_CXXFLAGS = -D__LINUX__ -llua -llualib -ldl
#AM_CXX_FLAGS = -D__LINUX__ -DDEBUG
crpg2_LDFLAGS =  -lxml2 

crpg2_SOURCES = creature.h \
                crpg.cpp \
		definitions.h \
		enemy.cpp enemy.h \
		event.h \
		events.cpp events.h \
		eventprocessor.cpp eventprocessor.h \
		exception.h \
		game.cpp game.h \
		item.cpp item.h \
		itemmodel.h \
		map.cpp map.h \
		object.h \
		parser.cpp parser.h \
		player.cpp player.h \
		position.h \
		threads.cpp threads.h \
		timer.cpp timer.h \
		utilities.cpp utilities.h

CLEANFILES = *~ *.o
