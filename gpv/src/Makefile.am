## Process this file with automake to produce Makefile.in

INCLTDL = -I${top_srcdir}/../libltdl
INSTALL_STRIP_PROGRAM = ${SHELL} $(install_sh) -c -s
LIBLTDL = ../../libltdl/libltdlc.la
ABELLIB = ../../../abelmon/libabel

INCLUDES = -I$(top_srcdir)/../../abelmon/libabel \
	-I$(top_srcdir)/../src \
	-I$(srcdir)/../gstripchart/src \
	$(GNOME_INCLUDEDIR) \
	$(LIBGUPPI_CFLAGS) \
	$(GTK_EXTRA_CFLAGS)

bin_PROGRAMS = gpv # ngpv
if GTKPLOT
  noinst_PROGRAMS = testgtkplot3d testpixmap #demo
endif

NECLIB = -L../../src -lgnuaec -lstdc++ $(LIBLTDL) "-dlopen" self

#ngpv_SOURCES = \
#	gpv.c gpv.h \
#	2dplot.c \
#	3dplot.c \
#	gtksup.c 


#ngpv_LDADD = $(GNOME_LIBDIR) $(GNOMEUI_LIBS) \
#	     $(GTK_EXTRA_LIBS)
#ngpv_DEPENDENCIES = $(LIBLTDL)

if GTKPLOT
	PLOT = gtkplot.c # guppi.c
	GTKPLOT_LIBS = $(GTK_EXTRA_LIBS)
endif

gpv_SOURCES = \
	main.c \
	support.c support.h \
	interface.c interface.h \
	callbacks.c callbacks.h \
	system.c $(PLOT)

gpv_LDADD = $(GNOME_LIBDIR) \
	$(GNOMEUI_LIBS) \
	$(LIBGUPPI_LIBS) \
	$(NECLIB)

gpv_DEPENDENCIES = $(LIBLTDL) ../../src/libgnuaec.la

# demo_SOURCES = demo.c
# demo_LDADD = /usr/local/lib/libguppi.la \
# 	/usr/local/lib/libguppitank.la \
# 	$(LIBGUPPI_LIBS)

testpixmap_SOURCES = testpixmap.c
# testpixmap_LDFLAGS = $(LDADDS)
testpixmap_LDADD = $(GTK_EXTRA_LIBS) # $(GTK_LIBS)

testgtkplot3d_SOURCES = testgtkplot3d.c
testgtkplot3d_LDADD = $(GTK_EXTRA_LIBS) # $(GTK_LIBS)
