dnl Process this file with autoconf to produce a configure script.
AC_PREREQ(2.50)
AC_INIT(src/PVPanel.cc)
AM_CONFIG_HEADER(config.h)

AC_CONFIG_SUBDIRS(ext gpv)
dnl AC_CONFIG_SUBDIRS(gpv libltdl)

dnl These are required by automake
AM_INIT_AUTOMAKE(gnuae, 0.3)
AM_MAINTAINER_MODE
AC_PROG_MAKE_SET
AC_EXEEXT

AC_PROG_CC
AC_PROG_CXX
AC_PROG_INSTALL

AC_LIBTOOL_DLOPEN
AC_LIBLTDL_CONVENIENCE
AC_PROG_LIBTOOL

AC_SUBST(INCLTDL)
AC_SUBST(LIBLTDL)

DLOPEN="-dlopen"
DLPREOPEN="-dlpreopen"
AC_SUBST(DLOPEN)
AC_SUBST(DLPREOPEN)
                                                                                
dnl Substitute INCLTDL and LIBLTDL in the Makefiles
AC_SUBST(INCLTDL)
AC_SUBST(LIBLTDL)
AC_SUBST(LIBTOOL_DEPS)
                                                                                
AC_CHECK_HEADERS(values.h)

dnl See which dynamic library reader we can use
AC_CHECK_HEADERS(dlfcn.h dl.h)
AC_CHECK_LIB(dld, shl_load, DL_LIB="-ldld",[
        AC_CHECK_LIB(dl, dlopen, DL_LIB="-ldl",
AC_MSG_ERROR(Dynamic linking is not available on this platform.  Some
apps, like panel, will not run properly.))
])
AC_SUBST(DL_LIB)

dnl Find the Tcl Shell, cause the "Clean.tcl program needs it when
dnl we build a release
dnl GAE_AC_PATH_TCLSH

GAE_AC_PATH_DEJAGNU

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

dnl AM_CONDITIONAL(CYGWIN, test x$CYGWIN = xyes)

dnl AC_CONFIG_SUBDIRS(example/calc)

dnl AC_CONFIG_LINKS(ext/NEC.cc:src/NEC.cc)
dnl AC_CONFIG_LINKS(ext/NEC.cpp:src/NEC.cc)

AC_OUTPUT(Makefile
src/Makefile
src/testsuite/Makefile
)