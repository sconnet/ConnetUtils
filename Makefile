#*****************************************************************************
#
# Copyright (C) 2001 Steve Connet.  All rights reserved.
#
# Source File Name : makefile
# Author           : Steve Connet
#
# Version          : $Id: $
#
# Revision History : makefile for the ConnetUtils library
#
# $Log: $
#
#*****************************************************************************

SHELL = /bin/sh

TARGET = ConnetUtils

includedir = ../include
libdir = ../lib

STDINCDIR = /usr/local/include
STDLIBDIR = /usr/local/lib

RELEASE = -O2 -W -Wall -Werror -I$(STDINCDIR) -L$(STDLIBDIR)
DEBUG = -g -D_DEBUG_ -Wall -I$(STDINCDIR) -L$(STDLIBDIR)
CFLAGS = $(DEBUG)

OBJS = UUID.o Mutex.o Server.o Config.o misc.o
HDRS = UUID.h Exception.h Singleton.h Mutex.h Server.h Config.h misc.h TriggerQueue.h

# build the target
$(TARGET): $(OBJS)
	@ar -rusv $(TARGET).a $(OBJS)

install: $(TARGET)
	@rm -rfv lib$(TARGET).a;
	@mv -v $(TARGET).a $(libdir)/lib$(TARGET).a;
	@ln -sfv $(libdir)/lib$(TARGET).a;
	@for file in $(HDRS); do \
		cp -v $$file $(includedir); \
	done

release:
	$(MAKE) CFLAGS='$(RELEASE)' $(TARGET)

debug:
	$(MAKE) CFLAGS='$(DEBUG)' $(TARGET)

# build the OBJS
.cpp.o:
	$(CXX) $(CFLAGS) $*.cpp -c -o $@

depend:
	makedepend -Y  -- $(CFLAGS) -- *.cpp

clean: 
	@rm -rfv lib$(TARGET).a;
	@rm -rfv $(libdir)/lib$(TARGET).a;
	@for file in $(OBJS); do \
		rm -rfv $$file; \
	done;

	@for file in $(HDRS); do \
		rm -rfv $(includedir)/$$file; \
	done

# DO NOT DELETE

Config.o: misc.h Config.h
misc.o: misc.h
Mutex.o: misc.h Mutex.h
Server.o: Server.h Exception.h Mutex.h
UUID.o: UUID.h
