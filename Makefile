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

all-here: libs

dist: distdir
	-chmod -R a+r $(distdir) 
	GZIP=$(GZIP) $(TAR) chzf $(distdir).tar.gz $(distdir)
	-rm -rf $(distdir)

# default overwrites

# default definitions
GENFILES = .lib* libgem*.a
GENFILES += mt_gem.h Doxyfile gemlib.spec
GENFILES += html

ifeq ($(MULTILIBDIRS),)
	# gcc don't supports multilibs --> old stuff

ALL_LIBS = normal mshort

ifeq ($(WITH_020_LIB),yes)
ALL_LIBS += m68020 m68020mshort
endif

ifeq ($(WITH_V4E_LIB),yes)
ALL_LIBS += m5475 m5475mshort
endif

else
	ALL_LIBS = $(patsubst %,.mlibs/%/libgem.a, $(MULTILIBDIRS))
endif




libs: $(ALL_LIBS)

normal:
	$(MAKE) libgem.a TARGET=""

mshort:
	$(MAKE) libgem16.a TARGET="16"

m68020:
	$(MAKE) libgem020.a TARGET="020"

m68020mshort:
	$(MAKE) libgem02016.a TARGET="02016"

m5475:
	$(MAKE) libgemv4e.a TARGET="v4e"

m5475mshort:
	$(MAKE) libgemv4e16.a TARGET="v4e16"

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

define MULTI_TEMPLATE
.mlibs/$(1) :
	$$(AM_V_at)$$(MKDIR) -p $$@
.mlibs/$(1)/libgem.a : GENERAL += $(call MULTILIBFLAGS,$(1))
.mlibs/$(1)/libgem.a : mt_gem.h .mlibs/$(1) $(addprefix .mlibs/$(1)/, $(COBJS:.c=.o) $(SOBJS:.S=.o))
	$$(AM_V_at)$$(RM) $$@
	$$(AM_V_AR)$$(AR) rc $$@ $(addprefix .mlibs/$(1)/, $(COBJS:.c=.o) $(SOBJS:.S=.o))
	$(AM_V_RANLIB)$(RANLIB) $$@

endef
$(foreach DIR,$(MULTILIBDIRS),$(eval $(call MULTI_TEMPLATE,$(DIR))))

libgem$(TARGET).a: objs
	$(AM_V_at)$(RM) $@
	$(AM_V_AR)$(AR) rc $@ \
		$(shell for file in `cat .lib$(TARGET)/objs` ; \
			do echo .lib$(TARGET)/$$file ; done)
	$(AM_V_RANLIB)$(RANLIB) $@

objs: .lib$(TARGET) mt_gem.h
	cd .lib$(TARGET); $(MAKE)

.lib$(TARGET):
	$(AM_V_at)$(MKDIR) $@
	$(AM_V_at)$(CP) Makefile.objs $@/Makefile

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
ifeq ($(MULTILIBDIRS),)
	# gcc don't supports multilibs --> old stuff
	install -m 755 -d $(PREFIX)/lib
	install -m 644 libgem.a $(PREFIX)/lib/libgem.a
	install -m 755 -d $(PREFIX)/lib/mshort
	install -m 644 libgem16.a $(PREFIX)/lib/mshort/libgem.a
	ln -sf mshort/libgem.a $(PREFIX)/lib/libgem16.a
ifeq ($(WITH_020_LIB),yes)
	install -m 755 -d $(PREFIX)/lib/m68020-60
	install -m 644 libgem020.a $(PREFIX)/lib/m68020-60/libgem.a
	install -m 755 -d $(PREFIX)/lib/m68020-60/mshort
	install -m 644 libgem02016.a $(PREFIX)/lib/m68020-60/mshort/libgem.a
endif
ifeq ($(WITH_V4E_LIB),yes)
	install -m 755 -d $(PREFIX)/lib/m5475
	install -m 644 libgemv4e.a $(PREFIX)/lib/m5475/libgem.a
	install -m 755 -d $(PREFIX)/lib/m5475/mshort
	install -m 644 libgemv4e16.a $(PREFIX)/lib/m5475/mshort/libgem.a
endif
else
	for lib in $(MULTILIBDIRS); do \
		install -m 755 -d $(PREFIX)/lib/$$lib; \
		install -m 644 ./.mlibs/$$lib/libgem.a $(PREFIX)/lib/$$lib/libgem.a; \
	done
endif
	install -m 755 -d $(PREFIX)/include
	install -m 644 gem.h $(PREFIX)/include
	install -m 644 gemx.h $(PREFIX)/include
	install -m 644 mt_gem.h $(PREFIX)/include
	install -m 644 mt_gemx.h $(PREFIX)/include

uninstall:
ifeq ($(MULTILIBDIRS),)
	rm -f $(PREFIX)/lib/libgem.a
	rm -f $(PREFIX)/lib/libgem16.a
	rm -f $(PREFIX)/lib/mshort/libgem.a
ifeq ($(WITH_020_LIB),yes)
	rm -f $(PREFIX)/lib/m68020-60/libgem.a
	rm -f $(PREFIX)/lib/m68020-60/mshort/libgem.a
endif
ifeq ($(WITH_V4E_LIB),yes)
	rm -f $(PREFIX)/lib/m5475/libgem.a
	rm -f $(PREFIX)/lib/m5475/mshort/libgem.a
endif
else
	for lib in $(MULTILIBDIRS); do \
		rm -f $(PREFIX)/lib/$$lib; \
	done
endif
	rm -f $(PREFIX)/include/gem.h
	rm -f $(PREFIX)/include/gemx.h
	rm -f $(PREFIX)/include/mt_gem.h
	rm -f $(PREFIX)/include/mt_gemx.h

ifneq ($(MULTILIBDIRS),)
include $(top_srcdir)/DEPENDENCIES
endif
