#
# Makefile for gemma demo program
#
TARGET = przyklad.app

SHELL = /bin/sh
SUBDIRS = 

srcdir = .
top_srcdir = ../..
subdir = usage

default: all

include $(top_srcdir)/CONFIGVARS
include $(top_srcdir)/RULES
include $(top_srcdir)/PHONY

all-here: $(TARGET)

# default overwrites
INCLUDES += -I../src
GENERAL = -mshort

# default definitions
OBJS = $(SOBJS:.S=.o) $(COBJS:.c=.o)
LIBS = -L../libgemma -lgemma -L../libslb -lslb -lgcc
LDFLAGS= -nostartfiles -nostdlib
GENFILES = $(TARGET)


$(TARGET): $(OBJS) gemma.slb ../libgemma/libgemma.a ../libslb/libslb.a
	$(CC) -o $@ $(CFLAGS) $(LDFLAGS) $(OBJS) $(LIBS)

gemma.slb: ../src/gemma.slb
	cp $< $@


include $(top_srcdir)/DEPENDENCIES
