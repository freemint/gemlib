#
# Makefile for lib module
#

SHELL = /bin/sh
ifndef BUILDLIB
SUBDIRS = gemlib cflib gemma
else
SUBDIRS = $(BUILDLIB)
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
	$(MAKE) dist BUILDLIB=gemlib VERSION="0.42.99"

dist-cflib:
	$(MAKE) dist BUILDLIB=cflib VERSION="20"

dist-gemma:
	$(MAKE) dist BUILDLIB=gemma VERSION="dist"

dist: distdir
	-chmod -R a+r $(distdir) 
	GZIP=$(GZIP) $(TAR) chzf $(distdir).tar.gz $(distdir)
	-rm -rf $(distdir)


# default overwrites

# default definitions
