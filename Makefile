#
# Makefile for lib module
#

SHELL = /bin/sh
SUBDIRS = gemlib \
		cflib gemma

srcdir = .
top_srcdir = .
subdir = 

default: all

include $(top_srcdir)/CONFIGVARS
include $(top_srcdir)/RULES
include $(top_srcdir)/PHONY

all-here: 

# default overwrites

# default definitions
