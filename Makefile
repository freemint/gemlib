#
# Makefile for gemlib, the VDI & AES bindings
# gemxlib, bindings for VDI & AES extensions
#

SHELL = /bin/sh
SUBDIRS = 
BUILDLIB=gemlib

srcdir = .
top_srcdir = .
subdir = 
top_builddir = .

default: all

include $(top_srcdir)/CONFIGVARS
include $(top_srcdir)/RULES
include $(top_srcdir)/PHONY
include $(srcdir)/VERSION

ALL_LIBS = 68000 68020-60 68000.short 68020-60.short 5475 5475.short
BUILD_FAST=$(shell if $(CC) -mfastcall -E - < /dev/null >/dev/null 2>&1; then echo Y; else echo N; fi)
ifeq ($(BUILD_FAST), Y)
ALL_LIBS += 68000.fastcall 68020-60.fastcall 68000.short.fastcall 68020-60.short.fastcall 5475.fastcall 5475.short.fastcall
endif

all-here: $(addsuffix /libgem.a, $(addprefix .lib, $(ALL_LIBS)))

dist: distdir
	-chmod -R a+r $(distdir) 
	GZIP=$(GZIP) $(TAR) chzf $(distdir).tar.gz $(distdir)
	-rm -rf $(distdir)

# default overwrites

# default definitions
GENFILES = .lib* libgem*.a
GENFILES += mt_gem.h Doxyfile gemlib.spec
GENFILES += html

cpu=$(word 1, $(subst ., ,$(CPU-FPU)))
ifeq ($(cpu),5475)
	CPU=-mcpu=$(cpu)
else
	CPU=-m$(cpu)
endif
FLAVOUR=$(addprefix -m,$(wordlist 2,100, $(subst ., ,$(CPU-FPU))))

define LIB_TEMPLATE
.lib$(1)/libgem.a::
	@test -d .lib$(1) || mkdir .lib$(1)
	$(MAKE) -C .lib$(1) -f ../Makefile CPU-FPU=$(1) top_srcdir=.. srcdir=.. libgem.a
endef
define CC_TEMPLATE
$(1).o: $$(srcdir)/$(1)
	$$(AM_V_CC)$$(CC) $$(CPU) $$(FLAVOUR) $$(CFLAGS) -c -o $$@ $$<
endef

$(foreach DIR,$(ALL_LIBS),$(eval $(call LIB_TEMPLATE,$(DIR))))
$(foreach FILE,$(COBJS) $(SOBJS),$(eval $(call CC_TEMPLATE,$(FILE))))

OBJS = $(addsuffix .o,$(COBJS) $(SOBJS))

libgem.a: $(OBJS)
	$(AM_V_at)$(RM) $@
	$(AM_V_AR)$(AR) crs $@ $(OBJS)

clean::
	rm -rf .lib*

.PHONY: doc

ChangeLog:
	cvs log -d "20021201<" . >ChangeLog.tmp
	perl cvs2cl.pl --separate-header --no-wrap --usermap users --stdin --stdout <ChangeLog.tmp >ChangeLog
	rm -f ChangeLog.tmp
	
doc: Doxyfile ChangeLog mt_gem.h
	doxygen Doxyfile
# 	udo -s -l -W -y doc/udo/index.u -o doc/stg/gemlib.stg
# 	udo -h -l -W -y doc/udo/index.u -o doc/html/index.htm
	

# makefiles for compiler other than gcc
.PHONY: gcc gcc281 gcc28116 sox vbcc all-compilers zip
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

vbcc:
#68000 target (+mint : official config for vc for 68K target and mint)
	mkdir -p .vbcc; mkdir -p lib/vbcc; $(MAKE) -f vbcc.mak LIB_VBCC="lib/vbcc/libgem.a" MORE_CFLAGS="+mint" MORE_SFLAGS=""
#coldfire target (+mintcf : official config for vc for coldfire target and mint)
	$(MAKE) -f vbcc.mak LIB_VBCC="lib/vbcc/libgemv4e.a" MORE_CFLAGS="+mintcf" MORE_SFLAGS="-mv4e"
