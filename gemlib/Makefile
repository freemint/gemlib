#
# Makefile for gemlib, the VDI & AES bindings
# gemxlib, bindings for VDI & AES extensions
#

SHELL = /bin/sh
SUBDIRS = 

srcdir = .
top_srcdir = ..
subdir = gemlib

default: all

include $(top_srcdir)/CONFIGVARS
include $(top_srcdir)/RULES
include $(top_srcdir)/PHONY

all-here: libs

# default overwrites

# default definitions
GENFILES = .lib* libgem*.a


libs: normal mshort

normal:
	$(MAKE) libgem.a TARGET=""

mshort:
	$(MAKE) libgem16.a TARGET="16"

libgem$(TARGET).a: objs
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

install:
	install -m 644 -o root -g wheel lib{gem,gem16}.a $(PREFIX)/lib
	install -m 644 -o root -g wheel {gem,gemx}.h $(PREFIX)/include

uninstall:
	rm -f $(PREFIX)/lib/lib{gem,gem16}.a
	rm -f $(PREFIX)/include/{gem,gemx}.h

