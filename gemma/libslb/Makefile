#
# Makefile for gemma slb loader
#
TARGET = libslb.a

SHELL = /bin/sh
SUBDIRS = 

srcdir = .
top_srcdir = ../..
subdir = libslb

default: all

include $(top_srcdir)/CONFIGVARS
include $(top_srcdir)/RULES
include $(top_srcdir)/PHONY

all-here: $(TARGET)

# default overwrites

# default definitions
OBJS = $(COBJS:.c=.o) $(SOBJS:.s=.o)
GENFILES = $(TARGET)


$(TARGET): $(OBJS)
	$(AM_V_at)$(RM) $@
	$(AM_V_AR)$(AR) r $@ $(OBJS)
	$(AM_V_RANLIB)$(RANLIB) $@


include $(top_srcdir)/DEPENDENCIES
