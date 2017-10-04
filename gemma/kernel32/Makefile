#
# Makefile for kernel32
#

SHELL = /bin/sh
SUBDIRS = 

srcdir = .
top_srcdir = ../..
subdir = kernel32

default: all

include $(top_srcdir)/CONFIGVARS
include $(top_srcdir)/RULES
include $(top_srcdir)/PHONY

all-here: libs

# default definitions
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
	$(MAKE) kernel32.slb TARGET=""

normal020:
	$(MAKE) kernel32020.slb TARGET="020"

normalv4e:
	$(MAKE) kernel32v4e.slb TARGET="v4e"

kernel32$(TARGET).slb: objs
	$(AM_V_at)rm -f $@
	cp .lib$(TARGET)/kernel32.slb $@

objs: .lib$(TARGET)
	$(AM_V_at)cd .lib$(TARGET); $(MAKE)
.PHONY: objs

.lib$(TARGET): Makefile.objs
	$(AM_v_at)$(MKDIR) -p $@
	$(CP) Makefile.objs $@/Makefile

clean::
	rm -rf .lib* kernel*.slb

include $(top_srcdir)/DEPENDENCIES
