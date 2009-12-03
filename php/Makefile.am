# 
#   Copyright (C) 2003, 2004, 2005, 2006, 2007, 2008,
#	 	2009 Free Software Foundation, Inc.
# 
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3 of the License, or
# (at your option) any later version.
# 
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

AUTOMAKE_OPTIONS = 

phpdir = $(EXTENSION_DIR)

php_LTLIBRARIES = gnuae.la

AM_CPPFLAGS = -DPHP_ATOM_INC \
	-I$(top_srcdir)/src \
	-I$(srcdir) \
	$(PHP_INCLUDES)

ALL_OBJS = $(wildcard ../src/*.o)

gnuae_la_SOURCES = wrapper.c
gnuae_la_LDFLAGS = -export-dynamic -avoid-version -module # -rpath $(phplibdir)
gnuae_la_LIBADD = $(ALL_OBJS) $(MYSQL_LIBS) -lstdc++

install: gnuae.la
	@echo "WARNING!"
	@echo "Since the GnuAE extemsion to PHP needs to go in a system"
	@echo "directory which requires root priviledges, you must use"
	@echo "sudo install-php insted"

install-php: $(plugin_LTLIBRARIES)
	@test -d "$(DESTDIR)$(pphpdir)" || $(mkinstalldirs) "$(DESTDIR)$(phpdir)"
	@echo "Installing PHP GnuAE extension to $(DESTDIR)$(phpdir)"
	@if test -d .libs; then \
	  cp -f .libs/gnuae.so* $(DESTDIR)$(phpdir)/; \
	else \
	  cp -f gnuae.so* $(DESTDIR)$(phpdir)/; \
	fi


