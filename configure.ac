dnl Process this file with autoconf to produce a configure script.

dnl  
dnl  Copyright (C) 2005, 2006, 2007, 2008, 2009 Free Software Foundation, Inc.
dnl  
dnl  This program is free software; you can redistribute it and/or modify
dnl  it under the terms of the GNU General Public License as published by
dnl  the Free Software Foundation; either version 3 of the License, or
dnl  (at your option) any later version.
dnl  
dnl  This program is distributed in the hope that it will be useful,
dnl  but WITHOUT ANY WARRANTY; without even the implied warranty of
dnl  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
dnl  GNU General Public License for more details.
dnl  You should have received a copy of the GNU General Public License
dnl  along with this program; if not, write to the Free Software
dnl  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
dnl  

AC_PREREQ(2.50)
AC_INIT(src/PVPanel.cc)
AM_CONFIG_HEADER(config.h)
AC_CONFIG_MACRO_DIR(macros)
dnl AC_CONFIG_SUBDIRS(gpv)

dnl These are required by automake
AM_INIT_AUTOMAKE(gnuae, 0.4)
AM_MAINTAINER_MODE
AC_PROG_MAKE_SET
AC_EXEEXT

AC_PROG_CC
AC_PROG_CC_C_O
AC_PROG_CXX
AC_PROG_INSTALL

dnl LT_INIT([dlopen win32-dll disable-static])
dnl LTDL_INIT([installable recursive])
AC_DISABLE_STATIC
AC_PROG_LIBTOOL

dnl Dont ever install libltdl
AM_CONDITIONAL(INSTALL_LTDL, test x"${enable_ltdl_install-no}" = xyes)
AM_CONDITIONAL(CONVENIENCE_LTDL, test x"${enable_ltdl_convenience-no}" != xno)

AC_SUBST(LIBTOOL_DEPS)                                                                                
AC_CHECK_HEADERS(values.h)

GAE_PATH_MYSQL

dnl Find the Tcl Shell, cause the "Clean.tcl program needs it when
dnl we build a release
dnl GAE_AC_PATH_TCLSH

GAE_AC_PATH_DEJAGNU

sinclude(php/acinclude.m4)

# Find Abelmon's libraries.
dnl GAE_AC_PATH_ABELMON

dnl AC_CHECK_LIB(abel, main)

dnl AC_ARG_ENABLE(gtkplot, [  --enable-gtkplot          Enable support for debug tracing],
dnl [case "${enableval}" in
dnl   yes) gtkplot=yes ;;
dnl   no)  gtkplot=no ;;
dnl   *)   AC_MSG_ERROR([bad value ${enableval} for enable-gtkplot option]) ;;
dnl esac])

dnl AM_CONDITIONAL(GTKPLOT, test x$gtkplot = xyes)
dnl if test x$gtkplot = xyes; then
dnl   AC_DEFINE(USE_GTKPLOT)
dnl   AM_PATH_GTK_EXTRA  
dnl fi

dnl AC_ARG_ENABLE(trace, [  --enable-trace          Enable support for debug tracing],
dnl [case "${enableval}" in
dnl   yes) trace=yes ;;
dnl   no)  trace=no ;;
dnl   *)   AC_MSG_ERROR([bad value ${enableval} for enable-trace option]) ;;
dnl esac])

dnl AM_CONDITIONAL(TRACE, test x$trace = xyes)
dnl if test x$trace = xyes; then
dnl   AC_DEFINE(USE_TRACING)
dnl fi

dnl AC_ARG_ENABLE(asserts, [  --enable-asserts        Enable support for assertions],
dnl [case "${enableval}" in
dnl   yes) asserts=yes ;;
dnl   no)  asserts=no ;;
dnl   *)   AC_MSG_ERROR(bad value ${enableval} for enable-assert option) ;;
dnl esac])

AC_OUTPUT(Makefile
src/Makefile
php/Makefile
src/testsuite/Makefile
)
