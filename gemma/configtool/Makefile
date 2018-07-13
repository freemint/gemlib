#
# Makefile for gemma, a minimal GEM library
#

SHELL = /bin/sh
SUBDIRS = 

srcdir = .
top_srcdir = ../..
subdir = configtool

default: all

include $(top_srcdir)/CONFIGVARS
include $(top_srcdir)/RULES
include $(top_srcdir)/PHONY

CFLAGS += -Wno-inline

all-here: apps

# default definitions
GENFILES = .lib* gemma*.app

ALL_APPS = normal

ifeq ($(WITH_020_LIB),yes)
ALL_APPS += normal020
endif

ifeq ($(WITH_V4E_LIB),yes)
ALL_APPS += normalv4e
endif

apps: $(ALL_APPS)

normal:
	$(MAKE) gemma.app TARGET=""

normal020:
	$(MAKE) gemma020.app TARGET="020"

normalv4e:
	$(MAKE) gemmav4e.app TARGET="v4e"


gemma$(TARGET).app: objs
	$(AM_V_at)rm -f $@
	$(AM_V_at)cp .lib$(TARGET)/gemma.app $@

objs: .lib$(TARGET)
	cd .lib$(TARGET); $(MAKE)
.PHONY: objs

.lib$(TARGET): Makefile.objs
	$(AM_V_at)$(MKDIR) -p $@
	$(AM_V_at)$(CP) Makefile.objs $@/Makefile

clean::
	rm -rf .lib* gemma*.app

include $(top_srcdir)/DEPENDENCIES
