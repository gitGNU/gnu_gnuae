## Process this file with automake to generate Makefile.in

AUTOMAKE_OPTIONS = dejagnu

# RUNTESTDEFAULTFLAGS = --tool gnuae

GNUAELIB = ../libgnuae.la

INCLUDES = -I$(top_srcdir)/src 

CLEANFILES = *.log *.sum site.bak

check_PROGRAMS = tnec gdata guitest

tnec_SOURCES = tnec.cc
tnec_LDADD = $(MYSQL_LIBS) $(GNUAELIB)

# tnec_DEPENDENCIES = libabel.la

gdata_SOURCES = gdata.cc
gdata_LDADD = $(MYSQL_LIBS) $(GNUAELIB)

guitest_SOURCES = guitest.c
guitest_LDADD = $(MYSQL_LIBS) $(GNUAELIB) 
