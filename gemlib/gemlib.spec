Summary: GEM libraries and header files
Name: gemlib
Version: 38
Release: 5
Copyright: Public Domain
Group: Development/Libraries
Source: gemlib-%{version}.tar.gz
Patch0: gemlib38-config.patch
BuildRoot: /var/tmp/gemlib38-root
Packager: Guido Flohr <guido@freemint.de>
Vendor: Sparemint
Summary(de): GEM-Bibliothek und Header-Dateien

%description
Contains the standard libraries and header files to develop your own GEM
applications.

%description -l de
Enthält die Standard-Bibliotheken und Header-Dateien, die benötigt werden, 
um GEM-Programme selbst zu entwickeln.

%prep
%setup -q
%patch0 -p1

%build
cd gemlib

make

%install
cd gemlib

rm -rf $RPM_BUILD_ROOT
mkdir -p $RPM_BUILD_ROOT/usr/GEM
mkdir -p $RPM_BUILD_ROOT/usr/GEM/{include,lib}
install -m 644 -o root -g wheel lib{gem,gem16}.a \
  $RPM_BUILD_ROOT/usr/GEM/lib
install -m 644 -o root -g wheel include/{gem,gemx}.h \
  $RPM_BUILD_ROOT/usr/GEM/include

%clean
rm -rf $RPM_BUILD_ROOT

%files
%defattr(-,root,root)
%doc ChangeLog*
/usr/GEM/lib/lib*.a
/usr/GEM/include/*.h

%changelog
* Sat Sep 16 2000 Frank Naumann <fnaumann@freemint.de>
- updated to new version

* Mon Mar 27 2000 Frank Naumann <fnaumann@freemint.de>
- rebuild against new MiNTLib 0.55

* Wed Aug 11 1999 Guido Flohr <guido@freemint.de>
- Changed vendor to Sparemint
