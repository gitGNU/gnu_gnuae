# 
#   Copyright (C) 2009, 2010 Free Software Foundation, Inc.
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

gnuae_la_SOURCES = wrapper.c
gnuae_la_LDFLAGS = -avoid-version -module -prefer-pic # -rpath $(phpdir)
gnuae_la_LIBADD = $(MYSQL_LIBS)  ../src/libgnuae.la -lstdc++

install: gnuae.la
	@echo "WARNING!"
	@echo "Since the GnuAE extemsion to PHP needs to go in a system"
	@echo "directory which requires root priviledges, you must use"
	@echo "sudo install-php insted"

install-php: $(php_LTLIBRARIES)
	@test -d "$(DESTDIR)$(pphpdir)" || $(mkinstalldirs) "$(DESTDIR)$(phpdir)"
	@echo "Installing PHP GnuAE extension to $(DESTDIR)$(phpdir)"
	@if test -d .libs; then \
	  $(INSTALL_DATA) .libs/gnuae.so $(DESTDIR)$(phpdir)/; \
	else \
	   $(INSTALL_DATA) gnuae.so $(DESTDIR)$(phpdir)/; \
	fi


