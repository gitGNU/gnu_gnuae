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

SUBDIRS = libltdl src gpv 

TLCSH = @TCLSH@
FULLVERSION = $(VERSION).0

# Set ourselves up to build a RedHat package
dist2: rpmspec overview.html
	-rm -fr gnuae-${FULLVERSION}
	cp -fpr $(srcdir) gnuae-${FULLVERSION}
	@echo "clean up stuff we don't want in the source file"
	(cd gnuae-${FULLVERSION} ; $(srcdir)/Clean.tcl)
	-mkdir -p doc/overview
	-cp -fr doc/overview gnuae-${FULLVERSION}/doc/
	tar cvf ../gnuae-${FULLVERSION}.tar gnuae-${FULLVERSION}
	gzip -9fv ../gnuae-${VERSION}.tar
	cp -f ../gnuae-${FULLVERSION}.tar.gz /usr/src/redhat/SOURCES/
	cp -f $(srcdir)/redhat/gnuae.spec /usr/src/redhat/SPECS/

rpmspec:
	cp -f $(srcdir)/redhat/gnuae.spec /usr/src/redhat/SPECS/

rpm: dist rpmspec
	cp -f $(distdir).tar.gz /usr/src/redhat/SOURCES/
	rpm -ba /usr/src/redhat/SPECS/gnuae.spec

overview.html install-doc doc html dvi ps pdf rtf:
	cd doc && $(MAKE) $(FLAGS_TO_PASS) $@

# Automake sucks when it comes to building a distribution, so
# we just copy the source tree onto of what Automake did, and
# then we Sanitize it. Automake only includes the source files.
# We want all the testsuites, data files, and html versions of the doc.
dist-hook: rpmspec overview.html
	-rm -fr $(distdir)
	cp -fpr $(srcdir) $(distdir)
	(cd $(distdir) ; $(TCLSH) $(srcdir)/Clean.tcl)
	-cp -fr doc/overview $(distdir)/doc/
