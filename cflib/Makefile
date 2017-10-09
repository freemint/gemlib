#
# Makefile for cflib, a enhanced GEM library
#

SHELL = /bin/sh
SUBDIRS = demo intrface

srcdir = .
top_srcdir = ..
subdir = cflib

default: all

include $(top_srcdir)/CONFIGVARS
include $(top_srcdir)/RULES
include $(top_srcdir)/PHONY
include $(srcdir)/VERSION

all-here: libs

# default overwrites

# default definitions
GENFILES = .lib* libcflib*.a

ALL_LIBS = normal mshort

ifeq ($(WITH_020_LIB),yes)
ALL_LIBS += normal020
endif

ifeq ($(WITH_V4E_LIB),yes)
ALL_LIBS += normalv4e
endif

libs: $(ALL_LIBS)

normal:
	$(MAKE) libcflib.a TARGET=""

mshort:
	$(MAKE) libcflib16.a TARGET="16"
	
normal020:
	$(MAKE) libcflib020.a TARGET="020"

normalv4e:
	$(MAKE) libcflibv4e.a TARGET="v4e"

libcflib$(TARGET).a: objs
	$(RM) $@
	$(AR) rc $@ \
		$(shell for file in `cat .lib$(TARGET)/objs` ; \
			do echo .lib$(TARGET)/$$file ; done)
	$(RANLIB) $@

objs: .lib$(TARGET)
	cd .lib$(TARGET); $(MAKE)

.lib$(TARGET):
	$(MKDIR) $@
	$(CP) Makefile.objs $@/Makefile

cflib.spec: cflib.spec.in VERSION
	rm -f $@
	sed 's,@VERSION@,$(VERSION),g' $@.in >$@

docu: cflib.stg
	$(HCP) -ocflib.hyp cflib.stg

install:
	install -m 755 -d $(PREFIX)/include
	install -m 644 cflib.h        ${PREFIX}/include
	install -m 755 -d $(PREFIX)/lib
	install -m 644 libcflib.a     ${PREFIX}/lib
	install -m 755 -d $(PREFIX)/lib/mshort
	install -m 644 libcflib16.a   ${PREFIX}/lib/mshort/libcflib.a
	ln -sf mshort/libcflib.a	      ${PREFIX}/lib/libcflib16.a
ifeq ($(WITH_020_LIB),yes)
	install -m 755 -d $(PREFIX)/lib/m68020-60
	install -m 644 libcflib020.a  ${PREFIX}/lib/m68020-60/libcflib.a
endif
ifeq ($(WITH_V4E_LIB),yes)
	install -m 755 -d $(PREFIX)/lib/m5475
	install -m 644 libcflibv4e.a  ${PREFIX}/lib/m5475/libcflib.a
endif
	install -m 755 -d $(PREFIX)/lib/stguide
	install -m 644 cflib.hyp      ${PREFIX}/stguide
	install -m 644 cflib.ref      ${PREFIX}/stguide

uninstall:
	rm -f ${PREFIX}/include/cflib.h
	rm -f ${PREFIX}/lib/libcflib.a
	rm -f ${PREFIX}/lib/libcflib16.a
	rm -f ${PREFIX}/lib/mshort/libcflib.a
ifeq ($(WITH_020_LIB),yes)
	rm -f ${PREFIX}/lib/m68020-60/libcflib.a
endif
ifeq ($(WITH_V4E_LIB),yes)
	rm -f ${PREFIX}/lib/m5475/libcflib.a
endif
	rm -f ${PREFIX}/stguide/cflib.hyp
	rm -f ${PREFIX}/stguide/cflib.ref
