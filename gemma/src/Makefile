#
# Makefile for gemma, a minimal GEM library
#
TARGET = gemma32.slb

SHELL = /bin/sh
SUBDIRS = 

srcdir = .
top_srcdir = ../..
subdir = src

default: all

include $(top_srcdir)/CONFIGVARS
include $(top_srcdir)/RULES
include $(top_srcdir)/PHONY

all-here: $(TARGET)

# default overwrites
INCLUDES += 
GENERAL += -m68020-60

# default definitions
OBJS =  $(SOBJS:.s=.o) $(COBJS:.c=.o)
LDFLAGS = -nostartfiles -nostdlib
LIBS = -lc -lgcc
GENFILES = $(TARGET)


$(TARGET): $(OBJS)
	$(CC) -o $@ $(CFLAGS) $(LDFLAGS) $(OBJS) $(LIBS)
	$(STRIP) $@


include $(top_srcdir)/DEPENDENCIES
