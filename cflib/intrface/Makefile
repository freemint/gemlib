#
# Makefile for cflib intrface helper
#
TARGET = extobfix.prg

SHELL = /bin/sh
SUBDIRS = 

srcdir = .
top_srcdir = ../..
subdir = intrface

default: all

include $(top_srcdir)/CONFIGVARS
include $(top_srcdir)/RULES
include $(top_srcdir)/PHONY

all-here: $(TARGET)

# default overwrites
INCLUDES += -I..
GENERAL = -mshort

# default definitions
OBJS = $(COBJS:.c=.o) $(SOBJS:.s=.o)
LIBS += -L.. -lcflib16 -lgem16
GENFILES = $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $@ $(CFLAGS) $(LDFLAGS) $(OBJS) $(LIBS)
	$(STRIP) $@


include $(top_srcdir)/DEPENDENCIES
