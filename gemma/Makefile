#
# Makefile for gemma, a GEM library
#

SHELL = /bin/sh
SUBDIRS = libgemma kernel32 documentation libslb src configtool test

srcdir = .
top_srcdir = ..
subdir = gemma

libdir = ${PREFIX}/lib
slblibdir = ${PREFIX}/../mint/slb
includedir = ${PREFIX}/include
slbincludedir = ${includedir}/slb

default: all

include $(top_srcdir)/CONFIGVARS
include $(top_srcdir)/RULES
include $(top_srcdir)/PHONY
include $(srcdir)/VERSION

all-here: 

# default overwrites

# default definitions


install:
	install -m 755 -d ${libdir}
	install -m 755 -d ${slblibdir}
	install -m 755 -d ${slbincludedir}
	install -m 644 include/slb/gemma.h ${slbincludedir}
	install -m 644 include/slb/gemma-struct.h ${slbincludedir}
	install -m 644 include/slb/kernel.h ${slbincludedir}
	install -m 644 libgemma/libgemma.a ${libdir}
ifeq ($(WITH_020_LIB),yes)
	install -m 755 -d ${libdir}/m68020-60
	install -m 644 libgemma/libgemma020.a ${libdir}/m68020-60/libgemma.a
endif
ifeq ($(WITH_V4E_LIB),yes)
	install -m 755 -d ${libdir}/m5475
	install -m 644 libgemma/libgemmav4e.a ${libdir}/m5475/libgemma.a
endif
	install -m 755 src/gemma32.slb ${slblibdir}
ifeq ($(WITH_V4E_LIB),yes)
	install -m 755 -d ${slblibdir}/m5475
	install -m 755 src/gemma32v4e.slb ${slblibdir}/m5475/gemma32.slb
endif
ifeq ($(WITH_020_LIB),yes)
	install -m 755 -d ${slblibdir}/m68020-60
	install -m 755 src/gemma32020.slb ${slblibdir}/m68020-60/gemma32.slb
endif
	install -m 755 kernel32.slb ${slblibdir}

uninstall:
	rm -f ${slbincludedir}/gemma-struct.h
	rm -f ${slbincludedir}/gemma.h
	rm -f ${slbincludedir}/kernel.h
	rm -f ${libdir}/libgemma.a
	rm -f ${libdir}/m68020-60/libgemma.a
	rm -f ${libdir}/m5475/libgemma.a
	rm -f ${slblibdir}/gemma32.slb
	rm -f ${slblibdir}/m68020-60/gemma32.slb
	rm -f ${slblibdir}/m5475/gemma32.slb
	rm -f ${slblibdir}/kernel32.slb
