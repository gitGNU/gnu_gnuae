## Process this file with automake to generate Makefile.in

AUTOMAKE_OPTIONS = dejagnu

# RUNTESTDEFAULTFLAGS = --tool gnuae

RUNTEST = `if test -x $(top_srcdir)/../dejagnu/runtest; then \
              echo $(top_srcdir)/../dejagnu/runtest; \
           else \
              echo runtest; \
           fi`

# ABELPATH = @ABELPATH@
ABELPATH = ../../../abelmon/libabel
DL_LIB = @DL_LIB@ # @LIBADD_DL@
LIBLTDL = @LIBLTDL@
INCLTDL = @INCLTDL@

INCLUDES = -I$(ABELPATH)/include $(INCLTDL)

CLEANFILES = *.log *.sum site.bak

bin_PROGRAMS = tnec

tnec_SOURCES = tnec.cc
tnec_DEPENDENCIES = $(ABELPATH)/libabel.la $(LIBLTDL)
tnec_LDFLAGS = -module -avoid-version -no-undefined # "-dlopen" self
tnec_LDADD = $(ABELPATH)/libabel.la $(LIBLTDL) $(DL_LIB)

# tnec_DEPENDENCIES = libabel.la
 
