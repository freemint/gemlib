Summary: Christian Felsch's GEM utility library
Name: cflib
Version: 12
Release: 1
Copyright: Public Domain
Group: Development/Libraries
Source: cflib-%{version}.tar.gz
BuildRoot: /var/tmp/cflib-root
Prefix: %{_prefix}
Packager: Guido Flohr <guido@freemint.de>
Vendor: Sparemint
Summary(de): Christian Felschs GEM-Utility-Bibliothek

# TODO for gemlib: The macros G_SHORTCUT and ED_CRSR were missing in
# cflib.  Add them to gemlib.  Same for that stupid portab.h header 
# file.  Then rebuild cflib without these patches and make it
# conflict with gemlib less or equal version 38 release 2.

%description
This is a utility library/toolkit that provide a lot of helper functions
for developping GEM applications.  Sorry, the documentation is all
German.

NOTE: This package has experimental support for installing ST-Guide
hypertexts with rpm.  They will get installed in /usr/GEM/stguide.
Please make sure that this directory is located on a file system that
supports long filenames.  You should then edit your stguide.inf to
make sure that ST-Guide will search that directory for hypertexts.
Also make sure that stool (or stool.tos or stool.ttp) is found either 
in /usr/GEM/stguide or in your $PATH.

You should install cflib if you would like to write GEM applications
that support recent GEM extensions without having to care about 
compatibility issues.

%description -l de
Dies ist eine Hilfsbibliothek bzw. ein Toolkit, das eine Menge nützlicher
Funktionen für die Entwicklung von GEM-Applikationen enthält.  Hurra,
die Dokumentation ist komplett auf Deutsch!

BEMERKUNG: Dieses Paket hat experimentellen Support für die Installation
von ST-Guide-Hypertexten. Sie werden in /usr/GEM/stguide installiert.
Dieses Verzeichnis muss auf einem Dateisystem liegen, dass lange
Dateinamen unterstützt.  Die Konfigurationsdatei stuide.inf sollte
entsprechend geändert werden, damit der ST-Guide in diesem Verzeichnis
nach Hypertexten sucht. Es ist ferner sicherzustellen, dass stool
(oder stool.tos oder stool.ttp) entweder in /usr/GEM/stguide oder
in $PATH gefunden werden kann.

Sie sollten die Cflib installieren, wenn Sie GEM-Applikationen schreiben
wollen, die alle neueren GEM-Erweiterungen unterstützen, ohne sich um 
den ganzen Kompatibilitäts-Kram kümmern zu müssen.

%prep
%setup -q -n cflib

%build
cd cflib

make

%install
cd cflib

rm -rf $RPM_BUILD_ROOT
mkdir -p "$RPM_BUILD_ROOT"%{_prefix}/GEM/{include,lib,stguide}
install -m 644 -o root -g wheel lib{cflib,cflib16}.a \
  "$RPM_BUILD_ROOT"%{_prefix}/GEM/lib
install -m 644 -o root -g wheel cflib.h \
  "$RPM_BUILD_ROOT"%{_prefix}/GEM/include
install -m 644 cflib.hyp \
  "$RPM_BUILD_ROOT"%{_prefix}/GEM/stguide
install -m 644 cflib.ref \
  "$RPM_BUILD_ROOT"%{_prefix}/GEM/stguide

# Don't confuse people that want to compile the demo application.
# rm demo/Makefile.sparemint

%clean
rm -rf $RPM_BUILD_ROOT

%post
# Try to run ST-Guide's stool.
found_stool=yes
PATH=%{_prefix}/GEM/stguide:/usr/GEM/stguide:/usr/GEM/bin:"$PATH"
export PATH
stool  >/dev/null 2>&1 || \
stool.tos  >/dev/null 2>&1 || \
stool.ttp  >/dev/null 2>&1 || \
found_stool=no
if test $found_stool = "no"; then
	exec 1>&2
	echo "WARNING: Could not run stool to update ST-Guide"
	echo "catalog file.  If you have stool you should "
	echo "install it in "%{_prefix}/GEM/stguide" or"
	echo "in your PATH as stool, stool.tos or stool.ttp."
fi

%postun
# Try to run ST-Guide's stool.
found_stool=yes
PATH=%{_prefix}/GEM/stguide:/usr/GEM/stguide:/usr/GEM/stguide:"$PATH"
export PATH
stool  >/dev/null 2>&1 || \
stool.tos  >/dev/null 2>&1 || \
stool.ttp  >/dev/null 2>&1 \
found_stool=no
if test $found_stool = "no"; then
	exec 1>&2
	echo "WARNING: Could not run stool to update ST-Guide"
	echo "catalog file.  If you have stool you should "
	echo "install it in "%{_prefix}/GEM/stguide" or"
	echo "in your PATH as stool, stool.tos or stool.ttp."
fi

# FIXME: How do we tell rpm that the ST-Guide hypertexts are really
# documentation but don't get installed in /usr/doc?
%files
%defattr(-,root,root)
%doc LiesMich LiesMich.src
%doc demo intrface
%{_prefix}/GEM/lib/lib*.a
%{_prefix}/GEM/include/*.h
%{_prefix}/GEM/stguide/cflib.hyp
%{_prefix}/GEM/stguide/cflib.ref

%changelog
* Sat Sep 16 2000 Frank Naumann <fnaumann@freemint.de>
- updated to new CVS maintained version

* Mon May 26 2000 Frank Naumann <fnaumann@freemint.de>
- patch in objc.c for new MiNTLib, replaced itoa by ltoa

* Mon Mar 27 2000 Frank Naumann <fnaumann@freemint.de>
- rebuild against new MiNTLib 0.55
- small patch for new MiNTLib
- removed CR in cflib.h

* Thu Oct 21 1999 Guido Flohr <guido@freemint.de>
- Initial version for Sparemint
