%define version 0.3
%define release 0

Summary:   GNU Alternate Energy Design System
Name:      gnuae
Version:   %{version}
Release:   %{release}
Copyright: GPL
Group:     Applications/System          
BuildRoot: /usr/src/redhat/BUILD/gnuae/gnuae-%{version}.%{release}
Source: ftp://ftp.gnu.org/gnu/gnuae/snapshots/gnuae-%{version}.%{release}.tar.gz
Provides:  gnuae

%description
GnuAE is a program for designing power systems for off grid houses.

%prep
%setup -q -n gnuae-%{version}.%{release}

%build
./configure --disable-shared
make
                                                                                 
%install
rm -rf $RPM_BUILD_ROOT
mkdir -p $RPM_BUILD_ROOT/usr
mkdir -p $RPM_BUILD_ROOT/usr/include
mkdir -p $RPM_BUILD_ROOT/usr/share/gnuae
mkdir -p $RPM_BUILD_ROOT/usr/share/pixmaps
mkdir -p $RPM_BUILD_ROOT/usr/share/gnome/help/gnuae/C/images
mkdir -p $RPM_BUILD_ROOT/usr/share/gnome/help/gnuae/C/stylesheet
mkdir -p $RPM_BUILD_ROOT/usr/share/omf/gpv/
mkdir -p $RPM_BUILD_ROOT/usr/doc/gnuae-%{version}.%{release}
make prefix=$RPM_BUILD_ROOT/usr install
#make prefix=$RPM_BUILD_ROOT/usr install-html
                                                                                 
%clean
rm -rf $RPM_BUILD_ROOT

%files
%defattr(-,root,root)
"/./usr/bin/gnuae"
"/./usr/bin/gpv"
"/./usr/bin/neccalc"
"/./usr/lib/libgnuaec.a"
"/./usr/lib/libgnuaec.la"
"/./usr/share/gnome/help/gnuae/C/gnuae.xml"
"/./usr/share/gnome/help/gnuae/C/topic.dat"
"/./usr/share/gpv/doc/gnuae/C/gnuae.xml"
"/./usr/share/gpv/doc/gnuae/C/images/abelditch.png"
"/./usr/share/gpv/doc/gnuae/C/images/abel-drilling.png"
"/./usr/share/gpv/doc/gnuae/C/images/abelgen.png"
"/./usr/share/gpv/doc/gnuae/C/images/add-pv.png"
"/./usr/share/gpv/doc/gnuae/C/images/air-dome.png"
"/./usr/share/gpv/doc/gnuae/C/images/array.png"
"/./usr/share/gpv/doc/gnuae/C/images/barerack.png"
"/./usr/share/gpv/doc/gnuae/C/images/batt01.png"
"/./usr/share/gpv/doc/gnuae/C/images/battery-browser.png"
"/./usr/share/gpv/doc/gnuae/C/images/blank.png"
"/./usr/share/gpv/doc/gnuae/C/images/booster.png"
"/./usr/share/gpv/doc/gnuae/C/images/broadband-ant.png"
"/./usr/share/gpv/doc/gnuae/C/images/caution.png"
"/./usr/share/gpv/doc/gnuae/C/images/chargerbrowser.png"
"/./usr/share/gpv/doc/gnuae/C/images/controllers-browser.png"
"/./usr/share/gpv/doc/gnuae/C/images/display-active.png"
"/./usr/share/gpv/doc/gnuae/C/images/domespread.png"
"/./usr/share/gpv/doc/gnuae/C/images/draft.png"
"/./usr/share/gpv/doc/gnuae/C/images/edit-load.png"
"/./usr/share/gpv/doc/gnuae/C/images/fridge.png"
"/./usr/share/gpv/doc/gnuae/C/images/gnome-logo-icon.png"
"/./usr/share/gpv/doc/gnuae/C/images/home.png"
"/./usr/share/gpv/doc/gnuae/C/images/honda.png"
"/./usr/share/gpv/doc/gnuae/C/images/important.png"
"/./usr/share/gpv/doc/gnuae/C/images/interconnects.png"
"/./usr/share/gpv/doc/gnuae/C/images/inverter-browser.png"
"/./usr/share/gpv/doc/gnuae/C/images/laptop.png"
"/./usr/share/gpv/doc/gnuae/C/images/load.png"
"/./usr/share/gpv/doc/gnuae/C/images/MainWindow.png"
"/./usr/share/gpv/doc/gnuae/C/images/mx60.png"
"/./usr/share/gpv/doc/gnuae/C/images/nec-calc.png"
"/./usr/share/gpv/doc/gnuae/C/images/newpv.png"
"/./usr/share/gpv/doc/gnuae/C/images/next.png"
"/./usr/share/gpv/doc/gnuae/C/images/note.png"
"/./usr/share/gpv/doc/gnuae/C/images/panels.png"
"/./usr/share/gpv/doc/gnuae/C/images/phone-ant.png"
"/./usr/share/gpv/doc/gnuae/C/images/portablepower.png"
"/./usr/share/gpv/doc/gnuae/C/images/power-wall1.png"
"/./usr/share/gpv/doc/gnuae/C/images/power-wall2.png"
"/./usr/share/gpv/doc/gnuae/C/images/prev.png"
"/./usr/share/gpv/doc/gnuae/C/images/pvbrowser.png"
"/./usr/share/gpv/doc/gnuae/C/images/pvcombiner.png"
"/./usr/share/gpv/doc/gnuae/C/images/rewire01.png"
"/./usr/share/gpv/doc/gnuae/C/images/rewire04.png"
"/./usr/share/gpv/doc/gnuae/C/images/rewire06.png"
"/./usr/share/gpv/doc/gnuae/C/images/shed.png"
"/./usr/share/gpv/doc/gnuae/C/images/solarboost50.png"
"/./usr/share/gpv/doc/gnuae/C/images/tip.png"
"/./usr/share/gpv/doc/gnuae/C/images/toc-blank.png"
"/./usr/share/gpv/doc/gnuae/C/images/toc-minus.png"
"/./usr/share/gpv/doc/gnuae/C/images/toc-plus.png"
"/./usr/share/gpv/doc/gnuae/C/images/tower.png"
"/./usr/share/gpv/doc/gnuae/C/images/trace4024.png"
"/./usr/share/gpv/doc/gnuae/C/images/truckant.png"
"/./usr/share/gpv/doc/gnuae/C/images/up.png"
"/./usr/share/gpv/doc/gnuae/C/images/warning.png"
"/./usr/share/gpv/doc/gnuae/C/images/wiring.png"
"/./usr/share/gpv/doc/gnuae/C/legal.xml"
"/./usr/share/omf/gpv/gnuae.omf"
"/./usr/share/pixmaps/gpv/main.png"
"/./usr/share/pixmaps/gpv/sslogo.jpg"
# If we don't add the scrollkeeper files, rpmbuild refuses to complete.
"/./usr/var/scrollkeeper/C/scrollkeeper_cl.xml"
"/./usr/var/scrollkeeper/C/scrollkeeper_extended_cl.xml"
"/./usr/var/scrollkeeper/am/scrollkeeper_cl.xml"
"/./usr/var/scrollkeeper/am/scrollkeeper_extended_cl.xml"
"/./usr/var/scrollkeeper/az/scrollkeeper_cl.xml"
"/./usr/var/scrollkeeper/az/scrollkeeper_extended_cl.xml"
"/./usr/var/scrollkeeper/be/scrollkeeper_cl.xml"
"/./usr/var/scrollkeeper/be/scrollkeeper_extended_cl.xml"
"/./usr/var/scrollkeeper/ca/scrollkeeper_cl.xml"
"/./usr/var/scrollkeeper/ca/scrollkeeper_extended_cl.xml"
"/./usr/var/scrollkeeper/cs/scrollkeeper_cl.xml"
"/./usr/var/scrollkeeper/cs/scrollkeeper_extended_cl.xml"
"/./usr/var/scrollkeeper/da/scrollkeeper_cl.xml"
"/./usr/var/scrollkeeper/da/scrollkeeper_extended_cl.xml"
"/./usr/var/scrollkeeper/de/scrollkeeper_cl.xml"
"/./usr/var/scrollkeeper/de/scrollkeeper_extended_cl.xml"
"/./usr/var/scrollkeeper/el/scrollkeeper_cl.xml"
"/./usr/var/scrollkeeper/el/scrollkeeper_extended_cl.xml"
"/./usr/var/scrollkeeper/es/scrollkeeper_cl.xml"
"/./usr/var/scrollkeeper/es/scrollkeeper_extended_cl.xml"
"/./usr/var/scrollkeeper/fr/scrollkeeper_cl.xml"
"/./usr/var/scrollkeeper/fr/scrollkeeper_extended_cl.xml"
"/./usr/var/scrollkeeper/hu/scrollkeeper_cl.xml"
"/./usr/var/scrollkeeper/hu/scrollkeeper_extended_cl.xml"
"/./usr/var/scrollkeeper/it/scrollkeeper_cl.xml"
"/./usr/var/scrollkeeper/it/scrollkeeper_extended_cl.xml"
"/./usr/var/scrollkeeper/ja/scrollkeeper_cl.xml"
"/./usr/var/scrollkeeper/ja/scrollkeeper_extended_cl.xml"
"/./usr/var/scrollkeeper/kn/scrollkeeper_cl.xml"
"/./usr/var/scrollkeeper/kn/scrollkeeper_extended_cl.xml"
"/./usr/var/scrollkeeper/ko/scrollkeeper_cl.xml"
"/./usr/var/scrollkeeper/ko/scrollkeeper_extended_cl.xml"
"/./usr/var/scrollkeeper/nl/scrollkeeper_cl.xml"
"/./usr/var/scrollkeeper/nl/scrollkeeper_extended_cl.xml"
"/./usr/var/scrollkeeper/no/scrollkeeper_cl.xml"
"/./usr/var/scrollkeeper/no/scrollkeeper_extended_cl.xml"
"/./usr/var/scrollkeeper/pl/scrollkeeper_cl.xml"
"/./usr/var/scrollkeeper/pl/scrollkeeper_extended_cl.xml"
"/./usr/var/scrollkeeper/pt_BR/scrollkeeper_cl.xml"
"/./usr/var/scrollkeeper/pt_BR/scrollkeeper_extended_cl.xml"
"/./usr/var/scrollkeeper/ro/scrollkeeper_cl.xml"
"/./usr/var/scrollkeeper/ro/scrollkeeper_extended_cl.xml"
"/./usr/var/scrollkeeper/ru/scrollkeeper_cl.xml"
"/./usr/var/scrollkeeper/ru/scrollkeeper_extended_cl.xml"
"/./usr/var/scrollkeeper/scrollkeeper_docs"
"/./usr/var/scrollkeeper/sk/scrollkeeper_cl.xml"
"/./usr/var/scrollkeeper/sk/scrollkeeper_extended_cl.xml"
"/./usr/var/scrollkeeper/sl/scrollkeeper_cl.xml"
"/./usr/var/scrollkeeper/sl/scrollkeeper_extended_cl.xml"
"/./usr/var/scrollkeeper/sr/scrollkeeper_cl.xml"
"/./usr/var/scrollkeeper/sr/scrollkeeper_extended_cl.xml"
"/./usr/var/scrollkeeper/sr@Latn/scrollkeeper_cl.xml"
"/./usr/var/scrollkeeper/sr@Latn/scrollkeeper_extended_cl.xml"
"/./usr/var/scrollkeeper/sv/scrollkeeper_cl.xml"
"/./usr/var/scrollkeeper/sv/scrollkeeper_extended_cl.xml"
"/./usr/var/scrollkeeper/tr/scrollkeeper_cl.xml"
"/./usr/var/scrollkeeper/tr/scrollkeeper_extended_cl.xml"
"/./usr/var/scrollkeeper/uk/scrollkeeper_cl.xml"
"/./usr/var/scrollkeeper/uk/scrollkeeper_extended_cl.xml"
"/./usr/var/scrollkeeper/vi/scrollkeeper_cl.xml"
"/./usr/var/scrollkeeper/vi/scrollkeeper_extended_cl.xml"
"/./usr/var/scrollkeeper/zh_CN/scrollkeeper_cl.xml"
"/./usr/var/scrollkeeper/zh_CN/scrollkeeper_extended_cl.xml"
"/./usr/var/scrollkeeper/zh_TW/scrollkeeper_cl.xml"
"/./usr/var/scrollkeeper/zh_TW/scrollkeeper_extended_cl.xml"
 


%doc COPYING NEWS README AUTHORS INSTALL ChangeLog
                                                                                 
%changelog
* Sat Sep 18 2004 Rob Savoye <rob@senecass.com>
- Initial creation
