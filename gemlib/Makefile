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
include $(srcdir)/VERSION

all-here: libs

# default overwrites

# default definitions
GENFILES = .lib* libgem*.a
GENFILES += mt_gem.h Doxyfile gemlib.spec
GENFILES += html


libs: normal mshort

normal:
	$(MAKE) libgem.a TARGET=""

mshort:
	$(MAKE) libgem16.a TARGET="16"

.PHONY: doc

ChangeLog:
	cvs log -d "20021201<" . >ChangeLog.tmp
	perl cvs2cl.pl --separate-header --no-wrap --usermap users --stdin --stdout <ChangeLog.tmp >ChangeLog
	rm -f ChangeLog.tmp
	
doc: Doxyfile ChangeLog
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

pc:
	mkdir -p lib/purec; make -f pc.mak

zip:
	make -f zip.mak ZIP=zip
	
all-compilers:
	rm -f *.o; mkdir -p lib/sozobon lib/gcc lib/gcc281 include
	make -f sox.mak; rm -f *.o; 
	make -f gcc.mak; rm -f *.o; 
	make -f gcc281.mak; rm -f *.o; 
	make -f gcc281-16.mak; rm -f *.o; 
	cp gem.h gemx.h mt_gem.h mt_gemx.h include; make -f zip.mak

libgem$(TARGET).a: objs
	$(RM) $@
	$(AR) rc $@ \
		$(shell for file in `cat .lib$(TARGET)/objs` ; \
			do echo .lib$(TARGET)/$$file ; done)
	$(RANLIB) $@

objs: .lib$(TARGET) mt_gem.h
	cd .lib$(TARGET); $(MAKE)

.lib$(TARGET):
	$(MKDIR) $@
	$(CP) Makefile.objs $@/Makefile

gemlib.spec: gemlib.spec.in VERSION
	rm -f $@
	sed 's,@VERSION@,$(VERSION),g' $@.in >$@

Doxyfile: Doxyfile.in VERSION
	rm -f $@
	sed 's,@VERSION@,$(VERSION),g' $@.in >$@

# Special rule for mt_gem.h.  We build that automatically from
# mt_gem.h.in.
# If mt_gem.h would not change we won't replace it because that
# would cause a global rebuild.
mt_gem.h: mt_gem.h.in VERSION
	@echo Updating mt_gem.h ...
	@rm -f $(srcdir)/mt_gem.tmp
	@betatag=`echo $(VERSION) | sed 's,[^A-Za-z]*\.[0-9][0-9]*,,'`; \
	major=`echo $(VERSION) | sed 's,\..*,,'`; \
	minor=`echo $(VERSION) | sed -e "s,^$$major\.,," -e 's,\..*,,' \
		-e 's,[^0-9]*$$,,'`; \
	revision=`echo $(VERSION) | sed -e "s,^$$major\.$$minor\.*,,"  \
		-e "s,$$betatag,,"`; \
	test "$$revision" = "" && revision="0"; \
	betatag=\"$$betatag\"; \
	sed -e "s,@MAJOR@,$$major,g" -e "s,@MINOR@,$$minor,g" \
		-e "s,@REVISION@,$$revision,g" -e "s,@BETATAG@,$$betatag,g" \
		$(srcdir)/mt_gem.h.in >$(srcdir)/mt_gem.tmp \
	|| exit 1;
	mv $(srcdir)/mt_gem.tmp $(srcdir)/mt_gem.h
#	$(MOVEIFCHANGE) $(srcdir)/mt_gem.tmp $(srcdir)/mt_gem.h

install:
	install -m 644 libgem.a $(PREFIX)/lib
	install -m 644 libgem16.a $(PREFIX)/lib
	install -m 644 gem.h $(PREFIX)/include
	install -m 644 gemx.h $(PREFIX)/include
	install -m 644 mt_gem.h $(PREFIX)/include
	install -m 644 mt_gemx.h $(PREFIX)/include

uninstall:
	rm -f $(PREFIX)/lib/libgem.a
	rm -f $(PREFIX)/lib/libgem16.a
	rm -f $(PREFIX)/include/gem.h
	rm -f $(PREFIX)/include/gemx.h
	rm -f $(PREFIX)/include/mt_gem.h
	rm -f $(PREFIX)/include/mt_gemx.h

