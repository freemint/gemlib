#
# Makefile for gemma, a minimal GEM library
#

SHELL = /bin/sh
SUBDIRS = 

srcdir = .
top_srcdir = ../..
subdir = src

default: all

include $(top_srcdir)/CONFIGVARS
include $(top_srcdir)/RULES
include $(top_srcdir)/PHONY

all-here: libs

# default definitions
GENFILES = .lib* gemma*.slb

ALL_LIBS = normal

ifeq ($(WITH_020_LIB),yes)
ALL_LIBS += normal020
endif

ifeq ($(WITH_V4E_LIB),yes)
ALL_LIBS += normalv4e
endif

libs: $(ALL_LIBS)

normal:
	$(MAKE) gemma32.slb TARGET=""

normal020:
	$(MAKE) gemma32020.slb TARGET="020"

normalv4e:
	$(MAKE) gemma32v4e.slb TARGET="v4e"

gemma32$(TARGET).slb: objs
	$(AM_V_at)rm -f $@
	$(AM_V_at)cp .lib$(TARGET)/gemma32.slb $@

objs: .lib$(TARGET)
	cd .lib$(TARGET); $(MAKE)
.PHONY: objs

.lib$(TARGET): Makefile.objs
	$(AM_V_at)$(MKDIR) -p $@
	$(AM_V_at)$(CP) Makefile.objs $@/Makefile

clean::
	rm -rf .lib* gemma*.slb

include $(top_srcdir)/DEPENDENCIES
