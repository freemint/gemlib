#
# Makefile for gemma, a minimal GEM library
#

SHELL = /bin/sh
SUBDIRS = documentation libgemma libslb src

srcdir = .
top_srcdir = ..
subdir = gemma

default: all

include $(top_srcdir)/CONFIGVARS
include $(top_srcdir)/RULES
include $(top_srcdir)/PHONY

all-here: 

# default overwrites

# default definitions


install:
	install -m 644 include/gemma/struct.h ${PREFIX}/include/gemma
	install -m 644 include/gemma/gemma.h ${PREFIX}/include/gemma
	install -m 644 libgemma/libgemma.a ${PREFIX}/lib
	install -m 644 libgemma/libgemma020.a ${PREFIX}/lib/m68020-60

uninstall:
	rm -f ${PREFIX}/include/gemma/struct.h
	rm -f ${PREFIX}/include/gemma/gemma.h
	rm -f ${PREFIX}/lib/libgemma.a
	rm -f ${PREFIX}/lib/m68020-60/libgemma020.a

