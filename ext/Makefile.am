## Process this file with automake to generate Makefile.in
# 
#   Copyright (C) 2005, 2006, 2007, 2008, 2009 Free Software Foundation, Inc.
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
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

AUTOMAKE_OPTIONS = 

pluginsdir = $(libdir)/gnuae/plugins

plugins_LTLIBRARIES = libphpgnuae.la

AM_CPPFLAGS = -DPHP_ATOM_INC \
	-I$(top_srcdir)/src \
	-I$(srcdir) \
	$(PHP_INCLUDES)

libphpgnuae_la_SOURCES = wrapper.c
libphpgnuae_la_LDFLAGS = -export-dynamic -avoid-version -module # -rpath $(phplibdir)
libphpgnuae_la_LIBADD = \
	../src/Battery.lo \
	../src/Centers.lo \
	../src/Chargers.lo \
	../src/Combiners.lo \
	../src/Inverters.lo \
	../src/Loads.lo \
	../src/NEC.lo \
	../src/PVPanel.lo \
	../src/PhantasmCalc.lo \
	../src/Pumps.lo \
	../src/SandiaCalc.lo \
	../src/Wire.lo

#libphp5_la_SOURCES = wrapper.c
#libphp5_la_LDFLAGS = $(EXTRA_LDFLAGS) $(LDFLAGS) #-rpath $(phptempdir)
#libphp5_la_LIBADD = $(PHP_RPATHS) $(PHP_GLOBAL_OBJS) $(PHP_SAPI_OBJS) $(EXTRA_LIBS) $(ZEND_EXTRA_LIBS)

#libphp4.la: $(PHP_GLOBAL_OBJS) $(PHP_SAPI_OBJS)
#	$(LIBTOOL) --mode=link $(CC) $(CFLAGS) $(EXTRA_CFLAGS) -rpath $(phptempdir) $(EXTRA_LDFLAGS) $(LDFLAGS) $(PHP_RPATHS) $(PHP_GLOBAL_OBJS) $(PHP_SAPI_OBJS) $(EXTRA_LIBS) $(ZEND_EXTRA_LIBS) -o $@
#	-@$(LIBTOOL) --silent --mode=install cp libphp4.la $(phptempdir)/libphp4.la >/dev/null 2>&1

#libs/libphp4.bundle: $(PHP_GLOBAL_OBJS) $(PHP_SAPI_OBJS)
#	$(CC) $(MH_BUNDLE_FLAGS) $(CFLAGS_CLEAN) $(EXTRA_CFLAGS) $(LDFLAGS) $(EXTRA_LDFLAGS) $(PHP_GLOBAL_OBJS:.lo=.o) $(PHP_SAPI_OBJS:.lo=.o) $(PHP_FRAMEWORKS) $(EXTRA_LIBS) $(ZEND_EXTRA_LIBS) -o $@ && cp $@ libs/libphp4.so

install: $(all_targets) $(install_targets)

install-sapi: $(OVERALL_TARGET)
	@echo "Installing PHP SAPI module:       $(PHP_SAPI)"
	-@$(mkinstalldirs) $(INSTALL_ROOT)$(bindir)
	-@if test ! -r $(phptempdir)/libphp4.$(SHLIB_SUFFIX_NAME); then \
		for i in 0.0.0 0.0 0; do \
			if test -r $(phptempdir)/libphp4.$(SHLIB_SUFFIX_NAME).$$i; then \
				$(LN_S) $(phptempdir)/libphp4.$(SHLIB_SUFFIX_NAME).$$i $(phptempdir)/libphp4.$(SHLIB_SUFFIX_NAME); \
				break; \
			fi; \
		done; \
	fi
	@$(INSTALL_IT)

install-modules: build-modules
	@test -d modules && \
	$(mkinstalldirs) $(INSTALL_ROOT)$(EXTENSION_DIR)
	@echo "Installing shared extensions:     $(INSTALL_ROOT)$(EXTENSION_DIR)/"
	@rm -f modules/*.la >/dev/null 2>&1
	@$(INSTALL) modules/* $(INSTALL_ROOT)$(EXTENSION_DIR)

install-tester:
	@echo "Installing regression tester:     $(INSTALL_ROOT)$(PEAR_INSTALLDIR)/"
	@$(mkinstalldirs) $(INSTALL_ROOT)$(PEAR_INSTALLDIR)
	@$(INSTALL) -m 755 $(top_srcdir)/run-tests.php $(INSTALL_ROOT)$(PEAR_INSTALLDIR)

install-su: install-pear install-tester

test: 
	@if test -x $(SAPI_CLI_PATH) && test ! -z $(SAPI_CLI_PATH); then \
		TEST_PHP_EXECUTABLE=$(top_builddir)/$(SAPI_CLI_PATH) \
		TEST_PHP_SRCDIR=$(top_srcdir) \
		CC="$(CC)" \
			$(top_builddir)/$(SAPI_CLI_PATH) -n -d 'open_basedir=' -d 'safe_mode=0' -d 'output_buffering=0' $(top_srcdir)/run-tests.php $(TESTS); \
	else \
		echo "ERROR: Cannot run tests without CLI sapi."; \
	fi

clean:
	find . -name \*.lo | xargs rm -f
	find . -name \*.o | xargs rm -f
	find . -name \*.la | xargs rm -f
	find . -name \*.a | xargs rm -f
	find . -name \*.so | xargs rm -f
	find . -name .libs -a -type d|xargs rm -rf
	rm -f libphp4.la $(SAPI_CLI_PATH) $(OVERALL_TARGET) modules/* libs/*

distclean: clean
	rm -f config.cache config.log config.status Makefile.objects Makefile.fragments libtool main/php_config.h stamp-h php4.spec sapi/apache/libphp4.module buildmk.stamp
	egrep define'.*include/php' configure|sed 's/.*>//'|xargs rm -f
	find . -name Makefile | xargs rm -f


.PHONY: all clean install distclean test
.NOEXPORT:
