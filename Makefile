#
# Makefile for lib module
#

SHELL = /bin/sh
ifndef BUILDLIB
SUBDIRS = gemlib cflib gemma
else
SUBDIRS = $(BUILDLIB)
include $(BUILDLIB)/VERSION
endif

srcdir = .
top_srcdir = .
subdir = 
top_builddir = .

default: all

include $(top_srcdir)/CONFIGVARS
include $(top_srcdir)/RULES
include $(top_srcdir)/PHONY

all-here: 

dist-gemlib:
	$(MAKE) dist BUILDLIB=gemlib

dist-cflib:
	$(MAKE) dist BUILDLIB=cflib

dist-gemma:
	$(MAKE) dist BUILDLIB=gemma

dist: distdir
	-chmod -R a+r $(distdir) 
	GZIP=$(GZIP) $(TAR) chzf $(distdir).tar.gz $(distdir)
	-rm -rf $(distdir)


# default overwrites

# default definitions
