#
# Makefile for cflib demo program
#
TARGET = demo.app

SHELL = /bin/sh
SUBDIRS = 

srcdir = .
top_srcdir = ../..
subdir = demo

default: all

include $(top_srcdir)/CONFIGVARS
include $(top_srcdir)/RULES
include $(top_srcdir)/PHONY

all-here: $(TARGET)

# default overwrites
INCLUDES += -I..

# default definitions
OBJS = $(COBJS:.c=.o) $(SOBJS:.s=.o)
LIBS += -L.. -lcflib -lgem
GENFILES = $(TARGET)

$(TARGET): $(OBJS) ../libcflib.a
	$(CC) -o $@ $(CFLAGS) $(LDFLAGS) $(OBJS) $(LIBS)


include $(top_srcdir)/DEPENDENCIES
