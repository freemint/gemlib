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

.PHONY: doc
doc:
	doxygen Doxyfile
# 	udo -s -l -W -y doc/udo/index.u -o doc/stg/gemlib.stg
# 	udo -h -l -W -y doc/udo/index.u -o doc/html/index.htm
	

# makefiles for compiler other than gcc
.PHONY: gcc gcc281 gcc28116 sox all-compilers zip
gcc:
	mkdir -p lib/gcc; make -f gcc.mak

gcc281:
	mkdir -p lib/gcc281; make -f gcc281.mak

gcc28116:
	mkdir -p lib/gcc281; make -f gcc281-16.mak

sox:
	mkdir -p lib/sozobon; make -f sox.mak

zip:
	make -f zip.mak ZIP=zip
	
all-compilers:
	rm -f *.o; mkdir -p lib/sozobon lib/gcc lib/gcc281 include
	make -f sox.mak; rm -f *.o; 
	make -f gcc.mak; rm -f *.o; 
	make -f gcc281.mak; rm -f *.o; 
	make -f gcc281-16.mak; rm -f *.o; 
	cp gem.h gemx.h include; make -f zip.mak

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

