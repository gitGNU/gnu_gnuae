## Process this file with automake to produce Makefile.in

SUBDIRS = src doc macros

EXTRA_DIST = \
	autogen.sh \
	gpv.glade

install-data-local:
	@$(NORMAL_INSTALL)
	if test -d $(srcdir)/pixmaps; then \
	  $(mkinstalldirs) $(DESTDIR)$(datadir)/pixmaps/$(PACKAGE); \
	  for pixmap in $(srcdir)/pixmaps/*; do \
	    if test -f $$pixmap; then \
	      $(INSTALL_DATA) $$pixmap $(DESTDIR)$(datadir)/pixmaps/$(PACKAGE); \
	    fi \
	  done \
	fi

html: force
	@cd doc/C ; make html

install-html: force
	@cd doc/C ; make install-html

dist-hook:
	if test -d pixmaps; then \
	  mkdir $(distdir)/pixmaps; \
	  for pixmap in pixmaps/*; do \
	    if test -f $$pixmap; then \
	      cp -p $$pixmap $(distdir)/pixmaps; \
	    fi \
	  done \
	fi


force:

# Build an RPM package
#rpm: dist $(srcdir)/redhat/gnuae.spec
#	cp -f $(srcdir)/redhat/gnuae.spec /usr/src/redhat/SPECS/
#	cp -f gnuae-${VERSION}.tar.gz /usr/src/redhat/SOURCES/
#	rpm -ba /usr/src/redhat/SPECS/gnuae.spec

# Build a Debian GNU/Linux package
#deb: dist
#	rm -rf gnuae-${VERSION}
#	tar xfz gnuae-${VERSION}.tar.gz
#	cp -fr $(srcdir)/debian/deb gnuae-${VERSION}/
#	(cd gnuae-${VERSION}; dpkg-buildpackage)

# Most proprietary Unices use /opt for optional packages.
PKGDIR = /opt

#$(PKGDIR)/gnuae:
#	rm -rf gnuae-${VERSION}
#	mkdir gnuae-${VERSION}
#	cd gnuae-${VERSION}
#	$(srcdir)/configure -v --prefix $@
#	make install

