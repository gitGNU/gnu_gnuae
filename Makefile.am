# 
#   Copyright (C) 2003 Free Software Foundation, Inc.
#
#   This program is free software; you can redistribute it and/or modify
#   it under the terms of the GNU General Public License as published by
#   the Free Software Foundation; either version 2 of the License, or
#   (at your option) any later version.
#
#   This program is distributed in the hope that it will be useful,
#   but WITHOUT ANY WARRANTY; without even the implied warranty of
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#   GNU General Public License for more details.
#
#   You should have received a copy of the GNU General Public License
#   along with this program; if not, write to the Free Software
#   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
#

## Process this file with automake to generate Makefile.in

AUTOMAKE_OPTIONS = # dejagnu

SUBDIRS = src gpv # libltdl 

FULLVERSION = 0.3.0
VERSION = 0.3

# Set ourselves up to build a RedHat package. The "dist" target used by
# Automake isn't sufficient tp dop more than build a tarball
tarball: 
	-rm -fr gnuae-${FULLVERSION}
	cp -fpr $(srcdir) gnuae-${FULLVERSION}
	@echo "clean up stuff we don't want in the source file"
	-mkdir -p gpv/doc/C/html
	-cp -fr gpv/doc/C/html gnuae-${FULLVERSION}/doc/
	tar cvf ../gnuae-${FULLVERSION}.tar gnuae-${FULLVERSION}
	bzip2 -9kfv ../gnuae-${FULLVERSION}.tar
	gzip -9fv ../gnuae-${FULLVERSION}.tar
	cp -f ../gnuae-${FULLVERSION}.tar.gz /usr/src/redhat/SOURCES/

rpmspec:
	cp -f $(srcdir)/redhat/gnuae.spec /usr/src/redhat/SPECS/

rpm: tarball rpmspec
	cp -f ../gnuae-${FULLVERSION}.tar.gz /usr/src/redhat/SOURCES/
	cp -f ../gnuae-${FULLVERSION}.tar.bz2 /usr/src/redhat/SOURCES/
	rpmbuild -ba $(srcdir)/redhat/gnuae.spec

# Build a Debian GNU/Linux package
deb: tarball
#	rm -rf gnuae-${FULLVERSION}
#	tar zxfz ../gnuae-${FULLVERSION}.tar.gz
	cp -fr $(srcdir)/debian gnuae-${FULLVERSION}/
	(cd gnuae-${FULLVERSION}; dpkg-buildpackage -d)


install-doc doc html dvi ps pdf rtf:
	cd gpv/doc && $(MAKE) $(FLAGS_TO_PASS) $@
