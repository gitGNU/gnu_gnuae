
figdir = images
docname = gnuae
lang = C
omffile = gnuae.omf
entities = legal.xml
include $(top_srcdir)/doc/xmldocs.make
dist-hook: app-dist-hook
gnuae_helpdir = $(datadir)/gnome/help/$(docname)/C

gnuae_help_DATA =    \
        topic.dat       \
	gnuae.xml 

html: force
	mkdir -p html/stylesheet html/images
	rm -f html/stylesheet/*.png
	rm -f html/images/*.png
	xsltproc -v -o html/ $(srcdir)/stylesheets/general-customization.xsl $(srcdir)/gnuae.xml
	cp $(srcdir)/images/*.png html/images
	cp $(srcdir)/images/gnome-logo-icon.png html/stylesheet

# install GNOME help files, which are basically the html output
install-ghelp:
	$(mkinstalldirs) $(gnuae_helpdir)/stylesheet
	$(mkinstalldirs) $(gnuae_helpdir)/images
#	$(INSTALL_DATA) html/*.html $(gnuae_helpdir)
	$(INSTALL_DATA) $(srcdir)/*.xml $(gnuae_helpdir)
	$(INSTALL_DATA) html/stylesheet/*.png $(gnuae_helpdir)/stylesheet
	$(INSTALL_DATA) html/images/*.png $(gnuae_helpdir)/images

force:

scrollkeeper: 
	scrollkeeper-install /home/rob/projects/gnu/gnuae/gpv/doc/C/gnuae.omf

# scrollkeeper-install $(prefix)/gnuae.omf
# scrollkeeper-update $(prefix)/gnuae.omf
