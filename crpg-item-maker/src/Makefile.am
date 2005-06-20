bin_PROGRAMS = crpg_item_maker

AM_CXXFLAGS = `pkg-config gtkmm-2.4 --cflags`
crpg_item_maker_LDFLAGS =  `pkg-config gtkmm-2.4 --libs` -lxml2

crpg_item_maker_SOURCES = main.cpp \
			  mainwindow.cpp mainwindow.h \
			  numericentry.h \
			  wizard.cpp wizard.h

CLEANFILES = *~ *.o