#68030 target (+mint : official config for vc for 68K target and mint)
	$(MAKE) -f vbcc.mak LIB_VBCC="lib/vbcc/libgem030.a" MORE_CFLAGS="+mint -cpu=68030" MORE_SFLAGS="-m68030"
#68000 mshort target (+mint16 : unofficial config for vc for 68K target and mint with mshort option, replace "vbccm68k" by "vbccm68ks" in mint config and rename it to mint16 )
	$(MAKE) -f vbcc.mak LIB_VBCC="lib/vbcc/libgem16.a" MORE_CFLAGS="+mint16" MORE_SFLAGS="-D__MSHORT__"

lattice:
	rm -f count.txt;
	echo 1 >> count.txt;
	mkdir -p .lattice; mkdir -p lib/lattice; make -f lat.mak LIB_LATTICE="lib/lattice/gem.lib" MORE_CFLAGS="" MORE_SFLAGS="" LATTICE_COUNT="1"
	rm -f count.txt;
	echo 1 >> count.txt;
	make -f lat.mak LIB_LATTICE="lib/lattice/gem30.lib" MORE_CFLAGS="-m3" MORE_SFLAGS=""
	rm -f count.txt

ahcc:
	mkdir -p lib/ahcc; make -f ahcc.mak LIB_AHCC="lib/ahcc/gem.lib"

zip:
	make -f zip.mak
	
all-compilers:
	rm -f *.o; mkdir -p lib/sozobon lib/gcc lib/gcc281 lib/vbcc lib/lattice include
	make -f sox.mak; rm -f *.o; 
	make -f gcc.mak; rm -f *.o; 
	make -f gcc281.mak; rm -f *.o; 
	make -f gcc281-16.mak; rm -f *.o;
	make -f vbcc.mak;
	make -f zip.mak

gemlib.spec: gemlib.spec.in VERSION
	$(AM_V_at)rm -f $@
	$(AM_V_GEN)sed 's,@VERSION@,$(VERSION),g' $@.in >$@

Doxyfile: Doxyfile.in VERSION
	$(AM_V_at)rm -f $@
	$(AM_V_GEN)sed 's,@VERSION@,$(VERSION),g' $@.in >$@

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
	@for i in $(ALL_LIBS); do \
            cpu=`echo $$i | cut -d . -f 1`; \
            if test $$cpu = 5475; then cpu=-mcpu=$$cpu; else cpu=-m$$cpu; fi; \
            flavour=`echo "$$i." | sed -e 's/\./ -m/g' -e 's/[^ ]* //' -e 's/-m$$//'`; \
            multilibdir=`$(CC) $$cpu $$flavour -print-multi-directory`; \
	    echo install $$i/libgem.a $(PREFIX)/lib/$$multilibdir/libgem.a; \
	    install -m 755 -d $(PREFIX)/lib/$$multilibdir; \
	    install -m 644 .lib$$i/libgem.a $(PREFIX)/lib/$$multilibdir/libgem.a; \
        done
	ln -sf mshort/libgem.a $(PREFIX)/lib/libgem16.a
	install -m 755 -d $(PREFIX)/include
	install -m 644 gem.h $(PREFIX)/include
	install -m 644 gemx.h $(PREFIX)/include
	install -m 644 mt_gem.h $(PREFIX)/include
	install -m 644 mt_gemx.h $(PREFIX)/include

uninstall:
	@for i in $(ALL_LIBS); do \
            cpu=`echo $$i | cut -d . -f 1`; \
            if test $$cpu = 5475; then cpu=-mcpu=$$cpu; else cpu=-m$$cpu; fi; \
            flavour=`echo "$$i." | sed -e 's/\./ -m/g' -e 's/[^ ]* //' -e 's/-m$$//'`; \
            multilibdir=`$(CC) $$cpu $$flavour -print-multi-directory`; \
	    echo rm $(PREFIX)/lib/libgem.a; \
	    rm -f $(PREFIX)/lib/$$multilibdir/libgem.a; \
        done
	rm -f $(PREFIX)/include/gem.h
	rm -f $(PREFIX)/include/gemx.h
	rm -f $(PREFIX)/include/mt_gem.h
	rm -f $(PREFIX)/include/mt_gemx.h
