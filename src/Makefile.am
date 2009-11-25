# 
#   Copyright (C) 2004 Free Software Foundation, Inc.
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

FULLVERSION = $(VERSION).3

SUBDIRS = # testsuite

INCLUDES = #-I$(srcdir)/../../abelmon/libabel

# We don't need libdl cause we're not loading any shared modules directly
DL_LIB = # @DL_LIB@
LIBLTDL = # @LIBLTDL@
INCLTDL = # @INCLTDL@
# ABELLIB = ../../abelmon/libabel
ABELLIB =

lib_LTLIBRARIES = libgnuaec.la

libgnuaec_la_SOURCES = PVPanel.cc \
	Wire.cc Wire.h \
	SandiaCalc.cc SandiaCalc.h \
	PhantasmCalc.cc PhantasmCalc.h \
	Loads.cc Loads.h \
	Battery.cc Battery.h \
	Pumps.cc Pumps.h \
	Inverters.cc Inverters.h \
	Chargers.cc Chargers.h \
	Combiners.cc Combiners.h \
	Centers.cc Centers.h \
	NEC.cc NEC.h nec_tables.h

# 	DataType.cc DataType.h

bin_PROGRAMS = neccalc gnuae

gnuae_SOURCES = Main.cc
dnl gnuae_LDADD = $(ABELLIB)/libabel.la -lgnuaec $(LIBLTDL) "-dlopen" self
dnl gnuae_DEPENDENCIES = $(ABELLIB)/libabel.la libgnuaec.la $(LIBLTDL)
gnuae_LDADD = -lgnuaec $(LIBLTDL) "-dlopen" self
gnuae_DEPENDENCIES = libgnuaec.la $(LIBLTDL)

neccalc_SOURCES = NECcalc.cc
dnl neccalc_LDADD = $(ABELLIB)/libabel.la -lgnuaec $(LIBLTDL) "-dlopen" self
neccalc_LDADD = -lgnuaec $(LIBLTDL) "-dlopen" self
dnl neccalc_DEPENDENCIES = $(ABELLIB)/libabel.la libgnuaec.la $(LIBLTDL)
neccalc_DEPENDENCIES = libgnuaec.la $(LIBLTDL)


