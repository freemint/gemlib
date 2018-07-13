#
# Makefile for gemma, a minimal GEM library
#
TARGET = test.app

SHELL = /bin/sh
SUBDIRS = 

srcdir = .
top_srcdir = ../..
subdir = src

default: all

include $(top_srcdir)/CONFIGVARS
include $(top_srcdir)/RULES
include $(top_srcdir)/PHONY

CFLAGS += -Wno-inline

all-here: $(TARGET)

# default overwrites
INCLUDES += -I../include/
GENERAL = 

# default definitions
OBJS =  $(SOBJS:.S=.o) $(COBJS:.c=.o)
LDFLAGS = -nostartfiles -nostdlib -L../libgemma/
LIBS = -lgemma -lgcc
GENFILES = $(TARGET)


$(TARGET): $(OBJS)
	$(AM_V_CCLD)$(CC) -o $@ $(CFLAGS) $(LDFLAGS) $(OBJS) $(LIBS)
	$(AM_V_STRIP)$(STRIP) $@


include $(top_srcdir)/DEPENDENCIES
