# 
#   Copyright (C) 2003, 2004, 2005, 2006, 2007, 2008,
#		 2009 Free Software Foundation, Inc.
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

## Process this file with automake to generate Makefile.in

AUTOMAKE_OPTIONS = # dejagnu

FULLVERSION = $(VERSION).3

SUBDIRS = # testsuite

INCLUDES = -I$(srcdir) \
	$(MYSQL_CFLAGS)

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
	NEC.cc NEC.h nec_tables.h \
	MySQL.cc Database.h \
	log.h log.cc \
	err.h err.cc

# 	DataType.cc DataType.h

bin_PROGRAMS = neccalc gnuae

gnuae_SOURCES = Main.cc
gnuae_LDADD = -lgnuaec $(MYSQL_LIBS)

neccalc_SOURCES = NECcalc.cc
neccalc_LDADD = -lgnuaec $(MYSQL_LIBS)


